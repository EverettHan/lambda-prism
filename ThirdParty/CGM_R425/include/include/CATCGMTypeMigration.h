/* -*-c++-*- */
#ifndef CATCGMDeclareTypeMigration_H
#define CATCGMDeclareTypeMigration_H
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATCGMTypeMigration:
// Class representing the s used to manage a type.
///============================================================================
/**
* Type migration for an old type.
* <p>
* Used to provide the required s (constructor, unstreaming, streaming)
* to manage instances from types built with old versions.
*/
//=============================================================================
// May 98   Creation                                         Ph.Baucher (PHB)
//=============================================================================
#include "ExportedByCATCGMFusion.h"               
#include "CATCGMVersionDefinition.h"               
#include "CATCGMNewArray.h"


class ExportedByCATCGMFusion CATCGMTypeMigration
{
public:

   //-----------------------------------------------
    // Constructeur + Surcharge new et delete
    //----------------------------------------------
    CATCGMTypeMigration( short          iTypeCode );
    ~CATCGMTypeMigration();
    CATCGMNewClassArrayDeclare;  

 
   // void                SetUnstreamFct( CATCGMMigrate  iFct );
   // CATCGMMigrate       GetUnstreamFct() const  { return _UnstreamFct ; }
		 void               SetUnstreamFct( CATCGMMigrateUnstream  iFct );
    CATCGMMigrateUnstream       GetUnstreamFct() const  { return _UnstreamFct ; }

    void                SetStreamFct( CATCGMMigrate  iFct );
    CATCGMMigrate       GetStreamFct() const  { return _StreamFct ; }

    void                SetCorrection( CATCGMProcess  iFct );
    CATCGMProcess       GetCorrection() const  { return _CorrectionFct ; }


private:
    ///--------------------------------------------------------------------------
    /**
     *  Copy constructor (forbidden use).
     */
    CATCGMTypeMigration( const CATCGMTypeMigration& );
    CATCGMTypeMigration&    operator=( const CATCGMTypeMigration& );

    short               _TypeCode ;
    //CATCGMMigrate       _UnstreamFct ;
		CATCGMMigrateUnstream       _UnstreamFct ;
    CATCGMMigrate       _StreamFct ;
    CATCGMProcess       _CorrectionFct ;
};



#endif
