//=============================================================================
// COPYRIGHT Dassault Systemes 2009
//=============================================================================
// CATMathOBB.h
// Oriented Bounding Box
// This class can represent any rectangular box in 3D space. 
// The box is composed  of a center expressed in the global axis system
//                      of 3 ORTHONORMAL directions expressed in the global axis system
//                      of the box' half diagonal expressed in the box' system
//=============================================================================
// 2009-02-05   JXO/XXC: New
// 2009-04-07   ZIB: create CATMathOBB based on CATPolyOBB
// 2010-03-23   ZIB: create CATMathOBB wrapper around new CATMathOBBBase class
// 2010-11-23   FDS: INLINE instead of inline
// 2014_03_05   JSX: Define for removing Float API in CATMathOBB
// 2014-10-10   KJD: Define for removing Float data
// 2020-02-06   JSX: ajout IsDefinedForStream
//=============================================================================
#ifndef CATMathOBB_H
#define CATMathOBB_H
#include "CATMathAdvancedBox.h"
#include "CATMathOBBBase.h"
#include "CATMathInline.h"



/**
 * Oriented bounding box
 * Note that boxes were stored using floats until the end of 2014 and using double after.
 */
class ExportedByCATMathematics CATMathOBB : public CATMathAdvancedBox
{
public:
  /**
   * Build an empty undefined OBB
   */
  CATMathOBB();

  /**
   * Build an OBB containing a given array of points
   * @param[in] iPointList the points.
   * @param[in] iSize the array's length.
   */
  CATMathOBB(const CATMathPoint   * iPointList,
                   int              iSize     );

  /**
   * Duplicate an OBB
   */
  CATMathOBB(const CATMathOBB     & iOBBToCopy);
  CATMathOBB(const CATMathOBBBase & iOBBToCopy);

  /**
   * Build an OBB from an axis aligned box.
   */
  CATMathOBB(const CATMathBox & iBoxToCopy);

  /**
   * Build an OBB
   * @param[in] iBasis 3 orthonormal directions
   * @param[in] iDiag the box' half diagonal (ie the vector between
   *                     its center and the top right corner)
   * @param[in] iCenter the box' center
   */
  CATMathOBB(const CATMathVector   iBasis[],
             const CATMathVector & iDiag   ,
             const CATMathPoint  & iCenter );

  INLINE virtual ~CATMathOBB() {};

  /**
   * @return the advanced box type (CATMathOBBType)
   */
         CATMathAdvancedBoxType GetType() const;

  /**
   * Test for intersection against another OBB
   * @param[in] iOBB the other OBB
   * @return 1 if the OBBs intersect, 0 if they don't, -1 upon error
   */
  INLINE int                    IsIntersecting(const CATMathOBB &iOBB) const;

  /**
   * Test for intersection against another OBB
   * @param[in] iOBB the other OBB
   * @param[in] iTolerance a tolerance used to inflate the boxes before testing for intersection
   *            Note that the boxes are inflated by the half tolerance
   * @return 1 if the OBBs intersect, 0 if they don't, -1 upon error
   */
  INLINE int                    IsIntersecting(const CATMathOBB &, double iTolerance) const;

  /**
   * Test for point inclusion 
   * @param[in] iPoint The point.
   * @param[in] iTolerance a tolerance used when testing for inclusion
   * @return 1 if the point is contained by the OBB inflated by iTolerance, 0 if it isn't, -1 upon error
   */
  INLINE int                    IsContaining(const CATMathPoint &, double iTolerance) const;

  /**
   * Get a box containing the OBB
   * @param[out] oBox the axis aligned box.
   */
  INLINE void                   GetBox(CATMathBox &oBox) const;

  /**
   * Inflate the OBB 
   * @param[in] iTol the absolute (as opposed to relative) inflation value.
   * Note that the box is inflated by increasing by iTol the box' half diagonal expressed in the box' system
   */
         void                   Inflate(double iTol);

  /**
   * Check if the OBB is defined.
   * @return TRUE if the OBB is defined, FALSE otherwise.
   */
  INLINE CATBoolean             IsDefined() const;

  /**
   * Evaluate the minimum square distance to a point.
   * @param[in] iPoint the point.
   * @return negative value upon error, the square distance otherwise.
   */
  INLINE double                 SquareDistanceTo(const CATMathPoint &iPoint) const;

  /**
   * Evaluate the minimum square distance to another OBB cloud.
   * @param[in] iOBB the other OBB cloud.
   * @return negative value upon error, the square distance otherwise.
   */
  INLINE double                 SquareDistanceTo(const CATMathOBB &iOBB) const;

