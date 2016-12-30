# Battle Tetris Application Protocol

## Header
- 8 bytes Timestamp
- 2 bytes CMD number, what type of message is this, meaning depends on current client state
- 2 bytes Flags, dependent on CMD and State
- 4 bytes Length of body

## Client States
- 0  = Not Connected
- 10 = In Lobby
- 20 = In Game

## CMD Number grouping:
CMD numbers 64000 and above are reserved for special 'stateless' messages, and should not be used as normal messages.

Numbers 32000 through 63999 are used for messages sent from the server to the client, which the client should be listening for all the time.

Numbers 0 through 31999 are used for messages sent from client to server (i.e requests).

Any responses to requests will have the same CMD number and timestamp.

## Messages
---
### State 0 (Not Connected)
#### Client Requests:
- 0 = CONNECT_WITH_NICKNAME

---
### STATE 10 (In Lobby):
#### Client Requests:
- 0  = LOBBY_GET_USERS
- 10 = LOBBY_SEND_MESSAGE
- 20 = LOBBY_JOIN_QUEUE
#### Server Requests:
- 32000 = LOBBY_PLAYER_JOINED
- 32010 = LOBBY_PLAYER_LEFT
- 32020 = LOBBY_MESSAGE_SENT
- 32030 = LOBBY_MATCH_FOUND

---
### STATE 20 (In Game):
