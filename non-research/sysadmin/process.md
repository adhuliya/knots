Processes in Ubuntu
=========================

Important Files
----------------------
* `/proc`

Important Programs
----------------------
* `kill`, `pkill`, `pgrep`
* `bg`, `fg`, `jobs`
* `strace` # trace system calls
* `lsof`
* `netstat -tulpn` # list programs accessing tcp/udp ports
* `auditctl` # audit a program actions or a file or a directory access
* `xdg-open <filename>` # open the `filename` with the default program.

FAQs
------------
### Q. How to list processes listening on port ":8080"?
`sudo lsof -i :8080`

### Q. How to see the files opened by a process?
`sudo lsof | grep 'program-name'`

### Q. How to trace the files accessed by a process?
Note: This command has speed penalty.

    sudo strace -ff -e trace=file -o tracefile su user -c 'mycommand'

The command generated `tracefile.pid` files containing the system calls to access the different files and directories.

A custom command can be found [here][2].

Also see this [stackoverflow question][1].


References
-----------------
* [StackOverflow's File Trace Question][1]
* [Trace files GitHub][2]

[1]: https://unix.stackexchange.com/questions/18844/list-the-files-accessed-by-a-program
[2]: https://gitlab.com/ole.tange/tangetools/tree/master/tracefile
