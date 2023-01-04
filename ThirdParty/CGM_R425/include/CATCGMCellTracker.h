//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Class		:		CATCGMCellTracker
//	Creation	:		27/02/2009
//
//
//	Synopsis	:		Abstract class which allow cell tracking after applying an operator
//					
//	
//
//
//	Authors		:  AAD + KY1 +TCX
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//19/05/2009 KY1 Add method SetTrackMultipleDimension
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CATCGMCellTracker_H
#define CATCGMCellTracker_H


class CATCell;
class CATBody;
class CATCGMJournal;
class CATSoftwareConfiguration;
class CATCGMHashTable;

#include "CATIACGMLevel.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATBody.h"
#include "CATErrorDef.h"
#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"
//#include "CATLISTV_CATBoolean.h"
#include "ListVOfLong.h"
#include "CATCollec.h"

//class CATListOfInt;


class ExportedByCATGMModelInterfaces CATCGMCellTracker
{

public:
  /**
  * Creates a Cell Tracker which allows finding source or image cell of a given cell after
  * the execution of a topological operator  
  * @param iSC
  * The Software Configuration.
  * @return
  * The pointer to the created Cell Tracker. To delete with the usual C++ delete operator after use.
  */
  static CATCGMCellTracker *CATCreateCellTracker(CATSoftwareConfiguration * iSC);

//==========================================================================================================================
// Add an output body and its journal to the CellTracker 
//==========================================================================================================================
public://private:
virtual void AddOutputBody(CATBody *iOutputBody, CATCGMJournal *iJournal) = 0;

//==========================================================================================================================
// Destructor  
//==========================================================================================================================
public:
virtual ~CATCGMCellTracker();


//==========================================================================================================================
// Find the image cells of a cell belonging to an input body  
//==========================================================================================================================
/*
* @iSourceCell	:	a cell belonging to an input body, can be a face, an edge or a vertex; can 
*					not be NULL.
* @iInputBody	:	an input body to which iSourceCell belongs, can not be NULL
* @iOutputBody	:	an output body. oImageCells contains only the image cells that belong to iOutputBody
*				    if NULL, oImageCells contains only the image cells that belong to all output bodies.
* @oImageCells  :	the list of image cells
*
* @pioList_IsCellImageWithInfoJournal	: List Of TRUE/FALSE values. 
*										  If there is no info found then the list will be empty.
*										  If there is at least one info found. Each value indicates if the retrieved cell at the same index of the list @oImageCellList
*											has an info or not.
*
* @pioListOfInfoNumber					: List Of info number. 
*										  If there is no info found then the list will be empty.
*                                         If there is at least one info found. The info at a given index of the list corresponds to the retrieved cell at the same index 
*										  in the list @oImageCellList.has an info or not.
* BECARFULL : 
*    - Refer to the list pioList_IsCellImageWithInfoJournal to know if the retrieved cell has an info or not.
*    - To track info carried by Cells pioList_IsCellImageWithInfoJournal and pioListOfInfoNumber must be not NULL otherwise there is no info tracking
*
*/
public:
#ifdef CATIACGMR417CAA
virtual HRESULT GetImage(CATCell *iSourceCell, CATBody *iInputBody, CATBody *iOutBody, ListPOfCATCell &oImageCellList, CATListOfInt *pioList_IsCellImageWithInfoJournal = NULL, CATListOfLong *pioListOfInfoNumber = NULL) = 0;
#else
virtual HRESULT GetImage(CATCell *iSourceCell, CATBody *iInputBody, CATBody *iOutBody, ListPOfCATCell &oImageCellList) = 0;
#endif

//==========================================================================================================================
// Find the source cells of a cell belonging to an output body  
//==========================================================================================================================
/*
* @iImageCell	:	a cell belonging to an output body, can be a face, an edge or a vertex; can 
*					not be NULL.
* @iInputBody   :	an input body. oSourceCells contains only the source cells that belong to iInputBody
*					if NULL, oSourceCells contains the source cells that belong to all input bodies.
* @iOutput		:	an output body to which iImageCell belongs; can not be NULL. 
* @oSourceCells :	the list of source cells.
*
* @pioList_IsCellSourceWithInfoJournal	: List Of TRUE/FALSE values.
*										  If there is no info found then the list will be empty.
*										  If there is at least one info found. Each value indicates if the retrieved cell at the same index of the list @oSourceCellList
*										  has an info or not.
*
* @pioListOfInfoNumber					: List Of info number. 
*										  If there is no info found then the list will be empty.
*                                         If there is at least one info found. The info at a given index of the list corresponds to the retrieved cell at the same index 
*										  in the list @oSourceCellList.
* BECARFULL : 
*    - Refer to the list pioList_IsCellSourceWithInfoJournal to know if the retrieved cell has an info or not.
*    - To track info carried by Cells pioList_IsCellSourceWithInfoJournal and pioListOfInfoNumber must be not NULL otherwise there is no info tracking
*    - Particular Case : If Cell created from Scratch and wear an Info, then the C.T returtn a ListofCells containing NULL value and return the Info associated 
*      to the Cell in  pioListOfInfoNumber. 
*/
public:
#ifdef CATIACGMR417CAA
virtual HRESULT GetSource(CATCell *iImageCell, CATBody *iInputBody, CATBody *iOutBody, ListPOfCATCell &oSourceCellList, CATListOfInt *pioList_IsCellSourceWithInfoJournal = NULL, CATListOfLong *pioListOfInfoNumber = NULL) = 0;
#else
virtual HRESULT GetSource(CATCell *iImageCell, CATBody *iInputBody, CATBody *iOutBody, ListPOfCATCell &oSourceCellList) = 0;
#endif

//==========================================================================================================================

//==========================================================================================================================
// Enable Multiple Dimension Response: for a given dimension of a cell, the corresponding Source or Image cells 
// could have dimension different from the dimension of the cell.
// By default the behaviour of Cell Tracker is to keep only cells (source or image) which have same dimension as the cell
//==========================================================================================================================
public:
virtual void SetMultiDimensionTrack(CATBoolean iIsMultiDim) = 0;

/**
* Get all geometries referenced in a JournalList, It could be the input geometries or the output geometries
* @param ioReferencedInputCells 
*  Hash table intended  to store all input geometries referenced by the journal.The hash table must be created by the applicant.
* 
* @param ioReferencedOutputCells 
*  Hash table intended  to store all output geometries referenced by the journal.The hash table must be created by the applicant.
* N.B : if you want only retrieve input (output)referenced geometries set the other argument to NULL
*/
public:
  virtual void GetReferencedCellsInJournal(CATCGMHashTable* ioReferencedInputCells,CATCGMHashTable* ioReferencedOutputCells) = 0;

//==========================================================================================================================
// Constructors  
//==========================================================================================================================
protected:
CATCGMCellTracker();

private:
CATCGMCellTracker(const CATCGMCellTracker& CellTracker);

};

#endif
