#ifndef CATDynDraftDomain_h
#define CATDynDraftDomain_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 


#include "CATGMOperatorsInterfaces.h"
#include "CATDynDraftRibbon.h"
#include "CATMathDirection.h"
#include "ListPOfCATEdge.h"
#ifdef CATIACGMR217CAA
#include "CATTopDefine.h"
#include "ListPOfCATBody.h"
#include "CATListOfInt.h"
#endif

#include "CATIAV5Level.h"
#include "CATCGMVirtual.h"

class CATGeometry;
class CATBody;
class CATShell;
class CATSurface;
/**
 * The type of the draft domain.
 * @param CATDynDraftDomainAdd
 * Not yet implemented.
 * @param CATDynDraftDomainRemove
 * Not yet implemented.
 * @param CATDynDraftDomainReflect
 * Reflect line draft : the neutral curve is defined by a reflect line computation. In this case, matter is
 * only either added, or removed.
 * @param CATDynDraftDomainNeutral
 * The neutral element is explicitely given.
 * @param CATDynDraftDomainReflectKeepEdge
 * Not yet implemented.
 */
enum CATDynDraftDomainType
{
  CATDynDraftDomainAdd,
  CATDynDraftDomainRemove,
  CATDynDraftDomainReflect,
  CATDynDraftDomainNeutral,
  CATDynDraftDomainReflectKeepEdge
};


/**
 * Class defining a draft domain.
 * <br>A draft domain groups all the faces to draft with regards to the same pulling direction.
 * @see CATICGMDynDraft, CATDynDraftRibbon, CATDynDraftAngle
 */
class ExportedByCATGMOperatorsInterfaces  CATDynDraftDomain : public CATCGMVirtual
{
  public:
 
/**
 * Constructs a draft domain.
 * @param iPullingDirection
 * The pulling direction.
 * @param iType
 * The type of the draft operation.
 * @param iNeutral
 * The pointer to the neutral body.
 * To be provided when <tt>iType=CATDynDraftDomainNeutral</tt>.
 * @param iRibbons
 * The list of pointers to the CATDynDraftRibbon objects that contain the faces to draft with <tt>iPullingDirection</tt>.
 */
  CATDynDraftDomain ( CATMathDirection&            iPullingDirection,
		      const CATDynDraftDomainType  iType,
                      const CATBody*               iNeutral,
                      CATLISTP(CATDynDraftRibbon)& iRibbons);
/**
 * Constructs a draft domain.
 * @param iPullingDirection
 * The pulling direction.
 * @param iType
 * The type of the draft operation.
 * @param iNeutral
 * The pointer to the neutral face.
 * To be provided when <tt>iType=CATDynDraftDomainNeutral</tt>.
 * @param iRibbons
 * The list of pointers to the CATDynDraftRibbon objects that contain the faces to draft with <tt>iPullingDirection</tt>.
 */
  CATDynDraftDomain ( CATMathDirection&            iPullingDirection,
                      const CATDynDraftDomainType  iType,
                      const CATFace*               iNeutral,
		      CATLISTP(CATDynDraftRibbon)& iRibbons);
/**
 * @deprecated V5R15
 * Use the constructor whose third argument is a neutral element of type CATFace or
 * else use the constructor whose third argument is a neutral element of type CATBody.
 * Constructs a draft domain.
 * @param iPullingDirection
 * The pulling direction.
 * @param iFaces
 * The list of pointers to the faces to draft with <tt>iPullingDirection</tt>.
 * @param iType
 * The type of the draft operation.
 * @param iNeutral
 * The pointer to the neutral element. This element can be a CATSurface, a CATFace or a CATShell.
 * To be provided when <tt>iType=CATDynDraftDomainNeutral</tt>.
 */
  CATDynDraftDomain ( CATMathDirection& iPullingDirection,
		              CATLISTP(CATDynDraftRibbon)& iFaces,
		              const CATDynDraftDomainType   iType,
		              const CATGeometry* iNeutral);

/**
 * @nodoc
 * Constructs a draft domain without a pulling direction in case of DrivingDriven BothSides Draft.
 */
  CATDynDraftDomain (CATLISTP(CATDynDraftRibbon)& iFaces,
                     const CATDynDraftDomainType   iType,
		     const CATGeometry* iNeutral);
  
  ~CATDynDraftDomain ();

/**
 * Retrieves the pulling direction associated with <tt>this</tt> draft domain.
 * @param ioPullingDirection
 * The pulling direction.
 * @return
 * <tt>TRUE</tt> if the pulling direction is defined in <tt>this</tt> CATDynDraftDomain , <tt>FALSE</tt> otherwise.
 */
  CATBoolean GetPullingDirection (CATMathDirection& ioPullingDirection) const;

/**
 * Returns the ribbons associated with <tt>this</tt> draft domain.
 * <br> A draft ribbon is a set of connected faces.
 * @return
 * The list of pointers to draft ribbons.
 */
  const CATLISTP (CATDynDraftRibbon) & GetRibbons () const;

