# dbaa-linux
Linux scripts and things for setting up linux boxes for DBAA

## Linux users

My standard practice so far has been to create a user with admin priveleges called `dbaa` and a regular user called `player`. I also add dbaa to the group `player`

All important files (the games, source, scripts) should be owned by`dbaa` and have group ownership by `player` with permissions `rwxr-xr--` (This should be `chmod 754`).  


## game autostart
Save games in `/home/player/games/[name of game]`.

To have game autostart link `/home/player/game.start` to the game's startup file with 

```
ln -sf /full/path/to/game /home/player/game.start
```