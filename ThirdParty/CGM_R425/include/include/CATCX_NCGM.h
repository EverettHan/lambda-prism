/* -*-c++-*- */
#ifndef CATCX_NCGM_H
#define CATCX_NCGM_H
// COPYRIGHT DASSAULT SYSTEMES  1999
//============================================================================
// Pour les rapides d'esprit :
//
//  1) Build-Time, Insertion dans votre code d'une seule ligne
//        CATCX_NCGM::Save("MyOperator",InputGeometricalObjects);
//
//  2) Run-Time, Valuer avant Execution (activation et destination)
//        set CATCX_NCGM=1,home=E:\tmp
//
//  3) Exploiter les fichiers NCGM issus du Stream partiel ..
//
//============================================================================
//  Dedicated to NCGM debug FOR INTERNAL CGM USE
//
//  Sauvegarde automatique de la modelisation NCGM
//
//  Le code specifique au Mode DEBUG ne doit pas perturber la modelisation
//  Aucune creation de topologie/geometrie ne doit etre introduite
//----------------------------------------------------------------------------
//       lors de certains operateurs geometriques/topologiques
// 1) On ne sauvegarde que ce qui a ete identifie.
// 2) les operandes fournis sont temporairement modifies
//      pour apparaitre Explicite/Show a la relecture 
//      et de couleur successive Bleu/Jaune/...
// 3) Les sauvegardes effectuees sont transparentes sans Pack, ...
//----------------------------------------------------------------------------
// set CATCX_NCGM=home=E:\tmp,all,keep=CutBodies,extra=CXMODEL
//----------------------------------------------------------------------------
// Sept  99 TCX Creation                                                   TCX
// 11/01/22 NLD Mise au propre (detabulation, smart indent)
//===========================================================================
#include "ExportedByGeometricObjects.h"
#include "CATListOfCATGeometries.h"
#include "CATListOfCATICGMObjects.h"
#include "CATCGMEventType.h"
#include "CATBoolean.h"

class CATGeoFactory;
class CATGeometry;
class CATBody;
class CATTrace;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATICGMUnknown;
class CATCGMEvents;

class CATCXDumpOneLine
{
public:
   virtual void Message(ostream &logGlobale) const = 0; // petit message sur une ligne sans retour chariot
};

class ExportedByGeometricObjects CATCX_NCGM
{
//---------------------------------------------------------------
// Pour utilisation dans un operateur geometrique ou topologique
//---------------------------------------------------------------
public:

  //---------------------------------------------------------------------------
  // Pour les economes :  en une seule ligne de code : simplicite maximale
  //  exemple :  CATCX_NCGM::Save("MyOperator", InputShell, InputWire);
  //---------------------------------------------------------------------------

  inline static void SaveObjects  (const char                      iOperatorName[]         ,
                                         CATLISTP(CATICGMObject) & iOperands               ,
                                   const char                      iMessageForParameters[] = ""  ,
                                   const CATCXDumpOneLine        * iComplexLine            = NULL,
                                   const char                      iEXTRA[]                = ""  ,
                                   const int                       iPutColor               = 1   );

  inline static void Save         (const char                      iOperatorName[]         ,
                                         CATGeometry             * iFirstOperand           ,
                                         CATGeometry             * iSecondOperand          = NULL,
                                   const char                      iMessageForParameters[] = ""  ,
                                   const CATCXDumpOneLine        * iComplexLine            = NULL,
                                   const char                      iEXTRA[]                = ""  ,
                                   const int                       iPutColor               = 1   );

  inline static void Save         (const char                      iOperatorName[]         ,
                                         CATLISTP(CATGeometry)   & Operands                ,
                                   const char                      iMessageForParameters[] = ""  ,
                                   const CATCXDumpOneLine        * iComplexLine            = NULL,
                                   const char                      iEXTRA[]                = ""  ,
                                   const int                       iPutColor               = 1   );

  inline static void Save         (const char                      iOperatorName[]         ,
                                         CATGeometry            ** iInputOperands          = NULL,
                                   const char                      iMessageForParameters[] = ""  ,
                                   const CATCXDumpOneLine        * iComplexLine            = NULL,
                                   const char                      iEXTRA[]                = ""  ,
                                   const int                       iPutColor               = 1   );

