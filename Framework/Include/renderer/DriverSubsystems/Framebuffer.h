/*
 * Framebuffer.h
 *
 *  Created on: 06.09.2008
 *      Author: vedenko
 */

#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

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
/*
 *
 */
#include "core/EngineSubsystem.h"

#include "renderer/3DConstants.h"

namespace renderer
{
class Texture;
//! Framebuffer abstraction
/*!
 * This class provides API independent abstraction for off-screen frame buffer.
 * This class can be constructed using RenderingAPI driver only.
 */
class EXPORT Framebuffer: virtual public ::EngineSubsystem
{
public:
	//! Set dimensions of off-screen frame buffer.
    /*!
     * Set dimensions of frame buffer. Should be called before creating any render buffer attachments.
     * Render buffer is a buffer for internal only use with off-screen frame buffer
     * Also this method should be called before any binding routines, as they change the current view port state
     * \param width is a width of off-screen frame buffer
     * \param height is a height of off-screen frame buffer
     */
	virtual void	setDimensions(unsigned width,unsigned height) = 0;
	//Binding (returns true on success)
	//! Bind frame buffer
	/*!
	 * Binds the frame buffer described by this abstraction. All rendering before the following unbind are made to this frame buffer.
	 * All view port changes are done automatically.
	 * \return true ons success, false otherwise
	 */
	virtual bool 	bind() = 0;
	//! Bind previously used frame buffer
	/*!
	 * Activates the previously used frame buffer. All view port changes are done automatically. All rendering commands to described frame buffer should be finished before unbind returns.
	 */
	virtual void	unbind() = 0;
	//Binding is provided automatically by the following commands (if needed)
	//Attaches render buffer to attach_to using internal format
	//! Attach render buffer
	/*!
	 * Attaches render buffer to described frame buffer. All sufficient binding routines are done automatically.
	 * Render buffer is a helper buffer for internal rendering routines.
	 * \param attach_to is point of attachment described by FramebufferAttachment
	 * \param internalFormat is a internal storage format described by TextureInternalFormat
	 */
	virtual void 	attachRenderBuffer(renderer::FramebufferAttachment::type attach_to,renderer::TextureInternalFormat::type internalFormat) = 0;
	//! Detach render buffer
	/*!
	 * Detaches previously attached render buffer from described frame buffer. All sufficient binding routines are done automatically.
	 * \param detach_from is point where render buffer was attachment (described by FramebufferAttachment)
	 */
	virtual void	detachRenderBuffer(renderer::FramebufferAttachment::type detach_from) = 0;
	//Attaches texture tex to attach_to
	//! Attach texture to described frame buffer
	/*!
	 * Attaches texture to described frame buffer. All sufficient binding routines are done automatically.
	 * Attached texture could be used as render target.
	 * \param attach_to is point of attachment described by FramebufferAttachment
	 * \param tex is pointer to previously created texture object.
	 * \param level is a mip level of an attachment point with numeration from 0
	 */
	virtual void 	attachTexture(renderer::FramebufferAttachment::type attach_to,const Texture* tex,unsigned level = 0) = 0;
	//! Attach texture to described frame buffer (overloaded version for cube and 3d textures)
	/*!
	 * Attaches texture to described frame buffer. All sufficient binding routines are done automatically.
	 * Attached texture could be used as render target.
	 * \param attach_to is point of attachment described by FramebufferAttachment
	 * \param tex is pointer to previously created texture object.
	 * \param side is either a cube texture side described by CubeTextureSide, either depth level of 3d texture
	 * \param level is a mip level of an attachment point with enumeration from 0
	 */
	virtual void 	attachTexture(renderer::FramebufferAttachment::type attach_to,const Texture* tex,unsigned side,unsigned level) = 0; //Version for cubic textures

	//Draw targets/read target
	//! Set draw buffers
	/*!
	 * Sets the draw buffer to make rendering to. Multiply buffers can be attached if supported by hardware.
	 * Maximum number of color attachments could be determined using maxColorAttachments method
	 * \param size is a number of draw buffers to be attached.
	 * \param bufs is an array of draw buffer ID's (described by FramebufferAttachment)
	 */
	virtual void 	drawBuffers(unsigned size,renderer::FramebufferAttachment::type * bufs) = 0; //Bufs are described by FramebufferAttachment namespace
	//! Set read buffer
	/*!
	 * Sets the buffer the data will be read from.
	 * \param buf is a read buffer ID (described by FramebufferAttachment)
	 */
	virtual void	readBuffer(renderer::FramebufferAttachment::type buf) = 0;
	//Maximum attachement supported
	//! Get the maximum number of color attachments
	/*!
	 * Gets the maximum number of color attachments supported by hardware
	 * \return Maximum number of hardware-supported color attachments
	 */
	virtual unsigned maxColorAttachments() const = 0;
	//framebuffer status
	//! Retrieve the described frame buffer status
	/*!
	 *  Retieves current status of described framebuffer
	 *  \return stutus of frame buffer described by FramebufferStatus
	 */
	virtual unsigned status() const = 0;
};

}

#endif /* FRAMEBUFFER_H_ */
