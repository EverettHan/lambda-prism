# !!! WARNING CAA: cannot be included safely as-is for modules exposed in CAA !!!
# Regroup specific build options for the C++/CLI langage (Windows)
# CCFLAGS_WIN, POST_CCFLAGS_WIN allow to add options from inside an Imakefile

CLR = YES
CPP_EXCEPT=/EHa   # Need to override Native exceptions option for CLR modules
CXX_NOPERMISSIVE= YES
LOCAL_CCFLAGS = $(CCFLAGS_WIN)
# Unfortunetaly, "C++/CLI mode does not support C++ versions newer than C++17", dixit Microsoft
LOCAL_POST_CCFLAGS = $(POST_CCFLAGS_WIN) /D "NOMINMAX" /std:c++17 /permissive- /Zc:twoPhase-

#if os Windows
BUILD = YES
#else
BUILD = NO
#endif
