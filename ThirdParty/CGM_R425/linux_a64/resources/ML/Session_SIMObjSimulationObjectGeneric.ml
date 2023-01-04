[NODEDECLARATION]
SimObj : SIMObjSimulationObjectGeneric
MSRRef : SIMObjSimulationCategoryReference
MSRInst : SIMObjSimulationCategoryInstance
NV5Inst : SIMObjSimulationRepInstanceGeneric
NV5Rep : SIMObjSimulationRepReferenceGeneric
V5Inst : SIMObjSimulationV5RepInstanceGeneric
V5Rep : SIMObjSimulationV5RepReferenceGeneric
CnxRes : SIMObjectSimulationPublishedResultCnx
CnxMod : SIMObjSimulationSystem
CnxDoc1 : PLMDocConnection
CnxDoc2 : PLMDocConnection

[NAVIGATES]
SimObj-[Owner]!>MSRInst-[InstOf]>MSRRef
SimObj=>CnxDoc1
MSRRef-[Owner]!>V5Inst-[InstOf]>V5Rep
MSRRef-[Owner]!>NV5Inst-[InstOf]>NV5Rep
MSRRef=>CnxDoc2
MSRRef=>CnxRes
MSRRef=>CnxMod

