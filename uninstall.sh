#!/bin/bash
destination=/usr/local
dirname=test

if [ $(stat -c "%a" "$destination") == "755" ] 
	then 
    	sudo chmod 777 "$destination"
      	rm -rf "$destination/$dirname"
      	sudo chmod 755 "$destination"
else 
    rm -rf "$destination/$dirname"
fi 
