/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATPConics Computation
//  Class for construction PConics (PEllipses, PHyperbola, PParabola, ...) 
//  with various specifications
//
//=============================================================================
// Usage notes:
//
//=============================================================================
//       99  Creation                                        P. Tonnerre
//  Jan. 00  Ajout des constructions (4pts+1tgt) et (5pts)   X. Gourdon
//  March 14 XSCALE passage en private des methodes internes
//           Suppresion du Getdefault tolerance
//           rem : le sketcher appelle encore sans Config
// 12/03/20 Q48 Headers etc for math versioning
//=============================================================================
#ifndef CATPConicsComputation_H 
#define CATPConicsComputation_H 

// ExportedBy
#include "Y30C1XMM.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

//BigScale Mod. #SKA
#include "CATTolerance.h"

class CATSurface;
class CATPCurve;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATGeoODTScaleManager;

#include "CATMathDirection2D.h"
#include "CATMathAxis2D.h"
#include "CATMathPoint2D.h"
#include "CATMathVector2D.h"
#include "CATMathDef.h"
#include "CATMathLimits.h"

#include "CATString.h"
#include "CATGeoOpTimer.h"

//-------------------------------------------------------------------------
class ExportedByY30C1XMM CATPConicsComputation : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATPConicsComputation);
 public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------

  //Do not use - Use the constructor with CATSoftwareConfiguration
  CATPConicsComputation(CATGeoFactory * iFactory,
                        CATSurface *iSurface);
 CATPConicsComputation(CATGeoFactory * iFactory,
                       CATSoftwareConfiguration * iConfig,
                        CATSurface *iSurface);
  virtual ~CATPConicsComputation();

  /**
   * Compute PConics with 3 points (iExtremityPoints[0], iExtremityPoints[1], iPointOnConic)
   * and two tangents(iExtremityTangents[i] : Tangent of the PConic at iExtremityPoints[i])
   */
  virtual void SetPConicsDefinition(const CATMathPoint2D iExtremityPoints[2], 
                                    const CATMathDirection2D iExtremityTangents[2],
                                    const CATMathPoint2D &iPointOnConic);

  /**
   * Compute PConics with 3 points (iExtremityPoints[0], iExtremityPoints[2], iPointOnConic)  
   * and another point (iExtremityPoints[1] : intersection of the tangents computed at 
   * iExtremityPoint[0] and iExtremityPoints[2] )
   */
  virtual void SetPConicsDefinition(const CATMathPoint2D iExtremityPoints[3], 
                                    const CATMathPoint2D &iPointOnConic);

  /**
   * Compute PConics with 2 points (iExtremityPoint[0], iExtremityPoint[2]) and a ratio (0<Ratio<1)
   * and another point (iExtremityPoints[1] : intersection of the tangents computed at 
   * iExtremityPoint[0] and iExtremityPoints[2] )
   */
  virtual void SetPConicsDefinition(const CATMathPoint2D iExtremityPoints[3], 
                                    const double &Ratio);

  /** Compute PConics from 4 points and one tangent, the tangent corresponding to
   *  point index iTgtOfPtIndex (0<= iTgtOfPtIndex < 4)
   */
  virtual void SetPConicsDefinition(const CATMathPoint2D iPoints[4],
                                    const CATMathVector2D & iTangent, CATLONG32 iTgtOfPtIndex);

  /** Compute PConics from 5 points
   */
  virtual void SetPConicsDefinition(const CATMathPoint2D iPoints[5]);

  /**
   * Set Surface
   */
  virtual void SetSurface(CATSurface *iSurface);

  /**
   * Set tolerance (default is the resolution)
   */
  virtual void SetTolerance(double iTolerance);

  /**
   * Set the mode where a relimitation is required.
   * In this mode, the relimitation will occur between the first and last points given to
   * the operator using one of the SetPConicsDefinition methods.
   */
  virtual void SetRelimitation(CATBoolean iRelimit=1);

  /**
   * In SetRelimitation mode, specifies that an additional check must be performed,
   * ensuring that all other points will be located between the first and last given
   * to the operator. If it is not the case, a null pointer will be returned as result.
   */
  virtual void SetCheckRelimitation (CATBoolean iCheck=1);

  /**
   * Get the created PConics.
   * In degenerated cases, a NULL pointer will be returned.
   */
  virtual CATPCurve* GetPConic();

  /**
   * Get the orientation (+1 or -1)
   * with respect to the inputdata (in the Relimit mode only)
   */
  virtual int GetOrientation();

  /**
  * 
  */
  void SetParabolaFirst(CATBoolean iParabolaFirst = TRUE);
  
  //=======================================================================
  //- Protected Methods
  //=======================================================================
 protected:
  /**
   * Run method
   */
  virtual int RunOperator();


