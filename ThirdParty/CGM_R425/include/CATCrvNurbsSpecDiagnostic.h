//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//==========================================================================
// class CATNurbsDiagnostic
//==========================================================================
// May 2001   Creation                                            CCK-PRG
// 28/03/08 NLD Nomenclature: une courbure c'est une courbure, et un rayon
//              de courbure c'est un rayon de courbure. qu'on se le dise
//==========================================================================
// This object is used in the contect of geometry transfer.
// It relates about one geometrical pathology that has been detected
// during the transfer of a nurbs element.
// 
// It provides with some information about the pathology that has been detected :
//      1/ the severity of the pathology :
//             - In spite of this pathology, this element can be translated 
//            into a V5 element. It is just a warning.
//             - This pathology prevent us from translating the element into V5,
//             - the check detected a special behavious and could not conclude.
//             We have a doubt. A precise check has to be performed.
//      2/ geometrical elements other information like arc number, parameter, ...
//      that would be useful if we can not repair the element.
//
// This object is only an interface
//-----------------------------------------------------------------------------
#ifndef CATCrvNurbsSpecDiagnostic_H
#define CATCrvNurbsSpecDiagnostic_H


#include "CATListOfCATGeometries.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"


typedef enum {
              CATGeomNurbsCrvDiag_ArcTooShort,
              CATGeomNurbsCrvDiag_ExtNullTangent,
              CATGeomNurbsCrvDiag_CuspInsideAnArc,
              CATGeomNurbsCrvDiag_CuspAtArcsJunction,
              CATGeomNurbsCrvDiag_BadParametrisation,
              CATGeomNurbsCrvDiag_ControlPointsOutOfSpace,
              CATGeomNurbsCrvDiag_ControlPointsTooClose,
              CATGeomNurbsCrvDiag_CurveTooShort,
              CATGeomNurbsCrvDiag_MicroCurvature,
              CATGeomNurbsCrvDiag_DegeneratedBorderForms
              // CATGeomNurbsCrvDiag_ArcWithAutoIntersection,
              // CATGeomNurbsCrvDiag_CrvWithAutoIntersection,
              // CATGeomNurbsCrvDiag_PCurveOutOfSupport
             } CATGeomNurbsDiagType;

typedef enum {
              CATStrongErrorToTest,
              CATWarningToTest,
              CATNotToTest
             } CATSpecTypeError;
   

class ExportedByYP00IMPL CATCrvNurbsSpecDiagnostic : public CATCGMVirtual
{
  public :

      CATCrvNurbsSpecDiagnostic();
     ~CATCrvNurbsSpecDiagnostic();

      //===================================================================================
      // Methodes SET
      // Si aucun Set, on fait tous les checks avec les severites necessaires au transfert
      // V4toV5
      // Si pas de Set pour une pathologie donnee => Check effectue avec valeurs par defaut
      // Pour ne pas faire un check, faire un set avec CATNotToTest
      // A appeler AVANT le faire le Run sur le CATFrFBezierCrvAnalysis::Run()
      //===================================================================================

      void SetArcTooShortSpec            (CATSpecTypeError iSpecError         ,
                                          double           iArcLengthTolerance);
         // Defaut : CATWarningToTest ; iTolerance = factory->GetResolution() = 10-3

      void SetExtNullTangentSpec         (CATSpecTypeError iSpecError         ,
                                          double           iTgtTolerance      );
         // Defaut : CATWarningToTest ; iTgtTolerance = _Factory->GetResolution()

      void SetCuspInsideAnArcSpec        (CATSpecTypeError iSpecError         ,
                                          double           iInsideAngleMin    );
         // Defaut : CATStrongErrorToTest ; iInsideAngleMin = - sqrt(2) / 2

      void SetCuspAtArcJunctionSpec      (CATSpecTypeError iSpecError         ,
                                          double           iJunctionAngleMin  );
         // Defaut : CATStrongErrorToTest ; iJunctionAngleMin = -0.85

      void SetBadParametrisationSpec     (CATSpecTypeError iSpecError         ,
                                          double           iRatio             );
         // Defaut : CATWarningToTest ; iRatio = 10

      void SetControlPointsOutOfSpaceSpec(CATSpecTypeError iSpecError         ,
                                          double           iInfinite          );
         // Defaut : CATWarningToTest ; iInfinite = _Factory->GetInfinite()

      void SetControlPointsTooCloseSpec  (CATSpecTypeError iSpecError         ,
                                          double           iMinDist           );
         // Defaut : CATWarningToTest ; iMinDist = _Factory->GetResolution() / (degree + 1)

      void SetCurveTooShortSpec          (CATSpecTypeError iSpecError         ,
                                          double           iCrvTolerance      );
         // Defaut : CATStrongErrorToTest ; iCrvTolerance = _Factory->GetResolution()

      void SetMicroCurvatureRadius       (CATSpecTypeError iSpecError         ,
                                          double           iCurvatureRadiusTol);
         // Defaut : CATStrongErrorToTest ; iCurvatureTol = 0.01

      void SetDegenBorderForm            (CATSpecTypeError iSpecError         ,
                                          double           iMinDist           );
         // Defaut : CATNotToTest ; iMinDist = _Factory->GetResolution()

      // C'est la qu'on remplit le tableau des pathologies à checker
      void SetKindOfCheck                (CATGeomNurbsDiagType * iPatho       ,
                                          CATSpecTypeError     * iSpecDiag    ,
                                          CATLISTP(CATGeometry)* iGeomKO      );
    // Pour donner la geometrie 


      //===================================================================================
      // Methodes GET
      // A appeler APRES avoir fait le Run sur le CATFrFBezierCrvAnalysis::Run()
      // Il revient a l'appelant de detruire les objets retournes par les methodes GET
      //===================================================================================

      // returns :
      //  0 if is ok
      //  1 for a strong error, no transfer
      //  2 if is just a warning
      //  -1 if we do not know, more precise check have to be called.
      CATLONG32              GetSeverity      ();

      // Renvoie un tableau de pathologies detectees de type CATGeomNurbsDiagType
      CATGeomNurbsDiagType * GetDiagnosticType(CATLONG32& oNberKO);

      // Renvoie une liste de geometries permettant de localiser les pathologies
      CATLISTP(CATGeometry)* GetGeometricsElements();

      // Renvoie le nombre de pathologies detectees
      CATLONG32 GetNumberOfPathologies();


      //===================================================================================
      // Methodes GET a usage INTERNE
      //===================================================================================
      void GetLimitsValues (double & oArcLengthTolerance,
                            double & oTgtTolerance      ,
                            double & oInsideAngleMin    ,
                            double & oJunctionAngleMin  ,
                            double & oRatio             ,
                            double & oInfinite          ,
                            double & oMinDist           ,
                            double & oCrvLengthTolerance,
                            double & oCurvatureTol      ,
                            double & oPointingTol
                           );

      void GetSpecTypeError(CATSpecTypeError*& oSeverity);

      void GetGeomKO(CATLISTP(CATGeometry)& ListOfGeomKO);

   private :

      CATGeomNurbsDiagType * _SpecDiag;
      CATSpecTypeError     * _Severity;
      CATLISTP(CATGeometry)* _ListOfGeomKO;
      double                 _ArcLengthTolerance;
      double                 _TgtTolerance;
      double                 _InsideAngleMin;
      double                 _JunctionAngleMin;
      double                 _CurvatureRadiusTol;
      double                 _Ratio;
      double                 _Infinite;
      double                 _MinDist;
      double                 _CrvLengthTolerance;
      double                 _DegenBorderTol;
};

#endif
