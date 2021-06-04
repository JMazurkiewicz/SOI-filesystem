#!/bin/bash
# author: Jakub Mazurkiewicz

source test_new_delete.sh

if [ $? -ne 0 ]
then
    return 1
fi

source test_print.sh

if [ $? -ne 0 ]
then
    return 1
fi

source test_copy_remove.sh

if [ $? -ne 0 ]
then
    return 1
else
    return 0
fi
