#include "freya/FreyaRenderer.h"

#include <algorithm>

namespace CEGUI
{
namespace freya
{

namespace __internal
{
const char		_v_shader_source [] =
{
		"void main()\n"
		"{\n"
		"	gl_FrontColor = gl_Color;\n"
		"	gl_TexCoord[0] = gl_MultiTexCoord0;\n"
		"	gl_Position = ftransform();\n"
		"}\n"
};

const char	 	_f_shader_source [] =
{
		"uniform sampler2D guiTex;\n"
		"\n"
		"void main()\n"
		"{\n"
		"	gl_FragColor = gl_Color * texture2D(guiTex, gl_TexCoord[0].xy);\n"
		"}"
};
}
FreyaRenderer::FreyaRenderer()
{
	m_Rapi = core::EngineCore::getRenderingDriver();
	m_Shader = m_Rapi->createShader();
	//Todo: change it for some better way of loading shader
	m_Shader->addShaders(EString(__internal::_v_shader_source),EString(__internal::_f_shader_source));
	m_Shader->link();
	if(!m_Shader->isOk())
		throw CEGUI::RendererException("[CEGUI::FreyaRenderer]: Failed to compile display shader");
	m_SamplerLoc = m_Shader->getUniformLocation("guiTex");

	m_DefaultTarget	= new FreyaWindowTarget;
	m_Root			= new RenderingRoot(*m_DefaultTarget);
}

Texture & FreyaRenderer::createTexture(const Size & size)
{
	FreyaTexture * tex = new FreyaTexture;
	tex->loadFromMemory(0,size,Texture::PF_RGBA);
	m_Textures.push_back(tex);
	return *tex;
}

void FreyaRenderer::destroyAllTextures()
{
	while(!m_Textures.empty())
		destroyTexture(*(m_Textures.back()));
}

RenderingRoot & FreyaRenderer::getDefaultRenderingRoot()
{
	return *m_Root;
}

GeometryBuffer & FreyaRenderer::createGeometryBuffer()
{
	FreyaGeometryBuffer* buf = new FreyaGeometryBuffer;
	m_GeometryBuffers.push_back(buf);
	return *buf;
}

void FreyaRenderer::destroyTexture(Texture & texture)
{
	Textures::iterator	it = std::find(m_Textures.begin(),m_Textures.end(),&static_cast<FreyaTexture&>(texture));
	if(it != m_Textures.end())
	{
		m_Textures.erase(it);
		delete &texture;
	}
}

void FreyaRenderer::destroyTextureTarget(TextureTarget *target)
{
	TextureTargets::iterator it = std::find(m_TextureTargets.begin(),m_TextureTargets.end(),target);
	if(it != m_TextureTargets.end())
	{
		m_TextureTargets.erase(it);
		delete target;
	}
}

Texture & FreyaRenderer::createTexture()
{
	FreyaTexture * tex = new FreyaTexture;
	m_Textures.push_back(tex);
	return *tex;
}

void FreyaRenderer::endRendering()
{
	m_Rapi->disableAlphaBlend();
	m_Shader->unbind();
	m_Rapi->enableDepthTest();
}

Texture & FreyaRenderer::createTexture(const String & filename, const String & resourceGroup)
{
	FreyaTexture * tex = new FreyaTexture;
	tex->loadFromFile(filename,resourceGroup);
	m_Textures.push_back(tex);
	return *tex;
}

void FreyaRenderer::destroyAllTextureTargets()
{
	while(!m_TextureTargets.empty())
		destroyTextureTarget(m_TextureTargets.back());
}

const String &
FreyaRenderer::getIdentifierString() const
{
	static const String _id = "CEGUI Freya3D renderer";
	return _id;
}

void FreyaRenderer::beginRendering()
{
	m_Shader->bind();
	m_Rapi->disableCulling();
	m_Shader->setTexture(m_SamplerLoc,renderer::TextureUnit::TEXTURE0);
	m_Rapi->enableAlphaBlend();
	m_Rapi->alphaBlendFunction(renderer::AlphaFunction::SRC_ALPHA,renderer::AlphaFunction::ONE_MINUS_SRC_ALPHA);
	m_Rapi->disableDepthTest();
}

const Vector2 &
FreyaRenderer::getDisplayDPI() const
{
	static const Vector2 _dpi(96,96);
	return _dpi;
}

uint
FreyaRenderer::getMaxTextureSize() const
{
	m_Rapi->maxTextureSize();
}

FreyaRenderer::~FreyaRenderer()
{
	this->destroyAllGeometryBuffers();
	this->destroyAllTextureTargets();
	this->destroyAllTextures();
	m_Rapi->destroyShader(m_Shader);
	delete m_Root;
	delete m_DefaultTarget;
}

void FreyaRenderer::setDisplaySize(const Size & sz)
{
	if(sz != m_DisplaySize)
	{
		m_DisplaySize = sz;

		Rect area(m_DefaultTarget->getArea());
		area.setSize(sz);
		m_DefaultTarget->setArea(area);
	}
}

TextureTarget *FreyaRenderer::createTextureTarget()
{
	FreyaTextureTarget*	tex = new FreyaTextureTarget;
	m_TextureTargets.push_back(tex);
	return static_cast<TextureTarget*>(tex);
}

void FreyaRenderer::destroyGeometryBuffer(const GeometryBuffer & buffer)
{
	GeometryBuffers::iterator it = std::find(m_GeometryBuffers.begin(),m_GeometryBuffers.end(),&buffer);

	if(it != m_GeometryBuffers.end())
	{
		m_GeometryBuffers.erase(it);
		delete &buffer;
	}
}

void FreyaRenderer::destroyAllGeometryBuffers()
{
	while(!m_GeometryBuffers.empty())
		destroyGeometryBuffer(*m_GeometryBuffers.back());
}

const Size &
FreyaRenderer::getDisplaySize() const
{
	return m_DisplaySize;
}

}
}
