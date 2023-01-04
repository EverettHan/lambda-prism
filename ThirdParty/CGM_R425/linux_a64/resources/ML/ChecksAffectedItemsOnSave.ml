[NODEDECLARATION]
ECA: PLMActionBase
CNX: PLMChgTaskInput
REL: VPMInstance
REF: VPMReference
REPREF: VPMRepReference

[RELATIONDECLARATION]
PointedAff: Reference/PLMChgActionInput

[NAVIGATES]
ECA-[Owner]>CNX-[PointedAff]>REL
CNX-[PointedAff]>REF
CNX-[PointedAff]>REPREF

[LINES]
CNX.PLMID

[COLUMNS]
REL.PLM_ExternalID
REF.PLM_ExternalID
REPREF.PLM_ExternalID

