#ifndef CATDynChamferRibbon_h_
#define CATDynChamferRibbon_h_

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATIACGMLevel.h"
#include "CATGMOperatorsInterfaces.h"
#include "CATDynFilletRibbon.h"
#include "ListPOfCATFace.h"
#include "CATMathDef.h"
#include "ListPOfCATEdge.h"
#include "CATBody.h"
#include "ListPOfCATBody.h"
/**
 * The definition type of the chamfer specifications.
 * <b>ANGLES ARE TO BE SPECIFIED IN DEGREES.</b>
 * <br>Define:
 * <ul>
 * <li><tt>a1</tt>: the angle between the resulting face and the reference face. 
 * <li><tt>a2</tt>: the angle between the resulting face and the other face.
 * <li><tt>d1</tt>: the distance between the edge to remove and the intersection between the resulting face and
 * the reference face.
 * <li><tt>d2</tt>: the distance between the edge to remove and the intersection between the resulting face and
 * the other face.
 * <li><tt>d</tt>: the distance between the intersection points of resulting chamfer face with reference face and 
 * the other face 
 * </ul>
 * @param CATDynd1d2
 * The ribbon is defined with <tt>d1</tt> and <tt>d2</tt>.
 * @param CATDyna1a2
 * The ribbon is defined with <tt>a1</tt> and <tt>a2</tt>. Not implemented yet.
 * @param CATDynd1a1
 * The ribbon is defined with <tt>d1</tt> and <tt>a1</tt>.
 * @param CATDynd1a2
 * The ribbon is defined with <tt>d1</tt> and <tt>a2</tt>. Not implemented yet.
 * @param CATDyna1d2
 * The ribbon is defined with <tt>a1</tt> and <tt>d2</tt>. Not implemented yet.
 * @param CATDynd2a2
 * The ribbon is defined with <tt>d2</tt> and <tt>a2</tt>. Not implemented yet.
 * @param CATDynda1
 * The ribbon is defined with <tt>d</tt> and <tt>a1</tt>.
 * @param CATDynda2
 * Not implemented yet.
 */
enum CATDynTypeChamfer
{
  CATDynd1d2,
  CATDyna1a2,
  CATDynd1a1,
  CATDynd1a2,
  CATDyna1d2,
  CATDynd2a2,
  CATDynda1,
  CATDynda2,
  CATDynhca1,
  CATDynhcd2
};

/**
 * Class defining a chamfer ribbon.
 * <br>A chamfer ribbon is an elementary process of the chamfering operator.
 */
class ExportedByCATGMOperatorsInterfaces CATDynChamferRibbon : public CATDynFilletRibbon
{
public:
	/**
	 * Default constructor.
	 */
  CATDynChamferRibbon();

	/**
	 * Constructs a chamfer ribbon definition.
	 * @param iEdges
	 * The list of the pointers to the edges to chamfer.
	 * @param iSupport
	 * The list of the pointers to the corresponding reference faces.
	 * @param iTypeSpec
	 * The definition type.
	 * @param iLeftValue
	 * The value of the first parameter regarding to the definition mode. Angles are measured in degrees.
	 * @param iRightValue
	 * The value of the second parameter regarding to the definition mode. Angles are measured in degrees.
	 * @param iPropagation
	 * The automatic propagation of the ribbon.
	 * <br><b>Legal values</b>:
	 * <dl><dt><tt>CATEdgePropagAuto</tt></dt><dd>Automatic propagtion in tangency.
	 * <dt><tt>CATEdgePropagManual</tt></dt><dd>No propagtion.
	 * </dl>
	 */
  CATDynChamferRibbon(const CATLISTP(CATEdge)&   iEdges,
                      const CATLISTP(CATFace)&   iSupport,
                      const CATDynTypeChamfer       iTypeSpec,
                      const double            iLeftValue,
                      const double            iRightValue,
                      CATBody::CATPropagationTypePr3      iPropagation=CATBody::CATEdgePropagAuto);
  
