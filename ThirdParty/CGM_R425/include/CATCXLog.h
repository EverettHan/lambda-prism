#ifndef CATCXLog_H_
#define CATCXLog_H_

// COPYRIGHT DASSAULT SYSTEMES 1999

//-----------------------------------------------------------
//  Static INTERNAL Functionnalities For Topology LOG debugging
//-----------------------------------------------------------
#include "CXMODEL.h"

#include "CATListOfCATICGMObjects.h"
class CATGeoFactory;

class CATCGMObject;
class CATSubdOccurence;
class CATICGMObject;
class CATICGMContainer;

//--------------------------------------------------------------------
// Execution d'un CheckUp pour deceler les Error/PotDeVin/Warning
//    generation des detections sur la sortie standard avec renvoie du nombre d'occurence de problemes
//--------------------------------------------------------------------
class ExportedByCXMODEL CATCXLog
{
public:
  
  //--------------------------------------------------------------------
  //  CheckUp sur une liste d'objets appartenant a la meme CATGeoFactory
  //--------------------------------------------------------------------
  static int check(CATGeoFactory                 * iFactory, 
                   const CATLISTP(CATICGMObject) & iToCheck,
                   const char                      iName[]);
  
  //--------------------------------------------------------------------
  //  CheckUp specifique ...
  //--------------------------------------------------------------------
  static int check(CATCGMObject     *implementation);
  static int check(CATICGMObject    *itf1);  
  static int check(CATICGMContainer *itf2);
  static int check(CATSubdOccurence *booleanObject);
  
};
#endif

