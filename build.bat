@ECHO OFF

setlocal
SET CURRENT_DIR=%cd%
SET CMAKE_INSTALL_PREFIX=%CURRENT_DIR%/install
ECHO %CMAKE_INSTALL_PREFIX%

SET PYTHONPATH="%CURRENT_DIR%/build"
ECHO %PYTHONPATH%

if not exist "build" mkdir build
cd build


SET PYTHONPATH="%CURRENT_DIR%/build"
call cmake ..
call cmake --build . --config Release
call cmake --install .

cd ..
endlocal
pause
cmd /k
