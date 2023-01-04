// COPYRIGHT Dassault Systemes 2004
//===================================================================
//
// CATDumpFXYOnSTL.h
// Header definition of CATDumpFXYOnSTL
//
//===================================================================
//
// Usage notes:
//   Debug
//   Dump The Function in a STL File 
//
//===================================================================
//
//  Oct 2004  Creation:  BUD JSX
//  Janvier 2009 Descente dans AdvancedMathematics
//===================================================================
#ifndef CATDumpFXYOnSTL_H
#define CATDumpFXYOnSTL_H

#include "YN000DEV.h"
#include "CATMathInterval.h"

class CATUnicodeString;
class CATMathFunctionRN;
//-----------------------------------------------------------------------
class CATSoftwareConfiguration;


class ExportedByYN000DEV CATDumpFXYOnSTL 

  {
  public:

    CATDumpFXYOnSTL(CATMathInterval Dom[2]);
//      {_IntX = Dom[0]; _IntY= Dom[1];_ScaleXY=1;_ScaleF=1;_debugMountainCoeff=1;};
    
    void GetScale(CATMathFunctionRN *Fct,double *ScaleXYZ);

    void CreateFilePath(const CATUnicodeString *fileName,CATUnicodeString *ofilePath);
    void CreateFilePathForMaple(const CATUnicodeString *fileName, CATUnicodeString *oPath);

    void PrintFunction(const CATUnicodeString *fileName,CATMathFunctionRN *iF);
    void PrintFunctionForMaple(const CATUnicodeString *fileName,int iNbpt, double ** iPointsPosition ,CATMathFunctionRN *Fct, double *ScaleXYZ);
    void PrintFunctionDetail(int NivDBG, const CATUnicodeString * shortfileName,
                             int iNbpt, double * iPointsPosition ,double iZoomPercentage,
                             CATMathFunctionRN *Fct);
    void PrintPath        (int NivDBG,const CATUnicodeString *shortfileName, int iNbpt, double ** iPointsPosition , CATMathFunctionRN *Fct,double *Scalexyz=0);
    void PrintPathForBlend(int NivDBG,const CATUnicodeString *shortfileName, int iNbpt, double ** iPointsPosition); 

  private:
    double Eval2D(double x,double y,CATMathFunctionRN *Fct);
  private:
    CATMathInterval _IntX,_IntY;
    double _ScaleXY,_ScaleF;
    double _debugMountainCoeff;
    static CATLONG32 _IndexSTLFile;
    static CATLONG32 _CATSTLOUTPUT_VAR;
  };

#endif
