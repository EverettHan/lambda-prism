#ifndef CATCGMOutput_h_
#define CATCGMOutput_h_

// COPYRIGHT DASSAULT SYSTEMES  1999
//
// cgmout      : Sortie standard uniquement sous  CATDevelopmentStage
// cgmerr      : Sortie erreur   uniquement sous  CATDevelopmentStage
// cgmstatus   : dedie ODT de l'organisation CGM (uniquement moteur ODT)
// cgmstat     : dedie ODT de l'organisation CGM (pour statistique Developpeur CGMTest_Stat)
// cgmodt      : Sortie standard uniquement active sous mkodt
// cgmdoc      : dedie ODT de l'organisation CGM (uniquement moteur ODT. fichier doc des odts)
//

//=============================================================================
// jul 02  Portage 64 bits                                              HCN
// deb 06  Gestion d'un fichier cgmdoc                                  NLD
//=============================================================================

#include "ExportedByCATMathStream.h"

#ifndef NULL
/** 
* Defines the null value.
*/
#define NULL 0
#endif
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
#ifdef _WINDOWS_SOURCE
/** @c++ansi fbq 2004-08-06.11:10:35 [Redefinition of SMANIP()] **/
#ifdef _CAT_ANSI_STREAMS
#include <iomanip.h>
#define SMANIP(t) std::_Smanip<##t> 
#define __SMANIP_int SMANIP(int)
#else
class __SMANIP_int ;
#endif // _CAT_ANSI_STREAMS
#else
class smanip_int ;
#endif


class CATString;
class CATUnicodeString;

#include "CATBoolean.h"
#include "CATListOfInt.h"
#include "CATListOfFloat.h"
#include "CATListOfDouble.h"
#include "CATListOfCATString.h"
#include "CATMathInline.h"
#include "CATIAV5Level.h"
#ifdef CATIAR212
class CATListValShort;
#endif

// 64bits
#include "CATDataType.h"

// Version de Dump
#include "CATCGMStreamVersion.h"

/**
 * Class defining the dump of mathematical objects. 
 *<br> 
 * This class is an encapsulation of the <tt>ostream</tt>, <tt>ofstream</tt> classes. 
 */
class ExportedByCATMathStream CATCGMOutput
{
public :

  INLINE CATBoolean IsActive() const;

/**
 * Output device.
 * @param StdOut
 * The standard output.
 * @param StdErr
 * The standard error output.
 * @param
 * A file.
 * @param String
 * A string.
 * @param Format
 *
 */
  enum Mode {StdOut,StdErr,File,String,Format};

/**
 * The way to open the output.
 * @param out
 * To write.
 * @param ate
 * To locate at the end of the file. 
 * @param app
 * To add the date at the end of the strean(and not at the current position)
 * @param trunc
 * To delete the content of the current stream if it already exists.
 * @param nocreate
 * To block the creation of the stream if it does not currently exists.
 * @param noreplace
 * To block the opening if the stream already exists.
 */
  enum FileOpen {out, ate, app, trunc, nocreate, noreplace};

/**
 * Constructs a CATCGMOutput from an ostream.
 * @param iOsToCopy 
 * The pointer to the ostream to copy.
 */
  CATCGMOutput(ostream* iOsToCopy = NULL);

/**
 * Constructs a CATCGMOutput.
 * @param iMode
 * The output device.
 * @param iFilename
 * The name of the file (if <tt>iMode=CATCGMOutut::File</tt>).
 * @param FileOpen
 * The way to open the output.
 */
  CATCGMOutput(Mode iMode, const char* iFilename=NULL, FileOpen iOpen=out);

