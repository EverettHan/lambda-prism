//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyActiveCacheObserver
//
//===================================================================
// 14/11/17 F1Z : Creation
// DD/MM/YY
//===================================================================
#ifndef CATPolyActiveCacheObserver_H
#define CATPolyActiveCacheObserver_H

// Polyhedral Mathematics
#include "CATPolyObserver.h"

template<typename T>
class CATPolyActiveCacheObserver : public CATPolyObserver<CATPolyActiveCacheObserver<T> >
{
public:
   // Call made before the data is added to the active data set to stop the operation or not.
   virtual bool IsOkToAdd   (const T & iDataToAdd  ) { return true; };

   // Call made after the data is found in the active data set.
   virtual void DataFound   (const T & iDataFound  ) {};

   // Call made after the data is added to the active data set.
   virtual void DataAdded   (const T & iDataAdded  ) {};

   // Call made after the data is removed from the active data set.
   virtual void DataRemoved (const T & iDataRemoved) {};

   // Call made before the data is completly free
   virtual void DataFree    (const T & iDataFree) {};
};

#endif

