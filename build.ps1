# create build folder if doesn't exist
if (!(Test-Path -Path build)) { mkdir build }

# use GCC compiler to compile main.c to build/main
if ($?) { gcc main.c -o build\main }

# run the executable if exists
if ($?) { .\build\main }