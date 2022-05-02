@echo off
rmdir Intermediate /s /q 
rmdir DerivedDataCache /s /q 
rmdir Binaries /s /q 
rmdir Saved /s /q 
rmdir .vs /s /q 

del /q *.sln