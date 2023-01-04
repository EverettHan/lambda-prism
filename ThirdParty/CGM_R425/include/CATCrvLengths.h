//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
//===================================================================
//
// CATCrvLengths :
// Converts between global curve parameter and length 
// Intended for a big number of conversions. The creation
// is cumbersome but the subsequent evaluations are fast.
//
//===================================================================
// Usage notes:
//
//===================================================================
//   May 01 DJn Creation                                 D. Johansson
// 06/11/08 NLD Detabulation
// 06/11/08 NLD Ajout _SpecialLine
//              Suppression du constructeur sans SoftwareConfiguration
//              GetCurveLength() passe dans l'implementation
//              Ajout MakeSpecialLine()
// 07/11/08 NLD Contructeur sans SoftwareConfiguration retabli provisoirement pour impacts non vus
// 28/11/08 NLD Utilisation de CATCGMOperatorDebug pour outillage standard de debug/mesure
// 05/12/08 NLD Mieux: afin d'eviter des impacts de compilation des applications appelantes,
//              on declare toujours Run() et on l'implemente avec CATCGMOperatorDebugRunResult()
// 12/03/09 NLD Ajout _SpecialCircle et MakeSpecialCircle()
// 13/03/09 NLD Ajout GetCurveParamFromLengthSpecialCircle(), GetCurveParamFromLengthSpecialCompute(),
//              et GetLengthFromCurveParamCompute() GetLengthFromCurveParamSpecialCircle()
//              pour imputation CPU
// 07/04/09 NLD Ajout _Debug et CATCrvLengthsDebug
//              Ajout Init()
// 08/04/09 NLD Ajout OptimData et _Optim
//              Ajout _TolDJ
// 29/10/12 NLD Mise au propre: indentation et alignement
//              Ajout _SpecialHelix
//              Ajout _HelixData
//              Ajout _LinearCase
//              Protection par declaration en private, de:
//              - constructeur par defaut
//              - constructeur par copie
//              - operateur =  
// 01/10/13 NLD Decoupage interface/implementation (CATCrvLengthsImpl) sous #define
//              pour a terme isoler les donnees et methodes internes du monde exterieur
//                 OK011013 1) decoupage sous #define
//                 OK011013 2) activation du #define et livraison
//              KO OK081013 3) deflaggage du code
//              KO OK081013 4) deplacement des declarations de CATCrvLengthsImpl dans l'implementation
// 02/10/13 NLD Isolation de la gestion des polynomes _Polyn:
//              Ajout ResizePolyn(), GetPolyn(), GetLocalPolyn(), DeletePolyn()
//              ExpandArray() est renommee ResizeArray()
//              Ajout de _PolynSet et _PolynSetSize pour gestion d'allocation de polynomes par paquets
// 08/10/13 NLD Decoupage interface/implementation (CATCrvLengthsImpl), suite
//                          3) - deflaggage du code
//                          4) deplacement des declarations de CATCrvLengthsImpl dans l'implementation
// 12/03/20 Q48 Headers etc for math versioning
//===================================================================

#ifndef CATCrvLengths_H  
#define CATCrvLengths_H 

// ExportedBy
#include "Y30UIUTI.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include <stdlib.h>
#include "CATMathInline.h"

#include "CATString.h"
#include "CATDataType.h"
#include "CATListPV.h"
#include "CATListOfInt.h"

#include "CATSkillValue.h"

#include "CATCurve.h" 
#include "CATCGMVirtual.h"
#include "CATGeoFactory.h"
class CATLaw;
class CATCurve ; 
class CATSoftwareConfiguration;


#include "CATGeoOpTimer.h"
#include "CATExtCGMReplay.h"
#include "CATCGMStream.h"
#include "CATCGMOutput.h"
//#include "CATCGMOperatorDebug.h"

// class CATCrvLengthsDebug;
class CATCrvLengthsImpl;

class ExportedByY30UIUTI CATCrvLengths   : public CATGeoOperator

{    
  CATCGMVirtualDeclareClass(CATCrvLengths);

             //      -----------------------------------------------------------
 private   : // ----- Private   constructors
             //      -----------------------------------------------------------


  // Default constructor
           CATCrvLengths                     ();
  // Copy constructor
           CATCrvLengths                     (const CATCrvLengths&);

  // Operator '=' (overloaded) 
           CATCrvLengths& operator =         (const CATCrvLengths&);

 public:

/**
 * Object management
 */  
   //Do not use - Use the method with CATSoftwareConfiguration
           CATCrvLengths                     (const CATCurve                 * iCRV ) ;

           CATCrvLengths                     (      CATSoftwareConfiguration * iConfig,
                                              const CATCurve                 * iCRV ) ;

