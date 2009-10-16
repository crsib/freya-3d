/*
 * OpenGLSDLAPIInit.h
 *
 *  Created on: 30.08.2008
 *      Author: vedenko
 */

#ifndef OPENGLAPIINIT_H_
#define OPENGLAPIINIT_H_

/*
 *
 */
#ifdef _FREYA_SHARED_PLUGIN
#include <cstdlib>
namespace core
{
namespace memory
{
	extern void* (*Allocate)(size_t,unsigned);
	extern void  (*Free)(void*,unsigned);
}
}
#endif 
 
 
#include "windowmanager/DriverSubsystems/RenderingAPIInitialization/RenderingAPIInitialization.h"


namespace windowmanager
{
namespace drivers
{
namespace sdl
{

class OpenGLSDLAPIInit: public RenderingAPIInitialization
{
	friend class SDLWindowManagerDriver;
protected:
	OpenGLSDLAPIInit();
	virtual ~OpenGLSDLAPIInit();
public:
	virtual unsigned getAPI_ID();
	virtual void  setupAPI();
    unsigned getRedSize() const
    {
        return m_RedSize;
    }

    void setRedSize(unsigned  m_RedSize)
    {
        this->m_RedSize = m_RedSize;
    }

    unsigned getGreenSize() const
    {
        return m_GreenSize;
    }

    void setGreenSize(unsigned  m_GreenSize)
    {
        this->m_GreenSize = m_GreenSize;
    }

    unsigned getBlueSize() const
    {
        return m_BlueSize;
    }

    void setBlueSize(unsigned  m_BlueSize)
    {
        this->m_BlueSize = m_BlueSize;
    }

    unsigned getAlphaSize() const
    {
        return m_AlphaSize;
    }

    void setAlphaSize(unsigned  m_AlphaSize)
    {
        this->m_AlphaSize = m_AlphaSize;
    }

    unsigned getDoublebuffer() const
    {
        return m_Doublebuffer;
    }

    void setDoublebuffer(unsigned  m_Doublebuffer)
    {
        this->m_Doublebuffer = m_Doublebuffer;
    }

    unsigned getBufferSize() const
    {
        return m_BufferSize;
    }

    void setBufferSize(unsigned  m_BufferSize)
    {
        this->m_BufferSize = m_BufferSize;
    }

    unsigned getDepthSize() const
    {
        return m_DepthSize;
    }

    void setDepthSize(unsigned  m_DepthSize)
    {
        this->m_DepthSize = m_DepthSize;
    }

    unsigned getStencilSize() const
    {
        return m_StencilSize;
    }

    void setStencilSize(unsigned  m_StencilSize)
    {
        this->m_StencilSize = m_StencilSize;
    }

    unsigned getAccumRedSize() const
    {
        return m_AccumRedSize;
    }

    void setAccumRedSize(unsigned  m_AccumRedSize)
    {
        this->m_AccumRedSize = m_AccumRedSize;
    }

    unsigned getAccumGreenSize() const
    {
        return m_AccumGreenSize;
    }

    void setAccumGreenSize(unsigned  m_AccumGreenSize)
    {
        this->m_AccumGreenSize = m_AccumGreenSize;
    }

    unsigned getAccumBlueSize() const
    {
        return m_AccumBlueSize;
    }

    void setAccumBlueSize(unsigned  m_AccumBlueSize)
    {
        this->m_AccumBlueSize = m_AccumBlueSize;
    }

    unsigned getAccumAlphaSize() const
    {
        return m_AccumAlphaSize;
    }

    void setAccumAlphaSize(unsigned  m_AccumAlphaSize)
    {
        this->m_AccumAlphaSize = m_AccumAlphaSize;
    }

    unsigned getAccelerated() const
    {
        return m_Accelerated;
    }

    void setAccelerated(unsigned  m_Accelerated)
    {
        this->m_Accelerated = m_Accelerated;
    }

private:
	unsigned  m_RedSize;
	unsigned  m_GreenSize;
	unsigned  m_BlueSize;
	unsigned  m_AlphaSize;

	unsigned  m_Doublebuffer;

	unsigned  m_BufferSize;
	unsigned  m_DepthSize;
	unsigned  m_StencilSize;

	unsigned  m_AccumRedSize;
	unsigned  m_AccumGreenSize;
	unsigned  m_AccumBlueSize;
	unsigned  m_AccumAlphaSize;
	unsigned  m_Accelerated;
};

}
}
}

#endif /* OPENGLAPIINIT_H_ */
