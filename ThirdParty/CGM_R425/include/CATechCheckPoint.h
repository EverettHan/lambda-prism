#ifndef CATechCheckPoint_h
#define CATechCheckPoint_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//-------------------------------------------------------------------------------------------------
//   Infrastructure for CheckPoint/Inspector deployment
//-------------------------------------------------------------------------------------------------

/* 
* ------------------------------------------------------------------------------------------------------- 
*   CATech : Small Open Infrastructure for CheckPoint/Inspector paradigm 
*
*   This design is intended to bring the following enhancements :    
*
*       1/ Ambivalent :  Dynamic plug-in onFly , it means requiring no particular ODT infrastructure
*                        Validation checker should be as ambivalent as possible :
*                           -> under optimized commercial product / ODT replay (should work with Phoenix technologies)
*                         Differences are only about the report is given back and associated behavior.
*                         Always available accross the various workspace categories : Nominal, Convergence, Innovative.
*
*       2/ Immersive  : It should work along with various interactive context
*                       it means with no particular dedicated workbench
*                          integrated user interface should means generalized toolbar.
*                        -> 2008 Target
*
*       3/ Dynamic refinement : User Filter configurable and adaptative according to specific purpose 
*                        -> 2008 Target 
*
*  2007 : Creation for extract/external support software (Higher level and fewer impact on commercial one)
*  2008 : Small enhancement for execution history given as runtime tree  
*            (tiny Command pattern with explicit insertion on appropriate checkpoint)
*            (genuine service complementary (global overview ) to rich immersive)
*
* ------------------------------------------------------------------------------------------------------- 
*/
#include "ExportedByCATTechTools.h"
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATDataType.h"
#include "CATBoolean.h"
 
#include "CATLISTV_CATechInspector.h"
#include "CATListOfInt.h"
 
 
typedef unsigned int CATPhx_Category ;

typedef unsigned int CATPhx_Maturity ;

typedef unsigned int CATPhx_OneShotType;

class CATechCheckPoint;
class CATechManager;
class CATCGMTransaction;
class CATCGMOperator;
 

//-------------------------------------------------------------------------------------- 
// Inspectors identificators are manipulated 
//     either by integer (mask driven), either by name (user understable)
//
//  this association between name and hexadecimal integer value 
//    is predefined by customisation inside dictionnary
//       CNext\code\Phoenix\*.ComputationalCategory
//
//  with set of associations given by tuple value 
//        //    Name     MaskInteger  EggsLateType 
//        Tessellate     00400000   CATTessellate
//
//  Third (last) value of EggsLateType allows to extends  meaningfull context of a particular breakpoint
//     (Extract/Redo and CheckPoint/Inspector last integration ...)
//
//-------------------------------------------------------------------------------------- 

// Maturity Level
#define CATPhx_None                            0x00000000
#define CATPhx_Initial                         0x00000010
#define CATPhx_UnderDev                        0x00000020
#define CATPhx_Achieved                        0x00000100  // Completion=Defined=Run
#define CATPhx_Managed                         0x00000200    
#define CATPhx_Measured                        0x00000400  //  Controlled characteristics

// Transaction : Begin/End/OneShot
#define CATPhx_OneShot                         0x00000001
#define CATPhx_Begin                           0x00000002
#define CATPhx_End                             0x00000004

