#!/bin/bash

#TODO replace cp by mv
if [ $(stat -c "%a" "/bin") == "755" ] 
	then 
    	sudo chmod 777 "/bin"
      	rm -rf "/bin/test"
      	sudo chmod 755 "/bin"
else 
    rm -rf "/bin/test"
fi 
