Useful Ubuntu commands
=============================

### Working with paths

For Posix special characters like `% # ...` see [this resource](http://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_06_02).

    $ FILENAME=/this/is/dir/file.txt.bkp.tgz

    $ basename ${FILENAME}  #same as `print ${FILENAME##*/}`
    file.txt.bkp.tgz

    $ dirname ${FILENAME}
    /this/is/dir

    $ readlink /usr/bin/cc  #read symbolic link
    /etc/alternatives/cc

    $ mkdir -p hello/world  #creates dir sturcture if not already there.

    $ print ${#FILENAME}  #get length of the string
    29

    $ print ${FILENAME#*.}  #removes smallest prefix ('#' = prefix) of pattern `*.`
    txt.bkp.tgz

    $ print ${FILENAME##*.}  #remove largest prefix with pattern `*.`
    tgz

    $ print ${FILENAME%.*}  #remove smallest suffix ('%' = suffix) with pattern `.*`
    /this/is/dir/file.txt.bkp

    $ print ${filename%%.*}  #remove largest suffix with pattern `.*`
    /this/is/dir/file


### File related tests

    # check if file/dir exists
    $ if [[ -e file.txt ]]; then print "present"; else print "absent"; fi

    # check if file is a regular file
    $ if [[ -f file.txt ]]; then print "a file"; else print "not a file"; fi

    # check if file is a directory file
    $ if [[ -d file.txt ]]; then print "a dir"; else print "not a dir; fi


### grep: search pattern and print lines that contain it.

    man grep  #its your best friend

    egrep pattern  #use egrep over grep whenever possible
    grep -E pattern  #same as `egrep pattern`
    egrep -i pattern  #ignore case
    egrep -v pattern  #print lines that don't match

    egrep -A 1 pattern  #print one line After the line matched.
    egrep -B 1 pattern  #print one line Before the line matched.
    egrep -C 1 pattern  #print one line Before and After the line matched.

    egrep -n pattern  #print line numbers
    egrep -r pattern  #recursively search files for pattern (in current directory)

### mktemp: make temporary files

    man mktemp  #good info

    #mktemp always prints the full path of the file/directory created to stdout.

    mktemp  #creates and prints tmp file's abs path (template is /tmp/tmp.XXXXXXXXXX)
    mktemp --tmpdir=/home/codeman  #creates tmp file in the given dir
    mktemp -p /home/codeman  #same as above (short for --tmpdir ...)
    mktemp -t "new.XXX"  #creates file using the given template
    mktemp -d  #create a tmp directory (instead of a regular file)

    mktemp --tmpdir=$XDG_RUNTIME_DIR  #creates tmp file on RAM
    print $XDG_RUNTIME_DIR  #for me output was: /run/user/1000 (provided by systemd)
    #/run/usr is generally aliased to /dev/shm

    # unsafe operation but useful
    basename $(mktemp -u -t "XXXXXXXX")  #get a random 8 letter string (no file created)


Resources
----------------
* man pages are the best resources (always available)

