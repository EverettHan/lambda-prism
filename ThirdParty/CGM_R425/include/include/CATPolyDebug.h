/* -*-C++-*-*/
#ifndef CATPolyDebug_H
#define CATPolyDebug_H

#include "CATErrorDef.h" // HRESULT definition
#include "PolyhedralUtilities.h"   // ExportedBy definition

#include "CATPolyImportTypedef.h"
#include "CATPolyDumpable.h" // definition of inline function DumpPoly(elt)
#include "CATCGMOutput.h"    // same as above

#include "CATListOfInt.h"    // used

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 2003

// CATPolyDebug

// DESCRIPTION : A static "debug" object may be associated with a polyhedral model
// operator (e.g CGR import). It contains pilot variables for debug that can be initialized
// by a declarative file as well as environment variables. Static methods of general utility
// are also gathered in this class

// History

// Jun. 03   Church         Creation

//=============================================================================
class CATCGMOutput;
class CATPolyIndex;
class CATPolyObject;
class CATIPolyMesh;
class CAT4x4Matrix;

class CATPolyDebug;

// The following types (pointers to functions) enable setting all values in the
// CATPolyDebug object. The last argument (iToCopy) is generally null, it is used
// to copy a default version of the CATPolyDebug object
typedef void (CATPolyDebug::*SetIntValue) (int iValue, CATPolyDebug * iToCopy);
typedef void (CATPolyDebug::*SetFloatValue) (float iValue, CATPolyDebug * iToCopy);
typedef void (CATPolyDebug::*SetString) (char * iString, CATPolyDebug * iToCopy);
typedef void (CATPolyDebug::*SetIntTable) (int iPos, int iValue, CATPolyDebug * iToCopy);
typedef void (CATPolyDebug::*SetFloatTable) (int iPos, float iValue, CATPolyDebug * iToCopy);

#define POLYDUMP(name) ((CATPolyDebug::_pdbg) ? (CATPolyDebug::_pdbg->_DumpLevel[CATPolyDebug::name]) : (0))
#define DTRIGGERSSIZE CATPolyDebug::_DisplayTriggersSize

struct CATPolyDebugSetting
{
  char _name[50];
  unsigned char _DisableDefaultSetting; // =1 for static vars that must be kept between consecutive calls
  int  _vartyp; // 0=int, 1=float, 2=char*, 3=int[], 4=float[]
  union {
    SetIntValue   _SetIntValue;
    SetFloatValue _SetFloatValue;
    SetString     _SetString;
    SetIntTable   _SetIntTable;
    SetFloatTable _SetFloatTable;
  } _setfunc;
};

//============================================================
// CLASS DEFINITION
//------------------------------------------------------------ 

class ExportedByPolyhedralUtilities CATPolyDebug
{
public:

  enum { _StackMaxSize = 100, _MaxLineSize = 255, _MaxNbVar = 100 };
  enum { _AlgoTestSize = 10, _DumpLevelSize = 20 };

  // Used indexes in _DumpLevel[]
  enum { _DumpCoedges  =0, _DumpContainer=1, _DumpCondenser=2, _DumpRepScan=3,
         _DumpVertices =4, _DumpImportFaces=5, _DumpTriangles=6 };

  // Pointeur vers objet statique de debug, et vers une variable qui reste
  // a 0 tant qu'on n'a pas fait de CATGetEnv(CATCGMDebugPoly)
  // L'objet *_pdbg ne sera alloue que si cette variable vaut 1
  static int _DebugPolyModeHasBeenRead;
  static CATPolyDebug * _pdbg;

  // Initialisation de l'objet statique (appel a CATGetEnv puis au constructeur uniquement si v.env active)
  static int InitPolyDebug();

  // Nettoyage de l'objet CATPolyDebug, appele en fin d'appel a un operateur pour ne pas laisser de mlk en mode debug
  // (on pourrait ne pas le faire, l'objet est petit...)
  static void CleanPolyDebug();

  // Cycle de vie
  CATPolyDebug();
  virtual ~CATPolyDebug();

