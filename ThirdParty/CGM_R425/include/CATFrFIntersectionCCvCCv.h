// COPYRIGHT DASSAULT SYSTEMES 1998 
//===================================================================
//
// CATFrFIntersectionCCvCCv :
// Interface class of intersection between 2 CCvs operator
//
//===================================================================
// Usage notes:
// sample of use :
// to provide
//
//===================================================================
// November 1998      Creation                 Paul-Alexandre LOURME
//===================================================================
#ifndef CATFrFIntersectionCCvCCv_H
#define CATFrFIntersectionCCvCCv_H
//
#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"
#include "CATCGMVirtual.h"

//
class CATFrFCompositeCurve;
class CATFrFCCvLimits;
class CATFrFCCvParam;

//-------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATFrFIntersectionCCvCCv : public CATCGMVirtual
{
  public :
    // Destructor
    //-------------
    virtual ~CATFrFIntersectionCCvCCv();
    // Run
    //------
    virtual void Run() = 0;
    // To change the tolerance of the intersection
    //----------------------------------------------
    virtual void SetTolerance(double iNewTolerance) = 0;
    // To get the number of point solutions
    //---------------------------------------
    virtual CATLONG32 GetNumberOfPoints() const = 0;
    // To get the point solutions 
    //-----------------------------
    // --- !!! New and Delete :
    //     Two CATFrFCCvParam * are allocated during the run() method,
    //     and one is returned in oCCvParams for each call to this method - 
    //     depending on iCCvIndex. When one of this CATFrFCCvParam * is given
    //     to the user, it is not deleted by the destructor : THE USER HAS TO
    //     DO A delete [] ON IT. 
    virtual void GetCCvParams(CATFrFCCvParam *& oCCvParams,CATLONG32 iCCvIndex)  = 0;

    // Not supported yet :
    
    // To get the number of CCv solutions
    //-------------------------------------
    virtual CATLONG32 GetNumberOfCCv() const = 0;
    // To Get the ccv solutions
    //---------------------------
    // --- !!! New and Delete :
    //     Two CATFrFCCvParam * are allocated during the run() method,
    //     and one is returned in oCCvParams for each call to this method - 
    //     depending on iCCvIndex. When one of this CATFrFCCvParam * is given
    //     to the user, it is not deleted by the destructor : THE USER HAS TO
    //     DO A DELETE [] ON IT. 
    virtual void GetCCvLimits(CATFrFCCvLimits *& oCCvLimits,CATLONG32 iCCvIndex)  = 0;
};
#endif
