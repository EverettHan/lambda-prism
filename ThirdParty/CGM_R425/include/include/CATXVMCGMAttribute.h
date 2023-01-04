//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2009
//==============================================================================================================
// CATXVMCGMAttribute
//==============================================================================================================
// Creation: OST Jan-2009
//==============================================================================================================

#ifndef _CATXVMCGMAttribute_H_
#define _CATXVMCGMAttribute_H_

#include "CATCGMStreamAttribute.h"

/**
 * Abstract top class for the attributes storing XVM References.
 */
class CATCGMJournal ;
class CATGeometry ;
class CATBody ;
class CATLiveBody;

#include "CATGeometryType.h"
#include "IUnknown.h"
#include "CATLISTP_CATBaseUnknown.h"
#include "CATListOfCATGeometries.h"
#include "CATListOfInt.h"


class ExportedByYP00IMPL CATXVMCGMAttribute : public CATCGMStreamAttribute
{

//==============================================================================================================
// Public Part.
//==============================================================================================================

public:
	virtual HRESULT GetXVMRef(CATBaseUnknown *&oXVMRef, const CLSID& iType) const = 0 ;

	virtual HRESULT SetXVMRef(CATBaseUnknown * iXVMRef) = 0 ;

	virtual HRESULT SetAssociatedObject(CATGeometry * iObjectToAssociate) = 0 ;
	virtual HRESULT GetAssociatedObject(CATGeometry *&oAssociatedObject, CATGeometricType iRequestedType) const = 0 ;

	virtual HRESULT Synchronize(CATCGMJournal * iJournal, CATBaseUnknown * iDomain=NULL) = 0 ;

	/* Duplicates my XVMRef, under iTargetOwner.
	 * Return values :
	 *    E_INVALIDARG :  if either iTargetOwner or oNewRef is nul or not of the requested type ( E_INVALIDARG )
	 */
	virtual HRESULT DuplicateRef(CATBaseUnknown * iTargetOwner, CATBaseUnknown * &oNewRef) const = 0 ;
	
	/* Copies all the connections of my XVMRef connecting the geometries listed in iDomain,
     *        and the components pointed by the copied connections, inside ioTargetRef
     * Return values :
     *    E_INVALIDARG :  if ioTargetRef is nul or not of the requested type ( XVMRef )
	 */
	virtual HRESULT ExtractDomain(const CATLISTP(CATGeometry) & iDomain, CATBaseUnknown * ioTargetRef) const = 0 ;

  /* 
   * Deprecated (21 - 04 - 2010) - will be removed 
   */
  virtual HRESULT Extract(const CATLISTP(CATBaseUnknown) & iDomainXVM, const CATLISTP(CATGeometry) & iDomainCGM, CATBaseUnknown * ioTargetRef,
						    CATCGMJournal * iCGMJournal, int iJournalMode = 0 ) const = 0 ;

  /* Extraction method used for Copy/Paste 
   * The creation of XVMRef in target body is done only if there are constraints created
   * @param iStatelessXVMBody is FALSE during copy ( the body in the clipboard is stateless )
   *                             TRUE during paste
   */
  virtual HRESULT Extract(const CATLISTP(CATBaseUnknown) & iDomainXVM, const CATLISTP(CATGeometry) & iDomainCGM, CATLiveBody* iLiveBody,
						    CATCGMJournal * iCGMJournal, int iJournalMode, CATBoolean iStatelessXVMBody = FALSE ) const = 0 ;

	/* Concatenates the input references listed in iListOfRefs under the 
     * Return values :
     *    E_INVALIDARG :  if ioTargetRef is nul or not of the requested type ( XVMRef )
     *                    or if ANY of iListOfRefs is non nul but not of requested type. 
	 */
	virtual HRESULT ConcatenateRefs(const CATLISTP(CATBaseUnknown)& iListOfRefs, CATBaseUnknown * ioTargetRef) const = 0 ;

	/* Creates a new XVM reference of type XVMBodyCGM under an empty XVMCGMAttribute
     * Return values :
     *    E_FAIL       :  if this XVMCGM attribute already holds a XVMRef
     *    E_INVALIDARG :  if ioTargetRef is not of the requested type ( XVMRef )
	 */
	virtual HRESULT CreateXVMBody(CATBaseUnknown * &oNewXVMBody, CATBaseUnknown * iTargetOwner=NULL) = 0 ;

	/* Creates a new XVM reference of type XVMBodyCGM under an empty XVMCGMAttribute.
	 *   This XVMBody which will not be subject to State management ( and so will not be subject to Undo/Redo )
     * Return values :
     *    E_FAIL       :  if this XVMCGM attribute already holds a XVMRef
     *    E_INVALIDARG :  if ioTargetRef is not of the requested type ( XVMRef )
	 */
	virtual HRESULT CreateStatelessXVMBody(CATBaseUnknown * &oNewXVMBody, CATBaseUnknown * iTargetOwner=NULL) ;

	virtual HRESULT SetCGMBody(CATBody* iBody) = 0 ;

	// Compares the content of 2 XVMCGMAttributes based on a bodymapping.
	// iNewCells is an array of CATLISTP(CATGeometry), of dimension : iRefCells.Size() + 1
	// For each iRefCells[i], the list of new cells is stored in iNewCells[i]. iNewCells[0] is not used.
	// Caller has responsibility to delete[] iNewCells, as well as iData and oInfo if not nul.
	// So far iData and oInfo are not used.
	// Return codes : 
	//    0   : 'this' attribute is the image of iRefAttribute for the provided mapping.
	//   -1   : invalid arg, one of iRefAttribute, iRefBody, iNewBody, iNewCells is nul.
	//  other : 'this' attribute  is not an image of iRefAttribute for the provided mapping.
	virtual int Compare(const CATXVMCGMAttribute * iRefAttribute,
                        const CATGeometry * iRefBody, const CATGeometry * iNewBody,
						const CATLISTP(CATGeometry) & iRefCells, const CATLISTP(CATGeometry) * iNewCells,
						void *  iData = NULL,
						void ** oInfo = NULL) const = 0 ;

	CATXVMCGMAttribute() ;
	virtual ~CATXVMCGMAttribute() ;
} ;

#endif
