//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015
//===================================================================
// @author U69
// @usage Use in combination with CATCGMSTDSafeInludeEnd.h to protect #include directive from STD library
// @comment Thanks to Viz Team for code sample 
// @change 2015/01/14 Creation
// @see VisualizationFoundation\PrivateInterfaces\BeginSafeIncludeSTL.h
//===================================================================

#if (! defined CAT_ENABLE_NATIVE_EXCEPTION) && defined _AIX_SOURCE
#   if defined( RND_RESTORE_NATIVE_EXCEPTION )
#      error "Nested inclusion of this file not supported, include CATCGMSTDSafeInludeEnd before this file"
#   else
#      define RND_RESTORE_NATIVE_EXCEPTION
#   endif

#undef throw
#undef catch
#undef try

#endif //(! defined CAT_ENABLE_NATIVE_EXCEPTION) && defined _AIX_SOURCE
