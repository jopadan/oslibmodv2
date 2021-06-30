# OldSchool Library (OSLib) MODv2

This is a modded version of OSLib 2.10 and OSLib MOD

# CURRENT RELEASE

- [OSLib Modv2](https://dl.dropboxusercontent.com/u/12595498/OSLibmodv2_112.zip)

# DOCUMENTATION

You can find the documentation in the Doc directory, or consult it online here:  
http://dogo.github.io/oslibmodv2/

# License

OSLib Modv2 is free software, licensed under the GPLv2; see COPYING for details.

# SUPPORT

You can report bugs and talk about OSLib MODv2 here:  
diautilio@gmail.com

# INSTALL

To install OSLib MODv2  

```c
cmake .
make install
```

or

```c
cp -ar libosl.a to $PSPSDK/lib/  
cp -ar src/*.h in $PSPSDK/include/
```

# STATUS

platform support implemented:

[MIPS R4x00]:
- [pspmips   - Sony Playstation Portable](www.github.com/pspdev/)

platform support planned:

[various]:
- [win       - Microsoft Windows](http://www.microsoft.com/)
- [x11       - UNIX-like X.Org](http://www.x.org/)

[x86_64]:
- [beos      - BeOS/HaikuOS](https://www.haiku-os.org/)
- [kolibrios - KolibriOS](https://www.kolibrios.org/)
- [amiga     - Commodore Amiga/x86_64 AROS](https://aros.sf.net/)

[MIPS R4x00]:
- [pspmips   - Sony Playstation Portable](www.github.com/pspdev/)
- [u64mips   - Nintendo Ultra64 IRIX](http://www.ultra64.ca/)
- [sgimips   - SGI Indigo IRIX](http://www.sgi.com/)

[Motorola m68k]:
- [amiga     - Commodore Amiga/m68k AROS](http://aros.sf.net/)
- [amiga     - Commodore Amiga/m68k MorphOS](http://www.morphos-team.net/)
- [mac68k    - Apple/m68k](http://www.apple.com/)

[IBM PowerPC 970]:
- [macppc    - Apple PowerPC G4/5](http://www.apple.com/)
- [amigappc  - Commodore Amiga/PPC AROS](http://aros.sf.net/)
- [amigappc  - Commodore Amiga/PPC MorphOS](http://www.morphos-team.net/)

[Hitachi SH4]:
- [dreamcast - Sega Dreamcast KallistiOS](http://www.github.com/KallistiOS/)

# THANKS

uppfinnarn for update libpng and makefile  
Strangelove for fixing many bugs  
STAS for tha patch fixing many bugs  
pspZorba for his adhoc sample  
MrMr[iCE] for libpspmath  
InsertWittyName for all the sdk's dialog samples  
Brunni for OSLib  
Sakya for OSLib MOD  
BenHur for intraFont  
