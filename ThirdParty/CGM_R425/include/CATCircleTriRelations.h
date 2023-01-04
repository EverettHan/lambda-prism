//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// CATCircleTriRelations :
//  Class used to Solve a system of CATMathRelation
//
//=============================================================================
//
// Usage notes:
//
//
//=============================================================================
// 04/03/20 NLD Implementation de GetSoftwareConfiguration()
//              Detabulation
//              Mise au propre
// 20/03/20 Q48 C++ keywords for some virtual functions
//=============================================================================

#ifndef CATCircleTriRelations_H
#define CATCircleTriRelations_H

// ExportedBy
#include "Y30C1XMM.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include <stdlib.h>

#include "CATMathConstant.h"

#include "CATString.h"

#include "CATRelationCircle.h"
#include "CATCreateCircleTriRelations.h"

class CATCircleTriRelationsSol;

class CATMathInterval;
class CATMathIntervalND;
class CATMathPoint2D;
class CATMathRelationSolver;
class CATMathSetOfPointsND;
class CATMathVector2D;

class CATCrvLimits;
class CATCrvParam;
class CATGeoFactory;
class CATPCircle;
class CATPCurve;
class CATSurface;
class CATSurLimits;
class CATSurParam;
class CATSoftwareConfiguration;
class CATBooleanConstraintCircle;

//-------------------------------------------------------------------
class ExportedByY30C1XMM CATCircleTriRelations : public CATGeoOperator {
   // public methods
public:
   //=================================================================
   // Object management
   //=================================================================
   // It is necessary to set the limits of the center and the radius of the expected PCircle
   CATCircleTriRelations( CATSoftwareConfiguration *  iSoftwareConfiguration,
                          CATGeoFactory            *  iFactory              ,
                          CATSurface               *  iSupport              ,
                          CATSurLimits              & iCenterLimits         ,
                          CATMathInterval           & iRadiusLimits         );
   ~CATCircleTriRelations();

    CATSoftwareConfiguration* GetSoftwareConfiguration() const CATGEOOverride CATGEOFinal;

   //=================================================================
   // Add Methods
   //=================================================================
   // Generic AddRelation (for experts...)
   // -------------------------------------
   // oPosition is an array of CATLONG32 of size 2 :
   //    - oPosition[0] = Place of the relation in the system
   //    - oPosition[1] = Place of the first exterior var of the CATRelationCircle
   // they both are -1 if there were a Pb with storing the relation (too much relation)
   void      AddRelation(CATRelationCircle *iRelation, CATLONG32* oPosition = NULL);
   //------------------------
   // Specific AddRelation
   //------------------------
   // return position of the relation in the system ; -1 if relation can't be Add (already enough relation)
   CATLONG32 AddRelationByPoint(const CATMathPoint2D &iPoint);
   CATLONG32 AddRelationRadius(const double &iRadius);
   // iSide = 1 if the tangents are in the same direction, -1 in the opposite direction, 0 if it doesn't matter.
   CATLONG32 AddRelationTangentCurve(CATPCurve * iPCrv, const CATCrvLimits &iLimits, const CATLONG32 iSide=0);
   // return the position of the "relation by point" in the system; the "relation by tangent" is the next one.
   CATLONG32 AddRelationByTangent(const CATMathPoint2D &iPoint, const CATMathVector2D &iTangent, const CATLONG32 iSide=0);
   CATLONG32 AddRelationByTangent(CATPCurve * iPCrv, CATCrvParam *iCrvParam, const CATLONG32 iSide=0);

   //=================================================================
   // Set Methods
   //=================================================================
   //void SetInteriorDomain(CATSurLimits &iCenterLimits, CATMathInterval &iRadiusLimits);

