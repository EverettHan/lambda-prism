for fic in `ls`
do
  cd $fic
  adl_mk_elem -resp hwu */*
  cd ..
done
