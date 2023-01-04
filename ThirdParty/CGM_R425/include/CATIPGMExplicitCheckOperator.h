#ifndef CATIPGMExplicitCheckOperator_h_
#define CATIPGMExplicitCheckOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2014

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATCollec.h"
#include "CATPGMExplicitReport.h"
#include "CATExplicitLabelParameter.h"



class CATGeoOpTimer;
class CATICGMObject;
class CATBody;
class CATLISTP(CATBody);
class CATLISTP(CATICGMObject);
class CATLISTP(CATPGMExplicitReport);
class CATSoftwareConfiguration;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMExplicitCheckOperator;

/**
* Operator designed to achieve an Explicit Check on a CATICGMObject instance.
*<br>
* The CATIPGMExplicitCheckOperator allows you to perform an explicit check 
* on a set of CATICGMObject. It detects topological and/or geometrical 
* anomalies.
* An anomaly could be a Warning or an Error.
* 
* To use a CATIPGMExplicitCheckOperator class:
*<ul>
* <li>Create it with the <tt>CATPGMCreateExplicitCheck</tt> global methods
* <li>Tune it with appropriate options, using the <tt>SetXxx</tt> 
*     or <tt>AddXxx<tt> methods.
* <li>Run it
* <li>Get the result(s) with the <tt>GetNbAnomalies</tt> method 
*     or <tt>GetListIfAnomalies</tt>
* <li><tt>delete</tt> it after use.
*</ul> 
*/
class ExportedByCATGMModelInterfaces CATIPGMExplicitCheckOperator: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMExplicitCheckOperator();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------  
  /**
	* Set List of objects to be Checked <tt>piCGMObject</tt> 
	* to the list of object to be checked
	* @param piCGMObject 
	*   an additional Object to be Checked.
	*/
  virtual void SetListOfObjects(CATLISTP(CATICGMObject) &iListOfCATICGMObject) = 0;

  /**
	* Set the list of context bodies in which the specified anomalies 
	* will be checked.
	* Setting a Context Body (Bc), ensure that all CGM Objects involved in a detected 
	* « specific anomaly » are useful for the modele Bc.
	* Example : 
	*     - If user addd objects B1 and B2 to be checked (AddObject(B1),AddObject(B2))
	* There are 4 situations :
	*     1- No context bodies has been specified : anomalies that will be detected 
	*       could involve objects that are not useful for the modelisation 
	*       of B1 and B2
	*     2- Specify B1 as a context body : sub-objects that will checked 
	*       will be those belong to B1 and anomalies that will be detected will only
	*       concern objects that are useful for the context body B1
	*     3- Specify B2 as a context body : same effect as 2 but for B2
	*     4- Specify B1 and B2 as context bodies : anomalies that will detected 
	*       involve objects that are only useful for the modelisation 
	*       of B1 and B2.
	*
	* What objects useful for the model B mean ?
	*     
	*
	*  @param iListOfContextBodies 
	*   List of context bodies  
	*    
	*/
  virtual void SetContextBodies(CATLISTP(CATBody) &iListOfContextBodies) = 0;

  /**
	* Add the object to be Checked <tt>piCGMObject</tt> 
	* to the list of object to be checked
	* @param piCGMObject 
	*   an additional Object to be Checked.
	*/
  virtual void AddObject(CATICGMObject *piCGMObject) = 0;

  /**
	* Add an anomaly to the list of anomalies to be checked
	* @param iLabelAnomaly 
	*   an additional Anomaly to be Checked.
	*
	* Rmk :  If no anomalies have been specified via the AddAnomaly service,
	*        the default behavior is to check the "CATCGMInternalAnomalies" 
	*        set of anomaly
	*/
  virtual void AddAnomaly(CATCGMExplicitCheckAnomaly iLabelAnomaly) = 0;

  /**
	* Set a parameter for a selected specific anomaly. 
	* Setting parameters of a specific anomaly allows to tune the desired behavior. 
	* Tunning parameters of an anomaly impact directly the obtained results of the Explicit Check.
	* @param iLabelAnomaly 
	*   the Specific Anomaly under scope.
	* @param iExplicitLabelParam
	*   the label of parameter to set.
	*   the parameter label describes the meaning of the parameter to set.
	*   Examples : if a parameter to set is the maximum polynomial degree allowed 
	*              for a surface or a curve then the parameter label will be : 
	*					CATExplicitLabelParameter_Max_Polyn_Deg 
	* @param iParam
	*   the parameter value to set.
	*
	* N.B : Please refers to the documentation of specific anomalies (see CATPGMExplicitReport intrface)
	*       It describes :
	*				- the meaning and scope of each specific anomaly, 
	*				- its parameters and their meaning and labels, 
	*				- the CGM Objects that are involved in the anomaly 
	*				- Numerical values that describe the anomaly
	*/
  virtual void SetParameter(
    CATCGMExplicitCheckAnomaly iLabelAnomaly,
    CATExplicitLabelParameter iExplicitLabelParam,
    CATBoolean iParam) = 0;

  /**
	* Set a parameter for a selected specific anomaly. 
	* Setting parameters of a specific anomaly allows to tune the desired behavior. 
	* Tunning parameters of an anomaly impact directly the obtained results of the Explicit Check.
	* @param iLabelAnomaly 
	*   the Specific Anomaly under scope.
	* @param iExplicitLabelParam
	*   the label of parameter to set.
	*   the parameter label describes the meaning of the parameter to set.
	*   Examples : if a parameter to set is the maximum polynomial degree allowed 
	*              for a surface or a curve then the parameter label will be : 
	*					CATExplicitLabelParameter_Max_Polyn_Deg 
	* @param iParam
	*   the parameter value to set.
	*
	* N.B : Please refers to the documentation of specific anomalies (see CATPGMExplicitReport intrface)
	*       It describes :
	*				- the meaning and scope of each specific anomaly, 
	*				- its parameters and their meaning and labels, 
	*				- the CGM Objects that are involved in the anomaly 
	*				- Numerical values that describe the anomaly
	*/
  virtual void SetParameter(
    CATCGMExplicitCheckAnomaly iLabelAnomaly,
    CATExplicitLabelParameter iExplicitLabelParam,
    CATLONG32 iParam) = 0;

  /**
	* Set a parameter for a selected specific anomaly. 
	* Setting parameters of a specific anomaly allows to tune the desired behavior. 
	* Tunning parameters of an anomaly impact directly the obtained results of the Explicit Check.
	* @param iLabelAnomaly 
	*   the Specific Anomaly under scope.
	* @param iExplicitLabelParam
	*   the label of parameter to set.
	*   the parameter label describes the meaning of the parameter to set.
	*   Examples : if a parameter to set is the maximum polynomial degree allowed 
	*              for a surface or a curve then the parameter label will be : 
	*					CATExplicitLabelParameter_Max_Polyn_Deg 
	* @param iParam
	*   the parameter value to set.
	*
	* N.B : Please refers to the documentation of specific anomalies (see CATPGMExplicitReport intrface)
	*       It describes :
	*				- the meaning and scope of each specific anomaly, 
	*				- its parameters and their meaning and labels, 
	*				- the CGM Objects that are involved in the anomaly 
	*				- Numerical values that describe the anomaly
	*/
  virtual void SetParameter(
    CATCGMExplicitCheckAnomaly iLabelAnomaly,
    CATExplicitLabelParameter iExplicitLabelParam,
    double iParam) = 0;

  /**
	* Decrease severiy degree of a set of Internal anomalies in order to match CGM Check behavior
   * DO NOT USE (Only for internal & specifc usage)
	*/
  virtual void ActivateCGMInternalAnomaliesBehavior() = 0;

  /**
	* Performs the Check process
	*/
  virtual int Run() = 0;

  /**
	* Compute the number of errors and warnings found after the Check.
	* @param NbErrors 
	*   Number of errors resulting from the Check operation
	* @param NbWarnings 
	*   Number of warnings resulting from the Check operation
	*/
  virtual void GetNbAnomalies(int &NbErrors, int &NbWarnings) = 0;

  /**
	* Get the list of CATPGMExplicitReport objects. Each one is a report 
	* which contains usefull information on a single anomaly. 
	* The size of the list corresponds to the number of the anomalies
	* founded on the analyzed object. The number of anomalies is simply
	* the sum of errors and warnings.
	* @param NbErrors 
	*   Number of errors resulting from the Check operation
	* @param NbWarnings 
	*   Number of warnings resulting from the Check operation
	*/
  virtual void GetListIfAnomalies(CATLISTP(CATPGMExplicitReport) &ioListOfExplicitReports) = 0;

  /**
	* Enable Or Disable the capability to Dump the result of the Explicit Check
	* in specific files :
	*      *.CATPGMExplicitCheck : contains ID of anomalies prefixed with ERROR or WARNING word
	*      *.txt              : contains more details on each anomalies
	* @param iEnableDumpExplicitCheckResult 
	*  If TRUE its allow the Dump 
	* N.B : This capability is only available under ODT mode
	*/
  virtual void EnableDumpOfCheckResult(CATBoolean iEnableDumpExplicitCheckResult) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMExplicitCheckOperator(); // -> delete can't be called
};

/** 
* Creates an ExplicitCheck Operator.
*
* <br><b>Role</b>: Creates an ExplicitCheck Operator instance.
* To delete with the usual C++ delete operator after use.
*
* @return [out, delete]
*/
ExportedByCATGMModelInterfaces CATIPGMExplicitCheckOperator *CATPGMCreateExplicitCheckOperator(
  CATGeoFactory *piFactory,
  CATSoftwareConfiguration *piConfig);

#endif /* CATIPGMExplicitCheckOperator_h_ */
