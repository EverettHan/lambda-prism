#ifndef CATIPGMTopGNCommonTopologyData_h
#define CATIPGMTopGNCommonTopologyData_h

#include "CATIPGMVirtual.h"
#include "CATGMModelInterfaces.h"

#include "ListPOfCATTopology.h"
#include "CATListOfInt.h"


class CATBody;
class CATTopology;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopGNCommonTopologyData;


/**
 * Class defining the data structure to handle informations of a CommonEdge in 
 * the context of Generic Naming.
 * 
 * @warning 
 *  The data structure must not be used outside of the Generic Naming context.
 * For internal use only.
 * 
 * @details
 *  The data structure contains a CATTopology object which is common with a list of CATTopology lists.
 * 
 * It is streamable.
 */
class ExportedByCATGMModelInterfaces CATIPGMTopGNCommonTopologyData : public CATIPGMVirtual
{
public:

  /**
   * @return 
   *  The CATToplogy common topology object of the data structure
   */
  virtual CATTopology * GetCommonTopology() const = 0;

  /**
   * @brief
   * Gets the CATTopology lists that are bording the common topology groups.
   * 
   * e.g. : Considering the ListPOfListPOfCATTopology [[F1, F2], [F3, F4]] and having a common topology E1 bet. F1 and F3.
   * Then, ioBordTopoList = [F1, F3] since F1 (resp. F3) is bording E1.
   * 
   * @param 
   *  ioBordTopoLists [in/out]
   * List of bording topologies
   */
  virtual void GetBordingTopologyList(ListPOfCATTopology &ioBordTopoList) const = 0;

  /**
   * @brief
   * Returns a list of indices which indicate the List's index of each bording topology.
   * 
   * e.g. : Considering the ListPOfListPOfCATTopology [[F1, F2], [F3, F4]] and having a common topology E1 bet. F1 and F3.
   * Then, ioBordTopoIdxList = [1, 2] since F1 (resp. F3) belongs to the 1# list (resp 2# list).
   * 
   * @param 
   *  ioBordTopoIdxList [in/out]
   * List of bording topology indices
   * @return 
   */
  virtual void GetBordingTopologyIndexList(CATListOfInt &ioBordTopoIdxList) const = 0;

protected:
  CATIPGMTopGNCommonTopologyData();
  virtual ~CATIPGMTopGNCommonTopologyData();

  
};

/**
 * @brief
 * Creates a data structure to handle a common topology informations in Generic Naming contexT.
 * 
 * @param iBody
 * A pointer to the input body.
 * @param iCommonTopology
 * The common topology.
 * @param iBordTopoList
 * List of topology lists that are bording iCommonTopology
 * @param iBordTopoSizeList
 * List containing the initial group index of each bording topology
 * 
 * @return
 * The pointer to the data structure created for the common topology.
 */
ExportedByCATGMModelInterfaces CATIPGMTopGNCommonTopologyData * CATIPGMCreateTopGNCommonTopologyData(
  CATTopology *iCommonTopology,
  const ListPOfCATTopology &iBordTopoList,
  const CATListOfInt &iBordTopoIdxList);
#endif
