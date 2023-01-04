#ifndef CATGemSharpness_h
#define CATGemSharpness_h
#include "YI00IMPL.h"
#include "CATBoolean.h"
#include "CATMathConstant.h"
#include "CATGeoDef.h"
#include "CATTopDefine.h"
#include "ListPOfCATGemSharpness.h"
#include "CATCGMNewInterface.h"
#include "ListPOfCATFace.h"

//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2000
// Contexte de Vivicite : Edge, Face, Face
//=============================================================================
class CATGeoFactory;
class CATEdge;
class CATFace;
class CATShell;
class CATBody;

typedef struct 
{
  float           _param; // 0.0 to 1.0
  CATAngle        _Angle;
  CATTopSharpness _Sharpness;
}
CATLocalSharpness;

class CATHashTabCATGemSharpness;

class ExportedByYI00IMPL CATGemSharpness
{
public:
  CATGemSharpness(CATEdge *iEdge, CATFace *iFaceLeft,  CATOrientation iOriLeft,
    CATFace *iFaceRight, CATOrientation iOriRight, CATBody  *iBody, CATShell  *iShell);
  
  virtual ~CATGemSharpness();
  CATCGMNewClassArrayDeclare;  
  
  // pour evaluation globale et Locale 
  // avec comparaison pour mise en coherence
  //    rc=0 : probleme
  int  Run(CATShell *iDummyShell, int NumberOfSharpnessSamples);
  
  // pour gestion HashTable des Contextes 
  int IsEqual(const CATGemSharpness *other) const;
  unsigned int GetKey() const;
  

  // pour Generation de tous les contextes possibles d'un Body
  static void GetSharpnesses(CATBody *iBody, 
                     int NumberOfSharpnessSamples,
                     ListPOfCATGemSharpness &ioList,
                     CATBoolean OnlyAmbigous);
  
  // pour Generation de tous les contextes possibles de Sharpness d'une Factory
  static void GetSharpnesses(CATGeoFactory *iFactory, 
                     int NumberOfSharpnessSamples,
                     ListPOfCATGemSharpness &ioList,
                     CATBoolean OnlyAmbigous);
  
  // pour Generation de tous les contextes possibles de Sharpness 
  // d'une liste de Faces
  static void GetSharpnesses(CATLISTP(CATFace) &iFaces, 
                     int NumberOfSharpnessSamples,
                     ListPOfCATGemSharpness &ioList,
                     CATBoolean OnlyAmbigous);

  // Les donnees de definition d'une Vivicite Edge x Face x Face

  CATEdge            *_Edge;
  CATFace            *_Faces[2];
  CATOrientation      _Oris[2];

  CATBody            *_Body;
  CATShell           *_Shell;
  
  CATTopSharpness    _GlobalSharpness;
  
  CATBoolean         _GlobalIsFixed;
  CATBoolean         _GlobalComputed;
  CATBoolean         _LocalComputed;
  CATBoolean         _HasCompared;
  CATBoolean         _ComparisonOkay;

  int                 _NbLocal;
  CATLocalSharpness  *_LocalSharpness;

private :
  
  // pour Generation de tous les contextes possibles de Sharpness d'un Body
  static void GetSharpnesses(CATBody *iBody, CATHashTabCATGemSharpness  *isharpnesses,
                            CATBoolean iSpecifyTopologicalContext);
  
  static void GetIsolatedFaces(CATLISTP(CATFace) &iFaces, 
                               CATHashTabCATGemSharpness  *sharpnesses );

  static void ComputeSharpness(CATGeoFactory *iFactory,
                               CATBody       *iBody, 
                               CATHashTabCATGemSharpness  *sharpnesses,
                               int NumberOfSharpnessSamples,
                               ListPOfCATGemSharpness &ioList,
                               CATBoolean OnlyAmbigous);
};


#endif
