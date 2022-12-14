// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CATISysDynLicenseSettingAtt.h
// Define the CATISysDynLicenseSettingAtt interface
//
//===================================================================
//
// Usage notes:
//   New interface: describe its use here
//
//===================================================================
//
//  Nov 2003  Creation: Code generated by the CAA wizard  
//===================================================================
#ifndef CATISysDynLicenseSettingAtt_H
#define CATISysDynLicenseSettingAtt_H
// COPYRIGHT DASSAULT SYSTEMES 2003
/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */

#include "JS0LIB0.h"
#include "CATBaseUnknown.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByJS0LIB0 IID IID_CATISysDynLicenseSettingAtt;
#else
extern "C" const IID IID_CATISysDynLicenseSettingAtt ;
#endif

class CATSettingInfo;
class CATUnicodeString;
 
//------------------------------------------------------------------

/**
* Interface to handle the dynamic licensing settings.
* <b>Role</b>: This interface is implemented by a component which
* represents the controller of the dynamic Licenses. 
* <br>To access this property page:
* <li>Click the Options command in the Tools menu </li>
* <li>Click General</li>
* <li>Click the Shareable Products Property Page</li>
* <br>This interface defines:
* <li>A method to lock/unlock each parameter</li>
* <li>A method to retrieve the information concerning each parameter</li>
* <li> Note that when a license is selected in user mode, no information is written in the settings, 
* only the lock status is written in the settings.
*/

class ExportedByJS0LIB0 CATISysDynLicenseSettingAtt: public CATBaseUnknown
{
  CATDeclareInterface; 

  public:

