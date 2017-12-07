# Blitz3D File Format

Unofficial specification for version V0.01.
Based on [original doc](b3d_specs.txt) which is in Public Domain.

**Note**: this document is still work-in-progess.

## Introduction

Quoting original doc:

>The Blitz3D file format specifies a format for storing texture, brush and entity descriptions for
>use with the Blitz3D programming language.

This document mainly targets on using .b3d format in third-party applications unrelated to B3D.

## File Structure

The file is split into `chunks`. Each chunk is preceded by a chunk header.

From the original doc:
> If a chunk contains both data and other chunks, the data always appears first and is of a fixed
> length.
> A file parser should ignore unrecognized chunks.

> Anything that is referenced 'by index' always appears EARLIER in the file than anything that
> references it.

### Data Types

Multibyte primitive types are stored in Little-Endian order (least significant byte goes first).

* The type `byte` represents an unsigned byte value. Only used here as an array (`byte[]`) of some data
* The type `int` represents a four-byte signed integer value.
* The type `float` represents a four-byte IEEE-754 floating point value.
* The type `string` represents a C-style (null-terminated) string.

Optional fields' names are enclosed in '[]' brackets. Presence of these fields is determined by the amount of remaining data in the current chunk.

### Chunk Header
```
chunkHeader
{
	byte chunk_tag[4]
	int chunk_size
}
```

* The field `chunk_tag` describes the type of this chunk
* The field `chunk_size` describes size of this chunk. Header's size is not included.

### BB3D File
```
bb3dFile
{
	int version

	[TEXS]
	[BRUS]
	[NODE]
}
```

* The field `version` describes used file format. It is encoded in `major*100 + minor` format. Default value is `1`.

### TEXS Chunk
```
texsChunk
{
repeated:
	string file
	int flags
	int blend
	float pos_x, pos_y
	float scale_x, scale_y
	float rotation
}
```

* The field `file` describes a texture filename.
* `flags` has the same meaning as Blitz3D TextureFlags. Value of '65536' indicates that texture uses secondary UV values. Default value is '1'.
* `blend` has the same meaning as Blitz3D TextureBlend. Default value is '2'.
* `pos_x` and `pos_y` describe texture position. Default values are '0' and '0'.
* `scale_x` and `scale_y` sescribe texture scale. Default values are '1' and '1'.
* Field `rotation` describes rotation of a texture in radians. Default value is '0'.

### BRUS Chunk
```
brusChunk
{
	int n_texs
repeated:
	string name
	float red, green, blue, alpha
	float shininess
	int blend, fx
	int texture_id[n_texs]
}
```

### VRTS Chunk
```
vrtsChunk
{
	int flags
	int tex_coords
	int tex_coord_size
repeated:
	float x, y, z
	float nx, ny, nz								// only when flags & 1
	float red, green, blue, alpha					// only when flags & 2
	float tex_coords[tex_coords][tex_coord_size]
}
```

### TRIS Chunk
```
trisChunk
{
	int brush_id
repeated:
	int vertex_id[3]
}
```

### MESH Chunk
```
meshChunk
{
	int brush_id

	VRTS
	TRIS[, TRIS...]
}
```

### BONE Chunk
```
boneChunk
{
repeated:
	int vertex_id
	float weight
}
```

### KEYS Chunk
```
keysChunk
{
	int flags
repeated:
	int frame
	float position[3]		// only when flags & 1
	float scale[3]			// only when flags & 2
	float rotation[4]		// only when flags & 4
}
```

### ANIM Chunk
```
animChunk
{
	int flags				// unused
	int frames
	float fps
}
```

### NODE Chunk
```
nodeChunk
{
	string name
	float position[3]
	float scale[3]
	float rotation[4]

	[MESH or BONE]
	[KEYS, [KEYS...]]
	[NODE, [NODE...]]
	[ANIM]
}
```
