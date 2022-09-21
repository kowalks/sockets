# sockets

Socket programming abstractions for C++. It includes a web client that makes HTTP GET requests to some server and stores received data into local directory. It also includes a web server that listen for HTTP GET requests and serve local files.

# Instructions

The client makes one or more HTTP GET requests to provided URLs and saves received data into local directory.

```
./client url1 [url2 url3 ...]
```

The server listens for HTTP GET requests and send local files to client.

```
./server [host] [port] [dir]
```


