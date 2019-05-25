Nginx
================

Important Files/Dirs
--------------------

* `/etc/nginx/`: configuration directory
* `/etc/nginx/conf.d/` : user configuration directory (see [SampleServer](#SampleServer))

Important Commands
-----------------------

* `sudo systemctl restart nginx.service`

FAQs
----------------

### Q. How to setup a static file server?

Go to `/etc/nginx/conf.d/` and create a file named `file_server.conf` (any name can be given)

<a name="SampleServer"></a>

    # This is a valid comment.
    # a basic file server serving content from a fixed directory
    # files/directories are html navigatable
    
    server {
      listen *:5052;
      root /home/codeman/.itsoflife/local/tmp/public;
      autoindex on;
    }

Now restart the server `sudo systemctl restart nginx.service`. It will ask for a `Username` but that can be skipped by pressing `enter`.

### How to setup a load balancer (reverse proxy)?
<a name="loadbalancer"></a>

Requirements,
* nginx installed
* a basic server to run on ports `5055, 5056, 5057`, so that load can be balanced between them (see [Bottlpy](https://bottlepy.org/docs/dev/) to quickly run a dynamic server)

Now go to `/etc/nginx/conf.d/` and create a file `load_balancer.conf` with the following content,

    # This is a valid comment.
    # a load balancer to distribute requests to three servers
    #
    # ../nginx.conf copies this content inside http{} automatically
    upstream myapp1 {
        # least_conn; # selects server with least connections
        # ip_hash; # selects server as per hash of user's ip
        # round_robin; selection by default
    
        # server localhost:5055 weight=3; # adds weight to this server
    
        server localhost:5055;
        server localhost:5056;
        server localhost:5057;
    }
    
    server {
        listen 5054;
    
        location / {
            proxy_pass http://myapp1;
        }
    }

Now restart nginx with, `sudo systemctl restart nginx.service` (ignore Username and Password asked by nginx). Now a load balancer server is running at port `5054`.

All you have to do is run three servers at the three ports and see the load getting balanced in a round robin manner. A sample bottle server is given below, (note that they print their port numbers to the user to identify themselves uniquely)

    #!/usr/bin/env python3
    
    from bottle import route, run, template
    import sys
    
    test = ""
    
    @route('/')
    def index(name="World"):
        return template('<b>Hello {{name}}</b> ({{port}})!', name=name, port=test)
    
    # run(host='localhost', port=8080)
    
    if __name__ == "__main__":
      port = sys.argv[1]
      test = port
      run(host='localhost', port=int(port))

Run it three times as follows,

    chmod +x main.py
    nohup ./main.py 5055 &> /dev/null &
    nohup ./main.py 5056 &> /dev/null &
    nohup ./main.py 5057 &> /dev/null &

Now open the browser [`http://localhost:5054`](http://localhost:5054) and keep refresing it to see the three port numbers changing, which shows each time a different server being called.

Don't forget to kill the servers later.

### How to password protect a directory serverd via nginx?

To password protect a directory's content one can create a `.htpasswd` file using the `htpasswd` command in the directory to be protected and then edit the `*.conf` file of the server to include the authentication. For details see below,

Let suppose we are serving the contents of the directory `/home/codeman/.itsoflife/local/tmp/public` folder. Take the following setps,

1. If command `htpasswd` is not installed,

        $ sudo apt-get -y install apache2-utils

2. Create `.htpasswd` file in the directory to be protected, (it will ask for the passwd)

        # note: use -c only when creating the file for the first time, else the older one is overwritten
        $ htpasswd -c /home/codeman/.itsoflife/local/tmp/public/.htpasswd guest

3. Create the `.conf` file for the server as given below,

        # a basic file server serving content from a fixed directory
        # files/directories are html navigatable
        
        server {
          listen *:5052;
          root /home/codeman/.itsoflife/mydata/local/tmp/public;
          autoindex on;
        
          # for authentication: uid: guest, pwd: guest*
          location / {
            auth_basic "TopLevel";
            auth_basic_user_file /home/codeman/.itsoflife/mydata/local/tmp/public/.htpasswd;
          }
        
          # location /testdir is necessary for the authentication to work for sub-directory
          # for authentication: uid: guest1, pwd: guest1*
          location /testdir {
            auth_basic "testdir";
            auth_basic_user_file /home/codeman/.itsoflife/mydata/local/tmp/public/testdir/.htpasswd;
          }
        }

Note: for the sub-directory `testdir` one has to create a separate `.htpasswd` file for a separate
authentication, or one can remove it if only top level authentication is needed.
 
Also see: [this][2].

### How to increase the priority of the nginx process?

Use `nice` and `renice` command. Niceness of a command ranges from highest (-20) to lowest (19) priority. To see the niceness of `nginx` (or any process) see the NI column of the following output,

    $ ps -fl -C "nginx"
    F S UID        PID  PPID  C PRI  NI ADDR SZ WCHAN  STIME TTY          TIME CMD
    1 S root     14691     1  0  80   0 - 35155 -      18:06 ?        00:00:00 nginx: master process /usr/sb
    5 S www-data 14692 14691  0  80   0 - 35898 -      18:06 ?        00:00:00 nginx: worker process
    5 S www-data 14693 14691  0  80   0 - 35814 -      18:06 ?        00:00:00 nginx: worker process
    5 S www-data 14694 14691  0  80   0 - 35814 -      18:06 ?        00:00:00 nginx: worker process
    5 S www-data 14695 14691  0  80   0 - 35814 -      18:06 ?        00:00:00 nginx: worker process

So its niceness is zero, as seen from the column. The niceness can only be changed by the superuser. It can be done in the following ways,

1. Change the niceness using PID,

        $ sudo renice -n -19 -p 14691 -p 14692 # sets niceness to -19

2. Change the niceness using UID,

        $ sudo renice -n -20 -u www-data # sets niceness to -20

   Note that this changes the niceness of all processes of user `www-data`.

See also: [nice/renice tutorial](https://www.thegeekstuff.com/2013/08/nice-renice-command-examples/).

Resources
------------------------

* [NGINX][1]
* [NGINX password protect][2]

[1]: https://www.nginx.com/ "Nginx official site"
[2]: https://www.howtoforge.com/tutorial/basic-http-authentication-with-nginx/


