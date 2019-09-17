#!/bin/bash
while true
do
	echo "\nДля работы через консоль нажмите 1, \nдля работы через файл - 2, \nдля завершения - 3"
	read choose
	case $choose in
		1)
			g++ Source/with_console.cpp -o lab1
			./lab1
			;;
		2)
			g++ Source/with_file.cpp -o lab1
			./lab1
			;;
		3)
			return
			;;
	esac
done
