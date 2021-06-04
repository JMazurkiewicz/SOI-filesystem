#!/bin/bash
# author: Jakub Mazurkiewicz

svfs='../build/svfs'

disk_name='test_self_copy_remove'
disk_size='1000000'

replacement='alt_svfs'
response_empty=$'Disk is empty.'
ret=0

./$svfs new $disk_name $disk_size
cd ../build
cp svfs $replacement
./$svfs copy from native to ../tests/$disk_name.vd $replacement
./$svfs copy from ../tests/$disk_name.vd to native $replacement
cd ../tests

./$svfs remove $replacement from $disk_name.vd
got=`./$svfs print $disk_name.vd`

if [[ "$got" != "$response_empty" ]]
then
    ret=1
fi

got=`../build/$replacement print $disk_name.vd`

if [[ "$got" != "$response_empty" ]]
then
    ret=1
fi

rm $disk_name.vd
rm ../build/$replacement
return $ret
