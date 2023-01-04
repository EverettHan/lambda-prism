#ifndef CATIRefManager_h
#define CATIRefManager_h

// CATMathStream
#include "ExportedByCATTechTools.h"

// System
#include "CATCollec.h"
#include "CATBaseUnknown.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATIStreamManager.h"

class CATechMeta;
class CATTolerance;
class CATMathPoint;
class CATMathBox2D;
class CATMathVector;
class CATIRefObserver;
class CATUnicodeString;
class CATMathTransformation;
class CATPolyBody;
class CATPolyBodyServices;
class CATLISTP(CATPolyBody);
class CATPolyPolygon2D;

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATTechTools const IID IID_CATIRefManager;
#else
extern "C" const IID IID_CATIRefManager;
#endif

/* 
* @COPYRIGHT DASSAULT SYSTEMES 2012
* -------------------------------------------------------------------------------------------------
*  Interface for implementation of manager for Reference check mechanism for phoenix infrastructure
* -------------------------------------------------------------------------------------------------
*/

class ExportedByCATTechTools CATIRefManager : public CATBaseUnknown
{
  CATDeclareInterface;

public:

  /*
  * SetRefValue : Writes the passed data into a Reference.txt/Redo_Reference.txt file based on 
  *               current CATechTransaction behavior as to whether it is capture/redo
  * @param iRole : Role that needs streaming
  * @param iRoleValue : Value associated with the iRole
  * @return
  *   Returns S_OK if streaming was successful
  */

  virtual HRESULT SetRefValue(const CATechMeta & iRole,
                              unsigned char    & iRoleValue) = 0;             // CATechFormat_byte8

  virtual HRESULT SetRefValue(const CATechMeta & iRole,
                              short            &  iRoleValue) = 0;             // CATechFormat_Int16

  virtual HRESULT SetRefValue(const CATechMeta & iRole,
                              int              & iRoleValue) = 0;             // CATechFormat_Int32
  
  virtual HRESULT SetRefValue(const CATechMeta  & iRole,
                              CATLONG64         & iRoleValue) = 0;             // CATechFormat_Int64

  virtual HRESULT SetRefValue(const CATechMeta & iRole,
                              float            & iRoleValue) = 0;             // CATechFormat_Real32

  virtual HRESULT SetRefValue(const CATechMeta & iRole,
                              double           & iRoleValue) = 0;             // CATechFormat_Real64

  virtual HRESULT SetRefValue(const CATechMeta        & iRole,
                              const CATUnicodeString  & iRoleValue) = 0;      // CATechFormat_CATUnicode

  virtual HRESULT SetRefValue(const CATechMeta        & iRole,
                              const CATMathPoint      & iRoleValue) = 0;      // CATechFormat_Pt3D

  virtual HRESULT SetRefValue(const CATechMeta      & iRole,
                              const CATMathVector   & iRoleValue) = 0;        // CATechFormat_Vector3D

  virtual HRESULT SetRefValue(const CATechMeta    & iRole,
                              const CATMathBox2D  & iRoleValue) = 0;           // CATechFormat_Box2D

  virtual HRESULT SetRefValue(const CATechMeta              & iRole,
                              const CATMathTransformation   & iRoleValue) = 0; // CATechFormat_Tranfo3D

  virtual HRESULT SetRefValue(const CATechMeta  & iRole,
                              CATListOfInt      & iListOfValues) = 0;         // for list of integer values

  virtual HRESULT SetRefValue(const CATechMeta  & iRole,
                               CATListOfDouble  & iListOfValues) = 0;       // for list of double values

  virtual HRESULT SetRefValue(const CATechMeta  & iRole,
                               CATLISTV(CATMathPoint)  & iListOfValues) = 0;       // for list of CATMathPoint values
  
  virtual HRESULT SetRefValue(const CATechMeta  & iRole,
                               CATPolyBody*  & iPolyBody, CATUnicodeString  & iFilePath) = 0;              // for PolyBody

