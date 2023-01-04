#ifndef CATDynEdgeFilletRibbon_h_
#define CATDynEdgeFilletRibbon_h_

//=============================================================================
// Copyright Dassault Systemes 2006-2011, all rights reserved
//=============================================================================

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATDynFilletRibbon.h"
#include "CATIACGMLevel.h"
#include "CATGMOperatorsInterfaces.h"
#include "CATDynFilletRadius.h"
#include "CATBody.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATShell.h"
#include "ListPOfCATBody.h"
#include "CATFilletDefine.h"

/**
 * Class defining a fillet ribbon along an edge.
 * <br>A ribbon is an elementary process of the filleting operator.
 */
class ExportedByCATGMOperatorsInterfaces CATDynEdgeFilletRibbon : public CATDynFilletRibbon
{
public:
	/**
	 * Default constructor.
	 */
  CATDynEdgeFilletRibbon();
  
	/**
	 * Constructs a ribbon along an edge.
	 * @param iSupport
	 * The list of the pointers to the edges to fillet.
	 * @param iRadii
	 * The list of the radius definitions. There can be several radius definitions for each edge, in case
	 * of variable radius operation.
	 * @param iPropagation
	 * The automatic propagation of the ribbon.
	 * <br><b>Legal values</b>:
	 * <dl><dt><tt>CATEdgePropagAuto</tt></dt><dd>Automatic propagation in tangency.
	 * <dt><tt>CATEdgePropagStopOnCorner</tt></dt><dd>Propagation in tangency but on corner.
	 * <dt><tt>CATEdgePropagManual</tt></dt><dd>No propagation.
	 * </dl>
	 * @param iSpecialEdges
	 * The list of the pointers to the kept (or rolling) edges.
	 * @param iDefaultBehaviour
	 * Not yet implemented.
	 */
  CATDynEdgeFilletRibbon(const CATLISTP(CATEdge)&            iSupport,
                         const CATLISTP(CATDynFilletRadius)& iRadii,
                         CATBody::CATPropagationTypePr3      iPropagation=CATBody::CATEdgePropagAuto,
                         const CATLISTP(CATEdge)&            iSpecialEdges=NULL,
                         CATDynEdgeCrossing                  iDefaultBehaviour=CATDynRolling);
  virtual ~CATDynEdgeFilletRibbon();

/**
 * Returns the input list of the edges defining <tt>this</tt> ribbon.
 * @return
 * The list of the pointers to the edges.
 */
  const CATLISTP(CATEdge)&            GetSupport() const ;

/**
 * Returns the radius definitions of <tt>this</tt> ribbon.
 * @return
 * The list of pointers to the radius definitions.
 */
  const CATLISTP(CATDynFilletRadius)& GetRadii() const;

	/**
	 * Returns whether <tt>this</tt> ribbon is of variable radius.
	 * <br>This directly returns the input of the <tt>SetVariable</tt> method, and does not enquire the
	 * <tt>CATDynFilletRadius</tt> associated with <tt>this</tt> ribbon
	 */
  CATBoolean IsVariable() const;

	/**
	* Returns the propagation mode.
	* @return
	* The automatic propagation of the ribbon.
	* <br><b>Legal values</b>:
	* <dl><dt><tt>CATEdgePropagAuto</tt></dt><dd>Automatic propagation in tangency.
	* <dt><tt>CATEdgePropagStopOnCorner</tt></dt><dd>Propagation in tangency but on corner.
	* <dt><tt>CATEdgePropagManual</tt></dt><dd>No propagation.
	* </dl>
	*/
  CATBody::CATPropagationTypePr3      GetPropagationType() const;

	/**
	 * Defines that <tt>this</tt> ribbon is of variable radius.
	 */
  void                                SetVariable();

   /**
   * Defines the optional spine of <tt>this</tt> ribbon.
   * <br>If used, the spine defines the center of the circle or of the sphere. Moreover,
   * if the CATFilletCircleTool option is used, the plane of the circle is normal
   * to the spine.
   * @param iSpine
   * The pointer to the body only containing one wire. 
   */
  void                                SetSpine(CATBody * iSpine);

   /** @nodoc*/
  void SetSupport(const CATLISTP(CATEdge)& iEdges);

   /** @nodoc*/
  void AddToDelete(CATDynFilletRadius* iRadius);
   /** @nodoc*/
  void AddToDelete(const CATLISTP(CATDynFilletRadius)& iRadii);
   /** @nodoc*/
  CATDynEdgeFilletRibbon(const CATDynEdgeFilletRibbon& iToCopy); 
   /** @nodoc*/
  CATDynEdgeFilletRibbon& operator=(const CATDynEdgeFilletRibbon& iToCopy);  

  
private:

  CATDynEdgeCrossing GetDefaultBehaviour() const;
  virtual void GetSupportBodies(CATLISTP(CATBody) &oSupportBodies) const;
  virtual const short GetType();
  virtual void  GetInitialShells (CATTopData* iData, CATBody* InputBody, CATLISTP(CATShell) &InitialShells);
  virtual void  UpdateInputs (CATTopData* iTopData, CATCGMJournalList& iJournal, CATBody* InputBody, CATBody* iCreationBody, CATCGMJournalList * iOffJournal = 0);
  virtual void  UpdateInputs (const CATLISTP(CATEdge) & iInitialEdges, CATLISTP(CATEdge) & iNewEdges);

  virtual void Dump( CATCGMOutput& os ) ;
  virtual void Stream  (CATGeoFactory *iFactory, CATCGMStream& os, short iVersion);
  virtual void UnStream(CATGeoFactory *iFactory, CATCGMStream& os, short iVersion, const double iXScaleFactor = 1.);

  CATLISTP(CATEdge)                _support;
  CATLISTP(CATDynFilletRadius)     _radii;
  CATDynEdgeCrossing               _default_behaviour;
  int                              _VariableRadius;
  CATBody::CATPropagationTypePr3   _Propagation;
  CATLISTP(CATDynFilletRadius)     _RadiiToDelete;

  // Methods for Chain : change the input body y a new one
  virtual void UpdateWithNewBody (CATBody* iOldBody, CATBody* iNewBody);
  CATUnicodeString       GetTypeName() ;
  virtual CATBoolean             IsA(CATDynFilletRibbonType  iRibbonType);  

  friend class CATDynSolidFilletCGM;
  friend class CATCGMFilletUnit;
  friend class CATGMLiveShapeSingleFilletImpl;
};


/** 
 * @collection CATLISTP(CATDynEdgeFilletRibbon)
 * Collection class for pointers to fillet ribbons.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include <CATLISTP_Clean.h>
#include <CATLISTP_PublicInterface.h>
#include <CATLISTP_Declare.h>
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy    ExportedByCATGMOperatorsInterfaces
CATLISTP_DECLARE( CATDynEdgeFilletRibbon )

#endif