  virtual ~CATCGMOutput();

/**
 *  Outputs a <tt>char</tt>.
 * @param iChar
 * The char to output.
 */
  CATCGMOutput&	operator<<(char iChar);

/**
 *  Outputs an <tt>unsigned char</tt>.
 * @param iUChar
 * The unsigned char to output.
 */
  CATCGMOutput&	operator<<(unsigned char iUChar) ;

/**
 *  Outputs a  <tt>char</tt>.
 * @param iChar
 * The pointer to the char to output.
 */
  CATCGMOutput&	operator<<(const char*);

/**
 *  Outputs an <tt>int</tt>.
 * @param iInt
 * The int to output.
 */
  CATCGMOutput&	operator<<(int iInt); 

#ifndef PLATEFORME_DS64
/**
 *  Outputs a <tt>CATLONG32</tt>.
 * @param ilong
 * The CATLONG32 to output.
 */
  CATCGMOutput&	operator<<(CATLONG32 iLong);
#endif

/**
 *  Outputs a <tt>double</tt>.
 * @param iDouble
 * The double to output.
 */
  CATCGMOutput&	operator<<(double iDouble);

/**
 *  Outputs a <tt>float</tt>.
 * @param iFloat
 * The float to output.
 */
  CATCGMOutput&	operator<<(float iFloat);

/**
 *  Outputs an <tt>unsigned int</tt>.
 * @param iUInt
 * The unsigned int to output.
 */
  CATCGMOutput&	operator<<(unsigned int iUInt);

#ifndef PLATEFORME_DS64
/**
 *  Outputs an <tt>CATULONG32 </tt>.
 * @param iULong
 * The CATULONG32  to output.
 */
  CATCGMOutput&	operator<<(CATULONG32  iUlong);
#endif

  CATCGMOutput&	operator<<(void* iPointer);

/**
 *  Outputs a <tt>short</tt>.
 * @param iShort
 * The short to output.
 */
  CATCGMOutput&	operator<<(short iShort) ;

/**
 *  Outputs an <tt>unsigned short</tt>.
 * @param iUShort
 * The unsigned short to output.
 */
 CATCGMOutput&	operator<<(unsigned short iUShort) ;

#ifdef PLATEFORME_DS64

/**
 *  Outputs an <tt>CATLONG64</tt>.
 * @param iLONG64
 * The 64-bit signed integer to output.
 */
  CATCGMOutput&	operator<<(CATLONG64 iLONG64) ;

/**
 *  Outputs an <tt>CATULONG64</tt>.
 * @param iULONG64
 * The 64-bit unsigned integer to output.
 */
  CATCGMOutput&	operator<<(CATULONG64 iULONG64) ;

#endif

#if defined (PLATEFORME_DS64) && ! (defined (_WINDOWS_SOURCE))
/**
 *  Outputs an <tt>CATINTPTR</tt>.
 * @param iINTPTR
 * The 64-bit signed integer to output.
 */
  CATCGMOutput&	operator<<(CATINTPTR iINTPTR) ;

/**
 *  Outputs an <tt>CATUINTPTR</tt>.
 * @param iUINTPTR
 * The 64-bit unsigned integer to output.
 */
  CATCGMOutput&	operator<<(CATUINTPTR iUINTPTR) ;

#endif

/**
 *  Outputs a CATCGMOutput.
 * @param iOutput
 * The output.
 */
  CATCGMOutput&	operator<<(const CATCGMOutput& iOutput) ;
#ifdef _WINDOWS_SOURCE
  CATCGMOutput&	operator<<(const __SMANIP_int & ) ;
#else
  CATCGMOutput&	operator<<(const smanip_int & ) ;
#endif

/**
 * Flushes <tt>this</tt> CATCGMOutput.
 */
  void flush();
  operator ostream* () const;
  const char* str();

/**
 * Defines the number of decimals.
 * @param iPrecision
 * The number of decimals.
 */
  void precision(int iPrecision);

/**
 * Closes <tt>this</tt> CATCGMOutput.
 */
  void  close();

/**
 *  Retrieves <tt>this</tt>CATCGMOutput (if it is of CATCGMOutput::String type) as a unicode string.
 *  @param ioString
 *  The corresponding unicode string.
 */
  void  Get(CATUnicodeString& ioString);

/**
 *  Retrieves <tt>this</tt>CATCGMOutput (if it is of CATCGMOutput::String type) as a string.
 *  @param ioString
 *  The corresponding string.
 */
  void  Get(CATString& ioString);
  


