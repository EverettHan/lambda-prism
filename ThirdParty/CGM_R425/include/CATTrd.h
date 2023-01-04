/* -*-C++-*- */
#ifndef CATTrd_H
#define CATTrd_H
// COPYRIGHT DASSAULT SYSTEMES 2014

//===================================================================
//===================================================================
//
// CATTrd: Trihedron dedicated to mapping of exact BRep. CGMinternal use only. Do not use.
//
//===================================================================
//===================================================================
// April 2014    Creation                         R. Rorato
//===================================================================

#include "CATMathematics.h"
#include "CATCGMVirtual.h"
#include "CATCGMNewArray.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "ListPOfCATTrd.h"
#include "CATLISTV_CATMathTransformation.h"

class CATMathTransformation;
class CATPrTrd;
class CATTrdChk;
class CATTrdDic;

#define CATTrdCylindicalHoleTypeId 255
#define CATTrdDiskTypeId           254
#define CATTrdCylinderTypeId         3

class ExportedByCATMathematics CATTrd : public CATCGMVirtual
{
public:

  //------------------------------------------------------------------------------
  // Object Management
  //------------------------------------------------------------------------------
  enum SimilarityType {AnyType, PositiveSimilarity, NegativeSimilarity, PositiveIsometry, PlanarSymmetry, Mirror, Translation}; // Warning: PlanarSymmetry may include a translation too
  enum VertexType {SharpVertex = 0, SmoothVertex = 1, InternalEdgeVertex = 2, KnifeVertex = 3, AxisVertex = 4, AnisotropyVertex = 5};
  CATTrd(const CATMathPoint& iOrigin, const CATMathVector& iV1, const CATMathVector& iV2, const CATMathVector& iV3, const VertexType iVertexType);
  CATTrd();
  CATTrd(unsigned char* iStream, int& ioStreamPosition, CATTrdDic* iDic, const unsigned char iStreamLevel);
  virtual ~CATTrd();
  CATCGMNewClassArrayDeclare;        // Pool allocation

  //------------------------------------------------------------------------------
  // Put this into stream
  //------------------------------------------------------------------------------
  void Stream(unsigned char*& oStream, int& ioStreamPosition, const unsigned char iStreamLevel);
  int GetStreamSize(const int iStreamLevel);

  //------------------------------------------------------------------------------
  // Generic Utilities
  //------------------------------------------------------------------------------
  static void StabilizeOrientation(CATMathVector& ioNormedVector);

  //------------------------------------------------------------------------------
  // Compare this and iTransfoOnTrd(iTrd)
  //------------------------------------------------------------------------------
  CATBoolean IsEqual(const CATMathTransformation &iTransfoOnTrd, CATTrd& iTrd, const double iTolForAngleTest, const double iTolForSquareLengthTest, int Debug = 0);

  //------------------------------------------------------------------------------
  // Compare 2 CATTrd sets (iTrds1[] with regards to iTransfo*iTrds2[])
  // iPerCentRequired==1 means one equal Trd is enough to return FALSE
  // iPerCentRequired==100 means all Trds are equal 
 //------------------------------------------------------------------------------
  static CATBoolean CompareTrds(ListPOfCATTrd& iTrds1, const double iSize1, const CATMathTransformation& iTransfo, ListPOfCATTrd& iTrds2, const double iSize2, const double iTolForAngleTest, const double iTolForSquareLengthTest, const int iMinCount, int Debug = 0);

  //------------------------------------------------------------------------------
  // Find out Transformations so that iTransfo * iTrds1 = iTrds2
  // if ( NULL==iChecker ) then Check is performed on Trihedrons
 //------------------------------------------------------------------------------
  static CATBoolean AreSimilar(ListPOfCATTrd& iTrds1, CATTrd* iAnisotropy1, const double iSize1, const CATMathTransformation& iTransfo, ListPOfCATTrd& iTrds2, CATTrd* iAnisotropy2, const double iSize2, const double iTolForAngleTest, const double iTolForSquareLengthTest, CATTrdChk* iChecker, const CATTrd::SimilarityType iSimilarityType, CATLISTV(CATMathTransformation)& oTransfoFromTrds1ToTrds2);

  //------------------------------------------------------------------------------
  // Copy iTrds as a list of CATTrd (static type)
 //------------------------------------------------------------------------------
  static void Copy(ListPOfCATTrd& iTrds, ListPOfCATTrd& oTrds);

  //------------------------------------------------------------------------------
  // Data access (1<=iVector<=3)
  //------------------------------------------------------------------------------
  INLINE       CATMathVector& GetVector    (const int iVector) { return _Vector[iVector-1]; };
  INLINE const CATMathPoint&  GetOrigin    (                 ) { return _Origin           ; };
  INLINE const VertexType     GetVertexType(                 ) { return _VertexType       ; };
  //------------------------------------------------------------------------------

  // Assign Point or Vector index in Dictionary
  //------------------------------------------------------------------------------
  void SetDicIndex(const int iWhichIndex, const int iDicIndex); // 0 for Origin, 1, 2 or 3 for Vectors
  int GetDicIndex(const int iWhichIndex); 
  
