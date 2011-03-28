#ifndef CFLYCAMERA_H_
#define CFLYCAMERA_H_

#include "camera/BasicCamera.h"
#include "math/vector3d.hpp"
#include "math/quaternion.hpp"
#include "internal.h"
namespace camera
{
class EXPORT FlyCamera : public BasicCamera
{
public:
	FlyCamera(const math::vector3d& pos,const math::vector3d& dir,const math::vector3d& up) : BasicCamera(pos,dir,up){}
	FlyCamera(const math::vector3d& pos,const math::vector3d& dir,const math::vector3d& up,
				float FOW,float Aspect,float zNear,float zFar) : BasicCamera(pos,dir,up,FOW,Aspect,zNear,zFar){}

	virtual void moveForward(float Step);
	virtual void moveBackward(float Step);

	virtual void moveLeft(float Step);
	virtual void moveRight(float Step);

	virtual void moveUp(float Step);
	virtual void moveDown(float Step);

	virtual void changePitch(float AngleStep);
	virtual void changeYaw(float AngleStep);
	virtual void changeRoll(float AngleStep);
	~FlyCamera(){}
};
}
#endif /*CFIXEDCAMERA_H_*/
