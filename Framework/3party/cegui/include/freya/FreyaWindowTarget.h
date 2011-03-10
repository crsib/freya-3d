/*
 * FreyaWindowTarget.h
 *	This file is part of Freya 3D engine. For licencing information
 *  from LICENCE file 
 *  Created on: Oct 28, 2009
 *      Author: Dmitri crsib Vedenko
 */

#ifndef FREYAWINDOWTARGET_H_
#define FREYAWINDOWTARGET_H_

/*
 *
 */
#include "FreyaRenderTarget.h"
#include "CEGUIMemory.h"

namespace CEGUI
{

namespace freya
{

class FreyaWindowTarget : public CEGUI::freya::FreyaRenderTarget, public virtual CEGUI::CEGUIMemory
{
public:
	FreyaWindowTarget( );
	virtual ~FreyaWindowTarget( );

	virtual bool isImageryCache() const;
};

}

}

#endif /* FREYAWINDOWTARGET_H_ */
