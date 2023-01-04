// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// Base class designed to handle mapping between parametrization of
// two Curves of an EdgeCurve
// For this class, only one curve and its limits on the EdgeCurve are stored
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Mar. 99 Creation                                                   E. Guerin
// Mar. 04 Stream/UnStreamCompact(...),
//         Stream/UnStreamCompactLossAllowed(...)                         HCN
// May. 04 GetStreamSortingKey(...),
//         HasCommonStreamData(...),
//         CopyCommonStreamData(...)                                      HCN
// 05/06/08 NLD Ajout ForceMaxGap()
// Jul. 09 Suppression du StreamCompact                                   VUC
// Aug. 11 Modified the type enum (which was also in CATAdjustedMapX.h),
//         and added IsAdjustedMapXType() (for comparing geometries).     R1Y
//=============================================================================
#ifndef CATMapX_H
#define CATMapX_H

#include "YP00IMPL.h"                    
#include "CATMathDef.h"
#include "CATCGMStreamVersion.h"
#include "CATCGMNewArray.h"
#include "CATCGMVirtual.h"
#include "CATBoolean.h"

class CATCurve;
class CATCrvParam;
class CATCrvLimits;
class CATCGMStream;
class CATCloneManager;
class CATMathFunctionX;
class CATMathTransformation1D;
class CATMapMathunctionX;
class CATCGMOutput;
class CATEdgeCurve;

//-----------------------------------------------------------------------------
//
class ExportedByYP00IMPL CATMapX : public CATCGMVirtual
{
public:
   /** @nodoc */
  CATCGMNewClassArrayDeclare;

  //-------------------------------------------------------------------------
  // Constructors
  //-------------------------------------------------------------------------
	CATMapX(const CATCurve* iRefCurve);
  CATMapX(const CATCurve* iRefCurve, const CATEdgeCurve* iEdgeCurve);
  CATMapX(const CATMapX* iMapX);

  //-------------------------------------------------------------------------
  // virtual Destructor
  //-------------------------------------------------------------------------
  virtual ~CATMapX();
  
  //-------------------------------------------------------------------------
  // sets and gets the limits of the EdgeCurve on each Curve
  //-------------------------------------------------------------------------
  virtual void SetLimits(const CATCurve* iCurve,
                         const CATCrvLimits & iLimits);
  virtual void GetLimits(const CATCurve* iCurve,
                         CATCrvLimits & oLimits)const;
  virtual void GetLimits(const CATCurve* iCurve,
                         CATCrvParam & oLow, CATCrvParam & oHigh)const;
  virtual void GetMappingLimits(const CATCurve* iCurve,
                                double &        oLow,
                                double &        oHigh)const;

  //-------------------------------------------------------------------------
  // Creates CATMathFunctionX* which transforms a parameter expressed on
  // one curve to the parameter expressed on the other.
  // * If iRefCurveFist==1 (default), the function maps from RefCurve to Curve.
  // Otherwise, the function maps from Curve to RefCurve
	// * If iAdjustedC2=1, the returned function is adjusted to have a one-to-one mapping
	// and returns a C2 function.
  // The returned function must be deleted by the caller.
	//*iDomain contains the limits from RefCurve and Curve if iRefCurvefirst=1
	// on the contrary if iRefCurvefirst =!1
  //-------------------------------------------------------------------------
  virtual CATMathFunctionX* CreateFunctionX(short iRefCurveFirst=1, CATBoolean iAdjustedC2=0, const double * iDomain=0)const;

  //-------------------------------------------------------------------------
  // Gets the relative orientation between the two curves
  //-------------------------------------------------------------------------
  virtual short GetOrientation()const;

  //-------------------------------------------------------------------------
  // Retrieves the MaxGap.
  //-------------------------------------------------------------------------
  virtual double GetMaxGap()const;
  virtual double ComputeMaxGap();
  virtual void ForceMaxGap(double iMaxGap);

  //-------------------------------------------------------------------------
  // Gets the type of mapping
  //-------------------------------------------------------------------------
  enum Type {
    CATSingleMapXType,
    CATTrivialMapXType,
    CATIdentityMapXType,
    CATLinearMapXType,
    CATMathFunctionMapXType,
    CATSetOfPointsMapXType,
    CATProjectCrvSurMapXType,
    CATProjectInDirectionCrvSurMapXType
  };
  virtual short IsATypeOf(CATMapX::Type iType)const;
  virtual CATMapX::Type GetType()const;
  virtual CATBoolean IsAdjustedMapXType() const;

  //-------------------------------------------------------------------------
  // For Streaming
  //-------------------------------------------------------------------------
  virtual void Stream( CATCGMStream& Str ) ;
  virtual void UnStream( CATCGMStream& Str ) ;

  virtual int  GetStreamSortingKey(CATCGMStream& Str);
  virtual int  HasCommonStreamData(const CATMapX* ipMapXToCompare, CATCGMStream& Str);
  virtual void CopyCommonStreamData(const CATMapX* ipMapXToCompare, int iSimilarityLevel, CATCGMStream& Str);
  
  virtual CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

  static void Stream( CATCGMStream& Str, CATMapX *iMapX, const char iLabelReserved[] = ""  );
  static void UnStream( const CATCurve* iRefCurve, const CATCurve* iCurve, CATCGMStream& Str, CATMapX *&iMapX, const char iLabelReserved[] = ""  );

  //-------------------------------------------------------------------------
  // Returns the the mapped oEquivalentParam of a iCurrentParam expressed on iCurrentCurve.
  ///     GetEquivalentParam / GetApproximateEquivalentParam 
  //-------------------------------------------------------------------------

