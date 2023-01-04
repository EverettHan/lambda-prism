#ifndef CATIPGMHybClashBodyChecker_h_
#define CATIPGMHybClashBodyChecker_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"

class CATBody;
class CATPGMHybClashCellCellIter;
class CATSoftwareConfiguration;

// Ajout wmn apres cgmitfgenerate
#include "CATCollec.h" // CATLISTP
class CATListPtrCATCell;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMHybClashBodyChecker;

/**
 * Checks a given Body for self intersections
 */
class ExportedByCATGMModelInterfaces CATIPGMHybClashBodyChecker: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMHybClashBodyChecker();

  /**
   * Checks whether the input Body has self-intersections.
   * If a SurfaceCellLayer is available, intersections with 
   * Neighborhood faces on edges are not reported. 
   * @param iContacts
   *        TRUE to enable contact mode in polyhedral check
   * @param oSelfIntersects
   *        TRUE if body self-intersects, FALSE otherwise.
   * @return
   *        S_OK if everything went fine
   */
  virtual HRESULT Run(CATBoolean iContacts, CATBoolean &oSelfIntersects) = 0;

  /**
   * AddListOfFaces : To provide a list of faces to the polyhedral check operator.
   *
   * If 0 list is provided : a full check will be performed.
   *
   * If 1 list is provided : this list can be checked against itself,
   *                         this list will be checked against faces not present in the list.
   *
   * If N lists are provided : each list can be checked against itself,
   *                           each list will be checked against the other lists,
   *                           each list will be checked against faces not present in any list.
   *
   * iListOfFaces : the list of faces.
   * iCheckWithin : TRUE to check iListOfFaces against itself, FALSE otherwise.
   */
  virtual void AddListOfFaces(
    CATLISTP(CATCell) &iListOfFaces,
    CATBoolean iCheckWithin) = 0;

  /**
   * To disable checking of ALL lists against faces not present in any list.
   * This check is enabled by default.
   */
  virtual void CheckAgainstOtherFaces(CATBoolean iCheck) = 0;

  /**
   * To remove all lists of faces from the polyhedral check operator.
   */
  virtual void RemoveListsOfFaces() = 0;

  /**
   * Get an iterator on couples of faces that are intersecting each other.
   * Iterator must be released by caller.
   */
  virtual CATPGMHybClashCellCellIter *GetCouples() = 0;

  /**
   * Activate face self-intersection check.
   * Disabled by default.
   */
  virtual void CheckFacesAgainstThemselves(CATBoolean iCheck) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMHybClashBodyChecker(); // -> delete can't be called
};

ExportedByCATGMModelInterfaces CATIPGMHybClashBodyChecker *CATPGMCreateHybClashBodyChecker(
  CATBody *iBody,
  CATSoftwareConfiguration *iConfig);

#endif /* CATIPGMHybClashBodyChecker_h_ */
