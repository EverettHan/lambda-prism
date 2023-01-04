/* -*-c++-*- */
#ifndef CATCGMTopologyImpl_H
#define CATCGMTopologyImpl_H
/* -*-c++-*- */

// COPYRIGHT DASSAULT SYSTEMES 2015
//=============================================================================
// CATCGMTopologyImpl : Abstract Mother Class of ANY Topological Object in the Geometric Modeler
//
// Motivation :
//   This class allows to manage in the same CGMContainer both exact & polyhedral objects, 
//   with different derived implementations of common topological interfaces 
//   (from CATTopology class to CATCell & CATDomain derived classes).
//
// Example : 
//   Both CATCXTopoly & CATGMPolyTopology classes implement the CATTopology interface
//   and derive from the CATCGMTopologyImpl class.
//
//=============================================================================
// July.15 Creation                                                       DPS (approuved by AAD)
//         Integration between CATCXTopology & CATCGMObject classes       DPS (approuved by AAD)
//         Second direct derivation into CATGMPolyTopology class          DPS (approuved by AAD)
//
// Sept.15 Add static GetImplementCGMTopo()                               DPS
// Sept.15 Add GetAllTouchedCells to allow checker/cleaner 
//         of touched cells both exact & polyhedral                       DPS
// Jan. 17 Add static services to control the returned implementations    DPS
//         + define macros at the end of the header
// Nov. 19 Add virtual GetAllTopologies, to make it poly compliant        DPS
//=============================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMObject.h"    // derivation
#include "CATGeometryType.h"
#include "ListPOfCATTopology.h"

#include "CATIACGMLevel.h"
#include "CATErrorDef.h"     // HRESULT
#include "CATMathConstant.h" // CATAngle
#include "CATBoolean.h"
#include "CATSysBoolean.h"


class CATTopology;
class CATCXTopology;
class CATGMPolyTopology;

class CATBody;

class CATCXBody;

class CATCXDomain;
class CATCXLump;
class CATCXShell;
class CATCXEdgeDomain;
class CATCXWire;
class CATCXLoop;
class CATCXVertexInFace;
class CATCXVertexInVolume;

class CATCXCell;
class CATCXVolume;
class CATCXFace;
class CATCXEdge;
class CATCXVertex;

class CATCGMObjectHashTable;
struct CATCGMVisuData;


