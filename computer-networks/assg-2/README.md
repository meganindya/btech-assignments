# Assignment 2

## Questions

1. Develop a simple web server which is capable of processing only one request. Develop a simple client which sends a request for an image file (i.e., pgm format) and the server sends the file to the client. The client after receiving the file, inverts it (255-intensity) and sends it to the server. The server after receiving it, displays the inverted image and the original image side by side.

2. Write a client ping program using UDP. The corresponding server will send a pong message back. Determine the delay between when the client sent the ping message and received the pong message. This delay is called the Round Trip Time (RTT). Report the average RTT for 10 such ping messages.

## Example Console Output

### Question 1

#### Server

```
-- socket created successfully
-- socket binded successfully
-- client accepted by server

request for x31_f18.ascii.pgm received from client

FILE FOUND

sending file

image sent

inverted image received

-- socket closed
```

#### Client

```
-- socket created successfully
-- connected to server

requesting x31_f18.ascii.pgm from server

FILE FOUND

receiving file

image received

inverted image sent

-- socket closed
```

### Question 2

#### Server

```
-- socket created successfully
-- socket binded successfully
==========

pong 1
pong 2
pong 3
pong 4
pong 5
pong 6
pong 7
pong 8
pong 9
pong 10

-- socket closed
```

#### Client

```
-- socket created successfully

ping 1 : 1000.899170ms
ping 2 : 1000.664941ms
ping 3 : 1000.700879ms
ping 4 : 1000.770068ms
ping 5 : 1000.640879ms
ping 6 : 1000.913027ms
ping 7 : 1000.669971ms
ping 8 : 1001.104980ms
ping 9 : 1000.795996ms
ping 10 : 1000.697949ms

Average RTT: 1000.785786ms

-- socket closed
```
