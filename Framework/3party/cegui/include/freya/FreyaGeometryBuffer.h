/*
 * FreyaGeometryBuffer.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Oct 28, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef FREYAGEOMETRYBUFFER_H_
#define FREYAGEOMETRYBUFFER_H_

/*
 *
 */
#include "CEGUIGeometryBuffer.h"
#include "CEGUIMemory.h"

#include "core/EngineCore.h"
#include "core/memory/MemoryAllocator.h"
#include "renderer/RenderingAPIDriver.h"
#include "renderer/DriverSubsystems/VertexBufferObject.h"
#include "renderer/DriverSubsystems/Texture.h"

#include "CEGUIVertex.h"
#include "CEGUIRenderEffect.h"

#include "freya/FreyaTexture.h"

#include "math/matrix4x4.hpp"

#include <list>
#include <vector>

namespace CEGUI
{

namespace freya
{

class FreyaGeometryBuffer : public CEGUI::GeometryBuffer, public virtual CEGUI::CEGUIMemory
{
public:
	FreyaGeometryBuffer( );
	virtual ~FreyaGeometryBuffer( );
	virtual void draw() const;
	virtual void setTranslation(const Vector3& v);
	virtual void setRotation(const Vector3& r);
	virtual void setPivot(const Vector3& p);
	virtual void setClippingRegion(const Rect& region);
	virtual void appendVertex(const Vertex& vertex);
	virtual void appendGeometry(const Vertex* const vbuff, uint vertex_count);
	virtual void setActiveTexture(Texture* texture);
	virtual void reset();
	virtual Texture* getActiveTexture() const;
	virtual uint getVertexCount() const;
	virtual uint getBatchCount() const;
	virtual void setRenderEffect(RenderEffect* effect);
	virtual RenderEffect* getRenderEffect();

	const math::matrix4x4		getTransformation() const;
private:

	void				updateTransform() const;
	void				updateVBO() const;

	renderer::RenderingAPIDriver*		m_Rapi;
	Texture*							m_ActiveTexture;

	RenderEffect*						m_Effect;

	Vector3								m_Translation;
	Vector3								m_Rotation;
	Vector3								m_Pivot;

	Rect								m_ClipRegion;

	mutable renderer::VertexBufferObject*		m_VBO;
	typedef	std::list<std::pair<renderer::Texture*, size_t>, core::memory::MemoryAllocator<std::pair<renderer::Texture*, size_t> > > Batches;
	Batches								m_Batches;

	struct	FVertex
	{
		float	x,y,z,r,g,b,a,u,v;
	};

	typedef std::vector<FVertex, core::memory::MemoryAllocator<FVertex> >	Verticies;
	Verticies							m_Verticies;

	mutable math::matrix4x4						m_Transf;

	mutable size_t								m_VBOSize;

	mutable bool								m_MatrixDirty;
	mutable bool								m_VBOSync;
};


}

}

#endif /* FREYAGEOMETRYBUFFER_H_ */
