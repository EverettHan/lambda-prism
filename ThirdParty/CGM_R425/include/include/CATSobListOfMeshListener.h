//====================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//====================================================================
//
// CATSobListOfMeshListener.h
//
//====================================================================
//
// Usage notes: Liste de pointeurs d'objets CATSobMeshListener.
//
//====================================================================
// December,    2009 : RAQ : Creation
//====================================================================
#ifndef CATSobListOfMeshListener_H
#define CATSobListOfMeshListener_H

//Pour l'export
#include "CATSobObjects.h"

//Les listes
#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"

class CATSobMeshListener;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATSobObjects

CATLISTPP_DECLARE_TNS(CATSobMeshListener, SobMeshListener, 5)

typedef CATListPtrSobMeshListener CATSobListOfMeshListener;

#endif

