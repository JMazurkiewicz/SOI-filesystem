#!/bin/bash
# author: Jakub Mazurkiewicz

svfs='../build/svfs'

disk_name='test_copy_remove'
disk_size='500000'

response_empty=$'Disk is empty.'

message_name='msg1.txt'
message_altname='msg2.txt'

ret=0

./$svfs new $disk_name $disk_size

cd messages
../$svfs copy from native to ../$disk_name.vd $message_name
mv $message_name $message_altname
../$svfs copy from ../$disk_name.vd to native $message_name
cd ..

if cmp -s $message_altname $message_name
then
    ret=1
fi

./$svfs remove $message_name from $disk_name.vd
got=`./$svfs print $disk_name.vd`

if [[ "$got" != "$response_empty" ]]
then
    rm $disk_name.vd
    return 1
fi

rm messages/$message_altname
rm $disk_name.vd
return $ret
