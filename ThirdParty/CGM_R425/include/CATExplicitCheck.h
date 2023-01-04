
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2010
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//
//	Class		  :		CATExplicitCheck
//	Creation	:		18/08/2010
//
//
//	Synopsis	:	Header class of CATExplicitCheck. It allows to Call explicitly 
//              a Check on a CATICGMObject
//					
//	
//
//
//	Authors		:  AAD + KY1 +TCX
//-----------------------------------------------------------------------------
//18/08/2010 Class creation
//-----------------------------------------------------------------------------

#ifndef CATExplicitCheck_H
#define CATExplicitCheck_H


#include "ExportedByCATTopologicalObjects.h"
#include <CATListOfCATICGMObjects.h>
#include "CATPGMExplicitReport.h"
#include "ListPOfCATPGMExplicitReport.h"
#include "CATExplicitCheckSeverity.h"
#include "CATPGMExplicitCheck.h"
#include "CATCXReport.h"
#include "CATMathInline.h"
#include "CATListOfInt.h"
#include "CATExplicitLabelParameter.h"


class CATICGMObject;
class CATExplicitCheckOperator;
class CATExplicitCheck_SetOfAnomalies;
class CATGeoFactory;
class CATSoftwareConfiguration;

/**
* Class designed to achieve an Explicit Check on a CATICGMObject instance.
*<br>
* The CATExplicitCheck class allows you to perform an explicit check 
* on a CATICGMObject. It detects topological and/or geometrical anomalies.
* An anomaly could be a Warning or an Error.
* 
* To use a CATExplicitCheck class:
*<ul>
* <li>Create it with the <tt>CATCreateExplicitCheck</tt> global methods
* <li>Tune it with appropriate options, using the <tt>SetXxx</tt> 
*     or <tt>AddXxx<tt> methods.
* <li>Run it
* <li>Get the result(s) with the <tt>GetNbAnomalies</tt> method 
*     or <tt>GetListIfAnomalies</tt>
* <li><tt>delete</tt> it after use.
*</ul> 
*
* Rmk :  If no anomalies have been set via the AddAnomaly service.
*        the default behavior will be kept. The Explicit Check Operator 
*        will check the "Internal_Anomalies" set of anomaly
*/
class ExportedByCATTopologicalObjects CATExplicitCheck : public CATPGMExplicitCheck
{

public:

CATCGMNewClassArrayDeclare;

/**
* parameters Constructor
** @param piGeoFactory
*   the Geo Factory that objects to be set for check belong.
** @param piSoftConfig
*   the Software configuration
*/
CATExplicitCheck(CATGeoFactory *piGeoFactory,CATSoftwareConfiguration *piSoftConfig);

/**
* @deprecated
*
* default Constructor
*/
CATExplicitCheck();

/** 
* Create a CATExplicitCheck pointer.
*
* <br><b>Role</b>: Create a CATExplicitCheck pointer.
* To delete with the usual C++ delete operator after use.
*
* @return
*   The pointer to the created CATExplicitCheck object
*
*/
//static CATExplicitCheck *CATCreateExplicitCheck();

/**
* Add the object to be Checked <tt>piCGMObject</tt> 
* to the list of object to be checked
* @param piCGMObject 
*   an additional Object to be Checked.
*/
void AddObject(CATICGMObject * piCGMObject);

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
void SetContextBodies(ListPOfCATBody &iListOfContextBodies);

/**
* Add an anomaly to the list of anomalies to be checked
* @param iLabelAnomaly 
*   an additional Anomaly to be Checked.
*
* Rmk :  If no anomalies have been specified via the AddAnomaly service,
*        the default behavior is to check the "CATCGMInternalAnomalies" 
*        set of anomaly
*/
void AddAnomaly(CATCGMExplicitCheckAnomaly iLabelAnomaly);

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
void SetParameter(CATCGMExplicitCheckAnomaly iLabelAnomaly, CATExplicitLabelParameter iExplicitLabelParam, CATBoolean iParam);

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
void SetParameter(CATCGMExplicitCheckAnomaly iLabelAnomaly, CATExplicitLabelParameter iExplicitLabelParam, CATLONG32 iParam);

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
void SetParameter(CATCGMExplicitCheckAnomaly iLabelAnomaly, CATExplicitLabelParameter iExplicitLabelParam, double iParam);

/**
* Performs the Check process
*/
void Run();


/**
* Compute the number of errors and warnings found after the Check.
* @param NbErrors 
*   Number of errors resulting from the Check operation
* @param NbWarnings 
*   Number of warnings resulting from the Check operation
*/
void GetNbAnomalies(int& NbErrors,int& NbWarnings);

/**
* Get the list of CATExplicitReport objects. Each one is a report 
* which contains usefull information on a single anomaly. 
* The size of the list corresponds to the number of the anomalies
* founded on the analyzed object. The number of anomalies is simply
* the sum of errors and warnings.
* @param NbErrors 
*   Number of errors resulting from the Check operation
* @param NbWarnings 
*   Number of warnings resulting from the Check operation
*/
void GetListIfAnomalies(ListPOfCATPGMExplicitReport &ioListOfExplicitReports);


/**
* Enable Or Disable the capability to Dump the result of the Explicit Check
* in specific files :
*      *.CATExplicitCheck : contains ID of anomalies prefixed with ERROR or WARNING word
*      *.txt              : contains more details on each anomalies
* @param iEnableDumpExplicitCheckResult 
*  If TRUE its allow the Dump 
* N.B : This capability is only available under ODT mode
*/
void EnableDumpOfCheckResult(CATBoolean iEnableDumpExplicitCheckResult);

/**
* Dtor
*/
virtual ~CATExplicitCheck();

private:

//Data
CATExplicitCheckOperator*				_pExplicitCheckOperator;

//Methods 
/** @nodoc @nocgmitf */
CATExplicitCheck(const CATExplicitCheck& iExplicitCheck);
};

/** 
* Creates a CATExplicitCheck.
*
* <br><b>Role</b>: Creates a CATExplicitCheck pointer.
* To delete with the usual C++ delete operator after use.
*
* @return [out, delete]
*/
INLINE CATExplicitCheck *CATCreateExplicitCheck()
{
  return new CATExplicitCheck();
}

/** 
* Creates a CATExplicitCheck.
*
* parameters Constructor
** @param piGeoFactory
*   the Geo Factory that objects to be set for check belong.
** @param piSoftConfig
*   the Software configuration
*
* <br><b>Role</b>: Creates a CATExplicitCheck pointer.
* To delete with the usual C++ delete operator after use.
*
* @return [out, delete]
*/
INLINE CATExplicitCheck *CATCreateExplicitCheck(CATGeoFactory *piGeoFactory,CATSoftwareConfiguration *piSoftConfig)
{
  return new CATExplicitCheck(piGeoFactory,piSoftConfig);
}

#endif

