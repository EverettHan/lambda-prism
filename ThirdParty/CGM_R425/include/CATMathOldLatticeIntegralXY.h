// COPYRIGHT   : DASSAULT SYSTEMES 2009
//
//  00/00/00 XXX Creation
//  15/07/18 JSX Move some data to protected, to be used by LatticeIntegarlXYCuda
//
#ifndef CATMathOldLatticeIntegralXY_H
#define CATMathOldLatticeIntegralXY_H

#include "YN000FUN.h"
#include "CATBoolean.h"
#include "CATMathLatticeIntegralXY.h"

class CATSoftwareConfiguration;
class CATMathFunctionX;
class CATMathVectorialFunctionXY;

class ExportedByYN000FUN CATMathOldLatticeIntegralXY : public CATMathLatticeIntegralXY
{
public:
  /// Constructor for the CATMathOldLatticeIntegralXY class
  /// Emulates to the old CATMathLatticeIntegralXY class.
  ///
  /// @param[in] iSoftwareConfiguration
  /// @param[in] iF The integrands
  CATMathOldLatticeIntegralXY( CATSoftwareConfiguration *iSoftwareConfiguration,
                               const CATMathVectorialFunctionXY &iF );

  virtual ~CATMathOldLatticeIntegralXY();

  /// Set the maximum rank.
  /// Integrands will be evaluated 4^max rank times.
  ///
  /// @param[in] iRank
  /// @return Negative number upon error, 0 otherwise.
  virtual int SetMaxRank( int iRank );

  /// Set the integration relative error tolerance
  ///
  /// @param[in] iTolerance Error tolerance value for each of the integrands
  /// @return Negative number upon error, 0 otherwise.
  virtual int SetTolerance( const double *iTolerance,
                            CATBoolean iRelativeError );

  /// Set the integration domain
  /// The integrals are currently computed as 
  /// \int_{x=iXStart}^{iXEnd} \int_{y=iYStart(x)}^{iYEnd(x)} f(x,y) dy dx
  ///
  /// @param[in] iXStart Lower integration bound for x
  /// @param[in] iXEnd Upper integration bound for x
  /// @param[in] iYStart Lower integration bound for y(x)
  /// @param[in] iYEnd Upper integration bound for y(x)
  /// @return Negative number upon error, 0 otherwise.
  virtual int SetIntegrationDomain( double iXStart,
                                    double iXEnd,
                                    double iYStart,
                                    double iYEnd );
  virtual int SetIntegrationDomain( double iXStart,
                                    double iXEnd,
                                    double iYStart,
                                    const CATMathFunctionX *iYEnd );
  virtual int SetIntegrationDomain( double iXStart,
                                    double iXEnd,
                                    const CATMathFunctionX *iYStart,
                                    double iYEnd );
  virtual int SetIntegrationDomain( double iXStart,
                                    double iXEnd,
                                    const CATMathFunctionX *iYStart,
                                    const CATMathFunctionX *iYEnd );

  /// Set a bound to the integration domain
  /// _YEnd will be bounded to the [YStart,YBound] or
  /// [YBound,YStart] interval.
  ///
  /// @param[in] iYBound the bound
  /// @return Negative number upon error, 0 otherwise.
  virtual int SetIntegrationDomainBound( double iYBound );

  /// Evaluate the integrals
  ///
  /// @param[out] oResults The results
  /// @param[out] oErrors The errors (relative or absolute depending on the iRelativeError argument given to SetTolerance). Can be NULL.
  /// @return Negative number upon error, 0 otherwise.
  virtual int Eval( double *oResults, double *oErrors );

private:
  // Internal use methods
    int SetIntegrationDomain( double iXStart,
                              double iXEnd,
                              double iYStart,
                              double iYEnd,
                              const CATMathFunctionX *iYStartFunction,
                              const CATMathFunctionX *iYEndFunction );

  /// Clear non constructor specific settings
  void ClearSettings( void );  

protected:
  /// Reset the grid
  void ResetGrid( void );
  /// Choose the initial grid
  ///
  /// @return Negative number upon error, 0 otherwise.
  int ChooseGrid( void );

  /// Generate the initial grid
  ///
  /// @return Negative number upon error, 0 otherwise.
  int GenerateGrid( void );

  /// Cache subresults
  void CachePositionAndWeight( int iXOffset,
                               int iRank,
                               double *oSx,
                               double *oDSx,
                               double *oYStart,
                               double *oYEnd ) const;
private:

  /// Compute results on a subgrid
  ///
  /// @param[out] oResults Array to store results
  /// @param[in] iXOffset Offset of the x coordinate
  /// @param[in] iYOffset Offset of the y coordinate
  /// @param[out] oValues Buffer used durring computation (passed as a parameter to prevent multiple allocation. Should maybe be changed to a private data member)
  virtual void ComputeSubGrid( double *ioResults,
                       double *iSx,
                       double *iDSx,
                       double *iSy,
                       double *iDSy,
                       double *iYStart,
                       double *iYEnd,
                       double *oValues,
                       double *ioCompensation ) const;

  /// Check results with regards to error tolerance
  ///
  /// @param[in] iPreviousResults
  /// @param[in] iResults
  /// @return True if tolerance checks were all validated, false otherwise
  CATBoolean CheckTolerance( const double *iResults,
                       int iRank, int iSubRank, CATBoolean &oApprox1, double *oErrors );
  //===============================================================================================================
  // DATA
  //===============================================================================================================
  // 
  protected:
  // User settings
  CATSoftwareConfiguration *_SoftwareConfiguration;

  const CATMathVectorialFunctionXY &_F; /// Integrands
  double *_Tolerance; /// Relative error tolerance for each of the functions
  CATBoolean _FixTolerance; /// Never compare relative tolerances with absolute errors.

  double _XStart, _XEnd; /// Integration bounds for x
  double _YStart, _YEnd;
  const CATMathFunctionX *_YStartFunction, *_YEndFunction; /// Integration bounds for y(x)
  CATBoolean _UseYBound;
  double _YEndBound;

  double *_RelativeErrors; /// Relative errors cache used when emulating the old CATMathLatticeIntegralXY class.

  int _MaxRank; /// Maximum number of grid subdivision iterations. Must be >= 1 and <= 31-ceil(log2(numPoints))/2.

  // Internal variables and cache
  int _NumIntegrands;

  struct
  {
    int numerator;
    int denominator; /// should be coprime with numerator
    int *y;
  } _Grid; /// The Grid's definition
};

#endif
