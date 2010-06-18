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

#ifndef _FADIFF_H
#define _FADIFF_H

#include <math.h>
#include <iostream>

#include "fadbad.h"

template <class T>
class FTypeName
{
public:
	T v;
	T *g;
	int gsize;

	FTypeName();
	template <class U>
	FTypeName(const U& x):v(x),g(0),gsize(0){}
	FTypeName(const FTypeName& a);
	virtual ~FTypeName();
	FTypeName& operator= (const FTypeName& a);
	void diff(int idx, int n);
	void touchg(int n);
	T& x();
	T& d(int i);

  /* Declaration of overloading of (?)= */
	FTypeName& operator += (const FTypeName& x);
	FTypeName& operator -= (const FTypeName& x);
	FTypeName& operator *= (const FTypeName& x);
	FTypeName& operator /= (const FTypeName& x);
#ifdef BaseType
	FTypeName& operator += (const BaseType& x);
	FTypeName& operator -= (const BaseType& x);
	FTypeName& operator *= (const BaseType& x);
	FTypeName& operator /= (const BaseType& x);
#endif
};

template <class T>
INLINE1 FTypeName<T>::FTypeName():v(0),g(0),gsize(0)
{
}

/* Definition moved to class-declaration because of MS VC++ 6.0
template <class T>
template <class U>
INLINE1 FTypeName<T>::FTypeName(const U& x):v(x),g(0),gsize(0)
{
}
*/

template <class T>
INLINE2 FTypeName<T>::FTypeName(const FTypeName& a)
{
	v=a.v;
	gsize=a.gsize;
	if (gsize>0)
	{
		g=newArray(T,gsize);
		for (int i=0;i<gsize;i++) g[i]=a.g[i];
	}
	else
		g=0;
}

template <class T>
INLINE1 FTypeName<T>::~FTypeName()
{
	if (g!=0) delArray(T,g);
}

template <class T>
INLINE2 FTypeName<T>& FTypeName<T>::operator= (const FTypeName& a)
{
	v=a.v;
	if (g!=0) delArray(T,g);
	gsize=a.gsize;
	if (gsize>0)
	{
		g=newArray(T,gsize);
		for (int i=0;i<gsize;i++) g[i]=a.g[i];
	}
	else
		g=0;
	return *this;
}

template <class T>
INLINE2 void FTypeName<T>::diff(int idx, int n)
{
	int i;
	g=newArray(T,n);
	gsize=n;
	for(i=0;i<idx;g[i++]=T(0));
	g[idx]=T(1);
	for(i=idx+1;i<n;g[i++]=T(0));
}

template <class T>
INLINE2 void FTypeName<T>::touchg(int n)
{
/* This routine creates the vector for storage of g and initializes
all elements to zero. */
	INTERNAL_ASSERT(g==0,"g vector already allocated");
	if (n>0)
	{
		g=newArray(T,n);
		gsize=n;
	}
};

template <class T>
INLINE1 T& FTypeName<T>::x()
{
	return v;
}

template <class T>
INLINE2 T& FTypeName<T>::d(int i)
{
	if (g==0)
	{
		static T zero(0);
		zero=T(0);
		return zero;
	}
	else
	{
		USER_ASSERT(i<gsize,"Index out of bounds");
		return g[i];
	}
}

template <class T>
INLINE2 std::ostream& operator << (std::ostream& os, const FTypeName<T>& o)
{
	os << "{" << o.v;
	if (o.g!=0)
	{
		os << " [ ";
		for (int i=0;i<o.gsize;i++) os << o.g[i] << " ";
		os << "]";
	}
	os << "}";
	return os;
}

template <class T>
INLINE2 FTypeName<T> add1(const T& a, const FTypeName<T>& b)
{
	FTypeName<T> c(a+b.v);
	c.touchg(b.gsize);
	for (int i=0;i<b.gsize;i++) c.g[i]=b.g[i];
	return c;
}

template <class T>
INLINE2 FTypeName<T> add2(const FTypeName<T>& a,const T& b)
{
	FTypeName<T> c(a.v+b);
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i];
	return c;
}

