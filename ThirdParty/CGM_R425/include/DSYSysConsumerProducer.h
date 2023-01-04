#ifndef DSYSysConsumerProducerPrivate_H
#define DSYSysConsumerProducerPrivate_H

/************************************************************************/
/* Defines                                                              */
/************************************************************************/

/************************************************************************/
/* Global includes                                                      */
/************************************************************************/
#include <atomic>	// C++11 atomics

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "CATSysTS.h"
#include "CATThreads.h"
#include "DSYSysCommon.h"

/************************************************************************/
/* Classes declaration                                                  */
/************************************************************************/

/** @class DSYSysThread */
class DSYSysThread;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

/** @struct DSYSysProducerConsumerStruct */
struct DSYSysProducerConsumerStruct
{
  /// Procedure identifier.
  int _Id;

  /// Procedure callback data.
  void* _pData;
  void* _pDataEx;

  /// Procedure callback.
  void (*_fCbk)(const int, const int, void*, void*);
};

#ifdef __cplusplus
};
#endif  // __cplusplus

/************************************************************************/
/************************************************************************/

/** @class CATEvent */
class CATEvent;

/************************************************************************/
/************************************************************************/

/** @class DSYSysProducer */
class DSYSysProducer;

/************************************************************************/
/************************************************************************/

/**
 * @class DSYSysConsumer
 */
class ExportedByJS0MT DSYSysConsumer
{
  // Oh... My... God...
  friend class DSYSysProducer;

#ifdef DSY_SYS_BAN_EVIL_CONSTRUCTORS_MACROS_DEFINED
  DSYSysBanEvilConstructors(DSYSysConsumer);
#endif  // DSY_SYS_BAN_EVIL_CONSTRUCTORS_MACROS_DEFINED

  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:
  /// Procedure flag for emergency break.
  enum ProcedureFlag { EmergencyBreak = -1 };

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /// Constructor.
  DSYSysConsumer();

  /// Destructor.
  virtual~ DSYSysConsumer();

  /// Start consuming.
  void Start(const int iTimeOut = -1, void (*ifTimeOut)(void*) = NULL, void* ipTimeOutData = NULL);

  /// Stop consuming.
  void Stop(void);

  /// Check consume is on the air.
  bool IsBusy(void) const
  { return m_Busy; }

protected:
  /// Internal thread callback.
  static CATThreadsReturnCode S_fThread(void* ipParam);

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
protected:
  /// Break flag.
  std::atomic<int> m_Break;

  /// Busy flag.
  std::atomic<bool> m_Busy;

  /// Time out.
  int m_TimeOut;

  /// Time out callback.
  void (*m_fTimeOut)(void*);

  /// Time out callback parameter.
  void* m_pTimeOut;

private:
  /// Event object.
  CATEvent* m_pEvent;

  /// Thread class.
  DSYSysThread* m_pThread;

  /// Ring buffer address.
  void* m_hRingBuffer;
};

/************************************************************************/
/************************************************************************/

/**
 * @class DSYSysProducer
 */
class ExportedByJS0MT DSYSysProducer
{
#ifdef DSY_SYS_BAN_EVIL_CONSTRUCTORS_MACROS_DEFINED
  DSYSysBanEvilConstructors(DSYSysProducer);
#endif  // DSY_SYS_BAN_EVIL_CONSTRUCTORS_MACROS_DEFINED

  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /// Constructor (Default).
  DSYSysProducer();

  /// Constructors for fast consume.
  DSYSysProducer(const DSYSysConsumer& irConsumer, void** ioppData);
  DSYSysProducer(const DSYSysConsumer& irConsumer, const int iIdentifier, void (*ifCbk)(const int, const int, void*, void*) = NULL, void** ioppData = NULL, void* ipDataEx = NULL);

  /// Destructor.
  virtual~ DSYSysProducer();

  /// Produce.
  void Produce(const DSYSysConsumer& irConsumer, void** ioppData);
  void Produce(const DSYSysConsumer& irConsumer, const int iIdentifier, void (*ifCbk)(const int, const int, void*, void*) = NULL, void** ioppData = NULL, void* ipDataEx = NULL);

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
protected:
};

#endif  // DSYSysConsumerProducerPrivate_H