  /**
  * Define association with modelisation version 
  */
  void SetVersionNumber(CATCGMStreamVersion iVersionOfDump);

  /**
  * Get associated modelisation version (CatCGMStream_UnknownVersion By Default)
  */
  INLINE CATCGMStreamVersion GetVersionNumber() const;
  
  /**
  * Restrictive Dump of Persistent Data is required
  */
  INLINE CATBoolean IsDedicatedToPersistentData() const;

  /**
  * Define Restrictive Dump of Persistent Data is required
  */
  void SetDedicatedToPersistentData(CATBoolean iDedicated);

    
  /**
  * Restrictive Dump of Persistent Data is required
  */
  INLINE CATBoolean IsPartialPersistentData() const;

  /**
  * Define Restrictive Dump of Persistent Data is required
  */
  void SetPartialPersistentData(CATBoolean iPartialPersistentData);


/**
 * Change ostream of  <tt>this</tt> CATCGMOutput.
 */
  void  ChangeOstream(ostream *iNewOutput);

  static void        SetTraceMode(short on_or_off); 
  static void        SetStatusMode(short on_or_off); 
  static const char* PrintLine(const char* filename, int linenumber);
 

  static CATCGMOutput& SetFormat(CATULONG32 );
  CATCGMOutput& SetSetwFormat(int);
  CATCGMOutput& SetSetprecisionFormat(int);
  
  static CATCGMOutput & GetOut();
  static CATCGMOutput & GetErr();
  static CATCGMOutput & GetStatus();
  static CATCGMOutput & GetStat();
  static CATCGMOutput & GetOdt();
  static CATCGMOutput & GetDoc();


private :
  ostream*            _os;
  unsigned short      _format;  
  CATCGMStreamVersion _version;
  unsigned char       _mode;
  CATBoolean          _DedicatedToPersistentData;
  CATBoolean          _PartialPersistentData;

  CATCGMOutput& operator = (const CATCGMOutput&);
  CATCGMOutput(const CATCGMOutput&);
};


#define cgmout     (CATCGMOutput::GetOut())
#define cgmerr     (CATCGMOutput::GetErr())
#define cgmstatus  (CATCGMOutput::GetStatus())
#define cgmstat    (CATCGMOutput::GetStat())  
#define cgmodt     (CATCGMOutput::GetOdt())  
#define cgmdoc     (CATCGMOutput::GetDoc())  

INLINE CATBoolean CATCGMOutput::IsActive() const
{
  return _os ? TRUE : FALSE;
}

INLINE CATCGMOutput::operator ostream* () const
{
  return _os;
}


/**
 * Defines the end of the line.
 */
#define cgmendl "\n"

/**
 * Defines the end of a string.
 */
#define cgmends '\0'

/** @nodoc */
class ExportedByCATMathStream CGMMANIP 
{
public:
	CGMMANIP( int t); 
	ExportedByCATMathStream friend CATCGMOutput& operator<<(CATCGMOutput& s, CGMMANIP & sm);
private:
	int _tp;
};

/** @nodoc */
ExportedByCATMathStream CGMMANIP & cgmsetw(int w);

/** @nodoc */
class ExportedByCATMathStream CGMMANIPRECISION
{
public:
	CGMMANIPRECISION( int t);
    ExportedByCATMathStream friend CATCGMOutput& operator<<(CATCGMOutput& s,CGMMANIPRECISION & sm);
private:
	int _tp;
};

/** @nodoc */
ExportedByCATMathStream CGMMANIPRECISION & cgmsetprecision(int p);

class CATMathPoint;
/**
 * Outputs a CATMathPoint. 
 * @param iStream
 * The input stream.
 * @param iPoint
 * The point to output.
 */
