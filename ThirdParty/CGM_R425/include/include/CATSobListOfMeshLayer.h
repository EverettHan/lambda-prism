//====================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//====================================================================
//
// CATSobListOfMeshLayer.h
//
//====================================================================
//
// Usage notes: Liste de pointeurs d'objets CATSobMeshLayer.
//
//====================================================================
// December,    2009 : RAQ : Creation
//====================================================================
#ifndef CATSobListOfMeshLayer_H
#define CATSobListOfMeshLayer_H

//Pour l'export
#include "CATSobObjects.h"

//Les listes
#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"

class CATSobMeshLayer;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATSobObjects

CATLISTPP_DECLARE_TNS(CATSobMeshLayer, SobMeshLayer, 5)

typedef CATListPtrSobMeshLayer CATSobListOfMeshLayer;

#endif