  /**
   * Duplicate the current advanced box.
   * @return the copy
   */
         CATMathAdvancedBox   * Duplicate() const;
  
  /**
   * Define an OBB containing a given array of points
   * @param[in] iPointList the points.
   * @param[in] iSize the array's length.
   */
  INLINE HRESULT                DefineElements(const CATMathPoint * iPointList, int iSize);


#ifndef CATMathOBB_RemoveFloatAPI
  /**
   * @return the first direction
   */
  INLINE CATMathVectorf         U() const;
  /**
   * @return the second direction
   */
  INLINE CATMathVectorf         V() const;
  /**
   * @return the third direction
   */
  INLINE CATMathVectorf         W() const;

  /**
   * @return the box' center
   */
  INLINE CATMathVectorf         Center() const;
  /**
   * @return the box' half diagonal
   */
  INLINE CATMathVectorf         Diagonal() const;
#endif

  /**
  * @return the first direction expressed in the global axis system
  */
  INLINE CATMathVector          UDir() const;
  /**
  * @return the second direction expressed in the global axis system
  */
  INLINE CATMathVector          VDir() const;
  /**
  * @return the third direction expressed in the global axis system
  */
  INLINE CATMathVector          WDir() const;

  /**
  * @return the box' center expressed in the global axis system
  */
  INLINE CATMathPoint           CenterPoint() const;
  /**
  * @return the box' half diagonal expressed in the box' system
  */
  INLINE CATMathVector          BoxDiagonal() const;

  /**
   * Convert a point in the box' coordinate system to a global point
   * @param[in] iLocalPoint the point in the box' coordinate system
   * @return the point in the global coordinate system.
   */
  INLINE CATMathPoint           UVWtoXYZ(const CATMathPoint & iLocalPoint) const;
  /**
   * Convert a point in the global coordinate system to the box'
   * @param[in] iLocalPoint the point in the global coordinate system
   * @return the point in the box' coordinate system.
   */
  INLINE CATMathPoint           XYZtoUVW(const CATMathPoint & iGlobalPoint) const;

  /**
   * Convert a vector in the box' system to a global vector
   * @param[in] iLocalVector the point in the box' system
   * @return the vector in the global system.
   * Remark :
   * As it is a vector transformation, only the rotation is applied contrary to the APi with CATMathPoint
   */
  INLINE CATMathVector          UVWtoXYZv(const CATMathVector & iLocalVector) const;

  /**
   * Convert a vector of the global system to a vector of the box'system
   * @param[in] iLocalVector the vector in the global system
   * @return the vector in the box'system.
   * Remark :
   * As it is a vector transformation, only the rotation is applied contrary to the APi with CATMathPoint
   */
  INLINE CATMathVector          XYZtoUVWv(const CATMathVector & iGlobalVector) const;

  INLINE double                 SquareDistanceMin(const CATMathPoint & iPoint) const;
  INLINE double                 SquareDistanceMax(const CATMathPoint & iPoint) const;
  INLINE double                 SquareDistanceMin(const CATMathOBB & iOBB) const;
  INLINE double                 SquareDistanceMax(const CATMathOBB & iOBB) const;
  INLINE double                 MaxSquareDistanceTo(const CATMathPoint &) const;
  INLINE double                 MaxSquareDistanceTo(const CATMathOBB &) const;


   /**
   * Get the box' corners  in the global axis system
   * @param[out] oCornersList list of the corners
   */
        HRESULT                 GetCorners(CATLISTV(CATMathPoint) & oList) const;