// Global Category
#define CATPhx_MaskCategory                    0xFFF00000  // Category  / 
#define CATPhx_MaskSubCategory                 0x000FF000  //   SubCategory  / 
#define CATPhx_MaskComplexity                  0x00000FFF  //    Maturity/Transaction
#define CATPhx_MaskMaturity                    0x00000FF0  //     Maturity 
#define CATPhx_MaskTransaction                 0x0000000F  //     Transaction 
   
 
//
// High Mask = Category SubCategory : Operators
// Low Mask = Complexity : Entities
//
#define CATPhx_CGMReady                        0x08000000  // NCGM  : Read+Completed
#define CATPhx_Tessellate                      0x04000000  // Tess  : Global CATTessellate
#define CATPhx_MemoryManager                   0x02000000  // MemoryManager :
#define CATPhx_ImplementBehavior               0x01000000  // Operator 
#define CATPhx_Face                            0x00040000  // Face  
#define CATPhx_HybClashFEComputed              0x00080000  // Clash Face/Edge
#define CATPhx_HLRComputed                     0x10000000  // HLR  : Computed
#define CATPhx_SILHComputed                    0x20000000  // SILH 
#define CATPhx_MacroHLRComputed                0x40000000  // MacroHLR
#define CATPhx_ExactSceneHLRComputed           0x80000000  // ExactSceneHLR
#define CATPhx_CBSIComputed                    0x00100000  // CATBodySelfIntersector (doit etre aligne sur CNext\code\Phoenix\*.ComputationalCategory)
#define CATPhx_HLROperComputed                 0x00200000  // HLR Operator (Spatial interfaces)
#define CATPhx_TESSPAComputed                  0x00400000  // CATTessellatePreAnalysis (aligne sur CNext\code\Phoenix\*.ComputationalCategory)


//------------------------------------------------------------------------
// CATechCheckPoint
//   For Small Open Infrastructure for CheckPoint/Inspector paradigm 
//------------------------------------------------------------------------
class  ExportedByCATTechTools CATechCheckPoint
{ 
public :

  //------------------------------------------------------------------------
  // For  Availabality control
  //    dedicated to external OnFly analysis
  //------------------------------------------------------------------------

  /** 
  *  Service : Break Inspectores is activated
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  inline static HRESULT  IsActivated()  ;


  /** 
  *   PublishTransactionContext  
  *
  * @param i0Before_1After
  *
  * @param iTransaction.
  *
  * @param iOperator.
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  static HRESULT  PublishTransactionContext(const CATBoolean          i0Before_1After,
                                            const CATCGMTransaction * iTransaction,  
                                            CATCGMOperator          * iOperator);
 
  //-------------------------------------------------------------------------------------------------
  // CheckPoint deployment inside Release software
  //-------------------------------------------------------------------------------------------------

  /** 
  *  Publish "OneShot" to engage associated Inspectors.
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  inline static HRESULT OneShot(CATPhx_Category             iComputationalCategory,
                              void                                     *   iMainConcern,
                              void                                     *   iInput                   = NULL ,
                              const char                                   iRootCategoryBeginEnd[]  = "" ,
                              const char                                   iRelativeCategoryOneShot[] = "" );


  /** 
  *  Publish "Begin" to engage associated Inspectors.
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  inline static HRESULT Begin(CATPhx_Category             iComputationalCategory,
                              void                                     *   iMainConcern,
                              void                                     *   iInput                   = NULL ,
                              const char                                   iRootCategoryBeginEnd[]  = "" ,
                              const char                                   iRelativeCategoryOneShot[] = "" );

  /** 
  *  Publish "End" to engage associated Inspectors.
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  inline static HRESULT End(CATPhx_Category             iComputationalCategory,
                            void                                     *   iMainConcern,
                            void                                     *   iInput                   = NULL ,
                            const char                                   iRootCategoryBeginEnd[]  = "" ,
                            const char                                   iRelativeCategoryOneShot[] = "" );

  
  //------------------------------------------------------------------------
  // SetUp  for interactive purpose
  //------------------------------------------------------------------------
  /** 
  *  Get configuration Status
  *
  * @param oCheckPoints (Names). 
  *
  * @param oInspectors (Names). 
  *
  * @param oActivationStatus (0/1). 
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  static HRESULT  GetCheckPointsInspectors(CATListOfCATUnicodeString  & oCheckPoints,
                                           CATListOfCATUnicodeString  & oInspectors,
                                           CATListOfInt               & oActivationStatus  );

  /** 
  *  Set configuration Status
  *
  * @param iCheckPoints (Names). 
  *
  * @param iInspectors (Names). 
  *
  * @param iActivationStatus (0/1). 
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  static HRESULT  SetCheckPointsInspectors(const CATListOfCATUnicodeString  & iCheckPoints,
                                           const CATListOfCATUnicodeString  & iInspectors,
                                           const CATListOfInt               & iActivationStatus  );

  /** 
  *  Set CheckPoint Inspector Status
  *
  * @param iCheckPoint (Name). 
  *
  * @param iInspector (Name). 
  *
  * @param iActivationStatus (0/1). 
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  static HRESULT  SetCheckPointInspector(const CATUnicodeString  & iCheckPoint,
                                         const CATUnicodeString  & iInspector,
                                         const int                 iActivationStatus  );


  /** 
  *  GetCATCGMOperator configuration Status
  *
  * @return
  *      TRUE   if CATCGMOperator is active<br>
  *      FALSE  otherwise<br>
  */ 
  static CATBoolean  GetCATCGMOperator();

