#ifndef CATTopGeometricalMapping_h
#define CATTopGeometricalMapping_h
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
//   Not Yet Cerfied as Usable on Commercial Product
//
//  Ne fonctionne que sur les sommets dans un premier temps
//
// Auteurs: TYCX   
// Date: 11/02/2002
//
// Description: Obtenir les equivalences topologiques 
//              a partir des evaluations geometriques
//
//
//=============================================================================
#include "ExportedByCATTopologicalObjects.h"

#include "CATTopOperator.h"
#include "CATTopGeometricalMapType.h"
#include "CATGeometryType.h"
#include "CATBoolean.h"
#include "CATGeoFactory.h"

#include "CATString.h"

#include "CATListOfCATCGMArrayOfOrientedObjects.h"
#include "CATListOfCATICGMObjects.h"
#include "CATListOfCATICGMUnknowns.h"
#include "ListPOfCATTopology.h"
#include "CATListOfDouble.h"
#include "CATTopGeoMapping_QueryType.h"
#include "CATCollec.h"
#include "CATMathInline.h"

class CATTopology;
class CATBody;
//class CATLISTP(CATICGMUnknown);
class CATLISTP(CATTopology);
class CATExtTopGeometricalMapping;

class ExportedByCATTopologicalObjects CATTopGeometricalMapping : public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopGeometricalMapping);
public:
     
      //=======================================================================================================
      // Obtention du Mapping
      //========================================================================================================
      virtual void GetMapping( CATLISTP(CATCGMArrayOfOrientedObjects) & ioMapped, 
                               double                                ** ioGapOfMapped = NULL,
                               CATLISTP(CATICGMObject)                * ioIsolated = NULL,
                               CATLISTP(CATICGMObject)                * ioFailed   = NULL) = 0;

     
      //=======================================================================================================
      // Parametrages des resolutions
      //========================================================================================================
      virtual void GetResolution(double       & resolution, const CATResolutionType iResolutionType=CatC0) const = 0;
      virtual void SetResolution(const double & resolution, const CATResolutionType iResolutionType=CatC0) = 0;

      //=======================================================================================
      // Strategie d'execution
      //=======================================================================================
      /** @nodoc @nocgmitf */
      INLINE CATTopGeometricalMapType GetStrategy() const; 

      //=======================================================================================
      // Strategie d'execution
      //=======================================================================================
      /** @nodoc @nocgmitf */
      INLINE CATGeometricType GetFilter() const; 

      //=======================================================================================
      // Conditions d'entree
      //=======================================================================================
      /** @nodoc @nocgmitf */
      INLINE void GetInputs(CATLISTP(CATTopology) & ioInputs) const; 


      //=======================================================================================
      // Commodite pour l'integration CATCGMReplay
      //=======================================================================================
      /** @nodoc @nocgmitf */
      virtual const CATString * GetOperatorId(); 

      //=======================================================================================
      // Pour eviter d'interpreter   CATBody *GetResult()
      //=======================================================================================
      /** @nodoc @nocgmitf */
      virtual CATBoolean GivesBodyAsResult() const;

      //==============================
      // Seul destructeur admissible 
      //==============================
      virtual ~CATTopGeometricalMapping();

      //==============================
      // PrepareMapping + HasMapping 
      //==============================
      /** @nodoc @nocgmitf */
      virtual void       PrepareMapping() = 0;
      /** @nodoc @nocgmitf */
      virtual CATBoolean HasMapping( CATICGMUnknown *iMapping, CATCGMArrayOfOrientedObjects * & oMapping ) = 0;
      /** @nodoc @nocgmitf */
      virtual int        GetNumberOfFamilies() = 0;

      //KY1 : 04-02-2011

      /**	@nodoc @nocgmitf*/ 
      static const  CATString  *GetDefaultOperatorId();

protected:


      //=========================
      // KY1 (19/11/2010)
      //=========================
      /**	@nodoc @nocgmitf*/ 
      void  RequireDefinitionOfInputAndOutputObjects();

      //==============================
      // Seul constructeur admissible 
      //==============================
      CATTopGeometricalMapping(CATGeoFactory                  * iFactory, 
                               const CATLISTP(CATTopology) & iInputs, 
                               const CATTopData               & iTopData,
                               const CATTopGeometricalMapType   iStrategy,
                               const CATTopGeoMapping_QueryType iQueries,
                               const CATGeometricType            iFilter,
                               CATExtTopGeometricalMapping     * iExtTopGeometricalMapping);
      

      //=======================================================================================
      // Commodite pour l'integration CATCGMReplay
      //=======================================================================================
      static CATString _OperatorId;
      
      
      CATTopGeometricalMapType    _Strategy;
      CATTopGeoMapping_QueryType  _Query;
      CATGeometricType            _Filter;

      CATLISTP(CATTopology)    _Inputs;

      CATBoolean                  _Validated;
      CATBoolean                  _HasRun;
};


INLINE CATTopGeometricalMapType CATTopGeometricalMapping::GetStrategy() const
{
  return _Strategy;
}

INLINE CATGeometricType CATTopGeometricalMapping::GetFilter() const
{
  return _Filter;
}

INLINE void CATTopGeometricalMapping::GetInputs(CATLISTP(CATTopology) & ioInputs ) const
{
  ioInputs = _Inputs;
}

//========================================================================================
// Creation de l'operateur de mapping geometrique
//========================================================================================
ExportedByCATTopologicalObjects CATTopGeometricalMapping * CATCreateTopGeometricalMapping( 
     const CATTopData                 & iTopData, 
     const CATLISTP(CATICGMUnknown)   & iInputs,  
     const CATTopGeometricalMapType   iStrategy,
     const CATTopGeoMapping_QueryType iQueries,
     CATGeometricType                 iFilter );

ExportedByCATTopologicalObjects CATTopGeometricalMapping * CATCreateTopGeometricalMapping ( 
     const CATTopData                & iTopData,
     CATBody                         * iBody,
     const CATTopGeometricalMapType    iStrategy,
     const CATTopGeoMapping_QueryType  iQueries,
     CATGeometricType                  iFilter  );

ExportedByCATTopologicalObjects CATTopGeometricalMapping * CATCreateTopGeometricalMapping ( 
     const CATTopData                & iTopData,
     CATGeoFactory                   * iGeoFactory,
     const CATTopGeometricalMapType    iStrategy,
     const CATTopGeoMapping_QueryType  iQueries,
     CATGeometricType                  iFilter  );

#endif
