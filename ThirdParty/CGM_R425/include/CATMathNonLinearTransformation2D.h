// COPYRIGHT DASSAULT SYSTEMES 1998

//===================================================================
//===================================================================
//
// CATMathNonLinearTranformation2D
// Virtual class of for the restriction of a 
// CATMathNonLinearTransformation to a normal plane
//
//===================================================================


#ifndef CATMathNonLinearTransformation2D_H
#define CATMathNonLinearTransformation2D_H

#ifndef NULL
#define NULL 0
#endif

#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathSystemXY.h"
#include "CATMathTransformation2D.h"
#include "CATMathNonLinearTransfoType.h"
#include "CATMathInterval.h"
#include "CATMathStreamDef.h"
#include "CATBoolean.h"
class CATMathStream;
class CATSoftwareConfiguration;


class ExportedByYN000FUN CATMathNonLinearTransformation2D : public CATMathSystemXY
{
public:
  //-----------------------------------------------------------------
  // Constructor
  //-----------------------------------------------------------------
  
  CATMathNonLinearTransformation2D(CATSoftwareConfiguration * iConfig, const CATTolerance &iTol=CATGetDefaultTolerance());

  CATMathNonLinearTransformation2D(CATSoftwareConfiguration * iConfig, const CATMathTransformation2D & iTransfo, const CATTolerance &iTol = CATGetDefaultTolerance());

  CATMathNonLinearTransformation2D(CATSoftwareConfiguration * iConfig, const CATMathTransformation2D & iLTransfo, 
    const CATMathTransformation2D & iRTransfo,const CATTolerance &iTol=CATGetDefaultTolerance());

  //-----------------------------------------------------------------
  // Destructor
  //-----------------------------------------------------------------
  virtual ~CATMathNonLinearTransformation2D();
  
  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
  
  virtual CATMathClassId IsA() const = 0;

  virtual CATMathNonLinearTransfoType GetType() const = 0;
   
  //-----------------------------------------------------------------
  // Modifications and reading of coefficients 
  //-----------------------------------------------------------------
  
  virtual CATMathNonLinearTransformation2D * Duplicate() const = 0;

  virtual CATLONG32 GetNumberOfCoef() const = 0;

  virtual void GetCoef(double oCoef[]) const = 0;
  
  virtual void SetCoef(double iCoef[]) = 0;

  //-----------------------------------------------------------------
  // Right and Left Transformation management
  //-----------------------------------------------------------------
  void GetRightTransformation(CATMathTransformation2D * &oRightTransfo) const;

  void GetLeftTransformation (CATMathTransformation2D * &oLeftTransfo ) const;

/**
 * Defines the composition of a Linear Transformation with the nonlinear.
 * @return
 *  a new nonlinear transformation : CATMathTransformation o OldCATMathNonLinearTransformation2D
 */
  void ComposeLeft (const CATMathTransformation2D & iTransfo);

/**
 * Defines the composition of a Linear Transformation with the nonlinear.
 * @return
 *  a new nonlinear transformation : OldCATMathNonLinearTransformation2D o CATMathTransformation
 */
  void ComposeRight (const CATMathTransformation2D & iTransfo);

  virtual CATMathInterval EvalF( const CATMathInterval & X,const CATMathInterval & Y)const=0;
  virtual CATMathInterval EvalG( const CATMathInterval & X,const CATMathInterval & Y)const=0;
  virtual double EvalF(const double & x, const double & y) const = 0;
  virtual double EvalG(const double & x, const double & y) const = 0;
  virtual void EvalF(const double u, const double v, 
                      const CATMathOption iOptions,
                      double * f,
                      double * fx =0, double * fy=0,
                      double * fx2=0, double *fxy=0, double *fy2=0) const=0;
  virtual void EvalG(const double u, const double v, 
                      const CATMathOption iOptions,
                      double * f,
                      double * fx =0, double * fy=0,
                      double * fx2=0, double *fxy=0, double *fy2=0) const=0;




   //-----------------------------------------------------------------
   // Stream/Unstream specific management
   //-----------------------------------------------------------------
   /**
	* @nodoc
	*/
  void SetIsUnStreamed();

   /**
	* @nodoc
	*/
   virtual short GetStreamTransfo2DType() const;

   /**
   * @nodoc
   */   
   virtual CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

   /**
   * @nodoc
   */   
   static void Stream( CATMathStream& Str, CATMathNonLinearTransformation2D *iTransfo, const char iLabelReserved[] = ""  );

   /**
   * @nodoc
   */   
   static void UnStream( CATMathStream& Str, CATMathNonLinearTransformation2D * &ioTransfo
                       , const CATTolerance &iTol , const char iLabelReserved[] = ""  );

   /**
   * @nodoc
   */
   virtual void Stream( CATMathStream& Str, const char iLabelReserved[] = "" ) const;


protected:

  void DuplicateData(CATMathNonLinearTransformation2D * oTransfoDestination) const ;

  CATMathTransformation2D * _MathTransfoLeft;
  CATMathTransformation2D * _MathTransfoRight;

};

#endif  
