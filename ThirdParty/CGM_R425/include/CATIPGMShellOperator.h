#ifndef CATIPGMShellOperator_h_
#define CATIPGMShellOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2008

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATMathDef.h"
#include "CATCollec.h"
#include "CATSubdIntersectingFunction.h"

class CATBody;
class CATCGMJournalItem;
class CATCGMJournalList;
class CATFace;
class CATOpThick;
class CATShlXFacAttrib;
class CATTopData;
class CAThkPilot;
class CAThkShellScenario;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMShellOperator;

class ExportedByCATGMOperatorsInterfaces CATIPGMShellOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMShellOperator();

  // remise a jour des valeurs d'offset
  virtual void SetInternalDefaultOffset(CATLength iInternalOffsetValue) = 0;

  virtual void SetExternalDefaultOffset(CATLength iExternalOffsetValue) = 0;

  // Ajout de faces dans la liste privee de faces d'ouverture _OpenFaceList
  virtual void AppendOpening(const CATLISTP(CATFace) &iOpenFaces) = 0;

  // Ajout de la liste des faces d'ouverture propagee sur le body initial
  // quand on fait un regularisation et que l'option ConstantThickness est off
  // (ie booleen avec le body initial)
  virtual void AppendUnregularizedOpening(
    const CATLISTP(CATFace) &iUnregularizedOpenFaces) = 0;

  // Ajout d'une liste de faces a offsets speciaux
  // dans le tableau prive de listes _SpecialFaceListPtr
  // et enregistrement de ces offsets dans les tableaux _SpecialOffsetPtr[]
  virtual void AppendSpecialOffset(
    const CATLISTP(CATFace) &iSpecOffsetFaces,
    CATLength iInternSpecialOffsetValue,
    CATLength iExternSpecialOffsetValue) = 0;

  // Fonction de filtre des intersections booleennes de faces pour un passage
  // par pointeur sur fonction, en remplacement des anciens attributs
  static CATSubdIntersectionType FacesIntersectionType(
    CATFace *iFace1,
    CATFace *iFace2);

  // Execution de l'operation Shell (RunOperator ne doit servir qu'en mode
  // CGMReplay)
  virtual int Run() = 0;

  // Recuperation du Body initial 
  virtual CATBody *GetInitialBody() = 0;

  // body non regularise pour faire le booleen avec le vrai body initial
  // quand l'option ConstantThickness est off dans l'operateur CATIPGMShellOperatorPlus
  // avec regularisation.
  virtual void SetUnregularizedBody(CATBody *iUnregularizedBody) = 0;

  virtual CATBody *GetUnregularizedBody() = 0;

  /**
 * @nodoc
 * @param iFacesToRemove
 * @param iExternalThick (0/1)
 * 
 */
  virtual void SetMandatoryFacesToRemove(
    const CATLISTP(CATFace) &iFacesToRemove,
    short iExternalThick) = 0;

  virtual void GetOpenFaceListAfterPropag(CATLISTP(CATFace) &oOpenFaces) = 0;

  /**
 * @nodoc
 * @param oTrickyFaces
 * @param iExternalThick (0/1)
 * 
 */
  virtual void GetTrickyFaces(
    CATLISTP(CATFace) &oTrickyFaces,
    short iExternalThick,
    short iMixRegulDiagForbidden = 0) = 0;

  /**
 * @nodoc
 * @param oFacesToIgnore 
 * @param iExternalThick (0/1)
 * 
 */
  virtual void GetFacesToIgnore(CATLISTP(CATFace) &oFacesToIgnore, short iExternalThick) = 0;

  /**
 * @nodoc
 * @param oFacesToRegularise
 * @param oDiag
 * <br><b>Legal values:</b>
 * <dl><dt>0</dt><dd>Regularisation not required [forbidden output value]
 * <dt>1</dt><dd>Optimization required for local curvature problem
 * <dt>2</dt><dd>Optimization required for singular point
 * <dt>3</dt><dd>Optimization required for extrapolation failure
 * </dl>
 * @param iExternalThick (0/1)
 * 
 */
  virtual void GetFacesToRegularise(
    CATLISTP(CATFace) &oFacesToRegularise,
    CATListOfInt &oDiag,
    short iExternalThick) = 0;

  /**
  * @nodoc
  * @param oReverseMatterOutputFaces 
  * 
  */
  virtual void GetReverseMatterOutputFaces(CATLISTP(CATFace) &oReverseMatterOutputFaces) = 0;

  /**
  * @nodoc
  * @param oNotInverseRazorBladeFaces 
  * 
  */
  virtual void GetNotInverseRazorBladeFaces(CATLISTP(CATFace) &oNotInverseRazorBladeFaces) = 0;

  /**
  * @nodoc
  * @param oNotInverseRazorBladeFaces 
  * 
  */
  virtual void GetInitReverseMatterFaces(CATLISTP(CATFace) &oInitReverseMatterFaces) = 0;

  /**
  * Defines if procedural Offset surfaces must be approximated and
  * replaced by NurbsSurface
	* @param iApproxOffsetMode
	* <br><b>Legal values:</b>
  * <dl><dt>0</dt><dd>Approximation not required
  * <dt>1</dt><dd>Approximation required in C1 mode
  * <dt>2</dt><dd>Approximation required in C2 mode
  * @param iPostProRequired
  * <br><b>Legal values:</b>
  * <dl><dt>0</dt><dd>Approximation required during Offset algorithm
  * <dt>1</dt><dd>Approximation required after Offset algorithm
  * </dl>
  */
  virtual void SetApproxOffsetMode(short iApproxOffsetMode, short iPostProRequired = 1) = 0;

  /**
  * Defines the tolerance for C1 approximation 
	* @param iTolC1
  * </dl>
  */
  virtual void SetToleranceForApproxC1(double iTolC1) = 0;

  /**
  * Defines the tolerance for C2 approximation 
	* @param iTolC2
  * </dl>
  */
  virtual void SetToleranceForApproxC2(double iTolC2) = 0;

  /**
  * Defines whether propagation of opening faces should be activated or not
  * By default, it is enabled.
  * @param iPropagation
  * </dl>
  */
  virtual void SetOpeningFacesPropagation(CATBoolean iPropagation) = 0;

  /**
  * Defines whether propagation of special offset faces should be activated or not
  * By default, it is enabled.
  * @param iPropagation
  * </dl>
  */
  virtual void SetSpecialOffsetFacesPropagation(CATBoolean iPropagation) = 0;

  /**
  * Defines whether geometrical and topological simplification in post-treatment 
  *   should be activated or not.
  * By default, it is disabled.
  * @param iLevel
  * </dl>
  */
  virtual void SetSimplificationLevel(short iLevel) = 0;

  virtual short GetSimplificationLevel() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMShellOperator(); // -> delete can't be called
};

// constructeur a partir d'un CATBody et 2 valeurs d'offsets a appliquer
//  par defaut a toutes les faces (aucune face d'ouverture par defaut) 
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMShellOperator *CATPGMCreateShellOperator(
  CATBody *iBody,
  CATLength iInternalOffsetValue = 0.0,
  CATLength iExternalOffsetValue = 0.0,
  CATCGMJournalList *iJournal = NULL);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMShellOperator *CATPGMCreateShellOperator(
  CATBody *iBody,
  CATTopData *iTopData,
  CATLength iInternalOffsetValue = 0.0,
  CATLength iExternalOffsetValue = 0.0);

#endif /* CATIPGMShellOperator_h_ */
