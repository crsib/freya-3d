/*
 * VBOData.cpp
 *
 *  Created on: Jan 10, 2010
 *      Author: crsib
 */

#include "scenegraph/VBOData.h"

namespace scenegraph
{

VBOData::VBOData( ) : num_batches(0),batches(NULL),number_of_indicies(0),indicies(NULL),size_of_vertex_data(0), vertex_data(NULL)
{

}

VBOData::~VBOData( )
{
}

VBOData::VBOBatchHeader::VBOBatchHeader() : assembly_type(0),index_count(0),buffer_offset(0),layout(NULL)
{

}

VBOData::VBOBatchHeader::~VBOBatchHeader()
{

}

}
