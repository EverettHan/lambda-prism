// COPYRIGHT Dassault Systemes 2001
//=============================================================================
//
// CATCGMExtV4Geometry.h
// Header definition of CATCGMExtV4Geometry
//
//=============================================================================
//
// Usage notes: Default extension for CATGeometry Classes 
//               BUT Methods are not implemented
// CATGeometryV4 inherits from this class
//
//=============================================================================
//
// Mar. 01 Creation: Code generated by the CAA wizard                     HCN
// Jan. 05 Suppression CATIAV5R13 et CATIAV5R14                           HCN
//=============================================================================
#ifndef CATCGMExtV4Geometry_H
#define CATCGMExtV4Geometry_H

#include "YP00IMPL.h"
#include "CATCGMExtensionV4.h"
#include "CATCGMNewArray.h"

#include "CATBezierCurve.h"
#include "CATBezierSurface.h"
#include "CATBSplineCurve.h" //+
#include "CATBSplineSurface.h" //+
#include "CATCartesianPoint.h"
#include "CATCircle.h"
#include "CATCloudOfPoints.h"
#include "CATCone.h"
#include "CATConic.h"
#include "CATCurve.h" //+
#include "CATCylinder.h"
#include "CATElementarySurface.h"
#include "CATEllipse.h"
#include "CATHyperbola.h"
#include "CATLine.h"
#include "CATNurbsCurve.h"
#include "CATNurbsSurface.h"
#include "CATOrientable.h"
#include "CATParabola.h"
#include "CATPCurve.h"
#include "CATPlane.h"
#include "CATPoint.h"
#include "CATPointOnCurve.h"
#include "CATPointOnSurface.h"
#include "CATRevolutionSurface.h"
#include "CATSphere.h"
#include "CATSurface.h" //+
#include "CATTabulatedCylinder.h"
#include "CATTorus.h"
#include "CATParameterizationOption.h"

//#include "CATGeoFactory.h"
//#include "CATIGeomContainer.h"

//-----------------------------------------------------------------------

/**
 * Describe your class here.
 * <p>
 * Using this prefered syntax will enable mkdoc to document your class.
 */

/*

  La classe CATCGMExtV4Geometry implemente toutes les methodes des interfaces suivantes :

					CATBezierCurve
					CATCartesianPoint
					CATCircle
					CATCloudOfPoints
					CATEllipse
					CATHyperbola
					CATLine
					CATNurbsCurve
					CATOrientable
					CATParabola
					CATPCurve
					CATPointOnCurve
					CATBezierSurface
					CATCone
					CATCylinder
					CATElementarySurface
					CATNurbsSurface
					CATRevolutionSurface
					CATSphere
					CATTabulatedCylinder
					CATTorus
					CATPointOnSurface
					CATPlane

  Les methodes mises en commemtaires sont les methodes conflictuelles :

	- les methodes avec la meme signature
	- les methodes avec une signature qui ne differe que par le type de la valeur de retour.
		(precede du commentaire "Supprime car ne differe que par le type de retour").
*/

class ExportedByYP00IMPL CATCGMExtV4Geometry: public CATCGMExtensionV4
{
  CATDeclareClass;

  public:

  // Standard constructors and destructors
  // -------------------------------------
	CATCGMExtV4Geometry();
	virtual ~CATCGMExtV4Geometry();

// -- adhesion a l'interface CATBezierCurve ------------------------------

	virtual CATLONG32 GetDegreeOfOneArc(CATLONG32 ArcIndex) const;

	virtual void ModifyControlPoints(	CATLONG32 iNbrOfArcs,
										CATMathSetOfLongs *iArcsDegree,
										CATMathSetOfPoints *iCtrlPts) const;

// -- adhesion a l'interface CATBezierSurface ----------------------------
// no method

// -- adhesion a l'interface CATBSplineCurve -----------------------------

	virtual CATLONG32 GetNumberOfControlPoints()const;

	//virtual CATMathPoint GetOneControlPoint(CATLONG32 number)const;

	virtual CATMathSetOfPoints *GetControlPoints()const;

	virtual CATLONG32 GetDegree()const;
  
	//virtual void SetOneControlPoint(CATLONG32 number, const CATMathPoint & controlpointm);

// -- adhesion a l'interface CATBSplineSurface ---------------------------

	virtual void GetNumberOfControlPoints(	CATLONG32 & oNbrCtrlPtsU,
											CATLONG32 & oNbrCtrlPtsV) const;
	
	/*virtual CATMathPoint GetOneControlPoint(CATLONG32 iPointIndexU,
											CATLONG32 iPointIndexV) const;*/
	
	virtual void GetDegree(	CATLONG32 & oDegreeU,
							CATLONG32 & oDegreeV) const;

// -- adhesion a l'interface CATCartesianPoint ---------------------------

	virtual void SetCoord(	double iFirstCoord,
							double iSecondCoord,
							double iThirdCoord);

	virtual void SetX(double iFirstCoord);

	virtual void SetY(double iSecondCoord);

	virtual void SetZ(double iThirdCoord);


// -- adhesion a l'interface CATCircle -----------------------------------

	virtual double GetRadius() const;

	virtual CATAngle GetStartAngle() const;

	virtual CATAngle GetEndAngle() const;

	virtual void Set(	const double   iRadius, 
						const CATMathPlane      & iSupport,
						const CATAngle            iStart,
						const CATAngle            iEnd); 

