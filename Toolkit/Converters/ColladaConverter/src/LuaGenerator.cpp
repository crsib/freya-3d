
#include "common.h"
#include "LuaGenerator.h"

Object::Object()
:	mState(S_NOT_INITIALIZED), mParent(nullptr)
{
}
Object::Object(const String& _name)
:	mState(S_NOT_INITIALIZED), mName(_name), mParent(nullptr)
{
}

String Object::typeName(Type _type) const
{
	switch (_type)
	{
	case T_INT:			return "Int";
	case T_FLOAT:		return "Float";
	case T_STRING:		return "String";
	default:
		ASSERT2(0, "No name for type `" << _type << "`!");
		return "##Unnamed";
		break;
	}
}


void Object::initSingle(Type _type)
{
	ASSERT2(mState != S_MAP, "Setting single value instead of map values!");

	if (mState == S_NOT_INITIALIZED)
		mState = S_SINGLE;

	mType = _type;
}

void Object::checkSingle(Type _type) const
{
	ASSERT2(mState == S_SINGLE, "Must be single or object wasn't initialized!");
	ASSERT2(mType == _type, "Getting type `" << typeName(_type) << "` instead of storing `" << typeName(mType) << "`!");
}

void Object::initMap()
{
	ASSERT2(mState != S_SINGLE, "Using map in single-value object!");

	if (mState == S_NOT_INITIALIZED)
	{
		mState = S_MAP;
		mType = T_MAP;
	}
}

void Object::checkMap() const
{
	ASSERT2(mState == S_MAP, "Using map in single-value object or map wasn't initialized!");
}

Object& Object::operator = (float _f)
{
	initSingle(T_FLOAT);
	mValue.f = _f;
	return *this;
}

Object& Object::operator = (int _i)
{
	initSingle(T_INT);
	mValue.i = _i;
	return *this;
}

Object& Object::operator = (const String& _str)
{
	return operator = (_str.c_str()); // :-) cpp <-> c transferring
}

Object& Object::operator = (const char* _str)
{
	initSingle(T_STRING);
	mValue.str = new char[strlen(_str)];
	strcpy(mValue.str, _str);
	return *this;
}

Object* Object::get(const String& _name)
{
	initMap();
	FieldsIter iter = mFields.find(_name);
	ASSERT2(iter != mFields.end(), "No such object `" << _name << "`!");
	return iter->second;
}

const Object* Object::get(const String& _name) const
{
	checkMap();
	FieldsConstIter iter = mFields.find(_name);
	ASSERT2(iter != mFields.end(), "No such object `" << _name << "`!");
	return iter->second;
}

void Object::set(Object* _value)
{
	initMap();
	_value->notifyParent(this);
	mFields[_value->name()] = _value;
}

int Object::valInt() const
{
	checkSingle(T_INT);
	return mValue.i;
}

float Object::valFloat() const
{
	checkSingle(T_FLOAT);
	return mValue.f;
}

char* Object::valCStr() const
{
	checkSingle(T_STRING);
	return mValue.str;
}

void Object::notifyParent(Object* _parent)
{
	ASSERT2(mParent == nullptr, "Already has parent!");
	mParent = _parent;
}

Object::Iter Object::begin() const
{
	checkMap();
	return mFields.begin();
}

Object::Iter Object::end() const
{
	checkMap();
	return mFields.end();
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------

LuaFile::LuaFile(const String& _filename)
:	mFileName(_filename), mOut()
{
}

void LuaFile::write(const Object* _root)
{
	mOut.open(mFileName.c_str());
	writeRecursive(_root, 0);
	mOut.close();
}

void LuaFile::writeRecursive(const Object* _object, uint32 _tabExtend)
{
	tab(_tabExtend);
	mOut << _object->name();

	if (_object->isSingle())
		mOut << " = " << stringValue(_object) << "," << std::endl;
	else // Map
	{
		mOut << std::endl;
		tab(_tabExtend);
		mOut << "{" << std::endl;

		for (Object::Iter iter = _object->begin(); iter != _object->end(); ++iter)
			writeRecursive(iter->second, _tabExtend + 1);

		tab(_tabExtend);
		mOut << "}," << std::endl;
	}
}

String LuaFile::stringValue(const Object* _object)
{
	std::ostringstream out;

	switch(_object->type())
	{
	case Object::T_INT:
		out << _object->valInt();
		break;
	case Object::T_FLOAT:
		out << _object->valFloat();
		break;
	case Object::T_STRING:
		out << '"' << _object->valCStr() << '"';
		break;
	case Object::T_MAP:
		out << "<Map...>";
		break;
	default:
		ASSERT2(0, "Unknown type for string representation `" << _object->name() << "`!");
	}

	return out.str();
}

void LuaFile::tab(uint32 _tabExtend)
{
	for (uint32 iter = 0; iter < _tabExtend * 4; ++iter)
		mOut << ' ';
}