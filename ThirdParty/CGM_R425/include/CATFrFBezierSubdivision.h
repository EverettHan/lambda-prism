/*-*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 2001 
//==========================================================================
//
// CATFrFBezierSubdivision:
//		Algorithme de subdivision d'un arc de Bezier
//
//========================================================================== 
// February 2001     Creation                       CCK
//========================================================================== 

#ifndef CATFrFBezierSubdivision_H
#define CATFrFBezierSubdivision_H


#include "CATGeoFactory.h"
//#include "CATMathPoint.h"
//#include "CATMathSetOfPointsND.h"
#include "CATMathSetOfPoints.h"
#include "CATCGMVirtual.h"

#include "CATMathFunctionXY.h"

// ATTENTION, le degree ne peut etre superieur a 16 = CATMAxDegree !!!
// Si on demande un degre superieur, le constructeur renvoie un message
// d'erreur
#define CATMaxDegree 23


//-----------------------------------------------------------------------------
class ExportedByYP00IMPL CATFrFBezierSubdivision  : public CATCGMVirtual
{
  public :
    
    // Default Constructor
    CATFrFBezierSubdivision(const CATMathSetOfPoints* iInitialControlPoints);
    
    // Destructor
    ~CATFrFBezierSubdivision();

    void SetNbSubd(CATLONG32 iNbSubd);

    // Run : doit etre appele dans tous les cas
    // iN = Nbre de subdivision souhaitee
    // Retourne : 0 si tout s'est bien passe
    //            1 si erreur dans le processus
    //            -1 si donnees invalides (degre < 1 ou degre > 15)
    CATLONG32 Run();

    // Retourne les points de controle apres subdivision
    // Doit etre detruit par l'appelant
    CATMathSetOfPoints* GetCrltPtAfterSudb();

    // Calcul la longueur du nouveau polygone de controle
    // Il faut avoir fait un Run avant
    double GetNewPolygonLength();

    // Calcul la longueur du morceau du nouveau polygone de controle
		// compros entre le iIndexFirstPt-ieme nouveau pt et le iIndexSecondPt
		// iIndexFirstPt et iIndexSecondPt partent de 0.
		// Retourne -1 si calcul impossible (si iIndexSecondPt<iIndexFirstPt)
    double GetNewPolygonLengthBetween2pts(CATLONG32& iIndexFirstPt, CATLONG32& iIndexSecondPt);


  protected :

    // BasicRun : Subdivise un arc de Bezier en deux arcs de Bezier
    // retourne le nouveau polygone de controle
    // Ces deux methodes sont INTERNES !!!!
    // Si on veut appeler une seule subdivision, appeler la methode
    // NSubdivisions avec iN = 1
    CATMathSetOfPoints* BasicRun(CATMathSetOfPoints* InitialCtlPts);

    // NSubdivisions : Subdivise un arc de Bezier N fois => on obtient
    // 2^N arcs a la fin
    // Plus N est grand plus le polygone de controle est proche de la
    // courbe
    // ATTENTION :
    // Le CATMathSetOfPoints* retourne' doit etre detruit par l'appelant !
    CATMathSetOfPoints* NSubdivisions();

    // Calcul effectif de la longueur du nouveau polygone de controle, ou d'une partie
		// Retourne -1 si calcul impossible (si iIndexSecondPt<iIndexFirstPt)
    double ComputeLength(CATMathSetOfPoints* CP, CATLONG32& iIndexFirstPt, CATLONG32& iIndexSecondPt);

    // Methodes pour calculer les coeff du triangle de Pascal
    CATLONG32 PascalTriangle(int iN, int iI);
    void FillTriangle();

		// to enable 3D-distance computation for PCurves 
		void SetSupportEquations(CATMathFunctionXY* supportXGlobalEquation,
														 CATMathFunctionXY* supportYGlobalEquation,
												     CATMathFunctionXY* supportZGlobalEquation);
  private :
		CATMathSetOfPoints* _InitialControlPoints;
		CATMathSetOfPoints* _FinalCtlPts;
		CATMathSetOfPoints*  _FinalBasicControlPoints;
		CATLONG32                _degree;
		static int          _TriangleSize;
		static CATLONG32         _PascalTriangle[CATMaxDegree][CATMaxDegree];
		CATBoolean          _GetCalled;
    CATLONG32                _NbSubd;

		CATLONG32 _iDimCrv;

		CATMathFunctionXY* _supportXGlobalEquation;
		CATMathFunctionXY* _supportYGlobalEquation;
		CATMathFunctionXY* _supportZGlobalEquation;
};
#endif
