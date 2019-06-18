# dbaa-linux
Linux scripts and things for setting up linux boxes for DBAA

## Linux users

My standard practice so far has been to create a user with admin priveleges called `dbaa` and a regular user called `player`. I also create a group called `players` that both users are a members of. 

All important files (the games, source, scripts) should be owned by`dbaa` and have group ownership by `players` with permissions rwxr-xr-- (This should be `chmod 754`).  
