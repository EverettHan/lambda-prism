/* -*-c++-*- */
#ifndef CATSetCheckKnotVectorCount_h
#define CATSetCheckKnotVectorCount_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2001
//-----------------------------------------------------------------------------
// 15/10/01 TCX CATSetCheckKnotVectorCount(): Eviter le bloquer le File/Open sur un controle de debordement de _KnotCount
// 23/01/06 PRG Ajout CATMAXKnotsCount()
// 18/01/08 NLD Idem (pb File/Open)sur un probleme de tolerance alors qu'on ne connait pas l'echelle
//              avec CATSetCheckKnotVectorMonotonyWithTolerance()
// 07/09/11 NLD CATMAXKnotsCount() est dorenavant exportee, pour besoin DNR/JLH
//              (pour appel applicatif)
//              ce fichier passe de private en protected
//              (Ajout de nodoc et nocgmitf non necessaire: pas d'interfacage pour ce framework)
// 02/03/18 NLD Creation de CATKnotVectorInternal pour remplacer ces methodes
//              Shunt de CATSetCheckKnotVectorCount() et CATSetCheckKnotVectorMonotonyWithTolerance()
//              dont j'ai eliminé tous les appels
//-----------------------------------------------------------------------------
#include "ExportedByGeometricObjects.h"

#define CATSetCheckKnotVectorCount_ShuntForbidden "tentative NLD020318"

#ifndef CATSetCheckKnotVectorCount_ShuntForbidden
// DO NOT USE see CATKnotVectorInternal. NLD020318
// Internal and very restricted use
ExportedByGeometricObjects int CATSetCheckKnotVectorCount(int newMaxKnotCount);
#endif

// Gives back the maximum number of knots for any CATKnotVector object
extern ExportedByGeometricObjects int CATMAXKnotsCount();

#ifndef CATSetCheckKnotVectorCount_ShuntForbidden
// DO NOT USE see CATKnotVectorInternal. NLD020318
// ecrit/lit l'activation du check de monotonie avec tolerance (sinon tolerance nulle)
// iSet     : 1 ecrit, 0: lit
// ioActive : tolerance active 
ExportedByGeometricObjects void CATSetCheckKnotVectorMonotonyWithTolerance(int iSet, int& ioActive);
#endif

#endif
