# TCP Socket Learning

Simple C TCP client/server for learning Linux socket programming.

## Build

```bash
gcc server.c -o server
gcc client.c -o client
```

## Run

```bash
./server
./client
```

Server listens on port `2000`.

## Future Improvements

* Multithreading with `pthread`
* Multiprocessing with `fork()`
* Support multiple clients
