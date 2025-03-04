@echo off
mkdir build
cd build

cmake ..

cmake --build . --config Release

cd Release

Kits.exe %*