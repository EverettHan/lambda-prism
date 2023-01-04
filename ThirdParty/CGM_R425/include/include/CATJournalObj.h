#ifndef _CATJOURNALOBJ_H
#define _CATJOURNALOBJ_H

// COPYRIGHT DASSAULT SYSTEMES 1999

class CATCGMJournalObj;
class CATGeometry;
class CATBaseUnknown;
#include "CATListOfCATGeometries.h"
#include "YP0LOGRP.h"

/* get the history from an object. If there is no history then NULL */
ExportedByYP0LOGRP const CATCGMJournalObj * GetJournalObj(CATGeometry *obj );

/* get the history of an object. If there is no history then the method creates one */
/* and get it*/
ExportedByYP0LOGRP CATCGMJournalObj * GiveJournalObj(CATGeometry *obj );

/* set a history to an object. return is 0 so no error else */
/* the history can't be associated to the object */
ExportedByYP0LOGRP int SetJournalObj
(const CATCGMJournalObj * attr,CATGeometry *obj );

/* Give the object list whith the same history as the entry history */
/* a partir d'une etiquette */
ExportedByYP0LOGRP CATLISTP(CATGeometry) GetObjectFromEtiquette(CATCGMJournalObj * history,const  CATBaseUnknown * container/* body ou factory*/,int  dimension=0);

#endif
