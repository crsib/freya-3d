/*
 * TGALoader.h
 *
 *  Created on: 03.03.2009
 *      Author: vedenko
 */

#ifndef TGALOADER_H_
#define TGALOADER_H_

/*
 *
 */

#include "core.h"
#include "renderer.h"
#include "internal.h"
namespace images
{
class EXPORT TGALoader
{
public:
	static renderer::Texture*		load(const EString& path);
};
}
#endif /* TGALOADER_H_ */