#ifdef BaseType
template <class T>
INLINE2 FTypeName<T> operator+ (const BaseType& a, const FTypeName<T>& b)
{
	FTypeName<T> c(a+b.v);
	c.touchg(b.gsize);
	for (int i=0;i<b.gsize;i++) c.g[i]=b.g[i];
	return c;
}

template <class T>
INLINE2 FTypeName<T> operator+ (const FTypeName<T>& a,const BaseType& b)
{
	FTypeName<T> c(a.v+b);
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i];
	return c;
}
#endif

template <class T>
INLINE2 FTypeName<T> operator+ (const FTypeName<T>& a, const FTypeName<T>& b)
{
	if (a.gsize==0) return add1(a.v,b);
	if (b.gsize==0) return add2(a,b.v);
	FTypeName<T> c(a.v+b.v);
	USER_ASSERT(a.gsize==b.gsize,"derivative vectors not of same size in operator+");
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i]+b.g[i];
	return c;
}

template <class T>
INLINE2 FTypeName<T> sub1(const T& a, const FTypeName<T>& b)
{
	FTypeName<T> c(a-b.v);
	c.touchg(b.gsize);
	for (int i=0;i<b.gsize;i++) c.g[i]=-b.g[i];
	return c;
}

template <class T>
INLINE2 FTypeName<T> sub2(const FTypeName<T>& a,const T& b){
	FTypeName<T> c(a.v-b);
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i];
	return c;
}

#ifdef BaseType
template <class T>
INLINE2 FTypeName<T> operator- (const BaseType& a, const FTypeName<T>& b)
{
	FTypeName<T> c(a-b.v);
	c.touchg(b.gsize);
	for (int i=0;i<b.gsize;i++) c.g[i]=-b.g[i];
	return c;
}

template <class T>
INLINE2 FTypeName<T> operator- (const FTypeName<T>& a,const BaseType& b)
{
	FTypeName<T> c(a.v-b);
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i];
	return c;
}
#endif

template <class T>
INLINE2 FTypeName<T> operator- (const FTypeName<T>& a, const FTypeName<T>& b)
{
	if (a.gsize==0) return sub1(a.v,b);
	if (b.gsize==0) return sub2(a,b.v);
	FTypeName<T> c(a.v-b.v);
	USER_ASSERT(a.gsize==b.gsize,"derivative vectors not of same size in operator-");
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i]-b.g[i];
	return c;
}

template <class T>
INLINE2 FTypeName<T> mul1(const T& a, const FTypeName<T>& b)
{
	FTypeName<T> c(a*b.v);
	c.touchg(b.gsize);
	for (int i=0;i<b.gsize;i++) c.g[i]=b.g[i]*a;
	return c;
}

template <class T>
INLINE2 FTypeName<T> mul2(const FTypeName<T>& a,const T& b)
{
	FTypeName<T> c(a.v*b);
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i]*b;
	return c;
}

#ifdef BaseType
template <class T>
INLINE2 FTypeName<T> operator* (const BaseType& a, const FTypeName<T>& b)
{
	FTypeName<T> c(a*b.v);
	c.touchg(b.gsize);
	for (int i=0;i<b.gsize;i++) c.g[i]=b.g[i]*a;
	return c;
}

template <class T>
INLINE2 FTypeName<T> operator* (const FTypeName<T>& a,const BaseType& b)
{
	FTypeName<T> c(a.v*b);
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i]*b;
	return c;
}
#endif

template <class T>
INLINE2 FTypeName<T> operator* (const FTypeName<T>& a, const FTypeName<T>& b)
{
	if (a.gsize==0) return mul1(a.v,b);
	if (b.gsize==0) return mul2(a,b.v);
	FTypeName<T> c(a.v*b.v);
	USER_ASSERT(a.gsize==b.gsize,"derivative vectors not of same size in operator*");
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i]*b.v+b.g[i]*a.v;
	return c;
}

