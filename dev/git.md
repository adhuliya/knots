git notes
====================


## `git config`

Git comes with a tool called git config that lets you get and set configuration variables that control all aspects of how Git looks and operates. These variables can be stored in three different places:

1. /etc/gitconfig file: Contains values applied to every user on the system and all their repositories. If you pass the option --system to git config, it reads and writes from this file specifically. (Because this is a system configuration file, you would need administrative or superuser privilege to make changes to it.)

1. ~/.gitconfig or ~/.config/git/config file: Values specific personally to you, the user. You can make Git read and write to this file specifically by passing the --global option, and this affects all of the repositories you work with on your system.

1. config file in the Git directory (that is, .git/config) of whatever repository you’re currently using: Specific to that single repository. You can force Git to read from and write to this file with the --local option, but that is in fact the default. (Unsurprisingly, you need to be located somewhere in a Git repository for this option to work properly.)

Each level overrides values in the previous level, so values in .git/config trump those in /etc/gitconfig.


You can view all of your settings and where they are coming from using:

    $ git config --list --show-origin

Your identity,

    $ git config --global user.name "John Doe"
    $ git config --global user.email johndoe@example.com

Your Editor,

    $ git config --global core.editor vim

Check you settings, (sensitive to the repository you are in)

    $ git config --list
    $ git config --list --show-origin   # see the origin file of the setting too
    $ git config user.name              # view a specific variable
    $ git config --show-origin user.name   # view a specific variable with origin


## Getting Help

    $ git help <verb>
    $ git <verb> --help
    $ man git-<verb>

...you can try the #git or #github channel on the Freenode IRC server,
which can be found at <https://freenode.net>.


