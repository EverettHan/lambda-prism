#ifndef CATFrFTraceManager_H
#define CATFrFTraceManager_H

//=============================================================================
//
// DESCRIPTION : Trace manager / trace tools
//
//            (E) : english version (version anglaise)
//            (F) : french version  (version francaise)

//            (E)   Tools  (set of macros and services)        giving comparable traces in various environments/contexts
//            (F)   Outils (ensemble de macros et de services) donnant des traces comparables dans differents environnements/contextes
//
// (E) CAUTION  :    to use in a .cpp file and not in a .h file
//                   (in order to avoid conflicts between different uses in different objects)
//
// (F) ATTENTION:    a n'inclure que dans un .cpp et pas dans un .h
//                   (eviter les conflits entre differentes utilisations au sein d'objets differents)
//
//=============================================================================
//
// Use                                                                 | Utilisation:
// ---                                                                 | -----------
// 1) Definition                                                       | 1) Definition
//    ----------                                                       |    ----------
// 1.0)   (E) for no trace (default)                                   | 1.0)  (F) pour absence de traces (par defaut)
//    #include "CATFrFTraceManager.h"                                  |    #include "CATFrFTraceManager.h"
//                                                                     |
// 1.1)   (E) for traces independant from factory scale (default)      | 1.1)  (F) pour traces independantes de l'echelle (par defaut)
//            (if correct use)                                         |           (a condition de faire les appels corrects de macros)
// 1.1.a)     implicitly using tolerance object linked to _Factory     | 1.1.a)     avec utilisation implicite de la tolerance associee a _Factory
//            CATGetTolerance(_Factory)                                |            CATGetTolerance(_Factory)
//    //  (E) Traces activation                                        |    // (F) Activation des traces
//    #define TrMacOn                                                  |    #define TrMacOn
//    //  (E) Macros definition                                        |    // (F) Definition des macros
//    #include "CATFrFTraceManager.h"                                  |    #include "CATFrFTraceManager.h"
// 1.1.b) using the tolerance object linked to a user factory          | 1.1.b)(F) avec utilisation de la tolerance associee a une factory utilisateur
//    //  (E) Traces activation                                        |    // (F) Activation des traces
//    #define TrMacOn                                                  |    #define TrMacOn
//    CATGeoFactory*         UserFactory = ...;                        |    CATGeoFactory*         UserFactory = ...;
//    #define TrMacFactory   UserFactory                               |    #define TrMacFactory   UserFactory
//    //  (E) Macros definition                                        |    // (F) Definition des macros
//    #include "CATFrFTraceManager.h"                                  |    #include "CATFrFTraceManager.h"
// 1.1.c) (E) using a user tolerance object                            | 1.1.c)(F) avec utilisation de la tolerance definie par l'utilisateur
//    //  (E) Traces activation                                        |    // (F) Activation des traces
//    #define TrMacOn                                                  |    #define TrMacOn
//    const CATTolerance&    UserTolObject = ...;                      |    const CATTolerance&    UserTolObject = ...;
//    #define TrMacTolObject UserTolObject                             |    #define TrMacTolObject UserTolObject
//    //  (E) Macros definition                                        |    // (F) Definition des macros
//    #include "CATFrFTraceManager.h"                                  |    #include "CATFrFTraceManager.h"
//                                                                     |
// 1.2)   (E) for active traces depending on scale                     | 1.2)  (F) pour traces vraies, dependantes de l'echelle
//    //  (E) Traces activation                                        |    // (F) Activation des traces
//    #define TrMacOn                                                  |    #define TrMacOn
//    //  (E) Traces unscaling deactvation                             |    // (F) Desactivation du de la remise des traces echelle 1 : les traces restent a l'echelle
//    #define TrMacUnScaleOff                                          |    #define TrMacUnScaleOff                       
//    //  (E) Macros definition                                        |    // (F) Definition des macros
//    #include "CATFrFTraceManager.h"                                  |    #include "CATFrFTraceManager.h"
//                                                                     |
// 1.3)   (E) for output redefinition (default: cout, endl)            | 1.3)  (F) pour redefinition des sorties (par defaut, sur cout, endl)
//    #define TrMacOn                                                  |    #define TrMacOn
//    #define TrMacOut  cgmout                                         |    #define TrMacOut  cgmout
//    #define TrMacEndl cgmendl                                        |    #define TrMacEndl cgmendl
//    #include "CATFrFTraceManager.h"                                  |    #include "CATFrFTraceManager.h"
//                                                                     |
// 2) Samples of use                                                   | 2) Exemples d'utilisation
//    --------------                                                   |    ----------------------
//
//    cout<<" parametre "<<TrMacScale1Value(p)<<" SquareDistance"<<TrMacScale2Value(SquareDistance)<<endl;
//    TrMacVectorDump("Vecteur P1P2 au parametre "<<TrMacScale1Value(p), Vector);
//
// 3) Macros list                                                         | 3) Liste complete des macros
//    -----------                                                         |    -------------------------
//                                                                        |
// 3.1) Unscaling macros                                                  | Macros de mise au scale
//      ----------------                                                  | -----------------------
//      (give equivalent value at Scale 1 if unscaling active)            | (retournent la valeur equivalente a l'echelle 1 si UnScaling actif)
//                                                                        |
// 3.1.a) general macros                                                  | 3.1.a) macros generales
//        --------------                                                  |        ----------------
//        - TrMacScaleiValue    is the generic name for                   | - TrMacScaleiValue    est le nom generique pour la
//          tracing a value varying like power  i of scale                |   trace d'une valeur variant comme la puissance  i de l'echelle
//        - TrMacInvScaleiValue is the generic name for                   | - TrMacInvScaleiValue est le nom generique pour la
//          tracing a value varying like power -i of scale                |   trace d'une valeur variant comme la puissance -i de l'echelle
//                                                                        |
//        - TrMacScale0Value    (v) scale independant value               | - TrMacScale0Value    (v)   pour valeur independante du  scale
//        - TrMacScale1Value    (v) value varying like scale              | - TrMacScale1Value    (v)   pour valeur variant comme le scale
//        - TrMacScale2Value    (v) value varying like square scale       | - TrMacScale2Value    (v)   pour valeur variant comme la puissance 2 du scale
//        - TrMacInvScale1Value (v) value varying like 1/scale            | - TrMacInvScale1Value (v)   pour valeur variant comme l'inverse du scale
//        - TrMacInvScale2Value (v) value varying like 1/(squarescale)    | - TrMacInvScale2Value (v)   pour valeur variant comme l'inverse de la puissance 2 du scale
//        - TrMacScaleNValue    (v,N) value varying like scale**N         | - TrMacScaleNValue    (v,N) pour valeur variant comme la puissance N du scale
//                                                                        |
// 3.1.b) macros for standard XScale rules functions                      | 3.1.b) macros adaptees aux fonctions generales de conventions standard
//        ------------------------------------------                      |        ---------------------------------------------------------------
//        (parameter varying like power 1 of scale)                       | (parametre variant comme la puissance 1 du scale)
//        (function  varying like power 1 of scale)                       | (fonction  variant comme la puissance 1 du scale)
//        - TrMacXValue            (X)     parameter value                |  - TrMacXValue            (X)    pour valeur de parametre
//        - TrMacFValue            (F)     function value                 |  - TrMacFValue            (F)    pour valeur de fonction
//        - TrMacdFValue           (dF)    first derivative               |  - TrMacdFValue           (dF)   pour valeur de derivee premiere
//        - TrMacd2FValue          (d2F)   second derivative              |  - TrMacd2FValue          (d2F)  pour valeur de derivee seconde
//        - TrMacF2Value           (F2)    square function value          |  - TrMacF2Value           (F2)   pour valeur de fonction au carre
//        - TrMacdF2Value          (dF2)   square function derivative     |  - TrMacdF2Value          (dF2)  pour valeur de derivee premiere de fonction au carre
//        - TrMacd2F2Value         (d2F2)  square func 2nd derivative     |  - TrMacd2F2Value         (d2F2) pour valeur de derivee seconde  de fonction au carre
//                                                                        |
// 3.2)  complex values traces macros                                     | 3.2) macros de traces de valeurs complexes
//       ----------------------------                                     |      -------------------------------------
//        - TrMacPointTrace        (Texte,Point)     CATMathPoint    value|  - TrMacPointTrace        (Texte,Point)    trace la valeur d'un CATMathPoint
//        - TrMacPoint2DTrace      (Texte,Point2D)   CATMathPoint2D  value|  - TrMacPoint2DTrace      (Texte,Point2D)  trace la valeur d'un CATMathPoint2D
//        - TrMacTangentTrace      (Texte,Tangent)   CATMathVector   value|  - TrMacTangentTrace      (Texte,Tangent)  trace la valeur d'un CATMathVector contenant une tangente
//        - TrMacTangent2DTrace    (Texte,Tangent2D) CATMathVector2D value|  - TrMacTangentTrace      (Texte,Tangent2D)trace la valeur d'un CATMathVector2D contenant une tangente
//        - TrMacCrvParamTrace     (Texte,CrvParam)  CATCrvParam     value|  - TrMacCrvParamTrace     (Texte,CrvParam) trace la valeur d'un CATCrvParam
//        - TrMacIntervalTrace     (Texte,Interval)  CATMathInterval value|  - TrMacIntervalTrace     (Texte,Interval) trace la valeur d'un CATMathInterval
//                                                                        |
// 3.3)  Dump macros                                                      | 3.3) macros de Dump
//       -----------                                                      |      --------------
//       these macros give the dump of a text and an element,             | ces macros realisent le Dump d'un element, precede par un texte,
//       on output TrMacOut (default: cout)                               | sur la sortie TrMacOut (par defaut cout)
//        - TrMacCrvParamDump      (Text,CrvParam)  for a CATCrvParam    value
//        - TrMacCrvLimitsDump     (Text,CrvLimits) for a CATCrvLimits   value
//        - TrMacSurParamDump      (Text,SurParam)  for a CATSurParam    value
//        - TrMacPointDump         (Text,Point)     for a CATMathPoint   value
//        - TrMacPoint2DDump       (Text,Point2D)   for a CATMathPoint2D value
//        - TrMacVectorDump        (Text,Vector)    for a CATMathVector  value
//        - TrMacVector2DDump      (Text,Vector2D)  for a CATMathVector2D  value
//        - TrMacAxisDump          (Text,Axis)      for a CATMathAxis    value
//        - TrMacTransformationDump(Text,Transfo)   for a CATMathTransformation (WARNING: uses Dump() function for matrix, hence cout instead of TrMacOut user definition)
//        - TrMacTangentDump       (Text,Tangent)   for a CATMathVector value containing a tangent (not dependning on scale)
//
//=============================================================================
// 21/11/14 NLD Creation
//              Gestion de traces comparables
//              Premier jeu (issu de CATFrFTopologicalSweepCx2/CATExtruderBySweep)
//              1) Parametrisation
//              - TrMacUnScaleOff
//              - TrMacUnScaleOn          pour UnScaledTraces
//              - TrMacTolObject          pour _TolObject
//              2) Macros de traduction de valeurs
//              - TrMacScale1Value        pour Scale1ValueTrace
//              - TrMacInvScale1Value     pour InvScale1ValueTrace
//              - TrMacScale2Value        pour Scale2ValueTrace
//              - TrMacInvScale2Value     pour InvScale2ValueTrace
//              - TrMacScaleXValue
//              - TrMacScaleFValue
//              - TrMacScaleDFValue
//              - TrMacScaleD2FValue
//              - TrMacScaleF2Value
//              - TrMacScaleDF2Value
//              - TrMacScaleD2F2Value
//              3) Macros de Dump
//              - TrMacPointOrVectorDump  pour PointOrVectorDump
//              - TrMacPointDump          pour PointDump
//              - TrMacVectorDump         pour VectorDump
//              - TrMacTangentDump        pour TangentDump
//              - TrMacCrvParamDump       pour CrvParamDump
//              - TrMacCrvLimitsDump      pour CrvLimitsDump
//              - TrMacSurParamDump       pour SurParamDump
//              - TrMacAxisDump           pour AxisDump
//              - TrMacTransformationDump pour TransformationDump
// 09/12/14 NLD Documentation de TrMacFactory. Exemples d'utilisation 1.1.a, 1.1.b et 1.1.c
//              Documentation complete des macros dans en-tete: la lecture des macros n'est plus necessaires
//              Version anglaise / version francaise de la documentation
//              Changement de nomenclature:
//              - TrMacdFValue()   remplace TrMacDFValue()
//              - TrMacd2FValue()  remplace TrMacD2FValue()
//              - TrMacdF2Value()  remplace TrMacDF2Value()
//              - TrMacd2F2Value() remplace TrMacD2F2Value()
//              Ajouts
//              - TrMacCrvParamTrace()
// 11/12/14 NLD Ajout CATFrFTraceManager() avec AddressNumber()
// 12/12/14 NLD Argument optionnel iForceForget a AddressNumber()
// 21/01/15 NLD Renommages conformement a la documentation dans l'en-tete:
//              TrMacXValue    remplace TrMacScaleXValue
//              TrMacFValue    remplace TrMacScaleFValue
//              TrMacDFValue   remplace TrMacScaleDFValue
//              TrMacD2FValue  remplace TrMacScaleD2FValue
//              TrMacF2Value   remplace TrMacScaleF2Value
//              TrMacDF2Value  remplace TrMacScaleDF2Value
//              TrMacD2F2Value remplace TrMacScaleD2F2Value
// 28/01/15 NLD Ajout TrMacTangentTrace()
// 11/02/15 NLD Ajout instrumentation de couverture par niveau (CGMLevel) max
//              SetId(), UseMethod(), MethodUseSummary()
// 18/02/15 NLD Ajout TrMacScaleNValue()
// 09/03/15 NLD Ajout TrMacIntervalTrace()
// 15/04/15 NLD Ajout TrMacPointOrVector2DValue(), TrMacTangent2DValue(),
//              TrMacPointOrVector2DDump()
// 15/10/15 NLD Deplacement dans Mathematics
// 16/10/15 NLD Ajout TrMac3x3MatrixDump() essentiellement pour les besoins de TrMacTransformationDump()
//              avec dump sur la sortie parametrable et non plus selon les bons vouloirs de Dump()
//              Ajout d'exemple de redefinition de TrMacOut, TrMacEndl
//=============================================================================
// xx/xx/xx NLD A FAIRE
//              - TrMacSurLimitsDump
//=============================================================================

