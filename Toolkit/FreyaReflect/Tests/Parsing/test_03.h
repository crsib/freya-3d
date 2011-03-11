#ifndef TEST_03_H_
#define TEST_03_H_

typedef int* pint;
typedef int** ppint;
typedef pint* pppint;

namespace a
{
	class tmp
	{
	public:
		float avar;
		
	protected:
		static int asvar;
	};
	
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

	//"Difficult" template test
	template<
		class T, 
		template<class> class S,
		int
	>
	class SomeStrangeTemplate {};

	typedef SomeStrangeTemplate<float*, templated_test, 2 + 2> SomeStrangeTemplateSpecialization;

	typedef templated_test<IntTemplate> DualTemplate;

	class ClassMemberTest : public DualTemplate
	{
	public: 
		void foo(float a, int b, int c);
		ClassMemberTest& operator+= ( const ClassMemberTest& _o );
		ClassMemberTest  operator + ( const ClassMemberTest& _o ) const; 
		
		operator float () const;
	};
	
	typedef void (ClassMemberTest::* SomePtrToClassMethod)(void) ;
	typedef void (* my_awesome_type_t)(int a, float b) ;
	//typedef std::basic_string<int> string32;
}

typedef a::TmpPtr localTmpPtr;

typedef void* pvoid;

const int var = 0;

#endif