#ifndef CATDynRemoveFaceFilletRibbon_h_
#define CATDynRemoveFaceFilletRibbon_h_

//=============================================================================
// Copyright Dassault Systemes 2006-2014, all rights reserved
//=============================================================================

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include "CATDynFilletRibbon.h"
#include "CATIACGMLevel.h"
#include "CATGMOperatorsInterfaces.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATShell.h"
#include "ListPOfCATBody.h"
#include "CATDynFilletRadius.h"
#include "CATFilletDefine.h"


/**
 * Class defining a tri-tangent fillet ribbon.
 * <br>A ribbon is an elementary process of the filleting operator.
 */
class ExportedByCATGMOperatorsInterfaces CATDynRemoveFaceFilletRibbon : public CATDynFilletRibbon
{
public:
    /**
	 * Default constructor.
	 */
  CATDynRemoveFaceFilletRibbon();

	/**
	 * Constructs a tri-tangent ribbon.
	 * <br>In this case, the radius is automatically defined by the tri-tangency conditions.
	 * @param iRightSupport
	 * The list of pointers to the first faces.
	 * @param iLeftSupport
	 * The list of pointers to the opposite faces.
	 * @param iSupportToRemove
	 * The list of pointers the third suporting faces, that are removed in the operation.
	 */
  CATDynRemoveFaceFilletRibbon(const CATLISTP(CATFace)& iRightSupport,
                               const CATLISTP(CATFace)& iLeftSupport,
                               const CATLISTP(CATFace)& iSupportToRemove);

	/**
	 * Constructs a tri-tangent ribbon.
	 * <br>In this case, the radius is automatically defined by the tri-tangency conditions.
	 * @param iRightBody
	 * The pointer to the body of the first faces.
	 * @param iRightDomain
	 * The pointer to the domain of the first faces.
	 * @param iRightOrientation
	 * The orientation to take into account for the ribbon computation
	 * <br><b>Legal values</b>: <tt>CATOrientationPositive</tt> to take the natural orientation of the shell domain,
	 * <tt>CATOrientationNegative</tt> for the opposite orientation.
	 * @param iRightSupport
	 * The list of pointers to the first faces (belonging to <tt>iRightDomain</tt> and <tt>iRightBody</tt>).
	 * @param iLeftBody
	 * The pointer to the body of the opposite faces.
	 * @param iLeftDomain
	 * The pointer to the domain of the opposite faces.
	 * @param iLeftOrientation
	 * The orientation to take into account for the ribbon computation
	 * <br><b>Legal values</b>: <tt>CATOrientationPositive</tt> to take the natural orientation of the shell domain,
	 * <tt>CATOrientationNegative</tt> for the opposite orientation.
	 * @param iLeftSupport
	 * The list of pointers to the opposite faces (belonging to <tt>iLefttDomain</tt> and <tt>iLeftBody</tt>).
	 * @param iRemoveBody
	 * The pointer to the body of the third supporting faces, that are removed in the operation..
	 * @param iRemoveDomain
	 * The pointer to the domain of the third supporting faces to remove.
	 * @param iRemoveOrientation
	 * The orientation to take into account for the ribbon computation
	 * <br><b>Legal values</b>: <tt>CATOrientationPositive</tt> to take the natural orientation of the shell domain,
	 * <tt>CATOrientationNegative</tt> for the opposite orientation.
	 * @param iRemoveSupport
	 * The list of pointers to the third supporting faces to remove 
	 * (belonging to <tt>iRemoveDomain</tt> and <tt>iRemoveBody</tt>).
	 */
  CATDynRemoveFaceFilletRibbon(CATBody *                           iRightBody,
                               CATDomain *                         iRightDomain,
                               const CATOrientation                iRightOrientation,
                               const CATLISTP(CATFace)&            iRightSupport,
                               CATBody *                           iLeftBody,
                               CATDomain *                         iLeftDomain,
                               const CATOrientation                iLeftOrientation,
                               const CATLISTP(CATFace)&            iLeftSupport,
                               CATBody *                           iRemoveBody,
                               CATDomain *                         iRemoveDomain,
                               const CATOrientation                iRemoveOrientation,
                               const CATLISTP(CATFace)&            iRemoveSupport);
  
  virtual ~CATDynRemoveFaceFilletRibbon();
  
	/**
	 * Returns the first faces of <tt>this</tt> tri-tangent ribbon.
	 * @return
	 * The list of the pointers to the first faces.
	 */ 
  const CATLISTP(CATFace)& GetRightSupport()  const;

	/**
	 * Returns the opposite faces of <tt>this</tt> tri-tangent ribbon.
	 * @return
	 * The list of the pointers to the opposite faces.
	 */ 
  const CATLISTP(CATFace)& GetLeftSupport()   const;

	/**
	 * Returns the third supporting faces (to remove) of <tt>this</tt> tri-tangent ribbon.
	 * @return
	 * The list of the pointers to the third supporting faces to remove.
	 */ 
  const CATLISTP(CATFace)& GetRemoveSupport() const;

	/**
	 * Returns the radius definitions of <tt>this</tt> ribbon.
	 * @return
	 * The list of the radius definitions.
	 */
  const CATLISTP(CATDynFilletRadius)& GetRadii() const;

