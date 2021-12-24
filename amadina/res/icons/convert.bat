@echo off 
set "files="
for %%F in (*.ico) do call set files=%%files%% "%%F"
echo %files%
bin2c.exe -o icons.h %files%
xcopy /f /y /s .\icons.h ..\..\Amadina\wx_binding\res\icons.h
@pause