//=================================================================================
// Copyright Dassault Systemes Provence 2017, All Rights Reserved
//=================================================================================
//
// CATSobAddRefRelease.h
//
//=================================================================================
//
// Usage notes : Macros to add AddRef / Release abilities to a class
//
//=================================================================================
// 21.02.2017 : RAQ : Creation
//=================================================================================
#ifndef CATSobAddRefRelease_H
#define CATSobAddRefRelease_H



//Macro to use in your class'declaration
#define SOB_DECLARE_ADDREF_RELEASE                            \
public:                                                       \
                                                              \
inline void AddRef() { ++m_refCounter; }                      \
inline void Release() { if(--m_refCounter==0) delete this; }  \
                                                              \
private:                                                      \
                                                              \
  int m_refCounter;                                           \
       
       
//Macro to use in your class'contructors to initialize the ref-counter
#define SOB_INIT_ADDREF_RELEASE \
  m_refCounter(1)               \
       
     
#endif  //CATSobAddRefRelease_H


