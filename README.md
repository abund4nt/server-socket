# server-sockets

TCP server written in C using sockets to receive connections, the client was written in Python using sockets as well, over time clients will be added to demonstrate how programming languages communicate via sockets.

![](https://media.geeksforgeeks.org/wp-content/uploads/Socket_server-1.png)

## Usage

Compile server.

```
gcc server.c -o server
```

Usage server.

```
./server
```

![](https://media.geeksforgeeks.org/wp-content/uploads/Socket_server-1.png)

Usage client.

```
python3 client.py 127.0.0.1 8010
```

PoC:

![](src/pwn_00003.mp4)