	virtual void SetRadius(double iNewRadius);


// -- adhesion a l'interface CATCloudOfPoints ----------------------------

	virtual CATLONG32 GetNumberOfPoints() const;

	virtual CATLONG32 GetNumberOfScans() const;
	
	virtual CATLONG32 GetNumberOfPointsOnScan(const CATLONG32 iScan) const;
	
	virtual CATPositiveLength GetOperatingDistance() const;

	virtual CATMathPoint GetPoint(const CATLONG32 iGlobIndex) const;
	
	virtual CATMathPoint GetPoint(const CATLONG32 iScan, const CATLONG32 iLocIndex) const;
	
	virtual const CATMathSetOfPointsND * GetScan(const CATLONG32 iScan) const;		    

	virtual CATBoolean HasNormalsDefined() const;

	virtual CATMathDirection GetNormal(const CATLONG32 iIndex) const;
	
	virtual CATMathDirection GetNormal(const CATLONG32 iScan, const CATLONG32 iLocIndex) const;
	
	virtual CATLONG32 IsPointActive(const CATLONG32 iGlobIndex) const;
	
	virtual CATLONG32 IsPointActive(const CATLONG32 iScan, const CATLONG32 iLocIndex) const;
	
	virtual CATLONG32 GetNumberOfActivePoints() const;
	
	virtual void GetActivePointsGlobIndices(CATLONG32 * oPointsGlobIndices) const;
	
	virtual void GetActivePointsLocIndices(CATLONG32 * oPointsScanAndLocIndices) const;
	
	virtual void GetActivePoints(CATMathSetOfPointsND & oSetOfPoints) const;		    
	
	virtual void SetOperatingDistance(const CATPositiveLength iNewOperatingDistance);
	
	virtual void SetPoint(const CATLONG32 iGlobIndex, const CATMathPoint & iNewCoord);
	
	virtual void SetPoint(	const CATLONG32 iScan,
							const CATLONG32 iLocIndex,
							const CATMathPoint & iNewCoord);
	
	virtual void SetNormal(const CATLONG32 iGlobIndex, const CATMathDirection & iNewVector);
	
	virtual void SetNormal(	const CATLONG32 iScan,
							const CATLONG32 iLocIndex,
							const CATMathDirection & iNewVector);
	
	virtual void SetPointActivity(const CATLONG32 iGlobIndex, const int iActivity);
	
	virtual void SetPointActivity(	const CATLONG32 iScan,
									const CATLONG32 iLocIndex,
									const int iActivity);

	virtual void SetPointActivity(	const CATLONG32 * iGlobIndices,
									const CATLONG32 iCount,
									const int iActivity); 

	virtual void SetAllPointsToActive();
	
	virtual void InsertAt(	const CATLONG32 iGlobIndex, 
							const CATMathPoint & iNewPoint, 
							const CATMathDirection & iNewVector);
	
	virtual void InsertAt(	const CATLONG32 iScan,
							const CATLONG32 iLocIndex, 
							const CATMathPoint & iNewPoint, 
							const CATMathDirection & iNewVector);
	
	virtual void RemovePosition(const CATLONG32 iGlobIndex);
	
	virtual void RemovePosition(const CATLONG32 iScan, const CATLONG32 iLocIndex);
	
	virtual void InsertScanAt(	const CATLONG32 iScan, 
								CATMathSetOfPointsND * iSetOfPoints);

	virtual void RemoveScan(const CATLONG32 iScan);

	virtual void Locate(CATMathPoint & iRefPoint,
						const CATPositiveLength iMaxDistance,
						CATLONG32 & oGlobIndex) const;
	
	virtual void Locate(CATMathPoint & iRefPoint,
						const CATPositiveLength iMaxDistance,
						CATLONG32 & oScan,
						CATLONG32 & oLocIndex) const;
	
	virtual void Set(	CATLISTP(CATMathSetOfPointsND) & iSetOfPoints,
						const CATPositiveLength iOperatingDistance);

// -- adhesion a l'interface CATCone ------------------------------------

	virtual CATAngle    GetConeAngle() const;
	
	virtual double   GetStartRadius() const;

	//virtual CATAngle    GetStartAngle() const;
	
	//virtual CATAngle    GetEndAngle() const;
	
	virtual double   GetStartRuleLength() const;
	
	virtual double   GetEndRuleLength() const;
	
	virtual double      GetUScale() const;
	
	virtual void        SetUScale(const double iNewUScale);
	
	virtual double      GetVScale() const;
	
	virtual void        SetVScale(const double iNewVScale);
	
	virtual double      GetVShift() const;
	
	virtual void        SetVShift(const double iNewVScale);
	
	virtual CATAngle          GetSemiAngle()   const;
	
	virtual void GetApex(CATMathPoint & ioPoint)        const;
	
	virtual CATMathPoint      GetApex()        const;
	
	virtual  double  GetRadiusAtV(const double iVval)   const;

// -- adhesion a l'interface CATConic ------------------------------------

	virtual void GetSupport(CATMathPlane &ioSupport) const;
	
	virtual double GetEccentricity() const;
	
	//virtual CATMathPoint GetOrigin() const;
	
	//virtual void GetOrigin (CATMathPoint &ioCenter) const;
	
	//virtual void SetOrigin(const CATMathPoint & iNewCenter);
	