  // Mise a jour ou reaffectation des valeurs par defaut
  void UpdatePDBG();

  // Maintien de la coherence de l'objet debug, pour le cas ou des affectations
  // par v.env ou par declaratif s'averent incompatibles
  void CheckPDBG();

  // Utilitaire de decodage d'un time-tag dans une string (%time%) - rend null si absent,
  // sinon rend un char* alloue
  static char * DecodeTimeTag(char * iString);

  // Nettoyage complet
  void CleanAllocatedData();

  // Utilitaire d'elimination de blancs dans une string
  static void KillBlanks(char * iString);

  // Recuperation d'un CATCGMOutput pour ecritures massives: fichier si present et
  // iCondition=1, sinon cgmout. oFreeOutput=1 en sortie si le CATCGMOutput doit etre desalloue
  // iReplace = 0 si mode "append" (obligatoire si cgmout), 1 si "replace"
  static CATCGMOutput * GetDummyOutput(int iCondition, int & oFreeOutput, int iReplace=0);

  // Dump
  HRESULT Dump(CATCGMOutput & s) const; // not virtual (and not yet implemented)
  friend CATCGMOutput & operator << (CATCGMOutput& s, const CATPolyDebug & iObj);

  static void DumpMatrix(const CAT4x4Matrix * iMat, CATCGMOutput & s, char * iMargin=0);

  static void DumpTrianglesInMesh(const CATIPolyMesh * iMesh, CATCGMOutput & s);
  static void DumpVerticesInMesh(const CATIPolyMesh * iMesh, CATCGMOutput & s);

  // Initialisation de la liste des noms de variables (appele par le cst)
  void InitVariableNames();

  // Ecriture des donnees
  void SetAlgoTest(int iPos, int iVal, CATPolyDebug * iToCopy);
  void SetShowOctreeAttributes(int iPos, int iVal, CATPolyDebug * iToCopy);
  void SetWriteProgressionPercent(int iWrite, CATPolyDebug * iToCopy);
  void SetDumpLevel(int iPos, int iVal, CATPolyDebug * iToCopy);
  void SetDummyOutputFile(char * iFilePath, CATPolyDebug * iToCopy);
  void SetFaceNumberToDisplay(int iFaceNum, CATPolyDebug * iToCopy);
  void SetSaveDressUpInCGRFile(int iSave, CATPolyDebug * iToCopy);
  void SetDressUpDisplayTriggers(int iPos, int iTrigger, CATPolyDebug * iToCopy);
  void SetDressUpPickedFaceUponSelection(int iDressUp, CATPolyDebug * iToCopy);
  void SetShowOctreeUponSelection(int iShow, CATPolyDebug * iToCopy);
  void SetVoxelTolerance(float iTol, CATPolyDebug * iToCopy);
  void SetWatchAddressesDuplicatesInsideFaces(int iWatch, CATPolyDebug * iToCopy);
  void SetToleranceOnBaryCoord(int iApplyTol, CATPolyDebug * iToCopy);
  inline DressUpFaceMethod GetDebugRepDisplayMethod() const;
  inline void SetDebugRepDisplayMethod(DressUpFaceMethod iDUMethod);
  void SetKeepOnlyVoronoiData(int iPos, int iVal, CATPolyDebug * iToCopy);
  void SetTrackIJKBoxData(int iPos, int iVal, CATPolyDebug * iToCopy);
  void SetTrackIJKBoxTrigger(int iTrigger, CATPolyDebug * iToCopy);
  void SetKeepAllVoronoisTrigger(int iTrigger, CATPolyDebug * iToCopy);
  void SetCPTShowGrids(int iShow, CATPolyDebug * iToCopy);
  void SetCPTShowGradients(int iShow, CATPolyDebug * iToCopy);
  void SetCPTShowDistances(int iShow, CATPolyDebug * iToCopy);
  void SetCPTShowUnboundedVor(int iShow, CATPolyDebug * iToCopy);
  void SetCPTShowBoxes(int iShow, CATPolyDebug * iToCopy);
  void SetCPTBoxActive(int iActive, CATPolyDebug * iToCopy);
  void SetCPTBoxValue(int iPos, float iVal, CATPolyDebug * iToCopy);
  void SetPostCPTFocusBoxActive(int iActive, CATPolyDebug * iToCopy);
  void SetPostCPTFocusBoxValue(int iPos, float iVal, CATPolyDebug * iToCopy);
  void SetCPTShowGeneratingCells(int iShow, CATPolyDebug * iToCopy);
  void SetCPTShowRecoveryMesh(int iShow, CATPolyDebug * iToCopy);
  void SetCPTForceLinearExtendMode(int iForce, CATPolyDebug * iToCopy);
  void SetCPTForceNbAddedVoxels(int iNbAdded, CATPolyDebug * iToCopy);