  /** 
  *  SetCATCGMOperator configuration Status
  *
  * @param oActivationStatus (FALSE/TRUE). 
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  static HRESULT  SetCATCGMOperator(const CATBoolean iActivationStatus  );

  /** 
  *  Disable
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  inline static HRESULT  Disable()  ;

  /** 
  *  EnableAll
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  inline static HRESULT  EnableAll()  ;

  //-------------------------------------------------------------------------------------------------
  // Constructors / Destructors
  //-------------------------------------------------------------------------------------------------

  /** 
  *  Publish "OneShot" to engage associated Inspectors.
  *
  * @param iComputationalCategory.
  *     Computational Category.
  *
  * @param iMainConcern.
  *     Main Concern.
  *
  * @param iMaturity.
  *     Maturity.
  *
  * @param iInput.
  *     Input.
  *
  * @param iRootCategoryBeginEnd.
  *     const static global variable.
  *
  * @param iRelativeCategoryOneShot.
  *     const static global variable.
  *
  * @param iRootCategoryBeginEnd 
  *     Mandatory implementation as static variable.
  *     Necessary for ObjectModeler Inspector Adhesion.
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */        
  CATechCheckPoint(CATPhx_Category             iComputationalCategory,
                              void                                     *   iMainConcern,
                              void                                     *   iInput                   = NULL ,
                              const char                                   iRootCategoryBeginEnd[]  = "" ,
                              const char                                   iRelativeCategoryOneShot[] = "" );
 

  ~CATechCheckPoint() ;

    
  /**
  * dummy constructor <br>
  */ 
  CATechCheckPoint() ;

  /**
  * constructor by copy <br>
  */ 
  CATechCheckPoint (const CATechCheckPoint            & iCheckPoint);          

  /**
  * copy by constructor <br>
  */ 
  CATechCheckPoint& operator=(const CATechCheckPoint  & iCheckPoint);  

  /**
  * dummy constructor <br>
  */ 
  inline   int operator != (const CATechCheckPoint & iCopy) const;

  /**
  * dummy constructor <br>
  */ 
  inline   int operator == (const CATechCheckPoint & iCopy) const;

  //-------------------------------------------------------------------------------------------------
  // Event emitter 
  //-------------------------------------------------------------------------------------------------

