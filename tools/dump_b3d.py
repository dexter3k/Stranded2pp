#!/usr/bin/env python2

import sys

def uint32(data):
	assert len(data) == 4
	return int(data[::-1].encode('hex'), 16)

def dumpTEXS(data, depth):
	name = data[0:data.find('\x00')]
	print depth*' '+'Name', name

def dumpBRUS(data, depth):
	pass

def dumpNODE(data, depth):
	pass

def dumpBB3D(data, depth):
	version = uint32(data[0:4])
	print depth*' '+'Version', version
	i = 4
	while i < len(data):
		tag = data[i:i+4]
		size = uint32(data[i+4:i+8])
		print depth*' '+tag, 'of size', size
		if tag == 'TEXS':
			dumpTEXS(data[i+8:i+8+size], depth+2)
		elif tag == 'BRUS':
			dumpBRUS(data[i+8:i+8+size], depth+2)
		elif tag == 'NODE':
			dumpNODE(data[i+8:i+8+size], depth+2)
		else:
			print depth*' '+'Unknown tag'
		i += 8 + size

def dumpTags(data):
	tag = data[:4]
	size = uint32(data[4:8])
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
