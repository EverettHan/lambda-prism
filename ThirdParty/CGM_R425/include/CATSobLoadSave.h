//===========================================================================
// Copyright Dassault Systemes Provence 2004, All Rights Reserved 
//===========================================================================
//
// CATSobLoadSave.h
//
//===========================================================================
//
// Usage notes: Reads a mesh from a SDO file.
//              Writes a mesh to a SDO file.
//
//===========================================================================
// November,  2004 : RAQ : Suppression LoadBaseMeshFromArray
// October,   2004 : RAQ : Ajout LoadBaseMeshFromArray en commentaire
// April,     2004 : RAQ : Création
//===========================================================================
#ifndef CATSobLoadSave_H
#define CATSobLoadSave_H

//Pour l'export
#include "CATSobObjects.h"

//Divers
#include "CATSobDiag.h"
#include "CATSobListOfMesh.h"
#include "CATUnicodeString.h"


class CATSobMesh;


/**
 * Save a mesh to a SDO file
 *
 * @param iMesh
 * The mesh to save
 * @param iSDOFileName
 * The path to the SDO file. If the file exists it is overwritten,
 * else it is created.
 *
 * @return
 * CATSobDiag_OK if no problems occured.
 **/
ExportedByCATSobObjects
CATSobDiag SaveBaseMesh(const CATSobMesh* iMesh, const char* iSDOFileName);

/**
 * Reads a mesh from an existing SDO file
 *
 * @param iMesh
 * The mesh to save
 * @param iSDOFileName
 * The path to the existing SDO file.
 *
 * @return
 * CATSobDiag_OK if no problems occured.
 **/
ExportedByCATSobObjects
CATSobDiag LoadBaseMesh(CATSobMesh*& ioMesh, const char* iSDOFileName);


/**
 * Save a QUAD mesh to a MRM file
 *
 * @param iMesh
 * The mesh to save
 * @param iMRMFileName
 * The path to the MRM file. If the file exists it is overwritten,
 * else it is created.
 *
 * @return
 * CATSobDiag_OK if no problems occured.
 **/
ExportedByCATSobObjects
CATSobDiag SaveBaseMeshToMRM(CATSobMesh* iMesh, const char* iMRMFileName);

/**
 * Reads a mesh from an existing ASCII MRM file
 *
 * @param iMesh
 * The mesh to save
 * @param iMRMFileName
 * The path to the existing MRM file.
 *
 * @return
 * CATSobDiag_OK if no problems occured.
 **/
ExportedByCATSobObjects
CATSobDiag LoadBaseMeshFromMRM(CATSobMesh*& ioMesh, const char* iMRMFileName, const int iMaxLevelToKeep = -1);

/**
 * Saves a set of base meshes in an OBJ file.
 *
 * @param iMeshesToSave
 * The meshes to save.
 * @param iOBJFileName
 * The path to the OBJ file. If the file exists it is overwritten,
 * @param iMeshesToSaveNames
 * A pointer to a list that contains meshes names, if iMeshesToSaveNames is NULL no names are saved.
 *
 * @return
 * CATSobDiag_OK if no problems occured.
 **/
ExportedByCATSobObjects
CATSobDiag SaveBaseMeshesToOBJ(const CATSobListOfMesh& iMeshesToSave, const char* iOBJFileName, const CATListOfCATUnicodeString* iMeshesToSaveNames = 0);

/**
 * Reads a set of meshes from an existing ASCII OBJ file.
 *
 * @param iOBJFileName
 * The path to the obj file.
 * @param ioBaseMeshes
 * The list of read meshes.
 * @param ioBaseMeshesNames
 * A pointer to a list that will contain meshes names if written in the file.
 * If ioBaseMeshesNames is NULL, names are not retrieved.
 * @param iIgnoreMeshesInTopologicalError
 * If FALSE the operator breaks with a failure return code when a topological error is encountered,
 * if TRUE meshes producing these errors are ignored.
 * @param ioNbIgnoreMeshes
 * Optionnal, a pointer to an int that will contain the number of filtered meshes.
 * @param ioIgnoredMeshesNames
 * Optionnal, a pointer to a string list that will contain the filtered meshes names.
 *
 * @return
 * CATSobDiag_OK if no problems occured.
 **/
ExportedByCATSobObjects
CATSobDiag LoadBaseMeshesFromOBJ(const char* iOBJFileName, CATSobListOfMesh& ioBaseMeshes, CATListOfCATUnicodeString* ioBaseMeshesNames = 0,
                                 const CATBoolean iIgnoreMeshesInTopologicalError = FALSE, int* ioNbIgnoreMeshes = 0, CATListOfCATUnicodeString* ioIgnoredMeshesNames = 0);

#endif

