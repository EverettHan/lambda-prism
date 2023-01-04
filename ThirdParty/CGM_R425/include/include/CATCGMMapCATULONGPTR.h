#ifndef CATCGMMapCATULONGPTR_H
#define CATCGMMapCATULONGPTR_H
// COPYRIGHT DASSAULT SYSTEMES  2002
/** 
 * Utilitaire Table d'association entre deux ULONGPTR
 */
#include "CATDataType.h"
#include "CATBoolean.h"

#include "CATMathematics.h"
#include "CATCGMNewArray.h"
#include "CATCGMListOfCATULONGPTR.h"
#include "CATCGMVirtual.h"

#include <map>

class CATHashTabCGMULongPointers;

typedef std::map<CATULONGPTR, CATULONGPTR> CGMHashMapOfULongPointers;
typedef std::map<CATULONGPTR, CATULONGPTR>::const_iterator CGMHashMapIterator;

// -------------------------------------------------------------------------
// Map d'association de valeur de pointeur
// Created by TCX
//
// Y2021-W25 Update  by QF2
// -------------------------------------------------------------------------
class  ExportedByCATMathematics CATCGMMapCATULONGPTR  : public CATCGMVirtual
{
public:
  // Constructor
  CATCGMMapCATULONGPTR(unsigned int initialNumber = 0);
  // Destructor
  virtual ~CATCGMMapCATULONGPTR();

  CATCGMNewClassArrayDeclare;
  
  // Return Value is the number of true insertion (otherwise update)
  // en clair :
  //   If a new @param iItem is inserted, return code is 1. 
  //   If @param iItem is found, association is updated, return code is 0.
  int  Map(const CATULONGPTR iFrom /*iItem*/, const CATULONGPTR iTo /*iAssoc*/);
  
  // Return association value if @param iItem has been found.
  CATULONGPTR Search(const CATULONGPTR iFrom /*iItem*/, const CATULONGPTR iValueForNotFound ) const;
  
  // Return TRUE if @param iItem has been found, FALSE otherwise. et c'est pas plus simple ??
  CATBoolean  Locate(const CATULONGPTR iItem, CATULONGPTR &oAssoc) const;

#ifdef CATCGMMap_DEPRECATED
  // @deprecated - do not use
  int  Map(const CATCGMListOfCATULONGPTR & iFrom, const CATCGMListOfCATULONGPTR & iTo);
#endif


  // const Access to std container
  const CGMHashMapOfULongPointers & GetHashMapConst () const;


  // NE PAS UTLISER AddRef & Release dans cette classe,
  // Ils ne sont pas implémentés.... 
  virtual void AddRef();
  virtual void Release();
  

private :
  // for mother class only
  CGMHashMapOfULongPointers & GetHashMap();


  // CATHashTabCGMULongPointers *_Table;

  // New data  structure -> performance
  CGMHashMapOfULongPointers  _HashMap;

};

#endif