    //***********************************************************************
    // Ensure consistency with the IDL interface that will delegate its work
    // Check allowed signatures in System.CATSysSettingController
    //***********************************************************************
/**
* Retrieves the List of the Licenses.
* <br><b>Role</b>: Retrieves the list of the locked Licenses.
* There is no SetLicenseList() because the list is initialized using LUM.
* <li>When using packages, the licenses name appears like MyPackage.Package
* (Mypackage is the name of the package).</li>
* @param oNbLic
*	The number of Licenses
* @param oTabLic
*	The array of Licenses
* @return
*	<b>Legal values</b>:
*	<br><tt>S_OK :</tt>   on success
* 	<br><tt>E_FAIL:</tt>  on failure
*/
	virtual HRESULT GetLicensesList (int & NbLic, CATUnicodeString **&oTabLic) =0;

  
/** 
* Retrieves information about the LicensesList setting locking state (global lock for the LicensesList).
* <br><b>Role</b>: Retrieves information about the LicensesList setting locking state (global lock for the LicensesList) 
* It is used to get the lock status of the List of the Licenses.
* If the LicenseList is locked all the licenses are locked.
* When the licenses are locked, it means that an administrator has locked the attribute.
* It does not means that an administrator has changed the value of the attribute.
* The value of the setting is not updatable because it refers to a lock on a list. 
* That is why the return value is false.
* @param oInfo:
* Address of an object CATSettingInfo.
* <br>Parameter values in dump:
* <li>Parameter 1 : "Value taken in case of reset" : useless. Default value: "Default value".</li>
* <li>Parameter 2 : "Locking state" value : unlocked / locked / locked at Admin Level n</li>
* <li>Parameter 3 : "Returned value" : useless, default value : False</li>
* <br>Refer to @href CATSysSettingController for a detailed description.
*/
	virtual HRESULT GetLicensesListInfo (CATSettingInfo * oInfo)=0;
  

/** 
* Locks or unlocks the LicensesList setting parameter.
* <br><b>Role</b>:  Locks or unlocks the parameter describing the list of 
* installed licenses, if the  operation is allowed in the current
* administrated environment. In user mode  this method will always return E_FAIL.
* When the LicenseList is locked all the licenses are locked.
* When the LicenseList is unlocked all the licenses are unlocked.
* @param iLock
*	the locking operation to be performed:
*	<br><tt>1 :</tt>   to lock the parameter.
* 	<br><tt>0:</tt>   to unlock the parameter.
* @return
*	<b>Legal values</b>:
*	<br><tt>S_OK :</tt>   on success (the list has been successfully lock or unlocked).
*	<br><tt>E_OUTOFMEMORY:</tt> on allocation failure
* 	<br><tt>E_FAIL:</tt>  on other failures  
* <br>Refer to @href CATSysSettingController for a detailed description.
*/
    virtual HRESULT SetLicensesListLock ( unsigned char iLock)=0;
  

/**
* Retrieves the check_lock value of the license.
* <br><b>Role</b>: Retrieves the mapping between a name of a license and 
* the check_lock value of the license.
*
* Note: This method appears after a dump action by default in the generated macro when
* administrator parameters are locked.
* It does not return a granted or not granted status on the license.
* When the license is not checklocked GetLicense() does not appears in the dump, even when GetLicenseInfo()
* appears.
* Use this call to get the check_lock status of a license. 
* There is no inheritance of the check_lock status of a license for the end user: 
* If the check_lock has been requested for any of the administrator, the license appears locked for the end user,
* In user mode the license ZZZ.prd appears locked in the shareable product tab when parameter iLicense="Check_ZZZ.prd",
* and the parameter  oValue="CheckLockRequested".
* The value "CheckNotLockRequested" appears only when the setting exits (a license check button has been
* first unchecked, validated with OK button, and then the license check button has been rechecked).
* <li>There is no link between the lock on the license itself which is used when there are several admin levels.
* For iLicense="ZZZ.prd", the oValue may be "Locked" or "Unlocked".</li>
* <li>For a package:
* iLicense="Check_Mypackage.package" and oValue="CheckLockRequested".
* (Mypackage is the name of the package).</li>
*
* @param iLicense
* The license name begins with Check_ for checklocks
*
* @param oValue
*	the value of the License:
*	<br><tt> CheckLockRequested :</tt>   check_lock requested.
* 	<br><tt> CheckLockNotRequested :</tt>  check_lock not requested.
*   <br><tt> "":</tt> always if the licenses are not checklock. In that case
*                the license value is not modified.
*                It is the lock status whom cares.   
* @return
*	<b>Legal values</b>:
*	<br><tt>S_OK :</tt>   on success
* 	<br><tt>E_FAIL:</tt>  on failure
*/
  virtual HRESULT GetLicense(const CATUnicodeString *iLicense, 
			     CATUnicodeString *oValue)=0;


/**
* Sets the check_lock status of license.
* <br><b>Role</b>: Sets the check_lock value of the license.
* It it not possible to grant a license with this call.
* This method shoud be called in administrator mode.
* There is no inheritance of the check_lock status of a license for the end user:
* If the check_lock has been requested for any of the administrator, the license appears locked for the end user,
* In user mode the license ZZZ.prd appears locked in the shareable product tab when parameter iLicense="Check_ZZZ.prd",
* and the parameter  iValue="CheckLockRequested".
* The value "CheckNotLockRequested" appears only when the setting exits (a license check button has been
* first unchecked, validated with OK button, and then the license check button has been rechecked).
* <li>There is no link between the lock on the license itself which is used when there are several admin levels.
* For iLicense="ZZZ.prd", the iValue may be "Locked" or "Unlocked".</li>
* <li> For a package:
* iLicense="Check_Mypackage.package" and iValue="CheckLockRequested".
* (Mypackage is the name of the package).</li>
*
* @param iLicense
* The license name begins with Check_
* @param iValue
*	the value of the License:
*	<br><tt> CheckLockRequested :</tt>   check_lock requested.
* 	<br><tt> CheckLockNotRequested :</tt>  check_lock not requested.
* @return
*	<b>Legal values</b>:
*	<br><tt>S_OK :</tt>   on success
* 	<br><tt>E_FAIL:</tt>  on failure
*/
  virtual HRESULT SetLicense(const CATUnicodeString *iLicense, 
			     const CATUnicodeString *iValue)=0;

/**
* Retrieves the state of a given License.
* <br><b>Role</b>:  Retrieves the state of a given License.
* It it is used to get the lock status of a specific license.
* When the license is locked, it means that an administrator has locked the attribute.
* It does not means that an administrator has changed the value of the license.
* The return value is true when the license is checklocked, because the value of the
* license is Check_XXX.prd 
*
* @param iLicense:
* the name of the License.
* @param oInfo:
* Address of an object CATSettingInfo.
* @return
* <b>Legal values</b>:
* <br><tt>E_FAIL:</tt> 
* <br>Refer to @href CATSysSettingController for a detailed description.
* <br>Dump information:
* <li> Parameter 1 : the name of the License.</li>
* <li> Parameter 2 : "Set at Admin Level j" when locked, "Default value" when unlock.</li> 
* <li> Parameter 3 : locking state of the licenses Unlocked / Locked / Locked at Admin Level j. </li>
* <li> Return value : Always false if the license is not checklock, because the status of the license
*                     is not modified, only the lock status is modified.
*                     True if the license is checklock, because the value of the license has been
*                     changed to Check_XXX.prd.
*/
	virtual HRESULT GetLicenseInfo (const CATUnicodeString *iLicense,
				  CATSettingInfo* oInfo)=0;


/** 
* Locks or unlocks the License setting parameter.
* <br><b>Role</b>: Locks or unlocks the given License if the
* operation is allowed in the current administrated environment.
* In user mode this method will always return E_FAIL.
* @param iLicense:
* the name of the License.
* @param iLock
*	the locking operation to be performed:
*	<br><tt>1 :</tt>   to lock the parameter.
* 	<br><tt>0:</tt>   to unlock the parameter.
* @return
*	<b>Legal values</b>:
*	<br><tt>S_OK :</tt>   on success
* 	<br><tt>E_FAIL:</tt>  on failure
* <br>Refer to @href CATSysSettingController for a detailed description.
*/
	virtual HRESULT SetLicenseLock (const CATUnicodeString *iLicense,
				  unsigned char iLock)=0;
  

  // No constructors or destructors on this pure virtual base class
  // --------------------------------------------------------------
};

//------------------------------------------------------------------

#endif
