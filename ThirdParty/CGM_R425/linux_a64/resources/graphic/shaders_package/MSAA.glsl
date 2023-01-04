//#define IS_MSAA // needs to be defined as a shader option!!

#ifdef GLSLVersion
#if (GLSLVersion < 400)
#define NoPerSampleShading
#endif
#endif

