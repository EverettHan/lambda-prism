#ifndef CATDynFaceFaceFilletRibbon_h_
#define CATDynFaceFaceFilletRibbon_h_

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
#include "CATMath.h"
#include "CATBody.h"
#include "CATFilletDefine.h" 


/**
 * Class defining a fillet ribbon between two faces.
 * <br>A ribbon is an elementary process of the filleting operator.
 */
class ExportedByCATGMOperatorsInterfaces CATDynFaceFaceFilletRibbon : public CATDynFilletRibbon
{
public:
    /**
    * Default constructor.
    */
  CATDynFaceFaceFilletRibbon();
   /**
    * Constructs a ribbon between two faces.
    * @param iRightSupport
    * The list of pointers to the first faces.
    * @param iLeftSupport
    * The list of pointers to the opposite faces.
    * @param iRadii
    * The list of radius definitions.
    */
  CATDynFaceFaceFilletRibbon(const CATLISTP(CATFace)           & iLeftSupport, 
                             const CATLISTP(CATFace)           & iRightSupport,
                             const CATLISTP(CATDynFilletRadius)& iRadii,
                                   CATDynEdgeCrossing            iDefaultBehaviour,
                             const CATLISTP(CATEdge)           & iSpecialEdges );

   /**
    * Constructs a ribbon between two faces.
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
    * @param iRadii
    * The list of radius definitions.
    */
  CATDynFaceFaceFilletRibbon(      CATBody                     * iLeftBody,
                                   CATDomain                   * iLeftDomain,
                             const CATOrientation                iLeftOrientation,
                             const CATLISTP(CATFace)           & iLeftSupport,
                                   CATBody                     * iRightBody,
                                   CATDomain                   * iRightDomain,
                             const CATOrientation                iRightOrientation,
                             const CATLISTP(CATFace)           & iRightSupport,
                             const CATLISTP(CATDynFilletRadius)& iRadii );

  /** @nodoc */
  CATDynFaceFaceFilletRibbon(      CATBody                     * iLeftBody,
                                   CATDomain                   * iLeftDomain,
                             const CATOrientation                iLeftOrientation,
                             const CATLISTP(CATFace)           & iLeftSupport,
                                   CATBody                     * iRightBody,
                                   CATDomain                   * iRightDomain,
                             const CATOrientation                iRightOrientation,
                             const CATLISTP(CATFace)           & iRightSupport,
                             const CATLISTP(CATDynFilletRadius)& iRadii,
                                   CATDynEdgeCrossing            iDefaultBehaviour,
                             const CATLISTP(CATEdge)           & iSpecialEdges );

  /** @nodoc */
  CATDynFaceFaceFilletRibbon(      CATBody                     * iHoldBody,
                                   CATDomain                   * iHoldDomain,
                             const CATOrientation                iHoldOrientation,
                                   CATBody                     * iLeftBody,
                                   CATDomain                   * iLeftDomain,
                             const CATOrientation                iLeftOrientation,
                             const CATLISTP(CATFace)           & iLeftSupport,
                                   CATBody                     * iRightBody,
                                   CATDomain                   * iRightDomain,
                             const CATOrientation                iRightOrientation,
                             const CATLISTP(CATFace)           & iRightSupport,
                                   CATBody                     * iSpineBody,
                             const CATLISTP(CATEdge)           & iSpecialEdges = NULL);

   /**
    * Constructs a ribbon between two faces with a spine and different external radius law for both supports
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
   * @param iSpineBody
    * The pointer to the spine object.
   * @param iLeftMappingLaw
    * The pointer to the mapping law corresponding to the left body
   * @param iRightMappingLaw
    * The pointer to the mapping law corresponding to the right body
   * @param iLeftDistLaw
    * The pointer to the distance law corresponding to the left body
   * @param iRightDistLaw
    * The pointer to the distance law corresponding to the right body
   */
  CATDynFaceFaceFilletRibbon(      CATBody                     * iLeftBody,
                                   CATDomain                   * iLeftDomain,
                             const CATOrientation                iLeftOrientation,
                             const CATLISTP(CATFace)           & iLeftSupport,
                                   CATBody                     * iRightBody,
                                   CATDomain                   * iRightDomain,
                             const CATOrientation                iRightOrientation,
                             const CATLISTP(CATFace)           & iRightSupport,
                                   CATBody                     * iSpineBody,
                                   CATCompositeLaw             * iLeftMappingLaw,
                                   CATCompositeLaw             * iRightMappingLaw,
                                   CATCompositeLaw             * iLeftDistLaw,
                                   CATCompositeLaw             * iRightDistLaw);
  /**
    * Constructs a ribbon between two faces  with a spine and same external radius law for both supports
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
   * @param iSpineBody
    * The pointer to the spine object.
   * @param iMappingLaw
    * The pointer to the mapping law
   * @param iDistanceLaw
    * The pointer to the distance law.
   */
  CATDynFaceFaceFilletRibbon(      CATBody                     * iLeftBody,
                                   CATDomain                   * iLeftDomain,
                             const CATOrientation                iLeftOrientation,
                             const CATLISTP(CATFace)           & iLeftSupport,
                                   CATBody                     * iRightBody,
                                   CATDomain                   * iRightDomain,
                             const CATOrientation                iRightOrientation,
                             const CATLISTP(CATFace)           & iRightSupport,
                                   CATBody                     * iSpineBody,
                                   CATCompositeLaw             * iMappingLaw,
                                   CATCompositeLaw             * iDistanceLaw);

  virtual ~CATDynFaceFaceFilletRibbon();
  
