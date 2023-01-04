#ifndef DSYSysJSON_H
#define DSYSysJSON_H

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#undef DSYSYSJSON_DEPRECATED_R424
#ifdef DSYSYSJSON_DEPRECATED_R424
# define DSYSYSJSON_DEPRECATED_R424__(...)
#else   // DSYSYSJSON_DEPRECATED_R424
# define DSYSYSJSON_DEPRECATED_R424__(...)        __VA_ARGS__
#endif  // DSYSYSJSON_DEPRECATED_R424

#define DSYSYSJSON_EXPERIMENTAL_R424__(...)        __VA_ARGS__

/************************************************************************/
/* Global includes                                                      */
/************************************************************************/
#include <map>
#include <vector>

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "CATDataType.h"
#include "CATSysTS.h"
#include "DSYString.h"
#include "DSYSysCommon.h"
#include "DSYSysTrace.h"
#include "jsmn_def.h"

/************************************************************************/
/* Classes declaration                                                  */
/************************************************************************/

/**
 * @class CATSysSimpleHashTable
 */
class CATSysSimpleHashTable;

/************************************************************************/
/************************************************************************/

/**
 * @class DSYSysJSONObject
 */
class DSYSysJSONObject;

/**
 * @class DSYSysJSONArray
 */
class DSYSysJSONArray;

/**
 * @class DSYSysJSONValue
 */
class DSYSysJSONValue;

/**
 * @class DSYSysJSONPair
 */
class DSYSysJSONPair;

DSYSYSJSON_EXPERIMENTAL_R424__(
  /**
   * @class DSYSysJSONTraverse
   */
  class DSYSysJSONTraverse;
) // DSYSYSJSON_EXPERIMENTAL_R424__

DSYSYSJSON_EXPERIMENTAL_R424__(
  /**
   * @class DSYSysJSONWalker
   */
  class DSYSysJSONWalker;
) // DSYSYSJSON_EXPERIMENTAL_R424__

DSYSYSJSON_EXPERIMENTAL_R424__(
  /**
   * @class DSYSysJSONTokenizer
   */
  class DSYSysJSONTokenizer;
) // DSYSYSJSON_EXPERIMENTAL_R424__

DSYSYSJSON_DEPRECATED_R424__(
  /**
   * @class DSYSysJSONPairListImpl
   */
  class DSYSysJSONPairListImpl;

  /**
   * @class DSYSysJSONValueListImpl
   */
  class DSYSysJSONValueListImpl;
) // DSYSYSJSON_DEPRECATED_R424

/** class DSYSysJSONToken */
class DSYSysJSONToken;

/** class DSYSysJSONTokenizer */
class DSYSysJSONTokenizer;

/************************************************************************/
/* Types declaration                                                    */
/************************************************************************/

//=======================================================================
typedef std::vector<DSYSysJSONPair> DSYSysJSONPairs;
//=======================================================================

/************************************************************************/
/************************************************************************/

//=======================================================================
typedef std::vector<DSYSysJSONValue> DSYSysJSONValues;
//=======================================================================

/************************************************************************/
/* Functions declaration                                                */
/************************************************************************/

//=======================================================================
/** @nodoc */
ExportedByCATSysTS HRESULT DSYSysJSONStringEscape(CATUnicodeString& ioszString);
//=======================================================================

//=======================================================================
/** @nodoc */
ExportedByCATSysTS HRESULT DSYSysJSONStringEscape(_DSYSysUTF8_(char)** oszStringUTF8, size_t& oszCharLength, const _DSYSysUTF8_(char)* iszStringUTF8, size_t iszCharLength);
//=======================================================================

//=======================================================================
/** @nodoc */
ExportedByCATSysTS HRESULT DSYSysJSONStringUnescape(CATUnicodeString& ioszString);
//=======================================================================

/************************************************************************/
/* Classes declaration                                                  */
/************************************************************************/

DSYSYSJSON_DEPRECATED_R424__(
  /**
   * @class DSYSysJSONValueList
   */
  class ExportedByCATSysTS DSYSysJSONValueList
  {
    ///////////////////////////////////////////
    ////// Types/Constants/Struct/Enum ////////
    ///////////////////////////////////////////

    ///////////////////////////////////////////
    ///////////////// Methods /////////////////
    ///////////////////////////////////////////
  public:
    /// Constructor (default).
    DSYSysJSONValueList();

    /// Destructor.
    virtual ~DSYSysJSONValueList();

    /// Add item.
    void Add(const DSYSysJSONValue& iValue);

    /// Get first value.
    DSYSysJSONValue* GetFirst(void);

    /// Get next value.
    DSYSysJSONValue* GetNext(void);

    /// Get count.
    size_t Count(void) const;

    /// Reset list.
    void Erase(void);

    ///////////////////////////////////////////
    ///////////////// Members /////////////////
    ///////////////////////////////////////////
  protected:
    /// Value list object
    DSYSysJSONValueListImpl* m_pValueList;
  };
) // DSYSYSJSON_DEPRECATED_R424

/************************************************************************/
/************************************************************************/

DSYSYSJSON_DEPRECATED_R424__(
  /**
   * @class DSYSysJSONPairList
   */
  class ExportedByCATSysTS DSYSysJSONPairList
  {
    ///////////////////////////////////////////
    ////// Types/Constants/Struct/Enum ////////
    ///////////////////////////////////////////

    ///////////////////////////////////////////
    ///////////////// Methods /////////////////
    ///////////////////////////////////////////
  public:
    /// Constructor.
    DSYSysJSONPairList();

    /// Destructor.
    virtual ~DSYSysJSONPairList();

    /// Add item.
    DSYSysJSONPair* Add(const DSYSysJSONPair& iPair);

    /// Get first item.
    DSYSysJSONPair* GetFirst(void);

    /// Get first item.
    DSYSysJSONPair* GetNext(void);

    /// Get count.
    size_t Count(void) const;

    /// Remove all elements.
    void Erase(void);

    ///////////////////////////////////////////
    ///////////////// Members /////////////////
    ///////////////////////////////////////////
  protected:
    /// Pair list object.
    DSYSysJSONPairListImpl* m_pPairList;
  };
) // DSYSYSJSON_DEPRECATED_R424

