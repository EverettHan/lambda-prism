/* -*-c++-*- */
#ifndef CATCGMVersionDefinition_H
#define CATCGMVersionDefinition_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATCGMVersionDefinition:
/**
* Version definition to be supported by the current version.
* <p>
* A list of those objects will be built automatically at program start.
* <br>
* A previous version support will describe how each type in that version is
* now supported in the current version :
* <ol>
* <li>modelization of the type hasn't changed, so the current version can
* unstream objects of that type as if it has streamed them itself.
* <li>modelization of the type has changed, there are 2 posible answers:
*   <ol>
*   <li>it is no longer possible to recreate an object with the old informations
*       in the current version.<br>
*       (hum, are you thinking about leaving the company?)
*   <li>it is still possible to recreate an object with the old informations
*       in the current version, but this requires a migration .<br>
*       <b>This migration  will be provided as a pointer to .</b><br>
*       (gooood, rather hearing that...)
*   </ol>
* </ul>
* <p>
* Describing the support of a previous version implies to make a new class
* deriving from <b>CATCGMVersionDefinition</b>.
* <br>
* In the constructor code of such class, calls will be made to :
* <ul>
* <li>set the version name (the one streamed as prefix information).
* <li>register the necessary migrations s for the problematic types.
*   <br>(i.e. for contructor encapsulation )
*   <br>(i.e. for streaming/unstreaming)
* </ul>
* <p>
* The current version will have nothing in its constructor,
* except declaring it is the current one.
* <p>
* A macro <tt>CATCGM_BuildVersionDefinition( ClassName );</tt> has to
* be inserted in the .cpp file to ensure automatic object construction.
*/
//
//=============================================================================
// Apr.    98   Creation                                         Ph.Baucher (PHB)
// August. 99   Documentation et Optimisation (late binding)
// July    04   Ajout MakeInitSubdivision                        RAQ
// 
//    Dorenavant toute version de stockage ne se definit completement
// que si on cherche explicitement a exploiter cette definition.
// Il n'y a plus d'initialisation complete des variables globales au chargement
// de la shared-lib, c'est uniquement sur relecture d'une vieille version 
// ou sauvegarde sur une version specifique que l'on initialisera...
//                
//=============================================================================
#include "CATIACGMLevel.h"
#include "CATCollec.h" 
#include "CATUnicodeString.h" 
#include "ObjectTypesCGM.h" 
#include "CATCGMStreamVersionUtilities.h"
#include "CATMathInline.h"
#include "CATCGMStreamTypeDEFINE_MAX.h"
#include "CATCGMStreamBinder.h"
#include "ExportedByCATCGMFusion.h"

class CATCGMVersionDefinition;
class CATCGMTypeMigration;
class CATCGMObject;
class CATCGMStream;
class CATCGMStreamBinderGeoCGM;
class CATCGMContainer;
class CATHDICO(CATCGMVersionDefinition);
class CATLISTP(CATCGMTypeMigration);
class CATLISTP(CATICGMObject);
class CATRCOLL(CATCGMCreateVersion);

typedef CATCGMVersionDefinition*  (*CATCGMCreateVersion) ();
typedef void                      (*CATCGMMigrateUnstream)       (CATCGMObject &cgm, CATLISTP(CATICGMObject) &ListDependencies, CATCGMStream &Str);
typedef void                      (*CATCGMMigrate)       (CATCGMObject &cgm, CATCGMStream &Str);
typedef void                      (*CATCGMProcess)       (CATCGMObject &cgm);
typedef CATBaseUnknown*           (*CATCGMConstructor)   (CATCGMContainer* iContainer);

#define CATMaxObjectTypesCGM  CATCGMStreamTERMINATOR_Value
#define CATMaxIdentifierNAME  96
#define MagicMakeSureInitDone 28111966


class ExportedByCATCGMFusion CATCGMVersionDefinition
{
public:
  virtual  ~CATCGMVersionDefinition();
  
  /**
  *  Persistent Identification of Version
  *  Manage initialisation only when necessary
  */
  INLINE  const char * GetIdentifier() const; 
  
  INLINE CATCGMStreamVersion GetVersionNumber() const;
  
  INLINE double GetPLMInferie_CATMlcDataVersion() const;
 

