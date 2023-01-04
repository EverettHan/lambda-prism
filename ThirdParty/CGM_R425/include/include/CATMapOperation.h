//============================================================================= 
// COPYRIGHT DASSAULT SYSTEMES 2017, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : QF2
//
// DESCRIPTION  : Operation structure of CATMultiProcRunner
//                
//=============================================================================
// Creation QF2 January 2020
//=============================================================================
#ifndef CATMapOperation_H
#define CATMapOperation_H

#include "CATMathFP.h"
// #include "CATMultiProcRunner.h"
// #include "CATMultiProcOperation.h"
#include <functional>
#include "CATListPV.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATIPGMMultiProcChannel;



// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
// xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

#include "CATCGMSTDSafeIncludeStart.h"
#include <vector>
#include "CATCGMSTDSafeIncludeEnd.h"
#include "CATIPGMMultiProcTaskAdapter.h"

// ------------------------------------------------------------------------------------------------
// Template Abstract Class CATMapOperation
// ------------------------------------------------------------------------------------------------
/*
* This template class allows you to split up any "loop" operation into several processes. 
* Works on ArrayMap pattern
*
* This class inherits from CATMultiProcOperation. All its virtual methods has to be
* implemented, such as WriteInput, ReadInput, Execute, ...
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
* <br> This class works in conjunction with the CATMapReducer class.
*
* @see CATMapReducer
*
* ======================
* How is it working : 
* ======================        
*                            /----------\       
*                   |----->  | slaveMap | ---> Execute -----> [Reduce] ----|
*                   |        \----------/                                  |
*                   |                                                      v
*                   |        /----------\                                  |
*                   |----->  | slaveMap | ---> Execute -----> [Reduce] ----| 
*                   |        \----------/                                  |
*   __________      |                                                      v      
*  |          |     |                                                      |        
*  | UserMap  | ----|-----> /----------\                                   |         |===========|
*  | (master) |     |       | slaveMap | ---> Execute -----> [Reduce] -->--| ------> |  $Result  |
*  |__________|     |       \----------/                                   |         |===========|
*                   |                                                      ^
*                   |       /----------\                                   |
*                   |-----> | slaveMap | ---> Execute -----> [Reduce] -----|
*                   |       \----------/                                   |
*                   |                                                      ^
*                   |       /----------\                                   |
*                   |-----> | slaveMap | ---> Execute -----> [Reduce] -----|
*                   |       \----------/
*                   |                           |                 |
*                   |                           |                 |  
*                   v                           v                 v
*               [Map Step]             [Run in parallel]     [Reduce Step]
*            HRESULT Map (...)         (using MPRunner)      HRESULT Reduce(...)
*/


template <typename T>
class CATMapOperation : public CATIPGMMultiProcTaskAdapter
{

public :
  /* Default constructor */
  CATMapOperation();

  /* Construtor */
  CATMapOperation(const std::vector<T*> & iCollection);  

  /**
  * [Map Step]
  * Split evenly your code into several operations that can be append to the CATMapReducer.
  * It calls CreateAMap() to create a new instance of your operation. 
  * @param iNumberOfMap
  *   The number of sub maps you want to create and run in parallel.
  */
  HRESULT Map(CATULONG32 &iMasterId, CATUINT32 iNumberOfMap, CATListPV & oSplitMapList) const;

  /**
  * Create an instance with a partition of your input Collection. 
  * This method will be called by Map() above. 
  * @param iSubCollection
  *   A reference to a partitionned segment that have been computed by Map().
  * @return 
  *   A pointer to a new map operation that will be run in parallel.
  */
  virtual CATMapOperation * CreateAMap(const std::vector<T*> & iSubCollection) const = 0;

  /**
  * [Reduce Step]
  * Regroup your map results after processing. 
  * @param ipMapResult
  *   A single map result to be merged down into this master map. 
  */
  virtual HRESULT Reduce(CATGeoFactory *ipMainFactory, CATMapOperation & iSubMapResult) = 0;