/************************************************************************/
/************************************************************************/

/**
 * @class DSYSysJSONBase
 */
class ExportedByCATSysTS DSYSysJSONBase
{
  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /// Constructor (default).
  DSYSysJSONBase();

  /// Constructor (Copy).
  DSYSysJSONBase(const DSYSysJSONBase& irSource);

  /// Constructor (Move).
  DSYSysJSONBase(DSYSysJSONBase&& irrSource);

  /// Destructor.
  virtual ~DSYSysJSONBase();

  /// Assignment operator.
  DSYSysJSONBase& operator=(const DSYSysJSONBase& irSource);

  /// Assignment operator (move).
  DSYSysJSONBase& operator=(DSYSysJSONBase&& irrSource);

  /// Save data.
  ///   iMinify = true to get a compact JSON without end of line and tabulation.
  ///           = false to get a proper human readable JSON
  ///   iTabulation for recursion purpose, not to be used by user.
  HRESULT Stringify(CATUnicodeString& ioString, const bool iMinify = true, CATUnicodeString iTabulation = "");

  DSYSYSJSON_DEPRECATED_R424__(
    /// Save data.
    [[deprecated("[R424/R2022x] Use 'Stringify()' instead.")]] HRESULT SaveAsJSON(CATUnicodeString& ioString, const bool iMinify = true, CATUnicodeString iTabulation = "");
  ) // DSYSYSJSON_DEPRECATED_R424

protected:
  /// Save data.
  virtual HRESULT ChildSaveAsJSON(CATUnicodeString& ioString, const bool iMinify = true, CATUnicodeString iTabulation = "") = 0;
  
  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
protected:
  /// Tabulation.
  CATUnicodeString m_Tabulation;
};

/************************************************************************/
/************************************************************************/

/**
 * @class DSYSysJSONArray
 */
class ExportedByCATSysTS DSYSysJSONArray : public DSYSysJSONBase
{
  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /// Constructor (default).
  DSYSysJSONArray();

  /// Copy constructor.
  DSYSysJSONArray(const DSYSysJSONArray& irSource);

  /// Copy constructor.
  DSYSysJSONArray(DSYSysJSONArray&& irrSource);

  /// Destructor.
  virtual ~DSYSysJSONArray();

  /// Assigment operator.
  DSYSysJSONArray& operator=(const DSYSysJSONArray& irSource);

  /// Assignment operator (move).
  DSYSysJSONArray& operator=(DSYSysJSONArray&& irrSource);

  /// Add a value.
  void Push(const DSYSysJSONValue& irValue);
  void Push(DSYSysJSONValue&& irrValue);

  /// Pair count.
  size_t Count(void) const
  { return (nullptr == m_pValues)? 0 : m_pValues->size(); }

  /// Remove all values.
  void Clear(void);

  /// Walk list of value.
  template <class Func, class... Args>
  void Every(Func&& irrfEvery, Args&&... irrArgs);

  /// Iteration begin.
  DSYSysJSONValues::iterator Begin(void);

  /// Iteration begin.
  DSYSysJSONValues::iterator End(void);

  DSYSYSJSON_DEPRECATED_R424__(
    /// Add a value.
    [[deprecated("[R424/R2022x] Use 'Push()' instead.")]] void Add(const DSYSysJSONValue& irValue);
    [[deprecated("[R424/R2022x] Use 'Push()' instead.")]] void Add(DSYSysJSONValue&& irrValue);

    /// Get list of values.
    [[deprecated("[R424/R2022x] Use 'Every()' instead.")]] DSYSysJSONValueList* GetValues(void);
  ) // DSYSYSJSON_DEPRECATED_R424

protected:
  /// Save data.
  HRESULT ChildSaveAsJSON(CATUnicodeString& ioString, const bool iMinify = true, CATUnicodeString iTabulation = "") override;

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
protected:
  /// List of values.
  DSYSysJSONValues* m_pValues;

  DSYSYSJSON_DEPRECATED_R424__(
private:
    /// List of values.
    DSYSysJSONValueList* m_pValueList;
  ) // DSYSYSJSON_DEPRECATED_R424__
};

/************************************************************************/
/************************************************************************/

/**
 * @class DSYSysJSONObject
 */
class ExportedByCATSysTS DSYSysJSONObject : public DSYSysJSONBase
{
  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /// Constructor (default).
  DSYSysJSONObject();

  /// Constructor.
  DSYSysJSONObject(const DSYSysJSONPair& irPair);
  DSYSysJSONObject(DSYSysJSONPair&& irrPair);

  /// Copy constructor.
  DSYSysJSONObject(const DSYSysJSONObject& irSource);

  /// Constructor (Move).
  DSYSysJSONObject(DSYSysJSONObject&& irrSource);

  /// Destructor.
  virtual ~DSYSysJSONObject();

  /// Assigment operator.
  DSYSysJSONObject& operator=(const DSYSysJSONObject& irSource);

  /// Assignment operator (move).
  DSYSysJSONObject& operator=(DSYSysJSONObject&& irrSource);

  /// Add a value.
  void Push(const DSYSysJSONPair& irPair, DSYSysJSONPair** oppPairLastPushed = nullptr);
  void Push(DSYSysJSONPair&& irrPair, DSYSysJSONPair** oppPairLastPushed = nullptr);