  /** @nodoc */
  CATDynChamferRibbon(const CATLISTP(CATEdge) & iEdges,
                      const CATLISTP(CATFace) & iSupport,
                      const CATDynTypeChamfer   iTypeSpec,
                      const CATLISTP(CATEdge) & iHoldEdges,
                      const double              iValue,
                      CATBody::CATPropagationTypePr3      iPropagation = CATBody::CATEdgePropagAuto );

  virtual ~CATDynChamferRibbon();

	/**
	 * Returns the edges to chamfer.
	 * @return
	 * The list of the pointers to the edges to chamfer in <tt>this</tt> ribbon.
	 */
  const CATLISTP(CATEdge)&         GetEdge() const ;

	/**
	 * Returns the corresponding reference faces.
	 * @return
	 * The list of the pointers to the corresponding faces in <tt>this</tt> ribbon.
	 */
  const CATLISTP(CATFace)&         GetSupport() const;

	/**
	 * Returns the definition of the first value.
	 * @return
	 * The value.
	 */
  double                        GetLeftValue() const;
  /**
	 * Set the first value
	 * @param iLeftValue
	 */
  void                          SetLeftValue(const double iLeftValue) ;
	/**
	 * Returns the definition of the second value.
	 * @return
	 * The value.
	 */
  double                        GetRightValue() const;
  	/**
	 * Set the second value
	 * @param iRightValue
	 */
  void                          SetRightValue(const double iRightValue) ;
	/**
	 * Returns the definition type of <tt>this</tt> ribbon.
	 * @return
	 * The definition type.
	 */
  CATDynTypeChamfer                   GetTypeChamfer() const;

	/**
	* Returns the propagation mode.
	* @return
	* The automatic propagation of the ribbon.
	* <br><b>Legal values</b>:
	* <dl><dt><tt>CATEdgePropagAuto</tt></dt><dd>Automatic propagtion in tangency.
	* <dt><tt>CATEdgePropagManual</tt></dt><dd>No propagtion.
	* </dl>
	*/
  CATBody::CATPropagationTypePr3            GetPropagationType() const;

  /** @nodoc */
  virtual void GetSupportBodies(CATLISTP(CATBody) &oSupportBodies) const;

  /** @nodoc */
  const CATLISTP(CATEdge)&         GetHoldEdge() const ;

private:

  virtual const short GetType();
  virtual void  GetInitialShells (CATTopData* iData, CATBody* InputBody, CATLISTP(CATShell) &InitialShells);
  virtual void  UpdateInputs (CATTopData* iTopData, CATCGMJournalList& iJournal, CATBody* InputBody, CATBody* iCreationBody);
  virtual void  Stream  (CATGeoFactory *iFactory, CATCGMStream& os, short iVersion);
  virtual void  UnStream(CATGeoFactory *iFactory, CATCGMStream& os, short iVersion, const double iXScaleFactor = 1.);

  CATLISTP(CATEdge)                  _Edges;
  CATLISTP(CATFace)                  _Support;
  CATLength                          _LeftValue;
  CATLength                          _RightValue;
  CATDynTypeChamfer                  _TypeValues;
  CATBody::CATPropagationTypePr3     _Propagation;
  CATLISTP(CATEdge)                  _HoldEdges;

  friend class CATDynSolidChamferCGM;
  friend class CATGMLiveShapeChamferImpl;
  friend class CATGMLiveShapeSingleChamferImpl;
  friend class CATlsoRibbonContext;
};


/** 
 * @collection CATLISTP(CATDynChamferRibbon)
 * Collection class for pointers to chamfer ribbons.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include <CATLISTP_Clean.h>
#include <CATLISTP_PublicInterface.h>
#include <CATLISTP_Declare.h>
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy    ExportedByCATGMOperatorsInterfaces
CATLISTP_DECLARE( CATDynChamferRibbon )

#endif