  //---------------------------------------------------------------------------------
  //  Format de stockage du document CATPart
  //    CXR2 : V2R1 :  
  //    CXR3 : V2R4 : Partage des domaines, gain de place stockage de la Topologie
  //    CXR4 : CXR4 : Fonctionnalite  Helix, Cloud, ..
  //-----------------------------------------------------------------------------------
  static const CATCGMVersionDefinition *GetCATPartStreamVersion();

  /**
  *  Test if it is the current version.
  *  Get the current Version of Software in memory.
  *  Query for a given version support from its  Persistent Identification
  */
  INLINE int                            IsCurrent()    const;
  static const CATCGMVersionDefinition *GetCurrent();

  static const CATCGMVersionDefinition *QueryVersionDefinition(const char *iVersionName);

  static const CATCGMVersionDefinition *QueryVersionDefinition(CATCGMStreamVersion iVersionNumber);
  

  //int  RegisterUnstreaming(short itp, CATCGMMigrate   iPtrFunct);	
  //int  GetUnstreaming     (short itp, CATCGMMigrate  &oPtrFunct, int &oCorrectionExist ) const;

  int  RegisterUnstreaming(short itp, CATCGMMigrateUnstream   iPtrFunct);	
  int  GetUnstreaming     (short itp, CATCGMMigrateUnstream  &oPtrFunct, int &oCorrectionExist ) const;
  
  int  RegisterStreaming  (short itp, CATCGMMigrate   iPtrFunct);
  int  GetStreaming       (short itp, CATCGMMigrate  &oPtrFunct) const;
  
  int  RegisterCorrection (short itp, CATCGMProcess   iPtrFunct);
  int  GetCorrection      (short itp, CATCGMProcess  &oPtrFunct) const;
  
  static int RegisterVersionCreation(CATCGMCreateVersion iPtrFunct);


  //---------------------------------------------------------------------------------
  // Gestion globale sans versionning 
  //---------------------------------------------------------------------------------
  int  RegisterType               (short itp);

  // Make sure CATCGMStreamBind(itp) has been called
  INLINE int  IsARegisteredType          (short itp) const;
    
  int  RegisterConstructor(short itp, CATCGMConstructor       iPtrFunct);
  int  GetConstructor     (short itp, CATCGMConstructor      &oPtrFunct) const;

  //---------------------------------------------------------------------------------
  //  Pour etre certain du sequencement temporels des inits 
  // au chargement des shared-lib CATGeometricObjectsCGM puis CATTopologicalObjects
  //-----------------------------------------------------------------------------------
  INLINE static int MakeSureInitDone(); 

  static void CleanAtExit();

 
  //---------------------------------------------------------------------------------
  // Internal Use
  //---------------------------------------------------------------------------------
  static CATCGMVersionDefinition *CreateIfNecessary(CATCGMStreamVersion StreamVersion);

  CATCGMVersionDefinition(CATCGMStreamVersion iVersion, 
                          const char          iStrVersion[],
                          const CATBoolean    iWithGenerator ,
                          const double        iPLMInferie_CATMlcDataVersion  );

protected:

  // Init
  static CATCGMVersionDefinition                *_Current ;

private:

   // Init
  static int _DoMakeSureInit(); 
  static int _MakeSureInitDone;  

  //
  friend class CATCGMStreamBinderGeoCGM;


  // Static Classe
  static CATHDICO(CATCGMVersionDefinition)      *_DicoVersions ;

  // Version minimale a partir de laquelle l'object est reconnu
  static CATCGMVersionDefinition * _ObjectVersion     [ CATMaxObjectTypesCGM ];

  // Reference au constructeur d'object
  static CATCGMConstructor         _ObjectConstructor [ CATMaxObjectTypesCGM ];



  // Le vrai identificateur de Version courante
  CATCGMStreamVersion             _MyVersion;

  // Pour la version courante, stockage des traitements specifiques
  CATCGMTypeMigration            **_PtrTypesMigrations;

  // Identificateur caractere de la version courante
  char                            _Identifier[CATMaxIdentifierNAME] ;


  double                          _PLMInferie_CATMlcDataVersion;

  // NOT IMPLEMENTED
  CATCGMVersionDefinition(const CATCGMVersionDefinition &);
  CATCGMVersionDefinition& operator=(const CATCGMVersionDefinition&) ;

};




