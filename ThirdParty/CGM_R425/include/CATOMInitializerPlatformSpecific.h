// COPYRIGHT DASSAULT SYSTEMES 2021
#if !defined(CATOMInitializerPlatformSpecific_H)
#define CATOMInitializerPlatformSpecific_H
/** @CAA2Required */
/**********************************************************************/
/* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME */
/**********************************************************************/

#if !defined(CATOMInitializer_CompileTimeRegisterDisable)
#if (defined(__GNUC__) || defined(__clang__)) && defined(__ELF__)
// GCC/Clang

#if defined __has_attribute
# if __has_attribute (retain)   // Not supported/applicable on all platforms
#  define CATOM_ATTR_USED(sym_name) __attribute__((used,retain))
# endif
#endif
#if !defined(CATOM_ATTR_USED)
# define CATOM_ATTR_USED(sym_name)  __attribute((used))
#endif


#define CATOM_SECTION_DECL \
    /* Creating weak symbols allows to avoid potential link errors for modules that do not use CATOM_REGISTER_INITIALIZER at all */\
    /* It should still be ok when CATOM_REGISTER_INITIALIZER is used, because GCC generates strong symbols, that take precedence over weak ones at link time */\
    __attribute((weak, visibility ("hidden"))) extern const PCATOMFuncInit_t CATOM_SECTION_START; \
    __attribute((weak, visibility ("hidden"))) extern const PCATOMFuncInit_t CATOM_SECTION_END;

// Example: __attribute__ ((section (".qtmetadata"))) __attribute__((used))
#define CATOM_REGISTER_INITIALIZER(id, fn) \
    /* used/retain necessary to ensure linker doesn't eject the code */\
    __attribute((section(CATOM_XSTR(CATOM_BINARY_SECTION_NAME)))) CATOM_ATTR_USED(CATOM_XSTR(CATOM_INIT_VAR_NAME(id)))\
    static const PCATOMFuncInit_t CATOM_INIT_VAR_NAME(id) = fn

#else
#error "Unknown platform, not currently supported"  // For non ELF targets
#endif
#endif  // NOT CATOMInitializer_CompileTimeRegisterDisable


#endif  // CATOMInitializerPlatformSpecific_H


