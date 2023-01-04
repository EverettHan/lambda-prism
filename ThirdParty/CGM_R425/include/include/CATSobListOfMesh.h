//====================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//====================================================================
//
// CATSobListOfMesh.h
//
//====================================================================
//
// Usage notes: Liste de base mesh.
//
//====================================================================
// November,    2009 : RAQ : Creation
//====================================================================
#ifndef CATSobListOfMesh_H
#define CATSobListOfMesh_H

//Pour l'export
#include "CATSobObjects.h"

//Les listes
#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"

class CATSobMesh;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATSobObjects

CATLISTPP_DECLARE_TNS(CATSobMesh, SobMesh, 10)

typedef CATListPtrSobMesh CATSobListOfMesh;


/**
 * Removes all meshes in a list.
 **/
ExportedByCATSobObjects
void RemoveMeshes(CATSobListOfMesh& iMeshesList);


#endif

