#ifndef CATDynDraftRibbon_h
#define CATDynDraftRibbon_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATGMOperatorsInterfaces.h"

#include "ListPOfCATFace.h"
#include "CATDynDraftAngle.h"
#include "CATDynDraftParam.h"

#include "CATIAV5Level.h"
#include "CATCGMVirtual.h"
#include "CATIACGMLevel.h" 
class CATBody;
class CATWire;

/**
 * Class defining a draft ribbon.
 * <br>A draft ribbon groups all the connected faces to draft with regards to the same pulling direction and the
 * same neutral element.
 * @see CATDynDraftDomain, CATICGMDynDraft, CATDynDraftAngle
 */
class ExportedByCATGMOperatorsInterfaces CATDynDraftRibbon : public CATCGMVirtual
{
public:
/**
* Constructs a draft ribbon.
* @param iFacesAndAngles
* The list of pointers to the definitions of the elementary draft operations.
		*/
  CATDynDraftRibbon (const CATLISTP (CATDynDraftAngle) & iFacesAndAngles,
                     const CATBoolean iConeEnvelopMode = TRUE);

  /**
   * Constructs a square draft ribbon with a single angle value (other angles can be added afterwards).
   * @param iFaces
   * The listof pointers to the faces of the ribbon to draft.
   * @param iParam
   * The specification of the draft angle value.
   * @param iWireBody
   * The pointer to the wire body along which the angle is defined.
   * @param iWire
   * The pointer to the wire of <tt>iWireBody</tt> to be used.
   */
  CATDynDraftRibbon (const CATLISTP (CATFace) &iFaces,
                     const CATDynDraftParam   *iParam,
                     const CATBody            *iWireBody = NULL,
                     const CATWire            *iWire     = NULL);

  /**
   * Constructs a square draft ribbon without angle values.
   * @param iFaces
   * The listof pointers to the faces of the ribbon to draft.
   * @param iWireBody
   * The pointer to the wire body along which angle(s) can be defined.
   * @param iWire
   * The pointer to the wire of <tt>iWireBody</tt> to be used.
    */
  CATDynDraftRibbon (const CATLISTP (CATFace) &iFaces,
                     const CATBody            *iWireBody = NULL,
                     const CATWire            *iWire     = NULL);


#ifdef CATIACGMV5R21
  /**
   * Constructs a draft ribbon with a single angle value 
   * @param iFacesToDraft
   * The list of pointers to the faces of the ribbon to draft
   * @param iDraftAngle
   * The common angle value to associate with <tt>iFacesToDraft</tt>.
   * @param iWireBody
   * The pointer to the wire body which represents neutral element.
   * @param iWire
   * The pointer to the wire of <tt>iWireBody</tt> which is made up of Neutral edge(s).
   * If it is not specified, first wire in <tt>iWireBody</tt> is considered as Neutral wire  
   * The neutral edge(s) should also be a part of Body to draft. 
   * The neutral edge(s) should be border edges of faces to draft. 
   * The faces to draft should be on same side of neutral edges, w.r.t the pulling direction.
   * @param iConeEnvelopMode
   * Default TRUE. If FALSE draft is created in square mode.
   */
   CATDynDraftRibbon (const CATLISTP(CATFace) &iFacesToDraft,
                      const CATAngle &iDraftAngle,
                      const CATBody *iWireBody,
                      const CATWire *iWire = NULL,
                      const CATBoolean iConeEnvelopMode = TRUE );
#endif

  ~CATDynDraftRibbon ();

  /**
  * Clean Method to avoit FMR in destructor
  */
  void DeleteAngles();
  /**
   * Adds a specification of a draft angle value to define a variable draft.
   * @param iParam
   * The specification of the draft angle value.
   */
  void AddDraftParam (const CATDynDraftParam *iParam);
	/**
	 * Returns the definition of the elementary draft operations.
	 * @returns
	 * The list of pointers to the definitions of the elementary draft operations.
	 */
  const CATLISTP (CATDynDraftAngle) &  GetAngles ()         const;

	/**
	 * Returns the faces of all the elementary draft operations.
	 * @return
	 * The list of pointers to all the faces to draft of <tt>this</tt> draft ribbon.
	 */
  CATLISTP (CATFace)                   GetListOfFaces ()    const;

	/**
	 * Returns the parameters of the draft ribbon.
	 * @return
	 * The list of pointers to all the parameters of <tt>this</tt> draft ribbon.
	 */
  CATLISTP (CATDynDraftParam)          GetListOfParams () const;
	/**
	 * Tests whether all the elementary draft operations have the same draft angle.
	 * @return
	 * The result of the test.
	 * <br><b>Legal values</b>: <tt>1</tt> if all the CATDynDraftAngle elementary operations have the same angle value, 
	 * <tt>0</tt> otherwise.
	 */
  int                                  TestConstantAngle () const;

	/**
	 * Returns the common draft angle value, if any.
	 * @return
	 * The common draft angle value, if <tt>TestConstantAngle</tt> is <tt>TRUE</tt>.
	 */
  CATAngle                             GetConstantAngle ()  const;
  
  /** @nodoc */
  CATBoolean                           IsConeEnvelopMode () const;
  
  /**
  * @nodoc
  * Returns the neutral wire and neutral wire body, if any.
  */
  const CATWire *                      GetNeutralWire ()  const;
  /** @nodoc */
  const CATBody *                      GetNeutralWireBody ()  const;
  
 private:
 
  CATBoolean                   _ConeEnvelopMode;
  
  CATLISTP (CATDynDraftAngle)  _Angle;

  CATLISTP (CATDynDraftParam)  _Params;
  ListPOfCATFace               _Faces;
  const CATBody              * _NeutralWireBody;
  const CATWire              * _NeutralWire;
#ifdef CATIACGMV5R21
  CATDynDraftAngle           * _DraftAngle; 
#endif

  friend class CATGMLiveShapeDraftFaceImpl;
  friend class CATGMLiveShapeSingleDraftFaceImpl;
  friend class CATlsoRibbonContext;
};


/** 
 * @collection CATLISTP(CATDynDraftRibbon)
 * Collection class for pointers to draft ribbons.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include <CATLISTP_Clean.h>
#include <CATLISTP_PublicInterface.h>
#include <CATLISTP_Declare.h>
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy    ExportedByCATGMOperatorsInterfaces
CATLISTP_DECLARE( CATDynDraftRibbon )



#endif
