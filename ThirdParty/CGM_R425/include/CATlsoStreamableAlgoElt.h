/* -*-C++-*- */

// ------------------------------------------------------------------
// Oct 2014 -Created by QF2
// ------------------------------------------------------------------
//
// Class abstraite CATlsoStreamableAlgoElt
// --------------------------------------------
// - Objet :  Sert de classe mere pour le Stream des AlgoElements via un lsoPersistentContext
//            Les AlgoElements servent de structure de donnees pour les Operateurs persistants Multi-Inputs.
//
//            Les Services de cette classe mère permettent au developpeur d'implementer facilement et simplement le stream
//            des donnees multiples en entrée des operateurs persistants.
// 
// <> Guide pratique :
// ------------------
// 0. Prerequis : votre classe derivee DOIT être associee à un CATlsoPersistentContext.
//                Note : Le lsoPersistentContext sert de manager pour votre classe derivee.
//
// 1. Implementez la methode   virtual [Write/Load]InputElements(...)const=0   dans votre classe derivee.
//    Ne Streamez que les elements de votre classe fille (en versionant le stream, c'est mieux).
// 
// 2. {Important} Dans votre Context derive de CATlsoPersistentContext : 
//    Implementez la methode virtuelle  "CATlsoStreamableAlgoElt * GetInputDataObject(int iAdminIndex);"
//    Cette methode doit allouer un AlgoElt de type de votre classe derivee.
//
// 3. Dans le Stream de votre operateur : 
//   Utilisez les methodes statiques CATlsoPersistentContext::WriteMultiInputData(str) et CATlsoPersistentContext::ReadMultiInputData(...).
// 
//   Voilà, le Stream est operationel. 
// 
// Exemple de code :
// -----------------
// - CATlsoLiveExtrapolInputData avec CATlsoLiveExtrapolContext
// - CATlsoDraftInputData avec CATlsoDraftContext 
// - CATlsoThicknessFaceInputData avec CATlsoThicknessFaceContext
// 

#ifndef CATlsoStreamableAlgoElt_H
#define CATlsoStreamableAlgoElt_H

#include "PersistentCell.h"
#include "CATlsoAlgoElt.h"
#include "CATMathInline.h"
#include "CATBoolean.h"

class CATlsoChainMaster;
class CATlsoPersistentContext;
class CATGeoFactory;
class CATPersistentOperator;
class CATCGMStream;
class CATPersistentCellInfra;
class CATSoftwareConfiguration;
class CATPersistentBody;


class ExportedByPersistentCell CATlsoStreamableAlgoElt : public CATlsoAlgoElt
{

public:

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;
  
  // Destructeur
  virtual ~CATlsoStreamableAlgoElt();

  // Setters 
  // -----------------------------------------------------------
  INLINE void SetInitialInput (const CATBoolean iInitialInput);
  INLINE CATBoolean IsInitialInput () const;
  // -----------------------------------------------------------

  static CATLONG32 GetCountOfInitialElement(CATlsoChainMaster * iAdmin);
   
  INLINE virtual CATlsoStreamableAlgoElt * GetAslsoStreamableAlgoElt();

  // --------
  // Dump
  // --------
  virtual void DumpObj(CATCGMOutput& s, short iLongDump=0, short iZtrNoDump=0) const;

  // -----------------
  // Static Methodes
  // ------------------
  // Stream / Unstream 
  // -------------------------
  static void WriteStreamableAlgoElt(CATlsoStreamableAlgoElt &iStreamableAlgoElt, CATCGMStream  &ioStr);
  static void LoadStreamableAlgoElt (CATlsoStreamableAlgoElt &iStreamableAlgoElt, CATPersistentOperator &iOperatorToBeLoaded, CATGeoFactory *iFactory, CATCGMStream  &iStr);

  // Balayage de tous les objets de la classe
  static CATlsoStreamableAlgoElt * Next(CATlsoChainMaster * iAdmin, CATlsoStreamableAlgoElt* iCur);

protected:

    // Constructor for CATlsoPersistentContext only
  CATlsoStreamableAlgoElt(CATlsoPersistentContext * iPersistentContext,
                          CATlsoChainMaster       * iAdmin,
                          CATBoolean                iInitialInput=FALSE);


  CATlsoPersistentContext & GetPersistentContext() const; // safe
  CATPersistentCellInfra  & GetPersistentCellInfra() const; // safe

  CATSoftwareConfiguration * GetSoftwareConfiguration() const;


  void PutNameOnBody(CATPersistentBody * iPersistentBody, const char *iName) const;
  void PutNameOnBody(CATBody * iBody, const char *iName) const;

  // CGMReplay - Stream/Unstream
  // ------------------------------
  virtual void WriteStreamableAlgoElt(CATCGMStream  &ioStr) const = 0;
  virtual void LoadStreamableAlgoElt (CATCGMStream  &iStr, CATGeoFactory *iFactory, CATPersistentOperator *iOperatorToBeLoaded) const = 0;

  // Copy-constructeur et affectation (ne compilera pas)
  CATlsoStreamableAlgoElt(CATlsoStreamableAlgoElt& iOrig);
  CATlsoStreamableAlgoElt& operator= (const CATlsoStreamableAlgoElt& iRight);


  // -------------------
  // Internal Data
  // -------------------
  CATBoolean _InitialInput;

};


//----------------------------------------------------------------------------
// Implementations INLINE
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// IsInitialInput
//----------------------------------------------------------------------------
INLINE CATBoolean CATlsoStreamableAlgoElt::IsInitialInput () const {
  return _InitialInput; }

//----------------------------------------------------------------------------
// SetInitialInput
//----------------------------------------------------------------------------
INLINE void CATlsoStreamableAlgoElt::SetInitialInput (const CATBoolean iInitialInput) {
  _InitialInput = iInitialInput; }


INLINE CATlsoStreamableAlgoElt * CATlsoStreamableAlgoElt::GetAslsoStreamableAlgoElt() {
  return this; }

#endif

