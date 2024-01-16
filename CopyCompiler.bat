@echo off
set "CompilerName=MIECCompiler_SG"
set "Compiler=%CompilerName%.zip"    
set "QuellDatei=.\Debug\MIECCompiler.exe"
set "WorkingDir=.\Testbench\WorkingDir\%CompilerName%"
set "outDir=.\Testbench\out\%CompilerName%"
set "ZielOrdner=.\Testbench\Compiler_zip"
set "QuellOrdner=.\Testbench\Compiler_zip\MIECompiler" 

echo Loesche alte Konfiguration ...
del /q "%ZielOrdner%\*" 2>nul

echo Loesche Dateien in %WorkingDir% und %outDir%...
rd /s /q "%WorkingDir%" 2>nul
rd /s /q "%outDir%" 2>nul

echo Erstelle den Zielordner %QuellOrdner% und kopiere Dateien...
md "%QuellOrdner%" 2>nul
copy "%QuellDatei%" "%QuellOrdner%"

echo Verpacke den Inhalt von %QuellOrdner% in %CompilerName% ...
powershell Compress-Archive -Path "%ZielOrdner%\*" -DestinationPath "%ZielOrdner%\%CompilerName%"

echo Loesche den Quellordner %QuellOrdner% ...
rd /s /q "%QuellOrdner%"

echo Prozess abgeschlossen.