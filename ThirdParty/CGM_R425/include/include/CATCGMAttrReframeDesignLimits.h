#ifndef CATCGMAttrReframeDesignLimits_h_
#define CATCGMAttrReframeDesignLimits_h_

#include "CATCGMAttribute.h"
#include "CATCGMNewArray.h"
#include "YP0LOGRP.h"

class CATCGMObject;
class CATICGMObject;
class CATCGMContainer;

//  attribut pour stocker le lien inverse CATCGMObject -> ReframeDesignLimits

//---------------------------------------------------------------------------------
class ExportedByYP0LOGRP CATCGMAttrReframeDesignLimits : public CATCGMAttribute
{
public:
  CATCGMDeclareAttribute (CATCGMAttrReframeDesignLimits, CATCGMAttribute);
  CATCGMNewClassArrayDeclare; 

  static CATCGMAttrReframeDesignLimits * CreateReframeLink(CATCGMObject *iobj,void *iptr,CATCGMAttrReframeDesignLimits*iFirst=NULL);
  static CATCGMAttrReframeDesignLimits * GetReframeLink   (CATCGMObject *iobj);
  
  static void   DeleteReframeLink(CATCGMObject  *iobj);
  static void   DeleteReframeLink(CATICGMObject *itf);
  
  static void   DeleteReframeLink(CATCGMAttrReframeDesignLimits *iptr);
  static void * ReadReframeAssoc (CATCGMObject  *iobj);
  
  static void   FlushReframeLinks(CATCGMAttrReframeDesignLimits * iattr); 
  
  INLINE CATCGMObject                  * GetReframeOwner ();
  INLINE void                          * GetReframeAssoc ();
  INLINE CATCGMAttrReframeDesignLimits * GetPrevReframeLink ();
  INLINE CATCGMAttrReframeDesignLimits * GetNextReframeLink ();
  
  void InsertInChain(CATCGMAttrReframeDesignLimits * iattr);
protected:
  virtual ~CATCGMAttrReframeDesignLimits ();

private :
  CATCGMAttrReframeDesignLimits ( );
  CATCGMAttrReframeDesignLimits (CATCGMObject *iobj, void *iptr);
  CATCGMAttrReframeDesignLimits (const CATCGMAttrReframeDesignLimits & );//Necessary to prevent unwanted automatic creation by compiler
  void operator = (const CATCGMAttrReframeDesignLimits &);
  
  void RemoveFromChain();
//---------------------------------------------------------------------------------
private:
  CATCGMObject * _obj;
  void         * _assoc_ptr;
  CATCGMAttrReframeDesignLimits * _prev_Attr;
  CATCGMAttrReframeDesignLimits * _next_Attr;
};
//---------------------------------------------------------------------------------
INLINE CATCGMObject                  * CATCGMAttrReframeDesignLimits::GetReframeOwner()    {return _obj      ;}
INLINE void                          * CATCGMAttrReframeDesignLimits::GetReframeAssoc()    {return _assoc_ptr;}
INLINE CATCGMAttrReframeDesignLimits * CATCGMAttrReframeDesignLimits::GetNextReframeLink() {return _next_Attr==this ? NULL :_next_Attr ;}
INLINE CATCGMAttrReframeDesignLimits * CATCGMAttrReframeDesignLimits::GetPrevReframeLink() {return _prev_Attr==this ? NULL :_prev_Attr ;}
//---------------------------------------------------------------------------------
#endif