  virtual void GetEquivalentParam(const CATCurve *    iCurrentCurve, 
                                  const CATCrvParam & iCurrentParam,
                                  CATCrvParam &       oEquivalentParam,
                                  short               iReconvergence=1)const;

  virtual void GetApproximateEquivalentParam(const CATCurve          *  iCurrentCurve, 
                                             const CATCrvParam       &  iCurrentParam,
                                             const CATPositiveLength &  iApproximateResolution,
                                             CATCrvParam             &  oEquivalentParam ) const;



	

  //-------------------------------------------------------------------------
  // Gets a pointer toward each Curve of the mapping
  //-------------------------------------------------------------------------
	const CATEdgeCurve* GetEdgeCurve() const;
	void SetEdgeCurve(CATEdgeCurve* iEdgeCurve) ;
  const CATCurve* GetRefCurve()const;
  virtual const CATCurve* GetCurve()const;
  virtual const CATCurve* OtherCurve(const CATCurve* iCurve)const;

  //-------------------------------------------------------------------------
  // Change one of the Curves. If a CATMathTransformation1D is supplied,
  // the limits and mapping are changed using this Transfo. The returned
  // value is (this)
  // Eventually, if the operation can't be done without changing the type
  // of MapX, a new MapX is created and is pointed by the returned value.
  // The caller has to destroy the old mapping if necessary.
  //-------------------------------------------------------------------------
  virtual CATMapX* SetCurve(const CATCurve* iOldCurve, const CATCurve* iNewCurve,
                            const CATMathTransformation1D* iTransfo=0);

  //-------------------------------------------------------------------------
  // Change the RefCurve AND/OR the Curve if the corresponding pointers
  // are not NULL. It doesn't affect the limits or the mapping
  //-------------------------------------------------------------------------
  virtual void SetCurves(const CATCurve* iRefCurve,const CATCurve* iCurve);

  //-------------------------------------------------------------------------
  // Exchange the RefCurve with the Curve, and adapt mapping
  //-------------------------------------------------------------------------
  virtual void Invert();

  //-------------------------------------------------------------------------
  // Returns a fully duplicated object. The original can be destroyed.
  // The Curves are not cloned.
  //-------------------------------------------------------------------------
  virtual CATMapX* Duplicate()const;

  //-------------------------------------------------------------------------
  // Returns a fully duplicated object. The original can be destroyed.
  // The curves are cloned using the CATCloneManager
  //-------------------------------------------------------------------------
  virtual CATMapX* Clone(CATCloneManager& iCloneManager)const;  

  //-------------------------------------------------------------------------
  // Returns a new MapX, composition of this MapX and iMapX.
  // The new RefCurve is the curve of THIS MapX which is not in iMapX.
  // The new Curve is the curve of iMapX which is not in THIS.
  // THIS and iMapX can be destroyed afterwards, if necessary.
  //-------------------------------------------------------------------------
  virtual CATMapX* CreateComposition(const CATMapX* iMapX)const;

  //-------------------------------------------------------------------------
  // Says wether or not iCurve is in the M apping.
  // Returned value is 1 if iCurve is the RefCurve.
  // Returned value is 2 if iCurve is the Curve.
  //-------------------------------------------------------------------------
  virtual short IsContaining(const CATCurve* iCurve)const;

  //-------------------------------------------------------------------------
  // If possible, creates a new MapX which is simpler than the current one
  // For example, if a CATLinearMapX's (scale,offset) is (1,0), the returned
  // MapX is a new CATIdentityMapX.
  // If no simplification could be made, the returned value is THIS.
  //-------------------------------------------------------------------------
  virtual CATMapX* Simplify()const;


  //-------------------------------------------------------------------------
  // Unextrapolation: adjust limits, destroy useless data
  // The input limits are relative to the RefCurve
  // If Mode == 1, perform a check only- return value: 0 = ok, -1 = error
  //-------------------------------------------------------------------------
  virtual CATLONG32 Unextrapolate(const CATCrvLimits & NewLimits, double tol2, CATLONG32 Mode = 0);

  //-------------------------------------------------------------------------
  // Internal use.
  //-------------------------------------------------------------------------
  virtual void Dump(CATCGMOutput& os)const;
  virtual void AdjustLimits();
  //-------------------------------------------------------------------------
  // Data
  //-------------------------------------------------------------------------
  friend class CATMapMathFunctionX;



protected:
  virtual void Compose(const CATMapX* iMapX, const CATCurve* iCurve);

  virtual double GetEquivalentDouble(const CATCurve* iCurrentCurve,
                                     const double    iCurrentParam,
                                     short           iReconvergence=1)const;

  virtual double GetApproximateEquivalentDouble(const CATCurve* iCurrentCurve, const double    iCurrentParam,
                                              const CATPositiveLength &  iApproximateResolution ) const;


	virtual void UpdateLimits();

  // XGN 03/08/01 : ces deux methodes stabilisent les numero d'arc
  // des parametres Start et End lorsqu'ils se trouvent a la frontiere entre 2 arcs.
  void GetExtremityParams(const CATCurve * iCurve,
                          double iGlobalLow, double iGlobalHigh,
                          CATCrvParam & oLowParam, CATCrvParam & oHighParam) const;
  void GetExtremityLimit(const CATCurve * iCurve,
                          double iGlobalLow, double iGlobalHigh,
                          CATCrvLimits & oLimits) const;

  // INTERNAL ONLY 
  virtual size_t  GetStaticMemoryBytes() const;   

  //======================================================================================
  //
  //  DATA
  //
  //======================================================================================
  protected:
  const CATCurve*      _RefCurve;
  const CATEdgeCurve * _EdgeCurve;
};

#endif