  virtual HRESULT SetRefValue(const CATechMeta  & iRole,
                               CATPolyPolygon2D*  & iPolyPolygon2D, CATUnicodeString  & iFilePath) = 0;              // for PolyPolygon2D
   virtual HRESULT SetRefValue(const CATechMeta  & iRole,
                               CATLISTP(CATPolyBody) & iPolyBodyList, CATUnicodeString  & iFilePath) = 0;     // for PolyBodyList
       
  /*
  * GetRefValue : Outputs the value associated with iRole. Should be called during redo
  * @param iRole : input Role
  * @param oRoleValue : Value associated with the iRole
  * @return
  *   Returns S_OK if method returns successfully
  */

  virtual HRESULT GetRefValue(const CATechMeta & iRole,
                              int              & oRoleValue) = 0;             // CATechFormat_Int32

  virtual HRESULT GetRefValue(const CATechMeta & iRole,
                              double           & oRoleValue) = 0;             // CATechFormat_Real64

  virtual HRESULT GetRefValue(const CATechMeta      & iRole,
                              CATMathVector   & oRoleValue) = 0;        // CATechFormat_Vector3D

  virtual HRESULT GetRefValue(const CATechMeta        & iRole,
                              CATMathPoint      & oRoleValue) = 0;      // CATechFormat_Pt3D

  virtual HRESULT GetRefValue(const CATechMeta        & iRole,
                              CATLISTV(CATMathPoint)      & oListOfValues) = 0;      // list of CATMathPoint values

  virtual HRESULT GetRefValue(const CATechMeta        & iRole,
                              CATListOfInt      & oListOfValues) = 0;      // list of int values

  virtual HRESULT GetRefValue(const CATechMeta        & iRole,
                              CATListOfDouble      & oListOfValues) = 0;      //list of double values

     
  virtual HRESULT GetRefValue(const CATechMeta        & iRole,
                              unsigned char     & oRoleValue) = 0;      // CATechFormat_byte8

  virtual HRESULT GetRefValue(const CATechMeta        & iRole,
                              CATPolyBody*  & oRoleValue) = 0;              // for PolyBody

  virtual HRESULT GetRefValue(const CATechMeta  & iRole,
                               CATLISTP(CATPolyBody)  & oPolyBodyList) = 0; // for PolyBodyList
  virtual HRESULT GetRefValue(const CATechMeta        & iRole,
                              CATPolyPolygon2D*  & oRoleValue) = 0;              // for PolyPolygon2D

  /*
  * Compare : Checks if the capture and redo reference files match or not
  * @return
  *   Returns S_OK if the files match
  */
  virtual HRESULT Compare() = 0;

  /*
  * RegisterObserver : Registers an observer which will be notified by the ref manager if  
  *                    capture and redo reference files don't match
  * @return
  *   Returns S_OK if the current behavior is CATechBehavior_Redo
  */
  virtual HRESULT RegisterObserver(CATIRefObserver * ipRefObserver) = 0;

  /*
  * UnregisterObserver : Unregisters an observer which was to be notified by the ref manager if  
  *                      capture and redo reference files don't match
  * @return
  *   Returns S_OK if the current behavior is CATechBehavior_Redo and the removal was succesful
  */
  virtual HRESULT UnregisterObserver(CATIRefObserver * ipRefObserver) = 0;

  /*
  * SetInputDirectory : Set the directory path from which reference data is to be read.
  * @param iDirectory : The directory path for reading the reference file
  * @return
  *   Returns S_OK always
  */
  virtual HRESULT SetInputDirectory(const CATUnicodeString & iDirectory) = 0;

  /*
  * SetInputDirectory : Set the directory path from which reference data is to be read.
  * @param iDirectory : The directory path for writing the reference file
  * @return
  *   Returns S_OK always
  */
  virtual HRESULT SetOutputDirectory(const CATUnicodeString & iDirectory) = 0;

  /*
  * SetTolerance : Set the tolerance for comparing values
  * @param iTol : The tolerance value
  * @return
  *   Returns S_OK always
  */
  virtual HRESULT SetTolerance(const CATTolerance & iTol) = 0;

  /*
  * StartWriting : writes the version
  */
  virtual HRESULT StartWriting() = 0;

  /*
  * StartReading : reads the version
  */
  virtual HRESULT StartReading() = 0;

};

#endif
