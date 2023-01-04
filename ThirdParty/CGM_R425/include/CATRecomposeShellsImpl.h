#ifndef __CATRecomposeShellsPro_h__
#define __CATRecomposeShellsPro_h__

#include "CATRecomposeShells.h"

//=============================================================================
// Creation YL3   02 2011
//
// Protected Interface de l'Operator RecomposeShell pour CGMReplay 
//
// Modification DPS Oct.2016
//    Exact/Poly Management possible thanks to a new dedicated extension CATExtRecomposeShells
//    Add RunExactOperator, RunPolyOperator & RunGenericOperator
//
//=============================================================================

class CATCGMOutput;

class CATRecomposeShellsImpl : public CATRecomposeShells
{

public: 

  //============================
  // Constucteur et destructeurs
  //============================

  CATRecomposeShellsImpl(CATGeoFactory * iFactory,
                         CATTopData    * iData,
                         CATBody       * iBodyToRecompose);
  virtual ~CATRecomposeShellsImpl();

	static const  CATString  *GetDefaultOperatorId();
  int RunOperator();

protected :

  /** Exact - Poly Management*/
  /** @nodoc @nocgmitf */
  virtual int RunExactOperator();
  /** @nodoc @nocgmitf */
  virtual int RunPolyOperator();
  /** @nodoc @nocgmitf */
  int RunGenericOperator();

  /** @nodoc @nocgmitf : CATCGMReplay  / Dump de la definition de l'operateur et son status actuel (Config,Input) + affinite */
  virtual void Dump( CATCGMOutput& os );

  const  CATString  *GetOperatorId();
  void RequireDefinitionOfInputAndOutputObjects();
  CATExtCGMReplay*  IsRecordable(short &LevelOfRuntime, short &VersionOfStream);
  void WriteInput(CATCGMStream &ioStream);

  static  CATString  _OperatorId;

};

#endif 


