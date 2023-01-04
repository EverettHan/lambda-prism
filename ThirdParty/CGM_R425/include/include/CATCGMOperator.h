#ifndef CATCGMOperator_h_
#define CATCGMOperator_h_

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include <YP00IMPL.h>
#include "YP0LOGRP.h"

#include "CATIAV5Level.h"
#include "CATIACGMLevel.h"

#include "CATBoolean.h"
#include "CATDataType.h"

#include "CATGetTolerance.h"

#include "CATListOfCATICGMObjects.h"
#include "CATCGMVirtual.h"
#include "CATCGMWarning.h"
#include "CATCGMInterruptDef.h"
#include "CATICGMUnknown.h"

#include "CATMathInline.h"

class CATCGMStream;
class CATICGMObject;
class CATCloneManager;
class CATString;
class CATGeoFactory;
class CATBaseUnknown;
class CATExtCGMReplay;
class CATCGMOutput;
class CATTopOperator;
class CATExtCGMReplay;
class CATSoftwareConfiguration;
class CATTopCheckJournal;
class CATError;
class CATExtGeoOperator;
class CATCGMOperatorRun;
class CATTolerance;
class CATechSet;
class CATechAttribute;
#include "IUnknown.h"
 

//=======================================================================================================================


/**
 * Base class for all the CGM operators.
 * <br>To use a CGM operator:
 * <ul><li>Create it with the corresponding <tt>CreateXxx</tt> global method
 * <li>Tune some parameters if needed
 * <li>Run it
 * <li>Read the results
 * <li>Delete it with the usual C++ delete operator.
 *</ul>
 */
class ExportedByYP00IMPL CATCGMOperator : public CATCGMVirtual
{
  CATCGMVirtualDeclareClass(CATCGMOperator);
public:
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Runs <tt>this</tt> operator.
 */
  virtual int                                Run();

/**
 * Returns the factory of <tt>this</tt> operator. 
 * @return
 * The pointer to the geometric factory that creates the output objects.
 */
  INLINE  CATGeoFactory                    * GetFactory() const;

/**
 * Retrieves the name of <tt>this</tt> operator.
 * @return
 * The name. This output string is part of the class and will be deleted at its deletion.
 */
  virtual const CATString                  * GetOperatorId(); 

/** 
 * Defines the name of <tt>this</tt> operator.
 * @param iOperatorName
 * The name of the operator.
 */
           void                              SetOperatorId (const CATString iOperatorName);

  /**
  * @nodoc
  * Associates an interruption function with this operator.
  * @param ipInterruptFunction
  * The interruption function to be written by the application calling this operator.
  * Must return TRUE if the operator is to be interrupted.
  */
   virtual void                              EnableInterrupt(CATCGMInterruptFunction ipInterruptFunction);


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  /** @nodoc */
  enum CATCheckDiagnostic { CheckOK, CheckWarning, CheckError } ;


  /** @nodoc  */
  virtual                                   ~CATCGMOperator();



   /** 
   * @nodoc
   * Returns the Software configuration to be taken 
   * into acccount by <tt>this</tt> operator.
   * @return
   * The Software configuration.
   */
   virtual CATSoftwareConfiguration        * GetSoftwareConfiguration() const;




  /** @nodoc */
  virtual CATTopOperator                   * IsTopological();

   /** 
   * @nodoc @nocgmitf
   *  Returns true if the object is of type CATTopOperator
   * @return
   * return CATBoolean 
   */
  virtual  CATBoolean                        IsACATTopOperator();


  /** @nodoc @nocgmitf  dedicated to CATTopOperator/CATCGMreplay : internal use, do not overload */
  virtual void                               WriteTopOutput(CATCGMStream & ioStream);

  /** @nodoc @nocgmitf   dedicated to CATTopOperator/CATCGMreplay : internal use, do not overload */
  virtual CATTopCheckJournal*                ReadTopOutput(CATCGMStream& ioStream);

