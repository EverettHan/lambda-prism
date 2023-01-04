#ifndef CATAnalysisToolsErrors_H
#define CATAnalysisToolsErrors_H
#include "CATTopOpInError.h" 
#include "CATTopOpIntError.h" 

#define ThrowIfNullInput(ptr)                                                \
if (!ptr)                                                                    \
 { CATTopOpInError * Error =                                                 \
      new  CATTopOpInError (TopOpInNull,"TopOpInNull",TopOpInFile);          \
      CATThrow (Error);  } 
/*
#define ThrowBadTopology                                                     \
 { CATTopOpIntError * Error =   new  CATTopOpIntError                        \
       (TopOpIntBadTopology,"TopOpIntBadTopology",TopOpIntFile);             \
      CATThrow (Error);  } 
*/

#define ThrowBadArrangement                                                  \
 { CATTopOpIntError * Error =   new  CATTopOpIntError                        \
       (TopOpIntBadGeometry,"TopOpIntBadGeometry",TopOpIntFile);             \
      CATThrow (Error);  } 

#define PrintBadOri(i)             \
	cgmerr<<"******************************************"<<cgmendl;             \
	cgmerr<<"****** ERROR : CATCurvesArrangement ******"<<cgmendl;             \
	cgmerr<<"****** La courbe "<<i<<" est mal orientee" << cgmendl;            \
	cgmerr<<"******************************************"<<cgmendl;             \

#define PrintIsolatedCrv(i)             \
	cgmerr<<"******************************************"<<cgmendl;             \
	cgmerr<<"****** ERROR : CATCurvesArrangement ******"<<cgmendl;             \
	cgmerr<<"****** La courbe "<<i<<" n'a pas de voisine" << cgmendl;          \
	cgmerr<<"******************************************"<<cgmendl;             \

#define PrintNonManifoldCrv(i)             \
	cgmerr<<"******************************************"<<cgmendl;             \
	cgmerr<<"****** ERROR : CATCurvesArrangement ******"<<cgmendl;             \
	cgmerr<<"****** La courbe "<<i<<" a plus de 2 voisines" << cgmendl;        \
	cgmerr<<"******************************************"<<cgmendl;             \

#undef analysis_debug
//#define analysis_debug

#ifdef analysis_debug
#define Print(title) show_trace=1; cgmout<<title<<cgmendl;
#else
#define Print(title) if (show_trace>0) {cgmout<<title<<cgmendl;}
#endif

#endif





