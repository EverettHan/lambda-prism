// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATDisconnectEngine
// This class implements the algorithm to disconnect a face or a volume
// into connected regions. 
//
//=============================================================================
// Architecture and usage Notes:
//
// CATDisconnectEngine isolates the disconnect algorithm as described in
// the document "disconnect3d:proposition" by the inventor of the 
// method, Jean-Francois Rameau. 
// Other people having worked on the method and its first implementation
// in the CGM cell-complex prototype are Claire Fritz-Humblot, 
// Remy Ronfard, and Jean-Michel Houdoin (my apologies if I've left
// somebody out). 
// If you want to know more about the CGM cell-complex modeler prototype
// (1989-1992) read the documents "Prototype Topologique" and "Nouvelle
// Topologie" also by Jean-Francois Rameau.  
//
// The interface principle is to make a copy of the graph of the cell
// to be disconnected. This graph will be formed of faces attached by edges
// for the split of a volume, or of edges attached by vertices for the 
// split of a face. In general the cells that form the skin are called
// skin cells and the cells that attach these skin cells are called 
// connector cells. The highest level cells are the CATDisconnectCells
// which represent the disconnected zones (faces or volumes). 
// There is a hidden CATDisconnectCell inside the CATDisconnectEngine 
// which represents the ambient space into which the skins are introduced.
// The client will never see this cell but it's essential because it
// generates all the CATDisconnectCells that follow. 
//  
// Each cell in the graph contains a return pointer to the client 
// object. This way, when the disconnection algorithm needs extra 
// information it call make a callback to the client using the client
// pointer so the client loses no time finding the corresponding data.
//
//
// ------------------------------------------------------------
// IMPLEMENTATION NOTES
// the type CATLONG32 is used for integers because I've been told 
// it's the most portable type (problems with int if using idl). 
// ------------------------------------------------------------
//
//=============================================================================
// Jan 97 Creation (port from project Goliath in DSD/SRT) 
// Original code written May-October 96
// This file derived from original interface file CATTopology.h
//
// Modifications :
//
// DPS - June 2000 :
// The new method SetOptimisationMode() allows the client to choose 
// between two algorithms :
// the 0 value (default value) drives the oldest algorithm with 3 rules (DBN),
// the 1 value allows to switch to the new algorithm, which is optimised
// with only 2 rules (AAD).
//
// DPS - June 2000 :
// The CallBack Method IsMatterInsideCB() becomes pure virtual
//
// DPS - July 2000 :
// New CallBack IsSetEnclosingSkinCellsCB() allows to optimize
// the CallBack IsContainedCB(), but only if the client gives a special
// implementation in his owned derived class.
//
// DLR6 - July 2018 :
// Add several new methods, all used in a new daughter class : CATDisco3DEngine
// that is called by CATDisco3DCompatibleOp
//    * DisconnectCellCreationCB
//          optionnal callback that will only be called
//          if _discocellCreationCBRequestLevel has been set to 1 or 2
//          (two versions exist with two different types of argument list)
//    * SetDiscocellCreationCBRequestLevel
//          public method to change the discocellCreation callback request level
//          stored in CATDisconnectEngineData (default 0)
//    * ReviewCandidateDisconnectCellsCB
//          optionnal callback to allow the client to reduce the number of
//          possible candidate DisconnectCell containing a list of skincells.
//          Can be usefull if the caller or daughter class has some information
//          that they couldn't give to CATDisconnectEngine
//    * DumpDiscocellSkinsCompo
//          Method that can called by / on daughter classes of CATDisconnectEngine
//          to dump the skin composition of a DisconnectCell.
//          This method is necessary because CATDisconnectGateway can access
//          CATDisconnectCell but the callers of CATDisconnectEngine
//          will not be able to access it (unless they are in NewTopologicalObjects/DIS.m)
//    * ManualPreliminaryIntegration
//          public method that allows the client to integrate together a group
//          of skincells that they already know is connected among themselves
//          and fully disconnects a previously created DisconnectCell.
//          For example of use, see CATDisco3DCompatibleOp::ManuallyAddVolumes
//    * GetExteriorDisconnectCell()
//          protected method to allow the daughter classes to know the exterior
//          DisconenctCell
//
// DLR6 - July 2018 :
// Add a new dump method, by default not compiled (for coverage)
// (can be used for debug if define activated)
//    * DumpAllDiscocellsCompo
//          Method that dumps the compo of all DisconnectCells in the Engine
//          (calls DumpDiscocellSkinsCompo on those cells)
//
// DLR6 - January 2019 :
// Add a getter method (for being able to get the value without knowing the engine data)
//    * GetDiscocellCreationCBRequestLevel
//          public method to get the discocellCreation callback request level
//          stored in CATDisconnectEngineData (default 0)
//
// DLR6 - April 2022 :
//  Addition get / set method for new attribute _AuthorizeUndecidedMatterInside
//  of CATDisconnectEngineData
//=============================================================================

