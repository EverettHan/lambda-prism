#ifndef DSYExport_h
#define DSYExport_h

#ifdef DSYLocal
# undef DSYLocal
#endif /* DSYLocal */

#ifdef DSYExport
# undef DSYExport
#endif /* DSYExport */

#ifdef DSYImport
# undef DSYImport
#endif /* DSYImport */

#define DSYLocal  __attribute__ ((visibility("hidden")))
#define DSYExport __attribute__ ((visibility("default")))
#define DSYImport __attribute__ ((visibility("default")))

#endif /* DSYExport_h */
