#!/bin/bash
# author: Jakub Mazurkiewicz

svfs='../build/svfs'

disk_name='test_print'
disk_size='500000'

response_empty=$'Disk is empty.'
response_nonempty=$'File name                       | Size in bytes | Disk offset \n--------------------------------+---------------+-------------\nmsg1.txt                        | 409s0         | 1312        '

./$svfs new $disk_name $disk_size
got=`./$svfs print $disk_name.vd`

if [[ "$got" != "$response_empty" ]]
then
    rm $disk_name.vd
    return 1
fi

cd messages
../$svfs copy from native to ../$disk_name.vd msg1.txt
cd ..
got=`./$svfs print $disk_name.vd`

if [[ "$got" != "$response_nonempty" ]]
then
    rm $disk_name.vd
    return 1
fi

rm $disk_name.vd
return 0