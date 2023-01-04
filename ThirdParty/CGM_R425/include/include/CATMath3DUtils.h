#ifndef CATMATH3DUTILS_H
#define CATMATH3DUTILS_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 1998
//
//=============================================================================
//
// Utilities for computing scalar product, cross product, norm ...
// for double of three variables
//
// May 2005  cwm :  ajout de nouvelles methodes
// 
//=============================================================================
// INLINE Functions : all
//=============================================================================
//=============================================================================

#include "CATTolerance.h"
#include <math.h>
#include "CATMathLimits.h"
#include "CATMathInline.h"
#include "CATMathFP.h"
#include "CATMathBox.h"


//=============================================================================
// INTERFACES OF the FUNCTIONS
//=============================================================================

INLINE double CATDotProd(double id1[3], double id2[3]);
INLINE double CATSquareNorm(double id[3]);
INLINE double CATNorm(double id[3]);
INLINE void CATCrossProd(double id1[3], double id2[3], double *od);
INLINE void CATMult(double *iod,double a);
INLINE void CATMult(double id[3], double a, double *od);
INLINE void CATAddMult(double id1[3], double id2[3], double a, double *od);

// od = id1/norm(id1)
INLINE double CATNormalize(double *iod);

// od = id1 - id2
INLINE void CATDiff(double id1[3], double id2[3], double *od);

// od = 0.5*(id1+id2)
INLINE void CATAverage(double id1[3], double id2[3], double *od);

// od: projete de id1 sur le plan orthogonal a id2
INLINE void CATProj(double iV[3], double iN[3], double *oV);

// oV: projete de iV sur le plan orthogonal a iN
// odV: derivee du projete de oV
INLINE void CATProjAndDeriv(double iV[3], double iN[3], double *oV,
                            double idV[3], double idN[3], double *odV);

//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
INLINE double CATDotProd(double id1[3], double id2[3])
{
  return id1[0]*id2[0]+id1[1]*id2[1]+id1[2]*id2[2];
}


INLINE double CATSquareNorm(double id[3])
{
  return id[0]*id[0]+id[1]*id[1]+id[2]*id[2];
}

INLINE double CATNorm(double id[3])
{
  return sqrt(id[0]*id[0]+id[1]*id[1]+id[2]*id[2]);
}

INLINE void CATCrossProd(double id1[3], double id2[3], double *od)
{
  od[0]=id1[1]*id2[2]-id1[2]*id2[1];
  od[1]=id1[2]*id2[0]-id1[0]*id2[2];
  od[2]=id1[0]*id2[1]-id1[1]*id2[0];
}

INLINE void CATMult(double *iod,double a)
{
  for(int i=2;i>=0;i--) iod[i]*=a;
}

INLINE void CATMult(double id[3], double a, double *od)
{
  for(int i=2;i>=0;i--) od[i]=a*id[i];
}

INLINE void CATAddMult(double id1[3], double id2[3], double a, double *od)
{
  for(int i=2;i>=0;i--) od[i]=id1[i]+a*id2[i];
}

INLINE double CATNormalize(double *iod)
{
  double Norm = CATNorm(iod);
  if (Norm > CATGetDefaultTolerance().EpsgForRelativeTest())
    CATMult(iod, 1./Norm);
  return Norm;
}

INLINE void CATDiff(double id1[3], double id2[3], double *od)
{
  for (int i=0; i<3; i++)
    od[i] = id1[i] - id2[i];
}

INLINE void CATAverage(double id1[3], double id2[3], double *od)
{
  for (int i=0; i<3; i++)
    od[i] = 0.5*(id1[i]+id2[i]);
}

INLINE void CATProj(double iV[3], double iN[3], double *oV)
{
  double NormalizedN[3];
  for (int i=0; i<3; i++)
    NormalizedN[i] = iN[i];

  CATNormalize(NormalizedN);
  CATAddMult(iV, NormalizedN, -CATDotProd(iV, NormalizedN), oV); 
}

INLINE void CATProjAndDeriv(double iV[3], double iN[3], double *oV,
                            double idV[3], double idN[3], double *odV)
{
  // Projecte
  double NormalizedN[3] = { iN[0], iN[1], iN[2] };

  double Norm = CATNormalize(NormalizedN);
  double invNorm = 1.;
  if (Norm > CATGetDefaultTolerance().EpsgForRelativeTest())
    invNorm = 1./Norm;
  CATAddMult(iV, NormalizedN, -CATDotProd(iV, NormalizedN), oV); 

  // Derivee du projete
  double dNbis[3], dNormalizedN[3];
  CATMult(idN,invNorm, dNbis);
  CATAddMult(dNbis, NormalizedN, -CATDotProd(NormalizedN, dNbis), dNormalizedN);
  
  double coeff1 = CATDotProd(idV,NormalizedN) + CATDotProd(iV, dNormalizedN);
  double coeff2 = CATDotProd(iV,NormalizedN);
  
  for (int i=0; i<3; i++)
    odV[i] = idV[i] - coeff1*NormalizedN[i] - coeff2*dNormalizedN[i]; 
}

//INLINE void MakeAsFloat(CATMathBox& iBox)
//{
//  // Read datas
//  double dcoords[6];
//  iBox.GetExtremities(dcoords[0],dcoords[1],dcoords[2],dcoords[3],dcoords[4],dcoords[5]);
//  // Convert to float
//  float  fcoords[6] = { float(dcoords[0]), float(dcoords[1]), float(dcoords[2]),
//                        float(dcoords[3]), float(dcoords[4]), float(dcoords[5]) }; 
//  // Reconvert to double
//  iBox.SetExtremities(double(fcoords[0]),double(fcoords[1]),double(fcoords[2]),
//                      double(fcoords[3]),double(fcoords[4]),double(fcoords[5]));
//}
INLINE HRESULT MakeAsFloat(CATMathBox& iBox)
{
	// Read datas
	double dcoords[6];
	HRESULT IsOK = iBox.GetLimits(dcoords[0],dcoords[1],dcoords[2],dcoords[3],dcoords[4],dcoords[5]);
	if(IsOK==E_FAIL)
		return IsOK;
	// Convert to float
	float  fcoords[6] = { float(dcoords[0]), float(dcoords[1]), float(dcoords[2]),
		float(dcoords[3]), float(dcoords[4]), float(dcoords[5]) }; 
	// Reconvert to double
	iBox.SetExtremities(double(fcoords[0]),double(fcoords[1]),double(fcoords[2]),
		double(fcoords[3]),double(fcoords[4]),double(fcoords[5]));
	return IsOK;
}
#endif

