#!/bin/ksh
#############################################################################
# COPYRIGHT DASSAULT SYSTEMES 2004                                          #
# ==========================================================================#
#                                                                           #
#  This shell starts a specified browsere with an URL                       #
#  Its input argument is the URL                                            #
#                                                                           #
#  Return codes    : 0 if OK                                                #
#                    1 if Netscape cannot be found                          #
#                    2 if too long to start                                 #
#                                                                           #
#############################################################################
unset ENV
unset export
CATBROWSER=$1
CATBROWSEREXE=$CATBROWSER
CATStartUrl=$2
if  [ A$CATBROWSER = A"netscape" ] ; then
  # permits to support  a kind of non standard netscape7 installation if needed 
  whence netscape7 >/dev/null 2>&1
  if [ $? -eq 0 ]
  then
    CATBROWSEREXE=netscape7
  else
    whence netscape6 >/dev/null 2>&1
    if [ $? -eq 0 ]
    then
      CATBROWSEREXE=netscape6
    else
  # permits to support  a kind of non standard netscape6 installation if needed 
      whence $CATBROWSER >/dev/null 2>&1
      if [ $? != 0 ]
      then
        exit 1
      fi
    fi
  fi
else
  whence $CATBROWSER >/dev/null 2>&1
  if [ $? != 0 ]
  then
   exit 1
  fi
fi

INSTVAR=""
BRWVERSION=1
##=======================================================================
## we check the version
##=======================================================================
if  [ $CATBROWSER = "netscape" ] ; then
  BRWVERSITP=`$CATBROWSEREXE -version 2>&1` 
  BRWVERSION=`echo $BRWVERSITP | sed 's/^.*[Nn]etscape\/* *\([0-9]*\)\..*$/\1/'` 
  if [ $BRWVERSION = 4 ]  ;
  then
    INSTVAR="-install -no-about-splash"
  else
    INSTVAR=""
  fi
fi
if  [ $CATBROWSER = "mozilla" ] ; then
BRWVERSION=`$CATBROWSEREXE -version 2>&1 | sed 's/^Mozilla *\([0-9]*\)\..*$/\1/'` 
INSTVAR=""
fi

#==============================================================================
$CATBROWSEREXE $INSTVAR  $CATStartUrl?version=$BRWVERSION\&\?exe=$CATBROWSEREXE    >/dev/null 2>&1 
rc=$?

###if [ "`uname`" = "HP-UX" ] && type dtterm >/dev/null 2>&1 ;
###then
###  dtterm -iconic -geometry 1x1+0+0 -e $CATBROWSEREXE $INSTVAR $CATStartUrl?version=$BRWVERSION >/dev/null 2>&1
###  rc=$?
###else
###  $CATBROWSEREXE $INSTVAR  $CATStartUrl?version=$BRWVERSION\&\?exe=$CATBROWSEREXE    >/dev/null 2>&1 
###  rc=$?
###fi
exit $rc