  // Utilitaire de calcul de longueur d'une mantisse (bourrin, mais efficace)
  static int GetNbDigitsForPositiveNumber(int iNum);

  // Utilitaires d'ecriture de l'avancement
  static int InitializeStepForReport(char * iStepName, int iStepNumber=0, int iDeltaPercent=1); // rend 0 si pas de report
  static void ReportProgress(CATCGMOutput & s, int iPercent);

  /*
  // Ajout ou recuperation d'une rep de debug
  static void AddDebugRep(CAT3DRep * iRep, char * iTitle, int iUpdateDebug=0, int iReplaceIfSameTitle=0);
  CAT3DRep * GetDebugRep(char * iTitle, int iOccurenceIndex=0);
  void AddDebugRepToList(CAT3DRep * iRep, char * iTitle, int iReplaceIfSameTitle=0);

  // Structure destinee a associer des reps a des intitules de debug (char*)
  struct DebugRepAssoc {
    CAT3DRep * _DebugRep;
    char     * _Title;
    DebugRepAssoc();
    ~DebugRepAssoc();
    DebugRepAssoc & operator= (const DebugRepAssoc &iOther) ;
  };
  */

  // Data
  // ----

  // Longueur de segment de polyline ou d'arete de triangle au dela de laquelle on
  // dumpe des points intermediaires pour eviter des imprecisions lors d'un trace par un
  // "chart" excel
  float _SegmentLengthThreshold;

  // Path d'un fichier utilisable pour les ecritures massives 
  char * _DummyOutputFile;

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Tableau destine au tuning des ecritures: liste de niveaux de dump a affecter aux parties de l'algo
  int   _DumpLevel[_DumpLevelSize];

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Tableau destine a la mise au point de l'algo: liste de flags mis a 1 pour tester rapidement
  // des developpements, qui sont du coup individuellement debrayables (ou combinables)  par declaratif
  int   _AlgoTest[_AlgoTestSize];

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Faut-il ecrire le % d'avancement de chaque step
  int   _WriteProgressionPercent;

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Numero (>=1) d'une eventuelle face CATPolyImportFace a visualiser pour debug
  // Si _SaveDressUpInCGRFile==1, cette face (ou ces faces) seront sauvees sous %HOME%
  // Triggers = {DisplayVtxNumbers, DisplayTriangleNumbers, DisplayTrianglesOri, DisplayBdBars,
  //             DisplayBars, DisplayFaceName}
  //   0=no display, 1=display, -1=keep default
  int   _FaceNumberToDisplay;
  int   _SaveDressUpInCGRFile;

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Custo des CATPolyVoxelTreeImp (import ou autofillet)
  // Pilot = {0: MaxAreaSize,
  //          1: InitialNbIdsPerRecord,
  //          2: InitialAreaSize,
  //          3: MultiplyFactorForRelocatedBlocks,
  //          4: AddedWordsForLockedBlockInBigBlock,
  //          5: AddedWordsWhenReallocatedArea }
  // -1 = keep default, otherwise take value
#define VOXELPILOTSSIZE CATPolyDebug::_VoxelPilotSize
  enum { _VoxelPilotSize = 6 };
  enum { _VoxelMaxAreaSize_, _VoxelInitialNbIdsPerRecord_, _VoxelInitialAreaSize_,
         _VoxelMultiplyFactorForRelocatedBlocks_,
         _VoxelAddedWordsForLockedBlockInBigBlock_, _VoxelAddedWordsWhenReallocatedArea_ };
  int    _VoxelPilot[_VoxelPilotSize];
  void SetVoxelPilot(int iPos, int iPilot, CATPolyDebug * iToCopy);
#define DVOXL( x ) CATPolyDebug::_pdbg->_VoxelPilot[CATPolyDebug::_Voxel##x##_]

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Custo de l'habillage des triangles (import ou booleen)
  // Triggers = {0;DisplayVtxNumbers, 
  //             1;DisplayTriangleNumbers,
  //             2;DisplayTrianglesOri,
  //             3:DisplayBdBars (import)
  //             4:DisplayBars,
  //             5:DisplayFaceName(import) / ClashBarName(bool),
  //             6:DisplayBodyBdBars,
  //             7:Display normals at vertices
  //             8:Display only picked triangle
  //             9:Ancestor triangle (bool)
  //            10:Triangle family (bool)
  //            11:Numeros de vtx/tr selon bool objects au lieu de poly-model
  //            12:DisplayOwningFace (bool)   0:no, 1=wireframe, 2=1+vtx, 3=2+tr.names, 4=3+tr.ori
  //            13:DisplayCCxNum (bool)   0:no, 1=yes (on vertices and triangles bar & inside-splits)
  //            14:OnlyOpNum (bool)   0:both, 1=1st opd, 2=2nd opd
  //            15:OnlyInitTr (bool)  0:all triangles, 1=init triangles, 2=final triangles
  //              }
  //   0=no display, 1=display, -1=keep default
    
