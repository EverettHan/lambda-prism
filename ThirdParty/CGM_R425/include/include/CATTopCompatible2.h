/**
 * @COPYRIGHT DASSAULT SYSTEMES 2007
 */

/* -*-C++-*- */

#ifndef __CATTopCompatible2_H__
#define __CATTopCompatible2_H__

// COPYRIGHT DASSAULT SYSTEMES 2022

//===========================================================================
// Operator for compatible boolean union of two bodies.
//===========================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATTopMultiResultStreamed.h"

class CATGeoFactory;
class CATTopData;
class CATBody;
class CATTopCompatibleCGM;

/**
 * Class representing the topological operator which performs a compatible Boolean union of bodies.
 * <ul>
 * <li>Create it with the <tt>CATCreateTopCompatibleForCGM</tt> or <tt>CATCreateTopCompatibleForCVM</tt> global function.
 * <li>Run it ( only one time ).
 * <li>Get the resulting body with the <tt>GetResult</tt> method. 
 * If you do not want to keep this resulting body, 
 * use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory, after the operator deletion.
 * <li>Delete it after use with the usual C++ delete operator. 
 * </ul>
*/
class ExportedByCATTopologicalObjects CATTopCompatible2: public CATTopMultiResultStreamed
{
  CATCGMVirtualDeclareClass(CATTopCompatible2);
protected:

  /**
  * @nodoc
  * Constructor. Do not use. Use <tt>CATCreateTopCompatibleForCGM</tt>  or <tt>CATCreateTopCompatibleForCVM</tt> to create a
  * <tt>CATTopCompatible</tt>.
  */
  CATTopCompatible2(CATGeoFactory * iFactory, 
									 CATTopData    * iTopData,
                   CATTopCompatibleCGM * iExtensible);

public:
  /**
  * Destructor.
  */
  virtual ~CATTopCompatible2();

  /**
   * Activates suppress mode : in the case of a failure to integrate a body,
   * the operation continues with the remaining bodies. Any bodies which were
   * not integrated on the first pass get integrated together (where possible)
   * The results are returned as multiple bodies, with their own journals.
   * <br> This option is not activated by default. If activated, NonManifold
   * results <b>must</b> be authorised.
   * @param yes_or_no
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> Throw an error if a compatible operation fails.
   *     <dt><tt>1</tt><dd> Continue on error, and return multiple bodies</dl>
   */
  virtual void SetSuppressMode(int iSuppressMode = 1) = 0;

  /**
  * Returns the suppress mode.
  * @return
  * <br><b>Legal values</b>:
  * <dl><dt><tt>0</tt><dd> suppress mode not active.
  *     <dt><tt>1</tt><dd> suppress mode is active.</dl>
  */
  virtual int  GetSuppressMode() const = 0;
  
  /**
  * @nodoc
  * Activate or deactivate  the imprint follow up mode.
  */
  virtual void SetImprintFollowUpMode(CATBoolean iImprintFollowUpMode)=0;

  /**
  * @nodoc
  * Check if the imprint follow up mode is active or not.
  */
  virtual CATBoolean GetImprintFollowUpMode() const=0;

  /**
  * @nodoc
  * Activate or deactivate the volume journal mode.
  */
  virtual void SetVolumeJournalMode(CATBoolean iVolumeJournalMode)=0;

  /**
  * @nodoc
  * Check if the volume journal mode is active or not.
  */
  virtual CATBoolean GetVolumeJournalMode() const=0;

  /**
  * @nodoc
  * For stream of compatible operators in CGMReplays :
  * declares that we want the stream of outputs to use the recent intermediate class
  * CATTopMultiResultStreamed.
  */
  virtual void SetUseCATTopMultiResultStreamedForOutputs(CATBoolean iUseMultiResStream);
  virtual CATBoolean GetUseCATTopMultiResultStreamedForOutputs();
  virtual CATBoolean ValidateVolumeJournal(CATCGMOutput& os);
protected:
  CATTopCompatibleCGM* GetTopCompatibleExtensible()  const;

  void               RequireDefinitionOfInputAndOutputObjects();
  void               WriteInput(CATCGMStream& ioStream);

  void               WriteTopOutput(CATCGMStream& Str);

  void               Dump(CATCGMOutput& os);

  void               DumpOutput(CATCGMOutput& os);

  void               DumpOutput(CATCGMStream& Str,
    CATCGMOutput& os, int VersionNumber = 1);

  CATBoolean         ValidateTopOutput(CATTopCheckJournal* iEquivalent, CATCGMOutput& os);
  CATBoolean         ValidateTopOutput_Old(CATTopCheckJournal* iEquivalent, CATCGMOutput& os);

  CATTopCheckJournal* ReadTopOutput(CATCGMStream& Str);

  CATBoolean         ReadReferenceOutput(CATCGMStream& Str);

private:
  CATLONG32           _nbReferenceBodies;
  CATICGMObject** _ReferenceBodies;           // Expected resulting bodies.
  CATBoolean          _UseTopMultiResultStreamed_ForOutputs;

};

#endif
