# TCP Socket Learning

A simple TCP client and server written in C for learning Linux socket programming.

## Build

```bash
gcc server.c -o server
gcc client.c -o client
```

## Run

Start the server:

```bash
./server
```

Then, in another terminal:

```bash
./client
```

The server listens on port `2000`.

## Concepts

* IPv4 sockets
* TCP
* `socket()`
* `bind()`
* `listen()`
* `accept()`
* `connect()`
* `send()` / `recv()`
* Host vs network byte order
* Client/server communication
