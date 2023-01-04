#ifndef CATMathFunctionGeneral_H
#define CATMathFunctionGeneral_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include "CATIACGMLevel.h"
#include "YN000FUN.h"

#include "CATMathDef.h"
#include "CATMathDiagnostic.h"
#include "CATCGMNewArray.h"
#include "CATCGMStreamVersion.h"
#include "CATCGMVirtual.h"
 
class CATMathStream;
class CATMathFunctionX;
class CATMathFunctionXY;
#if defined ( CATIACGMR216CAA )
class CATTolerance;
#endif

/**
 * Class representing a scalar function of one or more variables.
 */ 
class ExportedByYN000FUN CATMathFunctionGeneral : public CATCGMVirtual
{

 public:
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

   //-----------------------------------------------------------------
   // Information methods
   //-----------------------------------------------------------------
/**
 * Returns the class name of <tt>this</tt>  CATMathFunctionGeneral.
 * @return
 * A pointer to the class name.
 */
   virtual CATMathClassId IsA() const = 0;

 /**
 * Tests if <tt>this</tt> CATMathFunctionGeneral derives from a class (given by its name).
 * @param iClassId
 * The name of the class.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> CATMathFunctionGeneral is a kind of <tt>iClassId</tt>,
 * <tt>FALSE</tt> otherwise.
 */
   virtual CATBoolean IsAKindOf(const CATMathClassId iClassId) const;

/**
 * Tests if an evaluator is available for <tt>this</tt> CATMathFunctionGeneral.
 * @param iOption
 * The type of evalution.
 * <br><b>Legal values</b>:
 * <dl> <dt>OptionEval   </dt>  <dd>  evaluation of the function
 * <dt>OptionEvalFirstDeriv   </dt>  <dd>  evaluation of the first derivative of the function
 * <dt>OptionEvalSecondDeriv</dt>  <dd>  evaluation of the second derivative of the function
 * <dt>OptionEvalThirdDeriv</dt>  <dd>  evaluation of the third derivative of the function
 * </dl>
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if the evaluation is available for <tt>this</tt> CATMathFunctionGeneral,
 * <tt>FALSE</tt> otherwise.
 */
   virtual CATBoolean IsOption (const CATMathOption iOption) const;

   




  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


   /**
	* @nodoc
	*/
  virtual ~CATMathFunctionGeneral();

   /**
   * @nodoc
   * Get the number of variables of the function 
   */
   virtual CATLONG32 GetNumberOfVariables() const = 0;

   /**
   * @nodoc
   * Gives the number of components (first level only, -1 means not implemented)
   */
   virtual int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;


   //-----------------------------------------------------------------
   // Stream/Unstream specific management
   //-----------------------------------------------------------------

#if defined ( CATIACGMV5R21 )
   /**
	* @nodoc
	*/
   virtual short GetStreamDomainType(char ioDomain[3]) const;
#else
   /**
	* @nodoc
	*/
   virtual short GetStreamType() const;
#endif

   /**
   * @nodoc
   */   
   static void StreamHead( CATMathStream& Str, CATMathFunctionGeneral *iFunction, const char iLabelReserved[] = ""  );

   /**
   * @nodoc
   */
   virtual void Stream( CATMathStream& Str, const char iLabelReserved[] = "" ) const;

   /**
   * @nodoc
   */   
   CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

   /**
   * @nodoc
   */   
   static void Stream( CATMathStream& Str, CATMathFunctionGeneral *iFunction, const char iLabelReserved[] = ""  );

   /**
   * @nodoc
   */   
#if defined ( CATIACGMR216CAA )
   static void UnStream( CATMathStream& Str, CATMathFunctionXY *&oFunctionXY, const CATTolerance &iTolObject, const char iLabelReserved[] = "" );
#else
   static void UnStream( CATMathStream& Str, CATMathFunctionXY *&oFunctionXY, const char iLabelReserved[] = ""  );
#endif

   /**
   * @nodoc
   */   
#if defined ( CATIACGMR216CAA )
   static void UnStream( CATMathStream& Str, CATMathFunctionX *&oFunctionX, const CATTolerance &iTolObject, const char iLabelReserved[] = "" );
#else
   static void UnStream( CATMathStream& Str, CATMathFunctionX *&oFunctionX, const char iLabelReserved[] = ""  );
#endif

 protected:

   /**
   * @nodoc
   */   
   virtual CATBoolean _IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

};

#endif

