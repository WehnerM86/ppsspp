// Copyright (c) 2012- PPSSPP Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0 or later versions.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official git repository and contact information can be found at
// https://github.com/hrydgard/ppsspp and http://www.ppsspp.org/.

#include "IndexGenerator.h"

// Points don't need indexing...
const u8 indexedPrimitiveType[7] = {
	GE_PRIM_POINTS,
	GE_PRIM_LINES,
	GE_PRIM_LINES,
	GE_PRIM_TRIANGLES,
	GE_PRIM_TRIANGLES,
	GE_PRIM_TRIANGLES,
	GE_PRIM_TRIANGLES,
};

void IndexGenerator::Reset() {
	prim_ = -1;
	inds_ = 0;
}

bool IndexGenerator::PrimCompatible(int prim) {
	if (prim_ == -1)
		return true;
	return indexedPrimitiveType[prim] == indexedPrimitiveType[prim_];
}

void IndexGenerator::Start(u16 *inds, int baseIndex, int prim)
{
	this->inds_ = inds;
	index_ = baseIndex;
}

void IndexGenerator::AddList(int numVerts)
{
	//if we have no vertices return
	int numTris = numVerts / 3;
	for (int i = 0; i < numTris; i++)
	{
		*inds_++ = index_ + i*3;
		*inds_++ = index_ + i*3 + 1;
		*inds_++ = index_ + i*3 + 2;
	}

	// ignore overflow verts
	index_ += numVerts;
}

void IndexGenerator::AddStrip(int numVerts)
{
	bool wind = false;
	int numTris = numVerts - 2;
	for (int i = 0; i < numTris; i++)
	{
		*inds_++ = index_ + i;
		*inds_++ = index_ + i+(wind?2:1);
		*inds_++ = index_ + i+(wind?1:2);
		wind = !wind;
	}
	index_ += numVerts;
}

void IndexGenerator::AddFan(int numVerts)
{
	int numTris = numVerts - 2;
	for (int i = 0; i < numTris; i++)
	{
		*inds_++ = index_;
		*inds_++ = index_ + i + 1;
		*inds_++ = index_ + i + 2;
	}
	index_ += numVerts;
}

void IndexGenerator::TranslateList(int numVerts, const u8 *inds, int offset)
{
	int numTris = numVerts / 3;
	for (int i = 0; i < numTris; i++)
	{
		*inds_++ = index_ + offset + inds[i*3];
		*inds_++ = index_ + offset + inds[i*3 + 1];
		*inds_++ = index_ + offset + inds[i*3 + 2];
	}
	index_ += numVerts;
}

void IndexGenerator::TranslateStrip(int numVerts, const u8 *inds, int offset)
{
	bool wind = false;
	int numTris = numVerts - 2;
	for (int i = 0; i < numTris; i++)
	{
		*inds_++ = index_ + offset + inds[i];
		*inds_++ = index_ + offset + inds[i + (wind?2:1)];
		*inds_++ = index_ + offset + inds[i + (wind?1:2)];
		wind = !wind;
	}
	index_ += numVerts;
}

void IndexGenerator::TranslateFan(int numVerts, const u8 *inds, int offset)
{
	if (numVerts <= 0) return;
	int numTris = numVerts - 2;
	for (int i = 0; i < numTris; i++)
	{
		*inds_++ = index_ + offset + inds[i];
		*inds_++ = index_ + offset + inds[i + 1];
		*inds_++ = index_ + offset + inds[i + 2];
	}
	index_ += numVerts;
}

void IndexGenerator::TranslateList(int numVerts, const u16 *inds, int offset)
{
	int numTris = numVerts / 3;
	for (int i = 0; i < numTris; i++)
	{
		*inds_++ = index_ + offset + inds[i*3];
		*inds_++ = index_ + offset + inds[i*3 + 1];
		*inds_++ = index_ + offset + inds[i*3 + 2];
	}
	index_ += numVerts;
}

void IndexGenerator::TranslateStrip(int numVerts, const u16 *inds, int offset)
{
	bool wind = false;
	int numTris = numVerts - 2;
	for (int i = 0; i < numTris; i++)
	{
		*inds_++ = index_ + offset + inds[i];
		*inds_++ = index_ + offset + inds[i + (wind?2:1)];
		*inds_++ = index_ + offset + inds[i + (wind?1:2)];
		wind = !wind;
	}
	index_ += numVerts;
}

void IndexGenerator::TranslateFan(int numVerts, const u16 *inds, int offset)
{
	if (numVerts <= 0) return;
	int numTris = numVerts - 2;
	for (int i = 0; i < numTris; i++)
	{
		*inds_++ = index_ + offset + inds[i];
		*inds_++ = index_ + offset + inds[i + 1];
		*inds_++ = index_ + offset + inds[i + 2];
	}
	index_ += numVerts;
}

//Lines
void IndexGenerator::AddLineList(int numVerts)
{
	int numLines = numVerts / 2;
	for (int i = 0; i < numLines; i++)
	{
		*inds_++ = index_ + i*2;
		*inds_++ = index_ + i*2+1;
	}
	index_ += numVerts;
}

void IndexGenerator::AddLineStrip(int numVerts)
{
	int numLines = numVerts - 1;
	for (int i = 0; i < numLines; i++)
	{
		*inds_++ = index_ + i;
		*inds_++ = index_ + i + 1;
	}
	index_ += numVerts;
}

void IndexGenerator::TranslateLineList(int numVerts, const u8 *inds, int offset)
{
	int numLines = numVerts / 2;
	for (int i = 0; i < numLines; i++)
	{
		*inds_++ = index_ + i*2;
		*inds_++ = index_ + i*2+1;
	}
	index_ += numVerts;
}

void IndexGenerator::TranslateLineStrip(int numVerts, const u8 *inds, int offset)
{
	int numLines = numVerts - 1;
	for (int i = 0; i < numLines; i++)
	{
		*inds_++ = index_ + i;
		*inds_++ = index_ + i + 1;
	}
	index_ += numVerts;
}

void IndexGenerator::TranslateLineList(int numVerts, const u16 *inds, int offset)
{
	int numLines = numVerts / 2;
	for (int i = 0; i < numLines; i++)
	{
		*inds_++ = index_ + i*2;
		*inds_++ = index_ + i*2+1;
	}
	index_ += numVerts;
}

void IndexGenerator::TranslateLineStrip(int numVerts, const u16 *inds, int offset)
{
	int numLines = numVerts - 1;
	for (int i = 0; i < numLines; i++)
	{
		*inds_++ = index_ + i;
		*inds_++ = index_ + i + 1;
	}
	index_ += numVerts;
}