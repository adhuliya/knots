Z Shell
===============

Important Files
------------------
* `~/.zshrc`
* `~/.zprofile`

## Useful snippets

<a name="sizeofafile"></a>
### Get size of a file

    stat --printf='%s' filename   # see: man stat (recommended way)
    cat filename | wc -c          # not recommended

<a name="zmv"></a>
### zmv usecases
Used to rename files in bulk using patterns,

    autoload zmv        # must be put in .zshrc file
    zmv -n '(*).bin' '$1.jpg'    # `-n` forces dry run output
    zmv -n 'Page(*)/shot.png' 'shot-${1}.png'    # `-n` forces dry run output
    # enter zmv without any arguments to read its help message

Resources
-------------------
* [Master your Z Shell][1]
* [Z Shell Arch Wiki][2]
* [zmv examples][3]

[1]: http://reasoniamhere.com/2014/01/11/outrageously-useful-tips-to-master-your-z-shell/
[2]: https://wiki.archlinux.org/index.php/zsh
[3]: https://gist.github.com/niksmac/77de3f19d1de0e7c20a8a0f5736c837d

