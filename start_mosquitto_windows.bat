@echo off
set MOSQUITTO_DIR=modules\mosquitto
set CONFIG_FILE=mosquitto.conf

REM Create necessary directories
if not exist %MOSQUITTO_DIR%\log mkdir %MOSQUITTO_DIR%\log
if not exist %MOSQUITTO_DIR%\data mkdir %MOSQUITTO_DIR%\data

REM Read the port number from the configuration file
for /f "tokens=2 delims= " %%a in ('findstr /r "^listener" %CONFIG_FILE%') do set PORT=%%a

REM Debug output to verify the port number
echo Starting mosquitto broker on port %PORT%...

REM Start the mosquitto broker
%MOSQUITTO_DIR%\build\src\Debug\mosquitto.exe -c %CONFIG_FILE%

pause