	/**
	 * Returns the operation draft type.
	 * @return
	 * The operation draft type.
	 */
  CATDynDraftDomainType                GetDomainType () const;

	/**
	 * Returns the neutral element.
	 * @return
	 * The pointer to the neutral element. This element can be a CATSurface, a CATFace or a CATShell.
	 */
  const CATGeometry *                  GetNeutral () const;

#ifdef CATIACGMR217CAA

  /**
   * @nodoc
   */
  void AddPartingElement (CATBody           *iPartingElement,
                          CATOrientation     iPartingOrientation = CATOrientationUnknown,
                          CATBoolean         iIsPartingUntil     = FALSE) ;
  /**
   * @nodoc
   */
  void AddLimitingElement (CATBody           *iLimitingElement,
                           CATOrientation     iLimitingOrientation = CATOrientationUnknown,
                           CATBoolean         iIsLimitingUntil = FALSE) ;

 /**
   * @nodoc
   */
  void GetPartingElement (CATBody           *&oPartingElement,
                          CATOrientation     &oPartingOrientation,
                          CATBoolean         &oIsPartingUntil) const;
  /**
   * @nodoc
   */
  void GetLimitingElements (CATLISTP(CATBody)  &oLimitingElements,
                            CATListOfInt       &oLimitingOrientation,
                            CATBoolean         &oIsLimitingUntil) const;

#endif
	/**
     * @nodoc
	 * Deprecated.
	 * Defines the neutral surface associated with <tt>this</tt> draft domain.
	 * @param iSurface
	 * The pointer to the neutral surface. 
	 */
  void SetNeutral  (CATSurface        * iSurface  );

	/**
     * @nodoc
	 * Deprecated.
	 * Defines the neutral body associated with <tt>this</tt> draft domain.
	 * @param iBody
	 * The pointer to the neutral body. 
	 * @param iShell
	 * The pointer to the domain of <tt>iBody</tt> to take into account for the neutral element.
	 */
  void SetNeutral  (CATBody           * iBody,
                    CATShell          * iShell    );

	/**
     * @nodoc
	 * Not yet implemented.
	 * @paran iKeepEdges
	 * The list of pointers to the edges ....
	 */
  void AddKeepEdges(CATLISTP(CATEdge) & iKeepEdges);
 
	/**
     * @nodoc
	* Not yet implemented.
	*/
  void GetKeepEdges     (CATLISTP(CATEdge) *& oKeepEdges) const;

	/**
     * @nodoc
	 * Deprecated.
	 * Retrieves the neutral surface associated with <tt>this</tt> draft domain.
	 * @param oSurface
	 * The pointer to the neutral surface. This surface was associated with the <tt>SetNeutral</tt> method. It is not
	 * deleted at the domain deletion.
	 */
  void GetNeutralSurface(CATSurface        *& oSurface  ) const;

	/**
     * @nodoc
	 * Deprecated.
	 * Retrieves the neutral body associated with <tt>this</tt> draft domain.
	 * @param oBody
	 * The pointer to the neutral body. This body was associated with the <tt>SetNeutral</tt> method. It is not
	 * deleted at the domain deletion.
	 * @param oShell
	 * The pointer to the shell defining of <tt>oBody</tt> defining the neutral element.
	 */
  void GetNeutralBody   (CATBody           *& oBody,
                         CATShell          *& oShell    ) const;

  private:  
  CATMathDirection              _PullingDirection;
  CATBoolean                    _PullingDirectionIsSet;
  CATLISTP (CATDynDraftRibbon)  _Ribbon;
  CATDynDraftDomainType         _DraftDomainType;
  const CATGeometry            *_Neutral;
  CATSurface     * _NeutralSurface;
  CATShell       * _NeutralShell;
  CATBody        * _NeutralBody;
  ListPOfCATEdge * _KeepEdges;

#ifdef CATIACGMR217CAA
  CATLISTP(CATBody) _LimitingBodies;
  CATListOfInt      _LimitingOri;
  CATBody         * _PartingBody;
  int  			        _PartingOrientation;
  CATBoolean        _PartingUntil;
  CATBoolean        _LimitingUntil;
#endif
};


/** 
 * @collection CATLISTP(CATDynDraftDomain)
 * Collection class for pointers to draft domains.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include <CATLISTP_Clean.h>
#include <CATLISTP_PublicInterface.h>
#include <CATLISTP_Declare.h>
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy    ExportedByCATGMOperatorsInterfaces
CATLISTP_DECLARE( CATDynDraftDomain )


#endif