//=============================================================================
//                               // N.B afin de permettre la redescente au plus bas (ex Mathematics)
//                               //     on n'inclue pas de fichier geometrique, ex: CATCrvParam.h
//                               //     l'inclusion sera faite par le programme appelant si utilisation des macros correspondantes
#include "ExportedByCATMathStream.h"
// #include "CATTolerance.h"

//=============================================================================
// Traces manager definition
//=============================================================================
#include "CATListPV.h"
#include "CATListOfInt.h"
#include "CATCGMOutput.h"
#include "CATPower.h"
class ExportedByCATMathStream CATFrFTraceManager
{
 public:
  virtual           ~CATFrFTraceManager();
                     CATFrFTraceManager();
          //     numbering addresses may help obtain a stable trace, with a global or several traces managers
          //     N.B it may be helpful to force manager to forget address (at object deletion:
          //         a different number will then be associated to same address if memory pool uses
          //         this address later for another object)
          int        AddressNumber     (void* p            ,
                                        int   iForceForget = 0
                                       );

          // Utilities for summary of methods uses by level
          // ----------------------------------------------
          // defines global id for this manager
          void       SetId             (char* iId          );

          // indicates a method use
          void       UseMethod         (int   iMethodId    ,
                                        int   iCGMLevel    );

          // traces methods uses summary on output file
          void       MethodUseSummary  (CATCGMOutput& Output);

