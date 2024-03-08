@echo off
set SRC_FILE=Poker_Game_Simulator_CPP.cpp
set EXE_FILE=poker_simulator.exe

g++ -o %EXE_FILE% %SRC_FILE%

if %errorlevel% neq 0 (
    echo Compilation failed!
    pause
    exit /b 1
)

%EXE_FILE%
