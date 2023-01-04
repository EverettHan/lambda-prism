/* -*-c++-*- */
#ifndef CATGeoFactoryCGM_CATCGMBOAObject_H
#define CATGeoFactoryCGM_CATCGMBOAObject_H

#if defined ( CATCGMBOAObject )
  CATGeoFactoryCGM() ;
  CATRootContainerCGM    _MyRoot ;

  CATDeclareClass;                                                      
  virtual int   IsATypeOf(CATGeometricType itp) const;  
  virtual CATGeometricType GetVolatileType() const;     
  virtual size_t  GetStaticMemoryBytes() const;         
  CATCGMNewClassArrayDeclare;


  static CATGeoFactory * newExplicitFactory();

  // for debug BOA
  INLINE void  CheckAddRef(ULONG iCount)   { _MyRoot.CheckAddRef(iCount); }; 
  INLINE void  CheckRelease(ULONG iCount)  { _MyRoot.CheckRelease(iCount); }; 
  INLINE void  CheckEndOfLife(ULONG iCount)  { _MyRoot.CheckEndOfLife(iCount); }; 

  INLINE   void  SetInterface(CATICGMUnknown* Object) { _MyRoot.SetInterface(Object); }; 
#endif

#endif
