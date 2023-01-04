#ifndef CATGeoImplicitFactory_H
#define CATGeoImplicitFactory_H

// COPYRIGHT DASSAULT SYSTEMES  2021
//=============================================================================
//
//  Implicit objects management in the CGMContainer
//
//=============================================================================
// Usage Notes:
//
//    Please, note that the default behavior of the CATGeoImplicitFactory consists in instanciating all the implicit objects in the "Implicit" mode, 
//    excepted for the bodies if the root GeoFactory is itself Explicit and only in this case.
//    -> Explanation here :
//    1. Create CATBody objects in the "Explicit" mode means that the caller is in charge of its Life Cycle and has to call explicitely the "Remove()" method in order to delete it.
//    2. Instanciate all the other types in the "Implicit" mode means that the caller has to choose between :
//          attaching the object to another one in order to create direct or indirect dependency with at least one body,
//       or changing the mode from Implicit to Explicit thanks to the method "SetMode(CATCGMExplicit)"
//       -> in the first case, Remove bodies (and only bodies) with all dependancies leads to delete all the implicit objects in the Factory
//       -> in the second case, the caller has to use explicitely the Remove() method on all explicit objects
//
//=============================================================================
// Creation: WZC, Nov. 2021 from GMPoly equivalent
//=============================================================================

#include "CATIACGMLevel.h"
#include "YP00IMPL.h" 
#include "CATBaseUnknown.h"
#include "CATICGMContainer.h"

#include "CATListValCATCrvParam.h"
#include "CATListValCATSurParam.h"

#include "CATBoolean.h"
#include "CATSysBoolean.h"

#ifndef NULL
#define NULL 0
#endif

class CATGeoFactory;
class CATGeoFactoryProtected;
class CATCGMContainer;

class CATBody;  
class CATVolume;  
class CATFace;  
class CATEdge;  
class CATVertex;  
class CATLump;  
class CATShell;  
class CATLoop;  
class CATWire;  
class CATVertexInFace;  
class CATVertexInVolume;  

class CATSurface;
class CATCurve;
class CATSurParam;
class CATCrvParam;

class CATGeoImplicitSurface;

class CATMathVector;
class CATMathTransformation;


class ExportedByYP00IMPL CATGeoImplicitFactory : public CATBaseUnknown
{
	//CATDeclareInterface;

public:

  // No constructor, 
  // use the static method GetImplicitFactory() to retrieve or create the instance of CATGeoImplicitFactory attached to a specific CATGeoFactory

  //---------------------------------------------------------------------------
  // GetImplicitFactory
  //---------------------------------------------------------------------------

  // No creation here
  // Just a way to retrieve a CATGeoImplicitFactory attached to the Factory of the CGMContainer
  // If not, retrieve the CATGeoImplicitFactory attached to the implicit Factory of the CGMContainer 
  // (only if different from the first one)
  // The optional argument oImplicitFactory allows the caller to know the nature 
  // of the referencial GeoFactory from which the returned GeoImplicitFactory has been retrieved
  static CATGeoImplicitFactory * RetrieveGeoImplicitFactoryFromContainer(CATICGMContainer * iCGMContainer, CATBoolean * oImplicitFactory=NULL);

  
  // ************************************************************************************************
  // *** Retrieve or Create an instance of CATGeoImplicitFactory attached to a specific CATGeoFactory ***
  // ************************************************************************************************
  static CATGeoImplicitFactory * GetImplicitFactory(CATGeoFactory * iFactory, CATBoolean iCreationMode=TRUE);

  // ---------------------------------------------------
  // No destructor, use Release() instead


  // ========================================================================
  //   Object management SERVICE
  // ========================================================================

  virtual CATBoolean IsNativeOfGeoImplicitFactory(const CATICGMObject * ipICGMObject)=0;


public:
  
  // ========================================================================
  //   GEOMETRY
  // ========================================================================

  /**
  * Creates an implicit surface
  *<br> This object is mainly used by the GMImplicitObjects framework.
  * @param iVolume : the volume within which the surface will be evaluated
  * @return
  *   The pointer to the created CATGeoImplicitSurface.
  * This object will be created in an implicit mode, even if the Root GeoFactory is itself Explicit.
  */
  virtual CATGeoImplicitSurface * CreateGeoImplicitSurface(CATVolume* iWithinVolume, const CATUnicodeString& iExpression, const double iIsoVale = 0.0) = 0;

  //---------------------------------------------------------------------------
  // remove object from the container
  //---------------------------------------------------------------------------
  virtual void Remove(CATICGMObject*                                  iObjectToRemove, 
                      const CATICGMContainer::CATRemovingDependancies iHow = CATICGMContainer::RemoveDependancies) = 0;


  //---------------------------------------------------------------------------
  // Access to the root CATGeoFactory
  //---------------------------------------------------------------------------
  virtual CATGeoFactory * GetRootFactory() const = 0;

  //---------------------------------------------------------------------------
  // Retrieve the CATTolerance attached to the Root GeoFactory
  //---------------------------------------------------------------------------
  virtual const CATTolerance & GetTolerance() const = 0;

};


// *******************************************************
// *** DO NOT USE, UNDER INVESTIGATION, FOR DEBUG ONLY ***
// *******************************************************
// Global Create method dedicated to the CATGeoFactoryCGM class.
// Please, consider this as a private service reserved for friend classes.
ExportedByYP00IMPL CATGeoImplicitFactory * CATCreateGeoImplicitFactory(CATGeoFactoryProtected & iGeoFactoryProtected, 
                                                               CATCGMContainer        & iCGMContainer);

// CATDeclareHandler(CATGeoImplicitFactory,CATBaseUnknown);

#endif

