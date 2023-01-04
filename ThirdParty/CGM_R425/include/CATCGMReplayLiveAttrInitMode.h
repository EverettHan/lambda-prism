/* -*-c++-*- */
#ifndef CATCGMReplayLiveAttrInitMode_h
#define CATCGMReplayLiveAttrInitMode_h

// COPYRIGHT DASSAULT SYSTEMES 2008

// --------------------------------------------------------------------------
// Mode d'initialisation des attributs Live du Body résultat après le Run()
//   CATCGMReplayLiveAttrInit_None   : pas d'initialisation
//   CATCGMReplayLiveAttrInit_Auto   : initialisation des attributs Live si un Body d'entrée est Live
//   CATCGMReplayLiveAttrInit_Always : initialisation systématique des attributs Live
// --------------------------------------------------------------------------
enum CATCGMReplayLiveAttrInitMode 
{ 
  CATCGMReplayLiveAttrInit_None   = 0, 
  CATCGMReplayLiveAttrInit_Auto   = 1, 
  CATCGMReplayLiveAttrInit_Always = 2
};

#endif
