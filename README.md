# RenameUnitySoundFiles
Not very useful but neat program to rename some of my files

I had some sound files for a unity project, but I accidentally lost count when I was naming them. This program goes through and renames them to be in proper number order so I can use them easier in my unity scripts. If you want to run it to see it work, here's instruction for the bash scripts:
Sounds/ the master copy of the inccorectly named files
SoundsTemp/ where the renamed files go
rename.c the program
renametest.c I've never used rename() before so this was testing it out
debug.sh
    - runs gdb for debugging
reset.sh
    - Deletes SoundsTemp and creates a copy of Sound
run.sh
    - runs rename.c without debugging
runtest.sh
    - runs renametet.c
valgrind.sh
    - theoretically makes a valgrind report of rename.c, I'm on windows though and didn't feel like figuring out a docker or virtual machine so I just used the gdb and copilot for debugging

Everything else is just executables from gdb or text files for holding file names while program is running
