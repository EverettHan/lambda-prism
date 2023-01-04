//====================================================================
// Copyright Dassault Systemes Provence 2008, all rights reserved 
//====================================================================
//
// Class Singleton : Une seule instance par session ! permettant de fournir des SapKnotVector qui reviennent tres souvent dans les subdivisions
// Permet d'avoir une seule instance du KV pour des milliers de surfaces
// La construction/destruction des KV est gere par cette classe "Factory"

// 
//======================================================================
// 18/06/2008 : RNO : Creation
//======================================================================
#ifndef CATSapConstantsFactory_H
#define CATSapConstantsFactory_H 
#include "CATIACGMLevel.h"

//Pour l'export
#include "CATSapApprox.h"

#include "CATCGMOutput.h"
#include "CATDataType.h"
#include "CATSapApprox.h"
#include "CATSapKnotVector.h"
#include "CATSobFace.h"


#include "CATSapConstantsTypes.h"

class CATMathNxNBandSymMatrix;
class CATSapKnotVectorAuto;
class CATSapConstantsFactory;
class CATSapChainFactory;
class CATSapConstantsMonoLevelFactory;


ExportedByCATSapApprox
CATSapConstantsFactory & GetSapKVFactory();





//The CATSapConstantsFactory chain several MonoLevelFactory
class ExportedByCATSapApprox CATSapConstantsFactory
{
public:
  CATSapConstantsFactory();
  ~CATSapConstantsFactory();
   //Return The KnotVector associate to this Face
  // If aimed to be called a lot please consider to use the method below from the type
  // An AddRef is Done on the CATSapKnotVectorAuto
  CATSapKnotVectorAuto * GetSapKnotVector(CATSobFace * iFace, short iDaughterIdx=0, short iLevel=2);
  
  //Return The KnotVector from The Type (a little bit faster than the above one)
  CATSapKnotVectorAuto * GetSapKnotVectorFromSapKVType(const CATSAPKVType Type, short iLevel=2);

  //Return The KnotVector Type
  CATSAPKVType GetSapKVTypeFromSobFace(CATSobFace * iFace, short DaughterIdx=0, short iLevel=2) const;

  //Return the Precomputed Result Structure
  const CATSAPChangeKVResult * GetSapChangeKnotOneComputeResultFromType(const CATSAPChangeKVType Type, short iLevel=2);

  //Return the Precomputed Result Structure :
  // @Param iCopyNoCopyMode : 0 ==> NoCopyMode les resultats  NE DOIVENT PAS ETRE DETRUIT !!!
  //                          1 ==> Copy : les resultats sont copies et les tableaux DOIVENT ETRE DETRUIT (Exception : Oldbase, OldPol)
  void GetSapChangeKnotOneComputeResultFromType(const CATSAPChangeKVType Type, short iLevel, int iCopyNoCopyMode,
                          int                       & oSizeOfTransfPol,
                          double                   *& oTransfPol,
                          int                       & oSizeOfoTabImp,
                          int                      *& oTabImp,
                          int                      *& oOldBase,
                          int                       & oPeriodic,
                          CATMathNxNBandSymMatrix  *& oNewMat,
                          int                       & oWhichDer,
                          int                       & oNewSize,
                          CATMathPolynomX         **& oNewPol,
                          CATMathPolynomX         **& oOldPol,
                          CATMathNxNBandSymMatrix  *& oTempMat, 
                          CATMathNxNBandSymMatrix  *& oFactoCholesky, 
                          int                       & oerror) ;


  //Declare you use a Factory
  void AddRefMonoLevelFactory(short Level=2);
  //Declare you free a Factory
  void ReleaseMonoLevelFactory(short Level=2);
  
  
  
private :

  CATSAPKVType EstimateTriQuadKnotVector(CATSobFace *iFace, short iLevel=2) const;
  CATSAPKVType EstimateQuadKnotVector(CATSobFace *iFace, short iLevel=2) const;
  CATSapConstantsMonoLevelFactory * GetMonoLevelFactory(short Level=2);
  class CATSapChainFactory
  {
  public:
    CATSapChainFactory():_NextFactory(0),_TheFactory(0){};
    ~CATSapChainFactory()
    {
      _TheFactory=0;
      _NextFactory=0;
    }

    CATSapConstantsMonoLevelFactory * _TheFactory;
    CATSapChainFactory * _NextFactory;
  };

  CATSapChainFactory * _FirstFactory;
  CATSapConstantsMonoLevelFactory * _CurrentFactory;
};




//  
#endif
