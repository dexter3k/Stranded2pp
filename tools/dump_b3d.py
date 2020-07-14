#!/usr/bin/env python2

import sys
import struct

def int32(data):
	assert len(data) == 4
	return struct.unpack('i', data)[0]

def float32(data):
	assert len(data) == 4
	return struct.unpack('f', data)[0]

def hexColor(data):
	assert len(data) == 4
	return (hex(int(data[0] * 255))[2:4].zfill(2)
		+ hex(int(data[1] * 255))[2:4].zfill(2)
		+ hex(int(data[2] * 255))[2:4].zfill(2)
		+ hex(int(data[3] * 255))[2:4].zfill(2))

def dumpTEXS(data, depth):
	i = 0
	while len(data) > i:
		b, i = i, data.find('\x00', i)
		name, i = data[b:i], i+1
		flags = int32(data[i:i+4])
		blend = int32(data[i+4:i+8])
		position = (float32(data[i+8:i+12]), float32(data[i+12:i+16]))
		scale = (float32(data[i+16:i+20]), float32(data[i+20:i+24]))
		rotation = float32(data[i+24:i+28])

		i = i + 28

		if b != 0:
			print ''
		print depth*' '+'Name', name
		print depth*' '+'Flags', hex(flags)
		print depth*' '+'Blend', hex(blend)
		print depth*' '+'Position', position
		print depth*' '+'Scale', scale
		print depth*' '+'Rotation', rotation

def dumpBRUS(data, depth):
	texsCount = int32(data[0:4])

	i = 4
	while len(data) > i:
		b, i = i, data.find('\x00', i)
		name, i = data[b:i], i+1
		rgbaColor = struct.unpack('ffff', data[i:i+16])
		shininess = float32(data[i+16:i+20])
		blend = int32(data[i+20:i+24])
		fx = int32(data[i+24:i+28])
		textures = []
		# max 8 textures
		if texsCount > 0:
			textures = list(struct.unpack('i'*texsCount, data[i+28:i+28+texsCount*4]))

		i = i + 28 + texsCount*4

		if b != 4:
			print ''
		print depth*' '+'Name', name
		print depth*' '+'Blend', hex(blend)
		print depth*' '+'FX', hex(fx)
		print depth*' '+'Color', '#'+hexColor(rgbaColor), rgbaColor
		print depth*' '+'Shininess', shininess
		print depth*' '+'Textures', textures

def dumpVRTS(data, depth):
	flags = int32(data[0:4])
	texCoords = int32(data[4:8])
	texCoordSize = int32(data[8:12])

	print depth*' '+'Flags', hex(flags)
	print depth*' '+'Tex Coords', texCoords
	print depth*' '+'Tex Coord Size', texCoordSize

	verticeSize = 4*3
	if bool(flags & 1):
		verticeSize += 4*3
	if bool(flags & 2):
		verticeSize += 4*4
	if bool(flags & 4):
		verticeSize += 4*texCoords*texCoordSize

	print depth*' '+'Vertices', (len(data)-12) / verticeSize

def dumpTRIS(data, depth):
	brushId = int32(data[0:4])

	print depth*' '+'Brush ID', brushId
	print depth*' '+'Indices', (len(data)-4) / (4*3)

def dumpMESH(data, depth):
	brushId = int32(data[0:4])

	print depth*' '+'Brush ID', brushId

	i = 4
	while i+8 < len(data):
		tag = data[i:i+4]
		size = int32(data[i+4:i+8])
		print depth*' '+tag, 'of size', size
		if tag == 'VRTS':
			dumpVRTS(data[i+8:i+8+size], depth+2)
		elif tag == 'TRIS':
			dumpTRIS(data[i+8:i+8+size], depth+2)
		else:
			print depth*' '+'Unknown tag'
		i += size + 8

def dumpANIM(data, depth):
	flags = int32(data[0:4])
	frames = int32(data[4:8])
	fps = float32(data[8:12])

	print depth*' '+'Flags', hex(flags)
	print depth*' '+'Frames', frames
	print depth*' '+'FPS', fps

def dumpNODE(data, depth):
	name = data[0:data.find('\x00')]
	i = len(name)+1

	position = struct.unpack('fff', data[i:i+12])
	scale = struct.unpack('fff', data[i+12:i+24])
	rotation = struct.unpack('ffff', data[i+24:i+40])

	print depth*' '+'Name', name
	print depth*' '+'Position', position
	print depth*' '+'Scale', scale
	print depth*' '+'Rotation', rotation

	i += 40
	while i+8 < len(data):
		tag = data[i:i+4]
		size = int32(data[i+4:i+8])
		print depth*' '+tag, 'of size', size
		if tag == 'MESH':
			dumpMESH(data[i+8:i+8+size], depth+2)
		elif tag == 'ANIM':
			dumpANIM(data[i+8:i+8+size], depth+2)
		elif tag == 'NODE':
			dumpNODE(data[i+8:i+8+size], depth+2)
		else:
			print depth*' '+'Unknown tag'
		i += size + 8

def dumpBB3D(data, depth):
	version = int32(data[0:4])
	print depth*' '+'Version', version
	i = 4
	while i < len(data):
		tag = data[i:i+4]
		size = int32(data[i+4:i+8])
		print depth*' '+tag, 'of size', size
		if tag == 'TEXS':
			dumpTEXS(data[i+8:i+8+size], depth+2)
		elif tag == 'BRUS':
			dumpBRUS(data[i+8:i+8+size], depth+2)
		elif tag == 'NODE':
			dumpNODE(data[i+8:i+8+size], depth+2)
			pass
		else:
			print depth*' '+'Unknown tag'
		i += 8 + size

def dumpTags(data):
	tag = data[:4]
	size = int32(data[4:8])
	print tag, 'of size', size
	if tag == 'BB3D':
		dumpBB3D(data[8:8+size], 2)
	else:
		print 'Unknown tag'

def main():
	if len(sys.argv) < 2:
		print 'Usage:'
		print 4*' '+sys.argv[0], '<filename.b3d>'
		sys.exit(1)

	with open(sys.argv[1], 'rb') as file:
		data = file.read()

	dumpTags(data)

if __name__ == '__main__':
	main()