private:
  /**
   * Compute and get the coefficent of the reduced implicit equation of the conic
   * Psi(X,Y) = iA * X^2 + iC * Y^2 + iD*X + iE*Y + iF
   * in the axis (iCenter, iI, iJ)
   * returns 0 if OK
   * returns 1 if degenerate case
   * the systme to solve is not homogenus it blends
   * contant, length and square: we only knoaw that Sum( iX*iX ) = 1
   * To be able to have the same behavior in XSCALE we shooze to work with a scaled
   * equation  : 
   * so the conic equation is
   * Psi(X,Y) = iA * X^2 + iC * Y^2 + SCALE*iD*X + SCALE*iE*Y + SCALE*SCALE*iF
   */  
  virtual int GetCoefficients(double &iA, double &iC, double &iD, double &iE, double &iF,
                              CATMathPoint2D &iCenter,
                              CATMathVector2D &iI, CATMathVector2D &iJ,
                              double *iX0=0, double *iY0=0,
                              double *ixMean=0, double *iyMean=0, double * iSquareCharacteristicRadius=0 );
							  //double iTolerance=CATEpsg);
                              //double iTolerance=CATGetDefaultTolerance().EpsgForLengthTest());//@use scaled value of Epsg

  virtual void CheckData(const CATMathPoint2D iExtremityPoints[3], 
                         const CATMathPoint2D & iPointOnConic) const;
  virtual short ComputePParabola(const CATMathVector2D &iu,
                                 const CATMathVector2D &iv);
  virtual void ComputeOtherPConic(const CATMathVector2D &iu,
                                  const CATMathVector2D &iv,
                                  const double &iK);   

  virtual void RunGeometric(); // Run used when the definition is (3pts+2tgts)
  virtual void RunAnalytic();  // Run used when the definition is (4pts+1tgt) or (5pts)
  virtual CATBoolean RelimitPConic(); // To compute the start and end parameters of the Pconic

  void GetParamOnConic (double iU, double iV, double & oW);

  //-----------------------------------------------------------------------
  // CGMReplay methods
  //-----------------------------------------------------------------------
  const CATString * GetOperatorId();
  //- Gestion timer 
  CATGeoOpTimer * GetTimer();


  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  void WriteInput(CATCGMStream  & os);
  void WriteOutput(CATCGMStream & os);
  CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  void Dump( CATCGMOutput& os ) ;
  void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  CATCGMOperator::CATCheckDiagnostic CheckOutput (CATCGMOutput & os);
 
 private:
   void Init();

 public:
  /** @nodoc @nocgmitf */
   void ReadInput(CATCGMStream &Str, CATGeoODTScaleManager * iScaleManager, const short LevelOfRuntime, const short VersionOfStream);

  //=======================================================================
  //- Protected Data
  //=======================================================================
 private :

  // Input data
  CATSurface *_Surface;
  CATSoftwareConfiguration * _Config;

  CATLONG32 _NbSpecPoints;
  CATMathPoint2D _SpecPoints[3]; 
  CATMathPoint2D _PointOnPConic;

  CATLONG32 _NbPoints;
  CATMathPoint2D _Point[5];
  CATLONG32 _NbTangents;
  CATMathVector2D _Tangent[2];
  CATLONG32 _TgtOfPtIndex[2];

  double _Tolerance;
  CATBoolean _Relimit, _RelimitCheck, _ParabolaFirst;
  // cas particulier ellipse par 2 pts 2 tgts + pp et tgts //
  CATLONG32 _MustCreateEllipse;
  CATMathVector2D _TangentEllipse;
  CATMathDirection2D _dirTangentEllipse;

  // Internal data
  CATMathAxis2D _Axis;
  CATLONG32 _PConicType; // = 1 for ellipse, = 2 for parabola, = 3 for hyperbola
  int _DefinitionType; // = 1 for 2pt, 2tg, 1pt on conic
                       // = 2 for 3 spec pt, 1 pt on conic
                       // = 3 for 3 spec pt, 1 ratio (0.<ratio<1.)
                       // = 4 for 4 pt, 1 tg
                       // = 5 for 5 pt
  double _A, _B, _P;
  double _Rho;
  double _wStart, _wEnd;
  // Data for output
  int _Orientation;
  CATPCurve *_PConic;

  // data for CGMReplay functionnality
  friend class CATGeoStreamFactory; // pour gestion du mode Record Automatique

  // private static data
  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;

};


/**
 * Creates an operator for computing a PConics
 * Use ALWAYS  : 
 *     the Set methods of the CATPConicsComputation class to specify how to define the PConics
 *     the Run method of the CATPConicsComputation class to run the operator
 */
ExportedByY30C1XMM
CATPConicsComputation *CreatePConicsComputation(CATGeoFactory  *iWhere,
                                                CATSurface *iSurface);

/**
 * Removes the operator
 */
ExportedByY30C1XMM void Remove(CATPConicsComputation *PConicsOperatorComputing);

#endif

