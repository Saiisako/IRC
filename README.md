# IRC Server

A multi-client IRC server written in C++98, implementing a working subset of the [RFC 1459](https://www.rfc-editor.org/rfc/rfc1459) protocol. Compatible with real IRC clients (tested with `nc`, HexChat, WeeChat).

## Features

- **Non-blocking, single-threaded I/O** using `poll()` to handle an arbitrary number of simultaneous clients on one event loop.
- **Authentication**: server-wide password, `NICK`/`USER` registration flow with proper error codes (`ERR_NICKNAMEINUSE`, `ERR_NEEDMOREPARAMS`, ...).
- **Channels**: `JOIN`, `PART`, `TOPIC`, `INVITE`, `KICK`, with operator-only actions correctly restricted.
- **Channel modes**: invite-only (`+i`), topic lock (`+t`), key (`+k`), user limit (`+l`), operator (`+o`).
- **Messaging**: `PRIVMSG` to users and channels, with correct error replies for unknown targets.
- Robust partial-read handling: TCP messages spanning multiple `recv()` calls are correctly reassembled.

## Build & usage

```bash
make
./ircserv <port> <password>
```

Connect with any IRC client, or manually with netcat:

```bash
nc 127.0.0.1 <port>
PASS <password>
NICK myname
USER myname 0 * :Real Name
```

## Skills demonstrated

Network programming (BSD sockets, non-blocking I/O, `poll`), protocol implementation from an RFC spec, and designing stateful server-side objects (clients, channels, permissions) in C++98 without any external library.

*42 School — Common Core project.*
