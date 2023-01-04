#ifndef CATCGMDiagnosis_H
#define CATCGMDiagnosis_H

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CATGMModelInterfaces.h"

#include "CATInputError.h"
#include "ListPOfCATBody.h"
#include "CATBoolean.h"
#include "CATCGMNewArray.h"
#include "CATCGMInputError.h"


/**
 * Class for the management of the diagnosis raised during a topological operation.
 * A diagnosis is an error that also retrieves two lists of body pointers: 
 * <ul>
 * <li>The list of the pointers to the created bodies defining the topological location of the error
 * <li>The list of the pointers to the created bodies defining the topological neighborhood of the error.
 * </ul>
 * The bodies must be removed from the factory after use. Only valid bodies are pointed to. 
 * If the method <tt>GetLocation</tt> is not called, the bodies are deleted at the CATCGMDiagnosis deletion.
 */
class ExportedByCATGMModelInterfaces CATCGMDiagnosis: public CATCGMInputError 
{
  public:
   

    /**
     * Tests whether <tt>this</tt> diagnosis references bodies.
     * @param ioYesOrNo
     * The result of the test.
     * <br><b>Legal values</b>: <tt>TRUE</tt> if empty, <tt>FALSE</tt> if there is at least one body referenced. 
     */
    void IsEmpty (CATBoolean & ioYesOrNo);

    /**
     * Declares that the class CATCGMDiagnosis is an error class which derives
     * from CATTopOpInError.
     */
    CATDeclareError(CATCGMDiagnosis, CATCGMInputError)
    virtual ~CATCGMDiagnosis();

    /**
     * Retrieves the topological location of <tt>this</tt> error.
     * @param ioLocationList
     * The list of the pointers to the bodies defining the location of the error. Once read,
     * the bodies of the list must be managed by the caller. 
     * In particular, they must be removed (@href CATICGMContainer#Remove ) after use by the caller.
     * However, if the method <tt>GetLocation</tt> is not called, 
     * the <tt>CATCGMDiagnosis</tt> destructor removes them.
     * @param ioContextList
     * The list of the pointers to the bodies defining the topological neighborhood of the error. Once read,
     * the bodies of the list must be managed by the caller. 
     * In particular, they must be removed (@href CATICGMContainer#Remove ) after use by the caller.
     * However, if the method <tt>GetLocation</tt> is not called, 
     * the <tt>CATCGMDiagnosis</tt> destructor removes them.
     * @param iReadOnly
     * Dedicated to the case where you just want to read.
     * <br><b>Legal values</b>:
     * <tt>FALSE</tt> if the bodies of the list must be managed by the caller (default mode),
     * <tt>TRUE</tt> otherwise.
     */
    void GetLocation (CATLISTP(CATBody) & ioLocationList,
                      CATLISTP(CATBody) & ioContextList,
                      const CATBoolean iReadOnly = FALSE);

    /**
     * Retrieves the topological location of <tt>this</tt> error.
     * @param ioLocationList
     * The list of the pointers to the bodies defining the location of the error. Once read,
     * the bodies of the list must be managed by the caller. 
     * In particular, they must be removed (@href CATICGMContainer#Remove ) after use by the caller.
     * However, if the method <tt>GetLocation</tt> is not called, 
     * the <tt>CATCGMDiagnosis</tt> destructor removes them.
     * @param ioInputList
     * The list of the input bodies containing the cells of the location bodies, if it was specified.
     * If input list was specified during diagnosis creation, it has the same size as <tt>ioLocationList</tt>.
     * The n-th body of <tt>ioLocationList</tt> is associated to the n-th body of <tt>ioInputList</tt>.
     * If the input list was not specified, this list is empty.
     * @param ioContextList
     * The list of the pointers to the bodies defining the topological neighborhood of the error. Once read,
     * the bodies of the list must be managed by the caller. 
     * In particular, they must be removed (@href CATICGMContainer#Remove ) after use by the caller.
     * However, if the method <tt>GetLocation</tt> is not called, 
     * the <tt>CATCGMDiagnosis</tt> destructor removes them.
     * @param iReadOnly
     * Dedicated to the case where you just want to read.
     * <br><b>Legal values</b>:
     * <tt>FALSE</tt> if the bodies of the list must be managed by the caller (default mode),
     * <tt>TRUE</tt> otherwise.
     */
    void GetLocationWithInputBodies (CATLISTP(CATBody) & ioLocationList,
                                     CATLISTP(CATBody) & ioInputList,
                                     CATLISTP(CATBody) & ioContextList,
                                     const CATBoolean iReadOnly = FALSE);

    /**
     * Sets the topological location of <tt>this</tt> error.
     * @param iLocationList
     * The list of the pointers to the bodies defining the location of the error. To be called inside
     * an operator as an help for the caller.
     * @param iContextList
     * The list of the pointers to the bodies defining the topological neighborhood of the error. 
     * To be called inside an operator as an help for the caller.
     * @param iAppendOnly
     * Dedicated to the case where previous lists of pointers to the bodies were not empty.
     * <br><b>Legal values</b>:
     * <tt>FALSE</tt> if the previous lists of pointers to the bodies are forgotten,
     * <tt>TRUE</tt> if the previous lists of pointers to the bodies are kept.
     */
    void SetLocation (const CATLISTP(CATBody) & iLocationList,
                      const CATLISTP(CATBody) & iContextList,
                      const CATBoolean          iAppendOnly = FALSE);

    /**
     * Sets the topological location of <tt>this</tt> error.
     * @param iLocationList
     * The list of the pointers to the bodies defining the location of the error. To be called inside
     * an operator as an help for the caller.
     * @param iInputList
     * The list of the pointers to the input bodies containing the cells of the location bodies. To be called inside
     * an operator as an help for the caller. This list and <tt>iLocationList</tt> should have the same size.
     * @param iContextList
     * The list of the pointers to the bodies defining the topological neighborhood of the error. 
     * To be called inside an operator as an help for the caller.
     * @param iAppendOnly
     * Dedicated to the case where previous lists of pointers to the bodies were not empty.
     * <br><b>Legal values</b>:
     * <tt>FALSE</tt> if the previous lists of pointers to the bodies are forgotten,
     * <tt>TRUE</tt> if the previous lists of pointers to the bodies are kept.
     */
    void SetLocationWithInputBodies (const CATLISTP(CATBody) & iLocationList,
                                     const CATLISTP(CATBody) & iInputList,
                                     const CATLISTP(CATBody) & iContextList,
                                     const CATBoolean          iAppendOnly = FALSE);

    /**
     * Defines the list types.
     * @param NoList
     * The body is not referenced in any list
     * @param LocationList
     * The body is referenced in the location list
     * @param ContextList
     * The body is referenced in the context list
     */
    enum CATListType { NoList, LocationList, ContextList };
    
    /**
     * Tests whether a body is referenced inside one of the lists of <tt>this</tt> diagnosis.
     * @param iBodyTest
     * The pointer to the body to test.
     * @param ioListType
     * The list inside which the body is referenced.
     */
    void Contains (CATBody* iBodyToTest, CATCGMDiagnosis::CATListType & ioListType);

    
    /** @nodoc */
    CATCGMDiagnosis (const CATCGMDiagnosis & iError);

    /** @nodoc */
    CATCGMDiagnosis& operator=(const CATCGMDiagnosis&);


    /** @nodoc */
    CATCGMNewClassArrayDeclare; 

  private:
    void Init();
    CATLISTP(CATBody) _LocationList;
    CATLISTP(CATBody) _ContextList;
    CATLISTP(CATBody) _InputList;
    CATBoolean        _IsRead;
  
};

#endif
