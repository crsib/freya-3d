#ifndef TEST_03_H_
#define TEST_03_H_

typedef int* pint;
typedef int** ppint;
typedef pint* pppint;

namespace a
{
	class tmp {};
	
	typedef tmp * const TmpPtr;
	
	typedef TmpPtr& TmpPtrRef;
	
	struct tmp2 {};
	enum   tmp3 {};
	
	typedef tmp3 EnumAlias;
	typedef tmp2 StructAlias;
	
	typedef struct {} AnonAlias;
	
	template<class T>
	class templated_test {};
	
	typedef templated_test<int> IntTemplate;
	
	class ClassMemberTest
	{
	public: 
		void foo();
	};
	
	typedef void (ClassMemberTest::* SomePtrToClassMethod)(void) ;
}

typedef a::TmpPtr localTmpPtr;

typedef void* pvoid;

#endif