  /** @nodoc @nocgmitf   dedicated to CATTopOperator/CATCGMreplay : internal use, do not overload */
  virtual void                               DumpTopOutput(CATTopCheckJournal* iEquivalent, CATCGMOutput& os);

  /** @nodoc @nocgmitf   dedicated to CATTopOperator/CATCGMreplay : internal use, do not overload */
  virtual CATBoolean                         ValidateTopOutput(CATTopCheckJournal* iEquivalent, CATCGMOutput& os);


  /** @nodoc @nocgmitf   dedicated to CATCGMreplay : Dump current definition */
  virtual void                               Dump( CATCGMOutput& os ) ;

  /** @nodoc   dedicated to CATCGMreplay : Check validity of Inputs */
  virtual CATCGMOperator::CATCheckDiagnostic CheckInput(CATCGMOutput & os);
 

  /** @nodoc @nocgmitf   dedicated to CATCGMreplay : Save definition ..  Open is done by static CATLoadOperatorId(...) */
  virtual void                               WriteInput(CATCGMStream  & ioStream);



  /** @nodoc @nocgmitf   dedicated to CATCGMreplay : Dump result*/
  virtual void                               DumpOutput(CATCGMOutput &os);

  /** @nodoc   dedicated to CATCGMreplay : Check validity of Outputs */
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);




  /** @nodoc @nocgmitf   dedicated to CATCGMreplay : Save expected reference for Stability */
  virtual void                               WriteOutput(CATCGMStream & ioStream);

  /** @nodoc @nocgmitf   dedicated to CATCGMreplay : Dump expected reference for Stability */
  virtual void                               DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);

  /** @nodoc @nocgmitf   dedicated to CATCGMreplay : Check expected reference and computed result */
  virtual CATBoolean                         ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);





  /** @nodoc  */
          void                               DefineFactory(CATGeoFactory *Factory);
  
  
  /** @nodoc @nocgmitf */
          CATBoolean                         IsRunning();
  
  /** @nodoc  */
          CATULONG32                         GetSessionIdentifier();
  

   /** @nodoc */
          void                               SetWarningMode(CATCGMWarning iMode = Warning_On);

   /** @nodoc */
          CATCGMWarning                      GetWarningMode() const;


  /** @nodoc  Default is Valid and Modifiable (exeption CATCloneManager and CATTopOperator) */
          void                               GetResultStatus(       short & ioValidation,      short & ioModifiable ) const;
  
  /** @nodoc  */
          void                               SetResultStatus( const short   iValidation, const short iModifiable );

  /** @nodoc @nocgmitf*/
          void                               CopyBaseClassDataPreRunFrom(CATCGMOperator const * ipSource);

  /** @nodoc @nocgmitf*/
          void                               CopyBaseClassDataPostRunFrom(CATCGMOperator const * ipSource);

  /** @nodoc */
          short                              GetNumberOfReplay();


  /** @nodoc  */
  INLINE  CATExtGeoOperator                * GetExtensible(CATBoolean iRequired = TRUE) const;

  /**
  * @nodoc CGMTkJournaling
  */
  virtual HRESULT                            DumpObjects(const unsigned int iOptions, CATechAttribute * iOutput, CATechSet * iJournaling) ;

protected :

  /** @nodoc */
  virtual void                               CopyTopOperatorDataPreRunFrom(CATCGMOperator const *  iSource);

  /** @nodoc */
  virtual void                               CopyTopOperatorDataPostRunFrom(CATCGMOperator const *  iSource);



  /** @nodoc  */
  virtual CATExtCGMReplay                  * IsRecordable(short & LevelOfRuntime, short &VersionOfStream);

  /** @nodoc */
  virtual CATBoolean                         IsCAA();

  /** @nodoc */
  virtual CATBoolean                         IsNotAppli();

  /** @nodoc  */
  virtual int                                RunOperator();

  /** @nodoc  */
  virtual int                                RunExactOperator();

  /** @nodoc  */
  virtual int                                RunPolyOperator();

  /** @nodoc  */
  INLINE const CATTolerance                & GetTolerance() const;

  /** @nodoc  */
  INLINE const CATTolerance                & GetToleranceObject() const;

