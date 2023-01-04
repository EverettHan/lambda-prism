/* -*-c++-*- */
#ifndef CATGeometryCGM_H
#define CATGeometryCGM_H
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATGeometryCGM:
// Master class for geometric entities in CGM container (CXR2)
//
//=============================================================================
// Jan. 97   Creation                                        R. Rorato
// Dec. 97   Add IsIdentity2D                                I. Levy    (ily) 
// Feb. 98   Add ComputeMaxAngles, ComputeAngle              I. Levy    (ily)
// Aug. 98   Remove ComputeMaxAngles, ComputeAngle           I. Levy    (ily)
// Oct. 00   IsIdentity2D-> CATGeometryUtilities             ckn
// Jan. 08   Ajout UnstreamData pour CATSubdivMesh           R.Nosenzo  (rno) 
// May  11   Added the function CompareGeometry().           R. Moody   (r1y)
//=============================================================================
#include "ExportedByCATCGMFusion.h"
#include "CATIACGMLevel.h"
#include "CATMathDef.h"                        // For interface
#include "CATGeoFactory.h"
#include "CATCGMObject.h"                   // For inheritance
#include "CATMathInline.h"

class CATCompareContext;
class CATCompareResult;
class CATMathSetOfPoints ;
class CATMathSetOfVectors ;
class CATMathGridOfPoints ;
class CATMathGridOfVectors ;
class CATCrvParam ;
class CATParamData ;
class CATCrvLimits ;
class CATSurParam ;
class CATSurLimits ;
class CATKnotVector;
class CATMathPoint ;
class CATMathVector ;
class CATMathVector2D ;
class CATMathAxis ;
class CATMathSetOfPointsND;
class CATMathSetOfPointsNDTwoTangents;
class CATMathTransformation ;
class CATMathFunctionX ;
class CATMathFunctionXY ;
class CATSetOfPoints ;
class CATCurve ;
class CATSurface ;
class CATGeoFactory ;
class CATGeometry ;
class CATSubdivMesh;
class CATSubdivMeshGeo;
class CATMathTransformation2D ;
class CATTransfoManager;

class CATMathAdvancedBox;
#include "CATMathAdvancedBoxType.h"

#include "CATEvalCommand.h"
#include "CATGeometryUtilities.h"
#include "CATMathAdvancedBox_IsCacheRequest.h"
#include "CATMathInline.h"
class CATError;
 
//-----------------------------------------------------------------------------
class ExportedByCATCGMFusion CATGeometryCGM: public CATCGMObject
{
public:

  //-------------------------------------------------------------------------
  // Propagation des evenements:
  // Le IsModified est propage sur tous les abonnes.
  //-------------------------------------------------------------------------
  virtual void IsModified() ;
	virtual void IsTrimmed(CATBoolean NotifyModification = TRUE) ;
  //---------------------------------------------------------------------------
  //- Retreive the RootContainer/Factory from any object (default)
  //---------------------------------------------------------------------------
  virtual CATGeoFactory* GetFactory() const ;

  //---------------------------------------------------------------------------
  //- Applies a specified transformation to the object.
  //---------------------------------------------------------------------------
  virtual void ApplyTransformation (const CATMathTransformation &iTransfoToApply);


  // check en public pour etre appelable dans le cleaner 
  virtual CATError* CheckContinuity(const CATKnotVector & iKV, int iMinContinuity=2, const short iEvent=1);

  virtual void GetBoundingBox(CATMathBox &ioBox) const = 0; /* Not sure about this one */
  virtual int GetAdvancedBoundingBox(CATMathAdvancedBox &ioBox) const;
  virtual CATBoolean IsAdvancedBoundingBoxTypeAvailable(CATMathAdvancedBoxType iType) const;

 /**
  * @param iType
  *    Type of Box.
  * @param iRequest
  *    Type of Request.
  *   <dl>
  *    <dt>IsCacheAvailable</dt><dd>check if memory cache management is available</dd>
  *    <dt>IsCacheComputed</dt><dd>check if memory cache management is computed</dd>
  *   </dl>
  * @nodoc
  * @return TRUE if request of advanced bounding box cache management is available
  */
  virtual CATBoolean IsAdvancedBoundingBoxCache(const CATMathAdvancedBoxType            iType,
                                                const CATMathAdvancedBox_IsCacheRequest iRequest) const;

 /**
  * @param iGeometry
  *    Geometry to compare to this.
  * @param ioContext
  *    Comparison context e.g. options.
  * @param oResult
  *    Comparison result object.
  * @nodoc
  */
  virtual void CompareGeometry(const CATGeometryCGM * iGeometry,
                               CATCompareContext & ioContext,
                               CATCompareResult & oResult) const;

protected:


  //-------------------------------------------------------------------------
  // Tolerances pour les objets geometriques internes au container
  //-------------------------------------------------------------------------
  virtual double GetResolution(const CATResolutionType iResolutionType=CatC0) const ;
  virtual CATPositiveLength GetInfinite()   const;
  virtual CATPositiveLength GetModelSize() const ;
  
