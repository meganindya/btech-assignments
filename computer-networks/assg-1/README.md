# Assignment 1

## Question

Write a simple **`TCP`** `Server` and **`TCP`** `Client`.

## Example Console Output

### C

#### Server

```
-- socket created successfully
-- socket binded successfully

==========
-- server listening on port 4200
-- client accepted by server

CLIENT: Hello
SERVER: Hi
CLIENT: Wanna hear an interesting joke?
SERVER: No
CLIENT: exit?
SERVER: bye

-- server exit

-- socket closed
```

#### Client

```
-- socket created successfully
-- connected to server

CLIENT: Hello
SERVER: Hi
CLIENT: Wanna hear an interesting joke?
SERVER: No
CLIENT: exit?
SERVER: bye

-- client exit

-- socket closed
```

### Python

#### Server
```
starting up on localhost port 4200
waiting for a connection
connection from 127.0.0.1 port 43458

CLIENT: Hi
SERVER: Hey
CLIENT: Wanna hear an interesting joke?
SERVER: no
CLIENT: bye

closing socket
```

#### Client
```
connecting to localhost port 4200

CLIENT: Hi
SERVER: Hey
CLIENT: Wanna hear an interesting joke?
SERVER: no
CLIENT: bye

closing socket
```
