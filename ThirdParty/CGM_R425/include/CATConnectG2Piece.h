#ifndef CATConnectG2Piece_H
#define CATConnectG2Piece_H

//=============================================================================
// Copyright Dassault Systemes Provence 2010-2014, all rights reserved
//=============================================================================
//
// CATConnectG2Piece:
//
//=============================================================================
// Usage notes:
//=============================================================================
// 26/06/2014 : HLN ; Add _TwistDiagnostic for G2 surface
// 29/04/2011 : IZE : Add _InitialG1Face
// 02/12/2010 : HLN : 
// 15/12/2009 : CWM : Creation
//=============================================================================
#include "ConnectInt.h"

#include "CATMathDef.h"
#include "CATFilletBordersCommand.h"
#include "CATTopDefine.h"

#ifndef NULL
#define NULL 0
#endif

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATGeometry;
class CATCurve;
class CATSurface;
class CATFace;
class CATCrvParam;
class CATInclusionPtSur;

class ExportedByConnectInt CATConnectG2Piece
{
  public:
  CATConnectG2Piece(CATGeoFactory * iFactory, CATSoftwareConfiguration *iSoftwareConfiguration);
  CATConnectG2Piece(CATConnectG2Piece &iManagerToCopy);

  ~CATConnectG2Piece();

  void SetDuplicatedContacts(CATGeometry *iContact1, CATGeometry *iContact2);
  void GetContacts(CATGeometry *&oContact1, CATGeometry *&oContact2);

  void SetInitialSurface(CATSurface *iSurface, CATOrientation iOrientation);
  CATSurface *GetInitialSurface(CATOrientation *oOrientation=NULL);

  void SetInitialG1Face(CATFace *iG1Face);
  CATFace *GetInitialG1Face();
  
  void SetG2BlendSurface(CATSurface *iG2Surface, CATOrientation iOrientation);
  CATSurface *GetG2BlendSurface(CATOrientation *oOrientation=NULL);

  void SetTwistDiagnostic(int iTwistDiagnostic);
  void GetTwistDiagnostic(int &oTwistDiagnostic);

  void CreateG2BlendBorders(CATFilletBordersCommand iCommand,
                            CATGeometry*& SplineBorder1,
                            CATGeometry*& SplineBorder2,
                            CATGeometry*& StartCircularBorder, 
                            CATGeometry*& EndCircularBorder,
                            const CATCrvParam* iSplineStartPosition,
                            const CATCrvParam* iSplineEndPosition,
                            const CATCrvParam* iStartBorderPosition,
                            const CATCrvParam* iEndBorderPosition,
                            const CATLONG32 iParamID, 
                            CATSurface * FilletSurface) const;

  private:
  double UExtrFilletBorder(const CATCrvParam *iCrvParam,
                           CATCurve *iGuide,
                           const double &iUextr,
                           CATBoolean iSameParam,
                           CATInclusionPtSur *iInclusionPtSurOpe) const;


  CATGeoFactory   *_Factory;
  CATSoftwareConfiguration *_SoftwareConfiguration;
  CATFace         *_InitialG1Face; // FaceG1initiale
  CATSurface      *_InitialSurface; // Surface fillet initiale a deformer
  CATOrientation   _InitialSurfaceOrientation;
  CATSurface      *_G2BlendSurface; // Surface G2 apres deformation
  CATOrientation   _G2BlendSurfaceOrientation;
  CATGeometry     *_Contacts[2]; // MergeCurves contenant les PCurves sur les supports et les PCurves sur la surface initial
  int              _TwistDiagnostic; // diagnostic de twist de la surface G2
};

#endif

