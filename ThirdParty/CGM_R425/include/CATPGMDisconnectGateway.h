#ifndef CATPGMDisconnectGateway_h_
#define CATPGMDisconnectGateway_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @quickReview DLR6 2019:01:07
 * @quickReview DLR6 2018:07:06
 */

#ifndef NULL
#define NULL 0
#endif

#include "CATGMModelInterfaces.h"
#include "CATDataType.h"

class CATDisconnectCell;
class CATDisconnectEngine;
class CATDisconnectEngineData;
class CATHiddenImplementation;
class CATSkinCell;
class CATSoftwareConfiguration;

class CATDisconnectCellList;


//#define DLR6__DISCO3D_DEBUG_BUILD_EXISTING_CELLS


//-----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATPGMDisconnectGateway
{
public:
  /**
   * Constructor
   */
  CATPGMDisconnectGateway();

  /**
   * Destructor
   */
  virtual ~CATPGMDisconnectGateway();

  /*------------------------------------------------------------------
  Create a new skin cell. The disconnect algorithm will work on the 
  graph of skin cells and connections. 
  ------------------------------------------------------------------ */
  virtual CATSkinCell *AddSkinCell(void *iClientId) = 0;

  /*------------------------------------------------------------------
  Same as previous method but indicating that the skin cell is part 
  of an outermost shell or loop. This is an Optimisation to avoid 
  excessive callbacks: cells declared by AddSkinCell are considered
  to be inside cells declared by AddOuterSkinCell.
  -------------------------------------------------------------------*/
  virtual CATSkinCell *AddOuterSkinCell(void *iClientId) = 0;

  /* -----------------------------------------------------------------
  Add a connection between skin cells. 
  The two arrays iConnectedSkinCells and iOrientationFlags 
  are of dimension iConnectionOrder. 
  
  The meaning of the arguments is, interpreted for each of the 
  two application possibilities:
  
  1) Disconnect of a face 
  
  iConnectedSkinCells: edges that touch at a common vertex  
  iOrientationFlags: for each edge in iConnectedSkinCells,
  does it go in or out of the connection? in other words, if the 
  parametrisation of the edge is AWAY from the connection, the value
  should be FALSE, and if it's TOWARD the connection, the value must
  be TRUE. 
  Warning: you must indicate all open edges (end of edge which joins no
  other edge) by an order-1 connector. 
  
  2) Disconnect of a volume
  
  iConnectedSkinCells: faces that touch at a common edge 
  iOrientationFlags: for each face in iConnectedSkinCells,
  is the parametrisation of the connecting edge for or against 
  the matter-to-the-left convention? In other words, if you move
  along the parametrisation of the connecting edge, is the face 
  interior to the left (TRUE) or is it to the right (FALSE). 
  Warning: you must indicate all open faces (edge of face which joins no
  other face) by an order-1 connector.  
       
  ------------------------------------------------------------------ */
  virtual void AddConnection(
    int iConnectionOrder,
    CATSkinCell **iConnectedSkinCells,
    int *iOrientationFlags) = 0;

  /*------------------------------------------------------------------
  For optimization reasons, the DisconnectEngine doesn't respect the order
  in which the Client has added his SkinCells, during the Disconnect
  operation, which works by injection.
  But, sometimes, (in boolean context for exemple), the client wants to
  optimize the order by himself (to optimize his owned CallBacks)!
  In this case, if he wants the DisconnectEngine to NOT change the SkinCells
  order, he has to "freeze" his owned order by the following method.
  ------------------------------------------------------------------ */
  virtual void FreezeClientSkinCellsOrderForInjection() = 0;

  /*------------------------------------------------------------------
  the 0 value (default value) drives the oldest algorithm with 3 rules (DBN),
  the 1 value allows to switch to the new algorithm, which is optimized
  with only 2 rules (AAD).
  The method SetOptimisationMode() allows the client to change the default value.
  ------------------------------------------------------------------ */
  virtual void SetOptimisationMode(short iClientOptimisationMode) = 0;

  /*------------------------------------------------------------------
  the 0 value (default value) calls no callback when a DisconnectCell is created,
  the 1 value calls a CATDisconnectEngine::DisconnectCellCreationCB with limited
  provided info when a DisconnectCell is created
  the 2 value calls a CATDisconnectEngine::DisconnectCellCreationCB with exhaustive
  provided info when a DisconnectCell is created
  The method SetDiscocellCreationCBRequestLevel() allows the client to change
  the level of information they want.
  ------------------------------------------------------------------ */
  virtual void SetDiscocellCreationCBRequestLevel(short iInfoRequestLevel) = 0;

  /*------------------------------------------------------------------
  the 0 value (default value) calls no callback when a DisconnectCell is created,
  the 1 value calls a CATDisconnectEngine::DisconnectCellCreationCB with limited
  provided info when a DisconnectCell is created
  the 2 value calls a CATDisconnectEngine::DisconnectCellCreationCB with exhaustive
  provided info when a DisconnectCell is created
  The method SetDiscocellCreationCBRequestLevel() allows the client to change
  the level of information they want.
  ------------------------------------------------------------------ */
  virtual short GetDiscocellCreationCBRequestLevel() = 0;

  /*------------------------------------------------------------------
  the 0 value (default value) requests any IsMatterInside callback
  to give a determined result
  the 1 value authorizes an undetermined result from IsMatterInside callback
  under some circumstances
  ------------------------------------------------------------------ */
  virtual void SetAuthorizeUndecidedMatterInside(short iAuthorizeUndecidedMatterInside) = 0;
  virtual short GetAuthorizeUndecidedMatterInside() const = 0;

  /*------------------------------------------------------------------
  Performs the disconnection. 
  Use the methods below to find out the results. 
  ------------------------------------------------------------------ */
  virtual int Disconnect() = 0;


  /* ----------------------------------------------------------------
  // Methode optionnelle a appeler avant Disconnect() :
  // =========================================
  methode permettant de faire une pre-disconnection que
  le client peut appeler s'il le souhaite afin de
  faciliter le travail au disconnectEngine en commencant
  par utiliser des informations supplementaires dont il dispose
  
  Arguments:
      iNbSkinsToIntegrate     - the number of skins provided by the user
      iSkinCellsToIntegrate   - the array of SkinCells of that the user wants to integrate
                                together
                                /!\ Prerequisite : thos skincells msut FULLY DISCONNECT
                                the disconnectCell in which they are located
      ipContainingDiscoCell   - the containing disconnectCell, if the user knows it
  
  ------------------------------------------------------------------*/  
  virtual int ManualPreliminaryIntegration(
      int iNbSkinsToIntegrate,
      CATSkinCell** iSkinCellsToIntegrate,
      CATDisconnectCell* ipContainingDiscoCell = NULL) = 0;


  /* ----------------------------------------------------------------
  Recover the total number of cells created by the disconnection 
  ------------------------------------------------------------------*/
  virtual CATLONG32 GetNumberOfDisconnectCells() const = 0;

  /* ----------------------------------------------------------------
  Recover one of the cells created by the disconnection
  (0 <= iCellIndex < GetNumberOfDisconnectCells()) 
  ------------------------------------------------------------------*/
  virtual CATDisconnectCell *GetDisconnectCell(int iCellIndex) const = 0;

  /* ----------------------------------------------------------------
  Getter for the exterior DisconnectCell
  ------------------------------------------------------------------*/
  virtual CATDisconnectCell * GetExteriorDisconnectCell() const = 0;

  /* ----------------------------------------------------------------
  Recover the number of skin cells bounding a given CATDisconnectCell 

  SPECIAL BEHAVIOR if the CATDisconnectCell is null, the number
  of skin cells returned is the number of dangling cells exterior
  to all of the disconnect cells. 
  ------------------------------------------------------------------*/
  virtual CATLONG32 GetNumberOfSkinCells(CATDisconnectCell *) const = 0;

  /* ----------------------------------------------------------------
  Recover the number of outer skin cells : 
  -> all skin cells which belong only to one external loop, 
     or dangling out of all DisconnectCells
   [ another way to define this kind of skin cells : 
     all skins cells dangling or bounding the infinite DisconnectCell ]
  ------------------------------------------------------------------*/
  virtual CATLONG32 GetNumberOfOuterSkinCells() const = 0; 

  /* ----------------------------------------------------------------
  Recover the skin cells
   
  IF you want to recover the loop or shell structure you
  must impose a filter on the component number returned by reference.  
  0 is for the outer loop or outer shell, 1 to n for the voids 
  (holes or cavities), and -1 for the full cells (cells with matter 
  on both sides). For example, if you want the outer component:
  (outer loop if a face, outer shell if a volume) you should write
         

  CATPGMDisconnectGateway * engine = ... A valid CATPGMDisconnectGateway... 
  CATDisconnectCell * disc = e->GetDisconnectCell(SomeValidIndex); 

  for(int i = 0; i < engine->GetNumberOfSkinCells(disc); i++)
  {
    int componentNumber;    
    CATSkinCell skc = engine->GetSkinCell(disc, i, componentNumber);
    if(componentNumber == 0) 
    {
      ... Code working on elements of outer component ...    
    }
  }
  For the disconnect of a face you are guaranteed to recover the 
  skin cells in the order of the loop or hole (but the values of 
  i might not be adjacent). For the disconnect of a volume the 
  order is of course not significant because no order can be 
  established. 
   
  SPECIAL BEHAVIOR if the CATDisconnectCell is null, the skin cells
  returned are the dangling cells exterior to all disconnect cells. 
  ------------------------------------------------------------------*/
  virtual CATSkinCell *GetSkinCell(
    CATDisconnectCell *cell,
    CATLONG32 iSkinCellIndex,
    CATLONG32 &componentNumber,
    CATLONG32 &isLeft) const = 0;

  /* ----------------------------------------------------------------      
  Idem GetSkinCell for Outer Skin Cells
  -> all skin cells which belong only to one external loop, 
     or dangling out of all DisconnectCells
   [ another way to define this kind of skin cells : 
     all skins cells dangling or bounding the infinite DisconnectCell ]
  oComponentNumber and oIsLeft are relative to the infinite DisconnectCell
  ------------------------------------------------------------------*/
  virtual CATSkinCell * GetOuterSkinCell(CATLONG32   iSkinCellIndex, 
                                         CATLONG32 & oComponentNumber,
                                         CATLONG32 & oIsLeft ) const = 0; 


  /* ----------------------------------------------------------------      
  Retrieve the client id given to the skin cell at creation
  ------------------------------------------------------------------*/
  virtual void *GetSkinCellClientId(CATSkinCell *) const = 0;

  /* ----------------------------------------------------------------
  CALLBACK METHODS
  The user must define a class derived from CATPGMDisconnectGateway
  and give implementations of these methods to perform 
  the task required. Some implementations required, others optional.
  ------------------------------------------------------------------*/
  /* ----------------------------------------------------------------
  Test to see if a Closed Set of SkinCells (= a loop or shell), whose we know
  the Inward Orientations, contains a Connected Manifold Set of other SkinCells

  Arguments:
	     iNbSkinCellsInClosedSet  - the size of the 2 arrays that follow
	     iClosedSetSkinCells      - the array of SkinCells of the Closed Set
       iInwardOrientationIsLeft - the array of the centripetal orientations
                                  of the previous SkinCells
       iNbSkinCellsToLocate     - the size of the array that follows
       iSkinCellsToLocate       - the array of Connected Manifold SkinCells to locate

  Return: TRUE(1) if the ClosedSet contains the SkinCells list, FALSE(0) if it doesn't.
  
  This callback is used when a component of the boundary is not attached
  to the outer boundary of the original cell. Example:
  
  *-----------------*-------------------*      Face F is disconnected
  |                 .                   |      by the dotted edge. 
  |                 F                   |      h2 can be classified
  |  *----*         .      *----*       |      logically because it's 
  |  | h1:|         .  f2  | h2 |       |      connected to the outer
  |  | CB |   f1    .      | OK |       |      boundary of f2.
  |  *----*         .      *----*       |      h1 will be classified using 
  |                 .      |            |      IsSetEnclosingSkinCellsCB
  *-----------------*------*------------*
  
  This callback is similar to IsContainedCB() but allows 2 optimizations :
  the client can choose himself one SkinCell to locate among a list, and the
  Inward Orientations informations can help him logicaly in the search of the location

  If the client doesn't give special implementation for his derived class,
  the default implementation will call the derived implementation of the
  IsContainedCB CallBack !

  ------------------------------------------------------------------*/
  virtual CATLONG32 IsSetEnclosingSkinCellsCB(
    CATLONG32 iNbSkinCellsInClosedSet,
    void **iClosedSetSkinCells,
    short *iInwardOrientationIsLeft,
    CATLONG32 iNbSkinCellsToLocate,
    void **iSkinCellsToLocate) const = 0;

  /* ----------------------------------------------------------------
  Sometimes, the DisconnectEngine has the choice between 2 CallBacks
  (IsMatterInsideCB et IsContainedCB) to locate a domain with respect to another.
  IsContainedCB() is the default CallBack int his case, but the Client can
  specify his preference by the following method.
  */
  virtual void SetClientCBPreference(short iIsMatterInsideCBPrefered = 0) = 0;

  virtual void SetSearchDepth(short iSearchDepth=1) = 0;

  /* ----------------------------------------------------------------
  Overriding this methods gives the client the chance to insert her 
  own data into standard out during a dump of the contents of the 
  CATPGMDisconnectGateway.
  ------------------------------------------------------------------*/
  virtual void DumpCB(void *iClientId) const = 0;
  

#ifdef NOT_USE
  /* ----------------------------------------------------------------
  Creation of a new cell by the disconnexion. This callback is 
  optional, you can recover the new cells also by GetDisconnectCell. 
  ------------------------------------------------------------------*/
  virtual void DisconnectCellCreationCB(CATDisconnectCell *iNewCell) = 0;
#endif // NOT_USE

#ifdef DLR6__DISCO3D_DEBUG_BUILD_EXISTING_CELLS
  virtual int GetIndexOfDiscoCell(CATDisconnectCell* ipDiscoCell) = 0;
  virtual void GetDiscoCellListForBuilding(CATDisconnectCellList* oSubInfiniteDiscoList, CATDisconnectCellList* oOtherDiscoCells) = 0;
#endif  // DLR6__DISCO3D_DEBUG_BUILD_EXISTING_CELLS

  virtual int IsContained(void *innerClientId, int size, void **outerClientIds) = 0;

  /* ----------------------------------------------------------------
  Debug Help for The DisconnectEngine User, only if the Optimisation
  Mode has been required by the SetoptimisationMode(1) method.
  DO NOT CALL IN OFFICIAL CONTEXT !!!!
  ------------------------------------------------------------------*/
  virtual void SetDbgData(
    short iDumpErrorSpecificInfos = 0,
    short iCheckConsistencyBetweenCallbacks = 0,
    short iDumpInclusionDomainsTree = 0) = 0;

  /* ----------------------------------------------------------------
  DO NOT USE (internal use for debug)
  ------------------------------------------------------------------*/
  virtual void IncrementNbIsMatterInsideCB() const = 0;

  virtual void IncrementNbIsContainedCB() const = 0;

  virtual void IncrementNbIsSetEnclosingCB() const = 0;

  virtual void DecrementNbIsSetEnclosingCB() const = 0;

  // Sous-programmes exclusifs de Disconnect() :
  // =========================================
  // ancien algo (3 regles)
  virtual int SimpleRun() = 0;

  // nouvel algo (optimisation du nombre de CallBacks pour la determination du
  // positionnement SkinCell/DisconnectCells et application de 2 regles seulement
  // dans la phase de split)
  virtual int OptimizedRun() = 0;

  virtual void BuildExteriorCell() = 0;

  virtual int IsContained(CATDisconnectCell *outer, CATSkinCell *inner) = 0;

#ifdef NOT_USE
  virtual void DLR6_DumpAllDomains() const = 0;
#endif // NOT_USE
  virtual void DumpDiscocellSkinsCompo(CATDisconnectCell* ipDiscoCell) const = 0;

};

/**
 * @return [out, delete]
 */
ExportedByCATGMModelInterfaces CATPGMDisconnectGateway *CATPGMCreateDisconnectGateway(
  CATDisconnectEngine *engine,
  CATSoftwareConfiguration *iConfig);

#endif /* CATPGMDisconnectGateway_h_ */