/**
 * @nodoc
 * Constructs a CGM operator.
 * @param iFactoryForCreation
 * The pointer to the geometric factory for the operation: input and output objects are created 
 * with this factory. 
 */
                                             CATCGMOperator(CATGeoFactory     * iFactoryForCreation,
                                                            CATExtGeoOperator * iExtensible        = NULL);



  /** @nodoc  Necessite de definition de l'extension actuellement null, si echec alors c'est grave */
          CATExtGeoOperator                * RequireExtensible() const;


protected :

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            P R O T E C T E D   D A T A
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  /** @nodoc */
          CATGeoFactory     * const          _Factory; // the factory

  /** @nodoc  */
          CATExtGeoOperator * const          _Extensible;


private :

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            P R I V A T E     M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  /** @nodoc  forbidden functionality */
                                             CATCGMOperator(const CATCGMOperator&);

  /** @nodoc  forbidden functionality */
          CATCGMOperator&                    operator =    (const CATCGMOperator&);


  /** @nodoc  Operateur specifiant l'extension adequate des la creation */
          void                               DefineExtensible (CATExtGeoOperator * iExtensible);
  

  /** @nodoc  */
          void                               BeforeAction     (CATExtCGMReplay *& ioFactoryOperator,
                                                               CATCGMStream    *& ioStream         ,
                                                               size_t           & ioWhereDataBegin ,
                                                               short            & ioLevel          ,
                                                               short            & ioLevelOfRuntime ,
                                                               short            & ioVersionOfStream,
                                                         const short              iRecording       );

  /** @nodoc  */
          void                               AfterAction      (CATExtCGMReplay *& ioFactoryOperator,
                                                               CATCGMStream    *& ioStream         ,
                                                               size_t           & ioWhereDataBegin ,
                                                               short            & ioLevel          ,
                                                               short            & ioLevelOfRuntime ,
                                                               short            & ioVersionOfStream,
                                                         const short              iRecording       );

  /** @nodoc  */
          void                               AfterAction      (CATExtCGMReplay *& ioFactoryOperator,
                                                               CATCGMStream    *& ioStream         ,
                                                               size_t           & ioWhereDataBegin ,
                                                               short            & ioLevel          ,
                                                               short            & ioLevelOfRuntime ,
                                                               short            & ioVersionOfStream,
                                                         const short              iRecording       ,
                                                               CATError        *  iErr             );



    /** @nodoc */
  friend class CATExtCGMReplay;
    /** @nodoc */
  friend class CATCGMReplayRecord;
    /** @nodoc */
  friend class CATCGMOperatorRun;
    /** @nodoc */
  friend class CATExtGeoOperator;
    /** @nodoc */
  friend class CATCGMOperatorSpecialImplementation;
    /** @nodoc */
  friend class CATMProcOperatorStreamingSupport;
};

  /** @nodoc  */
INLINE CATExtGeoOperator *CATCGMOperator::GetExtensible(CATBoolean iRequired) const
{
  return (_Extensible || !iRequired) ? _Extensible  : RequireExtensible();
}

  /** @nodoc  */
INLINE CATGeoFactory * CATCGMOperator::GetFactory() const
{
  return _Factory;
}
  /** @nodoc  */
INLINE const CATTolerance &CATCGMOperator::GetTolerance() const
{
  return _Factory ? ((CATICGMUnknown*)_Factory)->GetToleranceObject() : ::CATGetDefaultTolerance();
}

  /** @nodoc  */
INLINE const CATTolerance &CATCGMOperator::GetToleranceObject() const
{
  return _Factory ? ((CATICGMUnknown*)_Factory)->GetToleranceObject() : ::CATGetDefaultTolerance();
}


#ifdef  _WINDOWS_SOURCE
extern "C"  { typedef __declspec(dllexport) CATCGMOperator *
#else
extern "C"  { typedef                       CATCGMOperator *
#endif
 CATLoadCATCGMOperator(CATCGMStream &Str, const short LevelOfRuntime, const short VersionOfStream); }


#endif
