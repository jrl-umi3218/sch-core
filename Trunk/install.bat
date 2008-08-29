set root_directory=C:\Mehdi\Projects\Libraries
set include_directory=%root_directory%\SCD\include

XCOPY release\*.lib %root_directory%\SCD\lib\*.lib /S /C /I /F /K /Y

XCOPY CD\*.h %include_directory%\CD\ /S /C /I /F /K /Y
XCOPY CD\*.hxx %include_directory%\CD\    /S /C /I /F /K /Y

XCOPY CD_Penetration\*.h %include_directory%\CD_Penetration\   /S /C /I /F /K /Y
XCOPY CD_Penetration\*.hxx %include_directory%\CD_Penetration\    /S /C /I /F /K /Y

XCOPY File_Parsing\*.h %include_directory%\File_Parsing\   /S /C /I /F /K /Y
XCOPY File_Parsing\*.hxx %include_directory%\File_Parsing\    /S /C /I /F /K /Y

::XCOPY Matrix\*Mod.h %include_directory%\Matrix\   /S /C /I /F /K /Y
::XCOPY Matrix\*Mod.hxx %include_directory%\Matrix\    /S /C /I /F /K /Y
::XCOPY Matrix\QuaternionM.h %include_directory%\Matrix\    /S /C /I /F /K /Y
::XCOPY Matrix\SCD_Types.h %include_directory%\Matrix\    /S /C /I /F /K /Y

XCOPY S_Object\*.h %include_directory%\S_Object\   /S /C /I /F /K /Y
XCOPY S_Object\*.hxx %include_directory%\S_Object\    /S /C /I /F /K /Y

XCOPY S_Polyhedron\*.h %include_directory%\S_Polyhedron\   /S /C /I /F /K /Y
XCOPY S_Polyhedron\*.hxx %include_directory%\S_Polyhedron\    /S /C /I /F /K /Y

XCOPY STP-BV\*.h %include_directory%\STP-BV\   /S /C /I /F /K /Y
XCOPY STP-BV\*.hxx %include_directory%\STP-BV\    /S /C /I /F /K /Y