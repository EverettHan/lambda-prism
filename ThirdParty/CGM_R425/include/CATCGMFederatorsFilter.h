/* -*-c++-*- */
#ifndef CATCGMFederatorsFilter_H
#define CATCGMFederatorsFilter_H
// COPYRIGHT DASSAULT SYSTEMES  2002
//============================================================================
//Mode de gestion de  CATCGMArrayOfOrientedObjects
//============================================================================
typedef unsigned int CATCGMFederatorsFilter;

//-------------------------------------------------------------------------
// SpecifiedByDocument = defaut depends du type de document 
//     CATPart  : Les elements flagges CATIGenericNamed de type "linked"
//     NCGM     : UseCount null (en l'absence de Specs sur les Federaros)
//-------------------------------------------------------------------------
#define CATCGMFederatorsFilter_SpecifiedByDocument          0x00000000

//-------------------------------------------------------------------------
// OnlySpecifiedShow   depends du type de document 
//     CATPart  : a partir de la V5R10 (requete asynchrone aupres de MechanicalModeler)
//     NCGM     : Lecture synchrone du bit Show/NoShow
//-------------------------------------------------------------------------
#define CATCGMFederatorsFilter_OnlySpecifiedShow            0x00000001

//-------------------------------------------------------------------------
// ForceOnlyNullUseCount pour comportement homogene (mais non desire)
//     entre document CATPart et NCGM
// Dans ce cas on obtiens de la modelisation temporaire oubliee
//-------------------------------------------------------------------------
#define CATCGMFederatorsFilter_ForceOnlyNullUseCount        0x00000002

//-------------------------------------------------------------------------
// Do not return DRep Geometry Objects linked to any CATCX Object by attribut
//-------------------------------------------------------------------------
#define CATCGMFederatorsFilter_NoDrepGeometry               0x00000010

//-------------------------------------------------------------------------
// Do return Only_DRep Geometry Objects without any other CATICGMObjects 
//-------------------------------------------------------------------------
#define CATCGMFederatorsFilter_OnlyDrepGeometry             0x00000020

#endif
