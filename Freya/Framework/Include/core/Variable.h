/*
 * Variable.h
 *
 *  Created on: 21.09.2008
 *      Author: vedenko
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_

/*
 *
 */
#include "core/EngineSubsystem.h"
#include "math/vector3d.hpp"
#include "math/quaternion.hpp"
#include "math/matrix4x4.hpp"
#include "math/matrix3x3.hpp"
#include "core/EString.h"
#include "internal.h"

struct lua_State;

namespace core
{
namespace lua
{
class LuaCore;
}
class EXPORT Variable : public ::EngineSubsystem
{
	friend class core::lua::LuaCore;
protected:
	explicit Variable(lua_State* l,const EString& name);//Name is fully qualified via all tables
public:
	enum
	{
		BOOLEAN,
		INT,
		DOUBLE,
		STRING,
		VECTOR3D,
		QUATERNION,
		MATRIX3X3,
		MATRIX4X4
	};

	explicit Variable(bool v);
	explicit Variable(int v);
	explicit Variable(double v);
	explicit Variable(const EString& v);
	explicit Variable(const math::vector3d& v);
	explicit Variable(const math::quaternion& v);
	explicit Variable(const math::matrix3x3& mtx);
	explicit Variable(const math::matrix4x4& mtx);

	virtual ~Variable();

	Variable(const Variable& v);

	Variable()
	{
		m_Type = DOUBLE;
		m_Double = 0.0;
	}

	bool				toBoolean() const;
	int					toInteger() const;
	double				toDouble() const ;
	EString				toString() const;
	math::vector3d		toVector3d() const;
	math::quaternion 	toQuaternion() const;
	math::matrix3x3		toMatrix3x3() const;
	math::matrix4x4     toMatrix4x4() const;

	unsigned
	getType() const
	{
		return m_Type;
	}

	//L-assigment
	Variable& operator = (bool v);
	Variable& operator = (int v);
	Variable& operator = (double v);
	Variable& operator = (const math::vector3d& v);
	Variable& operator = (const math::quaternion& v);
	Variable& operator = (const math::matrix3x3& v);
	Variable& operator = (const math::matrix4x4& v);
	Variable& operator = (const EString& v);

	Variable& operator = (const Variable& v);
	//Cast operators
	operator
	bool ()  const
	{
		return toBoolean();
	}

	operator
	int  ()  const
	{
		return toInteger();
	}

	operator
	double() const
	{
		return toDouble();
	}
	operator
	EString() const
	{
		return toString();
	}

	operator
	math::vector3d() const
	{
		return toVector3d();
	}

	operator
	math::quaternion()
	{
		return toQuaternion();
	}

	operator
	math::matrix3x3() const
	{
		return toMatrix3x3();
	}

	operator
	math::matrix4x4() const
	{
		return toMatrix4x4();
	}

private:
	unsigned 			m_Type;
	union
	{
		bool				m_Boolean;
		int					m_Integer;
		double				m_Double;
		EString*			m_String;
		math::vector3d*  	m_Vector3d;
		math::quaternion*	m_Quaternion;
		math::matrix3x3*	m_Matrix3x3;
		math::matrix4x4*	m_Matrix4x4;
	};

	void					m_Clear();
};

inline
std::ostream&	operator << (std::ostream& o,const Variable& var)
{
	return o << var.toString();
}
}

#endif /* VARIABLE_H_ */