  enum { _DisplayTriggersSize = 18 };
  int   _DressUpDisplayTriggers[_DisplayTriggersSize];

  enum { _DisplayVtxNumbers_=0, _DisplayTriangleNumbers_, _DisplayTrianglesOri_,
    _DisplayBdBars_, _DisplayBars_, _DisplayFaceOrBarName_, _DisplayBodyBdBars_,
    _DisplayVertexNormals_ /*_DisplayNeighbors_*/,
    _DisplayTrSplits_, _DisplayAncestors_, _DisplayFamily_, _DisplayBoolNumbers_,
    _DisplayOwningFace_, _DisplayCCxNum_, _DisplayCondenserCCx_, _DisplayCondenserIndex_,
    _DisplayOnlyOpNum_, _DisplayOnlyInitTr_
  };
#define NULLDTRIGGERS {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#define PYD( x ) CATPolyDebug::_Display##x##_
#define DPYD( x ) CATPolyDebug::_pdbg->_DressUpDisplayTriggers[CATPolyDebug::_Display##x##_]

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Faut-il habiller les faces GP lorsqu'elles sont selectionnees (habillage fugitif au dialogue)
  // 0=non, 1=oui, 2=oui+visualiser le cgmid
  int   _DressUpPickedFaceUponSelection;

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Faut-il dessiner un octree representant les faces GP lorsqu'elles sont selectionnees (habillage fugitif au dialogue)
  // 0=non, 1=oui a partir des points, 2=oui a partir des triangles, 3=oui a partir des 2
  // _ShowOctreeAttributes = {MajoDepth, IdMode, AttachToMaxDepth, NSubX, NSubY, NSubZ, DebugTriangleNumber };
  int   _ShowOctreeUponSelection;
  enum { _ShowOctreeAttributesSize = 7 };
  int   _ShowOctreeAttributes[_ShowOctreeAttributesSize];
  float _VoxelTolerance; // triangles and vertices are inflated by this value

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Faut-il tester les confusions entre vtx au sein des faces gp (-1=std(=non), 0=non, 1=oui)
  int   _WatchAddressesDuplicatesInsideFaces;


  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Debug CPT (les 3 premieres sections sont exclusives)
  // Faut-il ne generer et conserver que le ou les polyedres de Voronois associes a la cellule donnee :
  // _KeepOnlyVoronoiData = { cell_dimension, cell_idx1, cell_idx2, VoronoiPol_number, Pass_Number, InvolveRecoveryMesh }
  // cell_idx2 est utilisee uniquement pour designer une edge (dim=1) entre les vertex cell_idx1 et cell_idx2
  int          _KeepOnlyVoronoiData[6];

