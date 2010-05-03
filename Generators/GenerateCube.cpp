#include <iostream>
#include <fstream>
#include <stdint.h>
using namespace std;

namespace VertexFormat
{
	enum USAGE
	{
		POSITION = 0,            //!< POSITION
		NORMAL,                  //!< NORMAL
		TANGENT,   				 //!< TANGENT
		BINORMAL,  				 //!< BINORMAL
		POINT_SIZE,				 //!< Point size
		COLOR,                   //!< COLOR
		TEXT_COORD,              //!< TEXT_COORD
		TEXT_COORD0 = TEXT_COORD,//!< TEXT_COORD0
		TEXT_COORD1,             //!< TEXT_COORD1
		TEXT_COORD2,             //!< TEXT_COORD2
		TEXT_COORD3,             //!< TEXT_COORD3
		TEXT_COORD4,             //!< TEXT_COORD4
		TEXT_COORD5,             //!< TEXT_COORD5
		TEXT_COORD6,             //!< TEXT_COORD6
		TEXT_COORD7,             //!< TEXT_COORD7
		TEXT_COORD8,             //!< TEXT_COORD8
		TEXT_COORD9,             //!< TEXT_COORD9
		TEXT_COORD10,            //!< TEXT_COORD10
		TEXT_COORD11,            //!< TEXT_COORD11
		TEXT_COORD12,            //!< TEXT_COORD12
		TEXT_COORD13,            //!< TEXT_COORD13
		TEXT_COORD14,            //!< TEXT_COORD14
		TEXT_COORD15,            //!< TEXT_COORD15
		TEXT_COORD16,            //!< TEXT_COORD16
		TEXT_COORD17,            //!< TEXT_COORD17
		TEXT_COORD18,            //!< TEXT_COORD18
		TEXT_COORD19,            //!< TEXT_COORD19
		TEXT_COORD20,            //!< TEXT_COORD20
		TEXT_COORD21,            //!< TEXT_COORD21
		TEXT_COORD22,            //!< TEXT_COORD22
		TEXT_COORD23,            //!< TEXT_COORD23
		TEXT_COORD24,            //!< TEXT_COORD24
		TEXT_COORD25,            //!< TEXT_COORD25
		TEXT_COORD26,            //!< TEXT_COORD26
		TEXT_COORD27,            //!< TEXT_COORD27
		TEXT_COORD28,            //!< TEXT_COORD28
		TEXT_COORD29,            //!< TEXT_COORD29
		TEXT_COORD30,            //!< TEXT_COORD30
		TEXT_COORD31,            //!< TEXT_COORD31
		UNUSED                   //!< UNUSED
	};

	enum TYPE
	{
		FLOAT1 = 0,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		DWORD,
		UBYTE4,
		SHORT2,
		SHORT4,
	};
}

float cube_layout []= {// //vert x 3f,norm x 3f, tangent x 3f, binormal x 3f, uv x 2f
//front
-1, -1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0,
-1,  1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0,
 1,  1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1,
 1, -1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1,

//right
 1, -1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0,
 1,  1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1,
 1,  1,-1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1,
 1, -1,-1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
 
//back
-1, -1,-1, 0, 0,-1, 1, 0, 0, 0, -1, 0, 1, 0,
-1,  1,-1, 0, 0,-1, 1, 0, 0, 0, -1, 0, 1, 1,
 1,  1,-1, 0, 0,-1, 1, 0, 0, 0, -1, 0, 0, 1,
 1, -1,-1, 0, 0,-1, 1, 0, 0, 0, -1, 0, 0, 0,
 
//left
-1, -1, 1,-1, 0, 0, 0, 0, 1, 0, -1, 0, 0, 0,			 
-1,  1, 1,-1, 0, 0, 0, 0, 1, 0, -1, 0, 0, 1,
-1,  1,-1,-1, 0, 0, 0, 0, 1, 0, -1, 0, 1, 1,
-1, -1,-1,-1, 0, 0, 0, 0, 1, 0, -1, 0, 1, 0,

//top
-1,  1, 1, 0, 1, 0,-1, 0, 0, 0, 0, 1, 0, 0,
-1,  1,-1, 0, 1, 0,-1, 0, 0, 0, 0, 1, 1, 0,
 1,  1,-1, 0, 1, 0,-1, 0, 0, 0, 0, 1, 1, 1,
 1,  1, 1, 0, 1, 0,-1, 0, 0, 0, 0, 1, 0, 1,
 //bottom
-1, -1, 1, 0,-1, 0,-1, 0, 0, 0, 0,-1, 0, 0,
-1, -1,-1, 0,-1, 0,-1, 0, 0, 0, 0,-1, 1, 0,
 1, -1,-1, 0,-1, 0,-1, 0, 0, 0, 0,-1, 1, 1,
 1, -1, 1, 0,-1, 0,-1, 0, 0, 0, 0,-1, 0, 1
};