#ifndef CATDisconnectEngine_H
#define CATDisconnectEngine_H

// Forward declarations

class CATSkinCell; 
class CATHiddenImplementation;
class CATDisconnectCell;
class CATDisconnectCellList;
class CATSoftwareConfiguration;
class CATPGMDisconnectGateway;

#include "CATGMModelInterfaces.h"
#include "CATDataType.h"
#include "CATCollec.h" // for the define of NULL on Unix system
#include "CATCGMVirtual.h"
#include "CATSysTSDataType.h" // for the define of NULL on Unix system


//#define DLR6__DISCO3D_DEBUG_BUILD_EXISTING_CELLS


//-----------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATDisconnectEngine: public CATCGMVirtual
{
   
  public:
 
  /*------------------------------------------------------------------
  constructor, destructor
  -------------------------------------------------------------------*/
  CATDisconnectEngine(CATSoftwareConfiguration * iConfig=NULL);    
  virtual ~CATDisconnectEngine();
  
  /*------------------------------------------------------------------
  Create a new skin cell. The disconnect algorithm will work on the 
  graph of skin cells and connections. 
  ------------------------------------------------------------------ */
  CATSkinCell * AddSkinCell(void * iClientId);

  /*------------------------------------------------------------------
  Same as previous method but indicating that the skin cell is part 
  of an outermost shell or loop. This is an Optimisation to avoid 
  excessive callbacks: cells declared by AddSkinCell are considered
  to be inside cells declared by AddOuterSkinCell.
  -------------------------------------------------------------------*/
  CATSkinCell * AddOuterSkinCell(void * iClientId);

  /* -----------------------------------------------------------------
  Add a connection between skin cells. 
  The two arrays iConnectedSkinCells and iOrientationFlags 
  are of dimension iConnectionOrder. 
  
  The meaning of the arguments is, interpreted for each of the 
  two application possibilities:
  
  1) CATGMModelInterfacesof a face 
  
  iConnectedSkinCells: edges that touch at a common vertex  
  iOrientationFlags: for each edge in iConnectedSkinCells,
  does it go in or out of the connection? in other words, if the 
  parametrisation of the edge is AWAY from the connection, the value
  should be FALSE, and if it's TOWARD the connection, the value must
  be TRUE. 
  Warning: you must indicate all open edges (end of edge which joins no
  other edge) by an order-1 connector. 
  
  2) CATGMModelInterfacesof a volume
  
  iConnectedSkinCells: faces that touch at a common edge 
  iOrientationFlags: for each face in iConnectedSkinCells,
  is the parametrisation of the connecting edge for or against 
  the matter-to-the-left convention? In other words, if you move
  along the parametrisation of the connecting edge, is the face 
  interior to the left (TRUE) or is it to the right (FALSE). 
  Warning: you must indicate all open faces (edge of face which joins no
  other face) by an order-1 connector.  
       
  ------------------------------------------------------------------ */

  void AddConnection(int iConnectionOrder, 
		                 CATSkinCell ** iConnectedSkinCells,
		                 int * iOrientationFlags);


  /*------------------------------------------------------------------
  For optimization reasons, the DisconnectEngine doesn't respect the order
  in which the Client has added his SkinCells, during the Disconnect
  operation, which works by injection.
  But, sometimes, (in boolean context for exemple), the client wants to
  optimize the order by himself (to optimize his owned CallBacks)!
  In this case, if he wants the DisconnectEngine to NOT change the SkinCells
  order, he has to "freeze" his owned order by the following method.
  ------------------------------------------------------------------ */
  void FreezeClientSkinCellsOrderForInjection();

  /*------------------------------------------------------------------
  the 0 value (default value) drives the oldest algorithm with 3 rules (DBN),
  the 1 value allows to switch to the new algorithm, which is optimized
  with only 2 rules (AAD).
  The method SetOptimisationMode() allows the client to change the default value.
  ------------------------------------------------------------------ */
  void SetOptimisationMode(short iClientOptimisationMode);

  /*------------------------------------------------------------------
  the 0 value (default value) calls no callback when a DisconnectCell is created,
  the 1 value calls a CATDisconnectEngine::DisconnectCellCreationCB with limited
  provided info when a DisconnectCell is created
  the 2 value calls a CATDisconnectEngine::DisconnectCellCreationCB with exhaustive
  provided info when a DisconnectCell is created
  The method SetDiscocellCreationCBRequestLevel() allows the client to change
  the level of information they want.
  ------------------------------------------------------------------ */
  void SetDiscocellCreationCBRequestLevel(short iInfoRequestLevel);

  /*------------------------------------------------------------------
  the 0 value (default value) calls no callback when a DisconnectCell is created,
  the 1 value calls a CATDisconnectEngine::DisconnectCellCreationCB with limited
  provided info when a DisconnectCell is created
  the 2 value calls a CATDisconnectEngine::DisconnectCellCreationCB with exhaustive
  provided info when a DisconnectCell is created
  The method GetDiscocellCreationCBRequestLevel() allows the client to know / check
  the level of information that is recorded in the engine.
  ------------------------------------------------------------------ */
  short GetDiscocellCreationCBRequestLevel();

  /*------------------------------------------------------------------
  the 0 value (default value) requests any IsMatterInside callback
  to give a determined result
  the 1 value authorizes an undetermined result from IsMatterInside callback
  under some circumstances
  ------------------------------------------------------------------ */
  void SetAuthorizeUndecidedMatterInside(short iAuthorizeUndecidedMatterInside);
  short GetAuthorizeUndecidedMatterInside() const;

  /*------------------------------------------------------------------
  Performs the disconnection. 
  Use the methods below to find out the results. 
  ------------------------------------------------------------------ */
  int Disconnect();

  /* ----------------------------------------------------------------
  // Methode a appeler avant Disconnect() :
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
  int ManualPreliminaryIntegration(
      int iNbSkinsToIntegrate,
      CATSkinCell** iSkinCellsToIntegrate,
      CATDisconnectCell* ipContainingDiscoCell = NULL);

  /* ----------------------------------------------------------------
  Recover the total number of cells created by the disconnection 
  ------------------------------------------------------------------*/

  CATLONG32 GetNumberOfDisconnectCells() const;

  /* ----------------------------------------------------------------
  Recover one of the cells created by the disconnection
  (0 <= iCellIndex < GetNumberOfDisconnectCells()) 
  ------------------------------------------------------------------*/

  CATDisconnectCell * GetDisconnectCell(int iCellIndex) const; 

  /* ----------------------------------------------------------------
  Recover the number of skin cells bounding a given CATDisconnectCell 

  SPECIAL BEHAVIOR if the CATDisconnectCell is null, the number
  of skin cells returned is the number of dangling cells exterior
  to all of the disconnect cells. 
  ------------------------------------------------------------------*/

  CATLONG32 GetNumberOfSkinCells(CATDisconnectCell *) const; 
     

  /* ----------------------------------------------------------------
  Recover the number of outer skin cells : 
  -> all skin cells which belong only to one external loop, 
     or dangling out of all DisconnectCells
   [ another way to define this kind of skin cells : 
     all skins cells dangling or bounding the infinite DisconnectCell ]
  ------------------------------------------------------------------*/

  CATLONG32 GetNumberOfOuterSkinCells() const; 


  /* ----------------------------------------------------------------
  Recover the skin cells
   
  IF you want to recover the loop or shell structure you
  must impose a filter on the component number returned by reference.  
  0 is for the outer loop or outer shell, 1 to n for the voids 
  (holes or cavities), and -1 for the full cells (cells with matter 
  on both sides). For example, if you want the outer component:
  (outer loop if a face, outer shell if a volume) you should write
         

  CATDisconnectEngine * engine = ... A valid CATDisconnectEngine... 
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
  
  CATSkinCell * GetSkinCell(CATDisconnectCell * cell,
			                      CATLONG32   iSkinCellIndex, 
			                      CATLONG32 & oComponentNumber,
                            CATLONG32 & oIsLeft // See WARNING above
                            ) const; 


  /* ----------------------------------------------------------------      
  Idem GetSkinCell for Outer Skin Cells
  -> all skin cells which belong only to one external loop, 
     or dangling out of all DisconnectCells
   [ another way to define this kind of skin cells : 
     all skins cells dangling or bounding the infinite DisconnectCell ]
  oComponentNumber and oIsLeft are relative to the infinite DisconnectCell
  ------------------------------------------------------------------*/
  CATSkinCell * GetOuterSkinCell(CATLONG32   iSkinCellIndex, 
                                 CATLONG32 & oComponentNumber,
                                 CATLONG32 & oIsLeft ) const; 
   

  /* ----------------------------------------------------------------      
  Retrieve the client id given to the skin cell at creation
  ------------------------------------------------------------------*/ 
  void * GetSkinCellClientId(CATSkinCell *) const; 
        
  /* ----------------------------------------------------------------
  CALLBACK METHODS
  The user must define a class derived from CATDisconnectEngine
  and give implementations of these methods to perform 
  the task required. Some implementations required, others optional.
  ------------------------------------------------------------------*/ 
 
  /* ----------------------------------------------------------------
  Test to see if a skin cell is contained within a loop or shell
  of other skin cells.  
  Arguments: iSkinCellToTest - the skin cell to be tested
	     iNumContainerSkinCells - the size of the array that follows
	     iContainerSkinCells - the array of container cells 
  Return:  true if contained, false if not contained.
  
  This callback is used when a component of the boundary is not attached
  to the outer boundary of the original cell. Example:
  
  *-----------------*-------------------*      Face F is disconnected
  |                 .                   |      by the dotted edge. 
  |                 F                   |      h2 can be classified
  |  *----*         .      *----*       |      logically because it's 
  |  | h1:|         .  f2  | h2 |       |      connected to the outer
  |  | CB |   f1    .      | OK |       |      boundary of f2.
  |  *----*         .      *----*       |      h1 will be classified using 
  |                 .      |            |      IsContainedCB
  *-----------------*------*------------*
  
  ------------------------------------------------------------------*/  
 
  virtual CATLONG32 IsContainedCB(void * iSkinCellToTest, 
			                       CATLONG32 iNumContainerSkinCells,
			                       void ** iContainerSkinCells) const = 0;


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
  virtual CATLONG32 IsSetEnclosingSkinCellsCB(CATLONG32    iNbSkinCellsInClosedSet,
                                         void ** iClosedSetSkinCells,
                                         short * iInwardOrientationIsLeft,
                                         CATLONG32    iNbSkinCellsToLocate,
                                         void ** iSkinCellsToLocate) const;
 
  
  /* ----------------------------------------------------------------
  Find out if a loop or shell of skin cells defines a void (return FALSE)
  or a region of matter (return TRUE) .  
  The orientations given by the user during connector creation permits 
  the skin cells to be correctly oriented relative to each other. However,
  there are cases when the overall orientation of a loop or shell which 
  is not connected to the rest of the boundary is not determined 
  by this information alone. This callback gets the missing information. 
   
  Arguments: iNumContainerSkinCells - the size of the arrays that follow
	     iContainerSkinCells - array of skin cells 
	     iMatterToLeftFlags         - array of orientations for each skin cell.
	       
  Return: TRUE if loop or shell is OK, FALSE if it's reversed. 
  
  Notes:  
  1) Meaning of the iMatterToLeftFlags: TRUE means for an edge that the matter is
  to the left respect to the parametrisation direction. For a face, it means
  that the normal points outwards from the matter. FALSE is the opposite. 
  
  2) For the case of a loop of more than 2 edges, the order of 
  edges given in the array is guaranteed to be "correct" relative 
  to the orientation of the skin cells (if the edge is LEFT, the 
  loop runs the same way as the parametrisation, and if it's RIGHT 
  the loop is contrary to the parametrisation). For the case of a 
  shell, the ordering of the array has no meaning. 

  ------------------------------------------------------------------*/    
  virtual CATLONG32 IsMatterInsideCB(CATLONG32 iNumContainerSkinCells,
				                        void ** iContainerSkinCells,
				                        int   * iMatterToLeftFlags) const = 0;

  
  
  /* ----------------------------------------------------------------
  Callback to reduce the number of DisconnectCell candidates in which
  some skincells would be contained
  The goal of this callback is to cross-reference information known by
  the engine with information known by the caller (for example, CATDisco3DCompatibleOp)
  If the caller has no info to add, then it just needs to not overrid this method

  Arguments:
       iNbSkinCellsToLocate     - the size of the array that follows
       iSkinCellsToLocate       - the array of Connected Manifold SkinCells to locate
       iCandidateDiscoCellList  - according to the engine, the possible DisconnectCells
                                  that could contain the skins to locate

  ------------------------------------------------------------------*/  
  virtual void ReviewCandidateDisconnectCellsCB(
    CATLONG32 iNbSkinCellsToLocate,
    void **iSkinCellsToLocate,
    CATDisconnectCellList& ioCandidateDiscoCellList) const;
  
  
  /* ----------------------------------------------------------------
  Callback to signal the creation of a DisconnectCell.
  Note :  this callback will only be called if :
          _discocellCreationCBRequestLevel == 1

  Arguments:
       pNewDiscoCell                  - the newly created DisconnectCell
       pSplittedDiscoCell             - the DisconnectCell which was splitted by
                                        the creation of pNewDiscoCell
       iListSkcChangeDiscolink        - the list of skincells whose link with
                                        pSplittedDiscoCell has to be changed to
                                        a link with pNewDiscoCell

  ------------------------------------------------------------------*/  
  virtual void DisconnectCellCreationCB(
    CATDisconnectCell* pNewDiscoCell, CATDisconnectCell* pSplittedDiscoCell,
    const CATListPV& iListSkcChangeDiscolink) const;
  
  
  /* ----------------------------------------------------------------
  Callback to signal the creation of a DisconnectCell.
  Note :  this callback will only be called if :
          _discocellCreationCBRequestLevel == 2

  Arguments:
       pNewDiscoCell                          - the newly created DisconnectCell
       iListSkcLeftConnectedToNewDisc         - the skincells whose left link must now
                                                refer to pNewDiscoCell
       iListSkcRightConnectedToNewDisc        - the skincells whose right link must now
                                                refer to pNewDiscoCell
       pSplittedDiscoCell                     - the DisconnectCell which was splitted by
                                                the creation of pNewDiscoCell
       iListSkcLeftConnectedToSplittedDisc    - the skincells whose left link must now
                                                refer to pSplittedDiscoCell
       iListSkcRightConnectedToSplittedDisc   - the skincells whose right link must now
                                                refer to pSplittedDiscoCell

  ------------------------------------------------------------------*/  
  virtual void DisconnectCellCreationCB(
    CATDisconnectCell* pNewDiscoCell,
    const CATListPV& iListSkcLeftConnectedToNewDisc,
    const CATListPV& iListSkcRightConnectedToNewDisc,
    CATDisconnectCell* pSplittedDiscoCell,
    const CATListPV& iListSkcLeftConnectedToSplittedDisc,
    const CATListPV& iListSkcRightConnectedToSplittedDisc) const;


  /* ----------------------------------------------------------------
  Sometimes, the DisconnectEngine has the choice between 2 CallBacks
  (IsMatterInsideCB et IsContainedCB) to locate a domain with respect to another.
  IsContainedCB() is the default CallBack int his case, but the Client can
  specify his preference by the following method.
  */
  void SetClientCBPreference(short iIsMatterInsideCBPrefered=0);

  void SetSearchDepth(short iSearchDepth=1);

  /* ----------------------------------------------------------------
  Overriding this methods gives the client the chance to insert her 
  own data into standard out during a dump of the contents of the 
  CATDisconnectEngine.
  ------------------------------------------------------------------*/ 
  virtual void DumpCB(void * iClientId) const;  

#ifdef NOT_USE
  void DLR6_DumpAllDomains() const;
#endif // NOT_USE
  // Method that can called by / on daughter classes of CATDisconnectEngine
  // that know a class CATDisconnectCell exists but cannot
  // access either it nor CATDisconnectGateway
  void DumpDiscocellSkinsCompo(CATDisconnectCell* ipDiscoCell) const;
  
#ifdef NOT_USE
  void DumpAllDiscocellsCompo() const;
#endif // NOT_USE
  
  /* ----------------------------------------------------------------
  Creation of a new cell by the disconnection. This callback is 
  optional, you can recover the new cells also by GetDisconnectCell. 
  ------------------------------------------------------------------*/
#ifdef NOT_USE
    virtual void DisconnectCellCreationCB(CATDisconnectCell * iNewCell); 
#endif

#ifdef DLR6__DISCO3D_DEBUG_BUILD_EXISTING_CELLS
    int GetIndexOfDiscoCell(CATDisconnectCell* ipDiscoCell);
    void GetDiscoCellListForBuilding(CATDisconnectCellList* oSubInfiniteDiscoList, CATDisconnectCellList* oOtherDiscoCells);
#endif  // DLR6__DISCO3D_DEBUG_BUILD_EXISTING_CELLS

  enum Side     { UnknownSide=-1, Right=0, Left=1, Full=2 };
  enum Position { UnknownPosition=-1, Outside=0, Inside=1, OnBorder=2 };

  int IsContained(void * innerClientId, int size, void ** outerClientIds);
  
  /* ----------------------------------------------------------------
  Debug Help for The DisconnectEngine User, only if the Optimisation
  Mode has been required by the SetoptimisationMode(1) method.
  DO NOT CALL IN OFFICIAL CONTEXT !!!!
  ------------------------------------------------------------------*/  
  void SetDbgData(short iDumpErrorSpecificInfos=0,
                  short iCheckConsistencyBetweenCallbacks=0,
                  short iDumpInclusionDomainsTree=0);
  
  /* ----------------------------------------------------------------
  DO NOT USE (internal use for debug)
  ------------------------------------------------------------------*/  
  void IncrementNbIsMatterInsideCB() const;
  void IncrementNbIsContainedCB() const;
  void IncrementNbIsSetEnclosingCB() const;
  void DecrementNbIsSetEnclosingCB() const;

  protected:  
    /* ----------------------------------------------------------------
    Getter for the exterior DisconnectCell
    ------------------------------------------------------------------*/
    CATDisconnectCell* GetExteriorDisconnectCell() const;

  private:
    
    // Sous-programmes exclusifs de Disconnect() :
    // =========================================
    // ancien algo (3 regles)
#ifdef NOT_USE
    int SimpleRun();
#endif

    // nouvel algo (optimisation du nombre de CallBacks pour la determination du
    // positionnement SkinCell/DisconnectCells et application de 2 regles seulement
    // dans la phase de split)
    int OptimizedRun();

#ifdef NOT_USE
    void BuildExteriorCell();
    int IsContained(CATDisconnectCell * outer, CATSkinCell * inner);
#endif
    
    // Note: super safe data! even if you did something horrible 
    // to try to access the private data, you couldn't do anything
    // with it because you don't have the right header file!
    // (and don't you try and get it you dirty little rat)  
    
    CATPGMDisconnectGateway * _Gateway;
    
    
    // Methods that you should not be able to use on a 
    // CATDisconnectEngine : constructor, Copy constructor, operator =
    
    CATDisconnectEngine(const CATDisconnectEngine & iInstance);   
    void operator = (const CATDisconnectEngine & iInstance);
    
};

#endif