template <class T>
INLINE2 FTypeName<T> div1(const T& a, const FTypeName<T>& b)
{
	FTypeName<T> c(a/b.v);
	T tmp(-c.v/b.v);
	c.touchg(b.gsize);
	for (int i=0;i<b.gsize;i++) c.g[i]=tmp*b.g[i];
	return c;
}

template <class T>
INLINE2 FTypeName<T> div2(const FTypeName<T>& a,const T& b)
{
	FTypeName<T> c(a.v/b);
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=(a.g[i])/b;
	return c;
}

#ifdef BaseType
template <class T>
INLINE2 FTypeName<T> operator/ (const BaseType& a, const FTypeName<T>& b)
{
	FTypeName<T> c(a/b.v);
	T tmp(-c.v/b.v);
	c.touchg(b.gsize);
	for (int i=0;i<b.gsize;i++) c.g[i]=tmp*b.g[i];
	return c;
}

template <class T>
INLINE2 FTypeName<T> operator/ (const FTypeName<T>& a,const BaseType& b)
{
	FTypeName<T> c(a.v/b);
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=(a.g[i])/b;
	return c;
}
#endif

template <class T>
INLINE2 FTypeName<T> operator/ (const FTypeName<T>& a, const FTypeName<T>& b)
{
	if (a.gsize==0) return div1(a.v,b);
	if (b.gsize==0) return div2(a,b.v);
	FTypeName<T> c(a.v/b.v);
	USER_ASSERT(a.gsize==b.gsize,"derivative vectors not of same size in operator/");
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=(a.g[i]-c.v*b.g[i])/b.v;
	return c;
}

template <class T>
INLINE2 FTypeName<T> pow1(const T& a, const FTypeName<T>& b)
{
	FTypeName<T> c(pow(a,b.v));
	T tmp(b.v*pow(a,b.v-FADBAD_ONE)),tmp1(c.v*log(a));
	c.touchg(b.gsize);
	for (int i=0;i<b.gsize;i++)
		c.g[i]=tmp1*b.g[i];
	return c;
}
template <class T>
INLINE2 FTypeName<T> pow2(const FTypeName<T>& a, const T& b)
{
	FTypeName<T> c(pow(a.v,b));
	T tmp(b*pow(a.v,b-FADBAD_ONE)),tmp1(c.v*log(a.v));
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++)
		c.g[i]=tmp*a.g[i];
	return c;
}

#ifdef BaseType
template <class T>
INLINE2 FTypeName<T> pow (const BaseType& a, const FTypeName<T>& b)
{
	FTypeName<T> c(pow(a,b.v));
	T tmp(c.v*log(a));
	c.touchg(b.gsize);
	for (int i=0;i<b.gsize;i++) c.g[i]=tmp*b.g[i];
	return c;
}

template <class T>
INLINE2 FTypeName<T> pow (const FTypeName<T>& a,const BaseType& b)
{
	FTypeName<T> c(pow(a.v,b));
	T tmp(b*pow(a.v,b-FADBAD_ONE));
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=tmp*a.g[i];
	return c;
}
#endif

template <class T>
INLINE2 FTypeName<T> pow (const FTypeName<T>& a, const FTypeName<T>& b)
{
	if (a.gsize==0) return pow1(a.v,b);
	if (b.gsize==0) return pow2(a,b.v);
	FTypeName<T> c(pow(a.v,b.v));
	USER_ASSERT(a.gsize==b.gsize,"derivative vectors not of same size in pow");
	T tmp(b.v*pow(a.v,b.v-FADBAD_ONE)),tmp1(c.v*log(a.v));
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++)
		c.g[i]=tmp*a.g[i]+tmp1*b.g[i];
	return c;
}

/* Unary operators */
template <class T>
INLINE2 FTypeName<T> operator+ (const FTypeName<T>& a)
{
	FTypeName<T> c(a.v);
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i];
	return c;
}

template <class T>
INLINE2 FTypeName<T> operator- (const FTypeName<T>& a)
{
	FTypeName<T> c(-a.v);
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=-a.g[i];
	return c;
}

template <class T>
INLINE2 FTypeName<T> fabs (const FTypeName<T>& a)
{
	return (a < 0 ? -a : a);
}


