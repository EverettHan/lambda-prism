#ifndef CATDynDraftAngle_h
#define CATDynDraftAngle_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATGMOperatorsInterfaces.h"

#include "ListPOfCATFace.h"
#include "CATMathDef.h"

#include "CATIAV5Level.h"
#include "CATCGMVirtual.h"
#include "CATIACGMLevel.h"

/**
 * Class defining an elementary draft operation.
 * <br>An elementary draft operation defines the angle draft associated with faces to draft.<br>
 * <b>ANGLES ARE TO BE SPECIFIED IN DEGREES.</b>
 * @see CATDynDraftDomain, CATDynDraftRibbon, CATICGMDynDraft
 */
class ExportedByCATGMOperatorsInterfaces CATDynDraftAngle : public CATCGMVirtual
{
 public:  
	 /**
	  * Constructs an elementary draft operation.
		* @param iFacesToDraft
		* The list of pointers to the faces to draft.
		* @param iDraftAngle
		* The common angle value in degrees to associate with <tt>iFacesToDraft</tt>.
		*/
  CATDynDraftAngle (const CATLISTP (CATFace) & iFacesToDraft , const CATAngle & iDraftAngle);

	/**
	  * @nodoc
		*/
  CATDynDraftAngle (const CATLISTP (CATFace) & iFacesToDraft);
  ~CATDynDraftAngle ();

	/**
	 * @nodoc
	 */
  int               TestAngle () const;

	/**
	 * Returns the draft angle value.
	 * @return
	 * The draft angle value in degrees.
	 */
  CATAngle          GetAngle  () const;

#ifdef CATIACGMR215CAA
  /**
	 *VB7 - LiveOperators - multiRun
	 * @return
	 * The draft angle value in degrees.
	 */
  void              SetAngle  (const CATAngle iAngle);
#endif
	/**
	 * Returns the list of faces taken into account in <tt>this</tt> elementary draft operation.
	 * @return
	 * The list of pointers to the faces of <tt>this</tt>.
	 */
  const CATLISTP (CATFace) &GetFaces () const;

  
 private: 
  int                                  _AngleValuated;  
  CATAngle                             _Value;
  CATLISTP (CATFace)                   _Faces;
};


/** 
 * @collection CATLISTP(CATDynDraftAngle)
 * Collection class for pointers to elementary draft operations.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include <CATLISTP_Clean.h>
#include <CATLISTP_PublicInterface.h>
#include <CATLISTP_Declare.h>
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy    ExportedByCATGMOperatorsInterfaces
CATLISTP_DECLARE( CATDynDraftAngle )



#endif
