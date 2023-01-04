#ifndef CATIntersectionCheckDiagnosis_h_
#define CATIntersectionCheckDiagnosis_h_

// COPYRIGHT DASSAULT SYSTEMES 2006
//===========================================================================================
// 24/07/2015  G5S  Create read, write and validate functions so we can have a CGMReplay of 
//                  CATCXFaceBoundaryIntersectionChecker.
//===========================================================================================

#include "CATGMModelInterfaces.h"
#include "CATCheckDiagnosis.h"

class CATCXDomain;
class CATCXTopology;
class CATCell;
class CATDomain;
class CATTopology;

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

// Enumeration des types d'intersections invalides
enum CATCheckDiagnosisLocation
{
   CATUnknownDiagnosisLocation,
   CATPointSolutionIntersectionLocation,           // Solution Point resultat d'un face/face
   CATInteriorInteriorIntersectionLocation,        // Interieur/interieur resultat d'un arete/arete ou d'un face/face
   CATInteriorExtremityIntersectionLocation,       // Bord/interieur resultat d'un arete/arete
   CATExtremityInteriorIntersectionLocation,       // Interieur/bord resultat d'un arete/arete
   CATExtremityExtremityIntersectionLocation,      // bord/bord resultat d'un arete/arete
   CATMixedSolutionIntersectionLocation,           // Solution mixte resultat d'un arete/arete ou d'un face/face
   CATConfusionIntersectionLocation,               // Confusion resultat d'un arete/arete ou d'un face/face
   CATFirstIncludedConfusionIntersectionLocation,  // Confusion resultat d'un arete/arete avec inclusion de la 1ere edge ds la zdc
   CATSecondIncludedConfusionIntersectionLocation, // Confusion resultat d'un arete/arete avec inclusion de la 2eme edge ds la zdc
   CATBothIncludedConfusionIntersectionLocation    // Confusion resultat d'un arete/arete avec inclusion des 2 edge ds la zdc
};



class ExportedByCATGMModelInterfaces CATIntersectionCheckDiagnosis: public CATCheckDiagnosis
{
public:
  /**
   * Constructor
   */
  CATIntersectionCheckDiagnosis();

  /**
   * Destructor
   */
  virtual ~CATIntersectionCheckDiagnosis();

  //==========================
  // Acces aux donnees membres
  //==========================
  virtual CATCheckDiagnosisLocation GetCheckDiagnosisLocation() const = 0;

  virtual const char *GetCheckDiagnosisLocationAsString() const = 0;

  //	Retourne les deux domains (shell/wire) auquels appartiennent les deux topologies confrontées.
  virtual void GetIntersectedDomains(
    CATDomain *&oFirstDomain,
    CATDomain *&oSecondDomain) const = 0;

  //=================================
  // Methodes virtuelles
  //=================================
  // Retourne les deux topologies dont la confrontation a donné naissance au diagnostic
  virtual void GetIntersectedCells(
    CATCell *&oFirstCell,
    CATCell *&oSecondCell) const = 0;

  virtual void Dump(CATCGMOutput &iOutput) const = 0;

  virtual const char *ClassName() const = 0;

  virtual int IsATypeOf(unsigned int iTypeReference) const = 0;

  virtual unsigned int GetType() const = 0;
};

#endif /* CATIntersectionCheckDiagnosis_h_ */
