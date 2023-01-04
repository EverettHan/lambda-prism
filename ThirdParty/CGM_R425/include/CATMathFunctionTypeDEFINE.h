#ifndef CATMathFunctionTypeDEFINE_h
#define CATMathFunctionTypeDEFINE_h
// COPYRIGHT DASSAULT SYSTEMES  2009
//-------------------------------------------------------- 
//  V E R Y     I M P O R T A N T  !!!!!!!
//----------------------------------------------------------------------------
// Persistency.Engineering.Change  "DataBase" 
//        Advanced Mathematics Function Types
//  CATMathFunctionTypeDECLARE(FunctionName,FunctionPersistentType,FunctionCategory)  
//----------------------------------------------------------------------------
//  Storage : Persistency Change Management   
//
// #define CATCGMStreamTypeDECLARE(CGMTypeName,CGMTypeValue,CGMTypeIndex) \
//    CAT##CGMTypeName##Type  = CGMTypeValue, \
//

CATMathFunctionTypeDECLARE(PolynomX,1,FunctionX)
CATMathFunctionTypeDECLARE(TrigonometricX,2,FunctionX)
CATMathFunctionTypeDECLARE(FractionX,3,FunctionX)
CATMathFunctionTypeDECLARE(CombinationX,4,FunctionX)
CATMathFunctionTypeDECLARE(PiecewiseX,5,FunctionX)
CATMathFunctionTypeDECLARE(QuinticX,6,FunctionX)
CATMathFunctionTypeDECLARE(ArctanCosX,7,FunctionX)
CATMathFunctionTypeDECLARE(SingleMemoryX,8,FunctionX)
CATMathFunctionTypeDECLARE(CompositionXByXY,9,FunctionX)
CATMathFunctionTypeDECLARE(CubicX,10,FunctionX)
CATMathFunctionTypeDECLARE(CompositionXByX,11,FunctionX)
CATMathFunctionTypeDECLARE(LinearX,12,FunctionX)
CATMathFunctionTypeDECLARE(DerivX,13,FunctionX)
CATMathFunctionTypeDECLARE(OppositeX,14,FunctionX)
  
CATMathFunctionTypeDECLARE(PolynomXY,101,FunctionXY)
CATMathFunctionTypeDECLARE(PiecewiseXY,102,FunctionXY)
CATMathFunctionTypeDECLARE(SumXYs,103,FunctionXY)
CATMathFunctionTypeDECLARE(NormalSquareNorm,104,FunctionXY)
CATMathFunctionTypeDECLARE(FractionXY,105,FunctionXY)
CATMathFunctionTypeDECLARE(SingleMemoryXY,106,FunctionXY)
 


#endif
