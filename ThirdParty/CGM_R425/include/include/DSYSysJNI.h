#ifndef DSYSysJNI_H
#define DSYSysJNI_H

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#if defined(__DSYSysJNI)
# define ExportedByDSYSysJNI  DSYExport
#else  // __DSYSysJNI
# define ExportedByDSYSysJNI  DSYImport
#endif // __DSYSysJNI

#define DSY_SYS_JNI_VERSION                       JNI_VERSION_1_4

/************************************************************************/
/* Global includes                                                      */
/************************************************************************/
#include <jni.h>

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATSysErrorDef.h"
#include "DSYExport.h"

/************************************************************************/
/* Classes declaration                                                  */
/************************************************************************/

/**
 * This class gives access to the JNIEnv pointer
 */
class ExportedByDSYSysJNI DSYSysJNIEnv
{
public:
  /** 
   * Get the JNIEnv pointer
   * Warning, this pointer is only valid in the thread from which this method is called
   * That's why you should never store it for future use
   * @return the JNIEnv pointer (it must not be destroyed in any way)
   */
  static JNIEnv * GetJNIEnv();

  /**
   * Get JNI environment.
   *
   * @param opJNIErrorCode  JNI error code.
   * @param oppJavaVM       Java VM object.
   * @param oppJniEnv       Pointer to native method interface.
   */
  static void Get(int* opJNIErrorCode, JavaVM** oppJavaVM, JNIEnv** oppJniEnv);

  /**
   * Attach the JNI environment to the current thread.
   *
   * @param ipJavaVM    Java VM object.
   * @param oppJniEnv   Pointer to native method interface.
   *
   * @return            0 if successful or -1 in the case of an error.
   */
  static int AttachToThread(JavaVM** oppJavaVM, JNIEnv** oppJniEnv);

  /**
   * Detach the JNI environment to the current thread.
   *
   * @param ipJavaVM    Java VM object.
   *
   * @return            0 if successful or -1 in the case of an error.
   */
  static int DetachFromThread(JavaVM* ipJavaVM);

  /**
   * Check if a JNI exception has occured
   * @param iPrintStackTrace set to TRUE to display the stack associated with the exception
   * @param iClearException set to TRUE to clear exception if any is pending
   * @return FALSE if no JNI exception is pending
   */
  static CATBoolean HandleJNIException(CATBoolean iPrintStackTrace = TRUE, CATBoolean iClearException = TRUE);

private:
  // Remove default methods provided by compiler
  DSYSysJNIEnv();
  DSYSysJNIEnv(const DSYSysJNIEnv&);
  DSYSysJNIEnv& operator = (const DSYSysJNIEnv&);
};

#define DSYSysJNIDeclareClass \
  public: \
    virtual const char * IsA() const; \
    virtual CATBoolean IsAKindOf(const char *) const;

