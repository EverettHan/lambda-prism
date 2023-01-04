#ifndef CATIPGMTopGNCommonEdgeData_h
#define CATIPGMTopGNCommonEdgeData_h

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopGNCommonTopologyData.h"
#include "CATTopDefine.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATTopology.h"

class CATEdge;
class CATBody;
class CATDomain;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopGNCommonEdgeData;

class ExportedByCATGMModelInterfaces CATIPGMTopGNCommonEdgeData : public CATIPGMTopGNCommonTopologyData
{
public:
  /**
   * @brief
   * Returns the common topology as a CATEdge
   *  
   * @return 
   * A pointer to the CATEdge common topology 
   */
  virtual CATEdge * GetCommonEdge() const = 0;

  /**
   * @brief
   * Returns the orientation of the common topology
   * 
   * @return 
   * A CATOrientation of the common topology 
   */
  virtual CATOrientation GetOrientation() const = 0;

  /**
   * @brief
   * Gets the upper domain that contain the common edge
   * 
   * @param 
   *  oUppDomain [out]
   * Upper domain that contain the common edge
   */
  virtual CATDomain * GetUpperDomain() const = 0;


protected:
  CATIPGMTopGNCommonEdgeData();

  virtual ~CATIPGMTopGNCommonEdgeData();

};

/**
 * @brief
 * Method to create a CATIPGMTopGNCommonEdgeData object.
 *
 * @param iCommonEdge
 * Common edge belonging to iBody
 * @param iBordFaceList
 * Border faces of iCommonEdge in iBody
 * @param iOrient
 * Orientation of iCommonEdge in iBody
 * @param iUppDomain
 * Upper domain that contains iCommonEdge
 *
 * @return
 * A pointer to a (interface) CATIPGMTopGNCommonEdgeData
 */
ExportedByCATGMModelInterfaces CATIPGMTopGNCommonEdgeData * CATIPGMCreateTopGNCommonEdgeData(CATEdge * iCommonEdge,
                                                                                             const ListPOfCATTopology & iBordTopoList,
                                                                                             const CATListOfInt & iBordTopoIndexList,
                                                                                             CATOrientation & iOrient,
                                                                                             CATDomain * iUppDomain);

#endif
