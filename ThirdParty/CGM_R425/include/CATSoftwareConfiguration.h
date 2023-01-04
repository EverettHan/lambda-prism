#ifndef CATSoftwareConfiguration_h
#define CATSoftwareConfiguration_h
// COPYRIGHT DASSAULT SYSTEMES 1999
/**
* @CAA2Level L1
* @CAA2Usage U1
*/ 
#include "ExportedByCATMathStream.h"
#include "CATBaseUnknown.h"
#include "CATCGMNewArray.h"
#include "CATBoolean.h"

class CATSoftwareModification;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATMathStream;

//* <br>Example of use with a configuration stored on a feature.
//*  <pre> xxxxxxxx::Build() 
//*{
//*....
//*    CATSoftwareConfiguration* config = NULL;
//*    int toStore = 0;
//*....
//*    if (!attrib)
//*    {
//*        // old feature
//*        // creates a void closed configuration
//*        config = new CATSoftwareConfiguration(NULL,0);
//*    }
//*    else
//*    {
//*        if (attrib value)
//*        {
//*           // Update of the feature
//*           // creates a void closed configuration from the attribute
//*            config = new CATSoftwareConfiguration(Buffer,sizeof(Buffer));
//*            if (!config->IsSupported)
//*                ERROR
//*        }
//*        else
//*        {
//*            // Creates the feature
//*            // creates an open configuration
//*            config = new CATSoftwareConfiguration();
//*            toStore = 1;
//*        }
//*   }
//*....
//*    CATTopData* iTopData = new CATTopData(config,journal); 
//*    CATxxxOperator* TopOp = CATCreatexxxOperator(iFactory,iTopData,.....); 
//*    TopOp->Run();
//*    TopOp->GetResult();
//*    ....
//*    if (1==toStore )
//*    {
//*        // writes the attribute in the feature.
//*    }
//*....
//*}
//*</pre>           

/**
* Class defining the software configuration to be used to run a topological operator.
* <br>
* A configuration is a set of code modifications and a level on which the code must be run. 
* The protocol offered by the configuration management allows the code of an operator to be enhanced or
* modified with guaranteing the upwards compatibility of the customer data. 
* <br>The configuration can be stored with the customer data, and the stored configuration can be used
* to specify the code to run.
*/

class ExportedByCATMathStream CATSoftwareConfiguration
{
public :
	
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

   /**
    * Constructs a closed configuration.
	* <br>To use if the input of the algorithm has been previously stored. 
	* @param iStreamBuffer
	* The pointer to the stream.
	* @param iLength
	* The length of the stream.
	* @param iConvert
	* Internal use. Use the <tt>0</tt> default value.
	*/
	CATSoftwareConfiguration(const char* iStreamBuffer, int iLength, int iConvert=0); 
	
	/**
	* Constructs an open configuration.
	* <br>To use for running with the current configuration.  
	*/
	CATSoftwareConfiguration();

	/**
	* Creates the stream representing <tt>this</tt> configuration.
	* @param oStreamBuffer
	* The pointer to the created stream.
	* @param oLength
	* The length to the created stream.
	* @param iConvert
	* Internal use. Use the <tt>0</tt> default value.
	*/
	void Stream(char* &oStreamBuffer, int &oLength, int iConvert=0);
	
	/**
	* Tests whether <tt>this</tt> configuration is supported for the current software.
	* @return
	* The result of the test.
	* <br><b>Legal values</b>: 
	* <dl><dt><tt>1</tt></dt><dd> The configuration is valid 
	* <dt><tt>0</tt></dt><dd> The configuration is not valid:
	* <ul>
	* <li>The modification is known, but the level is not supported
	* <li>The modification is unknown
	*</ul>
	* </dl>
	*/
	int IsSupported() const; 

	/**
	* Increments the reference count for the given interface. 
	* @return The reference count value.
	* <br>This information is meant to be used for diagnostic/testing purposes only, because, in certain situations, the value may be unstable.
	*/
	virtual int AddRef();

	/**
	* Decrements the reference count for the given interface. 
	* @return The reference count value.
	* <br>This information is meant to be used for diagnostic/testing purposes only, because, in certain situations, the value may be unstable.
	*/
	virtual int Release();


  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	/** @nodoc */
	CATCGMNewClassArrayDeclare;