  CATULONG32 GetMasterId() const;

protected :

  // INLINE virtual CATBoolean IsMap() const { return TRUE; }

  INLINE const std::vector<T*> & GetCollection () const { return _UCollection; }
  INLINE void  AddElement (const T * iElement) { if (iElement) _UCollection.push_back((T*)iElement); }

    /* Destrutor */
  virtual ~CATMapOperation(); 


private :

  /* forbiden copy constructor*/
  CATMapOperation (const CATMapOperation & iMPOperation);
  /* forbiden operator */
  CATMapOperation & operator = (const CATMapOperation & iMPOperation);

  
  INLINE void SetMasterId(CATULONG32 iMasterId) { _MasterId = iMasterId; }  


/* Internal Data */
  std::vector<T*>  _UCollection;
  size_t           _Size;


  CATULONG32       _MasterId; // in slave case
};

// ==================================================================================== //
// Implement of CATMapOperation en test
// ==================================================================================== //


template <typename T>
CATMapOperation<T>::CATMapOperation() :
CATIPGMMultiProcTaskAdapter(),
_Size(0),
_MasterId(0)
{
}

// -----------------------------------------------------------------------------------
// Consttuctor 1
// -----------------------------------------------------------------------------------
template <typename T>
CATMapOperation<T>::CATMapOperation(const std::vector<T*> & iCollection):
CATIPGMMultiProcTaskAdapter(),
_UCollection(iCollection),
_Size(iCollection.size()),
_MasterId(0)
{
}



// -----------------------------------------------------------------------------------
// Destructor 
// -----------------------------------------------------------------------------------
template <typename T>
CATMapOperation<T>::~CATMapOperation()
{
  _Size=0;
}


// -----------------------------------------------------------------------------------
// Segment
// -----------------------------------------------------------------------------------
template <typename T>
HRESULT CATMapOperation<T>::Map(CATULONG32 &MasterId, CATUINT32 iNumberOfMap, CATListPV &oSplitMapList) const
{
  HRESULT hr = S_OK;

  size_t nbElements = _UCollection.size();

  if (nbElements < (size_t) iNumberOfMap)
    return E_FAIL;

  if ( this->GetMasterId() )
    return E_FAIL;

  // need copy constructor
  // 1.a Compute number sub operation 		
  // CATUINT32 NbSubIteration  ~= ( _NbElements / iNumberOfSegments);
  CATUINT32 NbSubIterations  = 0;

  double dNbIterations = (double ) nbElements;
  double dNbSegments   = (double ) iNumberOfMap;
  NbSubIterations      = CATFloor(dNbIterations / dNbSegments); // planché


  // Reste = CATRound (NbOperations - (dNbOperationPerProc * dNbProcess));
  CATUINT32 Reste = CATRound (dNbIterations - (NbSubIterations * iNumberOfMap)); // le reste

  int startIndex = 0; // this->GetStartingIndex();	
  int sgmtIndex  = startIndex;

  // 2. Create all segements for multi-processing
  CATUINT32 numSeg = 1;
  for ( ; numSeg <= iNumberOfMap && SUCCEEDED(hr) ; numSeg++)
  {
    CATUINT32 curNbSubIter = NbSubIterations;
    if (numSeg <= Reste)
      curNbSubIter ++; // Spreading

    // 2.b) Partitionnement des inputs du user 
    // ----------------------------------------------		
    std::vector <T*> curSubSegment;
    CATUINT32  iter  = startIndex;
    CATUINT32  counter = 0;
    while ( counter < curNbSubIter )
    // for ( ; iter < (curNbSubIter + startIndex) ; iter ++, sgmtIndex++)
    {
       T * pCurData = _UCollection[sgmtIndex];
       curSubSegment.push_back(pCurData);

      counter ++;
      sgmtIndex ++;
    }

    // PRobleme ici : comment créer instance ici
    // CATMapOperation * pCurMap = new CATMapOperation (Config, Factory, curSubSegment); /// impossible - classe abtraite
    CATMapOperation * pCurMap = this->CreateAMap(curSubSegment); // methode implementé par le user
    if (pCurMap)
    {
      pCurMap -> SetMasterId (MasterId);
      oSplitMapList.Append(pCurMap);
    }
    else
      hr = E_FAIL;
    // hr = ioRunner.Append(numSeg, pCurSegment) ;
  }
  
  return hr;
}