	/**
	 * Returns the body of the opposite faces of <tt>this</tt> tri-tangent ribbon.
	 * @return
	 * The pointer to the body of the opposite faces.
	 */ 
  CATBody *                     GetLeftBody () const;

	/**
	 * Returns the body of the first faces of <tt>this</tt> tri-tangent ribbon.
	 * @return
	 * The pointer to the body of the first faces.
	 */ 
  CATBody *                     GetRightBody () const;

	/**
	 * Returns the body of the third supporting faces (to remove) of <tt>this</tt> tri-tangent ribbon.
	 * @return
	 * The pointer to the body of the third supporting faces.
	 */ 
  CATBody *                     GetRemoveBody () const;

	/**
	 * Returns the domain of the opposite faces of <tt>this</tt> tri-tangent ribbon.
	 * @return
	 * The pointer to the domain of the opposite faces.
	 */ 
  CATDomain *                   GetLeftDomain () const;

	/**
	 * Returns the domain of the first faces of <tt>this</tt> tri-tangent ribbon.
	 * @return
	 * The pointer to the domain of the first faces.
	 */ 
  CATDomain *                   GetRightDomain () const;

	/**
	 * Returns the domain of the third supporting faces (to remove) of <tt>this</tt> tri-tangent ribbon.
	 * @return
	 * The pointer to the domain of the third supporting faces.
	 */ 
  CATDomain *                   GetRemoveDomain () const;

	/**
	 * Returns the orientation of the shell domain of the opposite faces to take into account 
	 * for <tt>this</tt> tri-tangent ribbon.
	 * @return
	 * The relative orientation.
	 */
  const CATOrientation          GetLeftOrientation () const;

	/**
	 * Returns the orientation of the shell domain of the first faces to take into account 
	 * for <tt>this</tt> tri-tangent ribbon.
	 * @return
	 * The relative orientation.
	 */
  const CATOrientation          GetRightOrientation () const;

	/**
	 * Returns the orientation of the shell domain of the third supporting faces to take into account 
	 * for <tt>this</tt> tri-tangent ribbon.
	 * @return
	 * The relative orientation.
	 */
  const CATOrientation          GetRemoveOrientation () const;

  /** 
   * Defines the multi-ribbon behaviour for the tri-tangent ribbon.
   * <br>If used, multiple tri-tangent ribbons will be performed in one step and possible self-intersection areas of the ribbons will be solved.
   * @param iMode
   * The mode that should be applied to the tri-tangent ribbon.
	 * <br><b>Legal values</b>: <tt>CATDynDefaultNoMultiSolutionAllowed</tt> no multi-ribbon is performed - default value
	 * <tt>CATDynMultiSolutionAllowed</tt> multi-ribbon is performed.
   */
  virtual void SetRemoveFaceInitMode(CATDynFilletFaceFaceInitMode iMode);

   /** @nodoc*/
private: 

  virtual const short GetType();
  virtual void  GetInitialShells (CATTopData* iData, CATBody* InputBody, CATLISTP(CATShell) &InitialShells);
  virtual void  GetSupportBodies(CATLISTP(CATBody) &oSupportBodies) const;
  virtual void  UpdateInputs (CATTopData* iTopData, CATCGMJournalList& iJournal, CATBody* InputBody, CATBody* iCreationBody, CATCGMJournalList * iOffJournal = 0);

  virtual void Dump( CATCGMOutput& os ) ;
  virtual void Stream  (CATGeoFactory *iFactory, CATCGMStream& os, short iVersion);
  virtual void UnStream(CATGeoFactory *iFactory, CATCGMStream& os, short iVersion, const double iXScaleFactor = 1.);

  // Methods for Chain : change the input body y a new one
  virtual void UpdateWithNewBody (CATBody* iOldBody, CATBody* iNewBody);
  CATUnicodeString       GetTypeName() ;
  virtual CATBoolean             IsA(CATDynFilletRibbonType  iRibbonType);  

  // Attribut and method for the multi-ribbon mode
  CATDynFilletFaceFaceInitMode _RemoveFaceInitMode; 
  virtual const CATDynFilletFaceFaceInitMode GetRemoveFaceInitMode();

  CATLISTP(CATFace)            _right_support;
  CATLISTP(CATFace)            _left_support;
  CATLISTP(CATFace)            _remove_support;
  CATBody *                    _right_body;
  CATBody *                    _left_body;
  CATBody *                    _remove_body;
  CATDomain *                  _right_domain;
  CATDomain *                  _left_domain;
  CATDomain *                  _remove_domain;
  CATOrientation               _right_orientation;
  CATOrientation               _left_orientation;
  CATOrientation               _remove_orientation;
  CATLISTP(CATDynFilletRadius) _radii;

  friend class CATDynSolidFilletCGM;
};

/** 
 * @collection CATLISTP(CATDynRemoveFaceFilletRibbon)
 * Collection class for pointers to fillet ribbons.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include <CATLISTP_Clean.h>
#include <CATLISTP_PublicInterface.h>
#include <CATLISTP_Declare.h>
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy    ExportedByCATGMOperatorsInterfaces
CATLISTP_DECLARE( CATDynRemoveFaceFilletRibbon )

#endif
