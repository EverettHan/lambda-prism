//=================================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved 
//=================================================================================
//
// Data of CGM implementation for the CATSubdivCellSurface object
//
//=============================================================================
// Usage notes:
//
// Strictement réservé aux implémentations CGM.
//=============================================================================
//=============================================================================
// HISTORIQUE :
//
// 24/01/2008 : RNO : Creation !! 
//============================================================================= 
#ifndef CATSapSubdivGridSurface_H
#define CATSapSubdivGridSurface_H
#include "CATSapApprox.h"
#include "CATSobDiag.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATCGMVirtual.h"
#include "CATSapSubdivSurface.h"


#include "CATMathDef.h"




class CATMathGridOfPoints;
class CATSapKnotVector;

class CATSobMesh;
class CATSobFace;

class CATSapEvalResult;
class CATSapSurParam;
class CATSapEvalCommand;

class CATMathFunctionXY;
class CATTolerance;

class CATMathTransformation;
class CATSapExtrapolData;


class ExportedByCATSapApprox CATSapSubdivGridSurface : public CATSapSubdivSurface
{
public :
  virtual ~CATSapSubdivGridSurface();
  virtual void GetGridSize(int &oNU,int &oNV) const =0;
  virtual void GetGridOfSobFaces(int &oNU,int &oNV,CATSobFace ** & oTabOfSobFace) const =0;
  virtual void GetGridOfSobFaces(int &oNU,int &oNV, CATSobFace ** & oTabOfSobFace, char *&oOrientations) const =0;
  virtual void GetFirstFaceAndEdgeIndex(const CATSobFace *& oFirstFace,short & oEdgeIdx)const =0;

  virtual void GetEquationsSize( int & oIndexOffsetU,int & oMaxCountU,
                            int & oIndexOffsetV,int & oMaxCountV )const =0;

  virtual CATSobDiag MathEval(const int Pu, const int Pv, const double LocalParamU, const double LocalParamV,
                      const CATMathOption iOptions, double * ioF, 
                      double * ioFx =0, double * ioFy=0,
                      double * ioFx2=0, double * ioFxy=0, double *ioFy2=0, 
                      double *iofx3=0, double * iofx2y=0,double * iofxy2=0,double *iofy3=0)=0;

  //No Doc (Please use this method as few as possible since it's very time consuming
  // : 0 : Full, 1 =Vmin, 2=Umax, 4=Vmax, 8=Umin, 15= AllSides,
  /*
  How to delete this : simply copy this !
  if(SapKVU)
  {
  delete [] SapKVU; 
  }
  SapKVU=0;
  if(SapKVV)
  {
  delete [] SapKVV;
  }
  SapKVV=0;
  if(GridOfCP &&oTableOfDestruction )
  {
  int Idx=0;
  for(int PV=0;PV<oNV;PV++)
  for(int PU=0;PU<oNU;PU++)
  {
  if(oTableOfDestruction[Idx] && GridOfCP[Idx])
  {
  delete GridOfCP[Idx];
  GridOfCP[Idx]=0; 
  }
  Idx++;
  }
  delete [] GridOfCP; GridOfCP=0;
  delete [] oTableOfDestruction; oTableOfDestruction=0
  }
  */

  

  virtual CATSobDiag GetInternalData(int Side,int &oNU, int & oNV,
    const CATSapKnotVector **& SapKVU, const CATSapKnotVector ** & SapKVV, 
    const char * & Orientation, CATMathGridOfPoints **& GridOfCP, char *& oTableOfDestruction)=0;  

  

  //Recupere toutes informations sur les parties extrapolees seulement (c'est une grille, la partie correspondant a la subdiv aura des pointeurs Null)
  // Attention ce sont des pointeurs sur des donnees internes donc PAS DE delete
  // oNu et oNv Correspondent a la taille totale du tableaux d'equation prenant donc en compte de la partie extrapolee
  // 
  virtual CATSobDiag GetAllExtrapolData(int &oNU, int & oNV,int &OffsetMinU, int &OffsetMaxU, int &OffsetMinV, int &OffsetMaxV,
    CATSapKnotVector * const*& SapKVU,  CATSapKnotVector * const* & SapKVV, 
    const char * & Orientation,  CATMathGridOfPoints * const*& GridOfCP)=0;


  //Get The internal Data but not the Gird Of Points to be uses in conjonction of ExtractOneGridFromCmpExtrapolData
  virtual CATSobDiag GetAllExtrapolParamData(int &oNU, int & oNV,int &OffsetMinU, int &OffsetMaxU, int &OffsetMinV, int &OffsetMaxV,
                                                           CATSapKnotVector * const*& SapKVU,  CATSapKnotVector * const* & SapKVV, 
                                                          const char * & Orientation) = 0;

