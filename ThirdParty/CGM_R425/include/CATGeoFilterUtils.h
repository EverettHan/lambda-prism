#ifndef CAT_GEO_FILTER_UTILS_H
#define CAT_GEO_FILTER_UTILS_H

#include <CATBoolean.h>
#include "YP00IMPL.h"

class CATGeometry;
class CATSoftwareConfiguration;

class ExportedByYP00IMPL CATGeoFilterUtils
{
public:
  /* Tests if 2 geometries possibly intersect.
   * @return TRUE if an intersection is possible, FALSE if it is ruled out. */
  static CATBoolean IsIntersectionPossible(CATSoftwareConfiguration * iConfig, const CATGeometry *, const CATGeometry *);

  /* Tests if 2 geometries possibly intersect if each is inflated by iOffset
   * (... well, all the bounding volumes considered will be inflated by iOffset)
   * @param onlyUseCacheableData If set to true (default), only use cacheable data
   *                             to check if intersection is possible. If set to
   *                             false, compute data that cannot be cached. This
   *                             is likely to be more precise but slower.
   * @return TRUE if an intersection is possible, FALSE if it is ruled out. */
  static CATBoolean IsIntersectionPossible(CATSoftwareConfiguration * iConfig, const CATGeometry *, const CATGeometry *, double iOffset, CATBoolean onlyUseCacheableData=TRUE);

  /* Returns a minorant (or lower bound) to the distance between two geometries
   * @param agressive Use a slightly better but more time consuming strategy if true
   * @param onlyUseCacheableData If set to true (default), only use cacheable data
   *                             to check if intersection is possible. If set to
   *                             false, compute data that cannot be cached. This
   *                             is likely to be more precise but slower.
   * @return distance minorant (>=0). */
   static double SquareDistanceMinorant(const CATGeometry *, const CATGeometry *, CATBoolean agressive=FALSE, CATBoolean onlyUseCacheableData=TRUE);

private:
  CATGeoFilterUtils();
};

#endif
