@echo off
set MOSQUITTO_DIR=modules\mosquitto
%MOSQUITTO_DIR%\build\mosquitto.exe -c mosquitto.conf
pause