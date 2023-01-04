// COPYRIGHT DASSAULT SYSTEMES 2009

#ifndef CATMathAdvancedBox_H
#define CATMathAdvancedBox_H

#include <CATMathematics.h>
#include <CATBoolean.h>
#include "CATMathAdvancedBoxType.h"
#include "CATMathInline.h"

class CATMathBox;
class CATMathPoint;

/**
 * Virtual advanced box
 * Implementations of this class are mainly used as bounding boxes.
 */

class ExportedByCATMathematics CATMathAdvancedBox
{
public:

	INLINE virtual ~CATMathAdvancedBox() {};

  /**
   * @return The box type as defined in CATMathAdvancedBoxTypeEnum.h
   */
  virtual CATMathAdvancedBoxType GetType() const = 0;

  /**
   * Inflate the box (absolute value)
   */
  virtual void Inflate(double) = 0;

  /**
   * Duplicate the box
   */
  virtual CATMathAdvancedBox *Duplicate() const = 0;
};

#endif