  /** 
  *  Publish "OneShot" to engage associated Inspectors.
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  inline HRESULT OneShot();


  /** 
  *  Publish "Begin" to engage associated Inspectors.
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  inline HRESULT Begin();

  /** 
  *  Publish "End" to engage associated Inspectors.
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  inline HRESULT End();

  /** 
  *     GetOneShotType : Get OneShot Type
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  inline CATPhx_OneShotType  GetOneShotType() const;

  //------------------------------------------------------------------------
  // String/Computational  Category
  //     for booting an CheckPoint/Inspector coupling 
  //     with System and dictionnary services Interface/Implementation.
  //------------------------------------------------------------------------


  /** 
  *     GetComputationalComplexity : Helpfull for quick runtime filtering
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  inline CATPhx_Category  GetComputationalCategory() const;
    

  /** 
  *     GetChkPtMaturity : Helpfull for quick runtime filtering
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  inline CATPhx_Maturity  GetChkPtMaturity() const;
 
 
    
  /** 
  *     VolatileStringGetRootBeginEnd  
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  inline const char * VolatileStringGetRootBeginEnd() const;
 
    
  /** 
  *     VolatileStringGetRelativeOneShot  
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  inline const char * VolatileStringGetRelativeOneShot() const;


  //-------------------------------------------------------------------------------------------------
  // MainConcern : anything but meaningfull only according to computational category context.
  // Input : anything but meaningfull only according to computational category context.
  //-------------------------------------------------------------------------------------------------

  /** 
  *    MainConcern
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  inline HRESULT HasMainConcern() const;
  inline void  * GetMainConcern() const;
  inline HRESULT SetMainConcern(void  *   iMainConcern);
  inline HRESULT UnsetMainConcern();


  /** 
  *    Input
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  inline HRESULT HasInput() const;
  inline void  * GetInput() const;
  inline HRESULT SetInput(void  *   iInput);
  inline HRESULT UnsetInput();


  /** 
  *    Output
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  inline HRESULT HasOutput() const;
  inline void  * GetOutput() const;
  inline HRESULT SetOutput(void  *   iOutput);
  inline HRESULT UnsetOutput();

  

  /** 
  *    ULongValue
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  inline CATULONG64 GetULongValue() const;
  inline HRESULT    SetULongValue(CATULONG64 iOutput);
 
  //------------------------------------------------------------------------
  // For Spatial management
  //    Box1D / Box2D / Box3D  
  //------------------------------------------------------------------------

  /**
  * Parametric Curves
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  inline HRESULT HasBox1D(const unsigned int iSupport1DIndex) const;
  inline HRESULT GetSupport1D(unsigned int & oSupport1DIndex) const;
  inline HRESULT GetBox1D(double w[2]) const;
  inline HRESULT SetBox1D(unsigned int iSupport1DIndex, const double w[2]);
  inline HRESULT UnsetBox1D();


  /**
  * Parametric Surfaces
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  inline HRESULT HasBox2D(const unsigned int iSupport2DIndex) const;
  inline HRESULT GetSupport2D(unsigned int & oSupport2DIndex) const;
  inline HRESULT GetBox2D(double u[2], double v[2]) const;
  inline HRESULT SetBox2D(unsigned int iSupport2DIndex, const double u[2], const double v[2]);
  inline HRESULT UnsetBox2D();

  /**
  * Spatial Coordinates
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  inline HRESULT HasBox3D(const unsigned int iSupport3DIndex) const;
  inline HRESULT GetSupport3D(unsigned int & oSupport3DIndex) const;
  inline HRESULT GetBox3D(double x[2], double y[2], double z[2]) const;
  inline HRESULT SetBox3D(unsigned int iSupport3DIndex, const double x[2], const double y[2], const double z[2]);
  inline HRESULT UnsetBox3D();



  //------------------------------------------------------------------------
  // For IsAvailable / ConvertToComputationalCategory
  //------------------------------------------------------------------------
 

  /** 
  *  Service : IsAvailable / Usefull for enhanced attributes specfications about this CheckPoint 
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  inline static HRESULT  IsAvailable( const CATPhx_Category  iCategoryFilter = 0xFFFFFFFF )  ;
 
   /** 
  *  Service : ConvertToComputationalCategory : Helpfull for quick runtime filtering
  *
  * @param iConvertToComputationalCategory.
  *     Computational Category.
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  static CATPhx_Category   ConvertToComputationalCategory(const char     * iConvertToComputationalCategory );

  /** 
  *  Service : SearchInspectors : Helpfull for quick runtime filtering
  *
  * @param iComputationalCategory.
  *     Computational Category.
  *
  * @param oInspectors (RTV). 
  *
  * @param oInspectorNames (Names for debug). 
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */ 
  static HRESULT  SearchInspectors(const CATPhx_Category               iComputationalCategory,
                                   CATLISTV(CATechInspector_var)     & oInspectors ,
                                   CATListOfCATUnicodeString         & oInspectorNames );

 

