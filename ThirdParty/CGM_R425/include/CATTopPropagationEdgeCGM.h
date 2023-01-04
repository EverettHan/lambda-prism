/**
 * @COPYRIGHT DASSAULT SYSTEMES 2001
 * @fullReview  HCN 02:01:11
 */

/* -*-C++-*- */

#ifndef __CATTopPropagationEdgeCGM_H__
#define __CATTopPropagationEdgeCGM_H__

// COPYRIGHT DASSAULT SYSTEMES 2002

//=============================================================================
// Operator for edge tangency propagation on a body as a replacement for the
// following CATBody method :
//
// virtual CATLISTP(CATCell) CATEdgePropagate(CATLISTP(CATCell) * iInitialEdges,
//                              CATPropagationTypePr3 iPropagationType,
//                              CATLISTP(CATEdge) * iRollingEdges = NULL) = 0;
// Cf. CATCreatePropagationEdge.h
//
//=============================================================================
// Jan. 02  Creation                                                      HCN
// Oct. 02  Propagation on wires                                          HCN
// Feb. 03  Correction PropagateEdgeOnWire(...) pour wire ferme           HCN
// Aout 2003    Ajout methode DumpInterne                                 CBK
// Feb 2012 Get average angle                                             UVC
//=============================================================================


#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "CATTopPropagationEdge.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "CATTopDef.h"
#include "CATBody.h"
#include "CATListOfInt.h"
#include "CATListOfDouble.h"

class CATGeofactory;
class CATTopData;
class CATShell;
class CATEdge;
class CATFace;
class CATVertex;;
class CATCrvParam;

class CATUnicodeString ;
class CATString ;

class ExportedByCATTopologicalObjects CATTopPropagationEdgeCGM: public CATTopPropagationEdge
{

  public :
    //============================
    // Constucteur et destructeurs
    //============================

    CATTopPropagationEdgeCGM(CATGeoFactory * iFactory,
                             CATTopData * iTopData,
                             CATBody * iBody,
                             CATLISTP(CATCell) * iInitialEdges,
                             CATBody::CATPropagationTypePr3 iPropagationType,
                             CATLISTP(CATEdge) * iRollingEdges);

    virtual ~CATTopPropagationEdgeCGM();

    //=============================================
    // Methodes specifiques a CATTopPropagationEdge
    //=============================================

    void GetResultListEdges(CATLISTP(CATCell) & ioListEdges);

    void SetRollingEdges(CATLISTP(CATEdge) * iRollingEdges);

    void SetSameConvexityRollingEdges(); // Default is False (Same convexity rolling edges are not considered as rolling edges)

    void AllowPropagationOnDifferentConvexity(); // Default is False (propagation is only allowed on edges whose convexity is same as SA)

    void SetPropagationType(CATBody::CATPropagationTypePr3  iPropagationType);

    void SetBody(CATBody* iBody);

    void SetShell(CATShell* iShell);

    //
    // @nocgmitf
    //
    void SetStoppingFaces( const ListPOfCATFace &iListStopFace );

    //=========================================================
    // Pour compatibilite d'utilisation avec CATPropagationEdge
    //=========================================================

    void InitShell();

    // oPlace indique si on veut effectuer 
    // l'insertion en fin ou début de Sa.
    // Cet argument n'est pris en compte que si l'edge que l'on rajoute
    // peut etre place indifferement en fin ou debut de la SA. (0==debut,1==fin,2==edge ajouté) 
    int AddEdge(CATEdge * iEdge, int oPlace=2);

    void RemoveEdge(CATEdge *iEdge);

    virtual CATTopPropagationEdge* Clone();

    //fonctions d'acces
    ListPOfCATEdge* GetListOfEdge() ;

    ListPOfCATFace* GetListOfFace1();

    ListPOfCATFace* GetListOfFace2();

    CATListOfInt* GetListOfOrientation();

    CATVertex* GetStartVertex();

    CATVertex* GetEndVertex();

    CATBody* GetBody();

    CATShell* GetShell();

    CATBody::CATPropagationTypePr3 GetPropagationType();

    CATTopSharpness GetSharpness();

    CATAngle GetAverageSharpnessAngle( CATEdge * iEdge = 0 );

    //Used to get Min, Max and Avg Sharpness Angles and corresponding CrvParams
    //To be called before Run
    void RequestDetailedInfoAboutSharpnessAngles();
    //To be called After Run
    void GetDetailedInfoAboutSharpnessAngles(CATListOfDouble &ioAngles, CATListOfDouble &ioCrvParams);

    // pour y voir qqchose 
    void DumpInterne( CATUnicodeString Commentaire ) ;