  /// Set as a single value.
  void Set(const DSYSysJSONPair& irPair);
  void Set(DSYSysJSONPair&& irrPair);

  /// Set as a single value (boolean).
  void Set(const _DSYSysUTF8_(char)* ipString, const bool iBool);
  void Set(const CATUnicodeString& irString, const bool iBool);

  /// Set as a single value (integer).
  void Set(const CATUnicodeString& irString, const int iInteger);
  void Set(const _DSYSysUTF8_(char)* ipString, const int iInteger);

  /// Set as a single value (integer).
  void Set(const _DSYSysUTF8_(char)* ipString, const CATLONG64 iInteger);
  void Set(const CATUnicodeString& irString, const CATLONG64 iInteger);

  /// Set as a single value (double).
  void Set(const _DSYSysUTF8_(char)* ipString, const double iDouble);
  void Set(const CATUnicodeString& irString, const double iDouble);

  /// Set as a single value (string).
  void Set(const _DSYSysUTF8_(char)* ipString, const _DSYSysUTF8_(char)* ipStringBuffer, const bool iEscape = false);
  void Set(const CATUnicodeString& irString, const _DSYSysUTF8_(char)* ipStringBuffer, const bool iEscape = false);

  /// Set as a single value (string).
  void Set(const _DSYSysUTF8_(char)* ipString, const CATUnicodeString& irStringValue, const bool iEscape = false);
  void Set(const CATUnicodeString& irString, const CATUnicodeString& irStringValue, const bool iEscape = false);

  /// Set as a single value (string move).
  void Set(const _DSYSysUTF8_(char)* ipString, CATUnicodeString&& irrStringValue, const bool iEscape = false);
  void Set(const CATUnicodeString& irString, CATUnicodeString&& irrStringValue, const bool iEscape = false);

  /// Set as a single value.
  void Set(const _DSYSysUTF8_(char)* ipString, const DSYSysJSONValue& irValue);
  void Set(const CATUnicodeString& irString, const DSYSysJSONValue& irValue);

  /// Set as a single value.
  void Set(const _DSYSysUTF8_(char)* ipString, DSYSysJSONValue&& irrValue);
  void Set(const CATUnicodeString& irString, DSYSysJSONValue&& irrValue);

  /// Remove all values.
  void Clear(void);

  /// Walk list of value.
  template <class Func, class... Args>
  void Every(Func&& irrfEvery, Args&&... irrArgs);

  /// Get value by string.
  DSYSysJSONValue& operator[](const _DSYSysUTF8_(char)* ipString);

  /// Pair count.
  size_t Count(void) const
  {  return (nullptr == m_pvPairs)? 0 : m_pvPairs->size(); }
  
  /// Iteration begin.
  DSYSysJSONPairs::iterator Begin(void);

  /// Iteration begin.
  DSYSysJSONPairs::iterator End(void);

  DSYSYSJSON_DEPRECATED_R424__(
    /// Add a value.
    [[deprecated("[R424/R2022x] Use 'Push()' instead.")]] void Add(const DSYSysJSONPair& iPair);
    [[deprecated("[R424/R2022x] Use 'Push()' instead.")]] void Add(DSYSysJSONPair&& irrValue);

    /// Get pairs.
    [[deprecated("[R424/R2022x] Use 'Every()' instead.")]] DSYSysJSONPairList* GetPairs(void);

    /// Found a specific pair.
    [[deprecated("[R424/R2022x] Use 'operator[]' instead.")]] DSYSysJSONValue GetByString(const _DSYSysUTF8_(char)* ipString);
  ) // DSYSYSJSON_DEPRECATED_R424__

protected:
  /// Save data.
  HRESULT ChildSaveAsJSON(CATUnicodeString& ioString, const bool iMinify = true, CATUnicodeString iTabulation = "") override;

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
protected:
  /// Vector of pairs.
  DSYSysJSONPairs* m_pvPairs;

private:
  /// Empty value.
  DSYSysJSONValue* m_pValueEmpty;

  DSYSYSJSON_DEPRECATED_R424__(
private:
    /// List of pairs.
    DSYSysJSONPairList* m_pPairList;

    /// Hash table.
    CATSysSimpleHashTable* m_pPairHash;
  ) // DSYSYSJSON_DEPRECATED_R424__
};

/************************************************************************/
/************************************************************************/

/**
 * @class DSYSysJSONValue
 */
class ExportedByCATSysTS DSYSysJSONValue : public DSYSysJSONBase
{
  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:
  /// Type enumeration.
  enum ValueTypeEnum
  {
    DSYSysJSONValue_NULL
#define DSYSysJSONValueNull     DSYSysJSONValue::DSYSysJSONValue_NULL

  , DSYSysJSONValue_BOOL
#define DSYSysJSONValueBoolean  DSYSysJSONValue::DSYSysJSONValue_BOOL

  , DSYSysJSONValue_NUMBER
#define DSYSysJSONValueInteger DSYSysJSONValue::DSYSysJSONValue_NUMBER

  , DSYSysJSONValue_NUMBER_FLOAT
#define DSYSysJSONValueDouble   DSYSysJSONValue::DSYSysJSONValue_NUMBER_FLOAT
#define DSYSysJSONValueFloat    DSYSysJSONValue::DSYSysJSONValue_NUMBER_FLOAT

  , DSYSysJSONValue_STRING
#define DSYSysJSONValueString   DSYSysJSONValue::DSYSysJSONValue_STRING

  , DSYSysJSONValue_OBJECT
#define DSYSysJSONValueObject   DSYSysJSONValue::DSYSysJSONValue_OBJECT

