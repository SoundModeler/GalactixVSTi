# Microsoft Developer Studio Project File - Name="MIDI Filter" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MIDI Filter - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MIDI Filter.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MIDI Filter.mak" CFG="MIDI Filter - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MIDI Filter - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MIDI Filter - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MIDI Filter - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /G6 /MT /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /FD -Qipo -Qip -Qprof_use /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /dll /machine:I386 /out:"Output\GalactiX.dll"

!ELSEIF  "$(CFG)" == "MIDI Filter - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /Zp16 /MT /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x410 /d "_DEBUG"
# ADD RSC /l 0x410 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"Output\LS3.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MIDI Filter - Win32 Release"
# Name "MIDI Filter - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AGain.cpp
# End Source File
# Begin Source File

SOURCE=.\AGainMain.cpp
# End Source File
# Begin Source File

SOURCE=.\AudioEffect.cpp
# End Source File
# Begin Source File

SOURCE=.\audioeffectx.cpp
# End Source File
# Begin Source File

SOURCE=.\def.def
# End Source File
# Begin Source File

SOURCE=.\editor.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AEffect.h
# End Source File
# Begin Source File

SOURCE=.\aeffectx.h
# End Source File
# Begin Source File

SOURCE=.\AEffEditor.hpp
# End Source File
# Begin Source File

SOURCE=.\AGain.hpp
# End Source File
# Begin Source File

SOURCE=.\AudioEffect.hpp
# End Source File
# Begin Source File

SOURCE=.\audioeffectx.h
# End Source File
# Begin Source File

SOURCE=.\editor.h
# End Source File
# End Group
# Begin Group "EditorVST"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Interface\ads_bk.h
# End Source File
# Begin Source File

SOURCE=..\Engine\comdo.h
# End Source File
# Begin Source File

SOURCE=..\Exe\CompileType.h
# End Source File
# Begin Source File

SOURCE=..\Interface\curves.hpp
# End Source File
# Begin Source File

SOURCE=..\Interface\dialogN.h
# End Source File
# Begin Source File

SOURCE=..\Interface\digits.hpp
# End Source File
# Begin Source File

SOURCE=..\Interface\EditorVST.hpp
# End Source File
# Begin Source File

SOURCE=..\Interface\fldigits.hpp
# End Source File
# Begin Source File

SOURCE=..\Interface\handles.h
# End Source File
# Begin Source File

SOURCE=..\Interface\keyboard.hpp
# End Source File
# Begin Source File

SOURCE=..\Interface\knob.hpp
# End Source File
# Begin Source File

SOURCE=..\Interface\knobSmall.hpp
# End Source File
# Begin Source File

SOURCE=..\Interface\ledbtn.hpp
# End Source File
# Begin Source File

SOURCE=..\Interface\logopak.h
# End Source File
# Begin Source File

SOURCE=..\Interface\menulist.hpp
# End Source File
# Begin Source File

SOURCE=..\Interface\runtext.hpp
# End Source File
# Begin Source File

SOURCE=..\Interface\waveview.hpp
# End Source File
# Begin Source File

SOURCE=..\Interface\wheel.hpp
# End Source File
# End Group
# Begin Group "Reverb"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\Vc98\Include\Basetsd.h
# End Source File
# Begin Source File

SOURCE=..\Reverb\tuning.h
# End Source File
# End Group
# Begin Group "Engine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Engine\Engine.cpp
# End Source File
# Begin Source File

SOURCE=..\Engine\Engine.hpp
# End Source File
# Begin Source File

SOURCE=..\Engine\fastTrig.h
# End Source File
# Begin Source File

SOURCE=..\Engine\kase_fft.h
# End Source File
# Begin Source File

SOURCE=..\Engine\mmacroses.h
# End Source File
# Begin Source File

SOURCE=..\Engine\pink.h
# End Source File
# Begin Source File

SOURCE=..\Interface\programms.h
# End Source File
# Begin Source File

SOURCE=..\Engine\TuneTables.h
# End Source File
# Begin Source File

SOURCE=..\Engine\wav32.h
# End Source File
# End Group
# End Target
# End Project
