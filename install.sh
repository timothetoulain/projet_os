#!/bin/bash

if [ $(stat -c "%a" "/bin") == "755" ] 
	then 
    	sudo chmod 777 "/bin"
      	cp -i -r "cmd_terminal" "/bin/test"
      	sudo chmod 755 "/bin"
else 
	cp -i -r "cmd_terminal" "/bin/test"

fi 