	// Supprime car ne differe que par le type de retour
	//virtual CATMathPlane GetAxis() const;

// -- adhesion a l'interface CATCurve ------------------------------------

	virtual void Eval(	const CATCrvParam       & iPoint,
						const CATCrvEvalCommand & iCommand,
						CATCrvEvalLocal         & ioResult) const;

	virtual void Eval(	const CATCrvLimits      & iDomainToEvaluate,
						const CATLONG32                iNbOfPoints,
						const CATCrvEvalCommand & iCommand,
						CATCrvEvalResult        & ioResult) const;

	virtual void Eval(	const CATCrvParam & iParam,
						const CATCrvEvalCommand & iCommand,
						CATMathPoint* iPoint,
						CATMathVector* iFirstDeriv,
						CATMathVector* iSecondDeriv,
						CATMathVector* iThirdDeriv) const;

	virtual void CreateParam(const double iGlobalParam, CATCrvParam & ioParam) const;

	virtual void CreateParam(const double iLocal, const CATLONG32 iArc, CATCrvParam & ioParam) const;

	// Supprime car ne differe que par le type de retour
	//virtual const CATCrvParamReference * GetParamReference() const;

	// Supprime car ne differe que par le type de retour
	// virtual CATLONG32 GetNumberOfComponent() const;

	virtual const CATKnotVector * GetKnotVector() const;

	virtual void GetLimits(CATCrvLimits & ioCurrentLimits) const;
	
	virtual void GetMaxLimits(CATCrvLimits & ioMaxLimits) const;
	
	virtual void GetInternalMaxLimits(const CATLONG32 iArc, CATCrvLimits & ioInternalMaxLimits) const;
	
	virtual void GetInternalLimits(const CATLONG32 iArc, CATCrvLimits & ioInternalMaxLimits) const;
	
	virtual void GetStartLimit(CATCrvParam & ioStartParam) const;
	
	virtual void GetEndLimit(CATCrvParam & ioEndParam) const;
	
	virtual void SetLimits(const CATCrvLimits & iLimits);
	
	virtual void Lock();
	
	virtual void Unlock();
	
	virtual void GetEquation(	const CATLONG32 iArc,
								const CATMathFunctionX * & oFx,
								const CATMathFunctionX * & oFy,
								const CATMathFunctionX * & oFz) const;
	
	virtual void GetGlobalEquation(	const CATMathFunctionX * & oFx,
									const CATMathFunctionX * & oFy,
									const CATMathFunctionX * & oFz) const;
	
	virtual CATBoolean IsClosed() const;

	virtual CATBoolean IsInvariant(	const CATMathTransformation & iTransfo,
									CATMathTransformation1D* oTransfo1D) const;

	virtual CATBoolean IsConfused(	const CATMathTransformation   & iTransfo,
									const CATCurve                * iTCurve,
									CATMathTransformation1D * oTransfo1D) const;

	virtual void GetInternalMaxBoundingBox(const CATLONG32 iArc, CATMathBox & ioBox) const;

	virtual void GetInternalBoundingBox(const CATLONG32 iArc, CATMathBox & ioBox) const;
	
	virtual void GetBox( const CATCrvLimits & iLimits, CATMathBox & ioBox ) const;
  virtual int GetAdvancedBox(const CATCrvLimits &iLimits, CATMathAdvancedBox &ioBox) const;
	
	virtual CATMathCurve* GetMathCurve() const;
	
	virtual CATBoolean HasMathCurve() const;
	
	virtual const CATCurve * GetGeometricRep(	CATCrvLimits & ioRepLimits,
												short & ioRepOrientation) const;

	virtual CATCurve::CATSolutionDiagnostic GetParam(	const CATMathPoint & iPoint,
														CATCrvParam  & ioParam) const;

	virtual CATCurve::CATSolutionDiagnostic GetParam(	const CATMathPoint & iPoint,
		          		       							CATCrvParam  & ioParam   ,
														const CATCrvLimits & iInside  ) const;

	virtual CATCurve::CATProjectionDiagnostic CreateProjection(	CATPlane* iOn, CATPCurve* & oProjection, 
																CATSetOfCrvParams* iIndexOnCurve,
																CATSetOfCrvParams* ioIndexOnPCurve) const;

	virtual CATBoolean IsContaining ( const CATCurve* iOther ) const;
	
	virtual CATGeometry* GetOwner ( ) const;
	
	virtual CATMathPoint EvalPoint(const CATCrvParam & iParam) const; 
	
	virtual CATMathVector EvalFirstDeriv(const CATCrvParam & iParam) const;
	
	virtual CATMathVector EvalSecondDeriv(const CATCrvParam & iParam) const;
	
	virtual CATMathVector EvalThirdDeriv(const CATCrvParam & iParam) const;
	
	virtual void Eval(	const CATCrvLimits & box,
						CATEvalCommand command,
						CATMathSetOfPoints *& point,
						CATMathSetOfVectors *& dw,
						CATMathSetOfVectors *& dw2) const;

	virtual CATCrvParam CreateParam(const double & iLocal, const CATLONG32 & iArc) const;
	
	virtual CATCrvParam CreateParam(const double & iGlobalParam) const;
	
	// Supprime car ne differe que par le type de retour
	//virtual CATCrvLimits GetLimits() const;
	
	// Supprime car ne differe que par le type de retour
	//virtual CATCrvLimits GetMaxLimits() const;
	