  virtual ~CATCrvLengths ()  ;

/**
 * Set tolerance: Default value is the "Factory Resolution". Empty,
 * argument, i.e. (0.0), returns to the "Factory Resolution".
 */  
  void SetTolerance ( double iTOL = 0.0 ) ;

/**
 * Set other curve ...
 */  
  void SetOtherCurve( const CATCurve *iCRV ) ;

/**
 * Set curve interval: Default values are the iCRV limits. Empty
 * argument, i.e. (1.0, 0.0), returns to the iCRV limits.
 */
  void SetCurveInterval( double iLowParam  = 1.0,
                         double iHighParam = 0.0 ) ;


/**
 * Run... Executes the set methods above.
 */  
  //NLD051208 Run() inconditionnel au lieu de CATCGMOperatorDebugDeclareRun(CATCrvLengths,CATGeoOperator);
  int Run();

/**
 * @nodoc @nocgmitf (internal) RunOperator ... Executes the set methods above.
 */  
  
  int RunOperator();

  

/**
 * Set global curve param iParU. The length (ParL) from iCRV(iLowParam)
 * will be returned.
 * iOrder is the order of the requested evaluation:
 * 0: the length.
 * 1: the first derivative of the length with respect to the param.
 * 2: the second derivative of the length with respect to the param.
 *
 * The derivatives are evaluated on the polynomial approximation and not
 * directly on the curve.
 */ 
  double GetLengthFromCurveParam ( double iParU , int iOrder = 0) ;

/**
 * Set length from iCRV(iLowParam), iParL. The global curve param (ParU) 
 * will be returned.
 * iOrder is the order of the requested evaluation:
 * 0: the param.
 * 1: the first derivative of the param with respect to the length.
 * 2: the second derivative of the param with respect to the length.
 *
 * The derivatives are evaluated on the polynomial approximation and not
 * directly on the curve.
 */
  double GetCurveParamFromLength ( double iParL , int iOrder = 0) ;

/**
 * Set length from iCRV(iLowParam), iParL. The global curve param (ParU) 
 * will be returned.
 * iOrder is the order of the requested evaluation:
 * 0: the param.
 * 1: the param and the first derivative of the param with respect to the length.
 * 2: the param the first and the second derivative of the param with respect to the length.
 * iParam the result allcated by caller 
 * iParam[0] : param ; iParam[1] : first derivative ; iParam[2] : second derivative
 */
  void GetCurveParamFromLength ( double iParL , int iOrder, double *iParam) ;

/**
 *Get curve length
 */
  double GetCurveLength () ;
  
/**
 * At creation, private interpolation data might be allocated in excess. 
 * Use "Compress()" if storage size is critical.
 */
  void Compress () ; 

/**
 * Renvoie la law de mapping. Cette méthode doit imperativement etre
 * appelee apres le run !!!
 * si double* Interval = NULL  => sur [0,1]
 * si double* Interval = [a,b] => sur [a,b]
 */
  CATLaw* GetLawMapping(double* iInterval);
  
protected:
  //friend class CATCrvLengthsImpl; 

private:

  CATCrvLengthsImpl*         _Impl;

public:  

//========================================================================
// CGMReplay Implementation - SKA Creation
//========================================================================
  /** @nodoc @nocgmitf */
  virtual const CATString       * GetOperatorId();
  virtual       CATGeoOpTimer   * GetTimer();
  /** @nodoc @nocgmitf */
  virtual       CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

  /** @nodoc @nocgmitf */
  virtual       void       WriteInput(CATCGMStream  & Str);
  /** @nodoc @nocgmitf */
  virtual       void       Dump( CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  virtual       void       WriteOutput(CATCGMStream & Str);
  /** @nodoc @nocgmitf */
  virtual       void       DumpOutput(CATCGMOutput & os) ;
  /** @nodoc @nocgmitf */
  virtual       void       DumpOutput(CATCGMStream& Str, CATCGMOutput& os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual       CATBoolean ValidateOutput(CATCGMStream& Str, CATCGMOutput & os,int VersionNumber=1);  
  /** @nodoc @nocgmitf */
  virtual       CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
};

//========================================================================
/**
 * Creator ...
 */
//Do not use
ExportedByY30UIUTI CATCrvLengths * CreateCATCrvLengths(const CATCurve *iCRV,
                 CATSkillValue mode = BASIC ) ;   

ExportedByY30UIUTI CATCrvLengths * CATCreateCATCrvLengths(CATSoftwareConfiguration * iConfig,
                                                          const CATCurve *iCRV,
                 CATSkillValue mode = BASIC ) ;  
#endif  
