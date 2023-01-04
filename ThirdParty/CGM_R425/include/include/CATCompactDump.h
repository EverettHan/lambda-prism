#ifdef _Coverage_GOO
#ifndef CATCompactDump_H
#define CATCompactDump_H
//
// COPYRIGHT DASSAULT SYSTEMES 2004
//
//===================================================================
// May 2004 - CCK - Creation
//===================================================================
//
#include "CompactFunction.h"

#include "CATCompactFunctionImp.h"

#include "CATListOfDouble.h"
#include "CATCGMOutput.h"

class ExportedByCompactFunction CATCompactDump 
{
 public:
	//
	CATCompactDump(CATCompactFunctionImp* iTreeX,
                 CATCompactFunctionImp* iTreeY,
                 CATCompactFunctionImp* iTreeZ,
                 CATCGMOutput& os);
	//
	//
	//
	~CATCompactDump();
	//
  void Run();
  //

 protected:

  void DumpNode(CATCompactFunctionImpNode* iNode_X,
                CATCompactFunctionImpNode* iNode_Y,
                CATCompactFunctionImpNode* iNode_Z);

  void DumpNodeU(CATCompactFunctionImpNodeU* iNodeU_X, 
                 CATCompactFunctionImpNodeU* iNodeU_Y,
                 CATCompactFunctionImpNodeU* iNodeU_Z);

  void DumpNodeV(CATCompactFunctionImpNodeV* iNodeV_X, 
                 CATCompactFunctionImpNodeV* iNodeV_Y,
                 CATCompactFunctionImpNodeV* iNodeV_Z);

  void DumpNodeUV(CATCompactFunctionImpNodeUV* iNodeUV_X,
                  CATCompactFunctionImpNodeUV* iNodeUV_Y,
                  CATCompactFunctionImpNodeUV* iNodeUV_Z);

  void WriteNode(int iCoord, CATCompactFunctionImpNode* iNode,
                 double& ou, double& ov);

  void WriteEmptyNode(int iCoord);

  void DumpNodeCorner(int iCorner, 
                      CATCompactFunctionImpNode* iNodeX,
                      CATCompactFunctionImpNode* iNodeY,
                      CATCompactFunctionImpNode* iNodeZ);

  void UpdateRoad(int& SizeXU, int& SizeXV, 
                  int& SizeYU, int& SizeYV,
                  int& SizeZU, int& SizeZV);

	//
 private:
	//
   CATCompactFunctionImp* _TreeX;
   CATCompactFunctionImp* _TreeY;
   CATCompactFunctionImp* _TreeZ;
   int _LastNode;
   int _CurrentLevel;
   int _Niveau;
   CATListOfDouble _RoadXU;
   CATListOfDouble _RoadXV;
   CATListOfDouble _RoadYU;
   CATListOfDouble _RoadYV;
   CATListOfDouble _RoadZU;
   CATListOfDouble _RoadZV;

   CATCGMOutput* _Os; // pour les traces



};
#endif
#endif