  , DSYSysJSONValue_ARRAY
#define DSYSysJSONValueArray    DSYSysJSONValue::DSYSysJSONValue_ARRAY
  };
#define DSYSysJSONValueType DSYSysJSONValue::ValueTypeEnum

  /// Primitive union.
  union PrimitiveUnion
  {
    bool _Boolean;
    CATLONG64 _Integer;
    double _Double;
  };
#define DSYSysJSONValuePrimitive DSYSysJSONValue::PrimitiveUnion

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /// Constructor (default).
  DSYSysJSONValue();

  /// Constructor.
  DSYSysJSONValue(const DSYSysJSONObject& irObject);
  DSYSysJSONValue(DSYSysJSONObject&& irrObject);

  /// Constructor.
  DSYSysJSONValue(const DSYSysJSONArray& irArray);
  DSYSysJSONValue(DSYSysJSONArray&& irrArray);

  /// Copy constructor.
  DSYSysJSONValue(const DSYSysJSONValue& irSource);

  /// Constructor (Move).
  DSYSysJSONValue(DSYSysJSONValue&& irrSource);

  /// Destructor.
  virtual ~DSYSysJSONValue();

  /// Assigment operator.
  DSYSysJSONValue& operator=(const DSYSysJSONValue& irSource);

  /// Assignment operator (move).
  DSYSysJSONValue& operator=(DSYSysJSONValue&& irrSource);

  /// Set null type.
  void SetNull(void);

  /// Set boolean type.
  void Set(const bool iBool);

  /// Set integer type.
  void Set(const int iInteger);
  void Set(const CATLONG64 iInteger);

  /// Set float type.
  void Set(const double iDouble);

  /// Set string type.
  void Set(const _DSYSysUTF8_(char)* iString, const bool iEscape = false);
  void Set(const CATUnicodeString &irString, const bool iEscape = false);
  void Set(CATUnicodeString&& irrString, const bool iEscape = false);

  /// Set object type.
  void Set(const DSYSysJSONObject& irObject);
  void Set(DSYSysJSONObject&& irrObject);

  /// Set array type.
  void Set(const DSYSysJSONArray& irArray);
  void Set(DSYSysJSONArray&& irrArray);

  /// Check null type.
  bool IsNull(void) const
  { return (m_Type == DSYSysJSONValue_NULL); }

  /// Check boolean type.
  bool IsBoolean(void) const
  { return (m_Type == DSYSysJSONValueBoolean); }

  /// Check integer type.
  bool IsInteger(void) const
  { return (m_Type == DSYSysJSONValueInteger); }

  /// Check double type.
  bool IsDouble(void) const
  { return (m_Type == DSYSysJSONValueFloat); }

  /// Check null type.
  bool IsString(void) const
  { return (m_Type == DSYSysJSONValueString); }

  /// Check object type.
  bool IsObject(void) const
  { return (m_Type == DSYSysJSONValueObject); }

  /// Check array type.
  bool IsArray(void) const
  { return (m_Type == DSYSysJSONValueArray); }

  /// Get value as a boolean.
  bool ToBoolean(void) const
  { return m_Stype._Boolean; }

  /// Get value as an integer.
  CATLONG64 ToInteger(void) const
  { return m_Stype._Integer; }

   /// Get value as a float.
  double ToDouble(void) const
  { return m_Stype._Double; }

  /// Get value as string.
  CATUnicodeString& ToString(void)
  { return m_String; }

  /// Get value as string (with escaping).
  CATUnicodeString ToString(const bool iUnescape);

  /// Get value as an array.
  DSYSysJSONArray& ToArray(void)
  { return m_Array; }

  /// Get value as an object.
  DSYSysJSONObject& ToObject(void)
  { return m_Object; }

  /// Get the value.
  DSYSysJSONValue& operator[](const _DSYSysUTF8_(char)* ipString);

  /// Walk list of value.
  template <class Func, class... Args>
  void Every(Func&& irrfEvery, Args&&... irrArgs);

  DSYSYSJSON_DEPRECATED_R424__(
    /// Value type.
    [[deprecated("[R424/R2022x] Use 'Is...()' instead.")]] int GetType(void) const
    { return m_Type; }

    /// Get the value.
    [[deprecated("[R424/R2022x] Use 'operator[]' instead.")]] DSYSysJSONValue GetByString(const _DSYSysUTF8_(char)* ipString);

    /// Get value as an object.
    [[deprecated("[R424/R2022x] Use 'ToObject()' instead.")]] DSYSysJSONPairList* ToPairs(void);

    /// Get value as an array.
    [[deprecated("[R424/R2022x] Use 'ToArray()' instead.")]] DSYSysJSONValueList* ToValues(void);
  ) // DSYSYSJSON_DEPRECATED_R424__

protected:
  /// Save data.
  HRESULT ChildSaveAsJSON(CATUnicodeString& ioString, const bool iMinify = true, CATUnicodeString iTabulation = "") override;

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
protected:
  /// Value type.
  int m_Type;

  /// Simple type.
  DSYSysJSONValuePrimitive m_Stype;

  /// String.
  CATUnicodeString m_String;

  /// Array.
  DSYSysJSONArray m_Array;

  /// Oject.
  DSYSysJSONObject m_Object;

private:
  /// Escape flag.
  bool m_IsEscaped;
};

/************************************************************************/
/************************************************************************/

/**
 * @class DSYSysJSONPair
 */
class ExportedByCATSysTS DSYSysJSONPair : public DSYSysJSONBase
{
  ///////////////////////////////////////////
  ////////////// Friendship /////////////////
  ///////////////////////////////////////////
  friend class DSYSysJSONObject;

  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /// Constructor (default).
  DSYSysJSONPair();

