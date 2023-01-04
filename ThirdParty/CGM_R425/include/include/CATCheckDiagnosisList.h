// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Creation NVT  21/02/2001
// 24/07/2015  G5S  Dump method changed because we have functionality for a CGMReplay of 
//                  CATCXFaceBoundaryIntersectionChecker, which uses diagnosis objects.
//
// Class de gestion de liste de diagnostics
//=============================================================================

#ifndef __CATCheckDiagnosisList_h__
#define __CATCheckDiagnosisList_h__

#include "CATDataType.h"
#include "CATUnicodeString.h"
#include "CheckOperators.h"
#include "CATListPOfCATCheckDiagnoses.h"

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATCheckDiagnosis;
class CATFace;
class CATWire;
class CATBody;
class CATGeoFactory;
class CATTopData;
class CATCGMOutput;

class ExportedByCheckOperators CATCheckDiagnosisList
{
    public: // Methodes a usage externe
     
    //============================
    // Constucteur et destructeurs
    //============================

    CATCheckDiagnosisList();

    ~CATCheckDiagnosisList();

    //==========================
    // Acces aux donnees membres
    //==========================
    CATLISTP(CATCheckDiagnosis) * GetDiagnosisList();
    CATLONG32                          GetNbDiagnoses() const;

    CATCheckDiagnosis   *NextDiagnosis();
    CATCheckDiagnosis   *CurrentDiagnosis();
    CATFace             *NextInvalidFace();
    CATFace             *CurrentInvalidFace();
    CATWire             *NextInvalidWire();
    CATWire             *CurrentInvalidWire();
    CATCheckDiagnosis   *NextFaceDiagnosis();
    CATCheckDiagnosis   *NextWireDiagnosis();
    
    void InitDiagnosis();
    void InitInvalidFace();
    void InitInvalidWire();

    //==========================
    // Methodes specifiques
    //==========================

    CATBoolean AddDiagnosis(CATCheckDiagnosis * iDiagnosis);
    CATBoolean MustDump();
    CATBoolean MustThrow();
    CATBoolean IsInvalid();
    CATBoolean HasInvalidGeometry();
  
    void       Dump(CATCGMOutput & iOutput) const;
    void       Dump(CATCGMOutput & iOutput, CATBoolean iOnlyMustDump) const;

    CATBody*   AutoIntersectFacesAndAdjFaces(CATGeoFactory* iFactory, const CATTopData & iData);

    protected: // Donnees membres

    CATLISTP(CATCheckDiagnosis) * _DiagnosisList;

    int       _MustDump;
    int       _MustThrow;
    int       _IsInvalid;

    int       _CurrentDiagnosisIndex;
    int       _CurrentInvalidFaceIndex;
    CATFace*  _CurrentInvalidFace;
    int       _CurrentInvalidWireIndex;
    CATWire*  _CurrentInvalidWire;
};

#endif
