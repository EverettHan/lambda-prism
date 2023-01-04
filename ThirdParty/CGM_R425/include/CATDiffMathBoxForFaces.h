// COPYRIGHT DASSAULT SYSTEMES 2011
//=============================================================================
// Creation OID  31/08/2011
//
// Operator comparing two faces and giving the mathbox including the differences between the two faces
// It has sense only if the two faces have some similarities, and are on a same
// geometric surface.
// Creation with a classical constructor.
// Deleting with the classical delete operator.
// Call Run, and then GetResultMathBox().
//=============================================================================

#ifndef __CATDiffMathBoxForFaces_h
#define __CATDiffMathBoxForFaces_h

#include "BOOPER.h"
#include "CATMathBox.h"
#include "ListPOfCATCell.h"

class CATGeoFactory;
class CATFace;
class CATPCurve;
class CATEdge;
class CATCrvParam;
class CATCGMHashTableWithAssoc;
class CATBody;
class CATPAD;

class ExportedByBOOPER CATDiffMathBoxForFaces
{

public: // Methodes a usage externe

   //============================
   // Constucteur et destructeurs
   //============================

   //-------------------------------------------------------------------------------------------------------
   // Surcharge du new/delete
   //-------------------------------------------------------------------------------------------------------
   // CATCGMNewClassArrayDeclare;

   CATDiffMathBoxForFaces(CATGeoFactory * iFactory,
                     CATFace       * iOldFace,
                     CATFace       * iNewFace);
   CATDiffMathBoxForFaces(CATGeoFactory * iFactory,
                  CATFace       * iOldFace,
                  CATFace       * iNewFace,
                  CATPAD        * iPAD);

   virtual ~CATDiffMathBoxForFaces();

   void Run();
   // virtual void        Dump(ostream& iOutput) const;
   // virtual CATCXBody * GetTopologicalResult();

   inline void SetOldFace( CATFace * iOldFace) { _OldFace = iOldFace;};
   inline void SetNewFace( CATFace * iNewFace) { _NewFace = iNewFace;};
   inline void SetPAD( CATPAD * iPAD) {_MyPAD = iPAD;};

   //====================================
   // Acces aux parametres de l'operateur
   //====================================

   inline CATFace * GetOldFace() const { return _OldFace;};
   inline CATFace * GetNewFace() const { return _NewFace;};
   inline CATPAD * GetPAD() const { return _MyPAD;};
   inline CATMathBox GetResultMathBox() const { return _ModificationMB;};

   //===========================================
   // Methodes de parametrisation de l'operateur
   //===========================================

   

   //==============================================
   // Methodes d'acces aux resultats de l'operateur
   //==============================================

   // VoB 
   inline CATCGMHashTableWithAssoc * GetPCurvesAndCellsHT() const { return _PCurvesAndCellsHT; };
   void SortEdgesByPCurves();


private: // Methodes a usage interne

   void Cleaner();
   // Methods for computing MathBoxes
   void CalculateModificationMathBox();
   int  SortAppearedAndDisappearedEdgesByPCurves();
   void CreateDiffEdgesInSamePCurve( CATPCurve * iPCurve, 
                                     ListPOfCATCell & iSortedConsecutiveEdges_1 , 
                                     ListPOfCATCell & iSortedConsecutiveEdges_2,
                                     short & ioListNotEnded);
   CATEdge * BuildDifferenceOfEdges( CATEdge * SupportEdge, 
                                     CATPCurve * iCommonPCurve, 
                                     const CATCrvParam & iLowerParam, 
                                     const CATCrvParam & iHigherParam);
   void CreateDifferenceEdges();
   // CATTopOperator              * GetTopOperator() const { return this->GetOperator(); }
   // CGMReplay
   /*
   virtual CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
   virtual void WriteInput(CATCGMStream  & ioStream);
   virtual void RequireDefinitionOfInputAndOutputObjects();
   virtual void Dump(CATCGMOutput& os);
   
   virtual void        WriteOutput(CATCGMStream &ioStream);
   virtual CATBoolean  ValidateOutput(CATCGMStream &Str, CATCGMOutput &os, int VersionNumber=1);
   virtual void        DumpOutput(CATCGMOutput& os);
   virtual void        DumpOutput(CATCGMStream &Str, CATCGMOutput &os, int VersionNumber=1);
   */


private: // Donnees membres
   CATGeoFactory            * _GeoFactory;
   CATBody                  * _CreationBody;
   CATFace                  * _OldFace;
   CATFace                  * _NewFace;

   CATMathBox               _ModificationMB;
   
   // Only For MathBoxes
   CATPAD                   * _MyPAD;
   CATBoolean                 _LocalPAD;
   CATCGMHashTableWithAssoc * _PCurvesAndCellsHT; // Associates a PCurve with all: the appeared Edges it supports in the first list of the CATLISTP(ListPOfCATCell) associated
                                                  //                               the disappeared ----------------------2nd list --------------------------------------------
   int                        _EstSizeDifferenceEdges;
   CATCGMHashTableWithAssoc * _DifferenceEdges;
   // Dynamic Check : internal use.
   ListPOfCATCell             _DiffEdgesToDelete;

   CATBoolean                 _SameFaceSupport;

};

#endif