//------------------------------------------------------------------------------------
// Basic class for all the implementations of topological objects in the CGMContainer
//------------------------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATCGMTopologyImpl : public CATCGMObject
{

public :

  //----------------------------------------------------------------------
  // Object Services retrieving the classified implementation of an interface
  //----------------------------------------------------------------------

  //----------------------------------------------------------------------
  // CATCGMTopologyImpl
  //----------------------------------------------------------------------

  // Basic service retrieving the implementation of an interface with a given expected type
  // *** Wrapping of CATCGMObject::GetImplementCGM with safe cast to CATCGMTopologyImpl ***
  // Returns NULL if the implementation of this interface doesn't derive from CATCGMTopologyImpl
  static CATCGMTopologyImpl * GetImplementCGMTopo(const CATICGMObject * iInterface, CATGeometricType iTypeReference=CATTopologyType);


  // Advanced service retrieving the implementation of a topological interface with a given expected type
  // The service will certify the request is consistent
  // Returns NULL if the implementation of this interface doesn't derive from CATCGMTopologyImpl
  static CATCGMTopologyImpl * GetControlledCGMTopologyImpl(const CATTopology * iTopoInterface, CATGeometricType iTypeReference=CATTopologyType);


  // Advanced service retrieving the implementation of a topological interface with a given expected type
  // The service will certify the request is consistent
  // Throws an error if the implementation of this interface doesn't derive from CATCGMTopologyImpl
  static CATCGMTopologyImpl * GetSecureCGMTopologyImpl(const CATTopology * iTopoInterface, CATGeometricType iTypeReference=CATTopologyType);


  //----------------------------------------------------------------------
  // CATCXTopology
  //----------------------------------------------------------------------

  // Basic service retrieving the exact (CX) implementation of an interface with a given expected type
  // *** Wrapping of CATCGMObject::GetImplementCGM with safe cast to CATCGMTopologyImpl ***
  // Returns NULL if the implementation of this interface doesn't derive from CATCXTopology
  static CATCXTopology       * GetImplementCXTopology       (const CATTopology * iInterface);

  // Dedicated services for each CX implementation              // CATTopology * ? A mediter.
  static CATCXBody           * GetImplementCXBody           (const CATICGMObject * iInterface);

  static CATCXDomain         * GetImplementCXDomain         (const CATICGMObject * iInterface);
  static CATCXLump           * GetImplementCXLump           (const CATICGMObject * iInterface);
  static CATCXShell          * GetImplementCXShell          (const CATICGMObject * iInterface);
  static CATCXEdgeDomain     * GetImplementCXEdgeDomain     (const CATICGMObject * iInterface);
  static CATCXWire           * GetImplementCXWire           (const CATICGMObject * iInterface);
  static CATCXLoop           * GetImplementCXLoop           (const CATICGMObject * iInterface);
  static CATCXVertexInFace   * GetImplementCXVertexInFace   (const CATICGMObject * iInterface);
  static CATCXVertexInVolume * GetImplementCXVertexInVolume (const CATICGMObject * iInterface);

  static CATCXCell           * GetImplementCXCell           (const CATICGMObject * iInterface);
  static CATCXVolume         * GetImplementCXVolume         (const CATICGMObject * iInterface);
  static CATCXFace           * GetImplementCXFace           (const CATICGMObject * iInterface);
  static CATCXEdge           * GetImplementCXEdge           (const CATICGMObject * iInterface);
  static CATCXVertex         * GetImplementCXVertex         (const CATICGMObject * iInterface);

  // Advanced service retrieving the exact (CX) implementation of a topological interface with a given expected type
  // The service will certify the request is consistent
  // Returns NULL if the implementation of this interface doesn't derive from CATCXTopology
  static CATCXTopology       * GetControlledCXTopology       (const CATTopology * iInterface, CATGeometricType iTypeReference=CATGeometryType);

  // Dedicated services for each CX implementation
  static CATCXBody           * GetControlledCXBody           (const CATICGMObject * iInterface);

  static CATCXDomain         * GetControlledCXDomain         (const CATICGMObject * iInterface);
  static CATCXLump           * GetControlledCXLump           (const CATICGMObject * iInterface);
  static CATCXShell          * GetControlledCXShell          (const CATICGMObject * iInterface);
  static CATCXEdgeDomain     * GetControlledCXEdgeDomain     (const CATICGMObject * iInterface);
  static CATCXWire           * GetControlledCXWire           (const CATICGMObject * iInterface);
  static CATCXLoop           * GetControlledCXLoop           (const CATICGMObject * iInterface);
  static CATCXVertexInFace   * GetControlledCXVertexInFace   (const CATICGMObject * iInterface);
  static CATCXVertexInVolume * GetControlledCXVertexInVolume (const CATICGMObject * iInterface);

  static CATCXCell           * GetControlledCXCell           (const CATICGMObject * iInterface);
  static CATCXVolume         * GetControlledCXVolume         (const CATICGMObject * iInterface);
  static CATCXFace           * GetControlledCXFace           (const CATICGMObject * iInterface);
  static CATCXEdge           * GetControlledCXEdge           (const CATICGMObject * iInterface);
  static CATCXVertex         * GetControlledCXVertex         (const CATICGMObject * iInterface);

  // Advanced service retrieving the exact (CX) implementation of a topological interface with a given expected type
  // The service will certify the request is consistent
  // Throws an error if the implementation of this interface doesn't derive from CATCXTopology
  static CATCXTopology       * GetSecureCXTopology       (const CATTopology * iInterface, CATGeometricType iTypeReference=CATTopologyType);

  // Dedicated services for each CX implementation
  static CATCXBody           * GetSecureCXBody           (const CATTopology * iInterface);

  static CATCXDomain         * GetSecureCXDomain         (const CATTopology * iInterface);
  static CATCXLump           * GetSecureCXLump           (const CATTopology * iInterface);
  static CATCXShell          * GetSecureCXShell          (const CATTopology * iInterface);
  static CATCXEdgeDomain     * GetSecureCXEdgeDomain     (const CATTopology * iInterface);
  static CATCXWire           * GetSecureCXWire           (const CATTopology * iInterface);
  static CATCXLoop           * GetSecureCXLoop           (const CATTopology * iInterface);
  static CATCXVertexInFace   * GetSecureCXVertexInFace   (const CATTopology * iInterface);
  static CATCXVertexInVolume * GetSecureCXVertexInVolume (const CATTopology * iInterface);

  static CATCXCell           * GetSecureCXCell           (const CATTopology * iInterface);
  static CATCXVolume         * GetSecureCXVolume         (const CATTopology * iInterface);
  static CATCXFace           * GetSecureCXFace           (const CATTopology * iInterface);
  static CATCXEdge           * GetSecureCXEdge           (const CATTopology * iInterface);
  static CATCXVertex         * GetSecureCXVertex         (const CATTopology * iInterface);

  //----------------------------------------------------------------------
  // CATGMPolyTopology
  //----------------------------------------------------------------------

  // Advanced service retrieving the polyhedral implementation of a topological interface with a given expected type
  // The service will certify the request is consistent
  // Returns NULL if the implementation of this interface doesn't derive from CATGMPolyTopology
  static CATGMPolyTopology * GetControlledGMPolyTopology(const CATTopology * iTopoInterface, CATGeometricType iTypeReference=CATTopologyType);


  //----------------------------------------------------------------------

  // Logical differenciation between exact & polyhedral topological objects
  // in order to prevent topological operators from an unexpected type of input bodies
  static CATBoolean IsCGMExact(const CATTopology * iTopoInterface);
  static CATBoolean IsCGMPolyhedral(const CATTopology * iTopoInterface);


  //----------------------------------------------------------------------
  // Object Management
  //----------------------------------------------------------------------

  // Safe Casts
  virtual CATCGMTopologyImpl * CastToCGMTopologyImpl()   const; 
  virtual CATCXTopology      * CastToCATCXTopology()     const;
  virtual CATGMPolyTopology  * CastToCATGMPolyTopology() const; 

  CATBoolean IsExact() const;
  CATBoolean IsPolyhedral() const;


  //----------------------------------------------------------------------
  // Visu Management (BuildRep)
  //----------------------------------------------------------------------

  // Fill the CATCGMVisuData object instanciated by the caller, computing information (Bounded cells, Sharpness ...) for the visu management of cells CATVertex, CATEdge, CATFace.
  // Please note that the last optional argument iMinSharpAngle is useless for CATFace objects.
  // Returns S_OK if the information has been computed, S_FALSE if the information has been read on the cell, E_FAIL if the CATCGMVisuData cannot be filled (CATVolume ...)
  virtual HRESULT ComputeCGMVisuData(CATBody * iBody, CATCGMVisuData * iopCGMVisuData, unsigned int iRequestedDataMask, CATAngle * iMinSharpAngle = NULL);

  // Clean the visu information data which had been stored in the CATCell objects in order to speed up the calls to ComputeCGMVisuData
  virtual void DeleteAllVisuData(); 


  //----------------------------------------------------------------------
  // Virtual CATCGMFusion methods
  //----------------------------------------------------------------------
  virtual CATLONG32  GetHighestDimension() const=0;
  virtual short      GetType()=0;

  //----------------------------------------------------------------------
  // Checker/Cleaner services
  //----------------------------------------------------------------------
  virtual void GetAllTouchedCells( CATLISTP(CATTopology)& ioResult)=0;

  virtual CATCGMObjectHashTable * GetAllTopologies()=0; // Rq : contient egalement this


protected :

  // Constructor for derived classes only
  CATCGMTopologyImpl(); 

  // No destructor while there is no data member & no clean to do


private:
  
  // Copy constructor & operator = without any implementation
  CATCGMTopologyImpl(const CATCGMTopologyImpl&);
  CATCGMTopologyImpl& operator = (const CATCGMTopologyImpl&);

 };

   // Returns NULL if the implementation of this interface doesn't derive from CATCGMTopologyImpl