  /// Constructor (boolean).
  DSYSysJSONPair(const _DSYSysUTF8_(char)* ipString, const bool iBool);
  DSYSysJSONPair(const CATUnicodeString& irString, const bool iBool);

  /// Constructor (integer).
  DSYSysJSONPair(const _DSYSysUTF8_(char)* ipString, const int iInteger);
  DSYSysJSONPair(const CATUnicodeString& irString, const int iInteger);

  /// Constructor (integer).
  DSYSysJSONPair(const _DSYSysUTF8_(char)* ipString, const CATLONG64 iInteger);
  DSYSysJSONPair(const CATUnicodeString& irString, const CATLONG64 iInteger);

  /// Constructor (double).
  DSYSysJSONPair(const _DSYSysUTF8_(char)* ipString, const double iDouble);
  DSYSysJSONPair(const CATUnicodeString& irString, const double iDouble);

  /// Constructor (string).
  DSYSysJSONPair(const _DSYSysUTF8_(char)* ipString, const _DSYSysUTF8_(char)* ipStringBuffer, const bool iEscape = false);
  DSYSysJSONPair(const CATUnicodeString& irString, const _DSYSysUTF8_(char)* ipStringBuffer, const bool iEscape = false);

  /// Constructor (string).
  DSYSysJSONPair(const _DSYSysUTF8_(char)* ipString, const CATUnicodeString& irStringValue, const bool iEscape = false);
  DSYSysJSONPair(const CATUnicodeString& irString, const CATUnicodeString& irStringValue, const bool iEscape = false);

  /// Constructor (string).
  DSYSysJSONPair(const _DSYSysUTF8_(char)* ipString, CATUnicodeString&& irrStringValue, const bool iEscape = false);
  DSYSysJSONPair(const CATUnicodeString& irString, CATUnicodeString&& irrStringValue, const bool iEscape = false);

  /// Constructor (value).
  DSYSysJSONPair(const _DSYSysUTF8_(char)* ipString, const DSYSysJSONValue& irValue);
  DSYSysJSONPair(const CATUnicodeString& irString, const DSYSysJSONValue& irValue);

  /// Constructor (value).
  DSYSysJSONPair(const _DSYSysUTF8_(char)* ipString, DSYSysJSONValue&& irrValue);
  DSYSysJSONPair(const CATUnicodeString& irString, DSYSysJSONValue&& irrValue);

  /// Copy constructor.
  DSYSysJSONPair(const DSYSysJSONPair& irSource);

  /// Constructor (Move).
  DSYSysJSONPair(DSYSysJSONPair&& irrSource);

  /// Destructor.
  virtual ~DSYSysJSONPair();

  /// Assigment operator.
  DSYSysJSONPair& operator=(const DSYSysJSONPair& irSource);

  /// Assignment operator (move).
  DSYSysJSONPair& operator=(DSYSysJSONPair&& irrSource);

  /// Set key/value (boolean).
  void Set(const _DSYSysUTF8_(char)* ipString, const bool iBool);
  void Set(const CATUnicodeString& irString, const bool iBool);

  /// Set key/value (integer).
  void Set(const _DSYSysUTF8_(char)* ipString, const int iInteger);
  void Set(const CATUnicodeString& irString, const int iInteger);

  /// Set key/value (integer).
  void Set(const _DSYSysUTF8_(char)* ipString, const CATLONG64 iInteger);
  void Set(const CATUnicodeString& irString, const CATLONG64 iInteger);

  /// Set key/value (deouble).
  void Set(const _DSYSysUTF8_(char)* ipString, const double iDouble);
  void Set(const CATUnicodeString& irString, const double iDouble);

  /// Set key/value (string).
  void Set(const _DSYSysUTF8_(char)* ipString, const _DSYSysUTF8_(char)* ipStringBuffer, const bool iEscape = false);
  void Set(const CATUnicodeString& irString, const _DSYSysUTF8_(char)* ipStringBuffer, const bool iEscape = false);

  /// Set key/value (string).
  void Set(const _DSYSysUTF8_(char)* ipString, const CATUnicodeString& irStringValue, const bool iEscape = false);
  void Set(const CATUnicodeString& irString, const CATUnicodeString& irStringValue, const bool iEscape = false);

  /// Set key/value (string move).
  void Set(const _DSYSysUTF8_(char)* ipString, CATUnicodeString&& irrStringvalue, const bool iEscape = false);
  void Set(const CATUnicodeString& irString, CATUnicodeString&& irrStringvalue, const bool iEscape = false);

  /// Set key/value.
  void Set(const _DSYSysUTF8_(char)* ipString, const DSYSysJSONValue& irValue);
  void Set(const CATUnicodeString& irString, const DSYSysJSONValue& irValue);

  /// Set key/value.
  void Set(const _DSYSysUTF8_(char)* ipString, DSYSysJSONValue&& irrValue);
  void Set(const CATUnicodeString& irString, DSYSysJSONValue&& irrValue);

  // Update string.
  void Set(const _DSYSysUTF8_(char)* ipString);
  void Set(const CATUnicodeString& irString);
  void Set(CATUnicodeString&& irrString);

  // Update value.
  void Set(const DSYSysJSONValue& irValue);
  void Set(DSYSysJSONValue&& irrValue);

  /// Get pair string.
  CATUnicodeString& GetString(void)
  { return m_String; }

  /// Get pair value.
  DSYSysJSONValue& GetValue(void)
  { return m_Value; }

protected:
  /// Save data.
  HRESULT ChildSaveAsJSON(CATUnicodeString& ioString, const bool iMinify = true, CATUnicodeString iTabulation = "") override;

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
protected:
  /// String.
  CATUnicodeString m_String;

  /// Value.
  DSYSysJSONValue m_Value;
};