 private:
          //                            // Data for association pointer/number in traces
          //                            // ---------------------------------------------
          CATListPV    _ListP;          // pointers list
          void*        _LastP;          // last pointer
          int          _LastN;          // last number

          //                            // Data for method use traces
          //                            // --------------------------
          char*        _Id;
          CATListOfInt _MethodId;
          CATListOfInt _MethodMaxLevel;
 
};

//=============================================================================
// Macros definition
//=============================================================================
// 0) Parametrisation des macros
//    --------------------------
#ifndef TrMacUnScaleOff
#define TrMacUnScaleOn  "NLD030812 par defaut les traces sont independantes du Scale"
#endif
#ifndef TrMacFactory 
#define TrMacFactory _Factory
#endif
#ifndef TrMacTolObject
#define TrMacTolObject (CATGetTolerance(TrMacFactory))
#endif
#ifndef TrMacOut
#define TrMacOut cout
#endif
#ifndef TrMacEndl
#define TrMacEndl endl
#endif

// 1) Macros de mise au scale (retournent la valeur equivalente a l'echelle 1 si UnScaling actif)
//    -----------------------
// 1.a) macros generales                                                (voir liste dans en-tete)
#define    TrMacScale0Value(x)   (x)
#ifdef TrMacUnScaleOn
#define    TrMacScale1Value(x)  ((x)/TrMacTolObject.GetScale()      )
#define TrMacInvScale1Value(x)  ((x)*TrMacTolObject.GetScale()      )
#define    TrMacScale2Value(x)  ((x)/TrMacTolObject.GetSquareScale())
#define TrMacInvScale2Value(x)  ((x)*TrMacTolObject.GetSquareScale())
#define TrMacScaleNValue(x,N)   ((x)/CATPower(TrMacTolObject.GetScale(),N))
#else
#define    TrMacScale1Value(x)   (x)
#define TrMacInvScale1Value(x)   (x)
#define    TrMacScale2Value(x)   (x)
#define TrMacInvScale2Value(x)   (x)
#define    TrMacScaleNValue(x,N) (x)
#endif
// 1.b) macros adaptees aux fonctions generales de conventions standard (voir liste dans en-tete)
//      parametre variant comme la puissance 1 du scale
//      fonction  variant comme la puissance 1 du scale
//      N.B les macros *F2Value peuvent etre utilisees soit pour le carre d'une fonction de convention standard
//          soit pour une fonction variant comme la puissance 2 du scale (ex: une fonction aux conventions d'un minimiseur)
#define    TrMacXValue(X)       (TrMacScale1Value(X))
#define    TrMacFValue(F)       (TrMacScale1Value(F))
#define    TrMacDFValue(dF)     (TrMacScale0Value(dF))
#define    TrMacD2FValue(d2F)   (TrMacInvScale1Value(d2F))
#define    TrMacF2Value(F2)     (TrMacScale2Value(F2))
#define    TrMacDF2Value(dF2)   (TrMacScale1Value(dF2))
#define    TrMacD2F2Value(d2F2) (TrMacScale0Value(d2F2))
//
#define    TrMacCrvParamTrace(Texte,CrvParam)   Texte<<"("<<(CrvParam).GetArcNumber()   <<","<<TrMacScale1Value((CrvParam).GetLocalParam ())<<")"
#define    TrMacIntervalTrace(Texte,Interval)   Texte<<"["<<TrMacScale1Value(Interval.GetMin())<<","<<TrMacScale1Value(Interval.GetMax())<<"]"


