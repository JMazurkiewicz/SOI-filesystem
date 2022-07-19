# SOI - system plików

[![linux](https://github.com/JMazurkiewicz/SOI-filesystem/actions/workflows/linux.yml/badge.svg)](https://github.com/JMazurkiewicz/SOI-filesystem/actions/workflows/linux.yml)

Author: Jakub Mazurkiewicz

## Get and build

```bash
git clone https://github.com/JMazurkiewicz/SOI-filesystem.git
cd SOI-filesystem
cmake -B build
cmake --build build
```

## Basic usage

```bash
mv build/svfs .

# Display help
./svfs help

# Create disk named `Drive.vd` of 3000000 bytes
./svfs new Drive 3000000

# Copy `CMakeLists.txt` to virtual drive
./svfs.exe copy from native to Drive.vd CMakeLists.txt

# Print content of virtual drive
./svfs.exe print .\Drive.vd
# This prints:
# * File name                       | Size in bytes | Disk offset
# * --------------------------------+---------------+-------------
# * CMakeLists.txt                  | 489           | 1312

# Delete `CMakeLists.txt` and get it back from virtual drive
rm CMakeLists.txt
./svfs.exe copy from Drive.vd to native CMakeLists.txt

# Remove file from drive
./svfs.exe remove CMakeLists.txt from Drive.vd
./svfs.exe print Drive.vd
# This prints:
# * Disk is empty.

# Delete virtual drive
/svfs.exe delete Drive.vd
```

## "Operating systems" course info

Task: [LINK](https://www.ia.pw.edu.pl/~tkruk/edu/soib/lab/t6.txt)

Score:

* Concept: 2/2
* Program: 6/6