INLINE  const char * CATCGMVersionDefinition::GetIdentifier() const
{
  return _Identifier; 
}

INLINE double CATCGMVersionDefinition::GetPLMInferie_CATMlcDataVersion() const
{
  return _PLMInferie_CATMlcDataVersion;
}

INLINE int  CATCGMVersionDefinition::IsCurrent()    const    
{
  return ( this == _Current ) ? 1 : 0 ; 
}

INLINE CATCGMStreamVersion CATCGMVersionDefinition::GetVersionNumber() const
{
  return _MyVersion;
}

INLINE int CATCGMVersionDefinition::MakeSureInitDone()
{
   if ( _MakeSureInitDone != MagicMakeSureInitDone ) _DoMakeSureInit();
   return _MakeSureInitDone;
}

INLINE int  CATCGMVersionDefinition::IsARegisteredType( short  iTypeCode ) const
{
  if ( _MakeSureInitDone != MagicMakeSureInitDone ) _DoMakeSureInit();

  if ( (iTypeCode <= 0) || (iTypeCode >= CATMaxObjectTypesCGM) )
    return 0;

  CATCGMVersionDefinition *volatile RootVersion =  _ObjectVersion[ iTypeCode ];
  if ( ! RootVersion )
  {
    CATCGMStreamBind(iTypeCode);
    RootVersion =  _ObjectVersion[ iTypeCode ];
  }

  if ( RootVersion && (RootVersion->_MyVersion <= _MyVersion) )
    return 1;

  return 0;
}

//=============================================================================
//              CATCGMVersionDefinitionDECLARE     
//=============================================================================

#define CATCGMVersionDefinitionDECLARE(CurrentVersion) \
class ExportedByCATCGMFusion CurrentVersion :   public CATCGMVersionDefinition \
{ \
public: \
  virtual  ~CurrentVersion(); \
  static CATCGMVersionDefinition *GetDefinition(); \
  CurrentVersion(CATCGMStreamVersion iVersion, const char iStrVersion[], const CATBoolean iWithGenerator ); \
    \
private:\
  CurrentVersion(const CurrentVersion&);\
  CurrentVersion& operator=(const CurrentVersion&) ; \
  static  CATCGMVersionDefinition*     _Definition ; \
}; 


#define CATCGMVersionDefinitionDEFINE(CurrentVersion,CurrentStringVersion,CurrentStreamVersion,CurrentPLMInferie_CATMlcDataVersionLevel) \
CATCGMVersionDefinition*   CurrentVersion::_Definition = NULL ; \
\
CurrentVersion::CurrentVersion(CATCGMStreamVersion iVersion, const char iStrVersion[], const CATBoolean iWithGenerator) \
  : CATCGMVersionDefinition(iVersion,iStrVersion,iWithGenerator,CurrentPLMInferie_CATMlcDataVersionLevel) {  } \
\
CurrentVersion::~CurrentVersion() \
{  if ( _Definition == this )  _Definition = NULL;  }  \
 \
CATCGMVersionDefinition *CurrentVersion::GetDefinition() \
{ \
  MakeSureInitDone(); \
 \
  if ( !_Definition && !CATCGMVersionDefinition::_Current )  \
    _Definition = new CurrentVersion(CurrentStreamVersion,CurrentStringVersion,FALSE) ;  \
 \
  return _Definition ; \
} 


#define CATCGMVersionDefinitionUNDEREVALUATE(CurrentVersion,CurrentStringVersion,CurrentStreamVersion,CurrentPLMInferie_CATMlcDataVersionLevel) \
CATCGMVersionDefinition*   CurrentVersion::_Definition = NULL ; \
\
CurrentVersion::CurrentVersion(CATCGMStreamVersion iVersion, const char iStrVersion[], const CATBoolean iWithGenerator) \
  : CATCGMVersionDefinition(iVersion,iStrVersion,iWithGenerator,CurrentPLMInferie_CATMlcDataVersionLevel) {  } \
\
CurrentVersion::~CurrentVersion() \
{  if ( _Definition == this )  _Definition = NULL;  }  \
 \
CATCGMVersionDefinition *CurrentVersion::GetDefinition() \
{ \
  MakeSureInitDone(); \
 \
  if ( !_Definition && !CATCGMVersionDefinition::_Current )  \
    _Definition = new CurrentVersion(CurrentStreamVersion,CurrentStringVersion,TRUE) ;  \
 \
  return _Definition ; \
} 

 

 


