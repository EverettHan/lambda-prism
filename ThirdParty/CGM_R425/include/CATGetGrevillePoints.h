/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//===================================================================
//
// CATGetGrevillePoints
// 
//
//===================================================================
// Usage notes : .
//===================================================================

#ifndef CATGetGrevillePoints_H
#define CATGetGrevillePoints_H
#include "CATGMModelInterfaces.h"


#include "CATMathGridOfPoints.h"
#include "CATNurbsSurface.h"
#include "CATNurbsCurve.h" 
#include "CATPNurbs.h"

class ExportedByCATGMModelInterfaces CATGetGrevillePoints 
{
public :

CATGetGrevillePoints( CATNurbsSurface * iNurbsSur);
                                
 

CATGetGrevillePoints( CATNurbsCurve * iNurbsCrv);


//Pour les PNurbs Grid contient des CATMathPoint (U ,V,0) ou U et V sont les parametres sur la surface                                
CATGetGrevillePoints( CATPNurbs * iNurbsCrv);

virtual ~CATGetGrevillePoints();

HRESULT RunOperator();

HRESULT GetGrid(CATMathGridOfPoints & ioResultGrid);

private :
	int _TypeNurbs;
	CATMathGridOfPoints _Grid;
	CATNurbsSurface *_NurbsSur ;
	CATNurbsCurve   *	_NurbsCrv;
	CATPNurbs *_PNurbs ;
};
#endif
