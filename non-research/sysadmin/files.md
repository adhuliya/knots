Important Ubuntu files/dirs
=============================

* `/usr/share/dict` : contains dictionary files with list of words (one per line), e.g. `american-english` which comes from `wamerican` package. `wbritish` package provides `british-english` file.

   On my machine the contents of `/usr/share/dict/words` was exactly the same as `/usr/share/dict/american-english` file. Programs like Firefox and OpenOffice use Hunspell whose dict is stored in the folder `/usr/share/hunspell/`.

   Vim uses its own binary file as dict which can be generated from `.aff` and `.dic` files in the `/usr/share/hunspell/` directory.

Resources
----------------