uint16_t indicies[] = {
//Front
0,1,2,2,3,0,
//Right
4,5,6,6,7,4,
//Back
8,9,10,10,11,8,
//Left
12,13,14,14,15,12,
//Top
16,17,18,18,19,16,
//Bottom
20,21,22,22,23,20,
};

unsigned format[]	= {
//sid,usg,tp,off
0, VertexFormat::POSITION, 	VertexFormat::FLOAT3, 0,
0, VertexFormat::NORMAL,	 	VertexFormat::FLOAT3, 3*4*1,
0, VertexFormat::TANGENT,	VertexFormat::FLOAT3, 3*4*2,
0, VertexFormat::BINORMAL,	VertexFormat::FLOAT3, 3*4*3,
0, VertexFormat::TEXT_COORD0,	VertexFormat::FLOAT2, 3*4*4,
(unsigned) -1, VertexFormat::UNUSED , VertexFormat::DWORD,		0	
};

namespace Primitive
{
enum type
{
	//! Each vertex is treated as a single point
	POINTS = 0,
	//! The two successive vertices are treated as line endings
	LINES,
	//! Same as above, but with information for adjacent vertices. (See SM 4.0 primitives information for details)
	LINES_ADJACENCY,
	//! Successive vertices are connected with lines
	LINE_STRIP,
	//! Same as above, but with information for adjacent vertices. (See SM 4.0 primitives information for details)
	LINE_STRIP_ADJACENCY,
	//! Successive verticies are connected with lines. Last vertex is connect with first
	LINES_LOOP,
	//! Vertices triplets are used to create triangle
	TRIANGLES,
	//! Same as above, but with information for adjacent vertices. (See SM 4.0 primitives information for details)
	TRIANGLES_ADJACENCY,
	//! Triangles are constructed as following (with correction for bypass direction) (1,2,3),(2,3,4),(3,4,5)...
	TRIANGLE_STRIP,
	//! Same as above, but with information for adjacent vertices. (See SM 4.0 primitives information for details)
	TRIANGLE_STRIP_ADJACENCY,
	//! Triangles are constructed as following (with correction for bypass direction) (1,2,3),(1,3,4),(1,4,5)...
	TRIANGLE_FAN,
};
}

int main()
{
	std::ofstream	stream("cube.vdata",std::ios::binary);
	//stream << (uint16_t) 1 << (uint32_t) Primitive::TRIANGLES << (uint16_t) 36 << (uint16_t) 0;
	//for(size_t i = 0; i < sizeof(format); i++)
	//	stream << format[i];
	uint16_t one 	= 1;
	uint16_t zero 	= 0;
	uint16_t _36 	= 36;
	uint32_t tr		= Primitive::TRIANGLES;
	stream.write(reinterpret_cast<char*>(&one), sizeof(one));
	stream.write(reinterpret_cast<char*>(&tr ), sizeof(tr));
	stream.write(reinterpret_cast<char*>(&_36), sizeof(_36));
	stream.write(reinterpret_cast<char*>(&zero), sizeof(zero));
	stream.write(reinterpret_cast<char*>(format),24*sizeof(unsigned));
	//Index buffer
	stream.write(reinterpret_cast<char*>(&_36 ), sizeof(_36));
	stream.write(reinterpret_cast<char*>(indicies),36*sizeof(uint16_t));
	uint32_t sz =  sizeof(cube_layout);
	stream.write(reinterpret_cast<char*>(&sz ), sizeof(sz));
	stream.write(reinterpret_cast<char*>(&cube_layout),sz);
	stream.close();
	return 0;
}
