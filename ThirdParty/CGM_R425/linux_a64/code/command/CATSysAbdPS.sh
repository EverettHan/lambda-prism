#!/bin/ksh
catsysos=`uname` 2>/dev/null  
catsysvar="-elaf"
if [ "$catsysos" = 'AIX' -o "$catsysos" = 'HP-UX'  ] ; then
  catsysvar="wvg"
fi


if [ $# -ge 1 ] ; then
  echo  >> $1 2>/dev/null
  echo "[RUNNING_PROCESSES]" >> $1 2>/dev/null
  echo  >> $1 2>/dev/null
  ps $catsysvar   >> $1 2>/dev/null
  echo  >> $1 2>/dev/null
fi
