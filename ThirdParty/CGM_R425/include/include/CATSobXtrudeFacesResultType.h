//============================================================================
// Copyright Dassault Systemes Provence 2014, all rights reserved 
//============================================================================
//
// CATSobXtrudeFacesResultType.h pour l'opérateur CATStoExtrudeFacesOperator
//
//============================================================================
//
// Usage notes:
//
//============================================================================
// April,     2014 : RBD : Creation CATSobXtrudeFacesResultType.h
//============================================================================
#ifndef CATSobXtrudeFacesResultType_H
#define CATSobXtrudeFacesResultType_H

//Pour l'export
#include "CATSobObjects.h"


/**
 * Les modes de création du résultat de CATStoExtrudeFacesOperator:
 **/
typedef enum 
{
CATSobXtrudeFacesResUndef,                      // Résultat non défini (Before the run)
CATSobXtrudeFacesResFill,                       // Résultat : Extrusion mode Fill
CATSobXtrudeFacesResJoin,                       // Résultat : Extrusion mode join avec création de faces traces
CATSobXtrudeFacesResMerge,                      // Résultat : Merge de couple de faces quasi-confondue
CATSobXtrudeFacesResXtrusionPure,               // Résultat : Extrusion pure des faces, avec création de faces traces par ensemble connexes
CATSobXtrudeFacesResXtrusionPureUnitaire,       // Résultat : Extrusion pure unitaire avec création de faces traces pour chaque face traitées
CATSobXtrudeFacesResMultiple                    // Résultat multiples : Traitement de plusieurs composantes connexes avec plusieurs types de résultats
} CATSobXtrudeFacesResultType;


/**
 * Gets the string corresponding to a diag
 *
 * @param iTResultType
 * The type of the result 
 *
 * @return
 * The string corresponding to the given diag
 **/

ExportedByCATSobObjects
const char* ToString(const CATSobXtrudeFacesResultType iTResultType);


#endif


