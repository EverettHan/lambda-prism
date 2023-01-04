#ifndef CATTopUntrivialConnectivity_h
#define CATTopUntrivialConnectivity_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2008
/**
      As a status,  main services (or operations)  have been specified and implemented 
         on generic topological configurations mainly based upon at most 2-manifold  solid modeling.

      Generic services as Bounded iterator or some direct method on Topology has already been provided
           with also some customised dedicated services such as GetBorderedFaces, CommonEdges ....

      However on some heterogeouns dimensions  or advanced (but maybe various numerous) possible configurations,  
        Intents may become unclear (not a simple single possible answer) when reusing default elementary services
        either explicit  FILTERING or EXPOSURE 

      So a more explicit (however still trivial) diagnosis management
           is provided to detect and conrol by better approach the management of advanced configurations

      Relatively t a Body , this particular connectivition concerns 
            in simple and with a generic maner as simple as possible,  
            this local context (on demand) of cells with non trivial configuration is provided.

       Here are particular local connectivity configurations which are currently considered for each cell's dimension
             Independantly from any further consideration of unexpected-invalid topological modelisation criteria :

        +------------+-------------------------------------------------------------------------
        |   Face     | bounded more than Shell (internal partition) = internal Face
        +------------+-------------------------------------------------------------------------
        |   Edge     |    bounded more than two loops
        |            | or
        |            |    boundary of internal Face  = internal edge
        +------------+-------------------------------------------------------------------------
        |   Vertex   |    bounded more than one wire  
        |            | or 
        |            |    bounded by at least one internal edge
        |            | or 
        |            |    bounded by a set of non connex faces
        +------------+-------------------------------------------------------------------------


      This generic helpers is proposed as transient cache (short term lifespan) on a current working body    
          for advanced programming coding with best relimitation impact management.

      According to statistic of possible ocurrences and usage,  either explicit  FILTERING or EXPOSURE 
          following tiny extensible characterisation dedicated to GM V5 topological implementation.
      Implementation of this model extension should have less footprint as possible on running implementation.
           (dynamic transient but yet not redondant with an already advanced internal data structure )
*/
//------------------------------------------------------------ 

#include "CATGMModelInterfaces.h"
#include "CATDataType.h"
#include "CATUnicodeString.h"
#include "CATMathInline.h"
#include "CATCGMExclusive.h"

#include "CATBoolean.h"
#include "CATechAttribute.h"
#include "CATListOfCATCells.h"
#include "ListPOfCATTopUntrivialConnectivity.h"
 

class CATBody;
class CATCell;
 
 
 
//------------------------------------------------------------ 
//  Advanced analysis of untrivial connectivity
//------------------------------------------------------------ 
 

/**
*  Specific diagnosis designed as short transaction helper for untrivial cell connectivity management .
*       to be consumed quickly in context of current "active" working frozen body 
*           invalidated by multiple bodies management (smart management) 
*           and  not inside bodies operator (because completion not achieved)
*  each instance represent a particular context of non trivial connectivity relative to a body
*     
*/



class ExportedByCATGMModelInterfaces CATTopUntrivialConnectivity  : public CATCGMExclusive 
{
public :

  //-------------------------------------------------------------------------------------------------------------- 
  //   Detecting  Untrivial Connectivity ....
  //-------------------------------------------------------------------------------------------------------------- 


  /**
  *  IsUntrivialConnectivity , computed (or retrieve cache) untrivial connectivity
  *     Do not forget to resulting oConfiguration->Release()  after usage     
  */
  static CATBoolean  IsUntrivialConnectivity( CATBody *iBody,     CATCell * iCell,  CATTopUntrivialConnectivity * & oConfiguration , CATBoolean   iOptimised  = TRUE)  ;
  
   /**
  *  GetUntrivialConnectivities (computation of all non trivial connectivities)
  *     Heavy complete analysis of Cell of one Body
  *   Do not forget to resulting oUnTrivials->Release()  on each potential result after usage 
  */
  static  CATBoolean GetUntrivialConnectivities( CATBody *iBody,   CATLISTP(CATTopUntrivialConnectivity) & oUnTrivials , CATBoolean   iOptimised  = TRUE )  ;


  //------------------------------------------------------------ 
  //  Analysis of untrivial connectivity
  //------------------------------------------------------------ 