// 2) Macros de dump
//    --------------
//#define TrMacPointOrVectorValue(Texte,PointOrVector)            (Texte)
#define TrMacPointOrVectorValue(Texte,PointOrVector)            \
        Texte                                                   \
     << "(x="<<TrMacScale1Value((PointOrVector).GetX())         \
     <<", y="<<TrMacScale1Value((PointOrVector).GetY())         \
     <<", z="<<TrMacScale1Value((PointOrVector).GetZ())         \
     <<")"
#define TrMacPointOrVector2DValue(Texte,PointOrVector)          \
        Texte                                                   \
     << "(x="<<TrMacScale1Value((PointOrVector).GetX())         \
     <<", y="<<TrMacScale1Value((PointOrVector).GetY())         \
     <<")"
#define TrMacTangentValue(Texte,Tangent)                        \
        Texte                                                   \
     << "(x="<<((Tangent).GetX())                               \
     <<", y="<<((Tangent).GetY())                               \
     <<", z="<<((Tangent).GetZ())                               \
     <<")"
#define TrMacTangent2DValue(Texte,Tangent)                      \
        Texte                                                   \
     << "(x="<<((Tangent).GetX())                               \
     <<", y="<<((Tangent).GetY())                               \
     <<")"

#ifdef TrMacOn
#define TrMacPointOrVectorDump(Texte,PointOrVector)  TrMacOut<<TrMacPointOrVectorValue(Texte,PointOrVector)
#define TrMacPointOrVector2DDump(Texte,PointOrVector) TrMacOut<<TrMacPointOrVector2DValue(Texte,PointOrVector)
#define      TrMacCrvParamDump(Texte,CrvParam)       TrMacOut<<TrMacCrvParamTrace(Texte,(CrvParam));
#define     TrMacCrvLimitsDump(Texte,CrvLimits)     {TrMacOut<<Texte<<"((CATCrvLimits) ";                                      \
                                                     CATCrvParam Start, End;(CrvLimits).GetExtremities(Start,End);             \
                                                     TrMacCrvParamDump(""                ,Start);                              \
                                                     TrMacCrvParamDump(" <= Parameter <=",End);                                \
                                                     TrMacOut<<")";}
