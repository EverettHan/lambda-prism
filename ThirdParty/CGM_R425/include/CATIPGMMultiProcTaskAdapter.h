#ifndef CATIPGMMultiProcTaskAdapter_h_
#define CATIPGMMultiProcTaskAdapter_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

#include "CATGMModelInterfaces.h"
#include "CATIPGMMultiProcTask.h"
#include "CATUnicodeString.h"
#include "CATSysErrorDef.h"
#include "CATMathInline.h"

class CATIPGMMultiProcChannel;

// Macro de definition de fonction externe pour le besoin du Load
// ------------------------------------------------------------------------------------------------
#define CATMP_TEXTIFY(A) #A 

#define CATIPGMultiProcTaskDeclare(ClassName, LibraryName) \
  public: \
  virtual CATUnicodeString GetLoadFunctionName() const; \
  virtual CATIPGMMultiProcTask * FCreateTask() const; \
  INLINE virtual CATUnicodeString  GetSharedLibrary() const { return #LibraryName; } \

#define CATIPGMMultiProcTaskImplement(ClassName) \
  extern "C" DSYExport CATIPGMMultiProcTask * Load##ClassName() { return new ClassName(); } \
  CATUnicodeString ClassName::GetLoadFunctionName() const { return CATMP_TEXTIFY(Load##ClassName); } \
  CATIPGMMultiProcTask * ClassName::FCreateTask() const { return new ClassName() ; }

/**
* =============================================================================================
*   Abstract Class CATIPGMMultiProcTaskAdapter 
* =============================================================================================
*
*  Description : 
* Class representing one operation or task to be computed using Experience Kernel.
* <b>Role:</b> This class contains operational data, the inputs and outputs of a task,
* as well as methods to facilitate the transfer of operational data between processes.
* <br> Clients add data members and overload the transfer methods in custom
* derived implementations.
* When multiple processes are utilized, a duplicate is created in the slave process, 
* and the streaming methods are used to transmit the operational data between them.
* <b>Note:</b> Clients should derive their custom operations from this class.
* <br> This class works in conjunction with the CATIPGMMultiProcRunner class.
*
* @see CATIPGMMultiProcRunner
*  
*  This base class HAS TO be derived.  
*  The following methods are to be implemented :
*
*     - virtual HRESULT Write     (CATIPGMMultiProcChannel       & iInputChannel) const = 0;
*     - virtual HRESULT Read      (const CATIPGMMultiProcChannel & iInputChannel)  = 0;
*     - virtual HRESULT OnExecute (CATIPGMMultiProcChannel       & ioResultChannel)= 0;
*     - virtual HRESULT OnResult  (const CATIPGMMultiProcChannel & iResultChannel) = 0; 
*     - virtual CATUnicodeString GetSharedLibrary()    const = 0;
*     - virtual CATUnicodeString GetLoadFunctionName() const = 0;
*
* @see example of CATMPTaskTopOperator.
*   NewTopologicalObjects\MPRunnerEngine.m\LocalInterfaces\CATMPTaskTopOperator.h
*
* ============================================================================================= */

class ExportedByCATGMModelInterfaces CATIPGMMultiProcTaskAdapter : public CATIPGMMultiProcTask
{

public: 
  
  // Destructor
  virtual ~CATIPGMMultiProcTaskAdapter();
  
  // Implement the writing of data necessary to execute your code.
  // [ Called on main process ]
  virtual HRESULT Write(CATIPGMMultiProcChannel &ioInputChannel) const override { return E_NOTIMPL; }

  // Implement the reading of data necessary to execute your code.
  // [ Called on sub process ]
  virtual HRESULT Read(const CATIPGMMultiProcChannel &iInputChannel) override { return E_NOTIMPL; }

  // Implement the code that will be called in each child process.
  // [ Called on sub process ]
  virtual HRESULT OnExecute(CATIPGMMultiProcChannel & ioResultChannel) override { return E_NOTIMPL; }

  // Implement the reading of your result data if you need specialized output data.
  // [ Called on main process ]
  virtual HRESULT OnResult (const CATIPGMMultiProcChannel &iResultChannel) override { return S_OK; }
  
 
  // -----------------------------------------------------------------------------------------
  // ** If you are NOT using the Macros only **
  // -----------------------------------------------------------------------------------------
  // this method must return the name of your external constructor function name.  
  virtual CATUnicodeString        GetLoadFunctionName() const = 0;
  // This method must return the library name where your child class is implemented.
  // Ex: virtual CATUnicodeString GetSharedLibrary () const { return “MyFrameworkLibraryName”; }
  virtual CATUnicodeString        GetSharedLibrary ()   const = 0;  

  // How to use the following MACROS 
  // =========================================================================================
  // Add Macro   CATIPGMultiProcTaskDeclare(YourClassName, MyFrameworkLibraryName);   in your header file.
  // Add Macro   CATIPGMultiProcTaskImplement(YourClassName);                          in your cpp file.

protected:
  // Constructor 
  CATIPGMMultiProcTaskAdapter ();

private:

  /* forbiden copy constructor*/
  CATIPGMMultiProcTaskAdapter(const CATIPGMMultiProcTaskAdapter & iMPTask);
  /* forbiden operator */
  CATIPGMMultiProcTaskAdapter & operator = (const CATIPGMMultiProcTaskAdapter & iMPTask);

};


/**
* ----------------------------------------------------------------* 
*            If you are NOT using the Macros only *
* ----------------------------------------------------------------*
* => Implment those methods :

extern "C" DSYExport CATIPGMMultiProcTask * LoadMyClass() { 
  return new MyClass(); 
}

CATUnicodeString MyClass::GetLoadFunctionName() { 
  return "LoadMyClass"; }

CATUnicodeString GetSharedLibrary () const { 
  return “MyFrameworkLibraryName”; }

*/

#endif