ExportedByCATMathStream CATCGMOutput& operator << (const CATCGMOutput& iStream,const CATMathPoint& iPoint);
class CATMathVector;
/**
 * Outputs a CATMathVector. 
 * @param iStream
 * The input stream.
 * @param iVector
 * The vector to output.
 */
ExportedByCATMathStream CATCGMOutput& operator << (const CATCGMOutput& iStream,const CATMathVector& iVector);
class CATMathVector2D;

/**
 * Outputs a CATMathVector2D.
 * @param iStream
 * The input stream.
 * @param iVector2D
 * The vector to output.
 */
ExportedByCATMathStream CATCGMOutput& operator << (const CATCGMOutput& iStream,const CATMathVector2D& iVector2D);
class CATMathDirBox;
/** @nodoc */
ExportedByCATMathStream CATCGMOutput& operator << (const CATCGMOutput& ,const CATMathDirBox& );
class CATMathBox;

/**
 * Outputs a CATMathBox. 
 * @param iStream
 * The input stream.
 * @param iBox
 * The box to output.
 */
ExportedByCATMathStream CATCGMOutput& operator << (const CATCGMOutput& iStream,const CATMathBox& iBox);
class CATMathBox2D;

/**
 * Outputs a CATMathBox2D. 
 * @param iStream
 * The input stream.
 * @param iBox2D
 * The box to output.
 */
ExportedByCATMathStream CATCGMOutput& operator << (const CATCGMOutput& iStream,const CATMathBox2D& iBox2D);
class CATMathPlane;

/**
 * Outputs a CATMathPlane. 
 * @param iStream
 * The input stream.
 * @param iPlane
 * The planex to output.
 */
ExportedByCATMathStream CATCGMOutput& operator << (const CATCGMOutput& iStream,const CATMathPlane& iPlane);
class CATMathCircleArc2D;

/**
 * Outputs a CATMathCircleArc2D. 
 * @param iStream
 * The input stream.
 * @param iCircleArc2D
 * The circle arc to output.
 */
ExportedByCATMathStream CATCGMOutput& operator << (const CATCGMOutput& iStream,const CATMathCircleArc2D& iCircleArc2D);

#ifdef CATIAR212

/**
 * Outputs a list of <tt>short</tt>s. 
 * @param iStream
 * The input stream.
 * @param iList
 * The list of ints to output.
 */
ExportedByCATMathStream CATCGMOutput& operator<<(const CATCGMOutput& iStream, const CATListValShort& iList);
#endif

/**
 * Outputs a list of <tt>int</tt>s. 
 * @param iStream
 * The input stream.
 * @param iList
 * The list of ints to output.
 */
ExportedByCATMathStream CATCGMOutput& operator << (const CATCGMOutput& iStream,const CATListOfInt& iList);

/**
 * Outputs a list of <tt>float</tt>s. 
 * @param iStream
 * The input stream.
 * @param iList
 * The list of floats to output.
 */
ExportedByCATMathStream CATCGMOutput& operator << (const CATCGMOutput& iStream,const CATListOfFloat& iList);

/**
 * Outputs a list of <tt>double</tt>s. 
 * @param iStream
 * The input stream.
 * @param iList
 * The list of doubles to output.
 */
ExportedByCATMathStream CATCGMOutput& operator << (const CATCGMOutput& iStream,const CATListOfDouble& iList);

/**
 * Outputs a list of <tt>float</tt>s. 
 * @param iStream
 * The input stream.
 * @param iList
 * The list of floats to output.
 */
ExportedByCATMathStream CATCGMOutput& operator << (const CATCGMOutput& iStream,const CATListOfCATString& iList);


/**
* Get associated modelisation version (CatCGMStream_UnknownVersion By Default)
*/
INLINE CATCGMStreamVersion CATCGMOutput::GetVersionNumber() const
{
  return _version;
}

INLINE CATBoolean CATCGMOutput::IsDedicatedToPersistentData() const
{
  return _DedicatedToPersistentData;
}

INLINE CATBoolean CATCGMOutput::IsPartialPersistentData() const
{
  return _PartialPersistentData;
}


#endif
