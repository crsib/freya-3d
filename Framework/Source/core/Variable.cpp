/*
 * Variable.cpp
 *
 *  Created on: 21.09.2008
 *      Author: vedenko
 */

#include "core/Variable.h"
#include <iostream>
#include <cmath>
#include "core/Utils/FromString.hpp"
#include <sstream>
namespace core
{

void Variable::m_Clear()
{
	switch(m_Type)
	{
	case 	STRING:
		delete	m_String;
		break;
	case	VECTOR3D:
		delete m_Vector3d;
		break;
	case	QUATERNION:
		delete m_Quaternion;
		break;
	case	MATRIX3X3:
		delete m_Matrix3x3;
		break;
	case	MATRIX4X4:
		delete m_Matrix4x4;
		break;
	}
}

Variable::~Variable()
{
	m_Clear();
}

Variable::Variable(const Variable& v)
{
	m_Type = v.m_Type;
	switch(m_Type)
	{
	case	BOOLEAN:
		m_Boolean = v.m_Boolean;
		break;
	case	INT:
		m_Integer = v.m_Integer;
		break;
	case	DOUBLE:
		m_Double = v.m_Double;
		break;
	case 	STRING:
		m_String = new EString(*(v.m_String));
		break;
	case	VECTOR3D:
		m_Vector3d = new math::vector3d(*(v.m_Vector3d));
		break;
	case	QUATERNION:
		m_Quaternion = new math::quaternion(*(v.m_Quaternion));
		break;
	case	MATRIX3X3:
		m_Matrix3x3 = new math::matrix3x3(*(v.m_Matrix3x3));
		break;
	case	MATRIX4X4:
		m_Matrix4x4 = new math::matrix4x4(*(v.m_Matrix4x4));
		break;
	}
}

Variable::Variable(bool v)
{
	m_Type = BOOLEAN;
	m_Boolean = v;
}

Variable::Variable(int v)
{
	m_Type = INT;
	m_Integer = v;
}

Variable::Variable(double v)
{
	m_Type = DOUBLE;
	m_Double = v;
}

Variable::Variable(const EString& v)
{
	m_Type = STRING;
	m_String = new EString(v);
}

Variable::Variable(const math::vector3d& v)
{
	m_Type = VECTOR3D;
	m_Vector3d = new math::vector3d(v);
}

Variable::Variable(const math::quaternion& v)
{
	m_Type = QUATERNION;
	m_Quaternion = new math::quaternion(v);
}

Variable::Variable(const math::matrix3x3& v)
{
	m_Type = MATRIX3X3;
	m_Matrix3x3 = new math::matrix3x3(v);
}

Variable::Variable(const math::matrix4x4& v)
{
	m_Type = MATRIX4X4;
	m_Matrix4x4 = new math::matrix4x4(v);
}

Variable& Variable::operator =(bool v)
{
	m_Clear();
	m_Type = BOOLEAN;
	m_Boolean = v;
	return (*this);
}

Variable& Variable::operator =(int v)
{
	m_Clear();
	m_Type = INT;
	m_Integer = v;
	return *this;
}

Variable& Variable::operator =(double v)
{
	m_Clear();
	m_Type = DOUBLE;
	m_Double = v;
	return *this;
}

Variable& Variable::operator =(const EString& v)
{
	m_Clear();
	m_Type = STRING;
	m_String = new EString(v);
	return *this;
}

Variable& Variable::operator =(const math::vector3d& v)
{
	m_Clear();
	m_Type = VECTOR3D;
	m_Vector3d = new math::vector3d(v);
	return *this;
}

Variable& Variable::operator =(const math::quaternion& v)
{
	m_Clear();
	m_Type = QUATERNION;
	m_Quaternion = new math::quaternion(v);
	return *this;
}

Variable& Variable::operator =(const math::matrix3x3& v)
{
	m_Clear();
	m_Type = MATRIX3X3;
	m_Matrix3x3 = new math::matrix3x3(v);
	return *this;
}

Variable& Variable::operator =(const math::matrix4x4& v)
{
	m_Clear();
	m_Type = MATRIX4X4;
	m_Matrix4x4 = new math::matrix4x4(v);
	return *this;
}

Variable& Variable::operator =(const Variable& v)
{
	m_Clear();
	m_Type = v.m_Type;
	switch(m_Type)
	{
	case	BOOLEAN:
		m_Boolean = v.m_Boolean;
		break;
	case	INT:
		m_Integer = v.m_Integer;
		break;
	case	DOUBLE:
		m_Double = v.m_Double;
		break;
	case 	STRING:
		m_String = new EString(*(v.m_String));
		break;
	case	VECTOR3D:
		m_Vector3d = new math::vector3d(*(v.m_Vector3d));
		break;
	case	QUATERNION:
		m_Quaternion = new math::quaternion(*(v.m_Quaternion));
		break;
	case	MATRIX3X3:
		m_Matrix3x3 = new math::matrix3x3(*(v.m_Matrix3x3));
		break;
	case	MATRIX4X4:
		m_Matrix4x4 = new math::matrix4x4(*(v.m_Matrix4x4));
		break;
	}
	return *this;
}

bool	Variable::toBoolean()
{
	switch(m_Type)
	{
	case	BOOLEAN:
		return m_Boolean;
		break;
	case	INT:
		return m_Integer != 0;
		break;
	case	DOUBLE:
		return m_Double > 0.0;
		break;
	case	STRING:
		if(m_String->find("false") != EString::npos)
			return false;
		else if(m_String->find("true") != EString::npos)
			return true;
		break;
	case	VECTOR3D:
		return true;
		break;
	case	QUATERNION:
		return true;
		break;
	case	MATRIX3X3:
		return true;
		break;
	case	MATRIX4X4:
		return true;
		break;
	}
	return true;
}

int		Variable::toInteger()
{
	switch(m_Type)
	{
	case	BOOLEAN:
		return m_Boolean;
		break;
	case	INT:
		return m_Integer;
		break;
	case	DOUBLE:
		return floor(m_Double);
		break;
	case	STRING:
		int val;
		from_string(val,*m_String);
		return val;
		break;
	case	VECTOR3D:
		return floor(m_Vector3d->x);
		break;
	case	QUATERNION:
		return floor(m_Quaternion->w);
		break;
	case	MATRIX3X3:
		return floor(m_Matrix3x3->_11);
		break;
	case	MATRIX4X4:
		return floor(m_Matrix4x4->_11);
		break;
	}
	return 0;
}

double  Variable::toDouble()
{
	switch(m_Type)
	{
	case	BOOLEAN:
		return m_Boolean ? 1.0 : 0.0;
		break;
	case	INT:
		return static_cast<double>(m_Integer);
		break;
	case	DOUBLE:
		return m_Double;
		break;
	case	STRING:
		int val;
		from_string(val,*m_String);
		return val;
		break;
	case	VECTOR3D:
		return m_Vector3d->x;
		break;
	case	QUATERNION:
		return m_Quaternion->w;
		break;
	case	MATRIX3X3:
		return m_Matrix3x3->_11;
		break;
	case	MATRIX4X4:
		return m_Matrix3x3->_11;
		break;
	}
	return 0.0;
}

EString Variable::toString()
{
	std::ostringstream stream;
	stream.clear();
	switch(m_Type)
	{
	case	BOOLEAN:
		return m_Boolean ? "true" : "false";
		break;
	case	INT:
		stream << m_Integer;
		return EString(stream.str().c_str());
		break;
	case	DOUBLE:
		stream << m_Double;
		return EString(stream.str().c_str());
		break;
	case	STRING:
		return *m_String;
		break;
	case	VECTOR3D:
		stream << "(" << m_Vector3d->x << "," << m_Vector3d->y << "," << m_Vector3d->z << ")";
		return EString(stream.str().c_str());
		break;
	case	QUATERNION:
		stream  << "(" << m_Quaternion->w << ",(" << m_Quaternion->u.x << ","
		<< m_Quaternion->u.y << "," << m_Quaternion->u.z << "))";
		return EString(stream.str().c_str());
		break;
	case	MATRIX3X3:
		stream
		<< "((" << m_Matrix3x3->_11 << "," << m_Matrix3x3->_21 << "," << m_Matrix3x3->_31 << ")\n"
		<< " (" << m_Matrix3x3->_12 << "," << m_Matrix3x3->_22 << "," << m_Matrix3x3->_32 << ")\n"
		<< " (" << m_Matrix3x3->_13 << "," << m_Matrix3x3->_23 << "," << m_Matrix3x3->_33 << "))";
		return EString(stream.str().c_str());
		break;
	case	MATRIX4X4:
		stream
		<< "((" << m_Matrix4x4->_11 << "," << m_Matrix4x4->_21 << "," << m_Matrix4x4->_31 << "," << m_Matrix4x4->_41 << ")\n"
		<< "((" << m_Matrix4x4->_12 << "," << m_Matrix4x4->_22 << "," << m_Matrix4x4->_32 << "," << m_Matrix4x4->_42 << ")\n"
		<< "((" << m_Matrix4x4->_13 << "," << m_Matrix4x4->_23 << "," << m_Matrix4x4->_33 << "," << m_Matrix4x4->_43 << ")\n"
		<< "((" << m_Matrix4x4->_14 << "," << m_Matrix4x4->_24 << "," << m_Matrix4x4->_34 << "," << m_Matrix4x4->_44 << "))";
		return EString(stream.str().c_str());
		break;
	}
	return EString();
}

math::vector3d Variable::toVector3d()
{
	float val;
	switch(m_Type)
	{
	case	BOOLEAN:
		val = m_Boolean ? 1.0f : 0.0f;
		return math::vector3d(val,val,val);
		break;
	case	INT:
		val = m_Integer;
		return math::vector3d(val,val,val);
		break;
	case	DOUBLE:
		val = m_Double;
		return math::vector3d(val,val,val);
		break;
	case	STRING:
		return math::vector3d();
		break;
	case	VECTOR3D:
		return *m_Vector3d;
		break;
	case	QUATERNION:
		return m_Quaternion->u;
		break;
	case	MATRIX3X3:
		return math::vector3d(m_Matrix3x3->_11,m_Matrix3x3->_21,m_Matrix3x3->_31);
		break;
	case	MATRIX4X4:
		return math::vector3d(m_Matrix4x4->_11,m_Matrix4x4->_21,m_Matrix4x4->_31);
		break;
	}
	return math::vector3d();
}

math::quaternion Variable::toQuaternion()
{
	float val;
	switch(m_Type)
	{
	case	BOOLEAN:
		val = m_Boolean ? 1.0f : 0.0f;
		return math::quaternion(val,val,val,val);
		break;
	case	INT:
		val = m_Integer;
		return math::quaternion(val,val,val,val);
		break;
	case	DOUBLE:
		val = m_Double;
		return math::quaternion(val,val,val,val);
		break;
	case	STRING:
		return math::quaternion();
		break;
	case	VECTOR3D:
		return math::quaternion(0.0f,*m_Vector3d);
		break;
	case	QUATERNION:
		return *m_Quaternion;
		break;
	case	MATRIX3X3:
		return math::quaternion(0.0f,m_Matrix3x3->_11,m_Matrix3x3->_21,m_Matrix3x3->_31);
		break;
	case	MATRIX4X4:
		return math::quaternion(m_Matrix4x4->_11,m_Matrix4x4->_21,m_Matrix4x4->_31,m_Matrix4x4->_41);
		break;
	}
	return math::quaternion();
}

math::matrix3x3  Variable::toMatrix3x3()
{
	float val;
	float val3x3[9];
	switch(m_Type)
	{
	case	BOOLEAN:
		val = m_Boolean ? 1.0f : 0.0f;
		return math::matrix3x3(val);
		break;
	case	INT:
		val = m_Integer;
		return math::matrix3x3(val);
		break;
	case	DOUBLE:
		val = m_Double;
		return math::matrix3x3(val);
		break;
	case	STRING:
		return math::matrix3x3();
		break;
	case	VECTOR3D:
		val3x3[0] = val3x3[3] = val3x3[6] = m_Vector3d->x;
		val3x3[1] = val3x3[4] = val3x3[7] = m_Vector3d->y;
		val3x3[2] = val3x3[5] = val3x3[8] = m_Vector3d->z;
		return math::matrix3x3(val3x3);
		break;
	case	QUATERNION:
		val3x3[0] = val3x3[3] = val3x3[6] = m_Quaternion->u.x;
		val3x3[1] = val3x3[4] = val3x3[7] = m_Quaternion->u.y;
		val3x3[2] = val3x3[5] = val3x3[8] = m_Quaternion->u.z;
		return math::matrix3x3(val3x3);
		break;
	case	MATRIX3X3:
		return *m_Matrix3x3;
		break;
	case	MATRIX4X4:
		val3x3[0] = m_Matrix4x4->_11; val3x3[1] = m_Matrix4x4->_12; val3x3[2] = m_Matrix4x4->_13;
		val3x3[3] = m_Matrix4x4->_21; val3x3[4] = m_Matrix4x4->_22; val3x3[5] = m_Matrix4x4->_23;
		val3x3[6] = m_Matrix4x4->_31; val3x3[7] = m_Matrix4x4->_32; val3x3[8] = m_Matrix4x4->_33;
		return math::matrix3x3(val3x3);
		break;
	}
	return math::matrix3x3();
}

math::matrix4x4  Variable::toMatrix4x4()
{
	float val;
	float val4x4[16];
	math::matrix4x4 mtx;
	switch(m_Type)
	{
	case	BOOLEAN:
		val = m_Boolean ? 1.0f : 0.0f;
		return math::matrix4x4(val);
		break;
	case	INT:
		val = m_Integer;
		return math::matrix4x4(val);
		break;
	case	DOUBLE:
		val = m_Double;
		return math::matrix4x4(val);
		break;
	case	STRING:
		return math::matrix4x4();
		break;
	case	VECTOR3D:
		val4x4[0] = val4x4[4] = val4x4[8]  = m_Vector3d->x; val4x4[12] = 0.0f;
		val4x4[1] = val4x4[5] = val4x4[9]  = m_Vector3d->y; val4x4[13] = 0.0f;
		val4x4[2] = val4x4[6] = val4x4[10] = m_Vector3d->z; val4x4[14] = 0.0f;
		val4x4[3] = val4x4[7] = val4x4[11] = 0.0f;		    val4x4[15] = 1.0f;
		return math::matrix4x4(val4x4);
		break;
	case	QUATERNION:
		val4x4[0] = val4x4[4] = val4x4[8]  = m_Quaternion->u.x; val4x4[12] = 0.0f;
		val4x4[1] = val4x4[5] = val4x4[9]  = m_Quaternion->u.y; val4x4[13] = 0.0f;
		val4x4[2] = val4x4[6] = val4x4[10] = m_Quaternion->u.z; val4x4[14] = 0.0f;
		val4x4[3] = val4x4[7] = val4x4[11] = m_Quaternion->w;   val4x4[15] = 1.0f;
		return math::matrix4x4(val4x4);
		break;
	case	MATRIX3X3:
		mtx._11 = m_Matrix3x3->_11;mtx._12 = m_Matrix3x3->_12;mtx._13 = m_Matrix3x3->_13;
		mtx._21 = m_Matrix3x3->_21;mtx._22 = m_Matrix3x3->_22;mtx._23 = m_Matrix3x3->_23;
		mtx._31 = m_Matrix3x3->_31;mtx._32 = m_Matrix3x3->_32;mtx._33 = m_Matrix3x3->_33;
		return mtx;
		break;
	case	MATRIX4X4:
		return *m_Matrix4x4;
		break;
	}
	return mtx;
}

}

