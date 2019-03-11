#!/bin/bash
#TODO replace cp by mv
if [ $(stat -c "%a" "/usr/local") == "755" ] 
	then 
    	sudo chmod 777 "/usr/local"
      	cp -i -r "cmd_terminal" "/usr/local/test"
      	sudo chmod 755 "/usr/local"
else 
	cp -i -r "cmd_terminal" "/usr/local/test"

fi 
