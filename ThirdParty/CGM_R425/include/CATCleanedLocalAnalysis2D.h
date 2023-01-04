// COPYRIGHT DASSAULT SYSTEMES 2022
//=============================================================================
//


//=============================================================================
//   /03/22 SMT1 Creation
//   Dedicated class for Meshing 
//   The Input Nurbs may have very short, but highly curved arcs at the four surface boundaries.
//   The aim of this operator is to 'clean' these boundaries and to wrap calls to Local2DAnalysis on the cleaned geometry.
//=============================================================================

#ifndef CATCleanedLocalAnalysis2D_H
#define CATCleanedLocalAnalysis2D_H


#include "CATGeoOperator.h"
#include "CATMathFunctionXY.h"
#include "Y30UIUTI.h"
#include "CATFrFNurbsBipar.h"
#include "CATMathInterval2D.h"
#include "CATCGMStream.h"

class CATLocalAnalysis2D;
class CATSoftwareConfiguration;
class CATCleanedLocalAnalysis2D;


class Local2DAnalysisFunc : public CATMathFunctionXY
{
public:
    enum Type{Max,Min,Dir} _Type;

    Local2DAnalysisFunc(CATSoftwareConfiguration* iConfig ,
                        CATSurface              * iSupport);

    ~Local2DAnalysisFunc();

    virtual CATMathClassId IsA() const {return "Local2DAnalysisFunc";}
    virtual CATMathFunctionXY * Duplicate() const {return NULL;}

    virtual double Eval           (const double                   & iX         ,
        const double                   & iY   ) const;

    void SetType(Local2DAnalysisFunc::Type iType) {_Type = iType;}
    void SetDir(double iX, double iY) {_Dir[0] = iX;_Dir[1] = iY;}
    void MinMaxCurvature(const CATMathInterval2D &iDomain, double &ioMax, double&ioMin, const CATTolerance& Tol, CATBoolean iDir = FALSE);


protected:

    CATLocalAnalysis2D       * _Analysis;
    CATSoftwareConfiguration * _Config;
    CATSurface               * _Support;
    double                     _Dir[2];

};

ExportedByY30UIUTI CATCleanedLocalAnalysis2D *CreateCleanedLocalAnalysis2D(CATGeoFactory * Factory,      
                                                                           CATSoftwareConfiguration * iConfig,
                                                                           const CATSurface *  iSurface,
                                                                           double iTol = 0.0); 

extern "C" ExportedByY30UIUTI CATGeoOperator * CATLoadCATCleanedLocalAnalysis2D(      CATCGMStream & Str,
                                                                                const short          LevelOfRuntime, 
                                                                                const short          VersionOfStream);

class  CATCleanedLocalAnalysis2D : public CATGeoOperator
{
public :
   
    ~CATCleanedLocalAnalysis2D ();

    virtual void GetMinMaxCurvaturesAndDirections
        (const CATSurParam &iParam, double & ioCmin, double & ioCmax, CATMathVector2D & ioDirMin2D, CATMathVector2D & ioDirMax2D,
        CATMathVector & ioDirMin3D, CATMathVector & ioDirMax3D);

private:

    CATCleanedLocalAnalysis2D (CATGeoFactory            * iFactory,
        CATSoftwareConfiguration * iConfig,
        const CATSurface *  iSurface,
         double iTol);

    virtual int RunOperator();

    void ComputeCleanedSurface();

    CATBoolean Bipar_GetArcDomain(const CATFrFNurbsBipar &iBipar, 
        CATLONG32 iSide, 
        CATLONG32 iStart, 
        CATLONG32 iEnd, 
        CATMathInterval2D  &ioDomain,
        double &ioWidth) const;

    void Bipar_RemoveKnot(CATLONG32 iSide, CATLONG32 iStart, CATLONG32 iEnd, CATFrFNurbsBipar &ioBipar) const;

    const CATSurface               * _InputSurface;
          CATSurface               * _CleanedSurface;
          CATSoftwareConfiguration * _Config;
    const CATTolerance             & _TolObject;
          double                     _Tol;
          CATLocalAnalysis2D       * _Analysis;
          CATLONG32                  _FinalDepth[4];

public:
    static CATString _OperatorId;
    const CATString * GetOperatorId(); 
    CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
    virtual void WriteInput(CATCGMStream  & os);
    virtual void WriteOutput(CATCGMStream & os);
    virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
    virtual void Dump( CATCGMOutput& os ) ;
    virtual void DumpOutput(CATCGMOutput & os);
    virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);

   friend ExportedByY30UIUTI CATCleanedLocalAnalysis2D *CreateCleanedLocalAnalysis2D(CATGeoFactory * Factory,      
                                                                           CATSoftwareConfiguration * iConfig,
                                                                           const CATSurface *  iSurface,
                                                                           double iTol); 

   friend ExportedByY30UIUTI CATGeoOperator * CATLoadCATCleanedLocalAnalysis2D(      CATCGMStream & Str,
                                                                                const short          LevelOfRuntime, 
                                                                                const short          VersionOfStream);
};




#endif 