  //------------------------------------------------------------------------------
  // Customization methods
  //------------------------------------------------------------------------------
  virtual CATBoolean IsSameSurfaceType(const CATTrd& iTrd); // Default is True
  virtual CATBoolean IsFromSameVertex(const CATTrd& iTrd); // Default is False
  virtual CATPrTrd* GetAsCATPrTrd() const;

  //------------------------------------------------------------------------------
  // Utilities
  //------------------------------------------------------------------------------
  static CATBoolean GetCenter(ListPOfCATTrd& iTrds, CATMathPoint& oCenter);

  static CATBoolean AreEqual(const CATMathTransformation& iT1,
                             const CATMathTransformation& iT2,
                             const double iDistanceTol, // Tolerance on every translation coef
                             const double iAngleTol); // Tolerance on every matrix coef

  static CATBoolean IsAMirror(const CATMathTransformation& iTransfo, const double iTolForSquareLengthTest);

  //------------------------------------------------------------------------------
  // Stream utilities
  //------------------------------------------------------------------------------
  static void          WriteUChar  (      unsigned char* oStream, int& ioStreamPosition, const unsigned char iToWrite); 
  static void          WriteShort  (      unsigned char* oStream, int& ioStreamPosition, const short         iToWrite); 
  static void          WriteInt    (      unsigned char* oStream, int& ioStreamPosition, const CATLONG32     iToWrite); 
  static void          WriteDoubles(      unsigned char* oStream, int& ioStreamPosition, const double*       iToWrite, const int iNumberToWrite); 
  static unsigned char ReadUChar   (const unsigned char* iStream, int& ioStreamPosition); 
  static short         ReadShort   (const unsigned char* iStream, int& ioStreamPosition); 
  static CATLONG32     ReadInt     (const unsigned char* iStream, int& ioStreamPosition); 
  static void          ReadDoubles (const unsigned char* iStream, int& ioStreamPosition, double* iToRead, const int iNumberToRead); 

  //------------------------------------------------------------------------------
  // Rectifies geometry. 
  //------------------------------------------------------------------------------
  static void Rectify(ListPOfCATTrd& iTrds, CATTrdDic* iDic);

  //------------------------------------------------------------------------------
  // Debug methods
  //------------------------------------------------------------------------------
  void Dump(ostream& oStream) const;

  //==============================================================================
  // Protected section
  //==============================================================================
protected:

  //------------------------------------------------------------------------------
  // Rectifies geometry. 
  //------------------------------------------------------------------------------
  void Rectify(const int iVector, const CATMathVector& iNormalizedDirection, const int iDicIndex);
  void Rectify(const CATMathPoint& iOrigin, const int iDicIndex);

  //------------------------------------------------------------------------------
  // Measure "distance" between iTrd1 & iTransfo*iTrd2 
  //------------------------------------------------------------------------------
  static double XProduct(const CATTrd & iTrd1, const CATMathTransformation& iTransfo, const CATTrd & iTrd2, const SimilarityType iSimilarityType, const double iTolForSquareLengthTest);
  static double Product (const CATTrd & iTrd1, const CATMathTransformation& iTransfo, const CATTrd & iTrd2);
  static double Symmetry(const CATTrd & iTrd1, const CATMathTransformation& iTransfo, const CATTrd & iTrd2);
  static double PMirror (const CATTrd & iTrd1, const CATMathTransformation& iTransfo, const CATTrd & iTrd2, const double iTolForSquareLengthTest);

  //==============================================================================
  // Private section
  //==============================================================================
private:

  //------------------------------------------------------------------------------
  // Returns whether oTransfoFromThisToInputTrd exists so that oTransfoFromThisToInputTrd(this) == iTrd 
  //------------------------------------------------------------------------------
  CATBoolean IsIsometric          (const double iSizeofThis, const CATMathTransformation &iTransfoOnTrd, CATTrd& iTrd, const double iSizeOfTrd, const int iTransfoSign, const double iTolForAngleTest, const double iTolForSquareLengthTest, CATLISTV(CATMathTransformation)& oTransfoFromThisToInputTrd);

  //------------------------------------------------------------------------------
  // Fast implementation
 //------------------------------------------------------------------------------
  CATBoolean IsIsometric(CATTrd& iTrd, const double iTolForAngleTest);
  CATBoolean IsIsometric(CATMathPoint& iPoint1, CATMathVector  iVector1[3], const double iSize1, const CATMathTransformation &iTransfoOnTrd, CATMathPoint& iPoint2, CATMathVector  iVector2[3], const double iSize2, const int iTransfoSign, const double iTolForAngleTest, const double iTolForSquareLengthTest, CATLISTV(CATMathTransformation)& oTransfoFromThisToInputTrd);
  CATBoolean IsIsometric(CATMathPoint& iPoint1, CATMathVector& iVector1   , const double iSize1, const CATMathTransformation &iTransfoOnTrd, CATMathPoint& iPoint2, CATMathVector& iVector2   , const double iSize2, const int iTransfoSign, const double iTolForAngleTest, const double iTolForSquareLengthTest, CATLISTV(CATMathTransformation)& oTransfoFromThisToInputTrd);

  //------------------------------------------------------------------------------
  // Data
  //------------------------------------------------------------------------------
  CATMathPoint          _Origin;
  CATMathVector         _Vector[3];
  CATAngle              _Angle;    // Performances only
  int                   _DicIndex[4];
  VertexType            _VertexType;
};

#endif
