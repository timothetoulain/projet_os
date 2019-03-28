#!/bin/bash
make

gcc cmd_terminal/cp2.c -o cmd_terminal/cp2 
gcc cmd_terminal/ls2.c -o cmd_terminal/ls2 
gcc cmd_terminal/mkdir2.c -o cmd_terminal/mkdir2 
gcc cmd_terminal/mv2.c -o cmd_terminal/mv2 
gcc cmd_terminal/rmdir2.c -o cmd_terminal/rmdir2 
gcc cmd_terminal/sizemem.c -o cmd_terminal/sizemem 
gcc cmd_terminal/touch2.c -o cmd_terminal/touch2 
gcc cmd_terminal/unlink2.c -o cmd_terminal/unlink2 
g++ cmd_terminal/cpdir.cpp -o cmd_terminal/cpdir -lstdc++fs
g++ cmd_terminal/mvdir.cpp -o cmd_terminal/mvdir -lstdc++fs

rm -rf *.o 

destination=/usr/local
source=cmd_terminal
dirname=command
if [ $(stat -c "%a" "$destination") == "755" ] 
	then 
    	sudo chmod 777 $destination
      	mv  "$source" "$destination/$dirname"
      	sudo chmod -R 777 "$destination/$dirname"

      	sudo chmod 755 "$destination"
else 
	mv  "$source" "$destination/$dirname"
	sudo chmod -R 777 "$destination/$dirname"
fi 
