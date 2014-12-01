@echo off
make
pause
cat tpsgui.3dsx | nc 192.168.137.137 9000
@echo on