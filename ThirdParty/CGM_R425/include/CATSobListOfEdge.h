//====================================================================
// Copyright Dassault Systemes Provence 2003, all rights reserved 
//====================================================================
//
// CATSobListOfEdge.h
//
//====================================================================
//
// Usage notes:
//
//====================================================================
// January,   2004 : RAQ : Changement d'architecture des subdivisions
// Marsh,     2003 : JCV : Creation CATSobListOfEdge.h
//====================================================================
#ifndef CATSobListOfEdge_h
#define CATSobListOfEdge_h

#include "CATSobObjects.h"

#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"

class CATSobEdge;
//#include "CATSobEdge.h"

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATSobObjects

CATLISTPP_DECLARE_TS( CATSobEdge, 10 )

#endif