  // Faut-il generer toute la CPT mais ne conserver et ecrire la generation que des Voronoi pols
  // qui contiennent au moins un point interieur a la boite IJK donnee
  int          _TrackIJKBoxTrigger; // following array is ignored if _TrackIJKBoxTrigger==0
  unsigned int _TrackIJKBoxData[6]; // {IMin,IMax, JMin,JMax, KMin,KMax}

  // Faut-il conserver tous les polyedres de Voronoi
  int          _KeepAllVoronoisTrigger;

  // Faut-il limiter le CPT a une boite ?
  int          _CPTBoxActive;
  float        _CPTBoxValue[6];

  // Faut-il eliminer les champs de la VRep exterieurs a une boite (focus posterieur a la generation de VRep)
  int          _PostCPTFocusBoxActive;
  float        _PostCPTFocusBoxValue[6];

  // Faut-il visualiser les points interieurs (_CPTShowGrids==1) ou meme exterieurs (_CPTShowGrids==2)
  // avec les vecteurs gradients, avec les distances en annotation, ou pas
  int          _CPTShowGrids;
  int          _CPTShowGradients;
  int          _CPTShowDistances;
  int          _CPTShowUnboundedVor; // visualiser les cones, wedges ou prismes generateurs de voronois

  // Faut-il visualiser les boites des points interieurs (et la boite complete de la vrep)
  int          _CPTShowBoxes;

  // Faut-il visualiser un body par cellule (vertex, edge, triangle) ayant genere un polyedre de Voronoi conserve
  int          _CPTShowGeneratingCells;

  // Faut-il visualiser un body par cellule (vertex, edge, triangle) appartenant au mesh de recuperation des triangles degeneres
  int          _CPTShowRecoveryMesh;

  // Faut-il forcer le mode LinearExtend (si != -1)
  int          _CPTForceLinearExtendMode;

  // Nombre de voxels "extend" pour le mode ExtendedBorderMode
  int          _CPTForceNbAddedVoxels;

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // Debug Booleen:

  // Faut-il appliquer une tolerance (=1/hauteur triangle) aux coords barycentriques
  int   _ToleranceOnBaryCoord;

  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
  // L'existence de l'objet statique CATPolyDebug conditionne l'utilisation des variables
  // d'environnement et du declaratif de debug polyedrique: 

  // Le seul getenv inconditionnel (CATCGMDebugPoly) sert a allouer ou non cet objet
  // s'il existe, on tentera de lire toutes les variables par getenv (CATCGMDebugPoly+nom),
  // sinon elles prendront les valeurs par defaut (ou seront affectees par le debugger).
  // Si l'affectation par getenv n'est pas concluante, on tentera de lire le chemin d'un fichier
  // declaratif (CATCGMDebugPolyDeclarative) et les valuations des variables non deja affectees
  // par un GetEnv direct se feront par le declaratif (lignes "var = valeur" sans commentaire #)

  // Cette initialisation (getenv + parcours du declaratif) est refaite ou non a chaque nouvel
  // operateur, selon la variable d'environnement CATCGMDebugPolyDynamicDcl
  // (relecture si =1, mais le chemin du declaratif n'est jamais relu, le nom du fichier ne peut
  // changer tant que la dll qui contient l'objet PolyDebug n'est pas dechargee.

  // L'affectation directe par le debugger (visual studio ou autre) ne surpassera ces
  // mecanismes que si le point d'arret est pose apres la lecture du declaratif

  int    _DynamicDcl;
  int    _InitDone;
  const char * _PolyDeclarative;

