@echo off
echo Building os lib test...
gcc -w -o build/os_lib_test.exe source/os_lib_test.c -lWs2_32

call .\build\os_lib_test.exe
