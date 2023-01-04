// COPYRIGHT DASSAULT SYSTEMES 2012
//===============================================================================================================
//
// CATDeclarativeOriginModeler :
// Name of the OriginModeler for a live recognition.
// The OriginModeler defines some tolerances for the recognizer agents, like filletRecognizer, chamferRecognizer, canonicRecognizer.
//
//===============================================================================================================
// July 09 Creation                                                                         L. Marini
//===============================================================================================================

#ifndef CATDeclarativeOriginModeler_H
#define CATDeclarativeOriginModeler_H 

enum CATDeclarativeOriginModeler {
  CATDeclarativeOriginModeler_CGM = 0,
  CATDeclarativeOriginModeler_Parasolid,
  CATDeclarativeOriginModeler_ACIS,
  CATDeclarativeOriginModeler_StrimStyler
};

#endif
