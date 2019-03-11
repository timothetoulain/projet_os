#!/bin/bash
#TODO replace cp by mv

destination=/usr/local
source=cmd_terminal
dirname=test
if [ $(stat -c "%a" "$destination") == "755" ] 
	then 
    	sudo chmod 777 $destination
      	cp -i -r "$source" "$destination/$dirname"
      	sudo chmod 755 "$destination"
else 
	cp -i -r "$source" "$destination/$dirname"

fi 