template <class T>
INLINE2 FTypeName<T> pow (const FTypeName<T>& a,int b)
{
	FTypeName<T> c(pow(a.v,b));
	c.touchg(a.gsize);
	T tmp(b*pow(a.v,b-1));
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i]*tmp;
	return c;
}

template <class T>
INLINE2 FTypeName<T> sqr (const FTypeName<T>& a)
{
	FTypeName<T> c(_sqr(a.v));
	c.touchg(a.gsize);
	T tmp(FADBAD_TWO*a.v);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i]*tmp;
	return c;
}

template <class T>
INLINE2 FTypeName<T> exp (const FTypeName<T>& a)
{
	FTypeName<T> c(exp(a.v));
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i]*c.v;
	return c;
}

template <class T>
INLINE2 FTypeName<T> log (const FTypeName<T>& a)
{
	FTypeName<T> c(log(a.v));
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i]/a.v;
	return c;
}

template <class T>
INLINE2 FTypeName<T> sqrt (const FTypeName<T>& a)
{
	FTypeName<T> c(sqrt(a.v));
	T tmp(c.v*FADBAD_TWO);
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i]/tmp;
	return c;
}

template <class T>
INLINE2 FTypeName<T> sin (const FTypeName<T>& a)
{
	FTypeName<T> c(sin(a.v));
	T tmp(cos(a.v));
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i]*tmp;
	return c;
}

template <class T>
INLINE2 FTypeName<T> cos (const FTypeName<T>& a)
{
	FTypeName<T> c(cos(a.v));
	T tmp(-sin(a.v));
	c.touchg(a.gsize);
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i]*tmp;
	return c;
}

template <class T>
INLINE2 FTypeName<T> tan (const FTypeName<T>& a)
{
	FTypeName<T> c(tan(a.v));
	c.touchg(a.gsize);
	T tmp(FADBAD_ONE+_sqr(c.v));
	for (int i=0;i<a.gsize;i++)  c.g[i]=a.g[i]*tmp;
	return c;
}

template <class T>
INLINE2 FTypeName<T> asin (const FTypeName<T>& a)
{
	FTypeName<T> c(asin(a.v));
	c.touchg(a.gsize);
	T tmp(FADBAD_ONE/sqrt(FADBAD_ONE-_sqr(a.v)));
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i]*tmp;
	return c;
}

template <class T>
INLINE2 FTypeName<T> acos (const FTypeName<T>& a)
{
	FTypeName<T> c(acos(a.v));
	c.touchg(a.gsize);
	T tmp(-FADBAD_ONE/sqrt(FADBAD_ONE-_sqr(a.v)));
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i]*tmp;
	return c;
}

template <class T>
INLINE2 FTypeName<T> atan (const FTypeName<T>& a)
{
	FTypeName<T> c(atan(a.v));
	c.touchg(a.gsize);
	T tmp(FADBAD_ONE/(FADBAD_ONE+_sqr(a.v)));
	for (int i=0;i<a.gsize;i++) c.g[i]=a.g[i]*tmp;
	return c;
}

/* --------------------------------------------------------------------- */
/*                                                                       */
/*                    COMPOUND ASSIGNMENT OPERATORS                      */
/*                                                                       */
/* --------------------------------------------------------------------- */

/* Code for FTypeNames += operator. Uses overloaded definition of + */
template <class T>
INLINE1 FTypeName<T>& FTypeName<T>::operator += (const FTypeName<T>& x)
{
	return *this = (*this)+x;
}

/* Code for FTypeNames -= operator. Uses overloaded definition of - */
template <class T>
INLINE1 FTypeName<T>& FTypeName<T>::operator -= (const FTypeName<T>& x)
{
	return *this = *this-x;
}

/* Code for FTypeNames *= operator. Uses overloaded definition of * */
template <class T>
INLINE1 FTypeName<T>& FTypeName<T>::operator *= (const FTypeName<T>& x)
{
	return *this = *this*x;
}

/* Code for FTypeNames /= operator. Uses overloaded definition of / */
template <class T>
INLINE1 FTypeName<T>& FTypeName<T>::operator /= (const FTypeName<T>& x)
{
	return *this = *this/x;
}

