//==========================================================================================
// COPYRIGHT DASSAULT SYSTEMES 2007
//==========================================================================================
//
// Utility to generate timer tree
//
//==========================================================================================
//
//==========================================================================================
// May 08 Creation                                    MPX
//==========================================================================================

#ifndef CATechTimerTree_H
#define CATechTimerTree_H

// To activate timer-tree,
// use #define ActivateCATechTimerTree 1

// default #define ActivateCATechTimerTree 0
#define ActivateCATechTimerTree 0

#if defined  (ActivateCATechTimerTree)  &&  (ActivateCATechTimerTree ==  1)  

#include "CATBoolean.h"
#include "CATString.h"
#include "CATechTimer.h"

class ExportedByCATTechTools CATechTimerTreeNode
{
public:
  static CATechTimerTreeNode* DeclareStartOfBlock(const CATString& iBlockName);
  void DeclareEndOfBlock();
  ~CATechTimerTreeNode();

protected:
  CATechTimerTreeNode(const CATString& iRootName); // constructor for root
  CATechTimerTreeNode(const CATString& iBlockName, CATechTimerTreeNode& iParent);
  void Start();
  void Stop(const CATBoolean iExceptionOccurred = FALSE);

  void ExceptionOccurredInChild();

  CATechTimerTreeNode* AddChild(const CATString& iBlockName);
  CATechTimerTreeNode* SearchChildren(const CATString& iBlockName) const;
  CATechTimerTreeNode* GetChild(const CATString& iBlockName);
  void TraceSelf();

  void AddResidueChildren();
  void Sort();
  CATechTimerTreeNode* SortNextSiblings();
  void Print(ostream& os);
  void PrintSelf(ostream& os);
  void PrintTreeLinks(ostream& os);
  void PrintPrefixKeyword(ostream& os);
  CATBoolean operator > (const CATechTimerTreeNode& iOtherNode) const;

  static void GoBackToParent();

  class NodeData
  {
  public:
    class TimeData
    {
      double _CPUTime;
    public:
      TimeData();
      void Print(ostream& os);
      void Append(const CATechTimer& iTimer);
      TimeData& operator -= (const TimeData& iTimeData);
      CATBoolean operator > (const TimeData& iTimeData) const;
      CATBoolean IsNegligible() const;
      double IsWhatPercentOf(const TimeData& RefTimeData) const;
    };

    NodeData(const CATString& iBlockName);
    void Print(ostream& os);

    CATString _BlockName;
    int _CallCount;
    TimeData _TotalTimeData;
    int _HeaviestCallNb;
    TimeData _HeaviestCallTime;

    CATString _ExceptionInfo;
    int _ExceptionOccurredAtCallNb;

    int _RecursionCount; // yet to be utilized
  };

  CATechTimer _Timer;
  NodeData _NodeData;
  CATechTimerTreeNode* _Parent;
  CATechTimerTreeNode* _NextSibling;
  CATechTimerTreeNode* _FirstChildNode;
  CATBoolean _ExceptionOccurredInChild;

  static CATechTimerTreeNode* _ActiveNode;
};

class ExportedByCATTechTools CATechTimerTreeRootNode: 
  public CATechTimerTreeNode
{
protected:
  CATechTimerTreeRootNode();
  ~CATechTimerTreeRootNode();

  int _NbRootOwners;

  static void OwnRoot();
  static void ReleaseRoot();
  static CATechTimerTreeRootNode* _Root;

  friend class CATechTimerTreeGenerator;
};

class ExportedByCATTechTools CATechTimerTreeGenerator
{
public:
  CATechTimerTreeGenerator();
  ~CATechTimerTreeGenerator();

  static void ActivateRecording() {_RecordingActive = TRUE;}
  static void DeactivateRecording() {_RecordingActive = FALSE;}
  static CATBoolean IsRecordingActive() { return _RecordingActive;}
protected:
  static CATBoolean _RecordingActive;
};

class ExportedByCATTechTools CATechBlockTimer
{
public:
  CATechBlockTimer(const char* sBlockName);
  ~CATechBlockTimer();
  void Stop();
protected:
  CATechTimerTreeNode* _RefNode;
};

class ExportedByCATTechTools CATechFunctionTimer
  :public CATechBlockTimer
{
public:
  CATechFunctionTimer(const char* sFuncName)
    : CATechBlockTimer(sFuncName) {}
};

#define CATechDeclareBlock(BLOCK_NAME) CATechBlockTimer __ThisBlock_DontUseMyNameElsewhere(#BLOCK_NAME)
#define CATechDeclareFunction(FUNC_NAME) CATechFunctionTimer __ThisFunction_DontUseMyNameElsewhere(#FUNC_NAME)

#define CATechTimerTree_TryBlockStart \
  CATTry \

#define CATechTimerTree_TryBlockEnd \
  CATCatch(CATError, AnyError) { \
    __ThisFunction_DontUseMyNameElsewhere.Stop(); \
    CATRethrow; \
  } \
  CATEndTry;

#endif //ActivateCATechTimerTree

#endif //CATechTimerTree_H