  /** 
  *  GetCurrentBeginEndDepth :  .. 
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  inline static int GetCurrentBeginEndDepth()  ;

  /** 
  *  GetFilteringBeginEndDepth :  .. 
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  inline static int GetFilteringBeginEndDepth()  ;
 
 

                       
private :


  /** 
  * PublishBreakPoint  to engage associated Inspectors.
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  static HRESULT PublishBreakPoint(const CATechCheckPoint & iBreakPoint);


  /** 
  *  Publish _OneShot to engage associated Inspectors.
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  HRESULT _OneShot();

  /** 
  *  Publish _Begin to engage associated Inspectors.
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  HRESULT _Begin();

  /** 
  *  Publish _End to engage associated Inspectors.
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  HRESULT _End();



  //------------------------------------------------------------------------
  //   Values
  //------------------------------------------------------------------------
  struct 
  {
    unsigned          _with1DBox  : 1;    // 1DBox 
    unsigned          _with2DBox  : 1;    // 2DBox
    unsigned          _with3DBox  : 1;    // 3DBox
 

    unsigned int      _Support1DIndex ;     // Support1DIndex
    unsigned int      _Support2DIndex ;     // Support2DIndex
    unsigned int      _Support3DIndex ;     // Support3DIndex
 

    double            _w[2];                  // 1D Box 

    double            _u[2];                  // 2D Box 
    double            _v[2];                  //  

    double            _x[2];                  // 3D Box 
    double            _y[2];                  //  
    double            _z[2];                  //  


    const char * _RootCategoryBeginEnd;     // RootCategoryBeginEnd
    const char * _RelativeCategoryOneShot;    // RelativeCategoryOneShot
 
    CATULONG64        _ULongValue;          // ULongValue

 
    unsigned int      _ComputationalCategory ;     // ComputationalCategory
 

    void        *     _MainConcern;                // MainConcern  Input Output
    void        *     _Input;
    void        *     _Output;

  } spartan;


  /** 
  *  _InitializeUnderPressure
  *
  * @return
  *      S_OK   if request succeeded <br>
  *      E_FAIL if request failed <br>
  */           
  static void   _Initialize();
 
  //------------------------------------------------------------------------
  //  Internal management
  //------------------------------------------------------------------------
  static int                                 _CurrentBeginEndDepth;     
  static int                                 _FilteringBeginEndDepth;     
  static CATPhx_Category                     _CumulativeMask;
  static CATListOfCATUnicodeString           _InspectorNamesFilter;
  static CATBoolean                          _IsInitialized;
  static CATBoolean                          _CATCGMOperator;

  friend class CATechManager;
};

//-------------------------------------------------------------------------------------------------
// IsActivated
//-------------------------------------------------------------------------------------------------
inline   HRESULT  CATechCheckPoint::IsActivated()  
{ 
  if ( ! _IsInitialized ) CATechCheckPoint::_Initialize();  
  HRESULT rc =   _CumulativeMask  ? S_OK : E_FAIL;
  return rc;
}

//-------------------------------------------------------------------------------------------------
// Disable
//-------------------------------------------------------------------------------------------------
inline   HRESULT  CATechCheckPoint::Disable()  
{ 
  _IsInitialized = TRUE;  
  _CumulativeMask = 0;
  return S_OK;
}

 

//-------------------------------------------------------------------------------------------------
// EnableAll
//-------------------------------------------------------------------------------------------------
inline   HRESULT  CATechCheckPoint::EnableAll()  
{ 
  if ( ! _IsInitialized ) CATechCheckPoint::_Initialize();  
  _CumulativeMask = CATPhx_MaskCategory;
  return S_OK;
}

 
//-------------------------------------------------------------------------------------------------
// IsAvailable
//-------------------------------------------------------------------------------------------------
inline   HRESULT  CATechCheckPoint::IsAvailable(const CATPhx_Category  iCategoryFilter)  
{ 
  if ( ! _IsInitialized ) CATechCheckPoint::_Initialize();  
  HRESULT rc = ( _CumulativeMask && (((iCategoryFilter&CATPhx_MaskCategory) & _CumulativeMask) == (iCategoryFilter&CATPhx_MaskCategory) ) ) ? S_OK : E_FAIL;
  return rc;
}
           

