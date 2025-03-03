@echo off
mkdir build 2>nul
cd build

cmake ..
if %errorlevel% neq 0 exit /b %errorlevel%

make
if %errorlevel% neq 0 exit /b %errorlevel%

Kits %*