	/**
	* Returns the level of a modification of <tt>this</tt> configuration.
	* @param iModifIID
	* The  given (code) modification identified by IID.
	* @param ioLevel
	* The level of a modification.
	* @return
 	* Determines if the modification has been found.
  * <br><b>Legal values</b>:
  * <tt>1</tt> if <tt>iModifIID</tt> found on <tt>this</tt>, <tt>0</tt> otherwise.<br>
	*/
   CATBoolean GetLevelFromIID(const IID &iModifIID, short & ioLevel) const; 
	
	/**
	* Adds a modification to a configuration. 
	* @param iModification
	* The  given (code) modification identified by its IID and its code level.
	*/
	void AddModification(const CATSoftwareModification &iModification);  

	/**
	* @nodoc
	* Force a modification in the configuration. 
	*/
	void ForceModification(const CATSoftwareModification &iModification);  
	
	/**
	* Returns the level of a modification of <tt>this</tt> configuration.
	* @param iModification
	* The given (code) modification 
	* @return
	* The version (or level) of the modification. If the configuration is "open", the version is the
	* current level of the software. If the configuration is "closed" and not known, the version is <tt>0</tt>.
	*/
   short GetModificationLevel(const CATSoftwareModification &iModification) const; 
	
	/**
	* @nodoc
	* Returns the count of modifications. For the tests.
	*/
	int GetModificationNb() const;
		
	/**
	* Dumps the content of the config. ONLY FOR INTERNAL USE
	*/
	void Dump(ostream & os);

	/**
	* @nodoc
	* Traces Management.
	*/
   short CATCGMVersionningTraces() const;
		
	/**
	* @nodoc
	* Checks Management.
	*/
   short CATCGMVersionningCheck() const;
		
	/**
	* @nodoc
	* Check the level of a modification of <tt>this</tt> configuration.
	*/
   short CheckModificationLevel(const CATSoftwareModification &iModification) const; 
	
	/**
	* @nodoc
	* Returns the count of occurences. For the tests.
	*/
	int GetNbOccurences() const;
	
	/**
	* @nodoc
	* Returns the occurence Number. For the tests.
	*/
   int GetOccurenceNumber() const;
	
   /** 
   * @nodoc 
   * Copy constructor.
   */  
	CATSoftwareConfiguration(const CATSoftwareConfiguration& ToCopy);

   /** 
   * @nodoc 
   * Assignment operator.
   */  
   CATSoftwareConfiguration& operator = (const CATSoftwareConfiguration&);
	

protected:
	/**
	* @nodoc
	* Will be move in Protected as soon as possible -> Use Release Mechanism instead.
	*/
	virtual ~CATSoftwareConfiguration();
	
	
private:
   
  friend class CATMathStreamImpl;

  class ModificationData 
  {
  public :
    IID    _ModificationId;
    short  _ModificationLevel;
  };
  
  static int _NbCreatedOccurences;        // Count of CATSoftwareConfiguration Occurences
  int _OccurenceNumber;                   // Occurence Number
  int _ReferenceCounter;                  // Reference Count
  int _IsOpen;                            // Open or closed configuration
  
  /**
	* @nodoc
	*/
  void RequireNbModifData( int NewNumberOfModifData );
  /**
	* @nodoc
	*/
  void PushModifData( int index, const IID &iModificationId, const short iLevel );

	int _NbModifications;                   // Count of modifications
	int _MaxModifications;                  // Maximum Size of ModificationData[]
	ModificationData* _ModificationArray;   // Pointer to the list of modifications
	ModificationData  _StaticModifArray[3];   // Performane modifications
};

/**
 * Constructs a closed configuration.
 * <br>To use if the input of the algorithm has been previously stored. 
 * @param iStreamBuffer
 * The pointer to the stream.
 * @param iLength
 * The length of the stream.
 * @param iConvert
 * Internal use. Use the <tt>0</tt> default value.
 * @return [out, CATSoftwareConfiguration#Release]
 */
ExportedByCATMathStream CATSoftwareConfiguration *CATCreateSoftwareConfiguration(const char* iStreamBuffer, int iLength, int iConvert=0); 

/**
 * Constructs an open configuration.
 * <br>To use for running with the current configuration.  
 * @return [out, CATSoftwareConfiguration#Release]
 */
ExportedByCATMathStream CATSoftwareConfiguration *CATCreateSoftwareConfiguration();

#endif
