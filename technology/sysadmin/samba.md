Filesystem sharing using Samba
================================================

1. Install Samba

        sudo apt-get update
        sudo apt-get install samba

2. Create a samba user and set its password.

        sudo smbpasswd -a <user_name>

   Samba uses separate set of passwords than the system.
   Therefore, to remember use your system password again.

   The `<user_name>` chosen should already exist.
   And the location intended to be shared must be accessibe to the user.

3. Save a copy of `/etc/samba/smb.conf` somewhere
   to restore `smb.conf` in case you wrongly edit it.

4. Edit `/etc/samba/smb.conf` and append the following at the end:
   (one entry for each folder shared)

        [<folder_name>]
        path = /home/<user_name>/<folder_name>
        valid users = <user_name>
        read only = no

5. Restart Samba service.

        sudo service smbd restart

6. Check `smb.conf` for any syntax errors. Run the following command.

        testparm

7. Test the samba server

        sudo apt-get install smbclient
        # List all shares:
        smbclient -L //<HOST_IP_OR_NAME>/<folder_name> -U <user>
        # connect:
        smbclient //<HOST_IP_OR_NAME>/<folder_name> -U <user>

8. Open samba share in nautilus file browser.
   Go to the address bar and type `smb://<host>/[<directory>]


------------------------------------------------
