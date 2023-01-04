#ifndef CATIPGMFilling_h_
#define CATIPGMFilling_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATListOfDouble.h"
#include "CATPolygonToSurfMeshFunction.h"
#include "CATIncompatibilityType.h"

class CATBody;
class CATCGMJournalList;
class CATCrvLimits;
class CATCrvParam;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATICContact;
class CATMathPoint;
class CATMathVector;
class CATOptionPlateFE;
class CATPCurve;
class CATPoint;
class CATShell;
class CATSurface;
class CATTopData;
class CATPowerCldPolygon;
class CATLISTP(CATFace);
class CATLISTP(CATEdge);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFilling;

class ExportedByCATGMOperatorsInterfaces CATIPGMFilling: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMFilling();

  // To define a constraint of type
  //  - Free Bound (The Edge is used to build the Face)
  //  - Internal   
  //  A G0 Tolerance can be atthached to the Constraint, 
  //  if iTolerance == 0.0 the default tolerance is used.
  //  if IsFree=TRUE the Edge iE is not constraint 
  virtual int Add(
    CATEdge *iE,
    const CATBoolean iIsBound = 1,
    const double iTolerance = 0.0,
    const CATBoolean isFree = FALSE) = 0;

  // To define a constraint of type Connected Bound :
  // if iIsBound = 1 The Edge is used to build the Face and build the shell
  // The Face/Face contact can be G0/G1/G2 if <iOrder> is 0/1/2
  virtual int Add(
    CATEdge *iE,
    CATFace *iF,
    const short iOrder,
    const double iToleranceG0 = 0.0,
    const CATBoolean iIsBound = 1,
    const double iToleranceG1 = 0.0) = 0;

  //To Define an inner wire 
  //the inner wire is defined by a list of Edges iListEdges
  //the size of  iListOfFree  && iListOfTol must be the same as iListEdges
  // iListOfFree : for each edge (i=1.. iListEdges.Size()) 
  // if iListOfFree[i]=1 the edge is not constraint (free)
  // if iListOfFree[i]=0 the edge is constraint
  // iListOfTol :for each edge (i=1.. iListEdges.Size()) 
  // iListOfTol[i] is the tolerance associated with each edge iListEdges[i]
  // 
  // To Add N inner Wires  this method must be called N times 
  virtual int Add(
    CATLISTP(CATEdge) &iListEdges,
    CATListOfInt &iListOfFree,
    CATListOfDouble &iListOfTol) = 0;

  //To Define an inner wire  with support
  //the inner wire is defined by a list of Edges iListEdges
  //the size of  iListFaces  iListOfOrder  && iListOfTol must be the same as iListEdges
  // iListFaces : for each edge (i=1.. iListEdges.Size())
  // iListFaces[i] is the face associated with the edge
  // if there is no face iListFaces[i] must be set to NULL 
  // iListOfOrder : for each edge (i=1.. iListEdges.Size()) 
  //  the continuity order associated with the edge 
  // iListOfTol :for each edge (i=1.. iListEdges.Size()) 
  // iListOfTol[i] is the tolerance associated with each edge iListEdges[i]
  // 
  // To Add N inner Wires  this method must be called N times 
  virtual int Add(
    CATLISTP(CATEdge) &iListEdges,
    CATLISTP(CATFace) &iListFaces,
    CATListOfInt &iListOfOrder,
    CATListOfDouble &iListOfTol) = 0;

  // To define a punctual G0 constraint 
  virtual int Add(const CATPoint *iPoint, const double Tolerance = 0.0) = 0;

  // To define a punctual contraint and associate a Normal 
  // if HasContactG0=1  the result pass by  the  3d Point 
  // if HasContactG0=0  only the normal is taken into account and not the 3d Point.
  virtual int Add(
    const CATPoint *iP,
    CATMathVector &iNormal,
    const double ToleranceG0 = 0.0,
    CATBoolean HasContactG0 = 1,
    const double ToleranceG1 = 0.5) = 0;

  // To define a punctual G0 constraint and associate U,V parameters 
  virtual int Add(
    const CATPoint *iPoint,
    const double U,
    const double V,
    const double Tolerance = 0.0) = 0;

  // pour definir un ensemble de contraintes points,
  // iCld    : de type CATPowerCldPolygon
  // iTolG0  :  tolerance G0
  // iRation : le taux de contrante a satisfaire 0< ratio <= 1.
  // iTolG1  :  tolerance G1
  // iTolG2  :  tolerance G2
  // RETURN  : 0 ok , autre => echec
  virtual int Add(CATPowerCldPolygon *iCld, double iTolG0, double iRatio) = 0;

  //  To Associate  to a 3d curve  a curve representing its  normal 
  //  if iTolerance == 0.0 the default tolerance is used.
  // the curve and  the normal are same parameter 
  virtual int Add(
    CATEdge *Edge,
    CATEdge *EdgeNormal,
    const double ToleranceG0 = 0.0,
    const double ToleranceG1 = 0.5) = 0;

  //To associate a contact to an edge 
  // iIsBound = 1 (The Edge is used to build the Face)
  // iIsBound = 0 (The Edge is not used to build the face , the edge is just a constraint)
  //  if iTolerance == 0.0 the default tolerance (resolution) is used.
  //  if IsFree=TRUE the Edge iE is not constraint 
  virtual int Add(
    CATEdge *iE,
    CATICContact *iContact,
    const CATBoolean iIsBound = 1,
    const double iTolerance = 0.0,
    const CATBoolean isFree = FALSE) = 0;

  // To define a initial surface.
  // The result will be based on a deformation of this surface.
  // if iDeformAll==1 the complete surface will be deformed
  // else only a usefull limitation will be deformed
  virtual void SetInitialSurface(CATSurface *iS, const CATBoolean iDeformAll = 0) = 0;

  //  ktu : mars  2004 :
  //  To reset Initial Surface = > for GDD
  virtual int ResetInitialSurface(
    CATSurface *iSurfInit,
    const CATBoolean iDeformAll = 0) = 0;

  // ToDefine Tolerances G1 and G2
  virtual void SetTolerance(
    const double TolAngular = 0.5,
    const double TolCurvature = 0.1) = 0;

  // ToDefine algorithm paameter
  virtual int SetResolParam(
    const short iOrder = 3,
    const short iNbIter = 3,
    const CATBoolean iWithAnisotropie = 0,
    const CATBoolean iWithFreeAnisotropie = FALSE) = 0;

  // To define NURBS parameters 
  // Warning if a value > 0 is returned the parameters are take into acount.  
  virtual int SetApproxParam(
    const int MaxNumberOfPatch = 64,
    const short Maxdegree = 8) = 0;

  virtual int SetApproxParam(
    const int MaxUNumberOfPatch,
    const int MaxVNumberOfPatch,
    const short MaxUdegree,
    const short MaxVdegree) = 0;

  // To define if the result have to be based on a NURBS Surface
  // This defined if the result have to be approximed.
  // <iMode> can be  
  //  0 : Face on procedural surface is returned (Interpolation)
  //  1 : Face on BSPline surface is returned (Interpolation & Approxmation)
  //  2 : Face on BSPline surface is returned (Smoothing)
  //   3 : Automatic mode :  best result betweemn Face on BSPline surface (Interpolation & Approximation)  
  //       or   Face on BSPline surface(Smoothing) 
  //  Other mode are reserved for the future
  // by default iMode=3
  virtual void SetMode(const short iMode = 3) = 0;

  // To set a code Level (it is useful to avoid some news in the operator)
  // -1 : Automatic choice (up to date)
  //  0 : Version 0 (the default)
  //  1 : Version 1
  //  2 : Version 2
  //  ... etc for future modification
  virtual void SetLevel(const int iLevel) = 0;

  // To Read or modify the Options for PlateFE
  // Only for advertice user !!!
  virtual CATOptionPlateFE *PlateFEOptions() = 0;

  // to use  HigherExponant in PlateFE// gdd 
  virtual void SetHigherExponent(const int iHigherExponent) = 0;

  // To set the Body to seew with the filling result
  virtual int SetBody(const CATBody *ibody) = 0;

  virtual int SetShell(CATShell *ishell) = 0;

  // Only a face is output (GetResult()==NULL) when SetBody has been called
  virtual int SetFaceOnly() = 0;

  virtual void SetModifJournal() = 0;

  // this method returns:
  // -1 :the initial surface has been loaded by the method SetInitialSurface 
  // 0 : the initial surface is computed and is not a plane
  // 1 : the initial surface is computed and is a plane
  // 2 :  Plan calcule , et  si le contour a une petite courbe (l<0.005) ,
  //         et si sa projetee est nulle 
  // 999 : Erreur..
  // this method must be called before the method Run()
  virtual int IsInitialSurfacePlane() = 0;

  // this methode returns the constraint  which corresponding to the small curve
  // with null projection if isInitialSurfacePlane=2 otherwise it returns 0
  virtual int GetNumSmallCurve() = 0;

  // the result is always a  Nurbs result even if  the result is a plane 
  virtual void SetNurbsResult() = 0;

  // there is a cutting curve in the contour to fill 
  virtual int SetCuttingCurve() = 0;

  // WARNING : this method is special for LVL in case of 
  // Regularizator project. THIS METHOD CHANGES THE APPROX PARAMS.
  // The result  face is only build from the surface computed by powerfill, 
  // the bounds are not taken into account in  the construction of the face  
  virtual void SetNoTrimmedResult() = 0;

  // a point  which does not belong to the 2D bounding box
  // of the bounds to fill is kept for the computation of the surface.
  // To use only for regularisator project
  virtual void SetNoUseUVBox() = 0;

  virtual void CreateContactByCompatibleComb() = 0;

  // Link method
  // to associate a PCurve to an Edge  
  virtual int Link(
    const CATEdge *iE,
    CATPCurve *iPCurve,
    const CATCrvLimits &iLimits) = 0;

  // if this method is called the orientation of the filling face 
  // depends on  the orientation of the first edge otherwise it depends on
  // the order of the edges 
  // 
  virtual void OrientationByFirstEdge(const int iorien) = 0;

  // convention pour l'orientation de la direction dans le 
  //cas du remplissge d'un cylindre G1 .
  // si iorien=1 alors on garde la convention geometrique
  // sinon on inverse 
  virtual void ConventionOrientation(const int iorien) = 0;

  // Construction
  virtual int Run() = 0;

  // this method returns :
  // the PCurve on the resulting surface corresponding to a given constraint.
  virtual CATPCurve *GetPCurve(const int iNumConst) = 0;

  //  this methods returns :
  // 0 :  the tolerance G0  is  not reached
  // 1 :  the  tolerance G0 is reached  
  virtual CATBoolean isFillG0OK() = 0;

  //  this methods returns :
  // 0 :  the tolerance G1  is  not reached
  // 1 :  the  tolerance G1 is reached  
  virtual CATBoolean isFillG1OK() = 0;

  //  this methods returns :
  // 0 :  the tolerance G2  is  not reached
  // 1 :  the  tolerance G2 is reached  
  virtual CATBoolean isFillG2OK() = 0;

  // this method returns 1 if all the ponctual contraints are too close of the contour to fill 
  // this method returns 2 if all the ponctual contraints are outside of the contour to fill 
  virtual int isInvalidPoint() = 0;

  // if iskeep =0 : the  fill result is null if  the tolerance G0  is  not reached
  // if iskeep =1 : the  fill result is  given even if the tolerance G0  is  not reached
  virtual void KeepNoG0Result(const CATBoolean iskeep = 1) = 0;

  // The filling Face
  virtual CATFace *Face() const = 0;

  // The seewed Body 
  virtual CATBoolean IsCurveConstraintOutside(const int &iConstIndex) = 0;

  virtual CATBoolean IsPointConstraintOutside(const int &iConstIndex) = 0;

  virtual void AllowPartialResult() = 0;

  //Limited use only for SurfaceNetWork 
  // In case of Fitting and AllG0 constraints or G0G1 constraints the initial plane is computed by flux method instead of inertia  
  virtual void ComputePlaneByFluxForFitting() = 0;

  // Get the initial surface 
  virtual CATSurface *GetInitialSurface() const = 0;

  //Information on the result accuracy
  virtual double G0MaxError() = 0;

  virtual double G1MaxError() = 0;

  virtual double G2MaxError() = 0;

  virtual double G0MaxDeviation() = 0;

  virtual double G1MaxDeviation() = 0;

  virtual double G2MaxDeviation() = 0;

  virtual double G0MaxDeviation(const int iE, CATMathPoint *ioMaxPoint = NULL) = 0;

  virtual double G1MaxDeviation(const int iE, CATMathPoint *ioMaxPoint = NULL) = 0;

  virtual double G2MaxDeviation(const int iE, CATMathPoint *ioMaxPoint = NULL) = 0;

  //Information on the result accuracy
  virtual double GetTolG0Max(const int iE) = 0;

  virtual double GetTolG1Max(const int iE) = 0;

  virtual double GetTolG2Max(const int iE) = 0;

  /**
   * pour activer les transverse
   * par defaut non activer
   * 0 succes, 1 autre echec
   * iIsG2Transverse:
   *     - true => chagement des contrainte transverses.
   *     - fasle=> pas de chargement des contraintes transverses.
   * Les 2derniers arg sont valable que si  ler le 1er arg == true
   * dans ces cas:
   * iIsAbsoluteTolG2:
   *      - true =>  on utilise la tolerance G2 des contact comme tolerance absolue
   *                 le dernier argument est inutile.
   *      - false => alors la tolG2 est un pourcentage donnes par iPercentTolG2 qui par
   *                 defaut == 5%. On n' utilise plus la tolG2 du contact.
   */
  virtual int SetG2Transverse(
    const CATBoolean iIsG2Transverse,
    const CATBoolean iIsAbsoluteTolG2 = 1,
    const double iPercentTolG2 = 0.05) = 0;

  /**
   * @nodoc
   * Possibility to create or not merged curves between the boundaries of the wire to fill
   * and the boundaries of fill surface.
   * if the type of the fill is powerfill, the merged curves are created by default.
   * if CreateMergedCurve=FALSE, a simcurve is created from the pcurves of the fill surface. 
   * if the type of the fill is analytic, the merged curves are not created. 
   */
  virtual void SetCreateMergedCurves(const CATBoolean iCreateMergedCurve = TRUE) = 0;

  /**
   * 0  il n'y a pas de contraintes G2
   * 1  le G2 est charge  
   * 2  le G2 n'est pas charge car forte pente 
   * 3  le G2 n'est pas charge car incompatibilites 
   */
  virtual int G2ConstraintsLoaded() = 0;

  // permet de gerer le pb des limites dans l'intersection segment/segment dans GeoPlateUtilities::VerifInterPolygon2D 
  // en attendant une gestion appropriee par codeLevel
  virtual void SetNewIntersectionSegment() = 0;

  virtual CATBoolean IsConsistentUV(double iU, double iV) const = 0;

  virtual void RemovePCurves() = 0;

  /**
    * SetMeshFunction : 
    *  To  set  the  mesh  fumnction.
    */
  virtual int SetMeshFunction(MeshFunc4P2S iFunc) = 0;

  virtual void SetGeomFeMode() = 0;

  virtual void SetFillTolerant() = 0;

  // pour imposer une continuite max 
  virtual void SetMaxContinuity(const int iCont) = 0;

  // Apres le Run  de l'operateur on libere les contacts et on les libere dans le Builder. 
  // On n'attend plus le delete de l'operateur pour le faire . Ceci permet de ne plus avoir
  // d'objects lockes apres le Run de l'operateur.
  virtual void SetContactFreedom() = 0;

  // prend en compte le smartGeometry. 
  // C'est a dire si deux edges adjacentes ont en commun la meme geometry, les edges correspondantes
  // du Fill ont la meme geometry. 
  virtual void SetSmartGeometry() = 0;

  //informations sur les incompatibilites.  
  virtual int GetNumberOfIncompatibilities() = 0;

  virtual void BeginningIncompatibility() = 0;

  virtual CATBoolean GetNextIncompatibility(
    int &oNumCont1,
    int &oNumCont2,
    double &oParam1,
    double &oParam2,
    FillingIncompatibilityType &oType,
    double &oValue) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFilling(); // -> delete can't be called
};

/**
 * Creates a topological operator that fills an area with respect of some constraints.
 * @param iGeoFactory
 * The pointer to the factory of the geometry. 
 * @param iData
 * The pointer to the topological data corresponding to the configuration and the journal.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFilling *CATPGMCreateFilling(CATGeoFactory *iFactory, CATTopData *iData);

#endif /* CATIPGMFilling_h_ */
