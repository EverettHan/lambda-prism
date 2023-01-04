// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
// CATSectionSolverData
// Data for sweep section computation by external solver 
//
//=============================================================================
// Usage notes:
//=============================================================================
// 25/09/02 JSX Creation
// 12/10/05 NLD Ajout _SG_Forms pour evolutivite (utilisation de cette architecture
//              avec multiforme en entree/sortie) et pour debug
// 27/10/09 NLD Initialisation de _SK_NbSketchCurve dans constructeur
//              pour utilisation hors mode fast eval dans atelier freeform par exemple
//=============================================================================
//
#ifndef CATSectionSolverData_H
#define CATSectionSolverData_H

#include "CATGMOperatorsInterfaces.h"

#include "CATListOfInt.h"
#include "CATListOfDouble.h"
#include "CATMathPlane.h"
#include "CATListOfCATCurves.h"
#include "CATFrFCompositeCurve.h"

class CATCurve;
class CATFrFNurbsMultiForm;

class ExportedByCATGMOperatorsInterfaces CATSectionSolverData : public CATCGMVirtual
  {
  public: 
    
    CATSectionSolverData()
      {
       _SK_CCV           = NULL;
       _SK_NbSketchCurve = 0 ;
      }
    virtual ~CATSectionSolverData();

  public :

    // level du data
    CATLONG32               _SSD_Level;

    //
    // A) Donnees definies par le Sketcher :
    //    leurs valeurs sont stables pour toutes les evaluations
    //======================================================================
    CATLONG32               _SK_NbSketchCurve;
    CATListOfInt            _SK_ContCrvCrv;  // Continuite entre 2 SC consecutives {0: non contraint 1: contraint}
    CATListOfDouble         _SK_AngleCrvCrv; // Angle a respecter
    CATListOfInt            _SK_ExtCont;
    //
    // B) Donnee fournie par la geometrie
    //===================================
    double                  _SG_WParam; // Parametre du MovingFrame
    CATMathPlane            _SG_Plane;  // Plan geometrique d'evaluation du sketch
    CATFrFNurbsMultiForm ** _SG_Forms ; // Multiformes en entree (NLD121005 pour evolutivite et debug)
    
    //
    
    // C) Infos renseignees par le Sketcher 
    //    Pour une evaluation en _SW_Param / Plan
    //    Gestion memoire par le Sketcher
    //    apres utilisation CGM met a null les pointeurs
    //===============================================
    CATListOfInt            _SK_NbGeoCurveBySketchCurve; // Correspondances  Sketch<->Edge
    //
    CATLONG32               _SK_KindOfRepresentation;    // Courbes ou Formes
    CATFrFCompositeCurve  * _SK_CCV;
    //CATLISTP(CATCurve)    _SK_Curves;
    CATFrFNurbsMultiForm ** _SK_Forms;
    

  } ;
#endif 