#define GetControlledCATCGMTopologyImpl(pointer)           CATCGMTopologyImpl::GetControlledCGMTopologyImpl(pointer)
#define GetControlledCATCGMTopologyImplType(pointer,type)  CATCGMTopologyImpl::GetControlledCGMTopologyImpl(pointer,type)

 // Throws an error if the implementation of this interface doesn't derive from CATCGMTopologyImpl
#define GetSecureCATCGMTopologyImpl(pointer)               CATCGMTopologyImpl::GetSecureCATCGMTopologyImpl(pointer)
#define GetSecureCATCGMTopologyImplType(pointer,type)      CATCGMTopologyImpl::GetSecureCATCGMTopologyImpl(pointer,type)

 // Returns NULL if the implementation of this interface doesn't derive from CATGMPolyTopology
#define GetControlledCATGMPolyTopology(pointer)            CATCGMTopologyImpl::GetControlledGMPolyTopology(pointer)
#define GetControlledCATGMPolyTopologyType(pointer,type)   CATCGMTopologyImpl::GetControlledGMPolyTopology(pointer,type)

 // Returns NULL if the implementation of this interface doesn't derive from CATCXTopology
#define GetControlledCATCXTopology(pointer)                CATCGMTopologyImpl::GetControlledCXTopology(pointer)
#define GetControlledCATCXTopologyType(pointer,type)       CATCGMTopologyImpl::GetControlledCXTopology(pointer,type)

 // Throws an error if the implementation of this interface doesn't derive from CATCXTopology
#define GetSecureCATCXTopology(pointer)                    CATCGMTopologyImpl::GetSecureCXTopology(pointer)
#define GetSecureCATCXTopologyType(pointer,type)           CATCGMTopologyImpl::GetSecureCXTopology(pointer,type)

#endif