   //-------------------------------
   // For the Relation Tangent Crv
   //-------------------------------
   // return FALSE if it couldn't find the PCrv
   CATBoolean ReplacePCrv(CATPCurve * iOldPCrv, CATPCurve * iNewPCrv,
                          const CATCrvLimits & iNewCrvLimits, const CATLONG32 iNewSide = 0);
   // Faster, False if Relation[iRelationNumber] is not a Relation Tangent Crv
   CATBoolean SetPCrv    (const CATLONG32 iRelationNumber, CATPCurve * iNewPCrv,
                          const CATCrvLimits & iNewCrvLimits, const CATLONG32 iNewSide = 0);

   // False if Relation[iRelationNumber] is not a Relation Tangent Crv
   CATBoolean SetSide(const CATLONG32 iRelationNumber, const CATLONG32 iNewSide);
   // Faster, return FALSE if it couldn't find the PCrv
   CATBoolean SetSide(CATPCurve * iPCrv, const CATLONG32 iNewSide);

   //=================================================================
   // Information Methods
   //=================================================================

   // TRUE if there is three relations well set
   CATBoolean IsSquare();



   //=================================================================
   // Solve Method
   //=================================================================
   // return CATMathOK if everything is all right
   //        CATMathIllConditionnedSystem : if the system is not square (there may have been an error during Add
   //                                       procedure : too much or not enough Adds, a mistake in the parameters...)
   //        Some other errors during the solve procedure may happen
   int RunOperator();
   CATMathDiagnostic GetDiagnostic();




   //=================================================================
   // Get Methods
   //=================================================================

   CATLONG32 GetNumberOfSolutions() const;

   // Management of Solutions
   void Beginning();
   CATBoolean Next();

   // This method creates a PCircle, so don't forget to do : iFactory->Remove(PCircle)
   // ioCrvParam is an array of size 3 : it return the CrvParams on the circle
   CATPCircle * CreatePCircleSolution(CATCrvParam *ioCrvParam = NULL) const;

   // To get the CrvParam on the curves
   // return TRUE if the CrvParam has been found correctly
   CATBoolean GetCrvParam(CATLONG32 iRelationNumber, CATCrvParam *ioCrvParam) const;
   // Slower than the previous one (need to compare all the CATPCurve*)
   CATBoolean GetCrvParam(CATPCurve * iPCrv, CATCrvParam *ioCrvParam) const;

   // To get the Side on the curves return 0 if no Side found
   // this method can be used for both "relation tangent curve" and "relation by tangent"
   CATLONG32 GetSide(CATLONG32 iRelationNumber) const;
   // this one can only be used for "relation tangent curve"
   CATLONG32 GetSide(CATPCurve * iPCrv) const;
   // to see if the current circle is a half a circle
   //should be called after CreatePCircleSolution
   CATBoolean IsHalfCircle() const ;




private:
   CATMathDiagnostic RunGeneric();

   CATMathDiagnostic RunByThreePoints();
   CATMathDiagnostic RunOneCurveTwoPoints();
   CATMathDiagnostic RunTwoCurvesOnePoint();
   CATMathDiagnostic RunThreeCurves();

   CATMathDiagnostic RunTanByTan();
   CATMathDiagnostic RunByTanByPoint();
   CATMathDiagnostic RunByTanRadius();

   CATMathDiagnostic RunBiTanRadius();
   CATMathDiagnostic RunTanPointRadius();
   CATMathDiagnostic RunBiPointRadius();


   // Solution private management
   void AddCenterRadius(CATSurParam &iCenter, const double iRadius,
                        double * iCrvParam = NULL, CATLONG32 *iSide = NULL, CATAngle *iAngle = NULL);
   void AddSurParam    (CATSurParam &iSurParam1, CATSurParam &iSurParam2, CATSurParam &iSurParam3,
                        double * iCrvParam = NULL, CATLONG32 *iSide = NULL);
   void ResetSol();


   //data
   CATMathDiagnostic           _Diagnostic;
   CATLONG32                   _NbRelations;
   CATLONG32                   _ExteriorDim;
   CATLONG32                   _Side[3];
   CATRelationCircle         * _RelationToDelete[3];
   CATMathRelationSolver     * _MathSolver;
   CATSurface                * _Support;
   CATMathIntervalND         * _InteriorDomain;
   CATSurLimits              * _CircleDomain;

