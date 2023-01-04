/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2002
//===========================================================================
// Class CATCGMSharpnessDataVertex
//---------------------------------------------------------------------------
// Structure pour marquage logique de la vivicite des edges
//---------------------------------------------------------------------------
// fev. 02   Creation des classes CATCGMSharpnessDataVertex et
//           CATCGMSharpnessDataVertex derivants de
//           CATCGMSharpnessData                                          HCN
// jan. 06   Ajout de l'argument iSecondInverted a 
//           IsEquivalentBoundingContext                                  FDN
//===========================================================================

#ifndef CATCGMSharpnessDataVertex_H
#define CATCGMSharpnessDataVertex_H

#include "CATCGMSharpnessData.h"
#include "CATCGMNewArray.h"

//--------------------------------------------------------------------
class ExportedByCATGeometricObjectsCGM CATCGMSharpnessDataVertex : public CATCGMSharpnessData
{
public:
	CATCGMNewClassArrayDeclare; // Surchage CGM du new/delete
  //----------------------------------------------------------------------
  // Constructor / Destructor
  //----------------------------------------------------------------------
	CATCGMSharpnessDataVertex(CATCGMObject*		 ipVertex,
						                CATCGMObject*		 ipEdge1,
                            CATCGMObject*		 ipEdge2,
                            CATGeoContinuity iContinuity,
                            CATAngle			   iMinSharpAngle); // en rad

	CATCGMSharpnessDataVertex(const CATCGMSharpnessDataVertex& iToCopy);

  virtual ~CATCGMSharpnessDataVertex();

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
  // Methode specifiques de CATCGMSharpnessDataVertex
  //----------------------------------------------------------------------

  //----------------------------------------------------------------------
  // Les donnees propres a la vivicite des vertices
  //----------------------------------------------------------------------
  CATBoolean _AlreadyCloned;
};

#endif
