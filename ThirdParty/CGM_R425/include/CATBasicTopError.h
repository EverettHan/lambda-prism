/* Generated from CATBasicTopError.msg on Fri Nov 27 13:48:10 1998
 */
#ifndef _CATBASICTOPERROR_INCLUDE
#define _CATBASICTOPERROR_INCLUDE

// COPYRIGHT DASSAULT SYSTEMES 1999

typedef enum {

  BasTopInError_InvalidArguments = 0x00020001u,
       BasTopInError_NullPointer = 0x00020002u,
    BasTopInError_OperationError = 0x00020003u,
    BasTopInError_NotImplemented = 0x00020004u,
  BasTopInError_InvalidaDistance = 0x00020005u,
       BasTopInError_InvalidType = 0x00020006u,
    BasTopInError_InvalidSubType = 0x00020007u,

       BasicTopIntError_Argument = 0x00020011u,
    BasicTopIntError_Orientation = 0x00020012u,
     BasicTopIntError_RankOfEdge = 0x00020013u,
BasicTopIntError_UnSuccessfulCreation = 0x00020014u,
   BasicTopIntError_InvalidInput = 0x00020015u,
       BasicTopIntError_NoVertex = 0x00020016u,
         BasicTopIntError_NoWire = 0x00020017u,
       BasicTopIntError_Internal = 0x00020018u,
        BasicTopIntError_Logical = 0x00020019u
} BasicTopologicalOpeErrors;

#endif
