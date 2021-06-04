#!/bin/bash
# author: Jakub Mazurkiewicz

svfs='../build/svfs'

disk_name='test_multiple_copies'
disk_size='2000000'

replacement='alt_svfs'
response_empty=$'Disk is empty.'
ret=0

big_msg='msg1.txt'
medium_msg='msg2.txt'
small_msg='msg3.txt'

medium1='medium1.txt'
medium2='medium2.txt'
medium3='medium3.txt'
big='big.txt'
small='small.txt'

cd messages
cp $big_msg $big
cp $medium_msg $medium1
cp $medium_msg $medium2
cp $medium_msg $medium3
cp $small_msg $small
cd ..

./$svfs new $disk_name $disk_size

cd messages
../$svfs copy from native to ../$disk_name.vd $medium1
../$svfs copy from native to ../$disk_name.vd $medium2
../$svfs copy from native to ../$disk_name.vd $medium3

../$svfs remove $medium2 from ../$disk_name.vd

../$svfs copy from native to ../$disk_name.vd $small
../$svfs copy from native to ../$disk_name.vd $medium2

../$svfs remove $medium1 from ../$disk_name.vd
../$svfs remove $medium3 from ../$disk_name.vd

../$svfs copy from native to ../$disk_name.vd $big

rm $big
rm $medium1
rm $medium2
rm $medium3
rm $small

../$svfs copy from ../$disk_name.vd to native $big
../$svfs copy from ../$disk_name.vd to native $small

if ! cmp -s "$big" "$big_msg"
then
    ret=1
fi

if ! cmp -s "$small" "$small_msg"
then
    ret=1
fi

rm $big
rm $small

cd ..
rm $disk_name.vd
return $ret