/** --------------------------------------------------------------------------------
*    CATechCheckPoint  :      OneShot/Begin/End
* -------------------------------------------------------------------------------- **/

inline   HRESULT CATechCheckPoint::OneShot(CATPhx_Category             iComputationalCategory   ,
                                             void                  *   iMainConcern             ,
                                             void                  *   iInput                   ,
                                             const char                iRootCategoryBeginEnd[]  ,
                                             const char                iRelativeCategoryOneShot[] )
{
  if ( ! _IsInitialized ) CATechCheckPoint::_Initialize();  
  if ( ! _CumulativeMask ) return E_FAIL;
  if ( ! ( iComputationalCategory & _CumulativeMask) )  return E_FAIL;
  CATechCheckPoint ChkPt(iComputationalCategory|CATPhx_OneShot,iMainConcern,iInput,iRootCategoryBeginEnd,iRelativeCategoryOneShot);
  return ChkPt.OneShot();  
}


inline   HRESULT CATechCheckPoint::Begin(CATPhx_Category             iComputationalCategory   ,
                                             void                *   iMainConcern             ,
                                             void                *   iInput                   ,
                                             const char              iRootCategoryBeginEnd[]  ,
                                             const char              iRelativeCategoryOneShot[] )
{
  if ( ! _IsInitialized ) CATechCheckPoint::_Initialize();  
  if ( ! _CumulativeMask ) return E_FAIL;
  if ( ! ( iComputationalCategory & _CumulativeMask) )  return E_FAIL;
  CATechCheckPoint ChkPt(iComputationalCategory|CATPhx_Begin,iMainConcern,iInput,iRootCategoryBeginEnd,iRelativeCategoryOneShot);
  return ChkPt.Begin();  
}


inline   HRESULT CATechCheckPoint::End(CATPhx_Category             iComputationalCategory   ,
                                           void                *   iMainConcern             ,
                                           void                *   iInput                   ,
                                           const char              iRootCategoryBeginEnd[]  ,
                                           const char              iRelativeCategoryOneShot[] )
{
  if ( ! _IsInitialized ) CATechCheckPoint::_Initialize();  
  if ( ! _CumulativeMask ) return E_FAIL;
  if ( ! ( iComputationalCategory & _CumulativeMask) )  return E_FAIL;
  CATechCheckPoint ChkPt(iComputationalCategory|CATPhx_End,iMainConcern,iInput,iRootCategoryBeginEnd,iRelativeCategoryOneShot);
  return ChkPt.End();  
}



//------------------------------------------------------------------------
// Constructors / Destructors
//------------------------------------------------------------------------

inline const char *  CATechCheckPoint::VolatileStringGetRootBeginEnd() const
{ return   spartan._RootCategoryBeginEnd; }

inline const char *  CATechCheckPoint::VolatileStringGetRelativeOneShot() const
{ return   spartan._RelativeCategoryOneShot; }


inline CATPhx_Category  CATechCheckPoint::GetComputationalCategory() const
{ return   spartan._ComputationalCategory; }

inline CATPhx_Maturity                CATechCheckPoint::GetChkPtMaturity() const
{ return (spartan._ComputationalCategory&CATPhx_MaskMaturity); }

 

//------------------------------------------------------------------------
// MainConcern
//------------------------------------------------------------------------

inline HRESULT CATechCheckPoint::HasMainConcern() const 
{ return spartan._MainConcern ? S_OK : E_FAIL; }

inline void  * CATechCheckPoint::GetMainConcern()  const 
{ return spartan._MainConcern; }

inline HRESULT CATechCheckPoint::SetMainConcern(void  *   iMainConcern) 
{ return (spartan._MainConcern = iMainConcern) ? S_OK : E_FAIL; }

inline HRESULT CATechCheckPoint::UnsetMainConcern() 
{  spartan._MainConcern = 0; return S_OK; }

 
inline HRESULT CATechCheckPoint::HasInput() const 
{ return  spartan._Input  ? S_OK : E_FAIL; }