	virtual CATCrvLimits GetInternalMaxLimits(const CATLONG32 iArc) const;
	
	virtual CATCrvLimits GetInternalLimits(const CATLONG32 iArc) const;
	
	// Supprime car ne differe que par le type de retour
	//virtual CATCrvParam GetStartLimit() const;
	
	// Supprime car ne differe que par le type de retour
	//virtual CATCrvParam GetEndLimit() const;
		
	virtual CATMathBox GetInternalMaxBoundingBox(const CATLONG32 iArc) const;
	
	virtual CATMathBox GetInternalBoundingBox(const CATLONG32 iArc) const;
	
	virtual void OpenEquation () const;
	
	virtual void CloseEquation () const;
	
	virtual double GetNaturalParamFromParam(const CATCrvParam &iParam) const;
	
	virtual void GetParamFromNaturalParam(double iNatural, CATCrvParam &oParam) const;

// -- adhesion a l'interface CATCylinder ---------------------------------

	//virtual double GetRadius() const;

	virtual double GetStartLength() const;
	
	virtual double GetEndLength() const;
	
	//virtual CATAngle GetStartAngle() const;
	
	//virtual CATAngle GetEndAngle() const;
	
	//virtual void SetRadius(double iRadius);
	
	virtual void SetLength(double iStartLength, double iEndLength);
	
	virtual void SetAngle(CATAngle iStartAngle, CATAngle iEndAngle);


// -- adhesion a l'interface CATElementarySurface ------------------------

	// Supprime car ne differe que par le type de retour
	// virtual CATMathAxis GetAxis() const;

	virtual void GetAxis(CATMathAxis &ioMathAxis) const;
	
	virtual void GetAxis(	CATMathPoint  &ioOrigin  ,
							CATMathVector &ioFirstDirection,
							CATMathVector &ioSecondDirection,
							CATMathVector &ioThirdDirection) const;

	virtual void SetOrigin(const CATMathPoint & ioNewOrigin);


// -- adhesion a l'interface CATEllipse ----------------------------------

	virtual double GetMajorAxis() const;
	
	virtual double GetMinorAxis() const;
	
	virtual void SetMajorAxis(double iNewMajorAxis);
	
	virtual void SetMinorAxis(double iNewMinorAxis);
	
	//virtual CATAngle GetStartAngle() const;
	
	//virtual CATAngle GetEndAngle() const;
	
	virtual void Set(	const double   iMajorAxis, 
						const double   iMinorAxis, 
						const CATMathPlane      & iSupport,
						const CATAngle            iStart,
						const CATAngle            iEnd); 


// -- adhesion a l'interface CATHyperbola --------------------------------

	//virtual CATPositiveLength GetMajorAxis() const;
	
	//virtual CATPositiveLength GetMinorAxis() const;
	
	//virtual void SetMajorAxis(CATPositiveLength iNewMajorAxis);
	
	//virtual void SetMinorAxis(CATPositiveLength iNewMinorAxis);


// -- adhesion a l'interface CATLine -------------------------------------

	virtual void GetOrigin(CATMathPoint &ioOrigin) const;
	
	virtual void GetDirection(CATMathDirection &ioDirection) const;
	
	virtual void Set(	const CATMathPoint & iSegmentLimit1,
						const CATMathPoint & iSegmentLimit2); 
	
	virtual void Set(	const CATMathPoint & iNewOrigin, 
						const CATMathDirection & iNewDirection);
	
	//virtual void SetOrigin(const CATMathPoint &iNewOrigin);
	

	// Ambigue avec  virtual void SetDirection(const CATMathDirection iNewDirection);
	//virtual void SetDirection(const CATMathDirection &iNewDirection);
	
	virtual CATMathPoint GetOrigin() const;
	
	virtual CATMathDirection GetDirection() const;


// -- adhesion a l'interface CATNurbsCurve -------------------------------

	virtual void GetOneControlPoint(CATLONG32 iNum, CATMathPoint &ioControlPoint) const;
	
	virtual void SetOneControlPoint(CATLONG32 iNum, const CATMathPoint & iNewCoord);
	
	virtual double GetOneWeight(CATLONG32 iNum) const;
	
	virtual void SetOneWeight(CATLONG32 iNum, double iNewWeight);
	
	virtual CATBoolean IsRational() const;
	
	virtual void Set(	const CATKnotVector &iNewKnotVector, 
						const CATLONG32 &iNewIsRational,
						const CATMathSetOfPoints &iNewVertices,
						const double * iNewWeights,
            const CATParameterizationOption iParameterizationOption );

  virtual void  SetData(const CATKnotVector &iNewKnotVector, 
			     const CATLONG32 &iNewIsRational,
			     const CATMathSetOfPoints &iNewVertices,
			     const double * iNewWeights,
                             const CATParameterizationOption iParameterizationOption );

	virtual void Extrapol(	const CATKnotVector &iNewKnotVector, 
							const CATLONG32 &iNewIsRational,
							const CATMathSetOfPoints &iNewVertices,
							const double * iNewWeights);
	
	virtual void GetOriginalParametrisationDATA(double &ioCoefficient, double &ioShift);
	
	virtual CATBoolean GetOriginalLimits(CATCrvLimits &ioOriginalLimits) const;
	
	virtual CATBoolean IsExtrapolated(CATCrvSide iSide) const;
	
