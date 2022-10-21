@echo "Deploying PneumocylinderConfigurator"

:: Путь к папке с деплоером windeployqt.exe, QtDir - переменная среды, должна быть заранее задана
set Qt_BinDir=%QtDir%\bin
:: Путь к папке этого проекта, %cd% - текущая папка
set PneumocylinderConfigurator_OutDir=%cd%\..\x64\Release

cd "%Qt_BinDir%"
start windeployqt.exe "%PneumocylinderConfigurator_OutDir%\PneumocylinderConfigurator.exe"
