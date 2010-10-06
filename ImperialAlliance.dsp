# Microsoft Developer Studio Project File - Name="ImperialAlliance" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ImperialAlliance - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ImperialAlliance.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ImperialAlliance.mak" CFG="ImperialAlliance - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ImperialAlliance - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ImperialAlliance - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/ImperialAlliance", RHWBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ImperialAlliance - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release\Profile"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W2 /GX /Zi /Ox /Ot /Oi /Op /I "code" /I "c:\dxsdk\include" /I "C:\Program Files\Microsoft Speech SDK 5.1\Include" /D "_MBCS" /D "HTL" /D "FS2_SPEECH" /D "NDEBUG" /D "_WINDOWS" /D "WIN32" /D "USE_OPENGL" /D "MORE_SPECIES" /U "_DEBUG" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 fmodvc.lib Quartz.lib Dxerr8.lib d3d8.lib d3dx8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib winmm.lib vfw32.lib msacm32.lib comctl32.lib code.lib /nologo /subsystem:windows /map /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcd.lib" /out:"ImperialAlliance.exe" /libpath:"release" /libpath:".\FMOD\\" /libpath:"c:\dxsdk\lib" /libpath:"C:\Program Files\Microsoft Speech SDK 5.1\Lib\i386"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ImperialAlliance - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug\Profile"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /G5 /MTd /W4 /Gm /Gi /GX /ZI /Od /I "code" /I "c:\mssdk\include\\" /I "c:\dxsdk\include" /I "c:\speech_api\include" /I "c:\devil-sdk\include" /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "NO_CD_CHECK" /D "MORE_SPECIES" /U "NDEBUG" /Fr /YX /FD /GZ /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"debug/profile/ImperialAlliance.bsc" "./debug/profile/*.sbr"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 fmodvc.lib Quartz.lib d3d8.lib d3dx8.lib DxErr8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib winmm.lib vfw32.lib msacm32.lib comctl32.lib code.lib Dxerr8.lib d3d8.lib d3dx8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib winmm.lib vfw32.lib msacm32.lib comctl32.lib code.lib Dxerr8.lib d3d8.lib d3dx8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib winmm.lib vfw32.lib msacm32.lib comctl32.lib code.lib Dxerr8.lib d3d8.lib d3dx8.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib winmm.lib vfw32.lib msacm32.lib comctl32.lib code.lib /nologo /subsystem:windows /debug /debugtype:both /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcd.lib" /out:"IA_debug.exe" /libpath:"debug" /libpath:".\FMOD\\" /libpath:"c:\mssdk\lib" /libpath:"c:\dxsdk\lib" /libpath:"c:\speech_api\lib"
# SUBTRACT LINK32 /pdb:none /incremental:no /map

!ENDIF 

# Begin Target

# Name "ImperialAlliance - Win32 Release"
# Name "ImperialAlliance - Win32 Debug"
# Begin Source File

SOURCE=.\code\FREESPACE2\app_icon.ico
# End Source File
# Begin Source File

SOURCE=.\CODE\freespace2\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\code\FREESPACE2\FreeSpace.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FREESPACE2\FreeSpace.h
# End Source File
# Begin Source File

SOURCE=.\code\FREESPACE2\FreespaceResource.h
# End Source File
# Begin Source File

SOURCE=.\code\freespace2\goal_com.bmp
# End Source File
# Begin Source File

SOURCE=.\code\freespace2\goal_fail.bmp
# End Source File
# Begin Source File

SOURCE=.\code\freespace2\goal_inc.bmp
# End Source File
# Begin Source File

SOURCE=.\code\freespace2\goal_none.bmp
# End Source File
# Begin Source File

SOURCE=.\code\freespace2\goal_ord.bmp
# End Source File
# Begin Source File

SOURCE=.\code\graphics\grstub.h
# End Source File
# Begin Source File

SOURCE=.\CODE\freespace2\IAMPDEMO.ico
# End Source File
# Begin Source File

SOURCE=.\CODE\freespace2\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\code\FREESPACE2\ImperialAlliance.rc
# End Source File
# Begin Source File

SOURCE=.\code\FREESPACE2\LevelPaging.cpp
# End Source File
# Begin Source File

SOURCE=.\code\FREESPACE2\LevelPaging.h
# End Source File
# Begin Source File

SOURCE=.\code\network\multiui.cpp
# End Source File
# Begin Source File

SOURCE=.\CODE\POPUP\popuptc.h
# End Source File
# End Target
# End Project
