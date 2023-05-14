#!/bin/bash
./bin/basic\ /bin/main /src/main/program.vb data.dat
./bin/assembler\ /bin/main /src/main/data.asm data.dat
cp data.o Computer\ Simulator/bin/
cd Computer\ Simulator/bin
./main.exe