	virtual void GetOriginalDegree(int &ioOriginalDegree) const;
	
	virtual CATMathPoint GetOneControlPoint(CATLONG32 iNum) const;
  

// -- adhesion a l interface CATNurbsSurface -----------------------------

	virtual void GetOneControlPoint(CATLONG32 iUNum,CATLONG32 iVNum, CATMathPoint & ioPoint) const;
	
	virtual CATMathPoint GetOneControlPoint(CATLONG32 iUNum,CATLONG32 iVNum) const;
	
	virtual void SetOneControlPoint(CATLONG32 iUNum,CATLONG32 iVNum, const CATMathPoint & iNewCoord);
	
	virtual double GetOneWeight(CATLONG32 iUNum,CATLONG32 iVNum) const;
	
	virtual void SetOneWeight(CATLONG32 iUNum,CATLONG32 iVNum, double iNewWeight);
	
	//virtual CATBoolean IsRational() const;
	
	virtual void Set(	const CATKnotVector &iNewUKnotVector, 
						const CATKnotVector &iNewVKnotVector,
						const CATLONG32 &iNewIsRational,
						const CATMathGridOfPoints &iNewVertices,
						const double * iNewWeights,
            const CATParameterizationOption iParameterizationOption );

  virtual void SetData( const CATKnotVector &iNewUKnotVector, 
			      const CATKnotVector &iNewVKnotVector,
			      const CATLONG32 &iNewIsRational,
			      const CATMathGridOfPoints &iNewVertices,
			      const double * iNewWeights,
                              const CATParameterizationOption iParameterizationOption );
	virtual void Extrapol(	const CATKnotVector &iNewUKnotVector, 
							const CATKnotVector &iNewVKnotVector,
							const CATLONG32 &iNewIsRational,
							const CATMathGridOfPoints &iNewVertices,
							const double * iNewWeights);
	
	virtual CATBoolean GetOriginalLimits(CATSurLimits &ioOriginalLimits) const;
	
	virtual CATBoolean IsExtrapolated(CATSurSide iSide) const;
	
	virtual void GetOriginalDegrees(int &ioOriginalDegreeU, int &ioOriginalDegreeV) const;
	
	virtual void GetOriginalParametrisationDATA(double &ioCoefficientU,
												double &ioShiftU,
												double &ioCoefficientV,
												double &ioShiftV);

	virtual void GetExtrapolationData(double *oAlpha,double *oBeta) const;
	
	virtual void SetExtrapolationData(	double *iAlpha,
										double *oBeta,
										CATLONG32 IsExtrapolatedU,
										CATLONG32 IsExtrapolatedV);


// -- adhesion a l'interface CATOrientable -------------------------------

	virtual void SetOrientation(CATLONG32 iOrientation);
	
	// Supprime car ne differe que par le type de retour
	// virtual CATLONG32 GetOrientation() const;
	
	virtual CATGeometry *GetSupport() const;


// -- adhesion a l'interface CATParabola ---------------------------------

	virtual CATLength GetFocalDistance() const;
	
	virtual CATMathPoint GetFocus() const;
	
	virtual void SetFocalDistance(CATLength iNewFocalDistance);

// -- adhesion a l'interface CATPCurve -----------------------------------
	
	virtual CATSurface *GetSurface() const;
	
	virtual void SetSurface(CATSurface* iNewSupport);
	
	virtual CATCurve::CATSolutionDiagnostic GetParamFromUV(	const CATSurParam  & iLocation,
															CATCrvParam  & ioIndex) const;
	virtual void EvalUV(const CATCrvParam & iParam,
						const CATCrvEvalCommand &iCommand,   
                        CATSurParam   *iPoint             ,
						CATMathVector2D *iFirstDeriv,          
						CATMathVector2D *iSecondDeriv,
						CATMathVector2D *iThirdDeriv) const;

	virtual void OpenEquationUV() const;
	
	virtual void CloseEquationUV() const;
	
	virtual void GetEquationUV(	const CATLONG32 iArc,
								const CATMathFunctionX *& oFx,
								const CATMathFunctionX *& oFy) const;
	
	virtual void GetGlobalEquationUV(	const CATMathFunctionX *& oFx,
										const CATMathFunctionX *& oFy) const;
	
	virtual CATCurve* Create3DCurve(CATGeoFactory* iWhere,
									CATSetOfCrvParams* iIndexOnPCurve,
									CATSetOfCrvParams* ioIndexOnCurve) const;
	
	virtual     void     GetBoundingBoxUV(CATSurLimits &ioUVBox) const;
	
	virtual    void       GetBoundingBoxUV(const CATCrvLimits & iSubset, CATSurLimits &ioUVBox) const;
	
	virtual     void     GetInternalBoundingBoxUV(const CATLONG32 iArc,  CATSurLimits &ioUVBox) const;
	
	virtual void GetInternalMaxBoundingBoxUV(	const CATLONG32 iArc,
												CATSurLimits & ioLimits) const;

	
	virtual double GetPrecisionUV(const CATCrvLimits &iLimits) const;
	
	virtual CATBoolean IsInvariantUV(	const CATMathTransformation2D & iTransfo2D,
										CATMathTransformation1D* oTransfo1D) const;
	
