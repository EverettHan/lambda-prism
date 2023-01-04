/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2001
//===========================================================================
// Class CATCGMSharpnessData
//---------------------------------------------------------------------------
// Structure pour marquage logique de la vivicite des edges/vertices
//---------------------------------------------------------------------------
// oct. 01   Creation                                        H. Chhoun (HCN)
// fev. 02   Supression des donnees membres Redressement et
//           CATCrvParam dans la classe CATCGMSharpnessData  HCN
// fev. 02   Creation des classes CATCGMSharpnessDataEdge et
//           CATCGMSharpnessDataVertex derivants de
//           CATCGMSharpnessData                             HCN
// jan. 06   Ajout de l'indication "SecondInverted" pour les edges
//           Protection des donnees par methodes d'acces
//           Nettoyages diverse                              FDN
//===========================================================================

#ifndef CATCGMSharpnessData_H
#define CATCGMSharpnessData_H

#include "ExportedByCATGeometricObjectsCGM.h"
#include "CATDataType.h"
#include "CATMathConstant.h"
#include "CATGeoDef.h"
#include "CATBoolean.h"
#include "CATCGMVirtual.h"
#include "CATMathInline.h"

class CATCGMObject;
class CATCGMOutput;

// #define TRACES_SHARPNESS

#ifdef TRACES_SHARPNESS
	extern ExportedByCATGeometricObjectsCGM int CATSharpnessDataTracesOn;

	#define TRACES_BEGIN if (CATSharpnessDataTracesOn) {
	#define TRACES_END }
#endif


//--------------------------------------------------------------------
class ExportedByCATGeometricObjectsCGM CATCGMSharpnessData : public CATCGMVirtual
{
public:
    //----------------------------------------------------------------------
    // Constructor / Destructor
    //----------------------------------------------------------------------
  CATCGMSharpnessData(CATCGMObject*		 ipMainCGMObject,
						          CATCGMObject*		 ipBoundedCGMObject1,
                      CATCGMObject*		 ipBoundedCGMObject2,
                      CATAngle			   iMinSharpAngle,
                      CATGeoContinuity iContinuity, // en rad
                      const char*      iClassName);

	CATCGMSharpnessData(const CATCGMSharpnessData& iToCopy);

  virtual ~CATCGMSharpnessData();

  const char* IsA() const;

  virtual void Dump(CATCGMOutput& os, CATBoolean All = TRUE) = 0;

  static size_t GetEstimatedMemoryBytesForMainCGMObject(CATCGMSharpnessData* pSharpnessData);


	void DeleteForMainCGMObject();
	void DeleteForBoundedCGMObject(CATCGMObject* ipBoundedCGMObject);
	void DeleteWithBoundedCGMObjectForMainCGMObject(CATCGMObject* ipBoundedCGMObject);

	CATCGMSharpnessData* NextForMainCGMObject();
	CATCGMSharpnessData* NextForBoundedCGMObject(CATCGMObject* ipBoundedCGMObject);

  // methode de comparaison
  virtual CATBoolean IsSameContext(CATCGMSharpnessData* ipSharpnessData) = 0;

  // methode interne de comparaison
  // ipBoundedCGMObject1 iSide1 : objet borde 1 et son TopoGeo side (voir ci-dessous pour la definition du side)
  // ipBoundedCGMObject2 iSide2 : objet borde 2 et son TopoGeo side
  // iSecondInverted : Indique si la seconde face a ete artificiellement retournee pour etre vue "right"
  //                   =1 si retournee, =0 si inconnu, =2 si non retournee
	virtual CATBoolean IsEquivalentBoundingContext(CATCGMObject*	ipBoundedCGMObject1,
                                  	  					 CATCGMObject*	ipBoundedCGMObject2,
                                                 CATBoolean		  iOneBoundedCGMObjectMayBeNULL,
                                                 short          iSecondInverted) = 0;

  static void CATDeleteSharpnessDataForMainCGMObject(CATCGMSharpnessData* pSharpnessDataToDelete);

	// La cellule dont on cherche la continuite (Edge ou Vertex...)
	CATCGMObject*			_pMainCGMObject;

	// Les CATCGMObject decrivant les cellules bordees par _pMainCGMObject dans
  // Dans le cas de la vivicite sur edge :
  // - CATPCurveCGM*
  // Dans le cas de la vivicite sur vertex :
  // - CATCXEdge*
	//
	// Dans le cas de la vivicite sur edge des sides sont a prendre en compte (voir CATCGMSharpnessDataEdge)
	CATCGMObject*			_pBoundedCGMObject1; 
	CATCGMObject*			_pBoundedCGMObject2;
 

	CATAngle				  _MinSharpAngle; // en rad

	CATGeoContinuity		_Continuity; // short

	CATCGMSharpnessData*	_pNextForMainCGMObject;
	CATCGMSharpnessData*	_pNextForBoundedCGMObject1;
	CATCGMSharpnessData*	_pNextForBoundedCGMObject2;

 	CATULONG32  CountForBoundedCGMObject(CATCGMObject* ipBoundedCGMObject);

  const char* _pClassName;

  static void SetNoStoreOnFrozenTopology(CATBoolean iValue);

  static INLINE CATBoolean NoStoreOnFrozenTopology()
  {
    return _NoStoreOnFrozenTopology;
  }

protected :

  static CATBoolean _NoStoreOnFrozenTopology;
};

#endif
