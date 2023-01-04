// COPYRIGHT DASSAULT SYSTEMES 1998

//===================================================================
//===================================================================
//
// CATMathNonLinearTranformation
// Virtual class of 3x3 systems with coupled variables
//
//===================================================================
// Nov. 98    Creation                         A. CADE
// 07/06/16 NLD Ajout Init()
//              Ajout constructeurs avec configuration
//===================================================================



#ifndef CATMathNonLinearTransformation_H
#define CATMathNonLinearTransformation_H

#include <stdio.h>
#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathSystem.h"
#include "CATMathTransformation.h"
#include "CATMathNonLinearTransfoType.h"
#include "CATMathInterval.h"
#include "CATCGMStreamVersion.h"
#include "CATBoolean.h"
class CATMathStream;
class CATMathPoint;
class CATMathVector;
class CATTolerance;

class CATMathNonLinearTransformation;

//===================================================================
/** @nodoc */
// Cette methode de creation, a l'implementation introuvable, semble etre une tentative avortee. NLD070616
extern ExportedByYN000FUN CATMathNonLinearTransformation * 
CreateMathNonLinearTransformation(CATMathNonLinearTransfoType   iType               ,
                                  double                      * iCoef               ,
                                  CATMathTransformation       * iRightTransfo = NULL,
                                  CATMathTransformation       * iLeftTransfo  = NULL);


//===================================================================
class ExportedByYN000FUN CATMathNonLinearTransformation : public CATMathSystem
{
public:
  //-----------------------------------------------------------------
  // Constructors
  //-----------------------------------------------------------------
  // 1) without none, one or two transformations
  CATMathNonLinearTransformation(      CATSoftwareConfiguration* iConfig    ,
                                 const CATTolerance            & iTolObject ,
                                 const CATMathTransformation   * iLTransfo  ,
                                 const CATMathTransformation   * iRTransfo
                                );
  
  // deprecated constructors
  // -----------------------
  // 1) without transformation
  CATMathNonLinearTransformation(const CATTolerance            & iTolObject = CATGetDefaultTolerance());
  
  // 2) with one transformation
  CATMathNonLinearTransformation(const CATMathTransformation   & iTransfo   , 
                                 const CATTolerance            & iTolObject = CATGetDefaultTolerance());
  
  // 3) with two transformations
  CATMathNonLinearTransformation(const CATMathTransformation   & iLTransfo, 
                                 const CATMathTransformation   & iRTransfo,
                                 const CATTolerance            & iTolObject = CATGetDefaultTolerance());
  
  //-----------------------------------------------------------------
  // Destructor
  //-----------------------------------------------------------------
  virtual ~CATMathNonLinearTransformation();
  
  //-----------------------------------------------------------------
  // Creation method
  //-----------------------------------------------------------------
  friend ExportedByYN000FUN CATMathNonLinearTransformation * 
    CreateMathNonLinearTransformation(CATMathNonLinearTransfoType   iType               ,
                                      double                      * iCoef               ,
                                      CATMathTransformation       * iRightTransfo,
                                      CATMathTransformation       * iLeftTransfo );

  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
  
  virtual CATMathClassId IsA() const = 0;

  virtual CATMathNonLinearTransfoType GetType() const = 0;
  
  //-----------------------------------------------------------------
  // Overloaded methods
  //-----------------------------------------------------------------
  virtual void Eval         (const double *iX, double *oFX, const double iArctanLimit) = 0;

  virtual void EvalJacobian (const double *iX, CATMathNxNFullMatrix *oJacobianFX) = 0; 
  
  virtual void EvalJacobian (const double *iX, double *oJacobianFX) = 0;
  
  virtual void EvalJacobian (const double *iX, double *oJacobianFX, const double iArctanLimit) = 0;

  virtual void Eval         (const double *iX,  double *oX,CATMathNxNFullMatrix *oJacobianFX, double iArctanLimit) = 0;

  virtual CATMathInterval EvalInterval( CATMathInterval * iIntervalArray, CATLONG32  iNumCoord, double iArctanLimit=0.) = 0;

  //-----------------------------------------------------------------
  // Modifications and reading of coefficients 
  //-----------------------------------------------------------------
  
  virtual CATMathNonLinearTransformation * Duplicate() const = 0;

  virtual CATLONG32 GetNumberOfCoef() const = 0;

  virtual void      GetCoef(double oCoef[]) const = 0;
  
  virtual void      SetCoef(double iCoef[]) = 0;

  //-----------------------------------------------------------------
  // Right and Left Transformation management
  //-----------------------------------------------------------------
  void GetRightTransformation(CATMathTransformation * &oRightTransfo) const;

  void GetLeftTransformation (CATMathTransformation * &oLeftTransfo ) const;

/**
 * Defines the composition of a Linear Transformation with the nonlinear.
 * @return
 *  a new nonlinear transformation : CATMathTransformation o OldCATMathNonLinearTransformation
 */
  void ComposeLeft (const CATMathTransformation & iTransfo);

/**
 * Defines the composition of a Linear Transformation with the nonlinear.
 * @return
 *  a new nonlinear transformation : OldCATMathNonLinearTransformation o CATMathTransformation
 */
  void ComposeRight (const CATMathTransformation & iTransfo);

/**
 * Get some characterstic of yhe deformation.
 * @return
 *  If it exists , the rip plane of the deformation
 */
  virtual CATMathPlane * GetRipPlane() =0;
                  
				 

   //-----------------------------------------------------------------
   // Stream/Unstream specific management
   //-----------------------------------------------------------------
   /**
	* @nodoc
	*/
   virtual short GetStreamTransfoType() const;

   /**
   * @nodoc
   */   
   virtual CATBoolean IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

   /**
   * @nodoc
   */   
   static void Stream( CATMathStream& Str, CATMathNonLinearTransformation *iTransfo, const char iLabelReserved[] = "", CATBoolean iStreamAllEvenIfTooOld = 0);

   /**
   * @nodoc
   */ 
   static void UnStream( CATMathStream& Str, CATMathNonLinearTransformation * &ioTransfo, const char iLabelReserved[] = "" );// Deprecated
   /**
   * @nodoc
   */ 
   static void UnStream( CATMathStream& Str, CATMathNonLinearTransformation * &ioTransfo, const CATTolerance & TolObject, const char iLabelReserved[] = "" );
   /**
   * @nodoc
   */
   virtual void Stream( CATMathStream& Str, const char iLabelReserved[] = "", CATBoolean iStreamAllEvenIfTooOld = 0) const = 0;


protected:


  void DuplicateData(CATMathNonLinearTransformation * oTransfoDestination) const;

private:
  void Init();
  
protected:

  CATMathTransformation * _MathTransfoLeft;
  CATMathTransformation * _MathTransfoRight;

};

#endif  
