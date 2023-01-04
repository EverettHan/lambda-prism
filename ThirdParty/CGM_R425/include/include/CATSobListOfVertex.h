//====================================================================
// Copyright Dassault Systemes Provence 2003, all rights reserved 
//====================================================================
//
// CATSobListOfVertex.h
//
//====================================================================
//
// Usage notes:
//
//====================================================================
// January,   2004 : RAQ : Changement d'architecture des subdivisions
// Marsh,     2003 : JCV : Creation CATSobListOfVertex.h
//====================================================================
#ifndef CATSobListOfVertex_h
#define CATSobListOfVertex_h

#include "CATSobObjects.h"

#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"

class CATSobVertex;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATSobObjects

CATLISTPP_DECLARE_TS( CATSobVertex, 10 )

#endif

