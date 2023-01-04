/**
 * @COPYRIGHT DASSAULT SYSTEMES 2001
 * @fullReview  HCN 01:12:10
*/

/* -*-C++-*- */
#ifndef CATCGMVisuData_H
#define CATCGMVisuData_H

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2001
// DESCRIPTION : Structures and Methods for topology/visualization interactions
//
// Nov. 01	Creation                                                     HCN
// Jan. 02  Supression du renvoie des bounded cells                      HCN
// Jan. 03  MASK_FORCE_GEOMETRIC_EVALUATION,
//          parametre iMinSharpAngle pour CATCGMGetVisuData(...)         HCN
// Jun. 05  Ajout de Side et IsInVolume (pour les faces)          
//          et migration de CGMVisuData sur CATCell                      FDN
// Dec. 05  Ajout des structures stockees pour les vertices              FDN
//=============================================================================

#include "CATDataType.h"
#include "CATGMModelInterfaces.h"
#include "CATTopDefine.h"
#include "CATBoolean.h"
#include "CATMathConstant.h"

class CATCell;
class CATVertex;
class CATEdge;
class CATFace;
class CATBody;

#define MASK_NB_BOUNDED_CELLS		        0x00000001 // bit 0
#define MASK_CONTINUITY				          0x00000002 // bit 1
#define MASK_SIDE       			          0x00000004 // bit 2
#define MASK_ISINVOLUME 			          0x00000008 // bit 3
#define MASK_SHARPNESS_CONNECT_CHECKER  0x00000010 // bit 4
#define MASK_HIDDEN_SEAM  		          0x00000020 // bit 5
#define MASK_FORCE_GEOMETRIC_EVALUATION 0x00008000 // bit 15

//-------------------------------------------------------------------------------------------
// Structure utilisee pour renvoyer des resultats par CATCGMGetVisuData
//-------------------------------------------------------------------------------------------
struct CATCGMVisuData
{
	CATLONG32				        NbBoundedCells;     // Pour les edges et les vertices seulement
	CATTopGeoContinuity	    Continuity;         // Pour les edges et les vertices seulement
                                              // IMPORTANT : Par definition (specs visu), on est Sharp des qu'il y a plus que 2 bordantes
  CATBoolean              ContinuityIsStored; // Pour les edges seulement et les vertices seulement
  CATSide                 Side;               // Pour les faces seulement
  CATBoolean              IsInVolume;         // Pour les faces seulement
	CATBoolean              IsHiddenSeamCell;   // Pour les vertex et edges seulement
  // Tableau alloue et rempli seulement si on active le masque MASK_NB_BOUNDED_CELLS
  // et si NbBoundedCells (sa taille) est non null
  // WARNING : Il faut toujours tester l'existance du tableau avant utilisation.
  // WARNING : Ne jamais faire de delete de ce tableau, il est fait lors de la destruction de la structure interne
  CATCell **              BoundedCells;       // Pour les edges et les vertices seulement
};

//-------------------------------------------------------------------------------------------
// Ces methodes permettent de recuperer des infos pour ipEdge ou ipFace dans le contexte de ipBody :
//
// Les donnees a renvoyer sont selectionnees par RequestedDataMask qui peut etre une
// combinaison de
//              MASK_NB_BOUNDED_CELLS      (nombre de faces bordees par l'edge)
//              MASK_CONTINUITY            (continuite de cette cellule par rapport aux deux premieres faces (CATSharp ou CATSmooth))
//              MASK_SIDE                  (side de la face dans son body)
//              MASK_ISINVOLUME            (indique si la face est dans un volume ou non)
//
//              MASK_FORCE_GEOMETRIC_EVALUATION => on ne tient pas compte des informations deja stockees
//
// Le resultat est renvoye dans la structure iopCGMVisuData vierge passee en entree.
//
// Remarques : 
//
//    1) Dans un but d'optimisation, le resultat est stocke au niveau de la cellule, relativement
//       a un body, si la cellule et le body sont GELES.
//
//    2) Toute donnee recalculee par rapport a un autre body remplace la precedente.
//
//-------------------------------------------------------------------------------------------

// return TRUE if the VisuData has been calculated, FALSE if it has been only read
ExportedByCATGMModelInterfaces CATBoolean CATCGMGetVisuData(CATVertex*      ipVertex,
											                         CATBody*        ipBody,
											                         CATCGMVisuData* iopCGMVisuData,
											                         unsigned int    RequestedDataMask,
                                               CATAngle        iMinSharpAngle = CATTopSharpAngle);


// return TRUE if the VisuData has been calculated, FALSE if it has been only read
ExportedByCATGMModelInterfaces CATBoolean CATCGMGetVisuData(CATEdge*        ipEdge,
											                         CATBody*        ipBody,
											                         CATCGMVisuData* iopCGMVisuData,
											                         unsigned int    RequestedDataMask,
                                               CATAngle        iMinSharpAngle = CATTopSharpAngle);

// return TRUE if the VisuData has been calculated, FALSE if it has been only read
ExportedByCATGMModelInterfaces CATBoolean CATCGMGetVisuData(CATFace*        ipFace,
											                         CATBody*        ipBody,
											                         CATCGMVisuData* iopCGMVisuData,
											                         unsigned int    RequestedDataMask);

//-------------------------------------------------------------------------------------------
// Provoque la destruction immediate de toutes les donnees temporaires de visu portee par les
// cellules d'un body.
// (Par defaut, cette destruction ne serait faite que lors de la destruction des cellules).
// iDimension : dimension des cellules a nettoyer
//              -1 : defaut (toutes)
//               0 : vertices seulement
//               1 : edges seulement
//               2 : faces seulement
//-------------------------------------------------------------------------------------------
ExportedByCATGMModelInterfaces void CATCGMDeleteAllVisuData(CATBody*  ipBody,
                                               int       iDimension = -1);
#endif
