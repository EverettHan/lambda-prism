// ----------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// ST5: Feature recognition -- Extrusion Primitives -- | Data Family Level |
// PRL: Ajout des infos pour decorations + des infos pour openwall
// ----------------------------------------------------------------------------//

#ifndef CATGMLiveExtrusionPrimitive_H
#define CATGMLiveExtrusionPrimitive_H

#include "CATMathInline.h"
#include "CATSysErrorDef.h"

#include "CATGMModelInterfaces.h"
#include "CATDRepSeed.h"

#include "CATMathVector.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATGMLiveExtrusionPrimitive.h"
#include "CATBoolean.h"
#include "CATListOfInt.h"

class CATFace;
class CATGMLiveSeparatedHolePrimitive;

class ExportedByCATGMModelInterfaces CATGMLiveExtrusionPrimitive: public CATDRepSeed
{
public:
  enum AdjConvexityType
  {
    Unknown = 0,
    FullCvx,
    FullCcv,
    MixedSharp // Cvx + Ccv   
  };

public: 
  CATGMLiveExtrusionPrimitive(CATMathVector &iDir, ListPOfCATFace &iRepFaces); 
  virtual ~CATGMLiveExtrusionPrimitive();

  //Set methods
  void SetPrimitiveVector(CATMathVector &iDir);
  void SetPrimitiveExtrude(ListPOfCATFace &iFaces);
  void AddPrimAdjacentFaces(ListPOfCATFace &iFaces, AdjConvexityType iType, ListPOfCATFace *iDecoFaces = NULL); // do not use with SetPrimitiveSupport/Clog/Exit, or SetPrimDecoSupport/Clog/Exit
  void SetExtrusionType  (int iType);
  void SetClosureType    (int iType);
  void SetLocalType      (int iType);
  void SetLocalAngle     (CATAngle iAg);
  void SetDraftType      (int iType);
  void SetDraftAngle     (CATAngle iAg);  

  //Get methods
  void GetPrimitiveVector(CATMathVector &oDir);
  void GetPrimitiveExtrude(ListPOfCATFace &oFaces);
  int  GetNbAdjFacesLists();
  void ResetPrimAdjacentFaces();
  void NextPrimAdjacentFaces(ListPOfCATFace &oFaces, AdjConvexityType& oType, ListPOfCATFace *oDecoFaces = NULL);
  void GetExtrusionType(int &oType);  

  //Analysis methods
  virtual CATBoolean IsProtrusion();
  virtual CATBoolean IsDepresion();
  CATBoolean IsClosed();
  CATBoolean IsOpen();
  CATBoolean IsLocal();
  CATBoolean IsDrafted_Constant();
  CATBoolean IsDrafted_FullCnes();
  CATAngle   GetDraftAngle();     // do not call if IsDrafted_Constant is not TRUE
  CATAngle   GetLocalAngle();     // do not call if IsLocal is not TRUE

  void GetRep(ListPOfCATFace &oRepFaces);
  CATBoolean HasInRep(CATFace &iFace) const;
  CATBoolean HasSameRepAs(CATGMLiveExtrusionPrimitive &iPrimitive);

  static CATGMLiveExtrusionPrimitive * Locate(CATFace &iFace, ListPOfCATGMLiveExtrusionPrimitive &iPrimitive);
  static void GetAllReps(ListPOfCATGMLiveExtrusionPrimitive &iPrimitive, ListPOfCATFace &ioReps);
  static void RemoveDuplicates(ListPOfCATGMLiveExtrusionPrimitive &iPrimitive);

  // Decorations
  void SetDecorationType (int iType);
  void SetInnerFillets   (int iType);
  CATBoolean IsDecorated();
  CATBoolean IsFilleted();
  CATBoolean IsChamfered();
  CATBoolean HasInnerFillets();

  // Specialisation
  void SetRecogType      (int iType);
  CATBoolean IsPossibleNotch();

  // Openwall
  void SetOwlType        (int iType);
  void SetOwlEntryFaces  (ListPOfCATFace &iFaces);
  CATBoolean IsOpenWall();
  void GetOwlEntryFaces  (ListPOfCATFace &oFaces);

  //Get method by RL1
  virtual CATGMLiveSeparatedHolePrimitive *GetAsSeparatedHolePrimitive();



protected:
  void SetRep(ListPOfCATFace &iRepFaces);

private:
  int _FacesCount;
  CATFace** _Faces;

  CATMathVector     _ExtrudeDir; //extrusion direction
  ListPOfCATFace    _ExtrudedFaces; //extruded faces
  //ListPOfCATFace    _SupportFaces; //support of the extrusion profile
  //ListPOfCATFace    _ClogFaces; //clog of the extrusion profile
  //ListPOfCATFace    _ExitFaces; //exit of the extrusion profile
  int               _NbAdjLists;
  ListPOfCATFace    _TAdjFaces[2];  // Aujourd'hui limite a 2 listes, mais evolutions possibles
  ListPOfCATFace    _TDecFaces[2];  // Aujourd'hui limite a 2 listes, mais evolutions possibles
  AdjConvexityType  _TAdjTypes[2];  // Aujourd'hui limite a 2 listes, mais evolutions possibles
  int               _AdjIndex;      // Index de lecture
  int               _ExtrusionType; //type of extrusion: 0=Unknown, 1=Protrusion, 2=Blind Depression, 3=Through depression, 4=External (protrusion socle),                                     
  int               _ClosureType;   //type of closure:   0=Unknown, 1=Closed,     2=Open    (Closed = la skin des faces d'extrusion est un ruban ferme)  
  int               _LocalType;     // 1=extrusion locale, 0=extrusion standard

  // Decorations
  //ListPOfCATFace    _SupportDecoFaces; // decoration for support of the extrusion profile
  //ListPOfCATFace    _ClogDecoFaces;    // decoration for clog of the extrusion profile
  //ListPOfCATFace    _ExitDecoFaces;    // decoration for exit of the extrusion profile
  int               _DecoType;         // type of decoration:   0=None or not recognized, 1=Fillet,  2=Chamfer, ...
  int               _InnerFltType;     // type de fillets internes: 0=None or part of the extrusion, 1=Cylindrical Fillets on full planar extrusion
  int               _RecogType;        // cf. CATTopRecExtTyp 
  int               _DraftType;        // 0: non drafted, 1: tappered, 2: cone, 3: geo, 4: full planes
  CATAngle          _DraftAngle;

  // Openwall
  int               _OwlType;          // type d'openwall:   0=Unknown, 1=Pad/Pocket, 2=? (Slot? a voir, pb de specs)
  ListPOfCATFace    _OwlEntryFaces;    // exit of the extrusion profile

};


#endif

