#ifndef CATCGMGraph_H
#define CATCGMGraph_H
//---------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2002
//---------------------------------------------------
#include "ExportedByGeometricObjects.h"
#include "CATCGMVirtual.h"
#include "CATCGMArrayOfOrientedObjects.h"
#include "CATCGMArrayManagement.h"
#include "CATBoolean.h"

class CATICGMObject;
class CATICGMUnknown;
class CATHashTabCATCXGraphNode;
class CATCGMTempoULONGPTR;
class CATGeoFactory;
class CATCXGraphNode;

#define CATCGMGraphCreate_Direct                          0x00000001
#define CATCGMGraphCreate_Inverse                         0x00000002

#define CATCGMGraphCreate_Default (CATCGMGraphCreate_Direct | CATCGMGraphCreate_Inverse )

//--------------------------------------------------------------------
// Graphe bi-directionnel
//   pour gestion native de liens inverses
//--------------------------------------------------------------------
class  ExportedByGeometricObjects CATCGMGraph  : public CATCGMVirtual
{
public:

  //----------------------------------------------------------------------
  //  Creation d'un Graphe 
  //----------------------------------------------------------------------
  static CATCGMGraph * Create(const unsigned int           iGraphSpecs      =  CATCGMGraphCreate_Default,
                              const CATCGMArrayManagement  iNodeManageNode  = CATCGMArrayManagement_DuplicationAuthorized, 
                              const CATGeometricType       iNodeControlType = CATUnknownGeometryType);

  void BuildGraph(CATICGMUnknown *iRoots);

  inline CATBoolean  IsMultipleSameArc() const;
  inline void        SetMultipleSameArc(CATBoolean iMulipleSameArc); 

  //--------------------------------------------------------------------------------
  //  DEFINE :  PERFO
  //--------------------------------------------------------------------------------
  CATGeoFactory* IsDedicatedToFactory() const;
  void           DedicateToFactory(CATGeoFactory *iFactory);

  //--------------------------------------------------------------------------------
  //  DEFINE :  Preparation pour Perfo (estimation du nombre d'arcs directs)
  //--------------------------------------------------------------------------------
  void EstimateDirectArcs(CATICGMObject *iFrom, const int iNbDirectArcs );

  //--------------------------------------------------------------------------------
  //  DEFINE :  Ajout d'une definition d'Arc (ajout automatique des noeuds)
  //--------------------------------------------------------------------------------
  void AddArc(CATICGMObject *iFrom, CATICGMObject *iTo, const short iOrientation = 0 );

  //--------------------------------------------------------------------------------
  //  DEFINE :  Fin de definition des arcs en partance (cf IsNode)
  //--------------------------------------------------------------------------------
  void FreezeNode(CATICGMObject *iFrom);

  //--------------------------------------------------------------------------------
  //  DEFINE    :  Suppression de noeuds du graphe 
  //  PREREQ    :  Graphe DIRECT et INVERSE
  //--------------------------------------------------------------------------------
  void DelNodes(CATCGMArrayOfOrientedObjects &ioNodes);



  //-------------------------------------------------------------------------------
  //  ANALYSE   :  Parcours des sommets du graphe
  //    set iNode=0 to start analysis
  //-------------------------------------------------------------------------------
  void * NextNode(void * iNode) const;

  //-------------------------------------------------------------------------------
  //  ANALYSE   :  Analyse d'un sommet de graphe
  //-------------------------------------------------------------------------------
  int    GetNode(void                         *   iNode, 
                 CATICGMObject                * & oNode,
                 CATCGMArrayOfOrientedObjects *   ioDirectNodes,
                 CATCGMArrayOfOrientedObjects *   ioInverseNodes) const;

  //-------------------------------------------------------------------------------
  //  ANALYSE   :  Obtention des Arcs (du graphe inverse)
  //  PREREQ    :  Graphe INVERSE
  //-------------------------------------------------------------------------------
  void GetArcsReverse(CATICGMObject *iTo, CATCGMArrayOfOrientedObjects &ioNodes) const;
  
  //---------------------------------------------------------------------------------------
  //  ANALYSE :  Obtention des Noeuds (du graphe direct) n'ayant que des Arcs en partance
  //             Ce sont les racines du Direct.Acyclic.Graph
  //  PREREQ  :  Graphe INVERSE
  //---------------------------------------------------------------------------------------
  int GetStartingNodesDirect(CATCGMArrayOfOrientedObjects &ioNodes) const;
  
  //---------------------------------------------------------------------------------------
  //  ANALYSE :  Reconnaissance en tant que Noeuds d'un Objet
  //      0 inconnu
  //      1 reconnu sans definition figee
  //      2 reconnu avec definition figee
  //---------------------------------------------------------------------------------------
  short IsNode(CATICGMObject *iObj) const;

  //---------------------------------------------------------------------------------------
  //  ANALYSE :  statistiques globales ..
  //---------------------------------------------------------------------------------------
  void Statistics(int &ioNbNodes, int &ioDirectArcs, int &ioInverseArcs ) const;

  //----------------------------------------------------------------------
  //  Nettoyage du Graphe 
  //----------------------------------------------------------------------
  virtual ~CATCGMGraph();
  CATCGMNewClassArrayDeclare;  

protected :
  
  CATCGMGraph(const unsigned int           iGraphSpecs,
              const CATCGMArrayManagement  iNodeManageNode,
              const CATGeometricType       iNodeControlType);
  
  unsigned int _GraphSpecs;
  
  CATHashTabCATCXGraphNode *RequireNodeArcs();
  CATHashTabCATCXGraphNode *_NodeArcs;

  CATCGMArrayManagement _ArrayManagement;
  CATGeometricType      _ArrayControlType;

  CATGeoFactory         * _Factory;
  CATCGMTempoULONGPTR   * _PerfoFactory;

  friend class CATCXGraphNode;
  CATCXGraphNode        * _FirstNode;

  CATBoolean              _MultipleSameArcs;
};






inline CATBoolean  CATCGMGraph::IsMultipleSameArc() const
{ return _MultipleSameArcs; }

inline void  CATCGMGraph::SetMultipleSameArc(CATBoolean iMulipleSameArc) 
{_MultipleSameArcs = iMulipleSameArc; }


#endif
