#!/bin/bash
# author: Jakub Mazurkiewicz

svfs='../build/svfs'

disk_name='test_new_delete'
disk_size='500000'

./$svfs new $disk_name $disk_size
got_size=`stat --printf="%s" $disk_name.vd`

if [ $got_size -ne $disk_size ]
then
    return 1
fi

./$svfs delete $disk_name.vd

if [ -f $disk_name.vd ]
then
    return 1
fi

return 0
