Write-Output "Creating PneumocylinderConfigurator app installer"
Write-Output ""

function Get-DevEnvExecutableFilePath {
    [string]$DevEnvExecutableFilePath = 'D:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\devenv.exe'
    if (!(Test-Path -Path $DevEnvExecutableFilePath)) {
        $DevEnvExecutableFilePath = 'C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\devenv.exe'
    }
    if (!(Test-Path -Path $DevEnvExecutableFilePath)) {
        $DevEnvExecutableFilePath = Read-Host "Enter VS devenv.exe path ($DevEnvExecutableFilePath) or press enter for auto search" 
        $DevEnvExecutableFilePath = (Get-ChildItem $DevEnvExecutableFilePath -Recurse -Filter "devenv.exe" | Select-Object -First 1).FullName
    }
    if (!(Test-Path -Path $DevEnvExecutableFilePath)) {
        $DevEnvExecutableFilePath = 'C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\devenv.exe'
        [bool] $vsSetupExists = $null -ne (Get-Command Get-VSSetupInstance -ErrorAction SilentlyContinue)
        if (!$vsSetupExists) {
            Write-Verbose "Installing the VSSetup module..."
            Install-Module VSSetup -Scope CurrentUser -Force
        }
        [string] $visualStudioInstallationPath = (Get-VSSetupInstance | Select-VSSetupInstance -Latest -Require Microsoft.Component.MSBuild).InstallationPath
        $DevEnvExecutableFilePath = (Get-ChildItem $visualStudioInstallationPath -Recurse -Filter "devenv.exe" | Select-Object -First 1).FullName
    }
    return $DevEnvExecutableFilePath
}

function Get-ISCCExecutableFilePath {
    [string]$ISCCExecutableFilePath = 'D:\Program Files (x86)\Inno Setup 6\ISCC.exe'
    if (!(Test-Path -Path $ISCCExecutableFilePath)) {
        $ISCCExecutableFilePath = 'C:\Program Files (x86)\Inno Setup 6\ISCC.exe'
    }
    if (!(Test-Path -Path $ISCCExecutableFilePath)) {
        $ISCCExecutableFilePath = Read-Host "Enter Inno Setup exe path ($ISCCExecutableFilePath)" 
        $ISCCExecutableFilePath = (Get-ChildItem $ISCCExecutableFilePath -Recurse -Filter "ISCC.exe" | Select-Object -First 1).FullName
    }
    return $ISCCExecutableFilePath
}

$noKernel = 0
$noVision = 0
If (!(Test-Path -Path "..\C3D\Kernel\Release\")) { $noKernel = 1 }
If (!(Test-Path -Path "..\C3D\Vision\Release\")) { $noVision = 1 }
If (!(Test-Path -Path "..\C3D\Kernel\Debug\")) { $noKernel = 1 }
If (!(Test-Path -Path "..\C3D\Vision\Debug\")) { $noVision = 1 }
If (!(Test-Path -Path "..\C3D\Kernel\Include\")) { $noKernel = 1 }
If (!(Test-Path -Path "..\C3D\Vision\Include\")) { $noVision = 1 }
if ($noKernel) { Write-Output "No C3D Kernel" }
if ($noVision) { Write-Output "No C3D Vision" }
if ($noKernel -or $noVision) { 
    Read-Host -Prompt "Press Enter to exit. "
    exit
}

Write-Output "Prepare building Release project"
$DevEnv = Get-DevEnvExecutableFilePath
$BuildReleaseArgs = "..\PneumocylinderConfigurator.sln /build Release"
Write-Output "You entered DevEnv.exe path: $DevEnv"
Write-Output "Start building Release project"
Start-Process -FilePath $DevEnv -ArgumentList $BuildReleaseArgs -Wait
Write-Output "End building Release"
Write-Output ""

Write-Output "Prepare deploying Qt libs"
Write-Output "Here all pathes are in Deploy.bat file"
Write-Output "Start deploying Qt libs"
Start-Process -FilePath ".\Deploy.bat" -Wait
Write-Output "End deploying"
Write-Output ""

Write-Output "Prepare creating Installer file"
[string]$ISCC = Get-ISCCExecutableFilePath
Write-Output "You entered ISCC.exe path: $ISCC"
Write-Output "Start creating Installer file"
Start-Process -FilePath $ISCC -ArgumentList "CreateInstaller.iss" -Wait
Write-Output "End creating Installer"
Write-Output ""

Read-Host -Prompt "Press Enter to exit. "