//=============================================================================
//  DECLARATION DE TOUTES LES VERSIONS 
//=============================================================================
// 2023Fall     for V5-6R2024-CXR34 & V6R2023x-R425
// New
CATCGMVersionDefinitionDECLARE(CATCGMVersion2023Fall)

// 2022Fall     for V5-6R2023-CXR33 & V6R2023x-R425
CATCGMVersionDefinitionDECLARE(CATCGMVersion2022Fall)

// 2021Fall     for V5-6R2022-CXR32 & V6R2022x-R424
CATCGMVersionDefinitionDECLARE(CATCGMVersion2021Fall)

// 2020Fall     for V5-6R2021-CXR31 & V6R2021x-R423
CATCGMVersionDefinitionDECLARE(CATCGMVersion2020Fall)

// 2019Fall     for V5-6R2020-CXR30 & V6R2020x-R422
CATCGMVersionDefinitionDECLARE(CATCGMVersion2019Fall)

// 2018Fall     for V5-6R2019-CXR29 & V6R2019x-R421
CATCGMVersionDefinitionDECLARE(CATCGMVersion2018Fall)

// 2017Fall     for V5-6R2018-CXR28 & V6R2018x-R420
CATCGMVersionDefinitionDECLARE(CATCGMVersion2017Fall)

// 2016Fall     for V5-6R2017-CXR27 & V6R2017x-R419
CATCGMVersionDefinitionDECLARE(CATCGMVersion2016Fall)

// 2015Fall     for V5-6R2016-CXR26 & V6R2016x-R418
CATCGMVersionDefinitionDECLARE(CATCGMVersion2015Fall)

// 2014Fall   for V5-6R2015-CXR25 & V6R2015x-R417
CATCGMVersionDefinitionDECLARE(CATCGMVersion2014Fall)
 
// CATCGMVersion2013 ... ?   
CATCGMVersionDefinitionDECLARE(CATCGMVersion2013Spring) 
CATCGMVersionDefinitionDECLARE(CATCGMVersion2013Fall) 
 


// 2012 Winter = To Be defined  R215 V5R24 ?   
CATCGMVersionDefinitionDECLARE(CATCGMVersion2012Winter) 
 
 
// 2012 Spring = August 2012 R214 V5R23  
CATCGMVersionDefinitionDECLARE(CATCGMVersion2012Spring) 

// 2012 For CGMReplay only CATCGMVersion2012March
CATCGMVersionDefinitionDECLARE(CATCGMVersion2012April) 

// 2011 Fall R212 = CXR22
CATCGMVersionDefinitionDECLARE(CATCGMVersion2011Fall)
 
// 2011 Spring R211 = CXR21 
CATCGMVersionDefinitionDECLARE(CATCGMVersion2011Spring)


// 2010 ?
CATCGMVersionDefinitionDECLARE(CATCGMVersion2010Fall)
CATCGMVersionDefinitionDECLARE(CATCGMVersionR209_V6R2011)
 
// June.2009 TCX
CATCGMVersionDefinitionDECLARE(CATCGMVersion2009Fall)
 
// Jun. 98   Creation                                         Ph.Baucher (PHB)
CATCGMVersionDefinitionDECLARE(CATCGMVersionV2R0)
CATCGMVersionDefinitionDECLARE(CATCGMVersionV2R1)

// CATCGMVersionV2R2: Class representing V2R2 version.
//     Version temporaire Stream EdgeCurve
// May  99   Creation                                         E. Guerin (EGE)
CATCGMVersionDefinitionDECLARE(CATCGMVersionV2R2)

// CATCGMVersionV2R3:  Nouvelle Version Stream EdgeCurve
//     Introduit a partir de la CXR2 SP1 (stockage a partir de la CXR3)
// Jun  99   Creation                                         E. Guerin (EGE)
CATCGMVersionDefinitionDECLARE(CATCGMVersionV2R3)

// CATCGMVersionV2R4: Stream Loop/Wire/Edge revu pour stabilite
//     But avoue : nouveau format stockage a partir de la CXR3  GA
// September 99   Creation                                       T CHAILLOUX
CATCGMVersionDefinitionDECLARE(CATCGMVersionV2R4)

