#!/bin/bash
# author: Jakub Mazurkiewicz

echo test_new_delete:
source test_new_delete.sh
echo 

if [ $? -ne 0 ]
then
    return 1
fi

echo test_print:
source test_print.sh
echo

if [ $? -ne 0 ]
then
    return 1
fi

echo test_copy_remove:
source test_copy_remove.sh
echo

if [ $? -ne 0 ]
then
    return 1
fi

echo test_self_copy_remove:
source test_self_copy_remove.sh
echo

if [ $? -ne 0 ]
then
    return 1
fi

echo test_multiple_copies:
source test_multiple_copies.sh
echo

if [ $? -ne 0 ]
then
    return 1
fi

return 0