	virtual CATPCurve::CATCreationDiagnostic CreateEquivalentPCurve(CATMathTransformation2D *  iTransfo2D,
																	CATSurface 	         *  iNewSupport,
																	CATPCurve  	         * &oPCurve,
																	CATMathTransformation1D   &oTransfo1D);

	// Supprime car ne differe que par le type de retour
	// virtual CATCurve *GetCurve() const;
	
	virtual CATSurParam EvalPointUV(const CATCrvParam & iParam) const;
	
	virtual CATMathVector2D EvalFirstDerivUV(const CATCrvParam & iParam) const;
	
	virtual CATMathVector2D EvalSecondDerivUV(const CATCrvParam & iParam) const;
	
	virtual CATMathVector2D EvalThirdDerivUV(const CATCrvParam & iParam) const;
	
	virtual CATSurLimits GetBoundingBoxUV() const;
	
	virtual CATSurLimits GetBoundingBoxUV(const CATCrvLimits & iSubset) const;
	
	virtual CATSurLimits GetInternalBoundingBoxUV(const CATLONG32 iArc) const;


// -- adhesion a l'interface CATPlane ------------------------------------
	
	virtual void GetAxis(CATMathPlane &ioMathPlane) const;
	
	virtual void GetAxis(	CATMathPoint       &ioOrigin,
							CATMathDirection &ioFirstDirection ,
							CATMathDirection &ioSecondDirection) const;
	
	virtual void GetNormal(	CATMathPoint  &ioOrigin ,
							CATMathVector &ioNormal) const;
	
	virtual void SetAxis(const CATMathPlane &iPlaneToCopy);
	
	// Supprime car ne differe que par le type de retour
	//virtual CATMathPlane GetAxis() const;

// -- adhesion a l'interface CATPoint -----------------------------------

	virtual void GetCoord(	double & ioFisrtCoord,
							double & ioSecondCoord,
							double & ioThirdCoord ) const;

	virtual double GetX() const;

	virtual double GetY() const;

	virtual double GetZ() const;

	virtual  void GetMathPoint(CATMathPoint & ioPoint) const;

	virtual CATMathPoint GetMathPoint() const;

// -- adhesion a l'interface CATPointOnCurve -----------------------------

	
	virtual void GetParam(CATCrvParam & oParam) const;
	
	// Supprime car ne differe que par le type de retour
	// virtual CATCrvParam GetParam() const;
	
	virtual void SetParam(const CATCrvParam & iNewParam);
	
	//virtual CATCurve *GetCurve() const;
	
	virtual void SetCurve(CATCurve* iNewSupport);


// -- adhesion a l'interface CATPointOnSurface ---------------------------

	
	virtual void GetParam(CATSurParam & ioParam) const;
	
	// Supprime car ne differe que par le type de retour
	//virtual CATSurParam GetParam() const;
	
	virtual void SetParam(const CATSurParam & iNewParam);
	
	//virtual CATSurface* GetSurface() const;
	
	//virtual void SetSurface(CATSurface* iNewSupport);
	
	
// -- adhesion a l'interface CATRevolutionSurface ------------------------
	
	
	virtual CATCurve* GetProfile()  const;
	
	virtual CATCurve* GetProfile(CATCrvLimits & ioProfileLimits)  const;
	
	virtual void GetProfileLimits(CATCrvLimits & ioProfileLimits) const;
	virtual void GetLimitsOnProfile(const CATSurLimits &iSurLim,
	                                CATCrvLimits & ioProfileLimits ) const;
	//virtual void GetAxis(CATMathAxis &ioMathAxis) const;
	
	/*virtual void GetAxis(CATMathPoint  &ioOrigin  ,
		       CATMathVector &ioFirstDirection,
		       CATMathVector &ioSecondDirection,
		       CATMathVector &ioThirdDirection) const;*/
	
	virtual CATAngle GetStart()  const;
	
	virtual CATAngle GetEnd()  const;
	
	virtual void Set(CATCurve* iProfile,
                     const CATCrvLimits & iProfileLimits,
	                 const CATMathAxis &iRefAxis,
	                 const CATAngle &iStart,
	                 const CATAngle &iEnd);
	
	virtual void Extrapolation(const CATLONG32  &iOldNumberOfArcs, const CATLONG32 &iRelativOffset);
	
	virtual void SetProfile(CATCurve* iNewProfile);
	
	virtual void SetAxis(const CATMathAxis & iRefAxis);
	
	virtual void SetStart(const CATAngle iNewStartAngle);
	
	virtual void SetEnd(const CATAngle iNewEndAngle);

	virtual void SetMeanAngle(const CATAngle iNewMeanAngle);
	
  virtual void ScaleAngularParameter(double iScale);

	// virtual CATMathAxis GetAxis()  const;


// -- adhesion a l'interface CATSphere -----------------------------------

	//virtual double GetRadius() const;
	
	virtual CATAngle GetMeridianStartAngle() const;
	
	virtual CATAngle GetMeridianEndAngle() const;
	
	virtual CATAngle GetParallelStartAngle() const;
	
	virtual CATAngle GetParallelEndAngle() const;
	
	virtual void Set(	const CATMathAxis       &iAxis,
						const double  iRadius,
						const CATAngle           iMeridianStart,
						const CATAngle           iMeridianEnd, 
						const CATAngle           iParallelStart,
						const CATAngle           iParallelEnd); 
	
	//virtual void SetRadius(double iRadius);

// -- adhesion a l'interface CATSurface ----------------------------------

