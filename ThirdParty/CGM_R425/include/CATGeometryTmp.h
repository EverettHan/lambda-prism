/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATGeometryTmp:
// Temporary implementation of CATGeometry interface for Assembly Design
//
//=============================================================================
// Oct. 97   Creation 
// 20 05 2014  PKC rajout virtual manquant sur IsATypeOf
//=============================================================================
#ifndef CATGEOMETRYTMP_H
#define CATGEOMETRYTMP_H

#include "YP00TMP.h"
#include "CATCrvParam.h"
#include "CATCrvLimits.h"
#include "CATGeometry.h"
#include "CATCGMExtGeometry.h"

//-----------------------------------------------------------------------------
class ExportedByYP00TMP CATGeometryTmp: public CATCGMExtGeometry
{
public :

  //-------------------------------------------------------------------------
  // Object Management
  //-------------------------------------------------------------------------
  CATGeometryTmp() ;
  ~CATGeometryTmp() ;

  //=========================================================================
  //- Implementations for CATGeometry interface
  //=========================================================================
  CATMathBox GetBoundingBox() const;
  void GetBoundingBox(CATMathBox & oBox) const;
  void ApplyTransformation (const CATMathTransformation &TranformationToApply);
  int PutAttribute(const int Key, 
                   void* Buffer, 
                   const int Length, 
                   const int Control);
  const void* GetAttribute(const int Key, int& Length);
  int DeleteAttribute(const int Key);
  void DeleteAllAttribute();
  virtual CATLONG32  PutAttribute(CATCGMAttribute * NewAttr) ;
  virtual CATCGMAttribute * GetAttribute(const CATCGMAttrId*) ;
  virtual CATLONG32 ReleaseAttribute(CATCGMAttribute * NewAttr) ;
  virtual void GetListAttribute(CATLISTP(CATCGMAttribute) &, const CATCGMAttrId*attrid=NULL);
  virtual void GetNextAttribute(CATCGMAttribute * PrevAttr,  CATCGMAttribute *& NextAttr);
  //-Nouvelles methodes de CATGeometry
  void Move3D(CATTransfoManager &T);
  CATGeometry * CloneAndMove3D(CATTransfoManager &T);
  virtual int IsATypeOf(CATGeometricType TypeReference);  
  CATICGMObject *Clone(CATCloneManager &Clone);
  CATBoolean   IsDeepConfused(CATTransfoManager & iTransfo,
                              const CATGeometry * iTGeometry) const;
  void GetLinks (CATLISTP(CATICGMObject) &Links,
                 CATCGMLinkType iLink = CatCGMDependancies,
                 CATRCOLL(int)* oSharedStatus = NULL,
                 CATLISTV(CATString)* String  = NULL);
  void GetAllLinks(CATLISTP(CATGeometry) &Links);
  CATULONG32  GetUseCount(CATCGMUseCountType iUseType =CatCGMUseCountAllCATICGMObject) const;
  CATULONG32  GetPersistentTag() const;
  CATGeoFactory* GetContainer(CATBoolean iThrowOnNullFactory = TRUE, CATCGMMode iMode = CatCGMExplicit);
  void SetExplicit();
  void SetMode(CATCGMMode iMode);
  CATLONG32 IsExplicit() const ; 
  CATBoolean IsModifiable() ;
  void CompletedFreeze(CATCGMOperator *iOperator); 
  void Completed(CATBoolean IsNoMoreModifiable = FALSE, 
                 const char IdentityBuildOperator[] = "",
                 const CATTopData  * iData = NULL);
  int Check();
  virtual void *GetImplementCGM(CATGeometricType iTypeReference) const; 
  virtual void *IsCGMV5() const;
  virtual int  IsImplementCGMRemoved(const CATGeometricType iTypeReference=CATGeometryType) const;
  CATBoolean HasBeenCompletedAsNoMoreModifiable() const ;
  CATBoolean HasBeenLoaded() const;
  //-
protected :
  void RaiseUnavailableMethod ( const char * MethodName ) const ;
};

#endif
