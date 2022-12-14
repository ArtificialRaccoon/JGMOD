@echo off
rem
rem  Sets up the JGMOD package for building with djgpp, and converting
rem  text files from LF to CR/LF format.
rem

echo Converting JGMOD files to DOS (DJGPP) format...

echo # generated by fixdjgpp.bat > .\src\makefile
echo include makefile.dj >> .\src\makefile

echo # generated by fixdjgpp.bat > .\examples\makefile
echo include makefile.dj >> .\examples\makefile


utod ...\*.bat ...\*.c  ...\*.h ...\*.scr
utod ...\*.txt ...\makefile.* ...\readme.* ...\plugins.*

echo Done!
echo.
