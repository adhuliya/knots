Django Notes
===============

## How to get help on Django?
Post a message to [djanog-users][2]
or drop by [#django on irc.freenode.net][3]
to chat with other Django users.

## Summary of commands in the django poll app?

The [`Poll App Tutorial`][1] has the following commands,

    # check if django is installed and its version.
    python3 -m django --version

    # create a project
    django-admin startproject mysite

    # start the development server at localhost only (port 8000)
    python3 manage.py runserver
    # OR to run at all interfaces at a chosen port
    python3 manage.py runserver 0:8000

    # creating an app
    python3 manage.py startapp polls


References
---------------
[1]: https://docs.djangoproject.com/en/2.2/intro/tutorial01/
[2]: https://docs.djangoproject.com/en/2.2/internals/mailing-lists/#django-users-mailing-list
[3]: irc://irc.freenode.net/django

