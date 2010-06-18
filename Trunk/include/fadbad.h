// Copyright (C) 1996-2003 Claus Bendtsen and Ole Stauning (ole.st@uning.dk)
// All rights reserved.

// This code is provided "as is", without any warranty of any kind,
// either expressed or implied, including but not limited to, any implied
// warranty of merchantibility or fitness for any purpose. In no event
// will any party who distributed the code be liable for damages or for
// any claim(s) by any other party, including but not limited to, any
// lost profits, lost monies, lost data or data rendered inaccurate,
// losses sustained by third parties, or any other special, incidental or
// consequential damages arising out of the use or inability to use the
// program, even if the possibility of such damages has been advised
// against. The entire risk as to the quality, the performance, and the
// fitness of the program for any particular purpose lies with the party
// using the code.

// This code, and any derivative of this code, may not be used in a
// commercial package without the prior explicit written permission of
// the authors. Verbatim copies of this code may be made and distributed
// in any medium, provided that this copyright notice is not removed or
// altered in any way. No fees may be charged for distribution of the
// codes, other than a fee to cover the cost of the media and a
// reasonable handling fee.

// ***************************************************************
// ANY USE OF THIS CODE CONSTITUTES ACCEPTANCE OF THE TERMS OF THE
//                         COPYRIGHT NOTICE
// ***************************************************************

#ifndef _FADBAD_H
#define _FADBAD_H

// Use BaseType double as the default BaseType.
#ifndef BaseType
#define BaseType double
#define HASEQ
#define HASNEQ
#define HASGT
#define HASGEQ
#define HASLT
#define HASLEQ
#endif

// Name for backward AD type:
#define BTypeName B

// Name for forward AD type:
#define FTypeName F

// Name for taylor AD type:
#define TTypeName T

// Should always be inline:
#define INLINE0 inline

// Methods with only one line:
#define INLINE1 inline

// Methods with more than one line:
#define INLINE2 inline

#ifdef __SUNPRO_CC
// FOR SOME REASON SOME INLINES CAUSES 
// UNRESOLVED SMBOLS ON SUN.
#undef INLINE0
#undef INLINE1
#undef INLINE2
#define INLINE0
#define INLINE1
#define INLINE2
#endif

#define FADBAD_ZERO BaseType(0.0)
#define FADBAD_ONE BaseType(1.0)
#define FADBAD_TWO BaseType(2.0)

// Define this if you want assertions, etc..
#ifdef _DEBUG

#include <sstream>
#include <iostream>

inline void ReportError(const char* errmsg)
{
	std::cout<<errmsg<<std::endl;
}

#define USER_ASSERT(check,msg)\
	if (!(check))\
	{\
		std::ostringstream ost;\
		ost<<"User assertion failed: \""<<msg<<"\", at line "<<__LINE__<<", file "<<__FILE__<<std::endl;\
		ReportError(ost.str().c_str());\
	}
#define INTERNAL_ASSERT(check,msg)\
	if (!(check))\
	{\
		std::ostringstream ost;\
		ost<<"Internal error: \""<<msg<<"\", at line "<<__LINE__<<", file "<<__FILE__<<std::endl;\
		ReportError(ost.str().c_str());\
	}
#define ASSERT(check)\
	if (!(check))\
	{\
		std::ostringstream ost;\
		ost<<"Internal error at line "<<__LINE__<<", file "<<__FILE__<<std::endl;\
		ReportError(ost.str().c_str());\
	}
#ifdef _TRACE
#define DEBUG(code) code;
#else
#define DEBUG(code)
#endif

#include <typeinfo>

template <typename T>
class MemMgrT
{
public:
	static T* doNewScalar()
	{
		std::cout << "Creating " << typeid(T).name();
		T* t=new T;
		std::cout << " addr=" << t << ", size=" << sizeof(t) << std::endl;
		return t;
	}
	static T* doNewCopy(const T& a)
	{
		std::cout << "Creating " << typeid(T).name() << " as copy";
		T* t=new T(a);
		std::cout << " addr=" << t << ", size=" << sizeof(t) << std::endl;
		return t;
	}
	static T* doNewArray(const size_t s)
	{
		std::cout << "Creating array of " << typeid(T).name() << " with length " << s;
		T* t=new T[s];
		std::cout << " addr=" << t << ", size=" << sizeof(t) << std::endl;
		return t;
	}
	static void doDelScalar(T*t)
	{
		std::cout << "Deleting " << typeid(T).name();
		std::cout << " at addr=" << t << std::endl;
		delete t;
	}
	static void doDelArray(T*t)
	{
		std::cout << "Deleting array of " << typeid(T).name();
		std::cout << " at addr=" << t << std::endl;
		delete[]t;
	}
};

/* Code for allocation-debugging
#define newScalar(T) MemMgrT< T >::doNewScalar()
#define newCopy(T,A) MemMgrT< T >::doNewCopy(A)
#define newArray(T,S) MemMgrT< T >::doNewArray(S)
#define delScalar(T,P) MemMgrT< T >::doDelScalar(P)
#define delArray(T,P) MemMgrT< T >::doDelArray(P)
*/
#define newScalar(T) new T
#define newCopy(T,A) new T(A)
#define newArray(T,S) new T[S]
#define delScalar(T,P) delete P
#define delArray(T,P) delete[]P

#else

#define USER_ASSERT(check,msg)
#define INTERNAL_ASSERT(check,msg)
#define ASSERT(check)
#define DEBUG(code)

#define newScalar(T) new T
#define newCopy(T,A) new T(A)
#define newArray(T,S) new T[S]
#define delScalar(T,P) delete P
#define delArray(T,P) delete[]P

#endif




#ifndef _sqr
#define _sqr(x) ((x)*(x))
#endif
#ifndef _pow
#define _pow(x,n) pow(x,n)
#endif



#endif