   CATBooleanConstraintCircle* _ConstraintToDelete[3];
   CATLONG32                   _NbOfConstraint;

   // Canonical treatment
   CATLONG32                   _CircleByPoint;
   CATLONG32                   _CircleByTan;
   CATLONG32                   _CircleRadius;
   CATLONG32                   _CircleTanCrv;
   //obh option interne au cgmreplay pour couvrir le run generic
   CATBoolean                  _ForceRunGeneric;

   // Results
   CATLONG32                   _SolIndex;
   CATLONG32                   _NbOfSol;

   CATCircleTriRelationsSol ** _Solutions;

   CATSoftwareConfiguration  * _SoftwareConfiguration;

   //========================================================================
   // Gestion CGMReplay
   //========================================================================
protected:
   friend class CATGeoStreamFactory;

   // private static data
   static CATString _OperatorId;

public:

   const CATString * GetOperatorId();
   //-----------------------------------------------------------------------
   //- Gestion timer
   //-----------------------------------------------------------------------  
   CATGeoOpTimer * GetTimer();

   //-----------------------------------------------------------------------
   //- Gestion Mode Record 
   //-----------------------------------------------------------------------  

   CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
   virtual void WriteInput(CATCGMStream &ioStream);
   void WriteByThreePoints(CATCGMStream &ioStream);
   void WriteOneCurveTwoPoints(CATCGMStream &ioStream);
   void WriteTwoCurvesOnePoint(CATCGMStream &ioStream);
   void WriteThreeCurves(CATCGMStream &ioStream);
   void WriteTanByTan(CATCGMStream &ioStream);
   void WriteByTanByPoint(CATCGMStream &ioStream);
   void WriteByTanRadius(CATCGMStream &ioStream);
   void WriteBiTanRadius(CATCGMStream &ioStream);
   void WriteTanPointRadius(CATCGMStream &ioStream);
   void WriteBiPointRadius(CATCGMStream &ioStream);
   void WriteGeneric(CATCGMStream &ioStream);


   virtual void WriteOutput(CATCGMStream &ioStream);

   virtual CATBoolean ValidateOutput(CATCGMStream& ioStream,  CATCGMOutput & os,int VersionNumber=1);
   virtual void Dump( CATCGMOutput& iOs ) ;
   virtual void DumpOutput(CATCGMOutput &iOs);
   virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& iOs,int VersionNumber=1);

   virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

   void ReadInput(CATCGMStream &ioStream, CATICGMObject ** ioGeometry, int VersionOfStream=1);
   void ReadByThreePoints(CATCGMStream &ioStream, CATICGMObject ** ioGeometry, int VersionOfStream=1);
   void ReadOneCurveTwoPoints(CATCGMStream &ioStream, CATICGMObject ** ioGeometry, int VersionOfStream=1);
   void ReadTwoCurvesOnePoint(CATCGMStream &ioStream, CATICGMObject ** ioGeometry, int VersionOfStream=1);
   void ReadThreeCurves(CATCGMStream &ioStream, CATICGMObject ** ioGeometry, int VersionOfStream=1);
   void ReadTanByTan(CATCGMStream &ioStream, CATICGMObject ** ioGeometry,int VersionOfStream=1);
   void ReadByTanByPoint(CATCGMStream &ioStream, CATICGMObject ** ioGeometry, int VersionOfStream=1);
   void ReadByTanRadius(CATCGMStream &ioStream, CATICGMObject ** ioGeometry, int VersionOfStream=1);
   void ReadBiTanRadius(CATCGMStream &ioStream, CATICGMObject ** ioGeometry, int VersionOfStream=1);
   void ReadTanPointRadius(CATCGMStream &ioStream, CATICGMObject ** ioGeometry, int VersionOfStream=1);
   void ReadBiPointRadius(CATCGMStream &ioStream, CATICGMObject ** ioGeometry, int VersionOfStream=1);
   //void ReadGeneric(CATCGMStream &ioStream, CATICGMObject **); not implemented yet
};

#endif