  /**
  * IsInternalCell (full status)
  *     2d : Face bounded by two Shells ("cloisons internes)
  *     1d : Edge   bounded only by "Internal" Face  (deductive)
  *     0d : Vertex bounded only by "Internal" Edge  (deductive)
  */
  virtual CATBoolean IsInternalCell() = 0;


  /**
  * HasBoundedInternalCells (as complementary of previous filtered as GetBorderedFaces)
  *     1d : Edge   bounded list by "Internal" Face  (deductive)
  *     0d : Vertex bounded list by "Internal" Edge  (deductive)
  */
  virtual CATBoolean  HasBoundedInternalCells( CATLISTP(CATCell) & oExpectedCells ) = 0;


    /** Cells' particular configuration ( ADVANCED, CATBoolean   iOptimised = FALSE is mandatory )  */
  virtual CATBoolean  HasDetected(const CATechMeta & iSensor) const  = 0;  


  //-------------------------------------------------------------------------------------------------------------- 
  // misc administration , managing current context 
  //-------------------------------------------------------------------------------------------------------------- 

  /**
  * IsValid (provided with weak reference AddRef()/Release() and diagnosis against LifeCycle of ownerships
  *    As this transient status is volatile  To be used during the transaction of working active body
  */
  virtual CATBoolean IsValid() = 0;


  /**
  * GetCell (...)
  */
  virtual CATCell * GetCell() = 0;

  /**
  * GetBody (...)
  */
  virtual CATBody * GetBody() = 0;
 

  //-------------------------------------------------------------------------------------------------------------- 
  //  PCS particular detection (Reserved)  Detecting  Untrivial Connectivity ....
  //-------------------------------------------------------------------------------------------------------------- 
 
   /**
  *  HasAlreadyHaveDetectedUntrivialConnectivity (pcs relimitation impact on demand , with trigger on nominal default behavior)
  *    (for optimised integration (respect of performance)  of with delayed advanced management of untrivial connectivity)
  *    (see GetBorderedFaces() ...  original request from GenericNaming )
  */
  static  CATBoolean HasAlreadyHaveDetectedUntrivialConnectivity( CATBody *iBody, CATCell * iCell )  ;


  //-------------------------------------------------------------------------------------------------------------- 
  //  GetMeta
  //-------------------------------------------------------------------------------------------------------------- 

    /** @nodoc (to implement with static method variable , type enabler ) */
  virtual  void * GetMeta();

 /** @nodoc (to implement with static method variable , type enabler ) */
  static  void * _GetMeta();

  
  /** @nodoc */
  INLINE CATLONG32   __stdcall  AddRef (void*  iReferencing = NULL);
  /** @nodoc */
  INLINE CATLONG32   __stdcall  Release(void*  iReferencing = NULL);

protected :

  /** @nodoc  */
  CATTopUntrivialConnectivity( CATBody *iBody, CATCell * iCell );

  /** @nodoc  */
  virtual ~CATTopUntrivialConnectivity();


private :

  CATTopUntrivialConnectivity(const CATTopUntrivialConnectivity &iCopy);
  CATTopUntrivialConnectivity& operator=(const CATTopUntrivialConnectivity &iCopy);

};


  /** @nodoc HasDetected  Vertex        ->  VertexNonConnexFaces */
ExportedByCATGMModelInterfaces const CATechMeta    &   CATTopSensor_VertexNonConnexFaces() ;

  /** @nodoc HasDetected  Vertex,Edge   ->  MultipleWires */
ExportedByCATGMModelInterfaces const CATechMeta    &   CATTopSensor_MultipleWires();

  /** @nodoc HasDetected  Edge          ->  MoreThanTwoLoops */
ExportedByCATGMModelInterfaces const CATechMeta    &   CATTopSensor_MoreThanTwoLoops();

  /** @nodoc HasDetected  Face          ->  InternalFace */
ExportedByCATGMModelInterfaces const CATechMeta    &   CATTopSensor_InternalFace();



/** @nodoc */
INLINE CATLONG32   __stdcall  CATTopUntrivialConnectivity::AddRef (void*  iReferencing) { return this->CATCGMExclusive::AddRef(iReferencing); } 
/** @nodoc */
INLINE CATLONG32   __stdcall  CATTopUntrivialConnectivity::Release(void*  iReferencing) { return this->CATCGMExclusive::Release(iReferencing); } 

#endif
