#include "CATThrowForNullPointer.h"
#include "CATUnicodeString.h"
#include "CATIPGMMultiProcTask.h"

//----------------------------------------------------------------
//  Implementation des methodes Templates
//----------------------------------------------------------------

template <class T>
T * CATPGMMultiProcOperation::GetClientTask() const
{
  T * pCTask = NULL;
  this->GetClientTask(pCTask);

  return pCTask;
}


// template <class T, class = typename std::enable_if<std::is_base_of<CATIPGMMultiProcTask,T>::value>::type>
template <class T,
          typename std::enable_if<std::is_base_of<CATIPGMMultiProcTask,T>::value>::type*>
void CATPGMMultiProcOperation::GetClientTask(T *& oTask) const
{  
  CATIPGMMultiProcTask * pCurrentTask = this->GetTask();
  if (pCurrentTask)
  {
    T localUserTask;
    CATUnicodeString testClassName = localUserTask.GetLoadFunctionName();

    CATUnicodeString currentClassName = pCurrentTask->GetLoadFunctionName();
    if (currentClassName == testClassName) // Check
    {
      oTask = (T *) pCurrentTask;
    }
    else
      CATThrowForNullPointer();
  }

}

