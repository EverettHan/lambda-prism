#ifndef CATCGMItfDestrBehavior_h
#define CATCGMItfDestrBehavior_h

/**
 * CGM interface destructor behavior.
 * @param CATCGMDontDeleteWithItf
 *   When the interface is deleted, its handled object is not deleted.
 * @param CATCGMDeleteObjWithItf
 *   When the interface is deleted, its handled object is deleted.
 */
enum CATCGMItfDestrBehavior
{
  CATCGMDontDeleteWithItf,
  CATCGMDeleteObjWithItf
};

#endif
