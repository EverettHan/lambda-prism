/*-*-C++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1998
//==========================================================================
//
// CATFrFNodeIterator :  manage node object
//
//==========================================================================
//
// Usage notes:
//
//==========================================================================
// Oct 98     Creation                       T.Phung (tpg)
//==========================================================================
//
#ifndef CATFrFNodeIterator_H
#define CATFrFNodeIterator_H
//
#include "FrFGeodesic.h"
#include "CATMathDef.h"
#include "CATCGMVirtual.h"

//
class CATFrFNode;
//-----------------------------------------------------------------------------
class ExportedByFrFGeodesic CATFrFNodeIterator : public CATCGMVirtual
{
 public :

 // Constructor
 CATFrFNodeIterator(void * iRoot=0,CATLONG32 iMaxSize=10);

 // Destructor
 virtual ~CATFrFNodeIterator();

 // Get Max Size (number of node levels)
 virtual CATLONG32 GetMaxSize() const;

 // Get Root
 virtual void * GetRoot();

 // Move in the tree
 virtual CATBoolean GoUp(); 
 virtual CATBoolean GoDown(); 
 virtual CATBoolean GoPrevious(); 
 virtual CATBoolean GoNext(); 

 // Get current node
 virtual void * GetCurrentNode();
 
 // Add a child to the current node 
 // the child becomes the current node
 virtual void AddChild(void * iChild);
 virtual void ReplaceData(void * iData);

 // Get Path
 virtual CATLONG32 GetNumberOfPaths();

 virtual void Beginning();
 virtual CATBoolean NextPath();
 virtual void GetPath(void ** iListOfData);
 virtual CATLONG32 GetNumberOfNodesInPath();
 virtual void * GetPath (CATLONG32 iIndexOfNodesInPath);
 virtual CATLONG32 GetNumberOfSubPaths();
 virtual CATLONG32 GetFirstElementOfSubPath(CATLONG32 iIndexOfSubPath);
 

  protected :

 virtual void Update( int force = 0 );
 
 // 
 //------------------- Datas -------------------  
 // 
  protected :

 CATLONG32          _MaxSize;

 CATFrFNode *  _Current;
 CATFrFNode *  _Root;
 CATFrFNode ** _Path;
 CATLONG32          _IndexPath;
 CATLONG32          _NumberOfNodesInPath;

};
#endif