inline void  * CATechCheckPoint::GetInput()  const 
{ return spartan._Input; }

inline HRESULT CATechCheckPoint::SetInput(void  *   iInput) 
{ return (spartan._Input = iInput) ? S_OK : E_FAIL; }

inline HRESULT CATechCheckPoint::UnsetInput() 
{  spartan._Input = 0; return S_OK; }


inline HRESULT CATechCheckPoint::HasOutput() const 
{ return  spartan._Output  ? S_OK : E_FAIL; }

inline void  * CATechCheckPoint::GetOutput()  const 
{ return  spartan._Output ; }

inline HRESULT CATechCheckPoint::SetOutput(void  *   iOutput) 
{ return (spartan._Output = iOutput) ? S_OK : E_FAIL; }

inline HRESULT CATechCheckPoint::UnsetOutput() 
{  spartan._Output = 0; return S_OK; }

//------------------------------------------------------------------------
// ULongValue
//------------------------------------------------------------------------
CATULONG64  CATechCheckPoint::GetULongValue() const
{ return  spartan._ULongValue; }

HRESULT     CATechCheckPoint::SetULongValue(CATULONG64 iOutput)
{ spartan._ULongValue = iOutput; return S_OK; }

//------------------------------------------------------------------------
// Box1D
//------------------------------------------------------------------------

inline HRESULT CATechCheckPoint::HasBox1D(const unsigned int iSupport1DIndex) const
{ return (spartan._with1DBox && (iSupport1DIndex == spartan._Support1DIndex)) ? S_OK : E_FAIL; }

inline HRESULT CATechCheckPoint::GetSupport1D(unsigned int & oSupport1DIndex) const 
{ oSupport1DIndex = spartan._Support1DIndex; return  spartan._with1DBox ? S_OK : E_FAIL; }

inline HRESULT CATechCheckPoint::GetBox1D(double w[2]) const 
{  
  w[0] = spartan._with1DBox ? spartan._w[0] : 0.0; 
  w[1] = spartan._with1DBox ? spartan._w[1] : 0.0; 
  return  spartan._with1DBox ? S_OK : E_FAIL; 
}

inline HRESULT CATechCheckPoint::SetBox1D(unsigned int iSupport1DIndex, const double w[2]) 
{ 
  spartan._with1DBox = 1;
  spartan._Support1DIndex = iSupport1DIndex;
  spartan._w[0] = w[0];
  spartan._w[1] = w[1];
  return S_OK;
}

inline HRESULT CATechCheckPoint::UnsetBox1D() 
{  spartan._with1DBox = 0; return S_OK; }

 

//------------------------------------------------------------------------
// Box2D
//------------------------------------------------------------------------

inline HRESULT CATechCheckPoint::HasBox2D(const unsigned int iSupport2DIndex) const
{ return (spartan._with2DBox && (iSupport2DIndex == spartan._Support2DIndex)) ? S_OK : E_FAIL; }

inline HRESULT CATechCheckPoint::GetSupport2D(unsigned int & oSupport2DIndex) const 
{ oSupport2DIndex = spartan._Support2DIndex; return  spartan._with2DBox ? S_OK : E_FAIL; }

inline HRESULT CATechCheckPoint::GetBox2D(double u[2], double v[2]) const 
{  
  if ( ! spartan._with2DBox  ) return E_FAIL; 
  u[0] = spartan._u[0];
  u[1] = spartan._u[1];
  v[0] = spartan._v[0];
  v[1] = spartan._v[1];
  return  S_OK;
}

inline HRESULT CATechCheckPoint::SetBox2D(unsigned int iSupport2DIndex, const double u[2], const double v[2]) 
{ 
  spartan._with2DBox = 1;
  spartan._Support2DIndex = iSupport2DIndex;
  spartan._u[0] = u[0];
  spartan._u[1] = u[1];
  spartan._v[0] = v[0];
  spartan._v[1] = v[1];
  return  S_OK;
}

