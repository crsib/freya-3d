/*
 * GData.h
 *
 *  Created on: 20.02.2010
 *      Author: Alexander Ptakhin
 */

#ifndef GDATA_H
#define GDATA_H

#include "common.h"
#include <renderer\3DConstants.h>

// FIXME: Copied from renderer\RenderingAPIDriver.h (has engine dependencies). 
// May be move it from there to more "public" files?
namespace renderer
{
	struct VertexElement/* : public EngineSubsystem*/
	{
		VertexElement(unsigned sid,renderer::VertexFormat::USAGE usg,renderer::VertexFormat::TYPE tp,unsigned off)
		: streamID(sid),usage(usg),type(tp),offset(off){}
		VertexElement(){}
		unsigned				streamID;
		VertexFormat::USAGE		usage;
		VertexFormat::TYPE		type;
		unsigned 				offset;
	};
}

class GDataFile
{
public:
	GDataFile(const String& _filename);

	void write(const domGeometryRef& _geom);

protected:

	std::ofstream mOut;

	const String mFileName;
};


class GData
{
public:
	void handle(const domLibrary_geometries_Array& _geoms);
};


#endif // #ifndef GDATA_H
