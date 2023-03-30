#!/bin/bash

echo "" > log.txt

# В фігурних дужках вписані стрічки, які шлються на наш сервак, відповідь записується в буферний файл get.txt
{ echo $2; sleep 0.1; echo close; } | nc 127.0.0.1 $1 > get.txt
sleep 0.1s

line=$(head -n 1 "get.txt")

if [[ $line != "2xx" ]] && [[ $line != "3xx" ]]; then
    echo $line > log.txt
fi
