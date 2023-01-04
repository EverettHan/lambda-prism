#ifndef CATCGMStreamExtendedReplay_h_
#define CATCGMStreamExtendedReplay_h_
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//    INTERDICTION D'INCLURE DANS HEADER CAA
//    HEADER IMPLEMENTATION : PERMETTRE EVOLUTION VUE IMPLEMENTATIVE
//=============================================================================
  /**
    * -------------------------------------------------------------------------------------------------------
    *  TOPIC  :  CGMReplay / Extended  Run() with original submission from CATIA Live Shape developpers .
    *  ========      aka initial prototype under environemnt variable   "Multi->Run()"
    *             Extended Run() for CGMReplay  
    *                can now be managed through an explicit implementation UnderMultipleRunRecord
    *                according a tactical requirement of minimal impact on implementation (expecting limited operators)
    *
    *   CONCEPTION : main idea is to Split in two pieces 
    *   ===========      original Full definition -> (1) Full Variational Parameters + (2) Others Parameters
    *    For CIP, the suggested management (not imposed) may incorporate following information :
    *           Technology  : kind of protocols and services (vary from operator) 
    *           Version     : for incremental management along times about variations integrations (vary from operator) 
    *           Completude  : bit fields of independant variations (vary from operator and version)  
    *    Remarks : variationnal parameters are not the roots for generation of operators !
    *       Have a look on the concrete implementation with extended Run 
    *       (contact CLS or see somtehing more significant than the dummy CloneManager)
    *
    *   INTERFACING :  About preliminary protocol, all start from virtual methods of CATExtGeoOperator :
    *   =============    GeometricObjects\ProtectedInterfaces\CATExtGeoOperator.h
    * 
    *         M.1) Implement the extraction of definition of variational parameters 
    *               virtual void       WriteInputMultipleRun(CATCGMStream &iStream, CATCGMPad * ioPad = NULL ); 
    *    
    *         M.2) Implement the extraction of definition of variational parameters 
    *               virtual void       ReadInputMultipleRun(CATCGMStream &iStream, CATCGMPad  * ioPad = NULL ); 
    *
    *         M.3) Activation of extended Run() integration according to the two previous convergence (with Tests)
    *            with one line of code : SetMultipleRun(); return TRUE;
    *               virtual CATBoolean IsMultipleRun(); 
    *    
    *   IMPLEMENTING : Then the quickiest and dirtiest implementation for faster recovery of your operator 
    *   ==============    for economic integration with the associated new  protocols 
    *                     of WriteInputMultipleRun and ReadInputMultipleRun methods
    *
    *    One shortest path is to take into account the modal context inside old symetric delageted Save/Load of CGMReplay
    *         a) From WriteInput , saving the requirement from the three possible contexts
    *                 a.1  ) Old : Keep all full definition (no more active)
    *                 a.2.1) New : Only Variational parameters (CATCGMStreamImpl *)->UnderExtendedReplay()   
    *                 a.2.2) New : Other definition than variation parameters  (CATCGMStreamImpl *)->WithoutVariationalParameters()   
    *         b) From CATLoadXXX, loading the requirement from the thrre possible contexts
    *                first enhance modularity with a static method with an optionnal already created operator
    *                 b.1) Old : Load the full definition (no more active)
    *                 b.2.1) New : Load Kernel and Other parameters (CATCGMStreamImpl *)->WithoutVariationalParameters()  
    *                 b.2.2) New : Load Only Variational parameters (CATCGMStreamImpl *)->UnderExtendedReplay()  
    *                         (for above in stack ReadInputMultipleRun, operator non null is mandatory)
    *
    *   TESTING :  For sample of ODT validation, you may have a look on 
    *   =========        CGMV5Interoperability.tst\FunctionTests\TestCases\CATGemODT_OnlyMultipleRun.sh
    *
    *   COMMODITIES :  Filter only Replay with multiple (extended) Run
    *   =========           set/export CATCGMReplay=OnlyMultipleRun,all,Home=${MyCATCGMReplayDIR},2
    *                       or interactive debug c:cgmdbg with OnlyMultipleRun label 
    *
    *   INTEGRATION  :  Suggested protocols is to be used with traditionnal methodology
    *   =============     The only change is about the multiple Run() which should be redone in Replay
    *                            Integratio has already be done inside the main 
    *                            HRESULT CATExtCGMReplay::Run(CATCGMOutput& os, int &rc, CATErrorId* oErrorId)
    * -------------------------------------------------------------------------------------------------------
 */
#include "CATMathInline.h"
#include "CATListPV.h"
#include "CATCGMStream.h"
#include "CATCGMStreamControl.h"
#include "CATBoolean.h"
#include "CATDataType.h"


/**
  * -------------------------------------------------------------------------------------------------------
  * CGMReplay / Extended  Run().  Utilities on simlified recovery of legacy
  *     for newcomers on extended Run() protocols
  * -------------------------------------------------------------------------------------------------------
*/

enum CATCGMStreamMultipleRun
{
  CatCGMStreamMultipleRun_Create,
  CatCGMStreamMultipleRun_Update,
  CatCGMStreamMultipleRun_Others
};

/**
  * -------------------------------------------------------------------------------------------------------
  * CGMReplay / Extended  Run().  Meta-Description Helpers fro variational parameters  
  *  with original submission from CATIA Live Shape developpers .
  *    Relimitation du prototype variable d environnement Fictif de la spec "Multi->Run()
  * Cache management on associated Stream
  *    Dirty Transient management proposal for quick and fast implementation
  *    from a root recovery of WriteInput and ::CATLoadOperatorID
  * -------------------------------------------------------------------------------------------------------
*/
struct CATCGMStreamExtendedReplay
{
  CATCGMStreamExtendedReplay() : _Technology(0x01), _Version(1), _Completude(0) 
  {}

  CATCGMStreamExtendedReplay(unsigned char  iTechnology, CATULONG32 iVersion, CATULONG32  iCompletude) 
    : _Technology(iTechnology), _Version(iVersion), _Completude(iCompletude) 
  {}

  unsigned char  _Technology;     // 0x01; Old Technology WriteInput
  CATULONG32     _Version;        //    1; Version depending on Operator 
  CATULONG32     _Completude;     //    0; BietField depending on Operator 
};

 
#include "CATCGMExplicitParameters.h"
 

class CATCGMPad; // R.F.U 
 

#endif
