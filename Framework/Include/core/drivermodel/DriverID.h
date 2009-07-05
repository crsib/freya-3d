/*
 * DriverID.h
 *
 *  Created on: 27.04.2009
 *      Author: vedenko
 */

#ifndef DRIVERID_H_
#define DRIVERID_H_

#include "core/EngineSubsystem.h"
#include "core/EString.h"

/*
 *
 */
namespace core
{
namespace drivermodel
{
class Driver;

class DriverID : virtual public ::EngineSubsystem
{
public:
	virtual core::drivermodel::Driver*		create() = 0;
	virtual EString							id() = 0;
};

}
}
#endif /* DRIVERID_H_ */