  //Only get the Offset Size and Data Type (0 for uncompressed, 1 for compressed)
  virtual CATSobDiag GetExtrapolBasicParam(int &oNU, int & oNV,int &OffsetMinU, int &OffsetMaxU, int &OffsetMinV, int &OffsetMaxV,
                                           char & oCompressType) const= 0;

   // GetCompressedExtrapolData MainData[9] as
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
  // One can be helped with  ZoneDefinition tool in SapUtilities
  // Orientation are number in the full traditionnal form
  // Note : the methode try to compress if it's not already compressed 
  virtual CATSobDiag GetCompressedExtrapolData(const CATSapExtrapolData * & MainData, const char * & Orientation) =0 ;
  
  // PU dans [0,NU[ et PV dans [0,NV[
  virtual CATMathGridOfPoints * ExtractOneGridFromCmpExtrapolData(int iPU, int iPV) =0;

  //WARNING THIS METHOD UPDATE THE EQUATIONS
  // All Data are used internally after Set (no copy-> do not delete element)
  //After call, only delete the array eg delete []  SapKVU, but do not do delete SapKVU[i], since the pointer is used
  // The Internal Part of the Grid corresponding to the true subdivision part shoulb set to zero/Null
  // OffsetMinU,  OffsetMaxU,  OffsetMinV,  OffsetMaxV corresponding to the new data to be added to the equation 
  virtual CATSobDiag SetNewExtrapolData(int OffsetMinU, int OffsetMaxU, int OffsetMinV, int OffsetMaxV,
                                 CATSapKnotVector ** SapKVU, CATSapKnotVector ** SapKVV,
                                  const char * Orientation,CATMathGridOfPoints **GridOfCP)=0;

  //Delete Equation to save Memory footprint
  //Delete Local and Global equations
  // If FullDelete==0 then the HotZone in the PCCM area is kept
  virtual void DeleteEquations(int FullDelete=1) =0;
  //Force the Update of the equations (Will be removed if necessary and rebuild if necessary)
  virtual void Update()=0;

  virtual void CountCPsInMemoryForExtrapol(CATULONG32 &NbCPs, CATULONG32 &NbExtrapolPatch) const =0;
protected:
  CATSapSubdivGridSurface();
  
};


//Standard Creator
ExportedByCATSapApprox CATSapSubdivGridSurface * 
CATCreateSapSubdivGridSurface(const CATTolerance & TolObject,
                              CATSobMesh * SobMesh,
                              int iNU,int iNV,
                              CATSobFace * const *  oTabOfSobFace,
                              const double * iKnotsU, const double * iKnotsV);


//Creator With ExtrapolData (Do Not Use)
ExportedByCATSapApprox CATSapSubdivGridSurface * 
CATCreateSapSubdivGridSurfaceWithExtrapolData(const CATTolerance & nTol, CATSobMesh *iMesh, const int NU, const int NV, CATSobFace * const * iFaces,
                                  int NUKnots,const double * iKnotsU, int NbVKnots, const double * iKnotsV, 
                                  int OffsetMinU, int OffsetMaxU, int OffsetMinV, int OffsetMaxV,
                                  CATSapKnotVector ** SapKVU, CATSapKnotVector ** SapKVV,
                                   const char * Orientation,CATMathGridOfPoints **GridOfCP);

ExportedByCATSapApprox CATSapSubdivGridSurface * 
CATCreateSapSubdivGridSurfaceWithCompressedExtrapolData(const CATTolerance & nTol, CATSobMesh *iMesh, const int NU, const int NV, CATSobFace * const * iFaces,
                                  int NUKnots,const double * iKnotsU, int NbVKnots, const double * iKnotsV, 
                                  int OffsetMinU, int OffsetMaxU, int OffsetMinV, int OffsetMaxV,
                                   const char * Orientation, CATSapExtrapolData * ExtrapolData );

//Scale : <0 Auto, >0 Manual, =1 Same Has original
// OPtimised Copy
/*
ExportedByCATSapApprox CATSapSubdivGridSurface * 
CATCreateSapSubdivGridSurfaceFromAnotherOne(const CATTolerance & TolObject,
                                                        CATSobMesh * SobMesh,
                                                          CATSobFace *	Face,
                                                          unsigned char	Daughter,
                                       const double iScaleU, const double iScaleV,
                                       CATSapSubdivGridSurface * iSapSubbdivCellRef,
                                       CATMathTransformation * iOptionalMathTransfo=0);
                                       */

#endif


