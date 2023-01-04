#ifndef CATlsoFaceUtil_H
#define CATlsoFaceUtil_H

// ++++ Includes ++++
#include "PersistentCell.h"
#include "CATBoolean.h"
#include "ListPOfCATFace.h"
#include "ListPOfListPOfCATFace.h"
#include "CATListOfULONG32.h"
#include "CATDataType.h"
#include "CATTopDefine.h"


// ++++ Predeclarations ++++
class CATGeoFactory;
class CATCGMStream;
class CATFace;
class CATSurface;
class CATMathTransformation;
class CATSurLimits;
class CATMathPoint;
class CATMathVector;
class CATSoftwareConfiguration;
class CATSurParam;
class CATFaceHashTable;
class CATLoop;
class CATEdge;
class CATICGMContainer;

//=============================================================================
// CATlsoFaceUtil
// 
// responsable: LAP
// 
// Classe utilitaire pour l'object Body. Elle ne contient que des methodes
// statiques pour le stream de body et des methodes de comparaison de geometries.
//=============================================================================

class ExportedByPersistentCell CATlsoFaceUtil
{
public:
  //---------------------------------------------------------------------------
  // METHODES STATIC
  //---------------------------------------------------------------------------

  static CATBoolean IsConfused2Surfaces(CATSurface                  & iS1,
                                        const CATSurLimits          & iUVBox1,
                                        CATSurface                  & iS2,
                                        const CATSurLimits          & iUVBox2,
                                        CATGeoFactory               * iFactory,
                                        CATSoftwareConfiguration    * iConfig);

  static CATBoolean Compare2Surfaces(CATSurface                  & iS1,
                                     const CATSurLimits          & iUVBox1,
                                     const CATMathTransformation & iTransfo,
                                     CATSurface                  & iS2,
                                     const CATSurLimits          & iUVBox2,
                                     CATGeoFactory               * iFactory,
                                     CATSoftwareConfiguration    * iConfig);

  static CATBoolean AreParallel(const CATMathVector & iV1,
                                const CATMathVector & iV2,
                                const double          iTolForAngle);

  static CATBoolean IsPointOnSurface(CATGeoFactory& iFactory, CATSoftwareConfiguration& iConfig, CATMathPoint& iPoint, const CATSurface& iSurface, const CATSurLimits& iLimits, const double iTolForLengthTest);

  static CATBoolean IsPointOnSurface(CATGeoFactory& iFactory, CATSoftwareConfiguration& iConfig, CATMathPoint& iPoint, const CATSurface& iSurface, const CATSurLimits& iLimits, const double iTolForLengthTest, CATSurParam & oSurParam);

  static CATLoop * GetExternalLoop(CATFace & iFace);

  static CATLoop * GetLoop(CATFace & iFace, CATEdge & iEdge, CATOrientation * ioOrientation=NULL);

  //-------------------------------------------------------------------------------------------------------
  // ListPOfCATFace
  //-------------------------------------------------------------------------------------------------------
  // Stream(List)
  static void StreamFaceList(const ListPOfCATFace & iFaceList, CATCGMStream& ioStr);
  static void StreamFaceHT(const CATFaceHashTable & iFaceHT, CATCGMStream& ioStr);
  static void StreamFaceListTags (const ListPOfCATFace & iFaceList, CATCGMStream& ioStr);
  static void StreamFace(const CATFace * iFace, CATCGMStream& ioStr);
  static void StreamFaceTag (const CATFace * iFace, CATCGMStream& ioStr);
  static void PutColorOnFaceList(const ListPOfCATFace & iFaceList, int red, int green, int blue);
  static void PutColorOnFaceHT(const CATFaceHashTable & iFaceHT, int red, int green, int blue);

  static void StreamListOfFaceList(const ListPOfListPOfCATFace & iListOfFaceList, CATCGMStream& ioStr);

  // UnStream(List)
  static void UnStreamFaceList(ListPOfCATFace & oFaceList, CATCGMStream& ioStr, CATGeoFactory * iFactory, CATBoolean iPutSelectColor=FALSE);
  static void UnStreamFaceHT(CATFaceHashTable & oFaceHT, CATCGMStream& ioStr, CATGeoFactory * iFactory, CATBoolean iPutSelectColor=FALSE);
  static void UnStreamFaceTagList (CATListOfULONG32 & oFaceTagList, CATCGMStream& ioStr);
  static CATFace * UnStreamFace(CATCGMStream& ioStr, CATICGMContainer * iFactory);
  static CATULONG32 UnStreamFaceTag (CATCGMStream& ioStr);
  static void UnStreamListOfFaceList(ListPOfListPOfCATFace & oListOfFaceList, CATCGMStream& ioStr, CATGeoFactory * iFactory);
};

#endif /* CATlsoFaceUtil_H */
