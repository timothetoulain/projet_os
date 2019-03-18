#!/bin/bash
#TODO replace cp by mv
#TODO allouer memoire pour logiciel
destination=/usr/local
source=cmd_terminal
dirname=command
if [ $(stat -c "%a" "$destination") == "755" ] 
	then 
    	sudo chmod 777 $destination
      	cp -i -r "$source" "$destination/$dirname"
      	sudo chmod -R 777 "$destination/$dirname"

      	sudo chmod 755 "$destination"
else 
	cp -i -r "$source" "$destination/$dirname"
	sudo chmod -R 777 "$destination/$dirname"
fi 
