#include "freya/FreyaGeometryBuffer.h"

namespace CEGUI
{
namespace freya
{

FreyaGeometryBuffer::FreyaGeometryBuffer()
{
	m_Effect 		= NULL;
	m_ActiveTexture = NULL;
	m_VBOSize		= 256;
	m_Rapi			= core::EngineCore::getRenderingDriver();
	m_MatrixDirty 	= m_VBOSync = true;
	m_VBO			= m_Rapi->createVertexBufferObject();
	m_VBO->setData(renderer::VBOTarget::VERTEX,renderer::VBOUsage::DYNAMIC_DRAW,m_VBOSize,0);
}



FreyaGeometryBuffer::~FreyaGeometryBuffer()
{
	reset();
	if(m_VBO)
	{
		m_Rapi->destroyVertexBufferObject(m_VBO);
	}
}



void
FreyaGeometryBuffer::draw() const
{
	updateVBO();
	updateTransform();

	m_Rapi->enableScissorTest();
	//assert(m_ClipRegion.d_left != m_ClipRegion.d_right);
	//assert(m_ClipRegion.d_top  != m_ClipRegion.d_bottom);
	m_Rapi->clipArea(m_ClipRegion.d_left,m_ClipRegion.d_top,m_ClipRegion.d_right,m_ClipRegion.d_bottom);

	m_Rapi->setMatrix(renderer::Matrix::WORLD,m_Transf);

	const int pass_count = m_Effect ? m_Effect->getPassCount() : 1;
	static renderer::VertexElement	fmt[] =
	{
			FREYA_DECLARATION(0,renderer::VertexFormat::POSITION,renderer::VertexFormat::FLOAT3,0),
			FREYA_DECLARATION(0,renderer::VertexFormat::COLOR,renderer::VertexFormat::FLOAT4,3*sizeof(float)),
			FREYA_DECLARATION(0,renderer::VertexFormat::TEXT_COORD0,renderer::VertexFormat::FLOAT2,(3 + 4)*sizeof(float)),
			FREYA_LAST_DECLARATION()
	};
	m_Rapi->setVertexFormat(fmt);
	for(int pass = 0; pass < pass_count; ++pass)
	{
		if(m_Effect)
			m_Effect->performPreRenderFunctions(pass);

		size_t pos = 0;
		Batches::const_iterator it = m_Batches.begin();
		for(; it != m_Batches.end(); ++it )
		{
			//std::cout << "Rendering batch with texture " << it->first << " from " << pos << " to " << it->second << std::endl;
			m_Rapi->setTexture(renderer::TextureUnit::TEXTURE0,it->first);
			m_Rapi->setStreamSource(0,m_VBO,0,sizeof(FVertex));
			m_Rapi->drawPrimitive(renderer::Primitive::TRIANGLES,pos,it->second);
			pos += it->second;
		}
	}

	if(m_Effect)
		m_Effect->performPostRenderFunctions();

	//m_Rapi->disableScissorTest();
}



void FreyaGeometryBuffer::setTranslation(const Vector3 & v)
{
	m_Translation = v;
	m_MatrixDirty = true;
}



void FreyaGeometryBuffer::setRotation(const Vector3 & r)
{
	m_Rotation	=	r;
	m_MatrixDirty = true;
}



void FreyaGeometryBuffer::setPivot(const Vector3 & p)
{
	m_Pivot	= p;
	m_MatrixDirty = true;
}



void FreyaGeometryBuffer::setClippingRegion(const Rect & region)
{
	m_ClipRegion = region;
}



void FreyaGeometryBuffer::appendVertex(const Vertex & vertex)
{
	appendGeometry(&vertex,1);
}



void FreyaGeometryBuffer::appendGeometry(const Vertex *const vbuff, uint vertex_count)
{
	//Check, if a new batch needed
	renderer::Texture*	freya_tex = NULL;
	if(m_ActiveTexture)
		freya_tex = static_cast<FreyaTexture*>(m_ActiveTexture)->getFreyaTexture();
	if(m_Batches.empty() || m_Batches.back().first != freya_tex)
		m_Batches.push_back(std::make_pair(freya_tex,0));
	m_Batches.back().second += vertex_count;
	//Parse geometry
	FVertex	v;
	for(uint i = 0; i < vertex_count; i++)
	{
		const Vertex& vs = vbuff[i];
		v.x = vs.position.d_x;
		v.y = vs.position.d_y;
		v.z = vs.position.d_z;
		v.r = vs.colour_val.getRed();
		v.g = vs.colour_val.getGreen();
		v.b = vs.colour_val.getBlue();
		v.a = vs.colour_val.getAlpha();
		v.u = vs.tex_coords.d_x;
		v.v = vs.tex_coords.d_y;
		m_Verticies.push_back(v);
//		std::cout << "Appended vertex \n\t( " << v.x << ", " << v.y << ", " << v.z <<
//				" )\n\t( " << v.r << ", " <<  v.g << ", "  << v.b << ", " << v.a <<
//				" )\n\t( " << v.u << ", " << v.v << " )" << std::endl;
	}
	m_VBOSync = true;
}



void FreyaGeometryBuffer::setActiveTexture(Texture *texture)
{
	m_ActiveTexture = texture;
}



void FreyaGeometryBuffer::reset()
{
	m_Verticies.clear();
	m_Batches.clear();
	m_ActiveTexture = NULL;
	m_VBOSync = true;
}



Texture *
FreyaGeometryBuffer::getActiveTexture() const
{
	return m_ActiveTexture;
}



uint
FreyaGeometryBuffer::getVertexCount() const
{
	return m_Verticies.size();
}



uint
FreyaGeometryBuffer::getBatchCount() const
{
	return m_Batches.size();
}



void FreyaGeometryBuffer::setRenderEffect(RenderEffect *effect)
{
	m_Effect = effect;
}



RenderEffect *FreyaGeometryBuffer::getRenderEffect()
{
	return m_Effect;
}

void
FreyaGeometryBuffer::updateVBO() const
{
	if(m_VBOSync)
	{
		size_t required_size = m_Verticies.size() * sizeof(FVertex);
		if(m_VBOSize < required_size)
		{
			while(m_VBOSize < required_size)
				m_VBOSize *= 2;
			m_VBO->setData(renderer::VBOTarget::VERTEX,renderer::VBOUsage::DYNAMIC_DRAW,m_VBOSize,0);
		}
		void* vmem = m_VBO->map(renderer::VBOAccess::WRITE_ONLY);
		assert(vmem);
		memcpy(vmem,&m_Verticies[0],required_size);
		m_VBO->unmap();
		m_VBOSync = false;
//		std::cout << "Updating vbo to size " << m_VBOSize << std::endl;
//		for (int i = 0; i < (required_size >> 2); i++)
//			std::cout << *(reinterpret_cast<const float*>(&m_Verticies[0]) + i) << " ";
//		std::cout << std::endl;
	}
}

void
FreyaGeometryBuffer::updateTransform() const
{
	if(m_MatrixDirty)
	{
		m_Transf = math::matrix4x4::translationMatrix(math::vector3d(m_Translation.d_x + m_Pivot.d_x,m_Translation.d_y + m_Pivot.d_y,m_Translation.d_z + m_Pivot.d_z))
		* math::matrix4x4::zRotationMatrix(m_Rotation.d_z) * math::matrix4x4::yRotationMatrix(m_Rotation.d_y)
		* math::matrix4x4::xRotationMatrix(m_Rotation.d_x)
		* math::matrix4x4::translationMatrix(math::vector3d(-m_Pivot.d_x,-m_Pivot.d_y,-m_Pivot.d_z));
		m_MatrixDirty = false;
	}
}

const
math::matrix4x4 FreyaGeometryBuffer::getTransformation() const
{
	updateTransform();
	return m_Transf;
}

}
}
