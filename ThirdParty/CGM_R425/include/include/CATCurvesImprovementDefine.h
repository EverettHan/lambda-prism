//===================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2000
//
// DESCRIPTION : 
//               1/ Enum pour le mode de priorite 
//               Deformation : mise en continuite avec maitrise de la deformation (jusqu'a une
//                             certaine limite)
//               Continuity  : mise en continuite sans se soucier de la deformation
//               NoPriority  : ??? pour le moment
//
//               2/ Enum pour la gestion des petites courbes
// 
//======================================================================
// January,  2001  : HLN : Creation
// July,     2003  : RNO : Add  CATCrvImprvC1ToC2Management
// 23/07     2019  : NLD : Warning stream/unstream
//                         <@CAUTION_NoInsertion_CATCurvesImprovementStreamedInputValues>
//                         et demarrage explicite à 0 des énumérations,
//                         plus explicitation de toutes les valeurs
//===================================================================
#ifndef CATCurvesImprovementDefine_H
#define CATCurvesImprovementDefine_H

//-------------------------------------------------------------------
// <@CAUTION_NoInsertion_CATCurvesImprovementStreamedInputValues>
// this tag means that no insertion/deletion must be done, values being used
// in CATCurvesImprovement stream for CGMReplay,
// as input values
//     NLD230719
//-------------------------------------------------------------------

// <@CAUTION_NoInsertion_CATCurvesImprovementStreamedInputValues>
typedef enum
{ 
   Deformation                = 0,
    Continuity                = 1,
    NoPriority                = 2
} CATCrvImprvPriority;

// <@CAUTION_NoInsertion_CATCurvesImprovementStreamedInputValues>
typedef enum
{ 
   NotModified                = 0,
      Modified                = 1,
      Concatenated            = 2
} CATCrvImprvSmallCurve;

// <@CAUTION_NoInsertion_CATCurvesImprovementStreamedInputValues>
typedef enum
{ 
           NoC1ToC2Management = 0,
      DefaultC1ToC2Management = 1,
    AllCurvesC1ToC2Management = 2
} CATCrvImprvC1ToC2Management;

typedef enum
{
  CATCrvImprvEvalRight        =  1,
  CATCrvImprvEvalLeft         = -1,
  CATCrvImprvEvalAny          = 0

} CATCrvImprvEvalPosition;

#endif
