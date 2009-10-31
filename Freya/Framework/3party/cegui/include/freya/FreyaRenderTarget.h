/*
 * FreyaRenderTarget.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Oct 28, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef FREYARENDERTARGET_H_
#define FREYARENDERTARGET_H_

/*
 *
 */
#include "CEGUIRenderTarget.h"
#include "CEGUIMemory.h"

#include "core/EngineCore.h"
#include "core/memory/MemoryAllocator.h"
#include "renderer/RenderingAPIDriver.h"

#include "math/matrix4x4.hpp"

#include "CEGUIRenderQueue.h"

#include "CEGUISystem.h"
namespace CEGUI
{

namespace freya
{

class FreyaRenderTarget : public virtual CEGUI::RenderTarget, public virtual CEGUI::CEGUIMemory
{
public:
	FreyaRenderTarget( );
	virtual ~FreyaRenderTarget( );

	virtual void draw(const GeometryBuffer& buffer);
	virtual void draw(const RenderQueue& queue);
	virtual void setArea(const Rect& area);
	virtual const Rect& getArea() const;
	virtual void activate();
	virtual void deactivate();
	virtual void unprojectPoint(const GeometryBuffer& buff,
			const Vector2& p_in, Vector2& p_out) const;
protected:

	void	updateMatrix() const;

	mutable	bool				m_MatrixValid;
	mutable math::matrix4x4		m_Matrix;
	Rect						m_Viewport;
	mutable float				m_ViewDistance;
    const unsigned*					m_Vp;
	renderer::RenderingAPIDriver* m_Rapi;

};

}

}

#endif /* FREYARENDERTARGET_H_ */
