Kerbal Space Program dev tools
==============================

General description
-------------------

This is a set of stuff that might or might not be useful for people
developing mods for Kerbal Space Programs on a Linux-based distribution.

Makefile
--------

The [Makefile](Makefile) intends to simplify the compilation of mods using
standard tools. It uses mcs to compile files and generates the source
and library dependencies from the provided C# project file (.csproj)
using awk.

To use it, you will need to install the C# base environment (Debian
package mono-complete). Copy-paste (or symlink) the Makefile from this
repository in the directory where the project file is. Then, from the
console, simply run make.

The path for KSP's custom DLLs is assumed to be in the default Steam
folder. This can be changed by setting LIBDIR to the appropriate value
at line 17.

Licence
-------

This program is distributed under the GPL licence (see
[LICENCE.md](LICENCE.md) file). The credits for markdown formatting goes
to https://github.com/IQAndreas/markdown-licenses
