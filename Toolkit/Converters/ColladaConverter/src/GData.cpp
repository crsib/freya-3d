
#include "common.h"
#include "GData.h"

GDataFile::GDataFile(const String& _filename)
:	mFileName(_filename), mOut()
{
}

// perversion FIXME!
template <typename T>
void binWrite(const T& write, std::ofstream& stream)
{
	stream.write((char*)&write, sizeof(write)); 
}

void GDataFile::write(const domGeometryRef& _geom)
{
	const domMeshRef& mesh = _geom->getMesh();

	//
	// Vertices
	//
	std::vector<float> verticesVector;

	//
	// Indices
	//
	std::vector<uint16> indicesVector;

	const domPolygons_Array& polygonArray = mesh->getPolygons_array();
	const domTriangles_Array& triangleArray = mesh->getTriangles_array();

	double tmpVec[3] = {0};

	std::vector<std::pair<const domSource*, domInputLocalOffsetRef>> order;

	typedef std::map<std::vector<uint32>, uint32> LinkVerticesMap;
	typedef LinkVerticesMap::iterator LinkVerticesMapIter;
	typedef LinkVerticesMap::const_iterator LinkVerticesMapConstIter;

	LinkVerticesMap linkVertices;

	ASSERT2(triangleArray.getCount() == 1, "Not ready for other cases!");

	for (size_t triangleIter = 0; triangleIter < triangleArray.getCount(); ++triangleIter)
	{
		const domTrianglesRef& triangles = triangleArray[triangleIter];
		const domPRef& pRef = triangles->getP();
		const domInputLocalOffset_Array& input = triangles->getInput_array();

		for (size_t inputIter = 0; inputIter < input.getCount(); ++inputIter)
		{
			String semantic = input[inputIter]->getSemantic();
			const domURIFragmentType& uri = input[inputIter]->getSource();
			const daeElementRef element = uri.getElement();
			const domVertices* vertices = nullptr;
			const domSource* source = nullptr; 

			String type(element.cast()->getTypeName());

			// Hmm... Nice down case :)
			//std::transform(type.begin(), type.end(), type.begin(), tolower);
            ERROR("TOLOWER!");
			
			if (type == "vertices")
				vertices = dynamic_cast<const domVertices*>(element.cast());
			else if (type == "source")
				source = dynamic_cast<const domSource*>(element.cast());
			else
				ERROR("No way!");

			if (vertices != nullptr)
			{
				const domInputLocal_Array& verticesInput = vertices->getInput_array();

				for (size_t verticesInputIter = 0; verticesInputIter < verticesInput.getCount(); ++verticesInputIter)
				{
					const domInputLocalRef verticesInput = vertices->getInput_array()[verticesInputIter];
					const domURIFragmentType& verticesInputUri = verticesInput->getSource();
					const domSource* verticesInputSource = dynamic_cast<const domSource*>(verticesInputUri.getElement().cast());

					order.push_back(std::make_pair(verticesInputSource, input[inputIter]));
				}
			}

			if (source != nullptr)
			{
				order.push_back(std::make_pair(source, input[inputIter]));
			}		
		}

		const domListOfUInts& pList = pRef->getValue();

		uint32 vertexId = 0; 

		for (size_t pListIter = 0; pListIter < pList.getCount(); )
		{
			std::vector<uint32> vertexSignature;
			
			for (size_t orderIter = 0; orderIter < order.size(); ++orderIter)
				vertexSignature.push_back((uint32)pList[pListIter++]);

			if (linkVertices.find(vertexSignature) == linkVertices.end())
			{
				for (size_t orderIter = 0; orderIter < vertexSignature.size(); ++orderIter)
				{
					const domSource* source = order[orderIter].first;
					const domListOfFloats& list = source->getFloat_array()->getValue();

					verticesVector.push_back((float)(list[(size_t)vertexSignature[orderIter]])); 
					verticesVector.push_back((float)(list[(size_t)vertexSignature[orderIter] + 1])); 
					verticesVector.push_back((float)(list[(size_t)vertexSignature[orderIter] + 2])); 
				}

				linkVertices.insert(std::make_pair(vertexSignature, vertexId));

				++vertexId;
			}
		}

		// Once again with indices
		for (size_t pListIter = 0; pListIter < pList.getCount(); )
		{
			std::vector<uint32> vertexSignature;
			
			for (size_t orderIter = 0; orderIter < order.size(); ++orderIter)
				vertexSignature.push_back((uint32)pList[pListIter++]);

			LinkVerticesMapConstIter iter = linkVertices.find(vertexSignature);

			if (iter != linkVertices.end())
				indicesVector.push_back(linkVertices[vertexSignature]);
			else
				ERROR("Strange signature or not added!");
		}
	}

	mOut.open(mFileName.c_str(), std::ios_base::binary);

	// Via http://freya3d.org/wiki/WorldDataFormats/GeometricData (20.02.2010)

	//(16-bit unsigned int) 	num_batches
	binWrite<uint16>(1, mOut);

	// 32-bit unsigned integer assembly_type
	binWrite<uint32>(renderer::Primitive::TRIANGLES, mOut);

	// 16-bit unsigned integer index_count 
	binWrite<uint16>(1, mOut);

	// 16-bit unsigned integer buffer_offset
	binWrite<uint16>(0, mOut);

	// renderer::VertexElement array layout
	//renderer::VertexElement vertexElement;

	uint32 vertexSize = 0;

	for (size_t orderIter = 0; orderIter < order.size(); ++orderIter)
	{
		uint32 oldVertexSize = vertexSize;

		String semantic = order[orderIter].second->getSemantic();

		// Hmm... Nice upper case :D
		//std::transform(semantic.begin(), semantic.end(), semantic.begin(), ::toupper);
        ERROR("TOUPPER!");

		renderer::VertexElement vertexElement;

		vertexElement.streamID = orderIter;
		vertexElement.offset = 0;

		if (semantic == "VERTEX")// FIXME: Some inconsistency between COLLADA and written code
		{
			vertexElement.usage = renderer::VertexFormat::POSITION;
			vertexElement.type = renderer::VertexFormat::FLOAT3;
			vertexSize += sizeof(float) * 3;// FIXME!
		}

		if (semantic == "NORMAL")
		{
			vertexElement.usage = renderer::VertexFormat::NORMAL;
			vertexElement.type = renderer::VertexFormat::FLOAT3;
			vertexSize += sizeof(float) * 3;// FIXME!
		}

		binWrite<renderer::VertexElement>(vertexElement, mOut);

		ASSERT2(oldVertexSize != vertexSize, "Who forget to add to full sum one new semantic? Or not only add?");
	}

	// Last declaration element
	binWrite<renderer::VertexElement>(renderer::VertexElement((unsigned)-1,renderer::VertexFormat::UNUSED,renderer::VertexFormat::DWORD,0), mOut);
	
	// 16-bit unsigned int  number_of_indicies
	binWrite<uint16>(indicesVector.size(), mOut);

	// 16-bit unsigned int array indcies
	for (size_t indicesIter = 0; indicesIter < indicesVector.size(); ++indicesIter)
		binWrite<uint16>(indicesVector[indicesIter], mOut);

	// 32-bit unsigned integer 	size_of_vertex_data
	binWrite<uint32>(vertexSize, mOut);

	// Raw vertex data
	for (size_t verticesIter = 0; verticesIter < verticesVector.size(); ++verticesIter)
		binWrite<float>(verticesVector[verticesIter], mOut);

	mOut.close();
}

void GData::handle(const domLibrary_geometries_Array& _geoms)
{
	for (size_t libIter = 0; libIter < _geoms.getCount(); ++libIter)
	{
		const domGeometry_Array& geomArray = _geoms[libIter]->getGeometry_array();

		String libName = "";

		if (_geoms[libIter]->getId())
			libName = String(_geoms[libIter]->getId()) + "_";

		for (size_t geomIter = 0; geomIter < geomArray.getCount(); ++geomIter)
		{
			const domGeometryRef& geom = geomArray[geomIter];

			GDataFile file(libName + geom->getId() + ".gdata");

			file.write(geom);
		}
	}
}