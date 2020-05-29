Django Production Deployment
===============

### Setting up Django and your web server with uWSGI and nginx


## Steps from scratch
[Resource](https://uwsgi.readthedocs.io/en/latest/tutorials/Django_and_nginx.html#configure-nginx-for-your-site)

Our goal is to enable the following interaction sequence:

    the web client <-> the web server <-> the socket <-> uwsgi <-> Django

To do this refer to the resource above and take note of the following
things as well.

### 0. install python virtualenv

    sudo apt-get install python3-venv

    # setup and activate a virtualenv
    python3 -m venv venv  # last argument is the dir name
    source venv/bin/activate
    ...
    deactivate            # leave the virtual env


### 1. install uWSGI

    # can also do this in virtualenv
    sudo apt-get install python3.6-dev  # assuming python 3.6
    pip3 install uwsgi






