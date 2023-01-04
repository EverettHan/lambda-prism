#!/bin/ksh
#############################################################################
# COPYRIGHT DASSAULT SYSTEMES 2004                                          #
# ==========================================================================#
#                                                                           #
#  This shell request a specified browser to connect                        #
#  a given URL                                                              #
#                                                                           #
#                                                                           #
#   usage : CATSysCmdNs.sh browser id url version ["netscape7"|"def"] ...   #
#              [command | "def"]  ["-nw" |"def"] [cmd_opt|"def"]        #
#                                                                           #
#                                                                           #
#                                                                           #
#  Return codes    : 0 if OK                                                #
#                    1 if Netscape cannot be found                          #
#                    2 if too long to start                                 #
#                                                                           #
#                                                                           #
#############################################################################

unset ENV
unset export
os=`uname 2>/dev/null`

CATBROWSER=$1
CATBROWSEREXE=$1
CATWinId=$2
CATSetUrl=$3
CATSetCmd=OpenURL
CATSetUrlOpt=""
CATSetCmdOpt=""
if [ $# -ge 4 ];then
CATBrwVersion=$4
else
CATBrwVersion="unknown"
fi
if [ $# -ge 5 ] ; then
  if [ $5 = "netscape7"  ] ; then   
  CATBROWSEREXE=$5
  fi
fi
if [ $# -ge 6 ];then
  if  [ $6 != "def" ]; then
    CATSetCmd=$6
  fi
fi 
if [ $# -ge 7 ];then
  if  [ $7 = "-nw" ]; then
    CATSetUrlOpt=",new-window"
   fi
fi 
if [ $# -ge 8 ];then
  if  [ $8 != "def" ]; then
    CATSetCmdOpt=$8
   fi
fi 
#====================================================
#test $CATBROWSER  access
whence $CATBROWSER >/dev/null 2>&1
if [ $? != 0 ]
then
 exit 3
fi
#====================================================
#check that $CATBROWSER  exits 
if [ $os = 'SunOS' ] ; then
  TmpDirRunNs=$CATTemp
  if [ A$CATTemp = "A"  ] ; then
    TmpDirRunNs=/tmp
  fi
  rm $TmpDirRunNs/ficRunNs_$$.txt >/dev/null 2>&1
  $CATBROWSEREXE -id 0x$CATWinId -remote 'saveAs('$TmpDirRunNs/ficRunNs_$$.txt')' >/dev/null 2>&1
  if [ $? = 0 ];
  then
    if [ -f $TmpDirRunNs/ficRunNs_$$.txt ] ; then
       rc=0
       rm $TmpDirRunNs/ficRunNs_$$.txt >/dev/null 2>&1
       #====================================================
       #send the URL and test if $CATBROWSER is running
       $CATBROWSEREXE -id 0x$CATWinId $CATSetCmdOpt  -remote $CATSetCmd'('$CATSetUrl$CATSetUrlOpt')' >/dev/null 2>&1
       rc=$?
    else
        ## even if the save failed we try load the URL
        $CATBROWSEREXE -id 0x$CATWinId  $CATSetCmdOpt -remote $CATSetCmd'('$CATSetUrl$CATSetUrlOpt')' >/dev/null 2>&1
       rc=2
    fi
  else
    ## even if the save failed we try load the URL
    $CATBROWSEREXE -id 0x$CATWinId  $CATSetCmdOpt -remote $CATSetCmd'('$CATSetUrl$CATSetUrlOpt')' >/dev/null 2>&1
    rc=2
  fi
else
 #send the URL and test if $CATBROWSER is running
 $CATBROWSEREXE -id 0x$CATWinId $CATSetCmdOpt -remote $CATSetCmd'('$CATSetUrl$CATSetUrlOpt')' >/dev/null 2>&1
 rc=$?
fi
