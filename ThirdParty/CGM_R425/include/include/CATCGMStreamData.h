#ifndef CATCGMStreamData_h_
#define CATCGMStreamData_h_

// COPYRIGHT DASSAULT SYSTEMES 2004
/** @CAA2Required */

//=============================================================================
// Mar. 05 RI0486478 : _OrderedLinkedObjectStream,
//                     _LinkedObjectStreamStage,
//                     _pCGMVersionDefinition,
//                     _WithExtraBits,
//                     _pPublishObject,
//                     _NbStreamedObjects                                 HCN
// Apr. 05 Migration de CATMathStream\CATCGMStream vers la classe
//           d'implementation CATMathStreamImpl\CATCGMStreamImpl          HCN
// Jul. 09 Suppression du StreamCompact                                   VUC
//============================================================================= 

#include "CATDataType.h"
#include "CATBoolean.h"
// pour size_t sous unix
#include "stdio.h"


class CATICGMContainer;
class CATExtCGMReplay;
class CATCGMStreamAttrObj;
class CATCGMMapCATULONGPTR;
class CATListPtrCATICGMObject;
class CATICGMUnknown;
class CATCGMVersionDefinition;

class CATCGMStreamData
{
public :
  CATCGMStreamData();
  ~CATCGMStreamData();

  CATICGMContainer*        _pAssociatedContainer;  // Container utile a l'Unstream pour FindObjectFromTag
  CATExtCGMReplay*         _pAssociatedReplay;     // Identification d'un Contexte de document CATCGMReplay
  size_t                   _ObjectStart;          // Gestion des attributs
  size_t                   _ObjectSize;           
  CATULONG32               _LinksToProcess;
  CATULONG32               _ProcessedLinks;
  CATULONG32               _NumberOfObjects;

  CATListPtrCATICGMObject* _pListLinkedObjects;
  short                    _LevelAssociatedContainer; // Gestion des empilages de transactions
  short                    _LevelExternalWeakLinks;    
  short                    _IsStreamingForBackwardCompatibility;  // CATBack
  int                      _nbAttrObj;                // Gestion des attributs
  int                      _maxAttrObj;
  CATCGMStreamAttrObj*     _pTabAttrObj;   
  CATCGMMapCATULONGPTR*    _ForUnstreamByInjection;

  CATBoolean               _LinkedObjectStreamStage;
  CATCGMVersionDefinition* _pCGMVersionDefinition;
  short                    _WithExtraBits;
  CATICGMUnknown*          _pPublishObject;
  CATULONG32               _NbStreamedObjects;
};

#endif 
