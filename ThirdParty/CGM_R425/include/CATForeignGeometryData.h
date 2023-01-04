#ifndef CATForeignGeometryData_H
#define CATForeignGeometryData_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include "YP00IMPL.h"
#include "CATCGMStreamAttribute.h"

class CATCGMOutput;
class CATMathStream;
class CATCloneManager;
class CATTransfoManager;
class CATIForeignSurface;
class CATGeometry;
class CATCX_CHECKUP;
#include "CATMathDef.h"

/**
 * Base class for the definition of foreign data on CGM objects.
 * <br>  If you want 
 * to create a new class of CGM data, you have to derive this class. By the way, you will
 * find two kinds of methods:
 * <ul>
 * <li> Mandatory methods: there is no default implementation, you must re-write them for
 * your own object. 
 * <li> Optional methods: they have a default implementation. You can re-write them to
 * increase the performances or to be more adapted to your own class.
 * </ul>
 * You must provide a default constructor. As in any C++ programmation, 
 * it is also strongly recommended to provide
 * a copy constructor and an assigment operator.
 */
class ExportedByYP00IMPL CATForeignGeometryData : public CATCGMStreamAttribute
{
  /** @nodoc */
  CATCGMDeclareAttribute (CATForeignGeometryData,CATCGMStreamAttribute);

public:
/**
 * Constructs a CATForeignGeometryData.
 */
  CATForeignGeometryData(); 
/**
 * Copy constructor.
 */
   CATForeignGeometryData(const CATForeignGeometryData &iToCopy);
/**
 * Assignement operator.
 */
  CATForeignGeometryData& operator = (const CATForeignGeometryData &iToAssign);
/**
 * Destructor
 */
  virtual ~CATForeignGeometryData();  
   
/** 
 * Constructs a copy of <tt>this</tt> CATForeignGeometryData.
 * <br>Mandatory method.
 * @param iCloning
 * The clone process to be used.
 */
  virtual CATForeignGeometryData* Clone(CATCloneManager& iCloning) const =0;
/**
 * Applies a geometrical transformation to <tt>this</tt> CATForeignGeometryData. 
 * <br>Mandatory method.
 * @param iTransfo
 * The transformation process to be used.
 */
  virtual void           Move3D(CATTransfoManager& iTransfo) =0;

/** 
 * Constructs a geometrically transformed copy of <tt>this</tt> CATForeignGeometryData. 
 * <br>Optional method. By default, copies , then transforms.
 * @param iTransfo
 * The transformation process to be used.
 */
  virtual CATGeometry*   CloneAndMove3D(CATTransfoManager& iTransfo) const ;

/**
 * @nodoc
 * Dumps the general characteristics of <tt>this</tt>.
 * <br>Optional method. Dumps the class name by default.
 * @param iWhereToWrite
 * The stream where to dump.
 */
   virtual void  Dump( CATCGMOutput& iWhereToWrite ) const; 
/**
 * Returns an estimation of the size in byte of <tt>this</tt> CATForeignGeometryData.
 * <br>Optional method. No size by default. 
 * @return
 * The estimated size.
 */
  virtual CATLONG32  GetSize() const;   

/**
 * @nodoc
 * Checks the validity of <tt>this</tt> CATForeignGeometryData.
 * <br>Optional method. No check by default. 
 */
  virtual void CheckUp(CATCX_CHECKUP* report);

/** @nodoc */
  void SetOwningObject(CATGeometry* );

  protected :

/**
 * Returns the value to be used to define an infinite line.
 * @return
 * The value of the infinite.
 */
  double GetInfinite() const;

/**
 * Returns a pointer to the CATGeometry object that owns <tt>this</tt> data.
 * @return
 * The CATForeignCurve or CATForeignSurface that have <tt>this</tt> data.
 */
  CATGeometry* GetInterface() const ;  
  
  private :
  
  CATGeometry* _OwningObject;
//=============================================================================
  
};

#endif

