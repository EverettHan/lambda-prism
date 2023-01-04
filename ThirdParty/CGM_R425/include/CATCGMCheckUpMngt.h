/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */

/* -*-c++-*- */
#ifndef CATCGMCheckUpMngt_H_
#define CATCGMCheckUpMngt_H_
//=============================================================================
// Apr. 03 Creation                                                       HCN
//=============================================================================

// Frameworks a reconstruire :
//    GeometricObjects GeometricObjectsCGM NewTopologicalObjects V4CGMInteroperability

// A commenter
// #define CGMCheckUpTraces


#ifdef CGMCheckUpTraces

#include "YP0LOGRP.h"
#include "CATCGMOutput.h"

class ExportedByYP0LOGRP CATCGMCheckUpMngt
{
public :
  CATCGMCheckUpMngt();
  ~CATCGMCheckUpMngt();
  static int _NbIdentSpaces;
};




#define CGMCheckUpMngtDumpClassTag( Msg )                                         \
                                                                                  \
CATCGMCheckUpMngt OneMngt;                                                        \
int NumCheck = 0;                                                                 \
                                                                                  \
cgmout << cgmendl;                                                                \
                                                                                  \
for (int NumSpace = 1; NumSpace <= CATCGMCheckUpMngt::_NbIdentSpaces; NumSpace++) \
  cgmout << " ";                                                                  \
                                                                                  \
cgmout << Msg << "::CheckUp(...)";                                                \
cgmout << " on " << this->IsA() << " " << this->GetPersistentTag() << cgmendl;    \
                                                                                  \
for (NumSpace = 1; NumSpace <= CATCGMCheckUpMngt::_NbIdentSpaces; NumSpace++)     \
  cgmout << " ";                                                                  \
                                                                                  \
for (NumSpace = 1; NumSpace <= (strlen(Msg) + 14) ; NumSpace++)                   \
  cgmout << "-";                                                                  \
                                                                                  \
cgmout << cgmendl;




#define CGMCheckUpMngtDumpClass( Msg )                                            \
                                                                                  \
CATCGMCheckUpMngt OneMngt;                                                        \
int NumCheck = 0;                                                                 \
                                                                                  \
cgmout << cgmendl;                                                                \
                                                                                  \
for (int NumSpace = 1; NumSpace <= CATCGMCheckUpMngt::_NbIdentSpaces; NumSpace++) \
  cgmout << " ";                                                                  \
                                                                                  \
cgmout << Msg << "::CheckUp(...)" << cgmendl;                                     \
                                                                                  \
for (NumSpace = 1; NumSpace <= CATCGMCheckUpMngt::_NbIdentSpaces; NumSpace++)     \
  cgmout << " ";                                                                  \
                                                                                  \
for (NumSpace = 1; NumSpace <= (strlen(Msg) + 14) ; NumSpace++)                   \
  cgmout << "-";                                                                  \
                                                                                  \
cgmout << cgmendl;




#define CGMCheckUpMngtDumpMethodeTag( Msg )                                       \
                                                                                  \
CATCGMCheckUpMngt OneMngt;                                                        \
int NumCheck = 0;                                                                 \
                                                                                  \
cgmout << cgmendl;                                                                \
                                                                                  \
for (int NumSpace = 1; NumSpace <= CATCGMCheckUpMngt::_NbIdentSpaces; NumSpace++) \
  cgmout << " ";                                                                  \
                                                                                  \
cgmout << Msg << "(...)";                                                         \
cgmout << " on " << this->IsA() << " " << this->GetPersistentTag() << cgmendl;    \
                                                                                  \
for (NumSpace = 1; NumSpace <= CATCGMCheckUpMngt::_NbIdentSpaces; NumSpace++)     \
  cgmout << " ";                                                                  \
                                                                                  \
for (NumSpace = 1; NumSpace <= (strlen(Msg) + 5) ; NumSpace++)                    \
  cgmout << "-";                                                                  \
                                                                                  \
cgmout << cgmendl;




#define CGMCheckUpMngtTraces( Msg )                                               \
                                                                                  \
NumCheck++;                                                                       \
cgmout << cgmendl;                                                                \
                                                                                  \
for (NumSpace = 1; NumSpace <= CATCGMCheckUpMngt::_NbIdentSpaces; NumSpace++)     \
  cgmout << " ";                                                                  \
                                                                                  \
cgmout << NumCheck << ") " << Msg << cgmendl;


#endif // #ifdef CGMCheckUpTraces

#endif
