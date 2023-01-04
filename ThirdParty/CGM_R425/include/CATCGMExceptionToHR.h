#ifndef CATCGMExceptionToHR_h
#define CATCGMExceptionToHR_h

/**
 * This macro runs the function or the method. If an exception is thrown, it's caught and it's
 * converted to a HRESULT return code and the global last error is set. See @href CATError#CATGetLastError .<br>
 * Example:<br>
 * 1 - The error is not analyzed<br>
 * <pre>
 *   HRESULT hr = S_OK;
 *   CATCGMExceptionToHR(hr, pOperator->Run());
 *   if (SUCCEEDED(hr))
 *     ...</pre>
 * 2 - The error is analyzed<br>
 * <pre>
 *   HRESULT hr = S_OK;
 *   CATCGMExceptionToHR(hr, pOperator->Run());
 *   if (SUCCEEDED(hr))
 *     ...
 *   else
 *   {
 *      CATError *pLastError = CATError::CATGetLastError(hr); // It's the error that was thrown
 *      ...
 *      pLastError->Release();
 *   }</pre>
 *
 * @param hr
 *   The return code.
 * @param CallWithException
 *   The method or the function that may throw an exception.<br>
 *   Note: as CATCGMExceptionToHR is a macro, you must put all the arguments of the function of the method
 *   in the same line, or you must use backslashes:<pre>
 *      CATCGMExceptionToHR(hr, MyFunction( \
 *        arg1, \
 *        arg2, \
 *        arg3));</pre>
 */
#define CATCGMExceptionToHR(hr, CallWithException) \
  CATTry \
  { \
    hr = S_OK; \
    CallWithException; \
  } \
  CATCatch(CATError, pError) \
  { \
    hr = pError->GetReturnCode(); \
    pError->CATSetLastError(); \
    pError->Release(); \
  } \
  CATEndTry;

#endif // CATCGMExceptionToHR_h
