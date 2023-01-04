// COPYRIGHT DASSAULT SYSTEMES 2019, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyQMSpecialization.h
//
//===================================================================
// October 2019  Creation JBS2
//===================================================================
#ifndef CATPolyQMSpecialization_H
#define CATPolyQMSpecialization_H


/**
* Enable QM from 3*3 to 5*5 dimension.
*/
const unsigned int minDimension = 3;
const unsigned int maxDimension = 5;


/**
* Recursive template class with methods to instatiate all QM templates.
*/
template<template<unsigned int> class Template, unsigned int Dimension = minDimension>
class CATPolyQMTemplateSpecialization {
public:
  template<class ReturnType, class ...Args>
  static ReturnType *New(unsigned int dimension, Args... args);

  template<class ...Args>
  static void Execute(unsigned int dimension, Args... args);

private:
  static inline void assertDimension();
};

/**
* Specialization for recursive terminal case.
*/
template<template<unsigned int> class Template>
class CATPolyQMTemplateSpecialization<Template, maxDimension> {
public:
  template<class ReturnType, class ...Args>
  static ReturnType *New(unsigned int dimension, Args... args);

  template<class ...Args>
  static void Execute(unsigned int dimension, Args... args);
};


/**
* Implementations for general case.
*/
template<template<unsigned int> class Template, unsigned int Dimension>
template<class ReturnType, class ...Args>
ReturnType *CATPolyQMTemplateSpecialization<Template, Dimension>::New(unsigned int dimension, Args... args)
{
  assertDimension();

  if (dimension == Dimension)
    return new Template<Dimension>(args...);
  else
    return CATPolyQMTemplateSpecialization<Template, Dimension + 1>::template New<ReturnType, Args...>(dimension, args...);
}

template<template<unsigned int> class Template, unsigned int Dimension>
template<class ...Args>
void CATPolyQMTemplateSpecialization<Template, Dimension>::Execute(unsigned int dimension, Args... args)
{
  assertDimension();

  if (dimension == Dimension)
    Template<Dimension>::Execute(args...);
  else
    CATPolyQMTemplateSpecialization<Template, Dimension + 1>::template Execute<Args...>(dimension, args...);
}

template<template<unsigned int> class Template, unsigned int Dimension>
inline void CATPolyQMTemplateSpecialization<Template, Dimension>::assertDimension()
{
  static_assert(minDimension <= Dimension && Dimension < maxDimension, "CATPolyQMTemplateSpecialization with wrong current dimension !");
}


/**
* Implementation for final case.
*/
template<template<unsigned int> class Template>
template<class ReturnType, class ...Args>
ReturnType *CATPolyQMTemplateSpecialization<Template, maxDimension>::New(unsigned int dimension, Args... args)
{
  if (dimension == maxDimension)
    return new Template<maxDimension>(args...);
  else
    return nullptr;
}

template<template<unsigned int> class Template>
template<class ...Args>
void CATPolyQMTemplateSpecialization<Template, maxDimension>::Execute(unsigned int dimension, Args... args)
{
  if (dimension == maxDimension)
    Template<maxDimension>::Execute(args...);
}


#endif
