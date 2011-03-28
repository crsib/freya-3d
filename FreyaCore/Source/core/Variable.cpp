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
#include <lua.hpp>
#include "core/lua/tolua++/tolua++.h"
#include "core/lua/VariableException.h"

namespace core
{

Variable::Variable(lua_State* L,const EString& name)
{
	//Parse name to parts using . sign
	//First of all, get global
	if(name.size() != 0)
	{
		EString orig_name(name);
		size_t pos;
		pos = orig_name.find_first_of('.');
		lua_getglobal(L, orig_name.substr(0,pos).c_str());//Stack first
		orig_name.erase(0,pos+1);	//Now string without first. Now - iterate
		if(pos != std::string::npos)
			while(true)
			{
				pos = orig_name.find_first_of('.');
				if(lua_istable(L,-1))
				{
					lua_getfield(L,-1,orig_name.substr(0,pos).c_str());
					lua_remove(L,-2);
					orig_name.erase(0,pos+1);
				}
				else
				{
					std::clog << "Lua error: value is not a table" << std::endl;
					lua_pop(L,1);

				}
				if(pos == std::string::npos) break;
			}
		//Ok, our name is on op of lua table now
		//Get type
		//Note - integer type will never ocure, as lua stores its numbers as doubles
		//Nevertheless - we can push integer value onto stack
	}
	tolua_Error err;
	//std::cout << "Variable::Variable lua top " << lua_gettop(L) << std::endl;
	if(tolua_isnumber(L,-1,0,&err))//Is it a number?
		m_Type = DOUBLE;
	else if(tolua_isboolean(L,-1,0,&err))
		m_Type = BOOLEAN;
	else if(tolua_isstring(L,-1,0,&err))
		m_Type = STRING;
	else if(tolua_isusertype(L,-1,(char*)"math::vector3d",0,&err))
		m_Type = VECTOR3D;
	else if(tolua_isusertype(L,-1,(char*)"math::quaternion",0,&err))
		m_Type = QUATERNION;
	else if(tolua_isusertype(L,-1,(char*)"math::matrix3x3",0,&err))
		m_Type = MATRIX3X3;
	else if(tolua_isusertype(L,-1,(char*)"math::matrix4x4",0,&err))
		m_Type = MATRIX4X4;
	else
	{
		lua_pop(L,1);
		std::clog << "Type of variable \"" << name << "\"is unsupported" << std::endl;
		throw core::lua::VariableException(name); //No supported type
	}
	//std::cout << "Variable ( " << name << " ) type: " << m_Type << std::endl;
	//Ok, we know what type to use. Load it now
	switch(m_Type)
	{
		case	DOUBLE:
			m_Double = tolua_tonumber(L,-1,0.0);
			//std::cout << "Double popped: " << m_Double << std::endl;
			break;
		case	BOOLEAN:
			m_Boolean = tolua_toboolean(L,-1,false);
			break;
		case	STRING:
			m_String = new EString;
			(*m_String) = tolua_tostring(L,-1,"");
			break;
		case	VECTOR3D:
			m_Vector3d = new math::vector3d;
			(*m_Vector3d) = *static_cast<math::vector3d*>(tolua_tousertype(L,-1,NULL));
			break;
		case	QUATERNION:
			m_Quaternion = new math::quaternion;
			(*m_Quaternion) = *static_cast<math::quaternion*>(tolua_tousertype(L,-1,NULL));
			break;
		case	MATRIX3X3:
			m_Matrix3x3 = new math::matrix3x3;
			(*m_Matrix3x3) = *static_cast<math::matrix3x3*>(tolua_tousertype(L,-1,NULL));
			break;
		case	MATRIX4X4:
			m_Matrix4x4 = new math::matrix4x4;
			(*m_Matrix4x4) = *static_cast<math::matrix4x4*>(tolua_tousertype(L,-1,NULL));
			break;
	}
	lua_pop(L,1);
	//std::cout << m_Double << std::endl;
}


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
	//std::cout << "Variable& Variable::operator =(const Variable& v)" << std::endl;
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
	//std::cout << "Double value after = " << m_Double << std::endl;
	return *this;
}

bool
Variable::toBoolean() const
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

int
Variable::toInteger() const
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

double
Variable::toDouble() const
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

