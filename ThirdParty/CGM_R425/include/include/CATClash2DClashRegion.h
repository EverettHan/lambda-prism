//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014
//=============================================================================
//
// CATClash2DClashRegion:
//    Header file for CATClash2D body-body clash region.
//
//=============================================================================
// Usage notes:
//=============================================================================
// 17/03/14 : XMH : Creation.
// 02/07/14 : XMH : GetBodies, Caller body id.
// 10/01/17 : F1Z : Add master/slave information.
// 07/02/17 : F1Z : Add master/slave computation status.
//=============================================================================
#ifndef CATClash2DClashRegion_H
#define CATClash2DClashRegion_H

// Export
#include "Clash2D.h" // for ExportedByClash2D

// Clash
#include "CATClash2D.h"

// Misc.
#include "CATBoolean.h"

// Streaming
#include "CATCGMOutput.h"
#include "CATCGMStream.h"

// Classes
class CATBody;
class CATEdge;
class CATMathPoint2D;
class CATMathDirection2D;

class ExportedByClash2D CATClash2DClashRegion
{
public:
  // CATClashRegionMasterSlaveStatus describes the master slave computation status
  /** Master Slave computation status
  * @param <tt>CATClashRegion_Unknown</tt>
  * The master/slave computation hasn't been launched.
  * @param <tt>CATClashRegion_InternalError</tt>
  * The computation has faced an inconsistency. The issue is inside the clashregion master slave computation.
  * @param <tt>CATClashRegion_OK</tt>
  * The computation didn't face any issue and a result is avalaible.
  * @param <tt>CATClashRegion_WarningPenetration</tt>
  * The segmentation is OK but no segment projection was directly found. The resulting segmentations is obtained by prospection around the crossings.
  * @param <tt>CATClashRegion_NoPenetration</tt>
  * The segmentation is OK but it was impossible to find a segment projecting on the slave border.
  */
   typedef enum 
  {
     CATClashRegion_Unknown               = -2,
     CATClashRegion_InternalError,      //= -1
     CATClashRegion_OK,                 //=  0
     CATClashRegion_WarningPenetration, //=  1
     CATClashRegion_NoPenetration       //=  2
     
  } CATClashRegionMasterSlaveStatus;

  //-----------------------------------------------------------------------
  //- Object Management
  //-----------------------------------------------------------------------
  // Constructors
  CATClash2DClashRegion();

  // Destructor
  virtual ~CATClash2DClashRegion();

  //-----------------------------------------------------------------------
  //- Results Methods
  //-----------------------------------------------------------------------

  /**
  * Gets the resulting clash classification for the region.
  * @return
  * The clash classification.
  */      
  virtual CATClash2D::CATClash2DClassification GetClashClassification() const = 0;

  /**
  * Get the bodies involved in the clash.
  * @param oBody1
  * The first body.
  * @param oCallerBodyId1
  * The user Id of the first body.
  * @param oBody1
  * The second body.
  * @param oCallerBodyId2
  * The user Id of the first body.
  */
  virtual void GetBodies(CATBody   *& oBody1,
                         CATLONG32  & oCallerBodyId1,
                         CATBody   *& oBody2,
                         CATLONG32  & oCallerBodyId2) const = 0;

  // Penetration data
  // ----------------------------------------------------------------
  /**
  * Gets the number of clash penetration data.
  */
  virtual CATLONG32 GetNumberOfPenetrationData() const = 0;

  /**
  * Initializes the iterator for accessing the clash penetration data.
  */
  virtual void BeginPenetrationData() const = 0;

  /**
  * Sets the iterator to point at the next penetration data.
  * @return
  * TRUE if there is data,
  * FALSE if the end of the data has been reached.
  */
  virtual CATBoolean NextPenetrationData() const = 0;

  /**
  * Gets the penetration data at the current iterator position.
  * @param oPenetrationEdge
  * The edge of body 1.
  * @param oPenetrationParam
  * The parameter of oPenetrationEdge.
  * @param oPenetrationPoint
  * The 2D penetration point.
  * @param oPenetrationDirection
  * The 2D penetration direction.
  * &param oPenetrationDepth
  * The penetration depth.
  * @return
  * TRUE if the penetration data is successfully retrieved,
  * FALSE otherwise.
  */
  virtual CATBoolean GetPenetrationData( CATEdge            *& oPenetrationEdge,
                                         CATCrvParam         & oPenetrationParam,
                                         CATMathPoint2D      & oPenetrationPoint,
                                         CATMathDirection2D  & oPenetrationDirection,
                                         double              & oPenetrationDepth ) const = 0;

  // Master/Slave border segmentation
  // ----------------------------------------------------------------
  virtual CATClashRegionMasterSlaveStatus GetMasterSlaveStatus               ()                                    const = 0;
  virtual CATBoolean                      IsFirstBodyMaster                  ()                                    const = 0;
  virtual void                            GetMasterBorderLength              (double & oSemgentsLength,
                                                                              double & oEdgesLength   )            const = 0;

  virtual void                            GetSlaveBorderLength               (double & oEdgesLength   )            const = 0;

  // Get the number of clash master border segmentation
  virtual CATLONG32                       GetNumberOfMasterBorderSegment     ()                                    const = 0;

  virtual void                            BeginMasterBorderSegment           ()                                    const = 0;

  virtual CATBoolean                      NextMasterBorderSegment            ()                                    const = 0;

  virtual CATBoolean                      GetMasterBorderSegment             (CATMathPoint2D     & oSegmentCenter,
                                                                              CATMathDirection2D & oNormal       ,
                                                                              double             & oSegmentLength,
                                                                              double             & oEdgeLength   ,
                                                                              double             & oPenetration  ) const  = 0;

  // Crossing
  // ----------------------------------------------------------------
  /**
  * Gets the number of clash crossings.
  */
  virtual CATLONG32 GetNumberOfCrossings() const = 0;

  /**
  * Initializes the iterator for accessing the clash crossings.
  */
  virtual void BeginCrossing() const = 0;

  /**
  * Sets the iterator to point at the next crossing.
  * @return
  * TRUE if there are crossings,
  * FALSE if the end of the crossings has been reached.
  */
  virtual CATBoolean NextCrossing() const = 0;

  /**
  * Gets the crossing at the current iterator position.
  * @param oCrossingEdge1
  * The crossing edge of body 1.
  * @param oCrossingParam1
  * The crossing parameter of oCrossingEdge1
  * @param oCrossingEdge2
  * The crossing edge of body 2.
  * @param oCrossingParam2
  * The crossing parameter of oCrossingEdge2
  * @param oCrossingPoint
  * The 2D crossing point
  * @param oCrossingDirection
  * The 2D crossing direction at oCrossingPoint
  * @return
  * TRUE if the crossing data is successfully retrieved,
  * FALSE otherwise.
  */
  virtual CATBoolean GetCrossing( CATEdge            *& oCrossingEdge1, 
                                  CATCrvParam         & oCrossingParam1, 
                                  CATEdge            *& oCrossingEdge2, 
                                  CATCrvParam         & oCrossingParam2,
                                  CATMathPoint2D      & oCrossingPoint,
                                  CATMathDirection2D  & oCrossingDirection ) const = 0;
};

#endif
