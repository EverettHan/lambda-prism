/* -*-c++-*- */
#ifndef CATRootContainerCGM_H
#define CATRootContainerCGM_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATRootContainerCGM:
// Implementation of the Root Container CXR2 CGM Objects.
//
//=============================================================================
// Usage notes:
//
// Creation of such a Container is done using CGMCreateRootContainer.
// Creation of objects is done using the CATGeoFactory or CATTopoFactory interfaces
// of this Root Container.
//
//=============================================================================
// Avril 2000  Add Unit                                        T.Chailloux
// Apr. 03 Parametre iNbLyingOnDataToRead pour UnStreamLyingOnData(...)   HCN 
// Apr. 03 CheckLyingOnAfterUnStream(...),
//         StreamSharpnessData(...), UnStreamSharpnessData(...)           HCN
// Oct. 09  CheckIncrementalStream                                        VUC
//=============================================================================
#include "ExportedByCATCGMFusion.h"        
#include "CATMathDef.h" 
#include "CATCGMScaleCategoryDef.h" 
#include "CATGeoFactory.h"
#include "CATCGMContainer.h"       
#include "CATCGMBOAObject.h"
#include "CATICGMUnknown.h"
#include "CATMathInline.h"

//checkincrementalStream
//#include "CATListOfCATCGMStream.h"

class CATGeoFactoryCGM;
class CATTolerance;
class CATech_CATGeoFactoryExt;
class CATCGMScaleCategoryDef;
class CATLISTP(CATBody);

class ExportedByCATCGMFusion CATRootContainerCGM : public CATCGMContainer
{


public :

  //---------------------------------------------------------------------------
  // Object Management
  //---------------------------------------------------------------------------
  short GetType();

  virtual void CheckStream(const CATCGMVersionDefinition *iVersion =NULL);


  // VUC : 16-10-09 Incremental Stream
  void CheckIncrementalStream(const CATCGMStreamVersion iVersion = CatCGMStream_UnknownVersion, CATCGMOperator *iOperator = NULL);

  //----------------------------------------------------------------------
  //  STREAM/UNSTREAM  Temporary Utility for LyingOn Security management
  //----------------------------------------------------------------------
  virtual void CheckLyingOnAfterUnStream(CATCGMStream &Str);

  //----------------------------------------------------------------------
  //  STREAM/UNSTREAM  LyingOn Data for R12 stream
  //----------------------------------------------------------------------
  virtual void StreamLyingOnData(CATCGMStream &Str); 
  virtual void UnStreamLyingOnData( CATCGMStream  & Str, CATULONG32 iNbLyingOnDataToRead, const CATBoolean      iTryPartialLoad); 

  //----------------------------------------------------------------------
  //  STREAM/UNSTREAM  Sharpness Data for R12 stream
  //----------------------------------------------------------------------
  virtual  void StreamSharpnessData(CATCGMStream &Str); 
  virtual  void UnStreamSharpnessData(  CATCGMStream  & Str, CATULONG32 iNbSharpnessDataToRead, const CATBoolean      iTryPartialLoad);
    
  //---------------------------------------------------------------------------
  // Object Modeler declaration
  //---------------------------------------------------------------------------
  CATCGMDeclareClass;

  virtual ~CATRootContainerCGM();

  //---------------------------------------------------------------------------
  //- Tolerances & Unit management
  //---------------------------------------------------------------------------
  CATPositiveLength GetModelSize() const ;
  CATPositiveLength GetUnit() const ;
  void SetModelSize(const CATPositiveLength &iTolerance) ;
  void SetModelSizeAndResolution( double      iModelSizeInUnit,
    CATBoolean  iKeepPreviousResolution,
    double      iResolutionC0FromModelSize);

  CATCGMTolerancesCompatibility CompareTolerances(CATGeoFactory *iOtherFactory, CATBoolean  iThrowIfComparableButNotIdentical);

  void SetUnit(const CATPositiveLength iUnitInMeter) ;

  void SetScaleCategory (CATCGMScaleCategory iScaleCategory);
  const CATTolerance & GetTolerance() const;

  //---------------------------------------------------------------------------
  //- Retreive the RootContainer/Factory from any object
  //---------------------------------------------------------------------------
  CATGeoFactory* GetFactory() const ;

  //---------------------------------------------------------------------------
  //- EB 
  //---------------------------------------------------------------------------
  void UnderOLKManagement(CATGeoFactory *iFactory);
  void UnderActivateManagement(CATGeoFactory *iFactory);
  static void UnderActivateObserver(CATCGMObject *IAmABody);
  //---------------------------------------------------------------------------
  //- Overloading Removes to redirect it to the Appendix
  //---------------------------------------------------------------------------
  virtual CATGeometry* GetNextChild(  CATGeometry       * Current,
    CATGeometricType    iType         = CATGeometryType,
    CATBoolean          WithImplicits = FALSE);

