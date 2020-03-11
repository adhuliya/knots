Django Notes
==============

## FAQs

### How to check if Django is installed?
The following command will return the version
if django is installed.

    python3 -m django --version

### How to start a webapp project?
In the desired directory run the following command,

    django-admin startproject mysite

This creates the following directory structure,

    mysite/
        manage.py
        mysite/
            __init__.py
            settings.py
            urls.py
            asgi.py
            wsgi.py

Avoid naming projects with the name of common python packages
and modules like, `test`, `django`, ...

### How to run a your project?
Use the default development server as following,

    # Run by default at: http://127.0.0.1:8000/
    python3 manage.py runserver

    # Run at: http://127.0.0.1:8080/
    python3 manage.py runserver 8080

    # Run at: http://0.0.0.0:8080/
    python3 manage.py runserver 0:8080

For more options see [runserver reference](https://docs.djangoproject.com/en/3.0/ref/django-admin/#django-admin-runserver).

