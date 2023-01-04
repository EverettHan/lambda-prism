/* -*-c++-*- */
#ifndef CATCXduplicate_h
#define CATCXduplicate_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2001
//-----------------------------------------------------------------------------
// Definition des signatures de methodes requises opur la SmartDuplication
// Oct 2001      TCX pour archi rapide et exposition externe vivicite geometrique
//-----------------------------------------------------------------------------

class CATCXTopology;
class CATCXBody;
class CATCXSmartBodyDuplicator;
class CATCXduplicateManager;


#define CATCXduplicateForCATCXTopology \
    virtual CATCXTopology *duplicate( CATCXBody * iNewBody , CATCXSmartBodyDuplicator* Dupl, CATCXduplicateManager*Mngt)

#define CATCXduplicateForCATSubdOccurence \
   virtual CATSubdOccurence *duplicate( CATCXBody * iNewBody , CATCXSmartBodyDuplicator* Dupl, CATCXduplicateManager*Mngt)

#endif
