#ifndef CATCellGraph_h
#define CATCellGraph_h

#include "CATDataType.h"
#include <CATCellNode.h>
#include "ExportedByGeometricObjects.h"

class CATCGMJournal;
class CATGeometry;
class CATHTabCATCellNode;

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class fstream;
#endif

#define CATCGMMAXLINELENGTH 1024

class ExportedByGeometricObjects CATCellGraph
{
public:

  static void SplitWords(char iString[CATCGMMAXLINELENGTH], CATListOfCATString & oWords);

  CATCellGraph(const CATCGMJournal * iJournal);
  CATCellGraph(fstream * iStream);
  ~CATCellGraph();

  int Size();
  CATCellNode * Get(int iPos);

  CATCellNode * Locate(CATLONG32 iTag);

private:

  CATCellNode * CreateNode(CATGeometry * iGeometry);
  CATCellNode * CreateNode(CATLONG32 iTag, CATCellNode::CellType iType);

  CATHTabCATCellNode * _Nodes;
  fstream * _str;
};

#endif
