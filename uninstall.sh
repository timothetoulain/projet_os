#!/bin/bash

if [ $(stat -c "%a" "/usr/local") == "755" ] 
	then 
    	sudo chmod 777 "/usr/local"
      	rm -rf "/usr/local/test"
      	sudo chmod 755 "/usr/local"
else 
    rm -rf "/usr/local/test"
fi 
