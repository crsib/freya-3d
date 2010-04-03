/*
 * VBOData.h
 *
 *  Created on: Jan 10, 2010
 *      Author: crsib
 */

#ifndef VBODATA_H_
#define VBODATA_H_

#include "core/EngineSubsystem.h"
#include "internal.h"
#include "renderer/RenderingAPIDriver.h"

namespace scenegraph
{

struct VBOData : public EngineSubsystem
{
	VBOData( );
	virtual ~VBOData( );

	//Header class
	struct VBOBatchHeader : public EngineSubsystem
	{
		VBOBatchHeader();
		virtual ~VBOBatchHeader();
		uint32_t						assembly_type;
		uint16_t   						index_count;
		uint16_t						buffer_offset;
		renderer::VertexElement*		layout;
	};
//Public members
	uint32_t							num_batches;
	VBOBatchHeader*						batches;
	uint16_t							number_of_indicies;
	renderer::VertexBufferObject*		indicies;
	uint32_t							size_of_vertex_data;
	renderer::VertexBufferObject*		vertex_data;
};

}

#endif /* VBODATA_H_ */
