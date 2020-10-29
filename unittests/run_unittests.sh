#!/bin/bash

fail=0
pass=0

for f in fix16_unittests_* fix16_exp_unittests fix16_macros_unittests fix16_str_unittests_*
do
  if ! ./$f >> /dev/null; then
    echo "./$f failed!"
    ((fail=fail+1))
  else
    ((pass=pass+1))
  fi
done

echo "$fail tests failed, $pass tests passed."