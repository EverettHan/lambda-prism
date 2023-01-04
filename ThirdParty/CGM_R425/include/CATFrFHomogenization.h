// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATFrFHomogenization:
// Mother class of homogenization tools for Nurbs.
//
//==========================================================================
//
// Usage notes:
// This class contains the Nurbs homogenization common attributes .
//
//==========================================================================
// Juin. 97 DHN Creation
// 24/05/05 NLD Ajout Init() et InitDegree()
//              remplacement de _Tolerance par _Tolerance_DoNotUseDirectly
//              Ajout de _UseDefaultTolerance
// 30/04/12 NLD Ajout _SoftwareConfiguration et SetSoftwareConfiguration()
//              Ajout InitMultiForms() et InitBipars()
//              Le copy constructor devient privé
//              (EN ATTENTE) On supprime aussi le constructeur à la noix mal typé
//========================================================================== 

#ifndef CATFrFHomogenization_H
#define CATFrFHomogenization_H

#include "CATFrFNurbsBipar.h"
#include "CATFrFNurbsMultiForm.h"
#include "CATKnotVector.h"
#include "CATSkillValue.h"

#include "YP00IMPL.h"
#include "CATCGMVirtual.h"
#include "CATTolerance.h"

// #define CATFrFHomogenization_ShuntIrrelevantConstructor "NLD30041"
class CATSoftwareConfiguration;
//-----------------------------------------------------------------------------
class ExportedByYP00IMPL CATFrFHomogenization  : public CATCGMVirtual
{
  private:
    //  copy constructor
    CATFrFHomogenization(const CATFrFHomogenization &iHomogenization);

  public :

    //-------------------  Basic Methods ------------------- 
    //  default constructor
    CATFrFHomogenization();
    //  constructor with 2 Bipars
    //  iBiparDirection = 1 if homogenization of U direction , 2 for V
    CATFrFHomogenization(      CATFrFNurbsBipar      & iBipar1         ,
                               CATFrFNurbsBipar      & iBipar2         , 
                         const CATLONG32            *  iBiparDirections, 
                         const CATSkillValue         & iMode           = BASIC  );
    #ifndef CATFrFHomogenization_ShuntIrrelevantConstructor
    //  constructor with a set of Bipars and/or a set of multiforms
    //  DON'T USE ANYMORE - USE THE NEXT ONE
    CATFrFHomogenization(      CATFrFNurbsMultiForm *  iMultiForm      , 
                         const CATLONG32             & iNbOfMultiForms , 
                               CATFrFNurbsBipar     *  iBipar          , 
                         const CATLONG32             & iNbOfBipars     , 
                         const CATLONG32            *  iBiparDirections, 
                         const CATSkillValue         & iMode           = BASIC  );
    #endif
    //  constructor with a set of Bipars and/or a set of multiforms
    CATFrFHomogenization(CATFrFNurbsMultiForm      **  iMultiForm      , 
                         const CATLONG32             & iNbOfMultiForms , 
                               CATFrFNurbsBipar    **  iBipar          , 
                         const CATLONG32             & iNbOfBipars     , 
                         const CATLONG32            *  iBiparDirections, 
                         const CATSkillValue         & iMode           = BASIC  );  

    //  destructor
    virtual ~CATFrFHomogenization();

    //------------------- Data Access Methods -------------------  
    // define software configuration
    //   not necessary if software configuration can be read in one of the input CATFrFNurbsMultiForm
    void SetSoftwareConfiguration(CATSoftwareConfiguration* iSoftwareConfiguration);

    CATLONG32 GetDegree() const;
    double GetTolerance() const;

    // impose a degree 
    void SetDegree(const CATLONG32 &);

    // impose a tolerance 
    void SetTolerance(const double &);

    // impose a reference multiform
    void SetReferenceMultiForm(const CATLONG32 &iMultIndex);

    // impose a reference bipar
    void SetReferenceBipar(const CATLONG32 &iBiparIndex);

    //------------------- Compute Methods -------------------  
    // Knot Vectors Harmonization (by Knot Insertion)
    void HomogenizeKnotVectors( );

    // compute the homogenization :
    // if iHomogenizeTheKnotVectors = 1, Knot Vectors are also 
    // homogenized (Knot Insertion)
    // if iHomogenizeTheKnotVectors = 0 (default value), 
    // only the degrees are homogenized
    void Compute(const CATLONG32 &iHomogenizeTheKnotVectors   = 0   );
    

  private :
    void Init() ;
    void InitMultiForms(      CATFrFNurbsMultiForm ** iMultiForm,
                        const CATLONG32             & iNbOfMultiForms);
    void InitBipars    (      CATFrFNurbsBipar     ** iBipar,
                        const CATLONG32             & iNbOfBipars,
                        const CATLONG32             * iBiparDirections);
    void InitDegree() ;
    //------------------- Datas -------------------
    CATSoftwareConfiguration * _SoftwareConfiguration;
    CATFrFNurbsBipar        ** _tabOfBipars  ;
    CATLONG32                  _NbOfBipars;

    CATLONG32                * _BiparDirections; //Bipar Direction to Homogenize
                                                 //1 -> U
                                                 //2 -> V

    CATFrFNurbsMultiForm    ** _tabOfMultiForms  ;
    CATLONG32                  _NbOfMultiForms;

    CATLONG32                  _Degree;
    double                     _Tolerance_DoNotUseDirectly;
    CATLONG32                  _RefMult;
    CATLONG32                  _RefBip;
    const CATTolerance       * _TolObject;
    int                        _UseDefaultTolerance ;
};

#endif