  virtual void  RemoveAllContents(const CATBoolean iUserClose);
  void  _RemoveAllContents(const CATBoolean iUserClose);


  //-------------------------------------------------------------------------
  // Explicit/Implicit management
  //-------------------------------------------------------------------------
  INLINE CATRootContainerCGM* GetImplicitContainer() const;
  INLINE CATRootContainerCGM* GetExplicitContainer() const;

  virtual CATGeoFactory   *GetExplicitFactory() const;

  //-------------------------------------------------------------------------
  // Obtention du Container surlequel sont geres le chainage des objects ...
  //-------------------------------------------------------------------------
  virtual CATCGMContainer * GetTrueContainer();

  //-------------------------------------------------------------------------
  // Tolerances for internal geometric objects
  //-------------------------------------------------------------------------
  double GetResolution(const CATResolutionType iResolutionType=CatC0) const ;
  INLINE CATPositiveLength GetInfinite()   const ;

  //-----------------------------------------------------------------------------
  // Datum access
  //-----------------------------------------------------------------------------
  const CATGeometry* GetDatum( const CATGeoFactory::CATDatumId DatumId ) const ;
  void SetDatum( const CATGeoFactory::CATDatumId DatumId, const CATGeometry* GeoDatum) ;

  virtual void Dump     ( CATCGMOutput& os );    //  Dump 
  virtual void DumpElem ( CATCGMOutput& os );    //  Dump 

  static void ConvertToV2R1( CATCGMObject &ioObject );

  static void StreamV2R0  ( CATCGMObject  &ioObject, CATCGMStream &ioStream );
  static void UnStreamV2R0( CATCGMObject  &ioObject, CATLISTP(CATICGMObject)& ListDependencies, CATCGMStream &ioStream );

  //---------------------------------------------------------------------
  // INTERNAL ONLY 
  //---------------------------------------------------------------------
  virtual void InitTransactionBit(const int value=0); 
  virtual void CheckUp(CATCX_CHECKUP* report);

  // internal use 
  virtual void TassTags();

  //-----------------------------------------------------------------------
  // INTERNAL ONLY : dedicated to NCGM Document management
  //----------------------------------------------------------------------
  static CATRootContainerCGM* ScanDoc(CATRootContainerCGM *const previous);  

  //---------------------------------------------------------------------
  // INTERNAL ONLY 
  //---------------------------------------------------------------------
  static CATBoolean CheckCopyAuthentication(CATGeoFactory* iReceiveFacotry, CATGeoFactory* iCopyFacotry);

  // Internal Use for CATCXBody
  CATGeoFactoryCGM *GetCATGeoFactoryCGM() const;


  virtual int  RemovingObject(CATICGMObject * Object);  

private :

  //-----------------------------------------------------------------------
  // INTERNAL ONLY : dedicated to OLK status in CGM ODT
  //----------------------------------------------------------------------
  static int Olk_RegressionStatus ();
  static int Activate_RegressionStatus ();

  //---------------------------------------------------------------------------
  //- Explicit Container (and Real Container which supports the Implicit Factory)
  //---------------------------------------------------------------------------
  CATRootContainerCGM *_EXPLICIT, *_IMPLICIT;
  CATGeoFactoryCGM    *_FactoryCGM;

#if defined ( CATCGMBOAObject )
  CATRootContainerCGM(CATCGMContainer * iContainer, const CATCGMScaleCategory iScaleCategory=ScaleNotSet);
  friend class CATGeoFactoryCGM;
#else
  CATRootContainerCGM( CATCGMContainer * iContainer, const CATCGMMode iMode = CatCGMImplicit
                                                   , const CATCGMScaleCategory iScaleCategory=ScaleNotSet );
  friend class CATCGMDebugImpl;
#endif

  CATRootContainerCGM(const CATRootContainerCGM &) ;      
  CATRootContainerCGM& operator=(const CATRootContainerCGM&);

  friend  class CATech_CATGeoFactoryExt;

};


//--------------------------------------------------------------------------
// Gestion de l'associativite au document NCGM
//-------------------------------------------------------------------------
INLINE CATRootContainerCGM* CATRootContainerCGM::GetImplicitContainer() const
{
  return ( (CGA.Explicit == 0) ? (CATRootContainerCGM*)this : _IMPLICIT );
}

INLINE CATRootContainerCGM* CATRootContainerCGM::GetExplicitContainer() const
{
  return ( (CGA.Explicit != 0)  ? (CATRootContainerCGM*)this : _EXPLICIT );
}

INLINE CATPositiveLength CATRootContainerCGM::GetInfinite() const   
{
	return ( ( _SHARED != NULL ) ? ( _SHARED -> _Infinite ) : 0 );   
}


#endif
