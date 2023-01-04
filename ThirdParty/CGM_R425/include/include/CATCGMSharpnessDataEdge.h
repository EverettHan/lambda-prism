/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2002
//===========================================================================
// Class CATCGMSharpnessDataEdgeEdge
//---------------------------------------------------------------------------
// Structure pour marquage logique de la vivicite des edges
//---------------------------------------------------------------------------
// fev. 02   Creation des classes CATCGMSharpnessDataEdge et
//           CATCGMSharpnessDataVertex derivants de
//           CATCGMSharpnessData                                          HCN
// jan. 06   Ajout de l'argument iSecondInverted a 
//           IsEquivalentBoundingContext                                  FDN
//===========================================================================

#ifndef CATCGMSharpnessDataEdge_H
#define CATCGMSharpnessDataEdge_H

#include "CATCGMSharpnessData.h"
#include "CATCGMNewArray.h"

//--------------------------------------------------------------------
class ExportedByCATGeometricObjectsCGM CATCGMSharpnessDataEdge : public CATCGMSharpnessData
{
public:
	CATCGMNewClassArrayDeclare; // Surchage CGM du new/delete
  //----------------------------------------------------------------------
  // Constructor / Destructor
  // iMinSharpAngle is in rad
  //----------------------------------------------------------------------
	CATCGMSharpnessDataEdge(CATCGMObject*		 ipEdge,
						              CATCGMObject*		 ipPCurve1,
                          CATCGMObject*		 ipPCurve2,
                          CATGeoContinuity iContinuity,
                          CATGeoConvexity	 iConvexity,
                          CATAngle			   iMinSharpAngle,
                          short            iSecondInverted);

	CATCGMSharpnessDataEdge(const CATCGMSharpnessDataEdge& iToCopy);

  virtual ~CATCGMSharpnessDataEdge();

  //----------------------------------------------------------------------
  // Methode surchargees de CATCGMSharpnessData
  //----------------------------------------------------------------------
  void Dump(CATCGMOutput& os, CATBoolean All = TRUE);

  virtual size_t  GetStaticMemoryBytes() const;   
  
  virtual char* IsA() const;


  // methode de comparaison
  virtual CATBoolean IsSameContext(CATCGMSharpnessData* ipSharpnessData);

  // methode interne de comparaison
	CATBoolean IsEquivalentBoundingContext(CATCGMObject*	ipBoundedCGMObject1,
                           						   CATCGMObject*	ipBoundedCGMObject2,
                                         CATBoolean		  iOneBoundedCGMObjectMayBeNULL = FALSE,
                                         short          iSecondInverted=0);

  //----------------------------------------------------------------------
  // Methode specifiques de CATCGMSharpnessDataEdge
  //----------------------------------------------------------------------

  //----------------------------------------------------------------------
  // Les donnees propres a la vivicite des edges
  //----------------------------------------------------------------------
	CATGeoConvexity			_Convexity; // short

  // Info indiquant si la seconde face a ete retournee au moment du calcul de vivicite pour etre vue "right"
  // La premiere face est TOUJOURS condieree comme Left
  // (si on est dans un shell, on cherche celle qui est left, et on la met en premier. Sinon, on prend d'office la premiere
  // comme left dans un shell bidon, et on ajuste POUR LE CALCUL l'orientation de l'autre pour etre vue Right dans ce shell bidon)
  short _SecondInverted; // 0 si inconnu, 1 si la seconde face a ete retournee, 2 si elle n'a pas ete retournee


};
#endif