    /** @nodoc @nocgmitf */ 
    static const  CATString  *GetDefaultOperatorId();

  protected:
    //========================================================
    // Methodes d'execution et de resultats (INTERFACES)
    //========================================================

    int Run();

    int RunOperator();

    //========================================================
    // Methodes specifiques a CATTopPropagationEdgeCGM
    //========================================================

    friend ExportedByCATTopologicalObjects
      CATTopPropagationEdge* CATCreatePropagationEdge( CATGeoFactory * iFactory,
                                                       CATTopData * iTopData,
                                                       CATBody * iBody,
                                                       CATLISTP(CATCell) * iInitialEdges,
                                                       CATBody::CATPropagationTypePr3 iPropagationType,
                                                       CATLISTP(CATEdge) * iRollingEdges );

    //========================================================
    // Methode pour capture des inputs et outputs par l'infra 
    // générique
    //========================================================  
    /** @nodoc @nocgmitf */
    static  CATString  _OperatorId;
    /** @nodoc @nocgmitf */
    const  CATString  *GetOperatorId();
    /**  @nodoc @nocgmitf */
    void   RequireDefinitionOfInputAndOutputObjects();


    private:
    //================================
    // Donnees membres
    //================================
    CATBody*              _pBody;
    CATShell*             _pShell;

    CATLONG32             _RunNumber;            // Nombre de fois que la methode Run a ete appelee

    CATLISTP(CATCell)     _InitialEdges;
    CATLISTP(CATEdge)     _RollingEdges;
    CATBody::CATPropagationTypePr3 _PropagationType;
    CATBoolean            _SameConvexityRollingEdges; // Default: FALSE => SameConvexityRollingEdges are ignored
    CATBoolean            _AllowPropagationOnDifferentConvexity; // Default: FALSE => propagation is only allowed on edges whose convexity is same as SA

    CATLISTP(CATCell)     _ResultEdges;

    // from CATPropagationEdge

    void AddFirstEdge(CATBody* Body,CATEdge * iEdge,CATBody::CATPropagationTypePr3 iPropagationType, CATShell *iShell=NULL);
    void AddFirstEdge_internal(CATBody* Body,CATEdge * iEdge,CATBody::CATPropagationTypePr3 iPropagationType, CATShell *iShell=NULL);
    void AddFirstEdge(CATEdge * iEdge);
    int  StepPropagation(int direction);
    int  Size();

    //fonctions d'acces
    CATEdge* getEdgeAt(int* pos); //la valeur pos est ecrasee par le flag d'orientation de l'edge 
    CATVertex * getStartVertex();
    CATVertex * getEndVertex();


    CATBoolean CurvaturePermitsRelimitation(double iCurveCandidate, double iCurveFrom, CATGeoFactory* iFactory);

    CATTopGeoContinuity  EvalCommonVertexSharpness(CATEdge* ipEdge1, CATEdge* ipEdge2);

    void PropagateEdgeOnWireUp(CATEdge*           ipEdge,
                               CATWire*           ipWire,
                               CATLISTP(CATCell)& iResultEdgesToAppendTo);

    void PropagateEdgeOnWireDown(CATEdge*           ipEdge,
                                 CATWire*           ipWire,
                                 CATLISTP(CATCell)& iResultEdgesToAppendTo);

    void PropagateEdgeOnWire(CATEdge*           ipEdge,
                             CATWire*           ipWire,
                             CATLISTP(CATCell)& iResultEdges);
    //
    // @nocgmitf
    //
    INLINE CATBoolean HasStoppingFaces() const { return _StoppingFaces.Size() ? TRUE : FALSE; };

    //  private
    //  -------
  private :

    void RetireAttribut();

    void MarquageEdge(CATEdge* iEdge);

    void GetNextEdgeOnSA(CATVertex* iVertex,
                         CATEdge* iEdge,
                         CATEdge*& oEdge);

    int _KeyAttMarqEdge;
    int _AttMarqEdge;

    CATTopSharpness _SharpnessOfSA;

    CATAngle        _AverageAngleOfSA;
    CATListOfDouble _ListOfAngle;
    int             _NbAngles; // for lazy evaluation

    CATLISTP(CATEdge) _LocalResult;

    //  ListPOfCATEdge * _ListOfEdge; // Garde pour compatibilite avec CATPropagationEdge
    ListPOfCATFace   _ListAdFace1;
    ListPOfCATFace   _ListAdFace2;
    CATListOfInt     _ListOfOrientationFlag;

    CATListOfDouble _ListOfMinMaxAvgAngles, _ListOfMinMaxAvgParams;
	short           _CGMLevel;
    CATBoolean      _AdvancedInfoRequested;

    ListPOfCATFace   _StoppingFaces;
};

#endif
