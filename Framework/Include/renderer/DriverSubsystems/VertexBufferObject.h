/*
 * VertexBufferObject.h
 *
 *  Created on: 06.09.2008
 *      Author: vedenko
 */

#ifndef VERTEXBUFFEROBJECT_H_
#define VERTEXBUFFEROBJECT_H_


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
#include <cstdlib>

#include "core/EngineSubsystem.h"
#include "renderer/3DConstants.h"

namespace renderer
{
//! Abstraction for vertex buffer object
/*!
 * This is an abstraction of vertex buffer object (VBO). The VBO is a primitive, that is used for efficient
 * memory exchange between RAM and VRAM an is often threaded as a source for vertex data. Another way of using VBO are different VRAM -> VRAM and RAM -> VRAM,
 * such as implementation of render to vertex buffer technique and efficient loading of texture data (which could be implemented in renderer::Texture implemetation
 */
class EXPORT VertexBufferObject : virtual public ::EngineSubsystem
{
public:
	//Default target
	//!Set the default target for VBO
	/*!
	 * Sets the default VBO target for binding
	 * \param target is a new default target to set (described by VBOTarget)
	 */
	virtual void 	setTarget(renderer::VBOTarget::type target) = 0; //Sets the default target to target (described in VBOTarget namespace)
	//Binding
	//!Bind VBO to default target
	/*!
	 * Binds VBO to previously set default target
	 */
	virtual void 	bind() = 0; //Binds buffer to default target
	//!Bind VBO to target
	/*!
	 * Binds VBO to target, that can be different from default
	 * \param target is a target (described by VBOTarget) to bind VBO on
	 */
	virtual void 	bind(renderer::VBOTarget::type target) = 0; //Binds buffer to target {target}. Default target is not affected
	//!Unbind VBO
	/*!
	 * Unbinds VBO from target and returns system to previous state (with respect to VBO)
	 */
	virtual void 	unbind() = 0;

	//!Map VBO to RAM.
	/*!
	 * Maps VBO to RAM. Please note, that choosing correct access mode could significantly increase performance.
	 * \param access is the way, in which memory should be accessed (described by VBOAccess)
	 * \return a pointer to memory region mapped
	 */
	virtual void*	map(renderer::VBOAccess::type access) = 0; //Map buffer to client memory with access type of {access} described in VBOAccess namespace
	//!Unmap VBO from RAM
	/*!
	 * Unmaps previously mapped VBO from RAM. Data copying between RAM and VRAM will possibly occur at this point.
	 */
	virtual void    unmap() = 0;//Unmaps buffer for client memory
	//setting buffer data (preferably called from manager)
	//! Set VBO data
	/*!
	 * Sets the VBO data. Must be called at least once (the overloaded version does the same) for correct usage of various mapping/updating routines.
	 * \param target is a VBO target type to load data to (does not affect the default target). Described by VBOTarget
	 * \param usage  is a way on which VBO will be mostly used. Described by VBOUsage
	 * \param size   is a size of data in bytes to be transmitted. It does affect internal VBO size
	 * \param p      is a pointer to a block of data to be transmitted. Could be NULL(in this case method just allocates internal memory for VBO)
	 */
	virtual void	setData(renderer::VBOTarget::type target,renderer::VBOUsage::type usage,size_t size,void* p) = 0; //Sets the data pointed by p of size {size} to VBO with target {target} (default not affected) and usage {usage} (described in VBOUsage namespace)
	//! Set VBO data
	/*!
	 * Sets the VBO data. Must be called at least once (the overloaded version does the same) for correct usage of various mapping/updating routines. Binding is done to default VBO target.
	 * \param usage  is a way on which VBO will be mostly used. Described by VBOUsage
	 * \param size   is a size of data in bytes to be transmitted. It does affect internal VBO size
	 * \param p      is a pointer to a block of data to be transmitted. Could be NULL(in this case method just allocates internal memory for VBO)
	 */
	virtual void	setData(renderer::VBOUsage::type usage,size_t size,void* p) = 0;//Same as above,but using default target
	//Manipulating sub data
	//Target is same as everywhere above
	//Sends sub-data pointed by p to buffer starting from offset offs of size {size}
	//! Update VBO sub-data
	/*!
	 * Updates VBO sub-data.
	 * \param target is a VBO target type to load sub-data to (does not affect the default target). Described by VBOTarget
	 * \param offs   is an offset in bytes from the VBO initial internal address
	 * \param size   is a size of data to be transmitted. It does not affect internal VBO size. offs + size must not exceed the size of VBO
	 * \param p      is a pointer to a block of data to be transmitted.
	 */
	virtual void	setSubData(renderer::VBOTarget::type target,size_t offs,size_t size,void *p) = 0;
	//! Update VBO sub-data
	/*!
	 * Updates VBO sub-data. Binding is done to default VBO target.
	 * \param offs   is an offset in bytes from the VBO initial internal address.
	 * \param size   is a size of data to be transmitted. It does not affect internal VBO size. offs + size must not exceed the size of VBO
	 * \param p      is a pointer to a block of data to be transmitted.
	 */
	virtual void	setSubData(size_t offs,size_t size,void* p) = 0;
	//Same is above, but data is being read from buffer. Memory is managed by client
	//! Retrieve VBO sub-data
	/*!
	 * Retrieves VBO sub-data
	 * \param target is a VBO target type to read sub-data from (does not affect the default target). Described by VBOTarget
	 * \param offs   is an offset in bytes from the VBO initial internal address
	 * \param size   is a size of data to be transmitted. It does not affect internal VBO size. offs + size must not exceed the size of VBO
	 * \param p      is a pointer to a block of data inside client memory. It's size should be at least {size}. Client is capable of memory management
	 */
	virtual void	getSubData(renderer::VBOTarget::type target,size_t offs,size_t size,void *p) = 0;
	//! Retrieve VBO sub-data
	/*!
	 * Retrieves VBO sub-data. Binding is done to default VBO target.
	 * \param offs   is an offset in bytes from the VBO initial internal address
	 * \param size   is a size of data to be transmitted. It does not affect internal VBO size. offs + size must not exceed the size of VBO
	 * \param p      is a pointer to a block of data inside client memory. It's size should be at least {size}. Client is capable of memory management
	 */
	virtual void	getSubData(size_t offs,size_t size,void* p) = 0;
};

}

#endif /* VERTEXBUFFEROBJECT_H_ */