  // Liste des noms de variables et methodes d'affectation associees
  // Un element de tableau aura pour nom "TableName[index]"
  CATPolyDebugSetting _VSet[_MaxNbVar];
  int _NbVar; // taille effective

  // Gestion de l'avancement des steps
  int _CurStepNumber;
  int _LastPercentReported;
  int _DeltaPercent;
  char * _StepName;

  // Liste de reps de debug et methode d'affichage
  DressUpFaceMethod _DebugRepDisplayMethod;
  /*
  DebugRepAssoc   * _DebugRepList;
  int               _DebugRepListSize;
  */
};

inline void CATPolyDebug::SetDebugRepDisplayMethod(DressUpFaceMethod iDUMethod) {
  _DebugRepDisplayMethod = iDUMethod; }

inline DressUpFaceMethod CATPolyDebug::GetDebugRepDisplayMethod() const {
  return _DebugRepDisplayMethod; }

// Classes dedicated to iostream (dump int, float or double value on imposed length)
// option for aligned dump of float or double: 0 = not concise, 1 = align left and fill with blanks, 2 = align left and cut if precision too big (default)
#define FLOATDUMP(lon,val) CATPolyFloatDump( lon , val )
#define FLOATDUMPALIGNED(lon,val,option) CATPolyFloatDump( lon , val , option )
#define INTDUMP(lon,val) CATPolyIntegerDump( lon , val )

class CATPolyFloatDump 
{
public:
  inline CATPolyFloatDump(int iLength, const double iVal, const int iConcise=2);
  inline CATPolyFloatDump(int iLength, const float iVal, const int iConcise=2);
  friend ExportedByPolyhedralUtilities CATCGMOutput& operator<< (CATCGMOutput& s, const CATPolyFloatDump & iObj);
  
private:
  double         _Value;
  int            _Length;
  int            _Conciseness;
};

inline CATPolyFloatDump::CATPolyFloatDump(int iLength, const double iVal, const int iConcise) :
_Value(iVal), _Length(iLength), _Conciseness(iConcise) {
}
inline CATPolyFloatDump::CATPolyFloatDump(int iLength, const float iVal, const int iConcise) :
_Value((double)iVal), _Length(iLength), _Conciseness(iConcise) {
}

class CATPolyIntegerDump 
{
public:
  inline CATPolyIntegerDump(int iLength, const int iVal);
  friend ExportedByPolyhedralUtilities CATCGMOutput& operator<< (CATCGMOutput& s, const CATPolyIntegerDump & iObj);
  
private:
  int            _Value;
  int            _Length;
};

inline CATPolyIntegerDump::CATPolyIntegerDump(int iLength, const int iVal) :
_Value(iVal), _Length(iLength) {
}

// Classes dedicated to iostream (dump array of int, or float or double values on imposed length)
// typ can be "int", "float" or "double", list is the array itself, nb is its length
// "item_length" is the number of characters used for one single value (a default is provided in DUMPARRAY)
// "nb_per_line" is the number of items dumped on one line, -1 means all items should be dumped on one line
// Note that a CATListOfInt may be input instead of an int*, in this case, the size (nb) can be left null
#define DUMPARRAY( typ,list,nb) CATPolyDumpArrayOf##typ ( list , nb , 0)
#define DUMPARRAYLG( typ,list,nb,item_length) CATPolyDumpArrayOf##typ ( list , nb , 0, item_length )
#define DUMPARRAYPERLINES( typ,list,nb,nb_per_line) CATPolyDumpArrayOf##typ ( list , nb , nb_per_line )
#define DUMPARRAYPERLINESLG( typ,list,nb,nb_per_line,item_length) CATPolyDumpArrayOf##typ ( list , nb , nb_per_line , item_length )

void CATPolyDumpArrayUtility(CATCGMOutput& s, int iType, // iType:1=int, 2=float, 3=double
                             void * iList, int iListSize, int iForcedNbPerLine, int iItemLength,
                             const CATListOfInt * const iCollec = 0);

