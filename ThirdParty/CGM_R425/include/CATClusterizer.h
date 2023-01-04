#ifndef CATClusterizer_h
#define CATClusterizer_h

/**
* Collection to build clusters of objects.
* Clusters are built with multiple calls to AddCouple.

  CATClusterizer Toto(20);
  Toto.AddCouple((void *)0x01, (void *)0x02);
  Toto.AddCouple((void *)0x01, (void *)0x03);
  Toto.AddCouple((void *)0x04, (void *)0x05);
  Toto.AddCouple((void *)0x04, (void *)0x02);
  Toto.AddCouple((void *)0x07, (void *)0x08);

  CATClusterizerBegin(Toto, CurrentCluster)
  {
    CATCGMHashTableBegin (*CurrentCluster, CurrElem, void *)
    {
      int u =9;
    } CATCGMHashTableEnd;
  } CATClusterizerEnd;

*/

#include "CATCGMHashTableWithAssoc.h"
#include "CATListPV.h"
#include "CATMathInline.h"
#include "ExportedByCATTopologicalObjects.h"
#include "CATAdaptiveHashTable.h"

class CATAdaptiveHashTable;

class ExportedByCATTopologicalObjects CATClusterizer
{
public:
  CATClusterizer(int iEstimatedSize);
  virtual ~CATClusterizer();

  void AddElement(void * iElem);
  void AddCouple(void * iElem1, void * iElem2);
  INLINE CATAdaptiveHashTable * GetCluster(void * iElem);
  INLINE CATAdaptiveHashTable * GetCluster(int I);

  void RemoveAll();

  INLINE int GetNbClusters();
  INLINE int GetNbElements();

private:

  CATCGMHashTableWithAssoc _ElemToCluster;
  CATAdaptiveHashTable _ClusterList;
};

INLINE CATAdaptiveHashTable * CATClusterizer::GetCluster(void * iElem)
{
  return (CATAdaptiveHashTable *)_ElemToCluster.LocateAssoc(iElem);
}

CATAdaptiveHashTable * CATClusterizer::GetCluster(int I)
{
  return (CATAdaptiveHashTable *)_ClusterList.Get(I);
}

INLINE int CATClusterizer::GetNbClusters()
{
  return _ClusterList.Size();
}

INLINE int CATClusterizer::GetNbElements()
{
  return _ElemToCluster.Size();
}

#define CATClusterizerBegin(CLUSTERIZER, CLUSTER) \
int CLUSTER##I, CLUSTER##N((CLUSTERIZER).GetNbClusters()); \
for (CLUSTER##I = 0; CLUSTER##I < CLUSTER##N; CLUSTER##I++) \
{ \
  CATAdaptiveHashTable * CLUSTER = (CLUSTERIZER).GetCluster(CLUSTER##I); \
  if (CLUSTER) \
  {
   
#define CATClusterizerEnd \
  } \
}




#endif