#define      TrMacSurParamDump(Texte,SurParam)       TrMacOut<<Texte<<"("<<(SurParam).GetPatchNumberU()<<","<<TrMacScale1Value((SurParam).GetLocalParamU())<<")"\
                                                        <<"("<<(SurParam).GetPatchNumberV()<<","<<TrMacScale1Value((SurParam).GetLocalParamV())<<")";
#define         TrMacPointDump(Texte,Point)          TrMacPointOrVectorDump(Texte,Point)
#define       TrMacPoint2DDump(Texte,Point)          TrMacPointOrVector2DDump(Texte,Point)
#define        TrMacVectorDump(Texte,Vector)         TrMacPointOrVectorDump(Texte,Vector)
#define      TrMacVector2DDump(Texte,Vector)         TrMacPointOrVector2DDump(Texte,Vector)
#define        TrMacTangentDump(Texte,Tangent)      {TrMacOut<<TrMacTangentValue(Texte,Tangent)<<TrMacEndl;}

#define          TrMacAxisDump(Texte,Axis)                                                                                     \
                                                    {TrMacOut<<Texte<<TrMacEndl                                                \
                                                             <<" Origin = "<<TrMacScale1Value((Axis).GetOrigin().GetX())       \
                                                             <<" "         <<TrMacScale1Value((Axis).GetOrigin().GetY())       \
                                                             <<" "         <<TrMacScale1Value((Axis).GetOrigin().GetZ())       \
                                                             <<TrMacEndl;                                                      \
                                                     TrMacOut<<TrMacTangentValue(" FirstDir  = ",(Axis).GetFirstDirection());  \
                                                     TrMacOut<<TrMacTangentValue(" SeconfDir = ",(Axis).GetSecondDirection()); \
                                                     TrMacOut<<TrMacTangentValue(" ThirdDir  = ",(Axis).GetThirdDirection());} //