  //-------------------------------------------------------------------------
  // Set a geometric pointer to an entity.
  // This pointer may replace an existing one (if Previous != 0).
  // Use Which=NULL to remove an existing pointer.
  // SubscriptionRequest specifies whether IsModified method of this object
  // will be called whenever Which's one is called.
  //-------------------------------------------------------------------------
  enum CATSubscription { Subscribe, DoNotSubscribe } ;
  void SubscribeTo ( CATGeometry*    Which, 
	                   CATGeometry*    Previous            = NULL,
		                 const CATSubscription SubscriptionRequest = Subscribe ) ;

  //-----------------------------------------------------------------------------
  // Backward Link Management.
  // Notifies Owned that it has to considered himself as owned by Owner.
  // To remove notification, Owner must be NULL.
  //-----------------------------------------------------------------------------
  virtual void SetBackwardLink ( CATBaseUnknown* Owned, CATGeometryCGM* Owner );

  //-------------------------------------------------------------------------
  // Methodes generiques de controle de validite
  // Les methodes statiques n utilisent pas les tolerances du container.
  // ajout de largument iEvent (par defaut a true) pour permettre le release
  // de l'objet en cas de creation (ievent=False) si probleme
  //-------------------------------------------------------------------------
  CATError* CheckPoint(const CATMathPoint &iPointToBeChecked, const short iEvent = 1 ) ;
  CATError* CheckCurveLength(const CATPositiveLength &iCurveLength, const short iEvent = 1) ;

  static CATError* CheckAngles( const double Start, const double End, const short iEvent = 1 ) ;

  static void  CheckLimits( const CATCrvLimits & iLimits) ;
  INLINE void  CheckArcNumberBetween( const CATLONG32 iToBeChecked, 
				                      const int  iMin, 
				                      const int  iMax) const; 
  static void ThrowErrorOnArcNumber ( const int  iMin, 
				                      const int  iMax) ; 
  static CATLONG32 CheckEvalPointsCount( CATEvalCommand                  iCmd, 
				    CATMathSetOfPoints   * &oEvalPts,
				    CATMathSetOfVectors  * &oEvalFirstVecs, 
				    CATMathSetOfVectors  * &oEvalSecondVecs);
  
  static void  CheckEvalPointsCount( CATEvalCommand                  iCmd, 
				    CATMathGridOfPoints  * &oEvalPts,
				    CATMathGridOfVectors * &oEvalFirstVecs,
				    CATMathGridOfVectors * &oEvalSecondVecs,
				    CATLONG32 &oNbrParamU,
				    CATLONG32 &oNbrParamV) ;


  //-------------------------------------------------------------------------
  // Methodes high level de Stream pour les objets derives.
  //-------------------------------------------------------------------------
										
  void UnStreamData( CATCGMStream& Str, CATICGMObject* iDependency, CATCurve*       &oRefd, 
                     const CATSubscription iSubscriptionRequest = Subscribe, const char iLabelReserved[] = "") ;
  void UnStreamData( CATCGMStream& Str, CATICGMObject* iDependency, CATSurface*     &oRefd, 
                     const CATSubscription iSubscriptionRequest = Subscribe, const char iLabelReserved[] = "") ;
  void UnStreamData( CATCGMStream& Str, CATICGMObject* iDependency, CATSetOfPoints* &oRefd, 
                     const CATSubscription iSubscriptionRequest = Subscribe, const char iLabelReserved[] = "") ;

#if defined CATIAV5R19 || defined CATIAR206 
  //RNO For CATSubdivCellSurface Stream
  void UnStreamData(CATCGMStream    & Str, CATICGMObject* iDependency, CATSubdivMesh* & oRefd, 
                                  const CATSubscription   iSubscriptionRequested= Subscribe,
                                  const char iLabelReserved[] = "" ); 

  void UnStreamData(CATCGMStream& iStr, CATICGMObject* iDependency, CATSubdivMeshGeo*& oMeshGeo,
                    const CATSubscription iSubscriptionRequested = Subscribe,
                    const char iLabelReserved[] = "" );
#endif

  //-------------------------------------------------------------------------
  // Object Management
  //-------------------------------------------------------------------------
  CATGeometryCGM() ;

  //---------------------------------------------------------------------------
  // Object Modeler declaration pour pouvoir faire des IsAKindOf
  //---------------------------------------------------------------------------
  CATCGMDeclareVirtualClass;

  //-------------------------------------------------------------------------
  // Pour Gain memoire (trois bits disponibles sur les Classes Feuilles)
  //-------------------------------------------------------------------------
  INLINE CATBoolean GetCGMViciousONE() const;
  INLINE void SetCGMViciousONE(CATBoolean iValue);

  INLINE CATBoolean GetCGMViciousTWO() const;
  INLINE void SetCGMViciousTWO(CATBoolean iValue);

  INLINE CATBoolean GetCGMViciousTHREE() const;
  INLINE void SetCGMViciousTHREE(CATBoolean iValue);

public:
  //-------------------------------------------------------------------------
  // Gestion des pointages retours.
  // Implementation par defaut a surcharger pour les objets ayant un support.
  //-------------------------------------------------------------------------
  void AddRetainingEquationObject() ;

