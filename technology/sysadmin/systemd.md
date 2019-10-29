systemd/journald Daemon
====================

Important files/dirs
----------------------
* `/etc/systemd/system/` : contains **unit** files or links to them (.service, .mount, .socket, .device etc.)
* `/etc/systemd/journald.conf` : configure saving of previous boot logs/msgs
* `/lib/systemd/system/` : contains the unit files that comes with systemd

Important Programs
-----------------------

    systemctl
    systemd-analyze
    journalctl


Important Commands
-----------------------

### Basic commands
* `sudo systemctl <start|stop|restart|reload|status|enable|disable|mask|unmask> nginx.service`

### Viewing system startup information
* `systemd-analyze` : time taken to boot and the target name
* `systemd-analyze blame` : time consumed to start each service

### Viewing the journal logs
* `sudo journalctl` : displays logs
* `sudo journalctl -b` : logs of the current boot only
* `sudo journalctl -k` : only kernel logs, its like `dmesg`
* `sudo journalctl -k -b` : limit the messages to the current boot
* `sudo journalctl -u nginx.service` : messages by the service
* `sudo journalctl -b -u nginx.service` : messages by the service, current boot only

### Quering unit files
* `systemctl list-units <--all>` : lists active units or with `--all` lists all units the systemd has attempted to load.
* `systemctl list-unit-files` : list all the unit files
* `systemctl list-unit-files --type=service` : list all the service unit files
* `systemctl status nginx.service` : check the status of the unit
* `systemctl cat nginx.service` : view the unit file contents
* `systemctl list-dependencies nginx.service` : direct dependencies that have to be started to start nginx.service.
* `systemctl list-dependencies --all nginx.service` : all recursive dependencies that have to be started to start nginx.service.
* `systemctl show nginx.service` : show low level details fo the unit's settings

### Edit unit files
* `sudo systemctl daemon-reload` : must execute after any unit file changes/additions.
* `sudo systemctl edit nginx.service`
* `sudo systemctl edit --full nginx.service`
* sample nginx.service file

        $ cat /etc/systemd/system/multi-user.target.wants/nginx.service       
        # Stop dance for nginx
        # =======================
        #
        # ExecStop sends SIGSTOP (graceful stop) to the nginx process.
        # If, after 5s (--retry QUIT/5) nginx is still running, systemd takes control
        # and sends SIGTERM (fast shutdown) to the main process.
        # After another 5s (TimeoutStopSec=5), and if nginx is alive, systemd sends
        # SIGKILL to all the remaining processes in the process group (KillMode=mixed).
        #
        # nginx signals reference doc:
        # http://nginx.org/en/docs/control.html
        #
        [Unit]
        Description=A high performance web server and a reverse proxy server
        Documentation=man:nginx(8)
        After=network.target
        
        [Service]
        Type=forking
        PIDFile=/run/nginx.pid
        ExecStartPre=/usr/sbin/nginx -t -q -g 'daemon on; master_process on;'
        ExecStart=/usr/sbin/nginx -g 'daemon on; master_process on;'
        ExecReload=/usr/sbin/nginx -g 'daemon on; master_process on;' -s reload
        ExecStop=-/sbin/start-stop-daemon --quiet --stop --retry QUIT/5 --pidfile /run/nginx.pid
        TimeoutStopSec=5
        KillMode=mixed
        
        [Install]
        WantedBy=multi-user.target

### Using Targets (run levels)
* `systemctl list-unit-files --type=target` : list target unit files only
* `sudo systemctl isolate multi-user.target` : change system target/run level
* `systemctl get-default` : get default target level when system boots
* `sudo systemctl set-default multi-user.target` : change the default target
* `systemctl list-dependencies multi-user.target` : units tied to the multi-user.target



FAQs
----------------------

### Q. How to create your own service?
A `.service` file corresponds to each service managed by systemd. A service file by the user goes to the location `/etc/systemd/system/` directory. `man systemd.service` provides the details of the contents of the file. I installed `nginx` and used its `nginx.service` file as sample to create my own service. Remember to run `sudo systemctl daemon-reload` after adding the service file.



Resources
--------------

* [systemd essentials, digitalocean][1]
* [Creating a systemd service][2]
* `man systemd.directives`
* `man systemd.service`

[1]: https://www.digitalocean.com/community/tutorials/systemd-essentials-working-with-services-units-and-the-journal
[2]: https://www.ubuntudoc.com/how-to-create-new-service-with-systemd/