/************************************************************************/
/************************************************************************/

# if !defined(__CATBBMagic)

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

  struct js_struct
  {
    DSYSysJSONValue* _pValue;

    jsmn_parser _JsmnParser;

    char* _pJsonString;

    jsmntok_t* _pToken;
    jsmntok_t* _pTokenAlloc;
    unsigned int _TokenAllocSize;

    size_t count;
    int indent;
    int _Next;
  };

  /** @struct DSYSysJSONTokenStruct */
  struct DSYSysJSONTokenStruct
  {
    jsmn_parser _JsmnParser;

    const char* _pJsonString;

    jsmntok_t* _pToken;
    jsmntok_t* _pTokenAlloc;
    jsmntok_t* _pTokenCandidate;

#ifdef PLATEFORME_DS64
    unsigned int _TokenAllocLen;
    unsigned int _TokenAllocSize;

    size_t count;
#else   // PLATEFORME_DS64
    int _TokenAllocLen;
    int _TokenAllocSize;

    int count;
#endif  // PLATEFORME_DS64
    int indent;
    int _Next;
    int _j;
  };
#ifdef __cplusplus
};
#endif  // __cplusplus

/************************************************************************/
/************************************************************************/

/**
 * @struct DSYSysJSONTokenIterator
 */
struct ExportedByCATSysTS DSYSysJSONTokenIterator
{
  using iterator_category = std::forward_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = js_struct;

  /// Constructor (default).
  DSYSysJSONTokenIterator();

  /// Constructor.
  DSYSysJSONTokenIterator(DSYSysJSONTokenizer* ipTokenizer, DSYSysJSONTokenStruct* ipJsonParser, jsmntok_t* ipTokenCandidate, const _DSYSysUTF8_(char)* ipKey = nullptr);

  /// Destructor.
  ~DSYSysJSONTokenIterator();

  /// Reference operator.
  DSYSysJSONToken& operator*() const
  { return *m_pJsonToken; }

  /// Pointer operator.
  DSYSysJSONToken* operator->()
  { return m_pJsonToken; }

  /// Increment operator.
  DSYSysJSONTokenIterator& operator++();

  /// Increment operator.
  DSYSysJSONTokenIterator operator++(int) { DSYSysJSONTokenIterator tmp = *this; ++(*this); return tmp; }

  /// Comparison operator.
  friend bool operator==(const DSYSysJSONTokenIterator& a, const DSYSysJSONTokenIterator& b)
  {
    if( nullptr == a.m_pJsonParser ) { return (nullptr == b.m_pJsonParser); }
    else if( nullptr == b.m_pJsonParser ) { return false; }
    return (a.m_pJsonParser->_Next == b.m_pJsonParser->_Next);
  };

  /// Comparison operator.
  friend bool operator!=(const DSYSysJSONTokenIterator& a, const DSYSysJSONTokenIterator& b)
  {
    if( nullptr == a.m_pJsonParser ) { return (nullptr != b.m_pJsonParser); }
    else if( nullptr == b.m_pJsonParser ) { return true; }
    return a.m_pJsonParser->_Next != b.m_pJsonParser->_Next;
  };

protected:
  DSYSysJSONTokenStruct* m_pJsonParser;

private:
  jsmntok_t* m_pTokenCandidate;
  DSYSysJSONTokenStruct m_TokenStruct;
  DSYSysJSONTokenStruct m_TokenStructNeutral;
  DSYSysJSONToken* m_pJsonToken;
};

/**
 * @class DSYSysJSONToken
 */
class ExportedByCATSysTS DSYSysJSONToken
{
  ///////////////////////////////////////////
  ////////////// Friendship /////////////////
  ///////////////////////////////////////////
  friend struct DSYSysJSONTokenIterator;
  friend class DSYSysJSONTokenizer;

  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /// Constructor (default).
  DSYSysJSONToken()
  : m_pJsonString(nullptr)
  , m_Type(DSYSysJSONValueNull)
  , m_Primitive({ 0 })
  , m_pChar(nullptr)
  , m_CharLen(0)
  , m_pToken(nullptr)
  , m_pTokenizer(nullptr)
  {}

  /// Copy constructor.
  DSYSysJSONToken(const DSYSysJSONToken& irSource)
  { operator=(irSource); }

  /// Constructor (Move).
  DSYSysJSONToken(DSYSysJSONToken&& irrSource)
  { operator=(std::move(irrSource)); }

  /// Destructor.
  virtual ~DSYSysJSONToken()
  { Reset(); }

  /// Assigment operator (copy).
  DSYSysJSONToken& operator=(const DSYSysJSONToken& irSource);

  /// Assignment operator (move).
  DSYSysJSONToken& operator=(DSYSysJSONToken&& irrSource);

  /// Reset.
  void Reset(void);

  /// Chech null type.
  bool IsNull(void) const
  { return (DSYSysJSONValueNull == m_Type); }

  /// Chech bolean type.
  bool IsBoolean(void) const
  { return (DSYSysJSONValueBoolean == m_Type); }

  /// Get value as a boolean.
  bool ToBoolean(void) const
  { return m_Primitive._Boolean; }

  /// Check integer type.
  bool IsInteger(void) const
  { return (DSYSysJSONValueInteger == m_Type); }

  /// Get value as an integer.
  CATLONG64 ToInteger(void) const
  { return m_Primitive._Integer; }

  /// Check double type.
  bool IsDouble(void) const
  { return (DSYSysJSONValueDouble == m_Type); }

  /// Get value as a double.
  double ToDouble(void) const
  { return m_Primitive._Double; }

  /// Check array type.
  bool IsArray(void) const
  { return (DSYSysJSONValueArray == m_Type); }

