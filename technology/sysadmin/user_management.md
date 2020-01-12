User Management in Ubuntu
==========================

## Useful snippets

<a name="addnewuser"></a>
### Adding a new user 'user2020' (with sudo permissions)
'user2020' is the initial login group of the user.
'sudo' is a supplementary group.

    sudo groupadd user2020      # first create initial login group of the user
    sudo useradd -g user2020 -G sudo -d /home/user2020 -m -s /bin/bash user2020
    sudo passwd user2020        # set a password
