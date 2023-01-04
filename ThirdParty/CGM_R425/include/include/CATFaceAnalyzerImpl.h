/* -*-C++-*- */
#ifndef CATFaceAnalyzerImpl_H
#define CATFaceAnalyzerImpl_H
// COPYRIGHT DASSAULT SYSTEMES 2009
//------------------------------------------------------------------------------------
//
//
//  SERVICE GEOMETRIQUE / TOPOLOGIQUE DEDIE A L'ANALYSE D'UNE FACE
//
//  owner: ZUS
//------------------------------------------------------------------------------------
#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "CATListOfCATSurfaces.h"
#include "CATErrorDef.h"
#include "CATFaceAnalyzer.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "CATIsoParameter.h"
#include "CATMathConstant.h"
#include "CATGeometryType.h"
#include "ListPOfCATCellManifold.h"
#include "CATMathDirection.h"
#include "ListPOfCATCell.h"

class CATFace;
class CATBody;
class CATLiveBody;
class CATMathPoint;
class CATMathVector;
class CATDeclarativeManifold;
class CATMathAxis;
class CATMathLine;
class CATSoftwareConfiguration;
class CATSurfaceRecognizer;
class CATSurface;
class CATFilletSurface;
class CATCellManifold;
class CATMathTransformation;
class CATCellManifoldGroup;
class CATGeoFactory;
class CATPCurve;
class CATCrvLimits;
class CATFace;
class CATJointFillet;


