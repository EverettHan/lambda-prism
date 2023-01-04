/*-*-c++-*-*/
//===============================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved 
//===============================================================================
//
// CATExtrapolSubdivSurface :
// Class for extrapoling a SubdivSurface (CATSubdivCellSurface or CATSubdivGridSurface) beyond a box.
//
//=============================================================================
// Usage notes:
//
// 
//=============================================================================
// History :
// 05/03/2009 : RNO : Creation (squelette)
// 12/03/2020 : Q48 : Headers etc for math versioning
//=============================================================================
#ifndef CATExtrapolSubdivSurface_H 
#define CATExtrapolSubdivSurface_H 

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATMathDef.h"

#include "CATExtrapolSurface.h"
#include "CATCGMVirtual.h"

class CATMathPoint;
class CATMathVector;

class CATMathNurbsBipar;
class CATMathGridOfPoints;
class CATKnotVector;

class CATGeoFactory;
class CATMathSetOfPoints;
class CATMathVector2D;
class CATSurParam;
class CATMathNurbsBipar;
class CATSoftwareConfiguration;


//Different Type d'erreur (il faut les numeroter pour pouvoir les caster en int facilement)
typedef enum
{
  CATExtrapolSubdivErrorType_OK                =0,
  CATExtrapolSubdivErrorType_NullPointer       =1,
  CATExtrapolSubdivErrorType_NotASubdivSurface =2,
  CATExtrapolSubdivErrorType_UnAbleToProcessYet=3,
  CATExtrapolSubdivErrorType_ClosedSide        =4,
  CATExtrapolSubdivErrorType_ErreurConversion  =5,
  CATExtrapolSubdivErrorType_OrientationProblem=6,
  CATExtrapolSubdivErrorType_InvalidZoneSize   =7,
  CATExtrapolSubdivErrorType_ExtrapolTooBig    =8,
  CATExtrapolSubdivErrorType_UpdateError       =9,
  CATExtrapolSubdivErrorType_RequiredVectorTooBig =10,
  CATExtrapolSubdivErrorType_MaxSpanSizeExcess =11,
  CATExtrapolSubdivErrorType_ActiveSplitThrow  =12

} CATExtrapolSubdivErrorType;

//RNO  Je mets une valeur aux side car ce n'est pas pratique pour faire des operations 
// Notamment pour les orientations primaires
/*
enum CATSurfaceSide
  {
    SideUMin = CATExtrapolSurfaceSideUMin,
    SideUMax = CATExtrapolSurfaceSideUMax,
    SideVMin = CATExtrapolSurfaceSideVMin,
    SideVMax = CATExtrapolSurfaceSideVMax,
    SideUMinVMin = CATExtrapolSurfaceSideUMinVMin,
    SideUMaxVMin = CATExtrapolSurfaceSideUMaxVMin,
    SideUMinVMax = CATExtrapolSurfaceSideUMinVMax,
    SideUMaxVMax = CATExtrapolSurfaceSideUMaxVMax
  };

*/

//


class ExportedByY30C3XGG CATExtrapolSubdivSurface   : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATExtrapolSubdivSurface);
public:
  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------

  //CTOR with SubdivCell or Grid
  CATExtrapolSubdivSurface (CATGeoFactory *iFactory,
                            CATSoftwareConfiguration * iConfig,
                              CATSurface * ioSur,
                              CATExtrapolSurface::CATSurfaceSide iSurfaceSide,
                              const CATMathVector2D & iDirection,
                              const CATSurParam & iParamOnSur);


  ~CATExtrapolSubdivSurface();

  CATCGMOperatorDebugDeclareRun(CATExtrapolSurface,CATGeoOperator);

  /** @nodoc @nocgmitf */
  int RunOperator();
 
  

