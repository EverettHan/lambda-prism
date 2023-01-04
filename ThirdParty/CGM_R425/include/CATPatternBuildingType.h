#ifndef CATPatternBuildingType_H
#define CATPatternBuildingType_H

// Use for DRepPattern technology
// ------------------------------
enum CATPatternBuildingType {
  CATPatternBuilding_UnknownType=0,         // 0: Unkown type
  CATPatternBuilding_PatternOfPatternType,  // 1: Pattern of Pattern
  CATPatternBuilding_RemoveRedoType,        // 2: Pattern of Depression/Protrusion/Domain build with RemoveRedoPattern
  CATPatternBuilding_NoRedoType,            // 3: Pattern of unknown topological type build directly by SingleTranformeFace : "IsoTopological" Pattern
  CATPatternBuilding_BlendDesingType,        // 4: Pattern of Blend Design are rebuild by the application
  CATPatternBuilding_DrawType
};

#endif
