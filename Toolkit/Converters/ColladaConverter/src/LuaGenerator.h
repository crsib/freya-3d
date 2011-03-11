/*
 * LuaGenerator.h
 *
 *  Created on: 19.02.2010
 *      Author: Alexander Ptakhin
 */

#ifndef LUA_GENERATOR_H
#define LUA_GENERATOR_H

#include "common.h"
#include <map>

class Object;

class Object
{
protected:
	typedef std::map<String, Object*> Fields;
	typedef Fields::iterator FieldsIter;
	typedef Fields::const_iterator FieldsConstIter;

public:
    /// Type if Single. See States.
	enum Type
	{
		T_STRING,
		T_INT,
		T_FLOAT,
		T_FLOAT3,
		T_FLOAT4,

        T_MAP, /// This type for S_MAP state.
	};

public:
	Object();
	Object(const String& _name);

	const String& name() const { return mName; }

	Object& operator = (float _f);
	Object& operator = (int _f);
	Object& operator = (const String& _str);
	Object& operator = (const char* _str);

	Object* get(const String& _name);
	const Object* get(const String& _name) const;

	void set(Object* _value);

    bool isInitialized() const { return mState == S_NOT_INITIALIZED; }

	bool isSingle() const { return mState == S_NOT_INITIALIZED || mState == S_SINGLE; }
	bool isMap() const { return mState == S_NOT_INITIALIZED || mState == S_MAP; }

	Type type() const { return mType; }

	String typeName(Type _type) const;

	/// Only for Singles
	//String getStringValue() const;

	int valInt() const;
	float valFloat() const;
	char* valCStr() const;

	
public:

	typedef FieldsConstIter Iter;

	
	Iter begin() const;
	Iter end() const;

protected:
	

	Type mType;

protected:

	// Initialize single-value object or checks it.
	void initSingle(Type _type);
	void checkSingle(Type _type) const;

	void initMap();
	void checkMap() const;

    // Joan: I'm your father!
    // Huan: Not he! I'm you real father!
	void notifyParent(Object* _parent);

	enum States
	{
		S_NOT_INITIALIZED,
		/// Has only one single value
		S_SINGLE,
		S_MAP
	};

	States mState;

	// For single-value object
	union Value
	{
		char* str;
		int i;
		float f;
		float* vf;
		Object* o;
	};

	Value mValue;

	/// Childs
	Fields mFields;
	
	String mName;

	Object* mParent;

};

class LuaFile
{
public:
	LuaFile(const String& _filename);

	void write(const Object* _root);

protected:
	void writeRecursive(const Object* _object, uint32 _tabExtend);

	String stringValue(const Object* _object);

	void tab(uint32 _tabExtend);

protected:

	std::ofstream mOut;

	const String mFileName;
};


#endif // #ifndef LUA_GENERATOR_H