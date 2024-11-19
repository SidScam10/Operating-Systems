#!/bin/bash

echo "--Operations--"
echo "+) Addition"
echo "-) Subtraction"
echo "*) Multiplication"
echo "/)  Division"

read -p "Enter First Number: " n1
read -p "Enter Second Number: " n2
read -p "Enter Operation: " ch

case $ch in
	"+")
		echo "$n1 + $n2 = $(( n1+n2 ))"
	;;
	"-")
                echo "$n1 - $n2 = $(( n1-n2 ))"
        ;;
	"*")
                echo "$n1 * $n2 = $(( n1*n2 ))"
        ;;
	"/")
                echo "$n1 / $n2 = $(( n1/n2 ))"
        ;;
esac