inline HRESULT CATechCheckPoint::UnsetBox2D() 
{  spartan._with2DBox = 0; spartan._Support2DIndex = 0; return S_OK; }




//------------------------------------------------------------------------
// Box3D
//------------------------------------------------------------------------

inline HRESULT CATechCheckPoint::HasBox3D(const unsigned int iSupport3DIndex) const
{ return (spartan._with3DBox && (iSupport3DIndex == spartan._Support3DIndex)) ? S_OK : E_FAIL; }

inline HRESULT CATechCheckPoint::GetSupport3D(unsigned int & oSupport3DIndex) const
{ oSupport3DIndex = spartan._Support3DIndex; return  spartan._with3DBox ? S_OK : E_FAIL; }

inline HRESULT CATechCheckPoint::GetBox3D(double x[2], double y[2], double z[2]) const
{  
  if ( ! spartan._with3DBox  ) return E_FAIL; 
  x[0] = spartan._x[0];
  x[1] = spartan._x[1];
  y[0] = spartan._y[0];
  y[1] = spartan._y[1];
  z[0] = spartan._z[0];
  z[1] = spartan._z[1];
  return  S_OK;
}

inline HRESULT CATechCheckPoint::SetBox3D(unsigned int iSupport3DIndex, const double x[2], const double y[2], const double z[2])
{ 
  spartan._with3DBox = 1;
  spartan._Support3DIndex = iSupport3DIndex;
  spartan._x[0] = x[0];
  spartan._x[1] = x[1];
  spartan._y[0] = y[0];
  spartan._y[1] = y[1];
  spartan._z[0] = z[0];
  spartan._z[1] = z[1];
  return  S_OK;
}

inline HRESULT CATechCheckPoint::UnsetBox3D()
{  spartan._with3DBox = 0; spartan._Support3DIndex = 0; return S_OK; }


 
  
   
/** ------------------------------------------------------------------------
*                  OneShot / Begin / End
------------------------------------------------------------------------ */

inline HRESULT CATechCheckPoint::OneShot()
{   
  return (    CATechCheckPoint::_CumulativeMask 
    && (((spartan._ComputationalCategory & CATechCheckPoint::_CumulativeMask)&CATPhx_MaskCategory) == (spartan._ComputationalCategory&CATPhx_MaskCategory))  ) 
    ? _OneShot() : S_OK;
}
 
inline HRESULT CATechCheckPoint::Begin()
{   
  return (    CATechCheckPoint::_CumulativeMask 
    && (((spartan._ComputationalCategory & CATechCheckPoint::_CumulativeMask)&CATPhx_MaskCategory) == (spartan._ComputationalCategory&CATPhx_MaskCategory))  ) 
    ? _Begin() : S_OK;
}
 
inline HRESULT CATechCheckPoint::End()
{   
  return (    CATechCheckPoint::_CumulativeMask 
    && (((spartan._ComputationalCategory & CATechCheckPoint::_CumulativeMask)&CATPhx_MaskCategory) == (spartan._ComputationalCategory&CATPhx_MaskCategory))  ) 
    ? _End() : S_OK;
}


inline CATPhx_OneShotType  CATechCheckPoint::GetOneShotType() const 
{ return (spartan._ComputationalCategory&CATPhx_MaskTransaction); }


inline int  CATechCheckPoint::GetCurrentBeginEndDepth()   
{ return _CurrentBeginEndDepth; }

inline int  CATechCheckPoint::GetFilteringBeginEndDepth()   
{ return _FilteringBeginEndDepth; }



/** --------------------------------------------------------------------------------
*          != 
* -------------------------------------------------------------------------------- **/
int CATechCheckPoint::operator!=(const CATechCheckPoint & iOther) const
{ return ((*this) == iOther) ? FALSE : TRUE; }

int CATechCheckPoint::operator==(const CATechCheckPoint & iOther) const
{ return (this == & iOther) ? TRUE : FALSE; }

extern "C" ExportedByCATTechTools void CATechInspectors_Clean() ;



#endif
