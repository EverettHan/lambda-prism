// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
// Creation EDS  11/10/2001
//
// Classe d'interface de l'operateur de relimitation des elements d'un body
// (volumes, shells, wires et vertex in volume) a l'interieur/exterieur de
// volumes d'un second body.
//
// Retourne un body constitue des sous-parties du premier body dont la position
// vis-a-vis des volumes du second body (in, out, boundary) est conforme a la 
// selection specifiee au niveau de l'operateur.
//
// Le body a relimiter peut-etre multi-domaine et heterogene (domaines de 
// differents types, lump et shell par exemple) mais il doit etre resolu
// (les intersections entre domaines doivent etre resolues).
//
// Tous les elements du body a relimiter sont decoupes par les volumes du
// body solide. Les sous-elements crees sont ensuites positionnes si 
// necessaire et selectionnes vis-a-vis du type de selection. Un sous-element
// (volume, shell, wire, vertex in volume) est positionne soit:
//   - OUT     : il est exterieur a tous les volumes du body solide,
//   - IN      : il est interieur a un unique volume du body solide,
//   - BOUNDARY: il est en confusion avec la peau d'un unique volume du body solide,
//
// Le type de selection est une combinaison des trois positions possibles:
// InsideVolume (IN), OutsideVolume (OUT), OnVolumeBoudnary (BOUNDARY).
// Si "type de selection"=InsideVolume, le body resultat sera constitue
// uniquement des sous-elements interieurs aux volumes.
// Si "type de selection"=InsideVolume|OnVolumeBoudnary, le body resultat sera 
// constitue des sous-elements interieurs aux volumes et des sous-elements
// poses sur les volumes.
// Dans le cas d'un type de selection constitue de plusieurs valeurs, les
// sous-elements peuvent etre fusionnes dans le resultat.
// Le type de selection OnVolumeBoudnary n'a pas de sens pour les sous-elements
// de type volume qui ne sont evidemment que IN ou OUT.
//
//=============================================================================

#ifndef __CATTopRelimitByVolume_h__
#define __CATTopRelimitByVolume_h__

/**
 * @level Protected
 * @usage U1
*/

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATTopRelimitByVolumeSelectionType.h"

class CATTopRelimitByVolumeContextForFastRun;

/**
* Operator to trim a shell or a wire by a volume.
* The generated result is made up of the portions of the input shell or wire which are
* inside or outside the input volume. <br>
* The body to be trimmed can be a multi-domain body. The domains making up the input body do 
* not have necessarily to be of the same type. For example, the input body can contain a mixture of shells
* and lumps.<br>
* All the cells of the input body are trimmed by the volume and the portions to be kept
* are to be specifed by using the <tt>SetSelectionType</tt> method. Resulting sub-elements
* can be merged.
* <p>
* The CATTopRelimitByVolume operator is not streamable. 
* <p>
* The CATTopRelimitByVolume operator is a multi-run operator: <br>
* the methods to set parameters as well as the <tt>Run</tt> and <tt>GetResult</tt> methods
* can be called several times from the same operator.
*  @param iFactory
* A pointer to the factory of the resulting body. 
* @param iTopData
* A pointer to the topological data.
* @param iBodyToRelimit
* A pointer to the body to be trimmed or relimited.
* @param iSolidBody
* A pointer to the solid used as trimming object.
* @return [out, IUnknown#Release]
*/
class ExportedByCATTopologicalObjects CATTopRelimitByVolume: public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopRelimitByVolume);
   public:

      enum SelectionType
      {	
         None             = CATTopRelimitByVolumeSelTypeNone,
         InsideVolume     = CATTopRelimitByVolumeSelTypeInsideVolume,
         OutsideVolume    = CATTopRelimitByVolumeSelTypeOutsideVolume,
         OnVolumeBoundary = CATTopRelimitByVolumeSelTypeOnVolumeBoundary
      };

   protected:

      //============================
      // Constucteur et destructeurs
      //============================

      CATTopRelimitByVolume(CATGeoFactory * iFactory, CATTopData * iTopData, CATExtTopOperator * iExtensible = NULL);      

   public:

      virtual ~CATTopRelimitByVolume();


      //===========================================
      // Methodes de parametrisation de l'operateur
      //===========================================

  /**
   * @nodoc
   */
      virtual CATBoolean GetCheckJournal()  const = 0;

  /**
   * Retrieves the type of selection (inside, outside or boundary)
   * @return
   * <ul>
   *   <li> 0 - no result is generated
   *   <li> 1 - the skin which is inside the volume is kept
   *   <li> 2 - the skin which is outside the volume is kept
   *   <li> 3 - all the sub-elements are kept
   *   <li> 4 - the skin which is on the volume boundary is kept
   * </ul>
   */
     virtual CATLONG32       GetSelectionType() const = 0;

  /**
   * @nodoc
   */
      virtual void       SetCheckJournal(CATBoolean iCheckMode) = 0;

  /**
   * Specifies the portions of the input body to be kept.
   * @param
   * <ul>
   *   <li> 0 - no result is generated
   *   <li> 1 - the skin which is inside the volume is kept
   *   <li> 2 - the skin which is outside the volume is kept
   *   <li> 3 - all the sub-elements are kept
   *   <li> 4 - the skin which is on the volume boundary is kept
   * </ul>
   */
      virtual void       SetSelectionType(CATLONG32 iSelectionType)  = 0;

      //===========================================
      // Fast Update Services
      //===========================================

  /**
   * @nodoc
   * Returns the context for fast run specific of CATTopRelimitByVolume operator.
   * @param iGetOnly
   * If FALSE and context doesn't exist, it is created.
   * @return
   * The context for fast run.
   */
      virtual CATTopRelimitByVolumeContextForFastRun * GetTopRelimitByVolumeContextForFastRun(CATBoolean iGetOnly = FALSE) = 0;
      
      //======================================
      // Methodes specifiques a CATTopOperator
      //======================================

  /**
   * Runs the operator.
   */
	   virtual int Run() = 0;
      
  /**
   * Retrieves the trimmed result.
   * @param ioJournal
   * The journal of operations
   * @return
   * The generated result.
   */
      virtual CATBody * GetResult(CATCGMJournalList * ioJournal) = 0;
};

#endif

