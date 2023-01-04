#ifndef CATGemEvtAction_H
#define CATGemEvtAction_H
//---------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2002
//---------------------------------------------------
/*
//---------------------------------------------------
Variable d'environnement CATGemEvt permettant DEBUG
     set CATGemEvt=action=event+event
//---------------------------------------------------

Liste des Actions possibles :

                    Dummy
                    Clean
                    CheckClean
                    DeltaMem                    
                    DumpMemory
                    Tessellate
  
Liste des Evenements ou des abonnements sont possibles

                    Create
                    CloseBefore
                    CloseAfter
                    OpenBefore
                    OpenAfter
                    SaveBefore
                    SaveAfter
                    GenericNamed
                    Extrapol
                    Completed
                    All
//---------------------------------------------------
*/ 
//---------------------------------------------------
#include "ExportedByGeometricObjects.h"

//---------------------------------------------------
//  Les Actions Possibles
//---------------------------------------------------
#define CATGemEvtAction_DeltaMem    0x00000001
#define CATGemEvtAction_Clean       0x00000002
#define CATGemEvtAction_Dummy       0x00000004
#define CATGemEvtAction_DumpMemory  0x00000008
#define CATGemEvtAction_CheckClean  0x00000010

#define CATGemEvtAction_Tessellate  0x00000020


//---------------------------------------------------
//  Les Evenements avec leurs actions associees
//---------------------------------------------------
struct CATGemEvtActions
{
  unsigned int      _Factory_Create;
  unsigned int      _Factory_Close_Before;
  unsigned int      _Factory_Close_After;
  unsigned int      _Factory_Open_Before;
  unsigned int      _Factory_Open_After;
  unsigned int      _Factory_Save_Before;
  unsigned int      _Factory_Save_After;

  unsigned int      _TopologyCompletion;
  unsigned int      _Extrapolation;

  unsigned int      _GenericNamed_Linked;
};


//---------------------------------------------------
//  Les Actions Possibles
//---------------------------------------------------
class ExportedByGeometricObjects CATGemEvtAction
{
public :
  
  static  short IsActive(CATGemEvtActions * actions = NULL );

private :

  //---------------------------------------------------
  // Decodage de la variable d'environnement CATGemEvt
  //---------------------------------------------------
  static  short CATGemEvt(const char *pCATGemEvt, CATGemEvtActions & actions);

};

#endif