  /**
    * Returns the first faces of <tt>this</tt> ribbon.
    * @return
    * The list of the pointers to the first faces.
    */ 
  const CATLISTP(CATFace)&            GetRightSupport() const ;

   /**
    * Returns the opposite faces of <tt>this</tt> ribbon.
    * @return
    * The list of the pointers to the opposite faces.
    */ 
  const CATLISTP(CATFace)&            GetLeftSupport() const ;

   /**
    * Returns the radius definitions of <tt>this</tt> ribbon.
    * @return
    * The list of the radius definitions.
    */
  const CATLISTP(CATDynFilletRadius)& GetRadii() const;

   /**
    * Returns the body of the opposite faces of <tt>this</tt> ribbon.
    * @return
    * The pointer to the body of the opposite faces.
    */ 
  CATBody *                     GetLeftBody () const;

   /**
    * Returns the body of the first faces of <tt>this</tt> ribbon.
    * @return
    * The pointer to the body of the first faces.
    */ 
  CATBody *                     GetRightBody () const;

   /**
    * Returns the domain of the opposite faces of <tt>this</tt> ribbon.
    * @return
    * The pointer to the domain of the opposite faces.
    */ 
  CATDomain *                   GetLeftDomain () const;

   /**
    * Returns the domain of the first faces of <tt>this</tt> ribbon.
    * @return
    * The pointer to the domain of the first faces.
    */ 
  CATDomain *                   GetRightDomain () const;

   /**
    * Returns the orientation of the shell domain of the opposite faces to take into account 
    * for <tt>this</tt> ribbon.
    * @return
    * The relative orientation.
    */
  const CATOrientation          GetLeftOrientation () const;

   /**
    * Returns the orientation of the shell domain of the first faces to take into account 
    * for <tt>this</tt> ribbon.
    * @return
    * The relative orientation.
    */
  const CATOrientation          GetRightOrientation () const;

  /** 
   * Defines the multi-ribbon behaviour for the face/face ribbon.
   * <br>If used, multiple face/face ribbons will be performed in one step and possible self-intersection areas of the ribbons will be solved.
   * @param iMode
   * The mode that should be applied to the face/face ribbon.
    * <br><b>Legal values</b>: <tt>CATDynDefaultNoMultiSolutionAllowed</tt> no multi-ribbon is performed - default value
    * <tt>CATDynMultiSolutionAllowed</tt> multi-ribbon is performed.
   */
  virtual void SetFaceFaceInitMode(CATDynFilletFaceFaceInitMode iMode);

   /** @nodoc*/
  void AddToDelete(CATDynFilletRadius* iRadius);
   /** @nodoc*/
  void AddToDelete(const CATLISTP(CATDynFilletRadius)& iRadii);
   /** @nodoc*/
  CATDynFaceFaceFilletRibbon(const CATDynFaceFaceFilletRibbon& iToCopy); 
   /** @nodoc*/
  CATDynFaceFaceFilletRibbon& operator=(const CATDynFaceFaceFilletRibbon& iToCopy);  

private:

                void                DisableLawSmoothing(CATFilletLawId iLawId, CATBoolean iIsLawSmoothingDisabled);
                CATDynEdgeCrossing  GetDefaultBehaviour() const;
  virtual       void                GetSupportBodies   (CATLISTP(CATBody) &oSupportBodies) const;
  virtual const short               GetType();
  virtual       void                GetInitialShells   (CATTopData* iTopData,
                                                        CATBody* InputBody, CATLISTP(CATShell) &InitialShells);
  virtual       void                UpdateInputs       (CATTopData* iTopData,
                                                        CATCGMJournalList& iJournal,
                                                        CATBody* InputBody, CATBody* iCreationBody, CATCGMJournalList * iOffJournal = 0);
  virtual const CATDynFilletFaceFaceInitMode GetFaceFaceInitMode();

  virtual       void                Dump               ( CATCGMOutput& os ) ;
  virtual       void                Stream             (CATGeoFactory *iFactory, CATCGMStream& os, short iVersion);
  virtual       void                UnStream           (CATGeoFactory *iFactory, CATCGMStream& os, short iVersion, const double iXScaleFactor = 1.);

  // Methods for Chain : change the input body with a new one
  virtual       void                UpdateWithNewBody  (CATBody* iOldBody, CATBody* iNewBody);
                CATUnicodeString    GetTypeName        () ;
  virtual       CATBoolean          IsA                (CATDynFilletRibbonType  iRibbonType);  

  CATLISTP(CATFace)            _right_support;
  CATLISTP(CATFace)            _left_support;
  CATBody *                    _right_body;
  CATBody *                    _left_body;
  CATDomain *                  _right_domain;
  CATDomain *                  _left_domain;
  CATOrientation               _right_orientation;
  CATOrientation               _left_orientation;
  CATLISTP(CATDynFilletRadius) _radii;
  CATDynEdgeCrossing           _default_behaviour;
  CATDynFilletFaceFaceInitMode _FaceFaceInitMode; 
  CATLISTP(CATDynFilletRadius) _RadiiToDelete;

  friend class CATDynSolidFilletCGM;
};

/** 
 * @collection CATLISTP(CATDynFaceFaceFilletRibbon)
 * Collection class for pointers to fillet ribbons.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include <CATLISTP_Clean.h>
#include <CATLISTP_PublicInterface.h>
#include <CATLISTP_Declare.h>
#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy    ExportedByCATGMOperatorsInterfaces
CATLISTP_DECLARE(CATDynFaceFaceFilletRibbon)

#endif
