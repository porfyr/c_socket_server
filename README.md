Спершу компілюється і запускається сервер
```bash
gcc server.c -o server
./server 'port'
```
невернестери вибачайте

Сервер прослуховує 'port', перевірити це можна в другому терміналі командою ```netstat -atn``` або ```ss -atn``` там і запустимо, є 2 путя:
- робота з сервером вручну: через утиліту ```netcat``` або ```nc```
```
nc localhost 'port'
#nc 127.0.0.1 'port'
```
в ```nc``` CLI вводимо всякі гадості або очікувані сервером команди

- або за умовою лаболаторної запустити клієнтський логуючий скрипт ```client.sh```, але він в кінці попросить сервер піти в туман прикритись тучкой
```bash
chmod u+x client.sh
./client.sh
```

Все зроблено максимально кустарно за 1 вечір, хотів би навчитись писати сервер і клієнт здорової людини по всіх стандартах шоб красиво