  inline static void SaveFederator(const char                      iOperatorName[]         ,
                                         CATGeometry             * iFederator              ,
                                         CATGeometry             * iFirstObject            ,
                                         CATLISTP(CATGeometry)   & iGeometryInsideFederator,
                                   const char                      iMessageForParameters[] = ""  ,
                                   const CATCXDumpOneLine        * iComplexLine            = NULL,
                                   const char                      iEXTRA[]                = ""  ,
                                   const int                       iPutColor               = 1   ); 

  //---------------------------------------------------------------------------
  // Detection d'un mode Debug associe a un operateur particulier
  //---------------------------------------------------------------------------
  static const CATCX_NCGM *GetDebug(const char                      iOperatorName[]         ,
                                    const char                      iEXTRA[]                = ""  ,
                                    const int                       iInitialize             = 0);

  //---------------------------------------------------------------------------
  // Plusieurs Mode de sauvegarde sont disponibles :
  //     - 1 ou 2 Operandes
  //     - Liste d'objects
  //     - Tableau d'objects (fin de tableau avec dernier element nul)
  //---------------------------------------------------------------------------
  
                void SaveObjects  (      CATLISTP(CATICGMObject) & Operands                ,
                                   const char                      iMessageForParameters[] = ""  ,
                                   const CATCXDumpOneLine        * iComplexLine            = NULL,
                                   const int                       iPutColor               = 1   ) const;

                void SaveObjects  (      CATICGMObject           * iFirstOperand           ,
                                         CATICGMObject           * iSecondOperand          = NULL,
                                   const char                      iMessageForParameters[] = ""  ,
                                   const CATCXDumpOneLine        * iComplexLine            = NULL,
                                   const int                       iPutColor               = 1   ) const;


                void Save         (      CATGeometry             * iFirstOperand           ,
                                         CATGeometry             * iSecondOperand          = NULL,
                                   const char                      iMessageForParameters[] = "",
                                   const CATCXDumpOneLine        * iComplexLine            = NULL,
                                   const int                       iPutColor               = 1   ) const;

                void Save         (      CATLISTP(CATGeometry)   & iOperands               ,
                                   const char                      iMessageForParameters[] = ""  ,
                                   const CATCXDumpOneLine        * iComplexLine            = NULL,
                                   const int                       iPutColor               = 1   ) const;

                void Save         (      CATGeometry             * iInputOperands[]        ,
                                   const char                      iMessageForParameters[] = ""  ,
                                   const CATCXDumpOneLine        * iComplexLine            = NULL,
                                   const int                       iPutColor               = 1   ) const;

                void SaveFederator(      CATGeometry             * iFederator              ,
                                         CATGeometry             * iFirstObject            ,
                                         CATLISTP(CATGeometry)   & iGeometryInsideBody     ,
                                   const char                      iMessageForParameters[] = ""  ,
                                   const CATCXDumpOneLine        * iComplexLine            = NULL,
                                   const int                       iPutColor               = 1) const;

 //---------------------------------------------------------------
 // Pour Gestion interne
 //---------------------------------------------------------------
  virtual ~CATCX_NCGM();

 //---------------------------------------------------------------
 // Pour Gestion interne, renvoi l'ancien mode d'activation
 //---------------------------------------------------------------
  static int TemporaryDesactivate(int iNewMode);




  //---------------------------------------------------------------------------
   // Pour Administration interactive
  //---------------------------------------------------------------------------
  /**
  * change the default directory where NCGM are registered
  */
  static void SetRecordDirectory(const char *iDirectory); 

  /**
  * change the default prefixe name for Operator
  */
  static void SetPrefixeName    (const char *iPrefixName);

  /**
  * change the extra Operator (not accessible by Default)
  */
  static void SetExtraName      (const char *iExtraName);

  /**
  *  Change the default overridding mode in the same document
  */
  static void SetDifferentName  (const short iDifferentNames);


  /**
  * get the default directory where NCGM are registered
  */
  static const char* GetRecordDirectory(); 

  /**
  * get the default prefixe name for Operator
  */
  static const char *GetPrefixeName();

  /**
  * change the extra Operator (not accessible by Default)
  */
  static const char *GetExtraName();

  /**
  *  Get the default overridding mode in the same document
  */
  static const short GetDifferentName();

  /**
  *  Get the current Mode
  */
  static const short GetMode();
  
  
protected: 
  
   static CATCX_NCGM  * GetCGM();

   CATCX_NCGM();
  
   static void          InitialisationRequired();

