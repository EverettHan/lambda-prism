//===================================================================
// CATMathClusterization.cpp
// Header definition of class CATMathClusterization
// Previously CATMathClusteringKernel
//===================================================================
//
// Usage notes:
//
//===================================================================
//  Creation 2011-04-21 : T. Rose (SRT)
//  Industrialization 2012-08-08 : E.-M. Duclairoir/KJD 
//   - addition of the CATClusteringDescription structure 
//      and of the CATDeclareClusteringMethod and CATImplementClusteringMethod macros 
//      in order to introduce a  linked list mecanism
//   - thanks to this linked list mecanism (CATClusteringDescription *_pFirst), 
//       implementation of InitialisationClusteringMethod which enables the user to build a class instance using only its name .
//   - addition of the Get/SetclusteringParam methods which modify 
//       or return the intrinsic parameters of the different clustering algorithms 
//              
//===================================================================

#ifndef CATMathClusterization_H
#define CATMathClusterization_H

#include "CATDataType.h"
#include "CATString.h"
#include "CATOptParam.h"
#include "CATOptTypes.h"
#include "CATTolerance.h"
#include "CATToleranceAccess.h"

class CATSoftwareConfiguration;


//-----------------------------------------------------------------------
class  ExportedByYN000OPT CATMathClusterization
{
public:
  // Standard constructors and destructors
  // -------------------------------------
  CATMathClusterization (CATSoftwareConfiguration * ipConfig, const CATTolerance & iTolObject);
  virtual ~CATMathClusterization ();


  /** Executes the clustering method
  * @param iPopulationSize    The population size
  * @param iSpaceSize         The space size
  * @param iaPositions        The particles positions 
  * @param iaValues           The function value for each particle
  */
  virtual void Run(CATULONG32, CATULONG32, CATOptReal const *, CATOptReal const *) = 0;

  /** Returns the number of desired clusters
  * @return               The numbers of desired clusters
  */
  CATULONG32 GetNumberClusters() const;

  /** Sets the number of desired clusters
  * @param iNbClusters    The numbers of desired clusters
  */
  void SetNumberClusters(CATULONG32);

  /** Returns the number of found clusters
  * @return               The numbers of found clusters
  */
  CATULONG32 GetRealNumberClusters() const;

  /** Returns clusters (Do not delete returned pointer)  
  * @return               An array which split particles in clusters
  */
  CATULONG32 const * const GetClusters() const;

  /** Returns clusters
  @ @param iPopulationSize    The population size
  * @param oaClusters         An array which split particles in clusters
  */
  void GetClusters(CATULONG32, CATULONG32 *) const;

  /** 
  * Sets/Gets the specific parameters of the different clustering algorithms  
  * iNameParam is the name of the parameter 
  * iParamValue its value
  * returns S_OK if the action is performed otherwise S_FALSE or E_FAIL
  * The available parameters are :
  * -> For the density method
  * cplDensity_MinimumPointNumber :  the minimum number of points to increase a cluster                             (Get/Set -> CATULONG32)
  * cplDensity_SphereRadius       :      the sphere radius                                                          (Get/Set -> CATOptReal)
  * -> For the kmeans methods
  *  cplKMeans_MaxIteration        : maximum of iteration done by the method                                          (Get/Set -> CATULONG32)
  *  cplKMeans_Epsilon             : difference between two successive position which determine stop condition        (Get/Set -> CATOptReal)
  * -> For the fuzzy version of kmeans methods
  *  cplKMeans_Fuzzyness           : Fuzzy alghorithm parameter (Range : 0..2)                                        (Get/Set -> CATOptReal)
  */
  virtual HRESULT SetClusteringParam ( const CATOptParamLabel & iNameParam, CATOptParam & iParamValue);

  virtual HRESULT GetClusteringParam ( const CATOptParamLabel & iNameParam, CATOptParam  & oParamValue);


  CATOptDescription  GetClusteringDescription();

protected:
  /** Delete arrays and pointers and set them to 0
  */
  virtual void ClearVariables();

 //===========================================================================================================
 //
 //  DATA
 //
 //===========================================================================================================

protected:
  CATSoftwareConfiguration           * _pConfig;
  short                                _CGMLevel;
  const CATFullTolerance             & _TolObject;

  CATULONG32 _nbClusters;  /* Number of desired clusters */
  CATULONG32 _nbRealClusters;  /* Number of found clusters */
  CATULONG32 * _aClusters;  /* Cluster distribution */

  /* Variables which indicate sizes which were used to create current array (like _aClusters) */
  CATULONG32 _currentNbClusters;
  CATULONG32 _currentSpaceSize;
  CATULONG32 _currentPopulationSize;
 
  CATOptDescription _methodDescription;


private:
  // Copy constructor and equal operator
  // -----------------------------------
  CATMathClusterization (CATMathClusterization &);
  CATMathClusterization& operator=(CATMathClusterization&);
};

ExportedByYN000OPT CATMathClusterization * CreateMathClusterization(CATSoftwareConfiguration * ipConfig, const CATTolerance & iTolObject, CATClusteringMethodId iMethodName);
//-----------------------------------------------------------------------

#endif

   
