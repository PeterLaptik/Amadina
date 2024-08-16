# ----------------------------------------------------------------
# Quick clean all CMake data files and MS VS projects (optionally)
# ----------------------------------------------------------------

#Clean CMake data
$DIR_PROJECTS_PATHS = -join((Get-Item .).FullName, "/"), # Current root directory
                    "./AmadinaModeller/",
                    "./wxOcctView/", 
                    "./AmadinaOCCT/", 
                    "./AmadinaObjects/"
                    
$DIR_CMAKEFILES_DIR = "CMakeFiles"

$FILE_CMAKE_FILES = "CMakeCache.txt","cmake_install.cmake"

# Remove dirs CMakeFiles
Write-Host "CMake files and directories clean..."
for ($i = 0; $i -lt $DIR_PROJECTS_PATHS.Count; $i++) {
    $dirToRemove = -join($DIR_PROJECTS_PATHS[$i], $DIR_CMAKEFILES_DIR)
    if(Test-Path -LiteralPath $dirToRemove) {
        Write-Host "Removing directory: " $dirToRemove
        rm $dirToRemove -r -force
    }
}

# Remove files
for ($i = 0; $i -lt $DIR_PROJECTS_PATHS.Count; $i++) {
    for($j = 0; $j -lt $FILE_CMAKE_FILES.Count; $j++) {
        $fileToRemove = -join($DIR_PROJECTS_PATHS[$i], $FILE_CMAKE_FILES[$j])
        if(Test-Path -LiteralPath $fileToRemove) {
            Write-Host "Removing file: " $fileToRemove
            rm $fileToRemove
        }
    }
}

Write-Host "CMake files and directories have been cleaned."


# Clean Microsoft Visual Studio data

$REMOVE_VS_PROJECTS = Read-Host -Prompt "Remove Visual Studio projects files? [y/n]"
if($REMOVE_VS_PROJECTS -eq 'y') {
    for ($i = 0; $i -lt $DIR_PROJECTS_PATHS.Length; $i++) {
        $files = Get-ChildItem $DIR_PROJECTS_PATHS[$i] | where {$_.extension -in ".vcxproj",".filters", ".sln"}
        for ($j = 0; $j -lt $files.Count; $j++) {
            $fileToRemove = $files[$j].fullname
            Write-Host "Removing file: " $fileToRemove
            rm $fileToRemove
        }
    }
    Write-Host "Visual Studio projects files have been cleaned."
} else {
    Write-Host "Visual Studio projects files clean skipped."
}

cmd /c 'pause'