# Hangman - CP/M version

This is a C implementation for CP/M of the classic "hangman" included in "bsdgames" popular package for UNIX.

## History
I just wanted to port to C language my library [XTerm for Modula-2](https://github.com/sblendorio/mod-xterm-cpm), and I needed something to do with it. During a funny Facebook thread a friend of mine showed his version of "hangman" using sicilian words, so I decided that "hangman" would be the first project using the [C port of XTerm](https://github.com/sblendorio/c-xterm-cpm).

## Suported platforms
Although it's basically a CP/M project, the C language is portabile, so I wrote source in order to make it compatible with following platforms:

- CP/M-80 (with HI-TECH C Compiler 3.09)
- POSIX (with GCC)
- Amiga (with SAS/C Compiler 6.58)

## Using compilers

### CP/M-80, HI-TECH C
```
c -lf hangman.c xterm.c
```

### POSIX, GCC
```
gcc hangman.c xterm.c
```

### Amiga, SAS/C
```
sc math=standard hangman.c xterm.c link to hangman
```

## Contents of package
- **source** - Source code in Turbo Modula-2 (despite the name ".BAS")
 - [**xterm.h**](https://github.com/sblendorio/hangman-cpm/blob/master/source/xterm.h) - XTerm Library: header file (for terminal portability)
 - [**xterm.c**](https://github.com/sblendorio/hangman-cpm/blob/master/source/xterm.c) - XTerm Library: implementation module
 - [**hangman.c**](https://github.com/sblendorio/hangman-cpm/blob/master/source/hangman.c) - Main module (run this)
 - [**words.txt**](https://github.com/sblendorio/hangman-cpm/blob/master/source/words.txt) - Sample set of words used in the game
- **binary** - Compiled .COM executable files for CP/M-80
 - [**hangman.com**](https://github.com/sblendorio/hangman-cpm/blob/master/binary/hangman.com?raw=true) - Binary executable file for CP/M-80
 - [**hangman.com**](https://github.com/sblendorio/hangman-cpm/blob/master/binary/hangman-for-amiga?raw=true) - Binary executable file for Amiga computers
 - [**words.txt**](https://github.com/sblendorio/hangman-cpm/blob/master/source/words.txt) - Sample set of words used in the game
- **dists** - Collection of CP/M (and Amiga) bootable disk images
 - [**hangman.d71**](https://github.com/sblendorio/hangman-cpm/blob/master/dists/hangman.d71?raw=true) - Includes C128 CP/M boot code, all sources and binaries, some utilities
 - [**hangman.d64**](https://github.com/sblendorio/hangman-cpm/blob/master/dists/hangman.d64?raw=true) - Includes C128 CP/M boot code, all sources and binaries
 - [**hangman.adf**](https://github.com/sblendorio/hangman-cpm/blob/master/dists/hangman.d64?raw=true) - Includes Amiga boot code, all sources and binaries
 - [**hangman.mfloppy**](https://github.com/sblendorio/hangman-cpm/blob/master/dists/hangman.mfloppy?raw=true) - Includes Memotech MTX CP/M boot code and binaries (Memotech type 07 disk image)
 - [**hangman-msx.dsk**](https://github.com/sblendorio/hangman-cpm/blob/master/dists/hangman-msx.dsk?raw=true) - Includes MSX-DOS boot code and binaries (MSX-DOS disk image)
 - [**hangman-cpc.dsk**](https://github.com/sblendorio/hangman-cpm/blob/master/dists/hangman-cpc.dsk?raw=true) - Includes CP/M for Amstrad CPC6128 boot code and binaries (CPC CP/M disk image)

##Credits
Thanks to [Gabriele Asbesto Zaverio](http://museo.freaknet.org/it/) for the idea.

##Screenshots on Commodore 128
###Terminal choosing
![C128 version](http://www.sblendorio.eu/images/hangman-c128a.png)
###Game screen
![C128 version](http://www.sblendorio.eu/images/hangman-c128b.png)

##Screenshots on Amiga
###On Amiga OS 1.3
![OS13](http://www.sblendorio.eu/images/hangman-amigaos13.png)
###On Amiga OS 3.1
![OS13](http://www.sblendorio.eu/images/hangman-amigaos13.png)

##Screenshot on CP/M emulator on Mac OS X
![OSX](http://www.sblendorio.eu/images/hangman-cpmosx.png)