EString Variable::toString() const
		{
	std::ostringstream stream;
	//stream.clear();
	switch(m_Type)
	{
		case	BOOLEAN:
			return m_Boolean ? "true" : "false";
			break;
		case	INT:
			stream << m_Integer;
			break;
		case	DOUBLE:
		//	std::cout << "Double value: " << m_Double << std::endl;
			stream << m_Double;
			break;
		case	STRING:
			return *m_String;
			break;
		case	VECTOR3D:
			stream << "(" << m_Vector3d->x << "," << m_Vector3d->y << "," << m_Vector3d->z << ")";
			break;
		case	QUATERNION:
			stream  << *m_Quaternion;
			return EString(stream.str().c_str());
			break;
		case	MATRIX3X3:
			stream
			<< "((" << m_Matrix3x3->_11 << "," << m_Matrix3x3->_21 << "," << m_Matrix3x3->_31 << "),"
			<< " (" << m_Matrix3x3->_12 << "," << m_Matrix3x3->_22 << "," << m_Matrix3x3->_32 << "),"
			<< " (" << m_Matrix3x3->_13 << "," << m_Matrix3x3->_23 << "," << m_Matrix3x3->_33 << "))";
			break;
		case	MATRIX4X4:
			stream
			<< "((" << m_Matrix4x4->_11 << "," << m_Matrix4x4->_21 << "," << m_Matrix4x4->_31 << "," << m_Matrix4x4->_41 << "),"
			<< "(" << m_Matrix4x4->_12 << "," << m_Matrix4x4->_22 << "," << m_Matrix4x4->_32 << "," << m_Matrix4x4->_42 << "),"
			<< "(" << m_Matrix4x4->_13 << "," << m_Matrix4x4->_23 << "," << m_Matrix4x4->_33 << "," << m_Matrix4x4->_43 << "),"
			<< "(" << m_Matrix4x4->_14 << "," << m_Matrix4x4->_24 << "," << m_Matrix4x4->_34 << "," << m_Matrix4x4->_44 << "))";
			break;
	}
	return EString(stream.str().c_str());
		}

math::vector3d
Variable::toVector3d() const
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
			return *m_Quaternion;
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

math::quaternion
Variable::toQuaternion() const
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

math::matrix3x3
Variable::toMatrix3x3() const
{
	float val;
	float val3x3[9];
	switch(m_Type)
	{
		case	BOOLEAN:
			val = m_Boolean ? 1.0f : 0.0f;
			return math::matrix3x3(val,0,0,
					0,val,0,
					0,0,val);
			break;
		case	INT:
			val = m_Integer;
			return math::matrix3x3(val,0,0,
					0,val,0,
					0,0,val);
			break;
		case	DOUBLE:
			val = m_Double;
			return math::matrix3x3(val,0,0,
					0,val,0,
					0,0,val);
			break;
		case	STRING:
			return math::matrix3x3();
			break;
		case	VECTOR3D:
			return math::matrix3x3(*m_Vector3d,*m_Vector3d,*m_Vector3d);
			break;
		case	QUATERNION:
			return math::matrix3x3(*m_Quaternion);
			break;
		case	MATRIX3X3:
			return *m_Matrix3x3;
			break;
		case	MATRIX4X4:
			val3x3[0] = m_Matrix4x4->_11; val3x3[1] = m_Matrix4x4->_12; val3x3[2] = m_Matrix4x4->_13;
			val3x3[3] = m_Matrix4x4->_21; val3x3[4] = m_Matrix4x4->_22; val3x3[5] = m_Matrix4x4->_23;
			val3x3[6] = m_Matrix4x4->_31; val3x3[7] = m_Matrix4x4->_32; val3x3[8] = m_Matrix4x4->_33;
			return math::matrix3x3(m_Matrix4x4->row[0],m_Matrix4x4->row[1], m_Matrix4x4->row[2]);
			break;
	}
	return math::matrix3x3();
}

math::matrix4x4
Variable::toMatrix4x4() const
{
	float val;
	float val4x4[16];
	math::matrix4x4 mtx;
	switch(m_Type)
	{
		case	BOOLEAN:
			val = m_Boolean ? 1.0f : 0.0f;
			return math::matrix4x4(val,0,0,0,
					0,val,0,0,
					0,0,val,0,
					0,0,0,1);
			break;
		case	INT:
			val = m_Integer;
			return math::matrix4x4(val,0,0,0,
					0,val,0,0,
					0,0,val,0,
					0,0,0,1);
			break;
		case	DOUBLE:
			val = m_Double;
			return math::matrix4x4(val,0,0,0,
					0,val,0,0,
					0,0,val,0,
					0,0,0,1);
			break;
		case	STRING:
			return math::matrix4x4();
			break;
		case	VECTOR3D:
			val4x4[0] = val4x4[4] = val4x4[8]  = m_Vector3d->x; val4x4[12] = 0.0f;
			val4x4[1] = val4x4[5] = val4x4[9]  = m_Vector3d->y; val4x4[13] = 0.0f;
			val4x4[2] = val4x4[6] = val4x4[10] = m_Vector3d->z; val4x4[14] = 0.0f;
			val4x4[3] = val4x4[7] = val4x4[11] = 0.0f;		    val4x4[15] = 1.0f;
			return math::matrix4x4(m_Vector3d->xmm,m_Vector3d->xmm,m_Vector3d->xmm,math::__internal::mtx4d_fourth_row.xmm);
			break;
		case	QUATERNION:
			return math::matrix4x4(*m_Quaternion);
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

