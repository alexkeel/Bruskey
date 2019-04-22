mkdir build
cd build
cmake ../
make all

cd Components/Compiler
./Compiler < testinput.txt > testOutput.c
indent -st -bap -bli0 -i4 -l79 -ncs -npcs -npsl -fca -lc79 -fc1 -ts4 testOutput.c > output.c

cd ../../Test/
./Tests

cp build/Components/Compiler/Compiler /usr/bin/Brusky