	virtual void GetBox(const CATSurLimits & iLimits, CATMathBox & ioBox) const;
  virtual int GetAdvancedBox(const CATSurLimits &iLimits, CATMathAdvancedBox &ioBox) const;

	virtual void EvalPoint(	const CATSurParam & iPosition,
							CATMathPoint & ioPoint )const;

	virtual void EvalFirstDeriv(const CATSurParam & iParam,
								CATMathVector     & ioDU,
								CATMathVector     & ioDV) const;

	virtual void EvalSecondDeriv(	const CATSurParam & iParam,
									CATMathVector     & ioDU2,
									CATMathVector     & ioDUDV,
									CATMathVector     & ioDV2) const;
	
	virtual void EvalThirdDeriv(	const CATSurParam & iParam,
									CATMathVector     & ioDU3,
									CATMathVector     & ioDU2DV,
									CATMathVector     & ioDUDV2,
									CATMathVector     & ioDV3) const;
	
	virtual void EvalNormal(const CATSurParam & iParam, CATMathDirection & ioNormal) const;
	
	virtual void EvalMultiple(	const CATSurLimits      & iBox,
								CATLONG32                      iNbOfPointsInU,
								CATLONG32                      iNbOfPointsInV,
								const CATSurEvalCommand & iCommand,
								CATSurEvalResult        & ioResult) const;
	
	virtual void EvalLocal(	const CATSurParam       & iPoint,
							const CATSurEvalCommand & iCommand,
							CATSurEvalLocal         & ioResult) const;
	
	virtual CATCurve *ExtractIsoParametricCurve(	const CATIsoParameter iIsoParameter,
													const CATSurParam & iParam,     
													CATGeoFactory *iWhere ) const;
	
	virtual CATBoolean IsClosedU() const;
	
	virtual CATBoolean IsClosedV() const;
	
	virtual void GetMappingU(CATMathTransformation1D &ioTransfo1D) const;
	
	virtual void GetMappingV(CATMathTransformation1D &ioTransfo1D) const;
	
	virtual short GetOrientation( ) const;
	
	virtual void SetOrientation( const short iNewOrientation );
	
	virtual CATBoolean IsInvariant(	const CATMathTransformation   & iTransfo,
									CATMathTransformation2D * ioTransfo2D) const;
	
	virtual CATBoolean IsConfused(	const CATMathTransformation   & iTransfo,
									const CATSurface              * iTSurface,
									CATMathTransformation2D * ioTransfo2D) const;
	
	virtual const CATKnotVector * GetKnotVectorU() const;
	
	virtual const CATKnotVector * GetKnotVectorV() const;
	
	virtual void CreateParam(	const double & iParamU,
								const double & iParamV,
								CATSurParam & ioResult) const;
	
	virtual void CreateParam(	const double & iParamU,
								const CATLONG32 & iPatchU,
								const double & iParamV,
								const CATLONG32 & iPatchV,
								CATSurParam & ioResult) const;

	// Supprime car ne differe que par le type de retour
	//virtual const CATSurParamReference * GetParamReference() const;
	
	virtual void GetStartLimit(CATSurParam & ioParam) const;
	
	virtual void GetEndLimit(CATSurParam & ioParam) const;
	
	virtual void GetLimits(CATSurLimits & ioLimits) const;
	
	virtual void GetMaxLimits(CATSurLimits & ioLimits) const;
	
	virtual void GetInternalLimits(	const CATLONG32 iPatchU, 
									const CATLONG32 iPatchV,
									CATSurLimits & ioLimits) const;
	
	virtual void GetInternalMaxLimits(	const CATLONG32 iPatchU, 
										const CATLONG32 iPatchV,
										CATSurLimits & oLimits) const;
	
	virtual void SetLimits(const CATSurLimits & iNewLimits);
	
	virtual void GetNumberOfComponent( CATLONG32 & oNbOfUPatches, CATLONG32 & oNbOfVPatches) const;
	
	//virtual void Lock();
	
	//virtual void Unlock();
	
	virtual void GetEquation(	const CATLONG32 iPatchU,
								const CATLONG32 iPatchV,
								const CATMathFunctionXY * & oFx,
								const CATMathFunctionXY * & oFy,
								const CATMathFunctionXY * & oFz) const;
	
	virtual void GetGlobalEquation(	const CATMathFunctionXY * & oFx,
									const CATMathFunctionXY * & oFy,
									const CATMathFunctionXY * & oFz) const;
	
	virtual CATMathFunctionRN *GetImplicitEquation () const;
	
	virtual CATBoolean HasImplicitEquation() const;
	
	virtual CATMathCurve* GetMathCurve(	const CATIsoParameter   iIsoParameter,
										const CATSurParam     & iLocation ) const;

	virtual CATBoolean HasMathCurve(const CATIsoParameter   iIsoParameter,
									const CATSurParam     & iLocation ) const;
	
	virtual void GetInternalBoundingBox(const CATLONG32 iPatchU, 
										const CATLONG32 iPatchV,
										CATMathBox & ioBox) const;
	
	virtual void GetInternalMaxBoundingBox(	const CATLONG32 iPatchU, 
											const CATLONG32 iPatchV,
											CATMathBox & ioBox) const;
	
	virtual void GetDirBox( CATMathDirBox & oDirBox ) const;
	