private:

  //Build _Side and Check for Closure
  CATExtrapolSubdivErrorType CheckAndTranslate();

  //Init Zone Number and Multiform Array
  CATExtrapolSubdivErrorType ZoneInits(int NU_NewGrids[9], int NV_NewGrids[9],CATMathNurbsBipar ** NewGrids[9]);

  //Construct the Bipar May also do a Pre-Extrapolation if needed
  CATExtrapolSubdivErrorType AdvancedInits( int FullNU_NewGrids[9],int FullNV_NewGrids[9], CATMathNurbsBipar ** FullNewGrids[9]);
  //Main Long Extrpolation Loop (add Patch One By One) ... The Bipar will be updated
  CATExtrapolSubdivErrorType ReExtrapolLoop(int FullNU_NewGrids[9],int FullNV_NewGrids[9], CATMathNurbsBipar ** FullNewGrids[9]);
  
  //Update the subdivGrid with the NewGrids
  CATExtrapolSubdivErrorType UpdateSurface(CATMathNurbsBipar **NewGrids[9],int NU_NewGrids[9], int NV_NewGrids[9]);

  //Tools
  //Split the Extrapolated Bipar
  CATExtrapolSubdivErrorType SplitBipar(int Side,CATMathNurbsBipar *&Extrapolatedbipar,double StartU, double  EndU, double  StartV, double EndV,
                                        CATMathNurbsBipar **NewGrids[9],int NU_NewGrids[9], int NV_NewGrids[9]);


    //    -------------------------------
    //   |      |                  |      |
    //   |  Z6  |        Z7        |  Z8  |
    //   |      |                  |      |                 Zone i
    //   |--------------------------------|            --------------------
    //   |      |                  |      |           |                    | 
    //   |      |                  |      |           |                    |
    //   |  Z3  |      Grid (Z4)   |  Z5  |           |                    |
    //   |      |                  |      |           |                    |
    //   |      | S0 S1 S2 ...     |      |           |                    |
    //   |--------------------------------|           |                    |
    //   |      |                  |      |           | S0 S1 S2 ...       |
    //   |  Z0  |        Z1        |  Z2  |            --------------------
    //   |      |                  |      |
    //    -------------------------------

  CATExtrapolSubdivErrorType FillZone1(int Nu[9],int Nv[9],CATMathNurbsBipar ** Zone[9]);
  CATExtrapolSubdivErrorType FillZone7(int Nu[9],int Nv[9],CATMathNurbsBipar ** Zone[9]);
  
  CATExtrapolSubdivErrorType FillZone3(int Nu[9],int Nv[9],CATMathNurbsBipar ** Zone[9]);
  CATExtrapolSubdivErrorType FillZone5(int Nu[9],int Nv[9],CATMathNurbsBipar ** Zone[9]);
  
  //Zones Coins
  CATExtrapolSubdivErrorType FillZone0(int Nu[9],int Nv[9],CATMathNurbsBipar ** Zone[9]);
  CATExtrapolSubdivErrorType FillZone2(int Nu[9],int Nv[9],CATMathNurbsBipar ** Zone[9]);
  CATExtrapolSubdivErrorType FillZone6(int Nu[9],int Nv[9],CATMathNurbsBipar ** Zone[9]);
  CATExtrapolSubdivErrorType FillZone8(int Nu[9],int Nv[9],CATMathNurbsBipar ** Zone[9]);

  
  

  //Construit les contraintes Points et Vector deplacement en fonction d'un Vecteur de Bipar
  // Les RefZone 0->Nu-1 pour les side VMax (+) et Vmin (-)
  
  // Les vecteurs construits ont une taille de Nu+1 pour les sides VMin et Vmax
 
  CATExtrapolSubdivErrorType BuildConstraintsV(int Side,int Nu,int Nv,CATMathNurbsBipar ** RefZone,
                                                                      CATKnotVector ** & oReferenceKVV,
                                                                      CATMathPoint * & oStartPoints,
                                                                      CATMathVector *  & oVectors);
  // Et RefZone 0->Nv-1 pour les side UMax (+) et UMin (-)
   // et une taille Nv+1 pour les sides Umin et Umax
  CATExtrapolSubdivErrorType BuildConstraintsU(int Side, int Nu,int Nv,CATMathNurbsBipar ** RefZone,
                                                                      CATKnotVector ** & oReferenceKVV,
                                                                      CATMathPoint * & oStartPoints,
                                                                      CATMathVector *  & oVectors);
  //Rempli la Zone de Bipar de dimension Nu x NV par des translations de points iv*BaseU
  CATExtrapolSubdivErrorType EasyFillFromGridV(int Side,int Nu,int Nv,CATMathNurbsBipar ** Zone,
                                               CATMathPoint  iStartPoints[], CATMathVector iTranslators[] ,
                                                                       CATKnotVector * iBaseU []);
  //Rempli la Zone de Bipar de dimension Nu x NV par des translations de points iu*BaseV
  CATExtrapolSubdivErrorType EasyFillFromGridU(int Side,int Nu,int Nv,CATMathNurbsBipar ** Zone,
                                                                       CATMathPoint iStartPoints[], CATMathVector iTranslators [],
                                                                       CATKnotVector * iBaseV []);

  void MemoryCheckInitSOFP(CATMathSetOfPoints &ResSOF );

  //Input Data
  //CATGeoFactory   * _Factory;
  CATSoftwareConfiguration * _Config;
  CATSurface      * _SubdivSurface;
  CATExtrapolSurface::CATSurfaceSide _Side;

  CATMathNurbsBipar ** _ExistingBipars; //Pour ReextrapolOnly (NU*NV)
  char             *_ExistingOri;      //Pour ReextrapolOnly (NU*NV)

  CATMathVector2D _Direction;
  CATSurParam _ParamOnSur ;
  int _Type; //0 For Cell 1 For Grid
  
  
 //Data on Input Surface
  int _NU,_NV; //Nombre de Surface en U et en V
  
  
  CATExtrapolSubdivErrorType _Error;

  CATLONG32 _SideAsInt;
  CATBoolean _ReExtrapolOnly,
             _ClosedU,
             _ClosedV;
};

#endif
