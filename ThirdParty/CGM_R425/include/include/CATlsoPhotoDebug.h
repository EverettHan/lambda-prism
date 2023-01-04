/* -*-C++-*- */

#ifndef CATlsoPhotoDebug_H
#define CATlsoPhotoDebug_H
/*  
=============================================================================

RESPONSABLE  : V Bouvier

DESCRIPTION  : class de NewTopo permettant la génération de photos
               
=============================================================================
*/

#include "CATCGMVirtual.h"
#include "CATCGMNewArray.h"
#include "PersistentCell.h"

//class CATlsoPhotoDebug;
class CATGeoFactory;
class CATString;

//--------------------------------------------------------------------------
// @nocgmitf
class ExportedByPersistentCell CATlsoPhotoDebug : public CATCGMVirtual
{

public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual ~CATlsoPhotoDebug() {};

  //methods virtuelles pure implementees dans CATlsoTstPhotoDebug
  virtual int BodySnapshot(int iTailleDesiree, int iMode, float iPourcentCadre)=0;
	virtual int WireSnapshot(int iTailleDesiree, int iMode, float iPourcentCadre)=0;

  virtual void SaveAs(CATString & filename,CATString & format)=0;
  
};

ExportedByPersistentCell CATlsoPhotoDebug * CATCreatelsoPhotoDebug(CATGeoFactory * iFactory);

typedef CATlsoPhotoDebug*  (*CATlsoPhotoDebugBridgeCreator) (CATGeoFactory * iFactory);

#endif