// N.B le Dump de matrice est dans CATMathOstream.cpp mais n'est pas utilisable ici avec une sortie quelconque
//#define TrMac3x3MatrixDump(Texte,Matrix)            {TrMacOut<<Texte<<TrMacEndl;Matrix.Dump();                               //
#define TrMac3x3MatrixDump(Texte,Matrix)            {TrMacOut<<Texte<<TrMacEndl;                                               \
                                                     int w = 12;                                                               \
                                                     CATMathVector Column1, Column2, Column3;                                  \
                                                     Matrix.GetFirstColumn(Column1);                                           \
                                                     Matrix.GetSecondColumn(Column2);                                          \
                                                     Matrix.GetThirdColumn(Column3);                                           \
                                                     TrMacOut<<" | "<<setw(w)<<Column1.GetX()<<" "<<setw(w)<<Column2.GetX()<<" "<<setw(w)<<Column3.GetX()<<" | "<<TrMacEndl;\
                                                     TrMacOut<<" | "<<setw(w)<<Column1.GetY()<<" "<<setw(w)<<Column2.GetY()<<" "<<setw(w)<<Column3.GetY()<<" | "<<TrMacEndl;\
                                                     TrMacOut<<" | "<<setw(w)<<Column1.GetZ()<<" "<<setw(w)<<Column2.GetZ()<<" "<<setw(w)<<Column3.GetZ()<<" | "<<TrMacEndl;\
                                                    }                                                      //
