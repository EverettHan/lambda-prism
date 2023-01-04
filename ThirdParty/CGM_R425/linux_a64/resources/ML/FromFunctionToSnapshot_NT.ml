[NODEDECLARATION]
LogicalREF    : RFLPLMFunctionalReference
SnapshotCNX   : Snapshot2DInputConnection
SnapshotREF   : SnapshotReference

[RELATIONDECLARATION]
SnapshotSR : Reference3/Snapshot2DSource

[NAVIGATES]
LogicalREF -[SnapshotSR]!> SnapshotCNX -[Owner]> SnapshotREF