class CATPolyDumpArrayOfint
{
public:
  inline CATPolyDumpArrayOfint(const int * iList, const int iNbValues, const int iNbPerLine=0,
    const int iLength = 10);
  inline CATPolyDumpArrayOfint(const CATListOfInt & iCollec, const int iNbValues, const int iNbPerLine=0,
    const int iLength = 10);
  friend ExportedByPolyhedralUtilities CATCGMOutput& operator<< (CATCGMOutput& s, const CATPolyDumpArrayOfint & iObj);
  
private:
  const CATListOfInt * _Collec;
  const int *          _List;
  const int            _Nb;
  const int            _Length;          // number of characters used for each item
  const int            _ForcedNbPerLine; // -1=>infinite, 0=>5 or 10 according to _Length
};

inline CATPolyDumpArrayOfint::CATPolyDumpArrayOfint(const int * iList, const int iNbValues, const int iNbPerLine, const int iLength) :
_Collec(0), _List(iList), _Nb(iNbValues), _Length(iLength), _ForcedNbPerLine(iNbPerLine) {
}
  inline CATPolyDumpArrayOfint::CATPolyDumpArrayOfint(const CATListOfInt & iCollec, const int iNbValues, const int iNbPerLine, const int iLength) :
_Collec(&iCollec), _List(0), _Nb(iCollec.Size()), _Length(iLength), _ForcedNbPerLine(iNbPerLine) {
}

class CATPolyDumpArrayOffloat 
{
public:
  inline CATPolyDumpArrayOffloat(const float * iList, const int iNbValues, const int iNbPerLine=0,
    const int iLength = 10);
  friend ExportedByPolyhedralUtilities CATCGMOutput& operator<< (CATCGMOutput& s, const CATPolyDumpArrayOffloat & iObj);
  
private:
  const float *        _List;
  const int            _Nb;
  const int            _Length;          // number of characters used for each item
  const int            _ForcedNbPerLine; // -1=>infinite, 0=>5 or 10 according to _Length
};

inline CATPolyDumpArrayOffloat::CATPolyDumpArrayOffloat(const float * iList, const int iNbValues, const int iNbPerLine, const int iLength) :
_List(iList), _Nb(iNbValues), _Length(iLength), _ForcedNbPerLine(iNbPerLine) {
}

class CATPolyDumpArrayOfdouble 
{
public:
  inline CATPolyDumpArrayOfdouble(const double * iList, const int iNbValues, const int iNbPerLine=0,
    const int iLength = 10);
  friend ExportedByPolyhedralUtilities CATCGMOutput& operator<< (CATCGMOutput& s, const CATPolyDumpArrayOfdouble & iObj);
  
private:
  const double *       _List;
  const int            _Nb;
  const int            _Length;          // number of characters used for each item
  const int            _ForcedNbPerLine; // -1=>infinite, 0=>5 or 10 according to _Length
};

inline CATPolyDumpArrayOfdouble::CATPolyDumpArrayOfdouble(const double * iList, const int iNbValues, const int iNbPerLine, const int iLength) :
_List(iList), _Nb(iNbValues), _Length(iLength), _ForcedNbPerLine(iNbPerLine) {
}

// Class dedicated to iostream (dump GP)
#define GPDUMP(val) CATPolyGPDump( val )
class CATGraphicPrimitive;

class CATPolyGPDump 
{
public:
  inline CATPolyGPDump(const CATGraphicPrimitive * iGP);
  friend ExportedByPolyhedralUtilities CATCGMOutput& operator<< (CATCGMOutput& s, const CATPolyGPDump & iObj);
  
private:
  const CATGraphicPrimitive *         _GP;
};

inline CATPolyGPDump::CATPolyGPDump(const CATGraphicPrimitive * iGP) :
_GP(iGP) {
}

// Inline definition of a non member function that dumps a CATPolyDumpable object
// Purpose = have this function readily available in "watch" windows in VisualC++
inline int DumpPoly(const void* iElt) {
  if (iElt) {
    const CATPolyDumpable * obj = (const CATPolyDumpable *) iElt;
    obj->Dump(cgmout);
  }
  return 0;
}

#endif
