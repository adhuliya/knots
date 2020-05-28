postgre sql v9.5
====================

Important Files
---------------------
* `/usr/share/postgressql/9.5/pg_hba.conf` : db local/remote access configurations
* `postgresql.service` : systemd service file (use `locate postgresql.service` to find)
* `psycopg2` python database bindings package  [see this](#psycopg2)-- `pip3 install psycopg2`

Important Commands
--------------------------
* `psql` : the command line postgres client
* `sudo systemctl reload postgresql.service`
* `psql -U hop -W -d hop -h 127.0.0.1 -p 5432` : login via cli to postgres server

Installing on Ubuntu (bionic)
-------------------------

Ref: <https://www.postgresql.org/download/linux/ubuntu/>

1. Create the file `/etc/apt/sources.list.d/pgdg.list` and add a line for the repository

        deb http://apt.postgresql.org/pub/repos/apt/ bionic-pgdg main

2. Import the repository signing key, and update the package lists

        wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
        sudo apt-get update

3. Now install postgresql and pgadmin

        apt-get install postgresql-11 pgadmin4


Starting `psql` client
--------------------------

    sudo -i -u postgres psql

`postgres` is the default database administrator created on install. The above command switches to the user `postgres` and invokes `psql`. Since the user name is `postgres` the postgresql assumes its own user (with the same name) `postgres` is trying to login.

Postgres Roles
------------------------

Refer [here][1].

> Tip: It is good practice to create a role that has the CREATEDB and CREATEROLE privileges, but is not a superuser, and then use this role for all routine management of databases and roles. This approach avoids the dangers of operating as a superuser for tasks that do not really require it.

Postgres has a uniform concept of `roles`. A `user` is a `role` with login priviledges. One role can be a member of another role.

    -- some commands for reference

    CREATE ROLE name SUPERUSER;
    CREATE ROLE name LOGIN;
    CREATE ROLE name CREATEDB CREATEROLE; -- good practice to use this role

    ALTER ROLE name RENAME TO new_name; -- rename role
    ALTER ROLE name WITH PASSWORD 'passwd'; -- change password
    ALTER ROLE davide WITH PASSWORD NULL;   -- remove password

    -- role1 will INHERIT the group_role permissions unless group_role has NOINHERIT set.
    -- by default a role is always has INHERIT enabled.
    GRANT group_role TO role1, ... ;
    REVOKE group_role FROM role1, ... ;

    CREATE ROLE joe LOGIN INHERIT;
    CREATE ROLE admin NOINHERIT;
    CREATE ROLE wheel NOINHERIT;
    GRANT admin TO joe;
    GRANT wheel TO admin;

    SET ROLE name; -- switch role to 'name'
    RESET ROLE;    -- return to the default role permissions of the login role


    -- allow rolename to work only on 'database_name'
    REVOKE connect ON DATABASE database_name FROM PUBLIC; -- run once as superuser
    REVOKE CONNECT ON DATABASE template1 FROM PUBLIC; -- run once as superuser
    GRANT connect ON DATABASE database_name TO rolename;



FAQ's
------------------------

### Q. How to comment?

    postgres=# -- this comment ends with newline

    postgres=# /* this can fit anywhere */


### Q. How to gather role related information?

    postgres=# SELECT * from pg_roles; 
    postgres=# -- or
    postgres=# \du


### Q. How to create a user with its login and default database?

    $ # start psql
    $ sudo -i -u postgres psql

    postgres=# -- inside psql
    postgres=# CREATE ROLE hop;
    CREATE ROLE
    postgres=# ALTER ROLE hop WITH CREATEDB CREATEROLE LOGIN ENCRYPTED PASSWORD 'anshuisneo';
    ALTER ROLE
    postgres=# -- change user to hop
    postgres=# SET ROLE hop;
    SET
    postgres=# SELECT current_user; -- confirms the current user
     current_user 
    --------------
     hop
    (1 row)

    postgres=# CREATE DATABASE hop; -- db with same name as user's is a convenience.
    postgres=# \c hop;  -- connect to db hop
    You are now connected to database "hop" as user "postgres".
    hop=#


### Q. How to login as the newly created user `hop`?

    $ # login to postgresql using psql
    $ # -U hop          : user is hop
    $ # -W              : prompt for password
    $ # -d hop          : connect to database hop
    $ # -h 127.0.0.1    : explicitly network login to the db
    $ # -p 5432         : port number. Default 5432.
    $ psql -U hop -W -d hop -h 127.0.0.1 -p 5432
    Password for user hop: 
    psql (9.5.12)
    SSL connection (protocol: TLSv1.2, cipher: ECDHE-RSA-AES256-GCM-SHA384, bits: 256, compression: off)
    Type "help" for help.

    hop=> -- inside psql connected to db hop as user hop


### Q. How to create a read-only user `hopro` for the db `hop`?

    $ # start psql as user hop
    $ psql -U hop -W -d hop -h 127.0.0.1 -p 5432

    hop=> -- create the user if not exists
    hop=> CREATE ROLE hopro LOGIN ENCRYPTED PASSWORD 'anshuisneoro';
    CREATE ROLE
    hop=> -- add default priviledges for hopro
    hop=> ALTER DEFAULT PRIVILEGES IN SCHEMA public GRANT SELECT ON TABLES TO hopro;
    ALTER DEFAULT PRIVILEGES
    hop=> -- do the following for all the existing objects
    hop=> GRANT CONNECT ON DATABASE hop TO hopro;
    GRANT 
    hop=> GRANT USAGE ON SCHEMA public TO hopro;
    GRANT 
    hop=> GRANT SELECT ON ALL TABLES IN SCHEMA public TO hopro;
    GRANT 
    hop=>


### Q. How to delete a role?

    hop=> DROP ROLE name; -- drops only if the role 'name' doesn't own any object.
    hop=> ALTER TABLE bobs_table OWNER TO alice; -- change ownership of tables


### Q. How to view tables in a database?

    hop=> \z -- when in interactive session

    hop=> -- or

    hop=> SELECT table_name FROM information_schema.tables WHERE table_schema='public';


### Q. How to describe a table?

    hop=> \d+ tablename


### Q. How to switch database?

    postgres=# \c hop -- or \connect hop
    You are now connected to database "hop" as user "postgres".
    hop=#


### Q. How to dump a database or its info or just data or both?

    $ # dump database and schema object definitions
    $ # -F p        : output in plain sql format (not suitable fot pg_restore)
    $ pg_dump -U hop -W -F p -h 127.0.0.1 hop -p 5432 > hop.db.sql

    $ # dump only the database schema object definitions
    $ # -F t        : output in plain sql format (not suitable fot pg_restore)
    $ pg_dump -U hop -W -F t -h 127.0.0.1 -p 5432 --schema-only hop > hop.schema.sql

    $ # dump only the data from database hop
    $ pg_dump -U hop -W -F p -h 127.0.0.1 -p 5432 --data-only hop > hop.data.sql


### Q. How to restore a database `hop` from its dump?

    $ # enter as postgres user
    $ sudo -i -u postgres psql

    postgres=# DROP DATABASE hop;
    DROP
    postgres=# SET ROLE hop;
    SET
    postgres=# CREATE DATABASE hop; -- user 'hop' should be the owner of the db
    CREATE DATABASE
    postgres=# \q -- quit

    $ # on command line
    $ # assuming plain sql dump file
    $ psql -U hop -W -d hop -h 127.0.0.1 < hop.db.sql

    # some errors like
    # ERROR:  must be owner of extension plpgsql
    # will be shown, which can be safely ignored.

<a id="psycopg2"></a>
## `psycopg2`
[`psycopg2`](https://www.psycopg.org/)
python database bindings package. It can be installed as,

    sudo apt-get update libpq-dev
    pip3 install psycopg2


References
---------------
* [Postgres Tuturial][5]
* [Postgres Doc User-manag][1]
* [Digital Ocean -- Install Postgres][2]
* [Practical Tips][3]
* [pgAdmin Install Method 2][4]

[1]: https://www.postgresql.org/docs/9.2/static/user-manag.html
[2]: https://www.digitalocean.com/community/tutorials/how-to-install-and-use-postgresql-on-ubuntu-16-04
[3]: https://severalnines.com/blog/postgresql-privileges-user-management-what-you-should-know
[4]: https://medium.com/@philip.mutua/postgresql-install-pgadmin-4-desktop-mode-in-ubuntu-16-04-6faca19f0cfe
[5]: http://www.postgresqltutorial.com/


