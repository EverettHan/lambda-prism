#ifndef CATContextForFastRunAdapt_h_
#define CATContextForFastRunAdapt_h_

//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2010
//
//  Adaptor between virtual interface (CATContextForFastRun) 
//  and not CGM inheritance (ex: CATOprTopologicalOperatorContextForFastRun) 
//
//  SEE CATCONTEXTFORFASTRUN.H FOR ALL THE DOCUMENTATIONS
//
// 2014 June 10   Unused default argument added to 11 functions due to the generalization of
//                CATContextForFastRun for multi-result operators.                            G5S
// 2014 Dec  17   Rename CreateInternalContexts to SetNbOldResults.                           G5S
// 2015 Mar  10  There's now only one smart level and smartification status for the main
//               context.                                                                     G5S
// 2015 Dec  15  Remove all methods, that are now defined by mother class                     LD2
// 2018 Feb  12  Add methods to deal with fast run attribute                                  LD2
//==========================================================================

#include "CATGMModelInterfaces.h"
#include "CATContextForFastRun.h"
#include "CATListOfCATICGMObjects.h"

class CATContextForFastRunExt;
class CATSoftwareConfiguration;

class ExportedByCATGMModelInterfaces CATContextForFastRunAdapt: public CATContextForFastRun
{
public:
  CATContextForFastRunAdapt();

  virtual ~CATContextForFastRunAdapt();

protected:

  friend class CATContextForFastRunAdaptExt;

  /**
   * Returns this.
   */
  virtual CATContextForFastRunAdapt * CastToAdapt();

  /**
   * Returns the type of Context
   */
  virtual CATString GetType();

  /**
   * Override this method in child class to activate the comparison of operator parameters via an attribute attached to the result body.
   * You must override the following 4 methods:
   *   IsAttributeManagementActive       -> it must return TRUE
   *   FillFastRunBuffer                 -> it must write on the buffer all the parameters of the operation (litterals and BReps)
   *   TransferFastRunAttributeToResult  -> it must call this->TransferFastRunAttribute(MyResult), where MyResult is the result of the operation
   *   GetAllOperatorInputObjects        -> it must fill the list of all input CGM objects of the operation (bodies and BReps)
   */
  virtual CATBoolean IsAttributeManagementActive();

  /**
   * See "IsAttributeManagementActive" for more information.
   */
  virtual void FillFastRunBuffer(CATCGMStream & oBuffer);

  /**
   * See "IsAttributeManagementActive" for more information.
   */
  virtual void TransferFastRunAttributeToResult();

  /**
   * See "IsAttributeManagementActive" for more information.
   */
  virtual CATBoolean GetAllOperatorInputObjects(
    CATListPtrCATICGMObject * oInputsCopy,
    CATListPtrCATICGMObject * oInputsNoCopy,
    CATListPtrCATICGMObject * oInputsNeutral);

  /**
   * Override this method to return your software configuration.
   */
  virtual CATSoftwareConfiguration * GetSoftwareConfiguration();
};  

#endif