   static int           _InitialisationDone;
   static int           _NumberOfSaveDone;

   static  CATCX_NCGM * _TheImplementation;

   static  int          _SaveWithDistintName;
   static  char       * _OutputDirectory;
   static  char       * _OperandFilter;
   static  char       * _ExtraAuthorized;

   static CATBoolean     _CATGMayday;

   static char          _CurrentOperator[512];

   static CATTrace    * _CATCX_NCGM;


  static char         * _PrefixOfNCGM;


  virtual void SaveCommon           (      CATICGMObject          ** InputOperands         ,
                                     const char                      MessageForParameters[],
                                     const CATCXDumpOneLine        * complexLine           ,
                                           CATICGMObject           * iFederator            ,
                                           CATICGMObject           * iFirstObject          ,
                                     const int                       iPutColor             ) const = 0;
};


//---------------------------------------------------------------
// Pour les economies en ligne de Code
//---------------------------------------------------------------
inline  void CATCX_NCGM::SaveObjects(const char                      OperatorName        [],
                                           CATLISTP(CATICGMObject) & Operands              ,
                                     const char                      MessageForParameters[],
                                     const CATCXDumpOneLine        * complexLine           ,
                                     const char                      EXTRA               [],
                                     const int                       iPutColor             )
{
  const CATCX_NCGM* debugcgm = CATCX_NCGM::GetDebug(OperatorName,EXTRA);
  if ( debugcgm )
    debugcgm->SaveObjects(Operands,MessageForParameters,complexLine,iPutColor);
}

//---------------------------------------------------------------
inline void CATCX_NCGM::Save        (const char                      OperatorName        [],
                                           CATGeometry             * FirstOperand          ,
                                           CATGeometry             * SecondOperand         ,
                                     const char                      MessageForParameters[],
                                     const CATCXDumpOneLine        * complexLine           ,
                                     const char                      EXTRA               [],
                                     const int                       iPutColor             )
{
  const CATCX_NCGM* debugcgm = CATCX_NCGM::GetDebug(OperatorName,EXTRA);
  if ( debugcgm )
    debugcgm->Save(FirstOperand,SecondOperand,MessageForParameters,complexLine,iPutColor);
}

//---------------------------------------------------------------
inline  void CATCX_NCGM::Save       (const char                      OperatorName        [],
                                           CATLISTP(CATGeometry)   & Operands              ,
                                     const char                      MessageForParameters[],
                                     const CATCXDumpOneLine        * complexLine           ,
                                     const char                      EXTRA               [],
                                     const int                       iPutColor             )
{
  const CATCX_NCGM* debugcgm = CATCX_NCGM::GetDebug(OperatorName,EXTRA);
  if ( debugcgm )
    debugcgm->Save(Operands,MessageForParameters,complexLine,iPutColor);
}

//---------------------------------------------------------------
inline  void CATCX_NCGM::Save       (const char                      OperatorName        [],
                                           CATGeometry             * InputOperands       [],
                                     const char                      MessageForParameters[],
                                     const CATCXDumpOneLine        * complexLine           ,
                                     const char                      EXTRA               [],
                                     const int                       iPutColor             )
{
  const CATCX_NCGM* debugcgm = CATCX_NCGM::GetDebug(OperatorName,EXTRA);
  if ( debugcgm )
    debugcgm->Save(InputOperands,MessageForParameters,complexLine,iPutColor);
}

//---------------------------------------------------------------
inline  void CATCX_NCGM::SaveFederator(const char                      OperatorName        [],
                                             CATGeometry             * iFederator            ,
                                             CATGeometry             * iFirstObject          ,
                                             CATLISTP(CATGeometry)   & GeometryInsideBody    ,
                                       const char                      MessageForParameters[],
                                       const CATCXDumpOneLine        * complexLine           ,
                                       const char                      EXTRA               [],
                                       const int                       iPutColor             )
{
  const CATCX_NCGM* debugcgm = CATCX_NCGM::GetDebug(OperatorName,EXTRA);
  if ( debugcgm )
    debugcgm->SaveFederator(iFederator,iFirstObject,GeometryInsideBody,MessageForParameters,complexLine,iPutColor);
}


//---------------------------------------------------------------
// Pour Gestion interne
//---------------------------------------------------------------
extern "C" 
{
  typedef void INIT_CATCX_NCGM(); 
}

//-------------------------------------------------------------------

#endif // CATCX_NCGM_H

