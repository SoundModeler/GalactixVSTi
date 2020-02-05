# GalactixVSTi
GalactiX VSTi Synth from Smartelectronix

An open-source version of GalactiX VSTi plugin written at the time of my membership in great smartelectronix community as Alex @ smartelectronix in 2002. 
I want to thank bram @ smartelectronix  and entire SE team for encouraging talks, tests, advices and fun during the program development.  It is a pity that such a great team was disaggregated then without shaping something good-working.
Later I had new versions of Galactix (with anti-aliased oscillators) but then I lost my access to smartelectronix web site, so this is the latest published version.

You can find the original GalactiX plugin on smartelectronix pages: http://alex.smartelectronix.com

The source code may not look as so well organized and commented because:
1. it was written when I just started to learn and was not so experienced;
2. it was exciting and took only 2 months from start to the release of the final version of GalactiX! 

#GUI
I used my own source code for gui. The logic behind this library is that 
every control corresponds to one class and one .hpp file and therefore there is no resource file in the project.

#Donations
http://paypal.me/Akritov

#Compilation
MC Visual Studio 6.0
There are 2 version for fast VSTi development: 
1/ as cpp.exe file that allows to play the same Galactix as .exe from PC keyboard without VST host app.
2/ and as actual Galectix.dll. The only difference in code is the file compiletype.h
You have to choose by commenting
#define EXE_COMPILE
///#define VST_COMPILE


There is Windows-only version.

#Licensing 
GPL for open source and non-GPL for commercial usage. 