//template <typename T>
//class CATMapOperation<T*> : public CATMultiProcOperation {} ;
template <typename T>
INLINE CATULONG32 CATMapOperation<T>::GetMasterId() const { 
  return _MasterId; }

















// ------------------------------------------------------------------------------------------------
// Abstract Class CATMapOperation
// ------------------------------------------------------------------------------------------------
// This class allows you to split up any "loop" operation into several processes. 

// Beware of the followings : 
// COLLECTION must implement an operator[] and a copy constructor. 
// By default, the first considered index is 1. But, you can change this value by 
// overloading virtual GetStartingIndex();

//template <class COLLECTION, typename T>
//class CATMapOperation : public CATMultiProcOperation
//{
//
//public :
//  /* Default constructor */
//  CATMapOperation();
//  /* Construtor */
//  CATMapOperation(CATSoftwareConfiguration *iConfig, CATGeoFactory *iFactory, const COLLECTION & iToSegment, CATUINT32 iNbElements);  
//  /* Destrutor */
//  virtual ~CATMapOperation(); 
//
//
//  /**
//  * Segment evenly your code into several operations that will be append to the Runner.
//  * It calls CreateASegment() to create a new instance of your operation. 
//  * @param iNumberOfSegments
//  *   The number of partition you want to append to the Runner. 
//  * @param ioRunner
//  *   A reference to the Runner. 
//  */
//  HRESULT Segment(CATMultiProcRunner &ioRunner, CATUINT32 iNumberOfSegments) const;
//
//  /**
//  * Create an instance with a partition of your input Collection. 
//  * This method will be called by Segment() above. 
//  * @param iSubSegment
//  *   A reference to a partitionned segment that have been computed by Segment().
//  * @return 
//  *   A pointer to a new segmented operation that will be given to the Runner. 
//  */
//  virtual CATMapOperation * CreateASegment(const COLLECTION & iSubSegment, CATUINT32 iNbElements) const = 0;
//
//  /**
//  * Needed for filling the collection with a new element.  
//  */
//  virtual void AddElementTo(COLLECTION &ioCollection, T * ipElement) const = 0;
//
//  /**
//  * Can be overloaded. 
//  * Returns the first index which start iteration on your collection. 
//  */
//  INLINE virtual CATUINT32 GetStartingIndex() const { return 1; }
//
//  /**
//  * Can be overloaded. 
//  * Returns an element of your collection regarding the given index.
//  */
//  INLINE virtual T * GetElement(const CATUINT32 iIndex) const { return _USERCollection[iIndex]; }
//
//  
// /**
// * -- En TEST -- Do not USE
// *
// * Bind a filling function instead of append.
// * Allow you to set a function that will be called for adding element into your collection.
// * Not yet implemented.
// */ 
// HRESULT BindFillingFunction(std::function <int (COLLECTION &, T *)> iAppendFunct);
//
//private :
//
///* Internal Data */
//  COLLECTION  _USERCollection;
//  CATUINT32   _NbElements;
//  
//  std::function <int (COLLECTION &, T *)>  _FAppendFunct;
//
//};
//
//// ==================================================================================== //
//// Implement of CATMapOperation en test
//// ==================================================================================== //
//
//template <class COLLECTION, typename T>
//CATMapOperation<COLLECTION, T>::CATMapOperation() :
//CATMultiProcOperation(),
//_NbElements(0),
//_FAppendFunct(NULL)
//{
//}
//
//// -----------------------------------------------------------------------------------
//// Consttuctor 1
//// -----------------------------------------------------------------------------------
//template <class COLLECTION, typename T>
//CATMapOperation<COLLECTION, T>::CATMapOperation(CATSoftwareConfiguration *iConfig, CATGeoFactory *iFactory, const COLLECTION & iToSegment, CATUINT32 iNbIter) :
//CATMultiProcOperation(iConfig, iFactory),
//_NbElements(iNbIter),
//_USERCollection(iToSegment),
//_FAppendFunct(NULL)
//{
//}
//
//// -----------------------------------------------------------------------------------
//// Destructor 
//// -----------------------------------------------------------------------------------
//template <class COLLECTION, typename T>
//CATMapOperation<COLLECTION, T>::~CATMapOperation()
//{
//  _NbElements = 0;
//  _FAppendFunct = NULL;
//}
//
//// -----------------------------------------------------------------------------------
//// Segment
//// -----------------------------------------------------------------------------------
//template <class COLLECTION, typename T>
//HRESULT CATMapOperation<COLLECTION, T>::Segment(CATMultiProcRunner &ioRunner, CATUINT32 iNumberOfSegments) const
//{
//  HRESULT hr = S_OK;
//
//  if (_NbElements < iNumberOfSegments)
//    return E_FAIL;
//
//  // need copy constructor
//  // 1.a Compute number sub operation 		
//  // CATUINT32 NbSubIteration  ~= ( _NbElements / iNumberOfSegments);
//  CATUINT32 NbSubIterations  = 0;
//
//  double dNbIterations = (double ) _NbElements;
//  double dNbSegments   = (double ) iNumberOfSegments;
//  NbSubIterations      = CATFloor(dNbIterations / dNbSegments); // planché
//
//
//  // Reste = CATRound (NbOperations - (dNbOperationPerProc * dNbProcess));
//  CATUINT32 Reste = CATRound (dNbIterations - (NbSubIterations * iNumberOfSegments)); // le reste
//
//  int startIndex = this->GetStartingIndex();	
//  int sgmtIndex  = startIndex;
//
//  // 2. Create all segements for multi-processing
//  CATUINT32 numSeg = 1;
//  for ( ; numSeg <= iNumberOfSegments && SUCCEEDED(hr) ; numSeg++)
//  {
//    CATUINT32 curNbSubIter = NbSubIterations;
//    if (numSeg <= Reste)
//      curNbSubIter ++; // Spreading
//
//    // 2.b) Partitionnement des inputs du user 
//    // ----------------------------------------------		
//    COLLECTION curSubSegment;
//    CATUINT32  iter  = startIndex;
//    CATUINT32  counter = 0;
//    while ( counter < curNbSubIter )
//    // for ( ; iter < (curNbSubIter + startIndex) ; iter ++, sgmtIndex++)
//    {
//      // T * pCurData = _USERCollection[sgmtIndex];
//      T * pCurData = this->GetElement(sgmtIndex);
//      this->AddElementTo(/*io*/curSubSegment, pCurData); // On appelle la function implementée par l'utilisateur pour peupler la collection.
//
//      counter ++;
//      sgmtIndex ++;
//    }
//
//    // PRobleme ici : comment créer instance ici
//    // CATMPSegmentOperation * pCurSegment = new CATMPSegmentOperation (Config, Factor, NbSubIteration); /// impossible - classe abtraite
//    CATMapOperation * pCurSegment = this->CreateASegment(curSubSegment, curNbSubIter); // methode implementé par le user
//
//    hr = ioRunner.Append(numSeg, pCurSegment) ;
//  }
//  
//
//  return hr;
//}
//
//// -----------------------------------------------------------------------------------
//// BindFunctionAppend
//// -----------------------------------------------------------------------------------
//template <class COLLECTION, typename T>
//HRESULT CATMapOperation<COLLECTION, T>::BindFillingFunction(std::function <int (COLLECTION &, T *)> iAppendFunct)
//{
//  HRESULT hr = E_FAIL;
//  if (iAppendFunct)
//  {
//    _FAppendFunct = iAppendFunct;
//    hr = S_OK;
//  }
//
//  return hr;
//}


#endif
