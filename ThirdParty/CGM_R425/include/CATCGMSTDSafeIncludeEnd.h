//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015
//===================================================================
// @author U69
// @usage Use in combination with CATCGMSTDSafeInludeStart.h to protect #include directive from STD library
// @comment Thanks to Viz Team for code sample 
// @change 2015/01/14 Creation
// @see VisualizationFoundation\PrivateInterfaces\EndSafeIncludeSTL.h
//===================================================================

#if (! defined CAT_ENABLE_NATIVE_EXCEPTION) && defined _AIX_SOURCE
#   if defined( RND_RESTORE_NATIVE_EXCEPTION )
#      undef RND_RESTORE_NATIVE_EXCEPTION
#   else
#      error "Nested inclusion of this file not supported, include CATCGMSTDSafeInludeStart before this file"
#   endif

#   define throw ERROR
#   define catch ERROR
#   define try ERROR

#endif //(! defined CAT_ENABLE_NATIVE_EXCEPTION) && defined _AIX_SOURCE
