/* -*-C++-*- */

#ifndef CATTopExtrusionConverger_H
#define CATTopExtrusionConverger_H

// COPYRIGHT DASSAULT SYSTEMES 2021


//=============================================================================
//=============================================================================
//
// CATTopExtrusionConverger : Operateur pour la convergence de la 
//                            reconnaissance des extrusions
//
//=============================================================================

//=============================================================================
// Dec  2021  Creation                                           P. Rossignol
//=============================================================================
//=============================================================================

// Def ExportedBy (pas encore utile)
#include "TopExtrudeRecog.h"

// Enum dans les interfaces
#include "CATCGMConvergerDef.h"

// Includes de base
#include "CATTopOperator.h"
#include "CATExtCGMReplay.h"

//
#ifndef NULL
#define NULL 0
#endif

//
class CATBody;
class CATShell;

// Classes de base
class CATGeoFactory;
class CATTopData;
class CATSoftwareConfiguration;

// Basique
#include "CATBoolean.h"

// Topolo
class CATBody;
class CATShell;

// Liens DRep
class CATGMLiveExtrusionPrimitive;

// Types
typedef CATCVG_ApplicationName CATExtr_AppName;
typedef CATCVG_CreationType    CATExtr_CreType;
typedef CATCVG_FeatureType     CATExtr_FtrType;
typedef CATCVG_PrimShapeType   CATExtr_PshType;



class ExportedByMdlTopExtr CATTopExtrusionConverger : public CATTopOperator
{

  CATCGMVirtualDeclareClass(CATTopExtrusionConverger);


public: 
//===========================================================================================================
  
  //------------------------------------------------------------------------------
  // Ctor/Dtor  
  // 
  // Virtual constructor of a <tt>CATTopExtrusionConverger</tt> operator.<br>
  // Do not call this constructor, instead use the <tt>CATCreateTopExtrusionConverger</tt> 
  // global function
  // to create a CATTopExtrusionConverger operator.
  //------------------------------------------------------------------------------    
  /* @nodoc @nocgmitf */
  CATTopExtrusionConverger           (CATGeoFactory*     iFactory,
                                      CATTopData*        iData,                    
                                      CATExtTopOperator* iExtensible = NULL);

  virtual ~CATTopExtrusionConverger  ();

  //------------------------------------------------------------------------------
  // Input
  //------------------------------------------------------------------------------       
  void         SetShell              (CATShell*                    iShell);

  void         SetAppli              (CATExtr_AppName              iName);        // Pour tracer l'origine du CGMReplay cree

  void         SetRefType            (CATExtr_CreType              iType);        // La facon de construire le body de reference (operation utilisee)  

  void         SetRunType            (CATExtr_CreType              iType);        // La facon de reconstruire le body (operation utilisee lors du Run du CGMReplay)

  void         AddRefFeature         (CATExtr_FtrType              iType);        // Les features consideres pour la construction du body de reference

  void         SetPrimShape          (CATExtr_PshType              iType);        // Les elements topos pris en compte pour construire le body (faces, (et aretes?))

  void         AddExtrusion          (CATGMLiveExtrusionPrimitive* iExtPrim);     // Les primitives a inclure: iExtPrim est sous la responsabilite de l'operateur (le delete sera fait par l'operateur)
      
  //------------------------------------------------------------------------------
  // Xx
  //------------------------------------------------------------------------------    
  
  
private :
//===========================================================================================================

  //------------------------------------------------------------------------------
  // CGM internal
  //------------------------------------------------------------------------------
  /* @nodoc @nocgmitf */
  virtual int RunOperator();

  //------------------------------------------------------------------------------
  // CGM internal - Replay
  //------------------------------------------------------------------------------
  /* @nodoc @nocgmitf */
  virtual CATExtCGMReplay * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  /* @nodoc @nocgmitf */
  virtual const CATString * GetOperatorId();
  /* @nodoc @nocgmitf */
  virtual const CATString * GetDefaultOperatorId();
  /* @nodoc @nocgmitf */
  virtual void RequireDefinitionOfInputAndOutputObjects();
  /* @nodoc @nocgmitf */
  virtual void WriteInput(CATCGMStream &Str);
  /* @nodoc @nocgmitf */
  virtual void Dump( CATCGMOutput& os );  
  /* @nodoc @nocgmitf */
  virtual void WriteTopOutput(CATCGMStream & ioStream);
  /* @nodoc @nocgmitf */
  virtual CATTopCheckJournal*  ReadTopOutput    (CATCGMStream& ioStream);
  /* @nodoc @nocgmitf */
  virtual CATBoolean           ValidateTopOutput(CATTopCheckJournal* iEquivalent, CATCGMOutput& os);  

};

/**
 * Creates a <tt>CATTopExtrusionConverger</tt> operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>iData</tt> is <tt>NULL</tt>, it is not filled.
 * @param iBody
 * The pointer to the body where the recognition will be performed.
 * @param iShell
 * The pointer to the shell where the recognition will be performed.
 * @return
 * The pointer to the created operator. To delete after use with the usual C++ <tt>delete</tt> operator.
 */
ExportedByMdlTopExtr CATTopExtrusionConverger* CATCreateTopExtrusionConverger 
  ( CATGeoFactory*     iFactory,                                                                                     
    CATTopData*        iData,                                                                              
    CATBody*           iBody);


#endif

// Ne rien ecrire sous cette ligne
//===========================================================================================================


