#ifndef CATCXActivateTraces_h
#define CATCXActivateTraces_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//------------------------------------------------------------ 
// 
//  if (   CATCX_MEMORY::CATCGMActivateTraces() || CATCX_MEMORY::CATCGMActivateStatistics() )
// 
//------------------------------------------------------------ 
#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"
#include "CATechSetOfChar.h"
#include "CATCGMDebug.h"
#include "CATCX_MEMORY.h"
#include "CATBodyMode.h"
#include "CATCGMHashTable.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATCGMHashTableWithDoubleAssoc.h"
 
//------------------------------------------------------------------------------------
// Pour gestion en sortie finale 
//    indication des multiples reutilisations de construction de liens inverses
//------------------------------------------------------------------------------------
class CATCGMActivateStatistics;
class CATCXTopology;
class CATCXBody;
class CATCGMContainer;

 
class  ExportedByCATTopologicalObjects CATCXActivateTraces
{
public :
   CATCXActivateTraces();
   ~CATCXActivateTraces();

   static double GetRatioActivate();

   static void   Activate(CATCXBody *IAmABody);

   static int    AtExit();

   static void   Dump();

   static void   Clean();

   static void   Slow(CATCXBody *IAmABody, CATCXTopology* owner, CATCXTopology* cxinside, const char iMsg[]);

   // .... FullSteps_EnsureInverseCache
   static void   FullSteps_EnsureInverseCache(CATCXBody *IAmABody, const char iContext[], CATCXTopology *iTopContext );

   // .... FullSteps_CreateBody
   static void   FullSteps_CreateBody(CATBodyMode  iMode , CATCXBody *IAmABody, const char *iTracability , const int   iLine );

   // .... FullSteps_Freeze
   static void   FullSteps_Freeze(CATCXBody *IAmABody);

   // .... IsRunningTessOperator
   static void   IsRunningTessOperator(CATCXBody *IAmABody);

   static void   DeactivationObserver(CATCXBody *IAmABody, CATCXBody *iActivatedBody, CATCXTopology * iTopContext );
   static void   DeactivationSummary(CATCXBody *IAmABody);
   static void   IsUnderActivate_Observer(CATCXBody *IAmABody);
   static void   ActivateSummary ( CATCGMContainer * ipCGMContainer, int &onbBodies, int &onbActivation, int &onbActivationMax);

private:

   static        CATCXActivateTraces & _CATCXActivate();
   static void   DeactivationStart(CATCXBody *IAmABody);
   static void   DeactivationStop(CATCXBody *IAmABody);
   
   unsigned int               _NbClean;
   CATBoolean                 _ToDump;


   // Level 1 = CATCGMActivateStatistics() 

   CATBoolean                 _WithStatisticsSteps;
   unsigned int               _NbStatisticsSteps;
   CATechSetOfChar            _StatisticsSteps;

   // Level 2 = CATCGMActivateTraces() 

   unsigned int               _NbBodyActivates;
   CATechSetOfChar            _StepActivate;

   unsigned int               _NbSlows;
   CATechSetOfChar            _StepSlow;
   CATBoolean                 _SlowToDump;
   unsigned int               _NbSlowDump;

   // Level 3 = CATCGMActivateFullTraces() 
   CATechSetOfChar            _StepEnsureInverseCache;
   unsigned int               _NbStepsEnsureInverseCache;
   CATBoolean                 _WithEnsureInverseCache;

   CATCGMActivateStatistics * _Statistics;
   CATCGMHashTableWithAssoc * _DeactivatedBodies;

   CATCXBody                * _FollowedBody;
   CATCGMHashTable          * _FollowedBodyTopologies;
   unsigned int               _NbDeactivatedTopologies;
   unsigned int               _NbReactivatedTopologies;
};

 

#endif