  /**
  * Compute the coordinates of the box iOBB in the box' system
  * @param[in] iOBB the box to convert
  * @param[out] oOBB the initial box expressed in the this' system
  */
        void                    ConvertIn(const CATMathOBB& iOBB, CATMathOBB & oOBB) const;

/**
* Compute the coordinates in the box' system  of the point iSourceLocalPoint defined in the iSourceOBB's system. 
* @param[in] iSourceLocalPoint the point in the iSourceOBB' coordinate system to convert
* @param[in] iSourceOBB the initial box using to define iSourceLocalPoint
* @param[out] oLocalPoint the point in the box' coordinate system
*/
        void                    ConvertIn(const CATMathPoint & iSourceLocalPoint,
                                          const CATMathOBB   & iSourceOBB       ,
                                                CATMathPoint & oLocalPoint      ) const;

/**
* Compute the coordinates in the box' system of the center of the iSourceOBB box. 
* @param[in] iSourceOBB the box whose center has to be converted
* @param[out] oLocalCenter the center of the iSourceOBB box in the box' coordinate system
*/
        void                    ConvertCenterIn(const CATMathOBB   & iSourceOBB,
                                                    CATMathPoint & oLocalCenter) const;

/**
* Test if the iOBB box is included in the box' system within the tolerance iTolerance
* @param[in] iOBB The box to test.
* @param[in] iTolerance the tolerance 
* @return 1 if the box is contained , 0 if it isn't, -1 upon error
*/
        CATBoolean              IsContaining   (const CATMathOBB & iOBB,
                                                      double       iTolerance) const;

/**
* Compute in the global axis system the vector 
* from the point iSourceLocalPoint expressed in the box' system 
* to the point iTargetLocalPoint expressed in the iTargetOBB's system 
* @param[in] iSourceLocalPoint the first point of the vector expressed in  the box's coordinate system 
* @param[in] iTargetLocalPoint the target point of the vector expressed in the iTargetOBBs' coordinate system 
* @param[in] iTargetOBB the box where is defined iTargetLocalPoint 
* @param[out] oVector the vector in the global axis system
*/
        void                    GetVectorBetween(const CATMathPoint  & iSourceLocalPoint,
                                                 const CATMathPoint  & iTargetLocalPoint,
                                                 const CATMathOBB    & iTargetOBB       ,
                                                       CATMathVector & oVector          ) const;

  // Transformation
  friend ExportedByCATMathematics CATMathOBB operator * (const CATMathTransformation & iTransfo, const CATMathOBB & iOBB);
/*
* Compute the axis aligned box built if the box's axis was considered as the global axis system
* and the transformation which transforms the global axis system into the box'axis 
* i.e. the transformation to apply to the CATMathBox obox to obtain the box
* @return E_FAIL if an error occurs (invalid box, ...), <tt>S_OK</tt> otherwise. 
*/
  INLINE HRESULT                ConvertToBoxAndTransformation(CATMathBox & obox, CATMathTransformation & otransfo) const;
  INLINE HRESULT                Absorb                       (CATMathOBB & iobb);

         void                   ForceDirection               (CATBoolean);
         CATBoolean             IsDirectionForced            () const;

  enum OBBFlags
  {
    Initialized        = 1, // 2^0  : 01/2020 : ! not clearly used in the implementation 
    ForcedDirection    = 2, // 2^1  : USED
    IsDefinedForStream = 4  // 2^2  : Used to stream/unstream the box ! Please use IsDefined() in all other cases !
  };

  unsigned char Flags() const; // ZIB: Used for stream method only (Exposing internal stuff like this is ugly)

  /**
   * @return the OBB's volume
   */
  INLINE double                 Volume() const;

  
  INLINE CATMathOBB &operator =(const CATMathOBB & iOBBToCopy);

protected:
  CATMathOBBBase _OBB;
  unsigned char  _Flags;
};

ExportedByCATMathematics INLINE CATMathOBB operator * (const CATMathTransformation & iTransfo, const CATMathOBB & iOBB);

//=============================================================================
INLINE CATMathOBB::CATMathOBB(const CATMathOBB & iOBBToCopy)
: _Flags(iOBBToCopy._Flags),
  _OBB  (iOBBToCopy._OBB)
{}

//-----------------------------------------------------------------------------
INLINE CATMathOBB &CATMathOBB::operator =(const CATMathOBB & iOBBToCopy)
{
   _Flags = iOBBToCopy._Flags;
   _OBB   = iOBBToCopy._OBB;
   return *this;
}

//-----------------------------------------------------------------------------
INLINE CATMathOBB::CATMathOBB(const CATMathVector   Basis[],
                              const CATMathVector & Diag   ,
                              const CATMathPoint  & C      )
: _Flags(0),
  _OBB  (Basis, Diag, C)
{}

//-----------------------------------------------------------------------------
INLINE unsigned char CATMathOBB::Flags() const
{
   return _Flags;
}

//-----------------------------------------------------------------------------
INLINE CATBoolean CATMathOBB::IsDefined() const
{
   return _OBB.IsDefined();
}

//-----------------------------------------------------------------------------
#ifndef CATMathOBB_RemoveFloatAPI
INLINE CATMathVectorf CATMathOBB::U() const
{
   return _OBB.U();
}

//-----------------------------------------------------------------------------
INLINE CATMathVectorf CATMathOBB::V() const
{
   return _OBB.V();
}

//-----------------------------------------------------------------------------
INLINE CATMathVectorf CATMathOBB::W() const
{
   return _OBB.W();
}

//-----------------------------------------------------------------------------
INLINE CATMathPointf CATMathOBB::Center() const
{
   return _OBB.Center();
}

//-----------------------------------------------------------------------------
INLINE CATMathVectorf CATMathOBB::Diagonal() const
{
   return _OBB.Diagonal();
}
#endif