#define TrMacTransformationDump(Texte,Transfo)      {TrMacOut<<Texte<<TrMacEndl<<"Matrix="<<TrMacEndl;                         \
                                                     TrMac3x3MatrixDump("",Transfo.GetMatrix())                                \
                                                     VectorDump("Vector=",Transfo.GetVector());                                \
                                                     TrMacOut<<TrMacEndl;}

#define        TrMacPointTrace(Texte,Point)          TrMacPointOrVectorValue(Texte,Point)                                      //
#define      TrMacPoint2DTrace(Texte,Point)          TrMacPointOrVector2DValue(Texte,Point)                                    //
#define        TrMacTangentTrace(Texte,Tangent)      TrMacTangentValue(Texte,Tangent)                                          //
#define        TrMacTangent2DTrace(Texte,Tangent)    TrMacTangent2DValue(Texte,Tangent)                                        //

#else
#define TrMacPointOrVectorDump(Texte,PointOrVector) //
#define TrMacPointOrVector2DDump(Texte,PointOrVector) //
#define      TrMacCrvParamDump(Texte,CrvParam)      //
#define     TrMacCrvLimitsDump(Texte,CrvLimits)     //
#define      TrMacSurParamDump(Texte,SurParam)      //
#define         TrMacPointDump(Texte,Point)         //
#define         TrMacPoint2DDump(Texte,Point)       //
#define        TrMacVectorDump(Texte,Vector)        //
#define      TrMacVector2DDump(Texte,Vector)        //
#define          TrMacAxisDump(Texte,Axis)          //
#define TrMac3x3MatrixDump(Texte,Matrix)            //
#define TrMacTransformationDump(Texte,Transfo)      //
#define        TrMacTangentDump(Texte,Tangent)      //
#define      TrMacTangent2DDump(Texte,Tangent)      //
#define        TrMacPointTrace(Texte,Point)         //
#define      TrMacPoint2DTrace(Texte,Point)         //
#define        TrMacTangentTrace(Texte,Tangent)     //
#define      TrMacTangent2DTrace(Texte,Tangent)     //
#endif

#endif
