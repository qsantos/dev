Random dev thingies
===================

Just a set of [files](https://en.wikipedia.org/wiki/Everything_is_a_file)
that some might or might not find useful for themselves.

Makefile for KSP mods
---------------------

The [Makefile](Makefile) intends to simplify the compilation of
Kerbal Space Program's mods using standard tools from Linux-based
distributions. It uses mcs to compile files and generates the source
and library dependencies from the provided C# project file (.csproj)
using awk.

To use it, you will need to install the C# base environment (Debian
package `mono-complete`). Copy-paste (or symlink) the Makefile from this
repository in the directory where the project file is. Then, from the
console, simply run make.

The path for KSP's custom DLLs is assumed to be in the default Steam
folder. This can be changed by setting LIBDIR to the appropriate value
at line 17.

Licence
-------

Some files are distributed under the GPL licence (see
[LICENCE.md](LICENCE.md) file). The credits for markdown formatting goes
to https://github.com/IQAndreas/markdown-licenses

If you want to use something from here but your licensing is not
compatible with the GPL licence, contact me at yoha@sinon.org and I might
(quite likely) grant a slacker licencing.