  /// Check object type.
  bool IsObject(void) const
  { return (DSYSysJSONValueObject == m_Type); }

  /// Check string type.
  bool IsString(void) const
  { return (DSYSysJSONValueString == m_Type); }

  /// Get value as a string.
  CATUnicodeString ToString(const bool iUnescape = false) const
  {
    CATUnicodeString l_String;
    l_String.BuildFromUTF8(m_pChar, m_CharLen);
#if !defined(__CATBBMagic)
    if( iUnescape ) DSYSysJSONStringUnescape(l_String);
#endif  // !__CATBBMagic
    return l_String;
  }

  /// Get value as a string buffer.
  const char* ToChar(size_t& orLen) const
  { orLen = m_CharLen; return m_pChar; }

  /// Get value by string.
  DSYSysJSONToken& operator[](const _DSYSysUTF8_(char)* ipKey)
  { return FindMember(ipKey); }

  /// Get value by string.
  DSYSysJSONToken& operator[](const CATUnicodeString& irString);

  /// Get value by string.
  DSYSysJSONToken& FindMember(const CATUnicodeString& irString);

  /// Get value by string.
  DSYSysJSONToken& FindMember(const _DSYSysUTF8_(char)* ipString);

  /// Begin iteration.
  DSYSysJSONTokenIterator Begin(void);

  /// End iteration.
  DSYSysJSONTokenIterator End(void);

  /// Walk list of value.
  template <class Func, class... Args>
  void Every(Func&& irrfEvery, Args&&... irrArgs);

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
protected:
  /// Original JSON string pointer.
  const _DSYSysUTF8_(char)* m_pJsonString;

  /// JSON type.
  DSYSysJSONValueType m_Type;

  /// Primitive object.
  DSYSysJSONValuePrimitive m_Primitive;

  /// String buffer.
  const char* m_pChar;

  /// String buffer length.
  size_t m_CharLen;

private:
  /// Token item.
  jsmntok_t* m_pToken;

  /// Tokenizer object.
  DSYSysJSONTokenizer* m_pTokenizer;
};

/************************************************************************/
/************************************************************************/

/**
 * class DSYSysJSONTokenizer
 */
class ExportedByCATSysTS DSYSysJSONTokenizer
{
#ifdef DSY_SYS_BAN_EVIL_CONSTRUCTORS_MACROS_DEFINED
  DSYSysBanEvilConstructors(DSYSysJSONTokenizer);
#endif  // DSY_SYS_BAN_EVIL_CONSTRUCTORS_MACROS_DEFINED

  ///////////////////////////////////////////
  ////////////// Friendship /////////////////
  ///////////////////////////////////////////
  friend class DSYSysJSON;
  friend class DSYSysJSONToken;
  friend struct DSYSysJSONTokenIterator;

  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /// Constructor (default).
  DSYSysJSONTokenizer();

  /// Copy constructor.
  //DSYSysJSONTokenizer(const DSYSysJSONTokenizer& irSource);

  /// Constructor (Move).
  //DSYSysJSONTokenizer(DSYSysJSONTokenizer&& irrSource);

  /// Destructor.
  ~DSYSysJSONTokenizer();

  /// Assigment operator (copy).
  //DSYSysJSONTokenizer& operator=(const DSYSysJSONTokenizer& irSource);

  /// Assignment operator (move).
  //DSYSysJSONTokenizer& operator=(DSYSysJSONTokenizer&& irrSource);

  /// Get value by string.
  DSYSysJSONToken& operator[](const _DSYSysUTF8_(char)* ipKey)
  { return FindMember(ipKey); }

protected:
  /// Get value by string.
  DSYSysJSONToken& FindMember(const _DSYSysUTF8_(char)* ipKey, jsmntok_t* ipTokenCandidate = nullptr);

  /// Get value by string.
  jsmntok_t* GetByKey(const _DSYSysUTF8_(char)* ipKey, jsmntok_t* ipTokenCandidate = nullptr) const;

  /// Begin iteration.
  DSYSysJSONTokenIterator Begin(jsmntok_t* ipTokenCandidate);

  /// End iteration.
  DSYSysJSONTokenIterator End(void);

private:
  /// Initialization.
  HRESULT Init(const _DSYSysUTF8_(char)* ipJsonString, DSYSysTraceHandle ihTrace = nullptr);
  HRESULT Init(const _DSYSysUTF8_(char)* ipJsonString, const size_t iJsonStringLen, DSYSysTraceHandle ihTrace = nullptr);

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
protected:
  /// Trace handle.
  DSYSysTraceHandle m_hTrace;

  /// Parser iterator item.
  DSYSysJSONTokenStruct m_JsonParser;

private:
  /// Token map.
  std::map<CATUnicodeString, DSYSysJSONToken> m_vToken;
};

/************************************************************************/
/************************************************************************/

/**
 * @class DSYSysJSON
 */
class ExportedByCATSysTS DSYSysJSON
{
#ifdef DSY_SYS_BAN_EVIL_CONSTRUCTORS_MACROS_DEFINED
  DSYSysBanEvilConstructors(DSYSysJSON);
#endif  // DSY_SYS_BAN_EVIL_CONSTRUCTORS_MACROS_DEFINED

  ///////////////////////////////////////////
  ////// Types/Constants/Struct/Enum ////////
  ///////////////////////////////////////////
public:

  ///////////////////////////////////////////
  ///////////////// Methods /////////////////
  ///////////////////////////////////////////
public:
  /// Constructor (default).
  DSYSysJSON();

  /// Destructor.
  virtual ~DSYSysJSON();

  /// Load from JSON string (DOM).
  HRESULT Load(DSYSysJSONValue& orValue, const _DSYSysUTF8_(char)* ipJSONString);
  HRESULT Load(DSYSysJSONValue& orValue, const CATUnicodeString& irJSONString);

