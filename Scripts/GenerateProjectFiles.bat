@echo off

pushd ..
Vendor\Premake\Windows\premake5.exe --file=VaelithEngine.lua vs2022

popd
PAUSE