	virtual void GetInternalDirBox(const CATLONG32 iPatchU, const CATLONG32 iPatchV, CATMathDirBox &oDirBox) const;
	
	virtual CATSurface::CATSolutionDiagnostic GetParam(	const CATMathPoint & iPoint,
														CATSurParam  & oIndex ) const;
	
	virtual CATSurface::CATSolutionDiagnostic GetParam(	const CATMathPoint & iPoint,
						                                CATSurParam  & ioIndex   ,
														const CATSurLimits & iInside  ) const;
	
	virtual CATSurface::CATSolutionDiagnostic GetParamOnIsopar( const CATMathPoint    & iPoint,
																const CATIsoParameter & iIsoparam,
																const CATSurParam     & iStart,
																const CATSurParam     & iEnd,
                                                                double          & ioLambdaOnIsopar) const;
	
	virtual CATBoolean Compare( const CATSurParam &iW1, const CATSurParam & iW2 ) const;
	
	virtual CATIsoParameter IsLinear() const;
	
	virtual CATIsoParameter IsCircular() const;
	
	virtual const CATSurface * GetGeometricRep() const;
	
	virtual CATSurface * CreateOffset(	CATGeoFactory * iWhere, 
		                                const CATLength & iOffset,
										const CATSurLimits &iLimits,
										CATMathTransformation2D * &oTransfo2D) const;

	virtual void Eval(	const CATSurLimits & iBoxToEvaluate,
						CATEvalCommand iCommand,
						CATMathGridOfPoints  * iPointm,
						CATMathGridOfVectors * iVectord1,
						CATMathGridOfVectors * iVectord2) const;

	virtual CATMathDirection EvalNormal(const CATSurParam & iParam) const;
	
	virtual CATMathPoint EvalPoint(const CATSurParam & iParam) const;
	
	virtual CATSurParam CreateParam(const double & iUParam,
									const double & iVParam) const;

	virtual CATSurParam CreateParam(const double & iUParam, const CATLONG32 & iUNum,
									const double & iVParam, const CATLONG32 & iVNum) const;

	// Supprime car ne differe que par le type de retour
	//virtual CATSurLimits GetLimits() const;

	// Supprime car ne differe que par le type de retour
	//virtual CATSurParam GetEndLimit() const;

	// Supprime car ne differe que par le type de retour
	//virtual CATSurParam GetStartLimit() const;
	
	virtual CATSurLimits GetInternalLimits(const CATLONG32 iIndexU, const CATLONG32 iIndexV) const;

	// Supprime car ne differe que par le type de retour
	//virtual CATSurLimits GetMaxLimits() const;
	
	virtual CATSurLimits GetInternalMaxLimits(const CATLONG32 iIndexU, const CATLONG32 iIndexV) const;
	
	virtual CATMathBox GetInternalBoundingBox(	const CATLONG32 iUNum,
												const CATLONG32 iVNum) const;
	
	virtual CATMathBox GetInternalMaxBoundingBox(	const CATLONG32 iUNum,
													const CATLONG32 iVNum) const;

	// Supprime car ne differe que par le type de retour
	//virtual CATMathSetOfLongs *GetNumberOfComponent() const;
	
	//virtual void OpenEquation () const;
	
	//virtual void CloseEquation () const;


// -- adhesion a l'interface CATTabulatedCylinder ------------------------

	
	//virtual CATCurve* GetProfile()  const;
	
	//virtual void GetProfileLimits(CATCrvLimits & ioProfileLimits) const;
	
	//virtual void GetDirection(CATMathDirection & ioDirection)  const;
	
	//virtual double GetStart()  const;
	
	//virtual double GetEnd()  const;
	
	virtual void Set(	CATCurve*               iProfile,
						const CATCrvLimits     &iProfileLimits,
						const CATMathDirection &iDirection,
						const double         iStart,
						const double         iEnd); 
	
	//virtual void Extrapolation(const CATLONG32  &iOldNumberOfArcs, const CATLONG32 &iRelativOffset);
	
	//virtual void SetProfile(CATCurve* iNewProfile);
	
	// Ambigue avec virtual void SetDirection(const CATMathDirection &iNewDirection);
	// virtual void SetDirection(const CATMathDirection iNewDirection);
	
	//virtual void SetStart(const double iNewStart);
	
	//virtual void SetEnd(const double iNewEnd);
	
	//virtual CATMathDirection GetDirection()  const;


// -- adhesion a l'interface CATTorus ------------------------------------

	virtual double GetMajorRadius() const;
	
	virtual CATAngle GetMajorStartAngle() const;
	
	virtual CATAngle GetMajorEndAngle() const;
	
	virtual double GetMinorRadius() const;
	
	virtual CATAngle GetMinorStartAngle() const;
	
	virtual CATAngle GetMinorEndAngle() const;
	
	virtual  void SetMinMinorAngle(const double iNewMin);
	
	virtual  void SetMaxMinorAngle(const double iNewMin);
	
	//virtual double GetUScale() const;
	
	//virtual void SetUScale(const double iNewScale);
	
	//virtual double GetVScale() const;
	
	//virtual void SetVScale(const double iNewScale);
	
	virtual double GetPhiShift() const;
	
	virtual void SetPhiShift(const CATLONG32 iNewCycles);
	
	virtual CATBoolean  IsAppleType() const;

};

//-----------------------------------------------------------------------

#endif
