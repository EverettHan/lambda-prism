/* -*-c++-*- */
#ifndef CATCGM_WeakAddRef_To_ModelReference_h
#define CATCGM_WeakAddRef_To_ModelReference_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2000
//-----------------------------------------------------------------------------
// Test de conversion d'un pointeur protege Ultra-faiblement par AddRef
//   en un pointeur d'une reference modele encore vivante dans la Factory
// Il s'agit uniquement d'un Filtrage 
//-----------------------------------------------------------------------------
#include "ExportedByCATCGMFusion.h"

ExportedByCATCGMFusion CATCGMObject *  \
   CATCGM_WeakAddRef_To_ModelReference( CATCGMObject *pointer );


#endif