#define DSYSysJNIImplementClass(Class, BaseClass) \
  const char * Class::IsA() const \
  { \
    return #Class; \
  } \
  CATBoolean Class::IsAKindOf(const char * iClassName) const \
  { \
    if (NULL != iClassName && strcmp(iClassName, #Class) == 0) \
      return TRUE; \
    return BaseClass::IsAKindOf(iClassName); \
  }

enum jtype {
  jt_error        = -1,
  jt_void         = 0,
  jt_boolean      = 1,
  jt_byte         = 2,
  jt_char         = 3,
  jt_short        = 4,
  jt_int          = 5,
  jt_long         = 6,
  jt_float        = 7,
  jt_double       = 8,
  jt_object       = 9,
  jt_class        = 10,
  jt_string       = 11,
  jt_objectArray  = 12,
  jt_booleanArray = 13,
  jt_byteArray    = 14,
  jt_charArray    = 15,
  jt_shortArray   = 16,
  jt_intArray     = 17,
  jt_longArray    = 18,
  jt_floatArray   = 19,
  jt_doubleArray  = 20
};

/**
 * This class is the base class for all JNI objects
 */
class ExportedByDSYSysJNI DSYSysJNIAny
{
  friend class DSYSysJNIJBoolean;
  friend class DSYSysJNIJByte;
  friend class DSYSysJNIJChar;
  friend class DSYSysJNIJShort;
  friend class DSYSysJNIJInt;
  friend class DSYSysJNIJLong;
  friend class DSYSysJNIJFloat;
  friend class DSYSysJNIJDouble;
  friend class DSYSysJNIJObject;
  friend class DSYSysJNIJObjectArray;

  friend class DSYSysJNIJTest;

private:
  /**
   * Constructor
   */
  DSYSysJNIAny();

  /**
   * Constructor
   * @param iClassName the object class name
   */
  DSYSysJNIAny(const char * iClassName);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIAny(const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIAny& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Destructor
   */
  virtual ~DSYSysJNIAny();

public:
  /**
   * Get this object class name
   * Must be overriden by sub classes (use DSYSysJNIDeclareClass/DSYSysJNIImplementClass)
   * @return the object class name
   */
  virtual const char * IsA() const;

  /**
   * Check if this object is an instance of a specific class (ex: "DSYSysJNIJObject")
   * Must be overriden by sub classes (use DSYSysJNIDeclareClass/DSYSysJNIImplementClass)
   * @param iClassName the class name
   * @return TRUE if this object is an instance of the specified class, FALSE otherwise
   */
  virtual CATBoolean IsAKindOf(const char * iClassName) const;

  /**
   * Check if this object is an instance of a specific java class (ex: "java/lang/String")
   * @param iClassName the class name
   * @return TRUE if this object is an instance of the specified class, FALSE otherwise
   */
  CATBoolean IsInstanceOf(const char * iClassName) const;

  /**
   * Get the native jtype
   * @return the native jtype
   */
  jtype GetType() const;

  /**
   * Get the native jvalue
   * @return the native jvalue
   */
  virtual jvalue GetValue() const;

  /**
   * Get the native jclass
   * @return the native jclass
   */
  jclass GetClass() const;

  /**
   * Get the native jclass name
   * @return the native jclass name (must not be modified nor destroyed by the caller)
   */
  const char * const GetClassName() const;

protected:
  /**
   * Invalidate this JNI object
   */
  virtual void Invalidate();

protected:
  jtype _jType;
  jclass _jClass;
  char * _jClassName;
  jvalue _jValue;
};

/**
 * This class represents a jboolean
 */
class ExportedByDSYSysJNI DSYSysJNIJBoolean : public DSYSysJNIAny
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iValue the boolean value
   */
  DSYSysJNIJBoolean(CATBoolean iValue = FALSE);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJBoolean(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJBoolean(const DSYSysJNIJBoolean& iSrc);

  /**
   * Assignment
   * @param iValue the boolean value
   */
  virtual DSYSysJNIJBoolean& operator = (CATBoolean iValue);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJBoolean& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJBoolean& operator = (const DSYSysJNIJBoolean& iSrc);

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJBoolean();

  /**
   * Get the boolean value
   * @return the boolean value
   */
  CATBoolean GetBoolean() const;
};

/**
 * This class represents a jbyte
 */
class ExportedByDSYSysJNI DSYSysJNIJByte : public DSYSysJNIAny
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iValue the char value
   */
  DSYSysJNIJByte(char iValue = '\0');

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJByte(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJByte(const DSYSysJNIJByte& iSrc);

  /**
   * Assignment
   * @param iValue the char value
   */
  virtual DSYSysJNIJByte& operator = (char iValue);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJByte& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJByte& operator = (const DSYSysJNIJByte& iSrc);

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJByte();

  /**
   * Get the char value
   * @return the char value
   */
  char GetByte() const;
};

/**
 * This class represents a jchar
 */
class ExportedByDSYSysJNI DSYSysJNIJChar : public DSYSysJNIAny
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iValue the UTF-16 char value
   */
  DSYSysJNIJChar(unsigned short iValue = 0);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJChar(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJChar(const DSYSysJNIJChar& iSrc);

  /**
   * Assignment
   * @param iValue the UTF-16 char value
   */
  virtual DSYSysJNIJChar& operator = (unsigned short iValue);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJChar& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJChar& operator = (const DSYSysJNIJChar& iSrc);

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJChar();

  /**
   * Get the UTF-16 char value
   * @return the UTF-16 char value
   */
  unsigned short GetChar() const;
};

/**
 * This class represents a jshort
 */
class ExportedByDSYSysJNI DSYSysJNIJShort : public DSYSysJNIAny
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iValue the short value
   */
  DSYSysJNIJShort(short iValue = 0);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJShort(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJShort(const DSYSysJNIJShort& iSrc);

  /**
   * Assignment
   * @param iValue the short value
   */
  virtual DSYSysJNIJShort& operator = (short iValue);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJShort& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJShort& operator = (const DSYSysJNIJShort& iSrc);

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJShort();

  /**
   * Get the short value
   * @return the short value
   */
  short GetShort() const;
};

/**
 * This class represents a jint
 */
class ExportedByDSYSysJNI DSYSysJNIJInt : public DSYSysJNIAny
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iValue the int value
   */
  DSYSysJNIJInt(CATINT32 iValue = 0);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJInt(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJInt(const DSYSysJNIJInt& iSrc);

  /**
   * Assignment
   * @param iValue the int value
   */
  virtual DSYSysJNIJInt& operator = (CATINT32 iValue);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJInt& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJInt& operator = (const DSYSysJNIJInt& iSrc);

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJInt();

  /**
   * Get the int value
   * @return the int value
   */
  CATINT32 GetInt() const;
};

/**
 * This class represents a jlong
 */
class ExportedByDSYSysJNI DSYSysJNIJLong : public DSYSysJNIAny
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iValue the long value
   */
  DSYSysJNIJLong(CATLONG64 iValue = 0);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJLong(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJLong(const DSYSysJNIJLong& iSrc);

  /**
   * Assignment
   * @param iValue the long value
   */
  virtual DSYSysJNIJLong& operator = (CATLONG64 iValue);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJLong& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJLong& operator = (const DSYSysJNIJLong& iSrc);

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJLong();

  /**
   * Get the long value
   * @return the long value
   */
  CATLONG64 GetLong() const;
};

/**
 * This class represents a jfloat
 */
class ExportedByDSYSysJNI DSYSysJNIJFloat : public DSYSysJNIAny
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iValue the float value
   */
  DSYSysJNIJFloat(float iValue = 0);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJFloat(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJFloat(const DSYSysJNIJFloat& iSrc);

  /**
   * Assignment
   * @param iValue the float value
   */
  virtual DSYSysJNIJFloat& operator = (float iValue);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJFloat& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJFloat& operator = (const DSYSysJNIJFloat& iSrc);

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJFloat();

  /**
   * Get the float value
   * @return the float value
   */
  float GetFloat() const;
};

/**
 * This class represents a jdouble
 */
class ExportedByDSYSysJNI DSYSysJNIJDouble : public DSYSysJNIAny
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iValue the double value
   */
  DSYSysJNIJDouble(double iValue = 0);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJDouble(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJDouble(const DSYSysJNIJDouble& iSrc);

  /**
   * Assignment
   * @param iValue the double value
   */
  virtual DSYSysJNIJDouble& operator = (double iValue);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJDouble& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJDouble& operator = (const DSYSysJNIJDouble& iSrc);

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJDouble();

  /**
   * Get the double value
   * @return the double value
   */
  double GetDouble() const;
};

/**
 * This class represents a jobject
 */
class ExportedByDSYSysJNI DSYSysJNIJObject : public DSYSysJNIAny
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   */
  DSYSysJNIJObject();

  /**
   * Constructor
   * @param iClassName the object class name (ex: "java/lang/Object")
   */
  DSYSysJNIJObject(const char * iClassName);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJObject(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJObject(const DSYSysJNIJObject& iSrc);

  /**
   * Constructor (copy and cast)
   * @param iSrc the object to copy and cast
   * @param iClassName the class name into which the object to copy must be casted
   */
  DSYSysJNIJObject(const DSYSysJNIJObject& iSrc, const char * iClassName);

  /**
   * Constructor (to be used carefully)
   * @param iObject the native object
   * @param iClassName the native object class name
   *        when class name is unknown, you can use "java/lang/Object" and then use GetClassNameEx with copy/cast constructor
   */
  DSYSysJNIJObject(jobject iObject, const char * iClassName);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJObject& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJObject& operator = (const DSYSysJNIJObject& iSrc);

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJObject();

  /**
   * Create native instance
   * @param iSignature the constructor signature
   * @param iParams the constructor parameters
   * @param iParamsCount the count of parameters
   * @return S_OK on success
   */
  HRESULT CreateInstance(const char * iSignature = "()V", DSYSysJNIAny ** iParams = NULL, int iParamsCount = 0);

  /**
   * Invoke method on native instance
   * @param iName the method name
   * @param iSignature the method signature
   * @param iParams the method parameters
   * @param iParamsCount the count of parameters
   * @param oResult the value returned by the method
   * @param iStatic set to TRUE to invoke a static method
   * @return S_OK on success
   */
  HRESULT Invoke(const char * iName, const char * iSignature, DSYSysJNIAny ** iParams, int iParamsCount, DSYSysJNIAny& oResult, CATBoolean iStatic = FALSE) const;

  /**
   * Get a field on native instance
   * @param iName the method name
   * @param iSignature the method signature
   * @param oResult the field value
   * @param iStatic set to TRUE to get a static field
   * @return S_OK on success
   */
  HRESULT Get(const char * iName, const char * iSignature, DSYSysJNIAny& oResult, CATBoolean iStatic = FALSE) const;

  /**
   * Set a field on native instance
   * @param iName the method name
   * @param iSignature the method signature
   * @param iValue the field value
   * @param iStatic set to TRUE to set a static field
   * @return S_OK on success
   */
  HRESULT Set(const char * iName, const char * iSignature, const DSYSysJNIAny& iValue, CATBoolean iStatic = FALSE);

  /**
   * Check if this object is a valid object
   * @return TRUE if this object is valid
   */
  CATBoolean IsValid();

  /**
   * Get the native jclass name
   * @return the native jclass name (must not be modified nor destroyed by the caller)
   *         contrary to GetClassName, this method returns the "real" class of this object
   */
  const char * const GetClassNameEx();

  /**
   * Create a new global reference to the native jobject (to be used carefully)
   * @return a new global referece to the native jobject
   */
  jobject MakeNewGlobalRef() const;

protected:
  /**
   * Invalidate this JNI object
   */
  virtual void Invalidate();

  /**
   * Get class name of a native object
   * @param iValue the native object
   * @return the class name on success (must be destroyed by the caller with free)
   */
  static char * GetObjectClassName(jobject iValue);

protected:
  char * _jClassNameEx;
};

/**
 * This class represents a jstring
 */
class ExportedByDSYSysJNI DSYSysJNIJString : public DSYSysJNIJObject
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iUTF8Value the UTF-8 string value
   */
  DSYSysJNIJString(const char * iUTF8Value = "");

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJString(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJString(const DSYSysJNIJString& iSrc);

  /**
   * Constructor (to be used carefully)
   * @param iString the native string
   */
  DSYSysJNIJString(jstring iString);

  /**
   * Assignment
   * @param iUTF8Value the UTF-8 string value to copy
   */
  virtual DSYSysJNIJString& operator = (const char * iUTF8Value);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJString& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJString& operator = (const DSYSysJNIJString& iSrc);

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJString();

  /**
   * Get the string value
   * @return the string value as UTF8 buffer (must be destroyed by the caller with delete [])
   */
  char * GetUTF8String() const;

private:
  /**
   * Initialize from UTF8 string
   * @param iUTF8Buffer the UTF8 string buffer
   * @param iUTF8Length the UTF8 string length
   */
  void Initialize(const char * iUTF8Buffer, int iUTF8Length);

  /**
   * Initialize from native object
   * @param iString the native object string
   */
  void Initialize(jobject iString);
};

/**
 * This class represents a jbooleanArray
 */
class ExportedByDSYSysJNI DSYSysJNIJBooleanArray : public DSYSysJNIJObject
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iItems the items
   * @param iItemsCount the items count
   */
  DSYSysJNIJBooleanArray(const CATBoolean * iItems = NULL, int iItemsCount = 0);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJBooleanArray(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJBooleanArray(const DSYSysJNIJBooleanArray& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJBooleanArray& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJBooleanArray& operator = (const DSYSysJNIJBooleanArray& iSrc);

  /**
   * Get the items
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetItems(CATBoolean *& oItems) const;

  /**
   * Get the items count
   * @return the items count or -1 on error
   */
  int GetItemsCount() const;

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJBooleanArray();

private:
  /**
   * Initialize array from items
   * @param iItems the items
   * @param iItemsCount the items count
   */
  void Initialize(const CATBoolean * iItems, int iItemsCount);

  /**
   * Initialize array from native array
   * @param iValue the native object value
   */
  void Initialize(jobject iValue);

  /**
   * Get data from native array
   * @param iValue the native object value
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetData(jobject iValue, CATBoolean *& oItems) const;
};

/**
 * This class represents a jbyteArray
 */
class ExportedByDSYSysJNI DSYSysJNIJByteArray : public DSYSysJNIJObject
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iItems the items
   * @param iItemsCount the items count
   */
  DSYSysJNIJByteArray(const char * iItems = NULL, int iItemsCount = 0);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJByteArray(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJByteArray(const DSYSysJNIJByteArray& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJByteArray& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJByteArray& operator = (const DSYSysJNIJByteArray& iSrc);

  /**
   * Get the items
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetItems(char *& oItems) const;

  /**
   * Get the items count
   * @return the items count or -1 on error
   */
  int GetItemsCount() const;

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJByteArray();

private:
  /**
   * Initialize array from items
   * @param iItems the items
   * @param iItemsCount the items count
   */
  void Initialize(const char * iItems, int iItemsCount);

  /**
   * Initialize array from native array
   * @param iValue the native object value
   */
  void Initialize(jobject iValue);

  /**
   * Get data from native array
   * @param iValue the native object value
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetData(jobject iValue, char *& oItems) const;
};

/**
 * This class represents a jcharArray
 */
class ExportedByDSYSysJNI DSYSysJNIJCharArray : public DSYSysJNIJObject
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iItems the items
   * @param iItemsCount the items count
   */
  DSYSysJNIJCharArray(const unsigned short * iItems = NULL, int iItemsCount = 0);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJCharArray(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJCharArray(const DSYSysJNIJCharArray& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJCharArray& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJCharArray& operator = (const DSYSysJNIJCharArray& iSrc);

  /**
   * Get the items
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetItems(unsigned short *& oItems) const;

  /**
   * Get the items count
   * @return the items count or -1 on error
   */
  int GetItemsCount() const;

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJCharArray();

private:
  /**
   * Initialize array from items
   * @param iItems the items
   * @param iItemsCount the items count
   */
  void Initialize(const unsigned short * iItems, int iItemsCount);

  /**
   * Initialize array from native array
   * @param iValue the native object value
   */
  void Initialize(jobject iValue);

  /**
   * Get data from native array
   * @param iValue the native object value
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetData(jobject iValue, unsigned short *& oItems) const;
};

/**
 * This class represents a jshortArray
 */
class ExportedByDSYSysJNI DSYSysJNIJShortArray : public DSYSysJNIJObject
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iItems the items
   * @param iItemsCount the items count
   */
  DSYSysJNIJShortArray(const short * iItems = NULL, int iItemsCount = 0);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJShortArray(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJShortArray(const DSYSysJNIJShortArray& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJShortArray& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJShortArray& operator = (const DSYSysJNIJShortArray& iSrc);

  /**
   * Get the items
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetItems(short *& oItems) const;

  /**
   * Get the items count
   * @return the items count or -1 on error
   */
  int GetItemsCount() const;

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJShortArray();

private:
  /**
   * Initialize array from items
   * @param iItems the items
   * @param iItemsCount the items count
   */
  void Initialize(const short * iItems, int iItemsCount);

  /**
   * Initialize array from native array
   * @param iValue the native object value
   */
  void Initialize(jobject iValue);

  /**
   * Get data from native array
   * @param iValue the native object value
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetData(jobject iValue, short *& oItems) const;
};

/**
 * This class represents a jintArray
 */
class ExportedByDSYSysJNI DSYSysJNIJIntArray : public DSYSysJNIJObject
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iItems the items
   * @param iItemsCount the items count
   */
  DSYSysJNIJIntArray(const CATINT32 * iItems = NULL, int iItemsCount = 0);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJIntArray(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJIntArray(const DSYSysJNIJIntArray& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJIntArray& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJIntArray& operator = (const DSYSysJNIJIntArray& iSrc);

  /**
   * Get the items
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetItems(CATINT32 *& oItems) const;

  /**
   * Get the items count
   * @return the items count or -1 on error
   */
  int GetItemsCount() const;

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJIntArray();

private:
  /**
   * Initialize array from items
   * @param iItems the items
   * @param iItemsCount the items count
   */
  void Initialize(const CATINT32 * iItems, int iItemsCount);

  /**
   * Initialize array from native array
   * @param iValue the native object value
   */
  void Initialize(jobject iValue);

  /**
   * Get data from native array
   * @param iValue the native object value
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetData(jobject iValue, CATINT32 *& oItems) const;
};

/**
 * This class represents a jlongArray
 */
class ExportedByDSYSysJNI DSYSysJNIJLongArray : public DSYSysJNIJObject
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iItems the items
   * @param iItemsCount the items count
   */
  DSYSysJNIJLongArray(const CATLONG64 * iItems = NULL, int iItemsCount = 0);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJLongArray(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJLongArray(const DSYSysJNIJLongArray& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJLongArray& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJLongArray& operator = (const DSYSysJNIJLongArray& iSrc);

  /**
   * Get the items
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetItems(CATLONG64 *& oItems) const;

  /**
   * Get the items count
   * @return the items count or -1 on error
   */
  int GetItemsCount() const;

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJLongArray();

private:
  /**
   * Initialize array from items
   * @param iItems the items
   * @param iItemsCount the items count
   */
  void Initialize(const CATLONG64 * iItems, int iItemsCount);

  /**
   * Initialize array from native array
   * @param iValue the native object value
   */
  void Initialize(jobject iValue);

  /**
   * Get data from native array
   * @param iValue the native object value
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetData(jobject iValue, CATLONG64 *& oItems) const;
};

/**
 * This class represents a jfloatArray
 */
class ExportedByDSYSysJNI DSYSysJNIJFloatArray : public DSYSysJNIJObject
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iItems the items
   * @param iItemsCount the items count
   */
  DSYSysJNIJFloatArray(const float * iItems = NULL, int iItemsCount = 0);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJFloatArray(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJFloatArray(const DSYSysJNIJFloatArray& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJFloatArray& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJFloatArray& operator = (const DSYSysJNIJFloatArray& iSrc);

  /**
   * Get the items
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetItems(float *& oItems) const;

  /**
   * Get the items count
   * @return the items count or -1 on error
   */
  int GetItemsCount() const;

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJFloatArray();

private:
  /**
   * Initialize array from items
   * @param iItems the items
   * @param iItemsCount the items count
   */
  void Initialize(const float * iItems, int iItemsCount);

  /**
   * Initialize array from native array
   * @param iValue the native object value
   */
  void Initialize(jobject iValue);

  /**
   * Get data from native array
   * @param iValue the native object value
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetData(jobject iValue, float *& oItems) const;
};

/**
 * This class represents a jdoubleArray
 */
class ExportedByDSYSysJNI DSYSysJNIJDoubleArray : public DSYSysJNIJObject
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   * @param iItems the items
   * @param iItemsCount the items count
   */
  DSYSysJNIJDoubleArray(const double * iItems = NULL, int iItemsCount = 0);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJDoubleArray(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJDoubleArray(const DSYSysJNIJDoubleArray& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJDoubleArray& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJDoubleArray& operator = (const DSYSysJNIJDoubleArray& iSrc);

  /**
   * Get the items
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetItems(double *& oItems) const;

  /**
   * Get the items count
   * @return the items count or -1 on error
   */
  int GetItemsCount() const;

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJDoubleArray();

private:
  /**
   * Initialize array from items
   * @param iItems the items
   * @param iItemsCount the items count
   */
  void Initialize(const double * iItems, int iItemsCount);

  /**
   * Initialize array from native array
   * @param iValue the native object value
   */
  void Initialize(jobject iValue);

  /**
   * Get data from native array
   * @param iValue the native object value
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetData(jobject iValue, double *& oItems) const;
};

/**
 * This class represents a jobjectArray
 */
class ExportedByDSYSysJNI DSYSysJNIJObjectArray : public DSYSysJNIJObject
{
  DSYSysJNIDeclareClass;

public:
  /**
   * Constructor
   */
  DSYSysJNIJObjectArray();

  /**
   * Constructor
   * @param iClassName the object item class name (ex: "java/lang/String")
   * @param iItems the items
   * @param iItemsCount the items count
   */
  DSYSysJNIJObjectArray(const char * iItemClassName, const DSYSysJNIJObject * iItems = NULL, int iItemsCount = 0);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJObjectArray(const DSYSysJNIAny& iSrc);

  /**
   * Constructor (copy)
   * @param iSrc the object to copy
   */
  DSYSysJNIJObjectArray(const DSYSysJNIJObjectArray& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJObjectArray& operator = (const DSYSysJNIAny& iSrc);

  /**
   * Assignment
   * @param iSrc the object to copy
   */
  virtual DSYSysJNIJObjectArray& operator = (const DSYSysJNIJObjectArray& iSrc);

  /**
   * Get the items
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetItems(DSYSysJNIJObject *& oItems) const;

  /**
   * Get the items count
   * @return the items count or -1 on error
   */
  int GetItemsCount() const;

  /**
   * Destructor
   */
  virtual ~DSYSysJNIJObjectArray();

private:
  /**
   * Initialize array from items
   * @param iClassName the object item class name
   * @param iItems the items
   * @param iItemsCount the items count
   */
  void Initialize(const char * iItemClassName, const DSYSysJNIJObject * iItems, int iItemsCount);

  /**
   * Initialize array from native array
   * @param iValue the native object value
   */
  void Initialize(jobject iValue);

  /**
   * Get data from native array
   * @param iValue the native object value
   * @param oItems the items (must be destroyed by the caller with delete[])
   * @return the items count or -1 on error
   */
  int GetData(jobject iValue, DSYSysJNIJObject *& oItems) const;
};

/************************************************************************/
/* Defines                                                              */
/************************************************************************/

#define USE_JSTRING_CONVERSION(T) \
  static DSYSysJNIJString JStringFrom##T(const T& iString) \
  { \
    DSYSysJNIJString jString; \
    \
    size_t utf8length = iString.GetLengthInChar() * 4 + 1; \
    char * utf8buffer = new char[utf8length]; \
    memset(utf8buffer, 0, utf8length); \
    iString.ConvertToUTF8(utf8buffer, &utf8length); \
    \
    jString = utf8buffer; \
    \
    delete [] utf8buffer; \
    utf8buffer = NULL; \
    \
    return jString; \
  } \
  \
  static T T##FromJString(const DSYSysJNIJString& iString) \
  { \
    T string; \
    \
    char * utf8buffer = iString.GetUTF8String(); \
    if (NULL != utf8buffer) \
    { \
      string.BuildFromUTF8(utf8buffer, strlen(utf8buffer)); \
      delete [] utf8buffer; \
      utf8buffer = NULL; \
    } \
    \
    return string; \
  }

#define USE_CATUNICODESTRING_CONVERSION        USE_JSTRING_CONVERSION(CATUnicodeString)

#endif