  /// Tokenize JSON string (fast parsing).
  HRESULT Parse(DSYSysJSONTokenizer& iorJsonTokenizer, const _DSYSysUTF8_(char)* ipJSONString);
  HRESULT Parse(DSYSysJSONTokenizer& iorJsonTokenizer, const _DSYSysUTF8_(char)* ipJSONString, const size_t iJSONStringLen);
  HRESULT Parse(DSYSysJSONTokenizer& iorJsonTokenizer, const CATUnicodeString& irJSONString);

public:
  DSYSYSJSON_EXPERIMENTAL_R424__(
    /// Parse JSON string.
    HRESULT Walk(DSYSysJSONWalker& iorJsonWalker, _DSYSysUTF8_(char)* ipJSONString);
  ) // DSYSYSJSON_EXPERIMENTAL_R424__

  DSYSYSJSON_EXPERIMENTAL_R424__(
    /// Parse JSON string (SAX-like).
    HRESULT Parse(const _DSYSysUTF8_(char)* ipJSONString, DSYSysJSONTraverse& iorJsonTraverse);
    HRESULT Parse(const CATUnicodeString& irJSONString, DSYSysJSONTraverse& iorJsonTraverse);
  ) // DSYSYSJSON_EXPERIMENTAL_R424__

public:
  DSYSYSJSON_DEPRECATED_R424__(
    /// Build from string.
    [[deprecated("[R424/R2022x] Use 'Load()' instead.")]] HRESULT Set(const _DSYSysUTF8_(char)* ipJSONString);
    [[deprecated("[R424/R2022x] Use 'Load()' instead.")]] HRESULT Set(const CATUnicodeString& iJSONString);

    /// Set value from value.
    [[deprecated("[R424/R2022x] Use 'DSYSysJSONValue' class directly instead.")]] HRESULT Set(const DSYSysJSONValue& irJSONValue);

    /// Get JSON object as a value.
    [[deprecated("[R424/R2022x] Use 'DSYSysJSONValue' class directly instead.")]] DSYSysJSONValue GetValue(void);

    /// Get a value by a specific string.
    [[deprecated("[R424/R2022x] Use 'operator[]' of 'DSYSysJSONValue' class instead.")]] DSYSysJSONValue GetValue(const _DSYSysUTF8_(char)* ipString);

    /// Export as a JSON string.
    [[deprecated("[R424/R2022x] Use 'Stringify()' instead.")]] CATUnicodeString ToString(const bool iMinify = true);
  ) // DSYSYSJSON_DEPRECATED_R424__

private:
  /// Parse JSON string.
  HRESULT Parse(const _DSYSysUTF8_(char)* ipJSONString, DSYSysJSONTraverse& iorJsonTraverse, DSYSysJSONValue* opValue);

  /// Internal parser function.
  void* ParseInternal(const _DSYSysUTF8_(char)* ipJSON, void* ipRootToken, void* ipCurrToken, DSYSysJSONTraverse& iorJsonTraverse, DSYSysJSONValue* iopValue = nullptr);

  ///////////////////////////////////////////
  ///////////////// Members /////////////////
  ///////////////////////////////////////////
private:
  /// Internal buffer.
  char* m_pBuffer;

  /// Internal buffer size.
  size_t m_BufferSize;

  /// Token array.
  void* m_pTokenArray;

  /// Token array size.
  unsigned int m_TokenCount;

  /// Trace handle.
  DSYSysTraceHandle m_hTrace;

  DSYSYSJSON_DEPRECATED_R424__(
private:
    /// Value.
    DSYSysJSONValue* m_pValue;
  ) // DSYSYSJSON_DEPRECATED_R424__
};

/************************************************************************/
/* Classes implementation                                               */
/************************************************************************/

//=======================================================================
template <class Func, class... Args>
inline void DSYSysJSONArray::Every(Func&& irrfEvery, Args&&... irrArgs)
//=======================================================================
{
  if( nullptr == m_pValues ) return;

  // Walk values.
  for( auto it = m_pValues->begin(); it != m_pValues->end(); it++ )
  {
    if( !irrfEvery(*it, irrArgs...) ) break;
  }
}

/************************************************************************/
/************************************************************************/

//=======================================================================
template <class Func, class... Args>
inline void DSYSysJSONObject::Every(Func&& irrfEvery, Args&&... irrArgs)
//=======================================================================
{
  if( nullptr == m_pvPairs ) return;

  // Walk pairs.
  for( auto it = m_pvPairs->begin(); it != m_pvPairs->end(); ++it )
  { if( !irrfEvery(*it, irrArgs...) ) break; }
}

/************************************************************************/
/************************************************************************/

//=======================================================================
template <class Func, class... Args>
inline void DSYSysJSONValue::Every(Func&& irrfEvery, Args&&... irrArgs)
//=======================================================================
{
  // Array only.
  if( !IsArray() ) return;

  // Walk values.
  for( auto it = m_Array.Begin(); it != m_Array.End(); it++ )
  {
    if( !irrfEvery(*it, irrArgs...) ) break;
  }
}

/************************************************************************/
/************************************************************************/

//=======================================================================
template <class Func, class... Args>
inline void DSYSysJSONToken::Every(Func&& irrfEvery, Args&&... irrArgs)
//=======================================================================
{
  // Array only.
  if( !IsArray() ) return;

  // Walk values.
  for( DSYSysJSONTokenIterator itr = Begin(); itr != End(); ++itr )
  {
    if( !irrfEvery(*itr, irrArgs...) ) break;
  }
}

# endif // !__CATBBMagic

#endif  // DSYSysJSON_H