//----------------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATFaceAnalyzerImpl: public CATFaceAnalyzer
{
public:
  // Constructeur en mode Surface
  CATFaceAnalyzerImpl (CATSoftwareConfiguration *iConfig, CATFace* ipFace, CATBoolean iGeometricalRecognition=FALSE, CATBody* ipBody=NULL); 
  // Constructeur en mode Live A SUPPRIMER
  CATFaceAnalyzerImpl (CATSoftwareConfiguration *iConfig, CATFace* ipFace, CATBody* ipBody, CATBoolean iModeSurface=FALSE, CATBoolean iGeometricalRecognition=FALSE); 
  // Constructeur avec une CM A SUPPRIMER
  CATFaceAnalyzerImpl(CATSoftwareConfiguration *iConfig, CATCellManifold* ipCM);

  // Constructeur avec CM et LiveBody en entree
  //---------------------------------------------------
  //---------------------------------------------------
  // MANDATORY Pour appel aux fonctionnalites PATTERN
  //---------------------------------------------------
  //---------------------------------------------------
  CATFaceAnalyzerImpl(CATSoftwareConfiguration *iConfig, CATCellManifold* ipCM, CATLiveBody* ipLiveBody, CATBoolean iGeometricalRecognition=FALSE);

  // Constructeur par copie
  CATFaceAnalyzerImpl (const CATFaceAnalyzerImpl& iFaceAnalyzerToCopy);
  
  // Destructeur
  virtual ~CATFaceAnalyzerImpl(); 

  // Surcharge de l'operateur =
  CATFaceAnalyzerImpl & operator=(const CATFaceAnalyzerImpl& iFaceAnalyzerToCopy);

  // -----------------------------------------------------------------------------------------
  // Enhancement Level : to activate the last FaceAnalyzer upgrade. 
  //     Max Level     = 1
  //     Current level = 0
  // If the given value is superior to the max level, throw. 
  // -----------------------------------------------------------------------------------------
  void SetUserEnhancementLevel (unsigned short iLevel);

  // -----------------------------------------------------------------------------------------
  // SetDRepFocusOnly : FaceAnalyzer only works on DRep Model and does no further analyze.
  //                    Input LiveBody is Mandatory for this option.
  //                    Return E_FAIL if inputs are not setted properly.
  // -----------------------------------------------------------------------------------------
  HRESULT SetDRepFocusOnly();

  //------------------------------------------------------------------------------------------
  // TEST PROCEDURE of the following HRESULT
  //    1) DO NOT use the key word SUCCEDEED
  //    2) you need to test via if(hr == S_OK, S_FALSE, E_FAIL)
  //
  // Diagnostic:
  //    1) S_OK the selected face is indeed a fillet, chamfer, cylinder,...
  //    2) S_FALSE the selected face isn't a fillet, chamfer, cylinder,...
  //    3) E_FAIL, an error occured during the operation (ex: no factory, null pointer,...)
  //------------------------------------------------------------------------------------------


  //=============================================================================================================================
  //  MANDATORY pour fonction HRESULT IsAFillet(double & oRadius, CATLISTP(CATSurface) oLeftAndRightSupports[2]); 
  //=============================================================================================================================
  // Fonction implementee pour les modes DREP, Surfacique et Geometrique
  // Pour le calcul des supports en mode Geometrique il est OBLIGATOIRE d'avoir un Body
  // Appeler : - Soit le constructeur en mode DREP avec activation du booleen reconnaissance geometrique
  //           - Soit le constructeur en mode Surface avec activation du booleen reconnaissance geometrique + DONNER UN BODY
  //=============================================================================================================================

  //-----------------------------------------------------------------------------
  // Retrieve surface recongizer.
  // Available only if GeometryRecognition has been set.
  // FaceAnalyzer IsXxx method must be called first.
  // Do not Run() again the SurfaceRecognizer ! Only get methods are avaible.
  // The retrieved pointer must be delete with delete C++ operand after use.
  //-----------------------------------------------------------------------------
  CATSurfaceRecognizer * GetSurfaceRecognizer(); 


  // Methodes
  // default tol = CATTolerance -> 10*ToleranceObject.GetResolution
  HRESULT SetLinearTol(double iLinearTol);

  // default tol = CATTolerance -> ToleranceObject.LargeResolutionForAngleTest
  HRESULT SetAngularTol(double iAngularTol);

  HRESULT GetAssociatedFace(CATFace *& oFace);
  HRESULT GetAssociatedCM(CATCellManifold *& opCM);
  HRESULT IsEqual(const CATFaceAnalyzer *ipFace);

  HRESULT IsPlanar();
  HRESULT IsPlanar(CATMathPoint &oOrigin, CATMathVector &oNormal, CATMathVector * opFirstDirection=0, CATMathVector * opSecondDirection=0);

  HRESULT IsCylindrical();
  HRESULT IsCylindrical(CATMathPoint &oOrigin, CATMathVector &oNormal, double & oRadius, CATMathVector *opFirstDirection=0, CATMathVector *opSecondDirection=0, double *opAxisParamMin=0, double *opAxisParamMax=0);

  HRESULT IsSpherical();
  HRESULT IsSpherical(CATMathPoint &oOrigin, double & oRadius, CATMathVector *opFirstDirection=0, CATMathVector *opSecondDirection=0, CATMathVector *opThirdDirection=0);

  HRESULT IsADisk();
  HRESULT IsADisk(CATMathPoint &oOrigin, double & oRadius);

  HRESULT IsAFillet();
  HRESULT IsAFillet(double & oRadius);
  HRESULT IsAFillet(double & oRadius, CATFilletRadiusType& oRadiusType, CATFilletSectionType& oSectionType, double& oFilletShapeParameter);
  HRESULT IsAFillet(double & oRadius, double & oMinVariableRadius, double & oMaxVariableRadius, CATSurfaceRecognizer **oGetSurfaceRecognizer=NULL);
  HRESULT IsAFillet(double & oRadius, double & oMinVariableRadius, double & oMaxVariableRadius, CATFilletRadiusType& oRadiusType, CATFilletSectionType& oSectionType);

  HRESULT IsAFillet(double & oRadius, double & oMinVariableRadius, double & oMaxVariableRadius, ListPOfCATFace oLeftAndRightSupports[2]);
  HRESULT IsAFillet(double & oRadius, ListPOfCATFace oLeftAndRightSupports[2]);

  HRESULT IsAChamfer();
  HRESULT IsAChamfer(int &oChamferType, double &oLeftValue, double &oRightValue);
  HRESULT IsAChamfer(int &oChamferType, double &oLeftValue, double &oRightValue, ListPOfCATFace oLeftAndRightSupports[2]);

  HRESULT IsADraft();
  HRESULT IsADraft(double &oDraftAngle, CATMathDirection &oPullingDir, ListPOfCATCell &oNeutralCellList);
  HRESULT IsADraft(CATMathDirection& oNewPullingDir,double& oNewAngle);
  HRESULT IsADraft(CATMathDirection& oNewPullingDir,double& oNewAngle, ListPOfCATEdge &oNeutralEdges);

  HRESULT IsConical();
  HRESULT IsConical(CATMathPoint &oOrigin, CATMathVector &oNormal, CATMathVector *opFirstDirection=0, CATMathVector *opSecondDirection=0);
  HRESULT IsConical(CATMathPoint &oOrigin, CATMathVector &oNormal, CATAngle &oConeAngle, CATMathVector *opFirstDirection=0, CATMathVector *opSecondDirection=0, double *opAxisParamMin=0, double *opAxisParamMax=0);

  HRESULT IsCoplanar(CATFaceAnalyzer *ipFaceAnalizer);
  HRESULT IsConcentric(CATFaceAnalyzer *ipFaceAnalizer);
  HRESULT HasEqualRadius(CATFaceAnalyzer *ipFaceAnalizer);
  HRESULT IsConfused(CATFaceAnalyzer *ipFaceAnalyzerItf);

  HRESULT IsRevol();
  HRESULT IsRevol( CATMathPoint &oOrigin, CATMathVector &oNormal, CATMathVector *opFirstDirection=0, CATMathVector *opSecondDirection=0);

  HRESULT IsTabulatedCylinder();
  HRESULT IsTabulatedCylinder(CATMathVector &oNormal);

  HRESULT IsToric();
  HRESULT IsToric( CATMathPoint &oOrigin, CATMathVector &oNormal, double &oMajorRadius, double &oMinusRadius, CATMathVector *opFirstDirection=0, CATMathVector *opSecondDirection=0);

  HRESULT IsAPatternCM();
  // PatternType = 1 => LinearPattern, PatternType = 2 => CircularPattern
  HRESULT IsAPatternCM(CATCellManifoldGroup* &ioNetworkGroup);
  HRESULT IsAPatternCM(CATCellManifoldGroup* &ioNetworkGroup, short &ioPatternType);

  // @Deprecated
  HRESULT IsAFillet(double & oRadius, CATLISTP(CATSurface) oLeftAndRightSupports[2]);

  // Allow the geometric recognition of G2 fillets
  // useful only when using a IsAFillet method on a geo FaceAnalyzer
  void SetAcceptG2FilletGeoDetection();

private:

  // Methods for debug
  void CheckInputForDebug();

  // Methodes
  void Init();
  HRESULT GetDeclarativeManifoldInformation(CATDeclarativeManifold *& opDeclarativeManifold);
	void SetPlanarDatum(CATMathPoint &iOrigin, CATMathVector &iNormal, CATMathVector * ipFirstDirection, CATMathVector* ipSecondDirection);
  void GetPlanarOutput(CATMathPoint &oOrigin, CATMathVector &oNormal, CATMathVector *opFirstDirection=0, CATMathVector *opSecondDirection=0);
  void SetCylindricalDatum(CATMathPoint &iOrigin, CATMathVector &iNormal, double &iRadius, CATMathVector *opFirstDirection=0, CATMathVector *opSecondDirection=0);
  void GetCylindricalOutput(CATMathPoint &oOrigin, CATMathVector &oNormal, double &oRadius, CATMathVector *opFirstDirection=0, CATMathVector *opSecondDirection=0);
  void SetSphericalDatum(CATMathPoint &iOrigin, double &iRadius, CATMathVector *ipFirstDirection, CATMathVector *ipSecondDirection, CATMathVector *ipThirdDirection);
  void GetSphericalOutput(CATMathPoint &oOrigin, double &oRadius, CATMathVector *opFirstDirection=0, CATMathVector *opSecondDirection=0, CATMathVector *opThirdDirection=0);
  void SetDiskDatum(CATMathPoint &iOrigin, double &iRadius);
  void GetDiskOuput(CATMathPoint &oOrigin, double &oRadius);
  void SetFilletDatum(double &iRadius);
  void SetFilletDatum(double &iMinVariableRadius, double &iMaxVariableRadius);
  void GetFilletOutput(double &oRadius);
  void GetFilletOutput(double &oMinVariableRadius, double &oMaxVariableRadius); // pour recuperer les rayons min et max d'un fillet variable
  void SetFilletSupports(ListPOfCATFace iLeftAndRightSupports[2]);
  void GetFilletSupports(ListPOfCATFace oLeftAndRightSupports[2]);
  void SetChamferDatum(int &iChamferType, double &iLeftValue, double &iRightValue);
  void GetChamferOutput(int &oChamferType, double &oLeftValue, double &oRightValue);
  void SetChamferSupports(ListPOfCATFace iLeftAndRightSupports[2]);
  void GetChamferSupports(ListPOfCATFace oLeftAndRightSupports[2]);
  void SetConicalDatum(CATMathPoint &iOrigin, CATMathVector &iNormal, CATAngle &iConeAngle, CATMathVector *ipFirstDirection=0, CATMathVector *ipSecondDirection=0);
  void GetConicalOutput(CATMathPoint &oOrigin, CATMathVector &oNormal, CATAngle &oConeAngle, CATMathVector *opFirstDirection=0, CATMathVector *opSecondDirection=0);
  void GetFilletRadius(CATFilletSurface *ipFilletSurface, double &oRadius, CATBoolean &oIsVariable);
  void GetFilletRadius(CATFilletSurface *ipFilletSurface, double &oRadius, CATBoolean &oIsVariable, double &oMinRadius, double &oMaxRadius);
  void SetDataFromGeometry(CATFace *iFace, CATBoolean iFilletDetection = FALSE);
  void SetRevolDatum(CATMathPoint &iOrigin, CATMathVector &iNormal, CATMathVector *ipFirstDirection=0, CATMathVector *ipSecondDirection=0);
  void GetRevolOutput(CATMathPoint &oOrigin, CATMathVector &oNormal, CATMathVector *opFirstDirection=0, CATMathVector *opSecondDirection=0);     
  void SetTabulatedCylinderDatum(CATMathVector &iNormal);
  void GetTabulatedCylinderOutput(CATMathVector &oNormal);    
  void SetTorusDatum(CATMathPoint &iOrigin, CATMathVector &iNormal, double &iMajorRadius, double &iMinusRadius, CATMathVector *ipFirstDirection=0, CATMathVector *ipSecondDirection=0);
  void GetTorusOutput(CATMathPoint &oOrigin, CATMathVector &oNormal, double &oMajorRadius, double &oMinusRadius, CATMathVector *opFirstDirection, CATMathVector *opSecondDirection);
  void SetPatternDatum(CATCellManifoldGroup* &iNetworkGroup, short &iPatternType);
  void GetPatternOutput(CATCellManifoldGroup* &ioNetworkGroup, short &ioPatternType);
  void SetDraftDatum(const double &iDraftAngle, const CATMathDirection &iPulDir, const ListPOfCATCell &iNeutralCellList, const ListPOfCATEdge *iNeutralEdges=NULL);
  void GetDraftOutput(double &oDraftAngle, CATMathDirection &oPullingDir, ListPOfCATCell &oNeutralCellList) const;
  void GetFacesOn(CATSurface* iSurface1, CATSurface* iSurface2, ListPOfCATFace oLeftAndRightSupports[2]);
  void SortSupportFaces(CATGeoFactory     &iFactory, 
                        int                iNumberOfCurves,
                        CATPCurve        **iListOfPCurves,
                        CATCrvLimits      *iListCrvLimits,
                        CATListOfInt      &iCurveToSortIndices,
                        ListPOfCATFace    &iFacesToSort,
                        CATSurface        &iFilletSurface,
                        CATIsoParameter   &iFilletIsoparDir,
                        ListPOfCATFace    &ioSupportFacesLow,
                        ListPOfCATFace    &ioSupportFacesHigh);
  void SetSurfaceRecognizer(CATSurfaceRecognizer *iSurfRecognizer);

  HRESULT FindSupportFromDeclarativeJointFillet_New(CATFace *ipFace, const CATJointFillet * iJointFillet, const ListPOfCATCellManifold & iJointFilletContext, ListPOfCATFace iLeftAndRightSupports[2]) const;
  HRESULT FindSupportFromDeclarativeJointFillet(const CATJointFillet * iJointFillet, const ListPOfCATCellManifold & iJointFilletContext, ListPOfCATFace iLeftAndRightSupports[2]) const;


  // Return max level between user-level and project level
  unsigned short GetEnhancementLevel() const; 

  HRESULT IsPlanar_Private();
  HRESULT IsCylindrical_Private();
  HRESULT IsSpherical_Private();
  HRESULT IsADisk_Private();
  HRESULT IsAFillet_Private();
  HRESULT IsAChamfer_Private();
  HRESULT IsADraft_Private();
  HRESULT IsConical_Private();
  HRESULT IsRevol_Private();
  HRESULT IsTabulatedCylinder_Private();
  HRESULT IsToric_Private();
  HRESULT IsAPatternCM_Private();

  void ComputeAxisParams(CATMathPoint & iOrigin, CATMathVector & iDirection);

  // -------------------------------------------------------------
  // Utilitaires
  // -------------------------------------------------------------
  const CATSurface * RetrieveUnderlyingReferenceSurfacePoly (CATFace * iFace) const;
  const CATSurface * RetrieveUnderlyingTypeOfSurface (CATFace * iFace, CATGeometricType iType) const;
  CATGeoFactory* GetFactory();

  //--------------------------
  // Debut Methodes Deprecated
  //--------------------------
  void SetFilletSupports(CATLISTP(CATSurface) iLeftAndRightSupports[2]);
  void GetFilletSupports(CATLISTP(CATSurface) oLeftAndRightSupports[2]);
  //--------------------------
  // Fin Methodes Deprecated
  //--------------------------

  //--------------------------
  // Input data
  //--------------------------
  CATSoftwareConfiguration *_Config;
  CATFace* _pFace;
  CATBody* _pBody;
  CATCellManifold* _pCM;
  CATBoolean _ModeLive;
  CATBoolean _DRepFocusOnly;
  CATBoolean _ModeSurface; // To Remove (allways true)
  CATBoolean _GeometricalRecognition;
  CATBoolean _G2FilletGeoRecognition;
  CATLiveBody* _pLiveBody;

  //--------------------------
  // Output data
  //--------------------------
  CATMathPoint          *  _pOrigin;
  CATMathVector         *  _pNormal;
  CATMathVector         *  _pFirstDirection;
  CATMathVector         *  _pSecondDirection;
  CATMathDirection      *  _PullDir;

  double                   _CylinderRadius, _SphereRadius, _FilletMinVariableRadius, _FilletMaxVariableRadius, _MinorRadius, _MajorRadius, _LeftValue, _RightValue, _DraftAngle;
  double                   _DiskRadius;
  CATAngle                 _ConeAngle;

  double                * _pAxisParamMin, * _pAxisParamMax;
  // Fillet data
  double                  _FilletRadius;
  double                  _FilletShapeParameter;
  CATFilletRadiusType     _FilletRadiusType;
  CATFilletSectionType    _FilletSectionType;
  CATLISTP(CATSurface)    _FilletLeftAndRightSupports[2]; // Deprecated
  ListPOfCATFace          _FilletLeftAndRightFacesSupports[2], _ChamferLeftAndRightFacesSupports[2];
  ListPOfCATEdge          _NeutralEdges;
  ListPOfCATCell          _DraftNeutralCells; // true neutral - can be faces or edges.

  CATSurfaceRecognizer  * _SurfaceRecogOpe; // can be returned for advanced users.

  int                     _ChamferType;
  CATCellManifoldGroup  * _NetworkGroup;
  short                   _PatternType;


  // Sauvegarde de Donnees
  int _Planar, _Cylindrical, _Spherical, _Fillet, _Chamfer, _Conical, _Revol, _TabulatedCylinder, _Toric, _PatternCM, _Draft; 
  int _Disk;

  // Usage interne
  int _FindFilletSupports, _FindChamferSupports, _FindDraftNeutral;


  // tolerance

  double _LinearTol;  // linear tolerance
  double _AngularTol; // angular tolerance

  // Upgrade level 
  // current level = 0
  unsigned short _EnhancementUserLevel;

};


#endif