// CATCGMVersionCXR4: Nouvelle structure de donnees pour la CXR4
//     Cloud, Helix, ..
CATCGMVersionDefinitionDECLARE(CATCGMVersionCXR4)


// CATCGMVersionCXR5: Nouvelle structure de donnees pour la CXR5
//  AdvancedMathematics
//     CATMathQuinticX   : Nouveau Format de Stockage
//  GeometricObjectsCGM
//     ProcCurve                   : Nouvelle Entite
//     SpecSurface                 : Nouvelle Entite
//     FilletSurfaceCGM            : Nouvelle Variete de type   BiTangentCircleFillet 
//     NonLinearTransfoSurfaceCGM  : Nouvelle Variete de type   CATMathConicDeformationFoldedType
// September 2000   Creation                                       T CHAILLOUX
CATCGMVersionDefinitionDECLARE(CATCGMVersionCXR5)

// CATCGMVersionCXR6: Nouvelle structure de donnees pour la CXR5
//
//  AdvancedMathematics
//     CATMathQuinticX   : Nouveau Format de Stockage
//  GeometricObjectsCGM
//     ProcCurve                   : Nouvelle Entite
//     SpecSurface                 : Nouvelle Entite
//     FilletSurfaceCGM            : Nouvelle Variete de type   BiTangentCircleFillet 
//     NonLinearTransfoSurfaceCGM  : Nouvelle Variete de type   CATMathConicDeformationFoldedType
CATCGMVersionDefinitionDECLARE(CATCGMVersionCXR6)

// CATCGMVersionCXR7: Nouvelle structure de donnees pour la CXR7
CATCGMVersionDefinitionDECLARE(CATCGMVersionCXR7)

// CATCGMVersionCXR8: Nouvelle structure de donnees pour la CXR8
// May 2001   Creation                                       T CHAILLOUX
CATCGMVersionDefinitionDECLARE(CATCGMVersionCXR8)

// Janvier 2002   Creation                                       T CHAILLOUX
CATCGMVersionDefinitionDECLARE(CATCGMVersionV5R9GA)

// Juillet 2002   Creation                                       T CHAILLOUX
CATCGMVersionDefinitionDECLARE(CATCGMVersionV5R10GA)

// Janvier 2002   Creation                                       T CHAILLOUX
CATCGMVersionDefinitionDECLARE(CATCGMVersionV5R11GA)

// Mar. 03 Creation                                                       HCN
CATCGMVersionDefinitionDECLARE(CATCGMVersionV5R12GA)

// Nov. 03 Creation                                                       HCN
CATCGMVersionDefinitionDECLARE(CATCGMVersionV5R13GA)

// Jan. 04 Creation                                                       HCN
CATCGMVersionDefinitionDECLARE(CATCGMVersionV5R14GA)

// Jan. 04 Creation                                                       HCN
CATCGMVersionDefinitionDECLARE(CATCGMVersionV5R15GA)

// Jan. 04 Creation                                                       HCN
CATCGMVersionDefinitionDECLARE(CATCGMVersionV5R16GA)

// Jan. 04 Creation                                                       HCN
CATCGMVersionDefinitionDECLARE(CATCGMVersionV5R17GA)

// Jan. 04 Creation                                                       HCN
CATCGMVersionDefinitionDECLARE(CATCGMVersionV5R18GA)

// Jan. 04 Creation                                                       HCN
CATCGMVersionDefinitionDECLARE(CATCGMVersionV5R19GA)


CATCGMVersionDefinitionDECLARE(CATCGMVersionR201GA)

CATCGMVersionDefinitionDECLARE(CATCGMVersionR20117)

CATCGMVersionDefinitionDECLARE(CATCGMVersionR202GA)

CATCGMVersionDefinitionDECLARE(CATCGMVersionR203GA)

CATCGMVersionDefinitionDECLARE(CATCGMVersionR204GA)

CATCGMVersionDefinitionDECLARE(CATCGMVersionR205GA)

CATCGMVersionDefinitionDECLARE(CATCGMVersionR206GA)

CATCGMVersionDefinitionDECLARE(CATCGMVersionR207GA)

 
// ...

CATCGMVersionDefinitionDECLARE(CATCGMVersionBeta)

CATCGMVersionDefinitionDECLARE(CATCGMVersionVolatile)


#endif
