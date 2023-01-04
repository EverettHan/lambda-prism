#ifndef CATFace_H
#define CATFace_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATGMModelInterfaces.h"
#include "CATCell.h"

class CATDomain;
class CATSurface;
class CATBoundaryIterator;
class CATBoundedCellsIterator;
class CATSurLimits;
class CATSurParam;
class CATMathBox;
class CATMathVector;
class CATShell;
class CATCGMJournalList;

#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATFace ;
#else
extern "C" const IID IID_CATFace ;
#endif

/**
 * Interface representing a topological face.
 * <br>A face is a topological cell which geometry 
 * is a surface. A face is bounded by edges (these edges are put together in
 * loops) and immersed vertices (a vertex immersed in a face must be put in a 
 * CATVertexInFace domain).
 * A CATFace is oriented with regards to its
 * underlying geometry:
 * <dl><dt><tt>CATOrientationNegative</tt><dd> the cell orientation is reversed
 * with regards to the standard orientation.
 *     <dt><tt>CATOrientationPositive</tt><dd> the cell orientation is the 
 * standard orientation.
 *     <dt><tt>CATOrientationUnknown</tt><dd> the cell orientation is not
 * defined.</dl>
 * <br>A CATFace is created with the @href CATBody#CreateCell or @href CATBody#CreateFace methods and
 * deleted with the @href CATICGMContainer#Remove method.
 */ 
class ExportedByCATGMModelInterfaces CATFace : public CATCell
{

  CATDeclareInterface;

  public :

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Sets the geometric surface of <tt>this</tt> CATFace.
 * @param iSurface
 * The pointer to the geometry of the face.
 * @param iOrientation
 * The relative orientation of <tt>this</tt> with regards to its geometry.
 */
  virtual void SetSurface( CATSurface * iSurface,
			 CATOrientation iOrientation=CATOrientationPositive)=0;

/**
 * Returns the geometric surface of <tt>this</tt> CATFace.
 * @param ioOrientation
 * The relative orientation of <tt>this</tt> with regards to its geometry. If <tt>NULL</tt>, this
 * argument is not filled out.
 * @return
 * The pointer to the geometry of <tt>this</tt> CATFace. 
 */
  virtual CATSurface * GetSurface(CATOrientation * ioOrientation=NULL)=0;

/**
 * Returns the 3D bounding box of <tt>this</tt> CATFace. 
 * @return
 * The 3D bounding box.
 */
  virtual const CATMathBox * Get3DBoundingBox()=0;

/**
 * Returns the 2D bounding box of <tt>this</tt> CATFace on its surface. 
 * @return
 * The 2D bounding box.
 */
  virtual const CATSurLimits * Get2DBoundingBox()=0;

/**
 * Retrieves a point belonging to <tt>this</tt> CATFace.
 * @param oCenterParam
 * The estimated center of <tt>this</tt> CATFace.
 */
  virtual void EstimateCenterParam(CATSurParam& oCenterParam) const = 0;

/**
 * Computes the normal vector on <tt>this</tt> CATFace at a given point.
 *<br> This takes into account the face orientation versus its surface. 
 * @param iSurParam
 * The point where to compute the normal.
 * This does not check if <tt>iSurParam</tt> is inside the face.
 * @param ioNormal
 * The computed normal
 * @param iNormalization
 * The mode of normalization.
 * <br><b>Legal values</b>:
 * <dl><dt><tt> TRUE </tt></dt><dd>if <tt>ioNormal</tt> must be  normalized.
 *     <dt><tt> FALSE </tt></dt><dd> otherwise.</dl> 
 * @return
 * The diagnosis of the evaluation.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>TRUE</tt></td><dd>if <tt>ioNormal</tt> is not null
 *     <dt><tt>FALSE</tt></td><dd>otherwise.</dl>
 */
  virtual CATBoolean  EvalNormal(CATSurParam&   iSurParam,
				   CATMathVector& ioNormal, CATBoolean     iNormalization=TRUE)=0;


 /**
 * @nodoc
 * @deprecated V5R14 @href CATDynMassProperties3D#GetWetArea
 */
  virtual double CalcArea() = 0;

  

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

 /** @nodoc */ 
  virtual CATFace* SmartDuplication(CATBody* iBody, CATShell* iOldShell, CATShell* iShell, CATCGMJournalList* iJournal=NULL) = 0;

 /** @nodoc */ 
	virtual CATFace* SmartDuplicationReplace(CATBody* iBody, CATShell* iShell, CATCGMJournalList* iJournal=NULL) = 0;
};

CATDeclareHandler(CATFace,CATCell);

#endif // CATFace_H
