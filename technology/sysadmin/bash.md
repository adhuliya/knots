Bash Shell & Scripting
===============

Important Files
------------------
* `~/.bashrc`
* `~/.bash_profile`

## FAQs

### Q. How to get the size of a file?

    stat --printf='%s' filename   # see: man stat (recommended way)
    cat filename | wc -c          # not recommended

### Q. How to do basic condition tests in bash?
Use the `test` command. See `man test`.
Use its `[[ expr ]]` format with `if`, `for` and `while` constructs.

### Q. What are Basic and Extended regular expressions?

See [`REGULAR EXPRESSION`](http://man7.org/linux/man-pages/man1/grep.1.html#REGULAR_EXPRESSIONS)
section in `man grep`.

Resources
-------------------
* [Bash Cheatsheet](https://devhints.io/bash)
* [GNU Bash Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html)
* [Master your Z Shell][1]
* [Z Shell Arch Wiki][2]
* <https://unix.stackexchange.com/questions/306111/what-is-the-difference-between-the-bash-operators-vs-vs-vs>

[1]: http://reasoniamhere.com/2014/01/11/outrageously-useful-tips-to-master-your-z-shell/
[2]: https://wiki.archlinux.org/index.php/zsh
