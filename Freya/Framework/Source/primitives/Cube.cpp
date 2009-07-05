#include "primitives/Cube.h"

namespace primitives
{
//============================== Default constructor==============================
renderer::VertexBufferObject*			Cube::m_Verticies = NULL;
renderer::VertexBufferObject*			Cube::m_Normals = NULL;
renderer::VertexBufferObject*			Cube::m_Indicies = NULL;
renderer::VertexBufferObject*			Cube::m_Tangents = NULL;
renderer::VertexBufferObject*			Cube::m_Binormals = NULL;
renderer::VertexBufferObject*			Cube::m_UV = NULL;

Cube::Cube()
{
	m_Shader = 0;
	rapi = core::EngineCore::getRenderingDriver();
	static float vert_arr[24*3] = {
			//Front
			-1,-1, 1,
			-1, 1, 1,
			1, 1, 1,
			1,-1, 1,
			//Right
			1,-1, 1,
			1, 1, 1,
			1, 1,-1,
			1,-1,-1,
			//Back
			-1,-1,-1,
			-1, 1,-1,
			1, 1,-1,
			1,-1,-1,
			//Left
			-1,-1, 1,
			-1, 1, 1,
			-1, 1,-1,
			-1,-1,-1,
			//Top
			-1, 1, 1,
			-1, 1,-1,
			1, 1,-1,
			1, 1, 1,
			//Bottom
			-1,-1, 1,
			-1,-1,-1,
			1,-1,-1,
			1,-1, 1,
	};

	static float	normals[24*3] = {
			//Front
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			//Right
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			//Back
			0, 0,-1,
			0, 0,-1,
			0, 0,-1,
			0, 0,-1,
			//Left
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			//Top
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			//Bottom
			0,-1, 0,
			0,-1, 0,
			0,-1, 0,
			0,-1, 0,
	};
	//Whats about tex coords and tbn?
	//It MUST be done in some better way, by this only tutorial purposed framework with tutorial only object, so... who cares?

	static float tangents [24*3] = {
			//Front+
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			//Right
			0, 0,1,
			0, 0,1,
			0, 0,1,
			0, 0,1,
			//Back
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			1, 0, 0,
			//Left+
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			//Top+
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			//Bottom+
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
			-1, 0, 0,
	};

	static float binormals[24*3] = {
			//Front+
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			//Right
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			0, 1, 0,
			//Back
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			//Left+
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			0, -1, 0,
			//Top
			0, 0, 1,+
			0, 0, 1,
			0, 0, 1,
			0, 0, 1,
			//Bottom+
			0, 0,-1,
			0, 0,-1,
			0, 0,-1,
			0, 0,-1,
	};

	static float uv[24*2] = {
			//Front
			0,0,
			1,0,
			1,1,
			0,1,
			//Right
			1,0,
			1,1,
			0,1,
			0,0,
			//Back
			1,0,
			1,1,
			0,1,
			0,0,
			//Left
			0,0,
			0,1,
			1,1,
			1,0,
			//Top
			0,0,
			1,0,
			1,1,
			0,1,
			//Bottom
			0,0,
			1,0,
			1,1,
			0,1,

	};

	static unsigned short indicies [36] = {
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

	//VBO
	if(m_Verticies == NULL)
	{
		m_Verticies = rapi->createVertexBufferObject();
		m_Verticies->setTarget(renderer::VBOTarget::VERTEX);
		m_Verticies->setData(renderer::VBOUsage::STATIC_DRAW,24*3*sizeof(float),vert_arr);

		m_Normals = rapi->createVertexBufferObject();
		m_Normals->setTarget(renderer::VBOTarget::VERTEX);
		m_Normals->setData(renderer::VBOUsage::STATIC_DRAW,24*3*sizeof(float),normals);

		m_Tangents = rapi->createVertexBufferObject();
		m_Tangents->setTarget(renderer::VBOTarget::VERTEX);
		m_Tangents->setData(renderer::VBOUsage::STATIC_DRAW,24*3*sizeof(float),tangents);

		m_Binormals = rapi->createVertexBufferObject();
		m_Binormals->setTarget(renderer::VBOTarget::VERTEX);
		m_Binormals->setData(renderer::VBOUsage::STATIC_DRAW,24*3*sizeof(float),binormals);

		m_Indicies = rapi->createVertexBufferObject();
		m_Indicies->setTarget(renderer::VBOTarget::INDEX);
		m_Indicies->setData(renderer::VBOUsage::STATIC_DRAW,6*6*sizeof(unsigned short),indicies);

		m_UV = rapi->createVertexBufferObject();
		m_UV->setTarget(renderer::VBOTarget::VERTEX);
		m_UV->setData(renderer::VBOUsage::STATIC_DRAW,24*2*sizeof(float),uv);
	}
	m_Diffuse = m_Specular = m_Bump = NULL;
}

//==============================~Default constructor==============================

//============================== Derived constructors==============================

//==============================~Derived constructors==============================

//============================== Destructor==============================

Cube::~Cube()
{
	//Destructor stub
}

//==============================~Destructor==============================

//============================== Method: render==============================

void		Cube::render()
{
	rapi->enableClientState(renderer::ClientState::VERTEX_ARRAY);

	rapi->enableClientState(renderer::ClientState::NORMAL_ARRAY);

	rapi->enableTextureCoordState(renderer::TextureUnit::TEXTURE0);
	rapi->enableTextureCoordState(renderer::TextureUnit::TEXTURE1);
	rapi->enableTextureCoordState(renderer::TextureUnit::TEXTURE2);

	rapi->vertexPointer(renderer::DataType::FLOAT,3,0,m_Verticies);

	rapi->normalPointer(renderer::DataType::FLOAT,0,m_Normals);

	rapi->textureCoordPointer(renderer::TextureUnit::TEXTURE0,renderer::DataType::FLOAT,2,0,m_UV);
	rapi->textureCoordPointer(renderer::TextureUnit::TEXTURE1,renderer::DataType::FLOAT,3,0,m_Tangents);
	rapi->textureCoordPointer(renderer::TextureUnit::TEXTURE2,renderer::DataType::FLOAT,3,0,m_Binormals);
	if(m_Shader)
	{
		//m_Shader->enableClientState("tangent");
		//m_Shader->enableClientState("binormal");
		//m_Shader->setAttributeArrayPointer("tangent",renderer::DataType::FLOAT,3,false,0,m_Tangents);
		//	m_Shader->setAttributeArrayPointer("binormal",renderer::DataType::FLOAT,3,false,0,m_Binormals);
		if(m_Diffuse)
			m_Shader->setTexture("diffuse",m_Diffuse);
		if(m_Specular)
			m_Shader->setTexture("specular",m_Specular);
		if(m_Bump)
			m_Shader->setTexture("bump",m_Bump);
		m_Shader->bind();
	}
	if(m_Diffuse)
		m_Diffuse->bind();
	if(m_Specular)
		m_Specular->bind();
	if(m_Bump)
		m_Bump->bind();

	rapi->drawIndexedPrimitive(renderer::Primitive::TRIANGLES,6*6,renderer::DataType::UNSIGNED_SHORT,m_Indicies,m_Arr);

	if(m_Diffuse)
		m_Diffuse->unbind();
	if(m_Specular)
		m_Specular->unbind();
	if(m_Bump)
		m_Bump->unbind();


	if(m_Shader)
	{
		//	m_Shader->disableClientState("tangent");
		//	m_Shader->disableClientState("binormal");
	}
	rapi->enableTextureCoordState(renderer::TextureUnit::TEXTURE0);
	rapi->enableTextureCoordState(renderer::TextureUnit::TEXTURE1);
	rapi->enableTextureCoordState(renderer::TextureUnit::TEXTURE2);

	rapi->disableClientState(renderer::ClientState::NORMAL_ARRAY);

	rapi->disableClientState(renderer::ClientState::VERTEX_ARRAY);
}

//==============================~Method: render==============================

//============================== Method: addInstance==============================

void		Cube::addInstance(const renderer::InstanceData& i)
{
	m_Arr.push_back(i);
}

//==============================~Method: addInstance==============================

//============================== Method: getInstance==============================

renderer::InstanceData& 		Cube::getInstance(unsigned i)
{
	return m_Arr.at(i);
}

//==============================~Method: getInstance==============================

//============================== Method: getInstancesCount==============================

unsigned		Cube::getInstancesCount()
{
	return m_Arr.size();
}

//==============================~Method: getInstancesCount==============================

} //End of unit_tests namespace

