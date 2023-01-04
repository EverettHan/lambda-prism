//====================================================================
// Copyright Dassault Systemes Provence 2003, all rights reserved 
//====================================================================
//
// CATSobListOfFace.h
//
//====================================================================
//
// Usage notes:
//
//====================================================================
// January,   2004 : RAQ : Changement d'architecture des subdivisions
// Marsh,     2003 : JCV : Creation CATSobListOfFace.h
//====================================================================
#ifndef CATSobListOfFace_h
#define CATSobListOfFace_h

#include "CATSobObjects.h"

#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"

class CATSobFace;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATSobObjects

CATLISTPP_DECLARE_TS( CATSobFace, 10 )

#endif