//-----------------------------------------------------------------------------
INLINE CATMathVector CATMathOBB::UDir() const
{
   return _OBB.UDir();
}

//-----------------------------------------------------------------------------
INLINE CATMathVector CATMathOBB::VDir() const
{
   return _OBB.VDir();
}

//-----------------------------------------------------------------------------
INLINE CATMathVector CATMathOBB::WDir() const
{
   return _OBB.WDir();
}

//-----------------------------------------------------------------------------
INLINE CATMathPoint CATMathOBB::CenterPoint() const
{
   return _OBB.CenterPoint();
}

//-----------------------------------------------------------------------------
INLINE CATMathVector CATMathOBB::BoxDiagonal() const
{
   return _OBB.BoxDiagonal();
}

//-----------------------------------------------------------------------------
INLINE CATMathPoint CATMathOBB::UVWtoXYZ(const CATMathPoint & iLocalPoint) const
{
   return _OBB.UVWtoXYZ(iLocalPoint);
}

//-----------------------------------------------------------------------------
INLINE CATMathPoint CATMathOBB::XYZtoUVW(const CATMathPoint & iGlobalPoint) const
{
   return _OBB.XYZtoUVW(iGlobalPoint);
}

//-----------------------------------------------------------------------------
INLINE CATMathVector CATMathOBB::UVWtoXYZv(const CATMathVector & iLocalVector) const
{
   return _OBB.UVWtoXYZv(iLocalVector);
}

//-----------------------------------------------------------------------------
INLINE CATMathVector CATMathOBB::XYZtoUVWv(const CATMathVector & iGlobalVector) const
{
   return _OBB.XYZtoUVWv(iGlobalVector);
}

//-----------------------------------------------------------------------------
INLINE HRESULT CATMathOBB::DefineElements(const CATMathPoint * iPointList, int iSize)
{
   return _OBB.DefineElements(iPointList, iSize);
}

//-----------------------------------------------------------------------------
INLINE int CATMathOBB::IsIntersecting(const CATMathOBB &iOBB) const
{
   return _OBB.IsIntersecting(iOBB._OBB);
}

//-----------------------------------------------------------------------------
INLINE int CATMathOBB::IsIntersecting(const CATMathOBB &iOBB, double iTolerance) const
{
   return _OBB.IsIntersecting(iOBB._OBB, iTolerance);
}

//-----------------------------------------------------------------------------
INLINE int CATMathOBB::IsContaining(const CATMathPoint &iPoint, double iTolerance) const
{
   return _OBB.IsContaining(iPoint, iTolerance);
}

//-----------------------------------------------------------------------------
INLINE void CATMathOBB::GetBox(CATMathBox &oBox) const
{
  _OBB.GetBox(oBox);
}

//-----------------------------------------------------------------------------
INLINE HRESULT CATMathOBB::ConvertToBoxAndTransformation(CATMathBox & oBox, CATMathTransformation & oTransfo) const
{
   return _OBB.ConvertToBoxAndTransformation(oBox, oTransfo);
}

//-----------------------------------------------------------------------------
INLINE HRESULT CATMathOBB::Absorb(CATMathOBB & iOBB)
{
   return _OBB.Absorb(iOBB._OBB);
}

//-----------------------------------------------------------------------------
INLINE double CATMathOBB::SquareDistanceTo(const CATMathPoint &iPoint) const
{
   return _OBB.SquareDistanceTo(iPoint);
}

//-----------------------------------------------------------------------------
INLINE double CATMathOBB::MaxSquareDistanceTo(const CATMathPoint & iPoint) const
{
   return _OBB.MaxSquareDistanceTo(iPoint);
}

//-----------------------------------------------------------------------------
INLINE double CATMathOBB::SquareDistanceTo(const CATMathOBB &iOBB) const
{
   return _OBB.SquareDistanceTo(iOBB._OBB);
}

//-----------------------------------------------------------------------------
INLINE double CATMathOBB::MaxSquareDistanceTo(const CATMathOBB &iOBB) const
{
   return _OBB.MaxSquareDistanceTo(iOBB._OBB);
}

//-----------------------------------------------------------------------------
INLINE double CATMathOBB::Volume() const
{
   return _OBB.Volume();
}

//-----------------------------------------------------------------------------
INLINE CATMathAdvancedBox *CATMathOBB::Duplicate() const
{
   return new CATMathOBB(*this);
}

//-----------------------------------------------------------------------------
INLINE CATMathOBB operator * (const CATMathTransformation & iTransfo, const CATMathOBB & iOBB)
{
   return CATMathOBB(iTransfo*iOBB._OBB);
}

#endif
