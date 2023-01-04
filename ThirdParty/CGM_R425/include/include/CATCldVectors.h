//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2006
//==============================================================================================================
// CATCldVectors
//==============================================================================================================
// 07-Oct-2009 - DNR - Suppression du #ifdef , aujourd'hui cette variable vaut toujours TRUE.
// 16-Jan-2006 - JLH - Création.
//==============================================================================================================

#ifndef CATCldVectors_H
#define CATCldVectors_H

#include "CATCldUniCell.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldVectors ;
#else
extern "C" const IID IID_CATCldVectors ;
#endif

/**
 * Interface for the CloudEditor entity <tt>CATCldVectors</tt>.<br>
 * @see CATCldGenEntity, CATCldCell, CATCldUniCell
 */

class ExportedByCATGMGeometricInterfaces CATCldVectors : public CATCldUniCell
{
  CATDeclareInterface ;

public:

//==============================================================================================================
// CATCldVectors characteristics.
//==============================================================================================================

  /**
   * Sets the reference cell.<br>
   * If there was a previous defined reference, we delete the associated vectors.
   */
  virtual void SetReference (const CATCldUniCell* iCell) = 0 ;

  /**
   * Gets the reference cell.
   */
  virtual const CATCldUniCell* GetReference() = 0 ;

//==============================================================================================================
// Specific points management for the CATCldVectors.
//==============================================================================================================

//--------------------------------------------------------------------------------------------------------------
// "Add" methods.
//--------------------------------------------------------------------------------------------------------------

  /**
   * Adds a vector given by its coordinates and the coordinates of its origin.
   */
  virtual int AddVector (const float   iOrigin[3],
                         const float   iVector[3],
                         const CATBoolean iDirect = TRUE) = 0 ;

  /**
   * Adds a vector given by its coordinates and its origin defined as the <tt>iNoPoint</tt>'s point of the
   * reference cell.<br>
   * <b>CAUTION:</b> An exception is raised if a reference cell has not been given.
   */
  virtual int AddVector (const int     iNoPoint,
                         const float   iVector[3],
                         const CATBoolean iDirect = TRUE) = 0 ;

//--------------------------------------------------------------------------------------------------------------
// "Set" methods.
//--------------------------------------------------------------------------------------------------------------

  /**
   * Sets the origin of a vector.<br>
   * <b>CAUTION:</b> An exception is raised if the vector has a reference as origin.
   */
  virtual void SetOrigin (const int   iNoVector,
                          const float iOrigin[3]) = 0 ;

  /**
   * Sets the origin of a vector.<br>
   * <b>CAUTION:</b> An exception is raised if a reference cell has not been given.
   */
  virtual void SetOrigin (const int iNoVector,
                          const int iNoPoint) = 0 ;

  /**
   * Sets the coordinates of a vector.
   */
  virtual void SetVector (const int   iNoVector,
                          const float iVector[3]) = 0 ;

  /**
   * Sets the orientation of a vector.
   */
  virtual void SetOrientation (const int     iNoVector,
                               const CATBoolean iDirect) = 0 ;

  /**
   * Adds a vector given by its coordinates and the coordinates of its origin.<br>
   * <b>CAUTION:</b> An exception is raised if the vector has a reference as origin.
   */
  virtual void SetVector (const int     iNoVector,
                          const float   iOrigin[3],
                          const float   iVector[3],
                          const CATBoolean iDirect = FALSE) = 0 ;

  /**
   * Adds a vector given by its coordinates and its origin defined as the <tt>iNoRef</tt>'s point of the
   * reference cell.<br>
   * <b>CAUTION:</b> An exception is raised if a reference cell has not been given.
   */
  virtual void SetVector (const int     iNoVector,
                          const int     iNoPoint,
                          const float   iVector[3],
                          const CATBoolean iDirect = FALSE) = 0 ;

//--------------------------------------------------------------------------------------------------------------
// "Get" methods.
//--------------------------------------------------------------------------------------------------------------

  /**
   * Gets the origin of a vector.
   */
  virtual void GetOrigin (const int iNoVector,
                          float     oOrigin[3]) = 0 ;

  /**
   * Gets the origin of a vector.<br>
   * <b>CAUTION:</b> returns 0 if the vector has no reference as origin.
   */
  virtual void GetOrigin (const int  iNoVector,
                          int       &oNoPoint) = 0 ;

  /**
   * Gets the coordinates of a vector.
   */
  virtual void GetVector (const int iNoVector,
                          float     oVector[3]) = 0 ;

  /**
   * Gets the orientation of a vector.
   */
  virtual CATBoolean IsDirect (const int iNoVector) = 0 ;

  /**
   * Gets the vector.
   */
  virtual void GetVector (const int  iNoVector,
                          float      oOrigin[3],
                          float      oVector[3],
                          CATBoolean   &oDirect) = 0 ;
} ;

CATDeclareHandler (CATCldVectors, CATCldUniCell) ;

#endif
