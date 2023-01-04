/* -*-C++-*- */
#ifndef CATToSort_H
#define CATToSort_H
// COPYRIGHT DASSAULT SYSTEMES 2011

//===================================================================
//===================================================================
//
// CATToSort: class dedicated to sort a list
//
//===================================================================
//===================================================================
// July 2011    Creation                         R. Rorato
//===================================================================

#include "CATCGMVirtual.h"
#include "CATMathInline.h"
#include "CATListOfInt.h"
#include "CATListOfDouble.h"
#include "CATCGMNewArray.h"
#include "PersistentCell.h"

class CATCGMOutput;

#define IndexMaxSize 2      

class ExportedByPersistentCell CATToSort : public CATCGMVirtual
{
public:
  //------------------------------------------------------------------------------
  // Constructor
  //------------------------------------------------------------------------------
  CATToSort(CATListOfDouble& iValues, CATListOfInt& iIndexes);
  CATToSort(const double iValue1, const double iValue2, const int iIndex1, const int iIndex2);

  CATCGMNewClassArrayDeclare;        // Pool allocation

  //------------------------------------------------------------------------------
  // Destructor
  //------------------------------------------------------------------------------
  virtual ~CATToSort();

  //------------------------------------------------------------------------------
  // Compare 2 instances
  //------------------------------------------------------------------------------
  static int Compare2Values(CATToSort* iValue1, CATToSort* iValue2);

  void Dump(CATCGMOutput& ioOS);

  //------------------------------------------------------------------------------
  // Data access
  //------------------------------------------------------------------------------
  INLINE double GetValue(const int iIndexNumber) { return _Value[iIndexNumber]; };
  INLINE int    GetIndex(const int iIndexNumber) { return _Index[iIndexNumber]; };

  //==============================================================================
  // Private section
  //==============================================================================
private :
  CATListOfDouble _Value;
  CATListOfInt    _Index;
};

//------------------------------------------------------------------------------
#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByPersistentCell 
CATLISTPP_DECLARE_TS(CATToSort, 10)
//------------------------------------------------------------------------------

#endif
