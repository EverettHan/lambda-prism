#!/bin/ksh
#############################################################################
# COPYRIGHT DASSAULT SYSTEMES 2004                                          #
# ==========================================================================#
# usage  CATSysIdtNs browser_name window_name                               #
#  rc : 0 if successful                                                     #
#       1 if failed                                                         #
#############################################################################
CATBROWSER=$1
CATBROWSEREXE=$CATBROWSER
CATWinName=$2
if [ A$CATBROWSER = Anetscape ] ; then
  whence netscape7 >/dev/null 2>&1
  if [ $? -eq 0 ]
  then
    ## adaptation tout possible non-standard ns7 installations
    CATBROWSEREXE=netscape7
  else
    whence netscape6 >/dev/null 2>&1
    if [ $? -eq 0 ]
    then
      ## adaptation tout possible non-standard ns7 installations
      CATBROWSEREXE=netscape6
    else
      whence $CATBROWSER >/dev/null 2>&1
      if [ $? != 0 ]
      then
        exit 1
      fi
    fi
  fi
  BRWVERSITP=`$CATBROWSEREXE -version 2>&1` 
  BRWVERSION=`echo $BRWVERSITP | sed 's/^.*[Nn]etscape\/* *\([0-9]*\)\..*$/\1/'` 
  if [ $BRWVERSION = 4 ]  ;
  then
    ## netscape 4
    CATWinPrefix="Netscape: "
    CATWinPostix=""
  else
    ## netscape autres
  CATWinPrefix=""
  CATWinPostix=" - Netscape"
  fi
fi
if [ A$CATBROWSER = Amozilla ] ; then
CATWinPrefix=""
CATWinPostix=" - Mozilla"
fi
os=`uname 2> /dev/null`
if [ $os = 'HP-UX' ] ; then
PATH=$PATH:/usr/contrib/bin/X11
fi
integer Tested=1
while [ Tested -lt 60 ] 
do 
xwininfo -name "${CATWinPrefix}${CATWinName}${CATWinPostix}"  >/dev/null 2>&1
if [ $? -eq 0 ] ; then
  val=`xwininfo -name "${CATWinPrefix}${CATWinName}${CATWinPostix}" 2>/dev/null`
  echo $val | sed "s/.*Window id *: *//" | sed "s! .*!!" 2>/dev/null
  exit 0
fi
Tested=Tested+1
done
exit 1
