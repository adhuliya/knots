ELF Notes
===================

* [ELF Specification PDF](elf.pdf)


### How to edit binary files in vim?
Refer <https://askubuntu.com/a/786687/777713>.
In short,
* Open a binary file in vim: `vim a.out`
* Press `esc` and enter `:% !xxd` (`:% !xxd -b` for binary)
* Now the file will be a readable format with hex codes displayed.
* You can edit the hex codes.
* Now press `esc` and enter `:% !xxd -r`.
* Now save the file.


Resources
-------------------
* <https://blog.k3170makan.com/2018/09/introduction-to-elf-format-elf-header.html>
* <http://blog.k3170makan.com/2018/09/introduction-to-elf-format-part-ii.html>