  //-------------------------------------------------------------------------
  // Remove a Subscriber from this.
  //-------------------------------------------------------------------------
  void RemoveRetainingEquationObject() ;
  
  //-------------------------------------------------------------------------
  // first Subscriber to Equation  Chain
  //-------------------------------------------------------------------------

  CATGeometryCGM* GetFirstRetainingEquationObject(CATGeometryCGM* iObject) const ;

  //-------------------------------------------------------------------------
  // Subscriber to Equation  Chain
  //-------------------------------------------------------------------------

  virtual CATGeometryCGM* NextRetainingEquationObject () const ;
  virtual CATGeometryCGM* PreviousRetainingEquationObject () const ; 

protected :

  virtual void NextRetainingEquationObject (CATGeometryCGM* PObject) ;
  virtual void PreviousRetainingEquationObject (CATGeometryCGM* PObject) ; 

private:

  //-------------------------------------------------------------------------
  // Declare to this a new Subscriber.
  // PreviousSubscriber and NextSubscriber methods must be provided 
  // by the Subscriber.
  //-------------------------------------------------------------------------
  void AddSubscriber(CATGeometryCGM* Subscriber) ;

  //-------------------------------------------------------------------------
  // Remove a Subscriber from this.
  //-------------------------------------------------------------------------
  void RemoveSubscriber(CATGeometryCGM* Subscriber) ;

  //-------------------------------------------------------------------------
  // Gestion des pointages retours.
  // Implementation par defaut a surcharger pour les objets ayant un support.
  //-------------------------------------------------------------------------
  virtual CATGeometryCGM* NextSubscriber () const ;
  virtual CATGeometryCGM* PreviousSubscriber () const ; 
  virtual void NextSubscriber (CATGeometryCGM*) ;
  virtual void PreviousSubscriber (CATGeometryCGM* PObject) ; 

  //-------------------------------------------------------------------------
  // Data
  //-------------------------------------------------------------------------
  INLINE CATGeometryCGM *GetFirstSubscriber() const;
  INLINE void SetFirstSubscriber(CATGeometryCGM *value);

  CATULONGPTR   _ViciousSubscrBits;

};

//-------------------------------------------------------------------------
// Acces a un element de liste doublement chaine des Subscriber
//-------------------------------------------------------------------------

INLINE CATGeometryCGM *CATGeometryCGM::GetFirstSubscriber() const
{
  CATGeometryCGM *value = (CATGeometryCGM *) (_ViciousSubscrBits & CATCGMViciousPerfHighPtr);
  return  value;
}

INLINE void CATGeometryCGM::SetFirstSubscriber(CATGeometryCGM *value)
{
  _ViciousSubscrBits = (((CATULONGPTR)value) & CATCGMViciousPerfHighPtr) | (_ViciousSubscrBits & CATCGMViciousPerfLow3Bits);
}

//-------------------------------------------------------------------------
// Acces vicieux (reserve aux inities) a trois bits disponibles
//-------------------------------------------------------------------------

INLINE CATBoolean CATGeometryCGM::GetCGMViciousONE() const
{
  return (_ViciousSubscrBits & 0x01) ? TRUE : FALSE;
}

INLINE void CATGeometryCGM::SetCGMViciousONE(CATBoolean iValue)
{
  if ( iValue == TRUE )
    _ViciousSubscrBits = _ViciousSubscrBits | ((CATULONGPTR) 0x01 );
  else
    _ViciousSubscrBits = _ViciousSubscrBits & (~ (CATULONGPTR) 0x01 );
}


INLINE CATBoolean CATGeometryCGM::GetCGMViciousTWO() const
{
  return (_ViciousSubscrBits & 0x02) ? TRUE : FALSE;
}

INLINE void CATGeometryCGM::SetCGMViciousTWO(CATBoolean iValue)
{
  if ( iValue == TRUE )
    _ViciousSubscrBits = _ViciousSubscrBits | ((CATULONGPTR) 0x02 );
  else
    _ViciousSubscrBits = _ViciousSubscrBits & (~ (CATULONGPTR) 0x02 );
}


INLINE CATBoolean CATGeometryCGM::GetCGMViciousTHREE() const
{
  return (_ViciousSubscrBits & 0x04) ? TRUE : FALSE;
}

INLINE void CATGeometryCGM::SetCGMViciousTHREE(CATBoolean iValue)
{
  if ( iValue == TRUE )
    _ViciousSubscrBits = _ViciousSubscrBits | ((CATULONGPTR) 0x04 );
  else
    _ViciousSubscrBits = _ViciousSubscrBits & (~ (CATULONGPTR) 0x04 );
}

INLINE void CATGeometryCGM::CheckArcNumberBetween( const CATLONG32 iToBeChecked, 
					                               const int  Min, 
					                               const int  Max) const
//-----------------------------------------------------------------------------
{
  if ( iToBeChecked < Min || iToBeChecked > Max )
    ThrowErrorOnArcNumber ( Min , Max );
}

#endif








