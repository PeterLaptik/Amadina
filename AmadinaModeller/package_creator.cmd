set OUTPUT_DIR_NAME=%1
set THIRD_PARTY_DLL_LIST_FILE_NAME=%2
set WX_WIDGETS_DLL_DIR_NAME=%3
set OPENCASCADE_DLL_DIR_NAME=%4

set OUTPUT_ROOT=%OUTPUT_DIR_NAME%\bin
set OUTPUT_DEBUG=%OUTPUT_DIR_NAME%\bin\Debug
set OUTPUT_RELEASE=%OUTPUT_DIR_NAME%\bin\Release

if exist  .\%OUTPUT_DEBUG%\ Copy %WX_WIDGETS_DLL_DIR_NAME%\*.dll .\%OUTPUT_DEBUG%\
    if exist  .\%OUTPUT_RELEASE%\ Copy %WX_WIDGETS_DLL_DIR_NAME%\*.dll .\%OUTPUT_RELEASE%\
    if not exist .\%OUTPUT_DEBUG%\ if not exist .\%OUTPUT_RELEASE%\ if exist .\%OUTPUT_ROOT%\ Copy %WX_WIDGETS_DLL_DIR_NAME%\*.dll .\%OUTPUT_ROOT%\
    
if exist  .\%OUTPUT_DEBUG%\ Copy %OPENCASCADE_DLL_DIR_NAME%\*.dll .\%OUTPUT_DEBUG%\
    if exist  .\%OUTPUT_RELEASE%\ Copy %OPENCASCADE_DLL_DIR_NAME%\*.dll .\%OUTPUT_RELEASE%\
    if not exist .\%OUTPUT_DEBUG%\ if not exist .\%OUTPUT_RELEASE%\ if exist .\%OUTPUT_ROOT%\ Copy %OPENCASCADE_DLL_DIR_NAME%\*.dll .\%OUTPUT_ROOT%\

for /f "tokens=1* EOL=#" %%a in (%THIRD_PARTY_DLL_LIST_FILE_NAME%) do (
    echo line=%%a
    if exist  .\%OUTPUT_DEBUG%\ Copy %%a\*.dll .\%OUTPUT_DEBUG%\
    if exist  .\%OUTPUT_RELEASE%\ Copy %%a\*.dll .\%OUTPUT_RELEASE%\
    if not exist .\%OUTPUT_DEBUG%\ if not exist .\%OUTPUT_RELEASE%\ if exist .\%OUTPUT_ROOT%\ Copy %%a\*.dll .\%OUTPUT_ROOT%\
)

:: TODO
set ICONS_MENU=share\menu


