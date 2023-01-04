/* -*-C++-*- */

#ifndef CATlsoDebugGraph_H
#define CATlsoDebugGraph_H
/*  
=============================================================================

RESPONSABLE  : V Bouvier

DESCRIPTION  : class de NewTopo permettant la génération de graphes
               
=============================================================================
*/

#include "CATCGMVirtual.h"
#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATUnicodeString.h"

//class CATlsoPhotoDebug;
class CATGeoFactory;
class CATString;
class CATCGMOutput;
class CATBody;


enum CATlsoDebugGraphColor
{
  CATlsoDebugGraphColor_Orange = 0,
  CATlsoDebugGraphColor_Yellow,
  CATlsoDebugGraphColor_Red,
  CATlsoDebugGraphColor_Green,
  CATlsoDebugGraphColor_Mauve,
  CATlsoDebugGraphColor_Grey
};

//--------------------------------------------------------------------------
// @nocgmitf
class ExportedByPersistentCell CATlsoDebugGraph
{

public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATlsoDebugGraph();

  virtual ~CATlsoDebugGraph();

  void AddNode(CATBody * iBody, int iOptionalBranch=-1);

  void AddNodeConfig(CATBody * iBody, CATlsoDebugGraphColor iBannerColor, CATlsoDebugGraphColor iBorderColor, CATUnicodeString iText, CATUnicodeString * iOptionalCGMReplayUrl=NULL, int iOptionalBranch=-1);

  void AddEdge();

  void AddEOL();

  static CATUnicodeString GetStrFromColor(CATlsoDebugGraphColor iColor);

private:

  void InitGraphFile();

private:

  CATCGMOutput * _GraphFile;

  CATUnicodeString _ConfigString;

};

#endif
