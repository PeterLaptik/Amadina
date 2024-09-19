set OUTPUT_DIR_NAME=%1

set OUTPUT_ROOT=%OUTPUT_DIR_NAME%\bin
set OUTPUT_DEBUG=%OUTPUT_DIR_NAME%\bin\Debug
set OUTPUT_RELEASE=%OUTPUT_DIR_NAME%\bin\Release

for /f "tokens=*" %%a in (CMake.win.dlls.txt) do (
    echo line=%%a
    if exist  .\%OUTPUT_DEBUG%\ Copy %%a\*.dll .\%OUTPUT_DEBUG%\
    if exist  .\%OUTPUT_RELEASE%\ Copy %%a\*.dll .\%OUTPUT_RELEASE%\
    if not exist .\%OUTPUT_DEBUG%\ if not exist .\%OUTPUT_RELEASE%\ if exist .\%OUTPUT_ROOT%\ Copy %%a\*.dll .\%OUTPUT_ROOT%\
)

set ICONS_MENU=share\menu


