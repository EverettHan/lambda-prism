/* -*-C++-*- */
#ifndef CATPropagationEdge_H
#define CATPropagationEdge_H

// COPYRIGHT DASSAULT SYSTEMES 1998
//-----------------------------------------------------------------------------
//
// CATPropagationEdge
// ------------------
// Definition d'une classe pour la propagation d'une edge pour donner 
//  une Super-Arete
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Fevrier 98    Creation                                Florent Langrognet  
// Mars    98    Ajout de la creation du wire            jgd
// May     98    Redescente dans NewTopologicalObjects   rad
// Sept.   98    Prise en compte de la propagation manuelle flt
//-----------------------------------------------------------------------------

#include "ListPOfCATEdge.h"
#include "YI00IMPL.h"
#include "CATTopDef.h"
#include "CATBody.h"
#include "CATCGMNewArray.h"

class CATBody;
class CATShell;
class CATWire;
class CATEdge;
class CATFace;
class CATVertex;;
class CATCrvParam;


class ExportedByYI00IMPL CATPropagationEdge
{
  public :

  //--------------------------------------------------------------------------
  // Constructor
  // -----------
  // iBody            : Body sur lequel on effectue la propagation 
  // iShell           : Shell sur lequel on effectue la propagation
  // iInitEdge        : Edge initialisant la propagation
  // iPropagationType : Type de propagation (manual ou auto)
  //---------------------------------------------------------------------------
  CATPropagationEdge(CATBody * iBody, CATShell * iShell,  CATEdge * iInitEdge,
                     CATBody::CATPropagationTypePr3 iPropagationType = CATBody::CATEdgePropagAuto);

  CATPropagationEdge();  
  CATPropagationEdge(CATPropagationEdge* SA); 

  //--------------------------------------------------------------------------
  // destructor
  //---------------------------------------------------------------------------
  virtual ~CATPropagationEdge();

  CATCGMNewClassArrayDeclare;

  //--------------------------------------------------------------------------
  // Run
  // ---
  //---------------------------------------------------------------------------
  void Run();


  //--------------------------------------------------------------------------
  // GetResult
  // -------------
  //---------------------------------------------------------------------------
  void      GetResult(ListPOfCATEdge & oMacroEdge);
  CATWire * GetResult(CATBody * iCreationBody); 
  CATTopSharpness GetSharpness();



    public:
                
  void AddFirstEdge(CATBody* Body,CATEdge * iEdge,CATBody::CATPropagationTypePr3 iPropagationType, 
                    CATShell *iShell=NULL);
  void AddFirstEdge(CATEdge * iEdge);
  void SetPropagationType(CATBody::CATPropagationTypePr3  iPropagationType);

  // fonctions concernant la propagation de la SA
  int  AddEdge(CATEdge * iEdge, int oPlace=2); // oPlace indique si on veut effectuer 
  // l'insertion en fin ou début de Sa.
  // Cet argument n'est pris en compte que si l'edge que l'on rajoute
  // peut etre place indifferement en fin ou debut de la SA. (0==debut,1==fin) 
  int  StepPropagation(int direction);
  void SetBody(CATBody* iBody);
  void SetShell(CATShell* iShell);
  void InitShell();
  // definition d'edges "rolling" qui permettent de forcer la propagation
  void SetRollingEdges(ListPOfCATEdge* iRollingEdges) ;

  //fonctions d'acces
  CATEdge * getEdgeAt(int* pos); //la valeur pos est ecrasee par le flag d'orientation de l'edge 
  CATVertex * getStartVertex();
  CATVertex * getEndVertex();

  ListPOfCATEdge * getListOfEdge() ;
  ListPOfCATFace * getListOfFace1();
  ListPOfCATFace * getListOfFace2();
  CATListOfInt   * getListOfOrientation();
  CATBody * getBody();
  CATShell * getShell();

  CATBody::CATPropagationTypePr3  getPropagationType();
  int	 Size();
	
  // surcharge d'operateur
  CATPropagationEdge& operator=(const CATPropagationEdge &SA);
  operator ListPOfCATEdge*() {return _ListOfEdge; }

  void                     Remove (CATEdge *iedge); 
  
  static CATBoolean CurvaturePermitsRelimitation(double iCurveCandidate, double iCurveFrom, CATGeoFactory* iFactory);

protected :

  // fonctions modifiant les donnees membre ?
  void	 SetListOfEdge(ListPOfCATEdge* iLedge) ;
  void	 SetListOfFace1(ListPOfCATFace* iLface) ;
  void	 SetListOfFace2(ListPOfCATFace* iLface) ;
  void	 SetListOfOrientation(CATListOfInt* iLorient) ;
  void   SetSharpness (CATTopSharpness & Sharp);




//  private
//  -------
  private :
  
  void            MarquageEdge(CATEdge * iEdge);
  //  void            MarquageVertex(CATVertex * iVertex, int iAtt);
  void            RetireAttribut();
  
  void GetNextEdgeOnSA(CATVertex * iVertex,
                       CATEdge * iEdge,
                       CATEdge *& oEdge);

  //  void AddEdge();

  int _KeyAttMarqEdge;
  int _AttMarqEdge;
  //  int _KeyAttMarqVertex;
  //  int _AttStartVertex;
  //  int _AttEndVertex;
 

  CATBody::CATPropagationTypePr3 _PropagationType;
  CATTopSharpness _SharpnessOfSA;
  //  CATEdge * _CurEdgeOnSA;
  //
  //  CATFace * _AdjFaceOfCurEdgeOnSA[3];
  CATBody * _Body;
  CATShell * _Shell;
  CATWire  * _Wire;
  //
  // attributs ajoutes du CATExtendedmacroEdge
  ListPOfCATEdge * _ListOfEdge;
  ListPOfCATFace * _ListAdFace1;
  ListPOfCATFace * _ListAdFace2;
  CATListOfInt   *_ListOfOrientationFlag;
 
  ListPOfCATEdge * _ListOfRollingEdges;

};




#endif
