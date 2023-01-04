//===================================================================
// COPYRIGHT Dassault Systemes 2014/01/28
//===================================================================
// DSYSysRscError.h
//===================================================================
//
// Usage notes:
//

#include "CATSysErrorDef.h"

/**
 * @nodoc
 * MessageId: E_FILENOTFOUND
 *  MessageText:
 *  File marker not found at specified path
 */
#define E_FILENOTFOUND                              _HRESULT_TYPEDEF_(0x8FEE0002L)


/**
 * @nodoc
 * MessageId: E_NAMEISNOTDIRECTPRY
 *  MessageText:
 *  The directory name is invalid.
 */
#define E_NAMEISNOTDIRECTORY                        _HRESULT_TYPEDEF_(0x8FEE0267L)

/**
 * @nodoc
 * MessageId: E_INDEXTABLEHASHCONFLICT
 *  MessageText:
 *  Two files with different name have the same hash value.
 */
#define E_INDEXTABLEHASHCONFLICT                    _HRESULT_TYPEDEF_(0x8FEE01FCL)

/**
 * @nodoc
 * MessageId: E_BADBUNDLEVERSION
 *  MessageText:
 *  The version of the bundle is not supported
 */
#define E_BADBUNDLEVERSION                          _HRESULT_TYPEDEF_(0x8FEE0643L)

/**
 * @nodoc
 * MessageId: E_EXCLUDEDFILE
 *  MessageText:
 *  The file is marked as excluded
 */
#define E_EXCLUDEDFILE                              _HRESULT_TYPEDEF_(0x8FEE016BL)

/**
 * @nodoc
 * MessageId: E_EXCLUDEDFILE
 *  MessageText:
 *  The file allready exists in the bundle
 */
#define E_FILEALREADYEXISTS                         _HRESULT_TYPEDEF_(0x8FEE0080L)

/**
 * @nodoc
 * MessageId: E_EXCLUDEDFILE
 *  MessageText:
 *  The file allready exists in the bundle
 */
#define E_CORRUPTEDINDEX                            _HRESULT_TYPEDEF_(0x8FEE0634L)
