@echo off
g++ -o maker maker.cpp
:loop
maker.exe > data.in
std.exe < data.in > std.out
force.exe < data.in > force.out
fc std.out force.out
if not errorlevel 1 goto loop
pause
goto loop