#ifdef BaseType
/* Code for FTypeNames += operator. Uses overloaded definition of + */
template <class T>
INLINE0 FTypeName<T>& FTypeName<T>::operator += (const BaseType& x)
{
	return *this = (*this)+x;
}

/* Code for FTypeNames -= operator. Uses overloaded definition of - */
template <class T>
INLINE0 FTypeName<T>& FTypeName<T>::operator -= (const BaseType& x)
{
	return *this = *this-x;
}

/* Code for FTypeNames *= operator. Uses overloaded definition of * */
template <class T>
INLINE0 FTypeName<T>& FTypeName<T>::operator *= (const BaseType& x)
{
	return *this = *this*x;
}

/* Code for FTypeNames /= operator. Uses overloaded definition of / */
template <class T>
INLINE0 FTypeName<T>& FTypeName<T>::operator /= (const BaseType& x)
{
	return *this = *this/x;
}
#endif

#ifdef HASEQ
template <class T>
INLINE1 bool operator == (const FTypeName<T> &a, const FTypeName<T> &b)
{
	return a.v==b.v;
}
#ifdef BaseType
template <class T>
INLINE1 bool operator == (const FTypeName<T> &a, const BaseType &b)
{
	return a.v==b;
}
template <class T>
INLINE1 bool operator == (const BaseType &a, const FTypeName<T> &b)
{
	return a==b.v;
}
#endif
template <class T>
INLINE1 bool operator != (const FTypeName<T> &a, const FTypeName<T> &b)
{
	return a.v!=b.v;
}
#ifdef BaseType
template <class T>
INLINE1 bool operator != (const FTypeName<T> &a, const BaseType &b)
{
	return a.v!=b;
}
template <class T>
INLINE1 bool operator != (const BaseType &a, const FTypeName<T> &b)
{
	return a!=b.v;
}
#endif
#endif
#ifdef HASGT
template <class T>
INLINE1 bool operator > (const FTypeName<T> &a, const FTypeName<T> &b)
{
	return a.v>b.v;
}
#ifdef BaseType
template <class T>
INLINE1 bool operator > (const FTypeName<T> &a, const BaseType &b)
{
	return a.v>b;
}
template <class T>
INLINE1 bool operator > (const BaseType &a, const FTypeName<T> &b)
{
	return a>b.v;
}
#endif
#endif
#ifdef HASGEQ
template <class T>
INLINE1 bool operator >= (const FTypeName<T> &a, const FTypeName<T> &b)
{
	return a.v>=b.v;
}
#ifdef BaseType
template <class T>
INLINE1 bool operator >= (const FTypeName<T> &a, const BaseType &b)
{
	return a.v>=b;
}
template <class T>
INLINE1 bool operator >= (const BaseType &a, const FTypeName<T> &b)
{
	return a>=b.v;
}
#endif
#endif
#ifdef HASLT
template <class T>
INLINE1 bool operator < (const FTypeName<T> &a, const FTypeName<T> &b)
{
	return a.v<b.v;
}
#ifdef BaseType
template <class T>
INLINE1 bool operator < (const FTypeName<T> &a, const BaseType &b)
{
	return a.v<b;
}
template <class T>
INLINE1 bool operator < (const BaseType &a, const FTypeName<T> &b)
{
	return a<b.v;
}
#endif
#endif
#ifdef HASLEQ
template <class T>
INLINE1 bool operator <= (const FTypeName<T> &a, const FTypeName<T> &b)
{
	return a.v<=b.v;
}
#ifdef BaseType
template <class T>
INLINE1 bool operator <= (const FTypeName<T> &a, const BaseType &b)
{
	return a.v<=b;
}
template <class T>
INLINE1 bool operator <= (const BaseType &a, const FTypeName<T> &b)
{
	return a<=b.v;
}
#endif
#endif


template <class T>
INLINE1 std::istream & operator >> (std::istream & in, FTypeName<T> &b)
{
    b = 0;
    in >> b.v;
	return in;
}

#endif
