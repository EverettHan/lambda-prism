//====================================================================
// Copyright Dassault Systemes Provence 2003, all rights reserved 
//====================================================================
//
// CATSobListOfCell.h
//
//====================================================================
//
// Usage notes:
//
//====================================================================
// January,   2004 : RAQ : Changement d'architecture des subdivisions
// Marsh,     2003 : JCV : Creation CATSobListOfCell.h
//====================================================================
#ifndef CATSobListOfCell_h
#define CATSobListOfCell_h

#include "CATSobObjects.h"

#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"

class CATSobCell;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATSobObjects

CATLISTPP_DECLARE_TS( CATSobCell, 10 )

#endif

