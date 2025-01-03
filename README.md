# Mega Man Battle Network 2

This is a disassembly of Mega Man Battle Network 2.

It uses the following ROM as a base:

* Mega Man Battle Network 2 (USA).gba  `md5: 39f8a42133df444eeb7bf0b2194d6286`

## Building

### Manual

Python 3, devkitPro, and make are required. For the Python tools, the pip packages `pypng` and `pycparser` are required and can be installed with `python3 -m pip install -r requirements.txt`.

To build, create a directory called `base`, place the ROM in the directory, and name it `base.gba`.

Then, run `build.py`. The output GBA file will be in the `build` directory.

To clean up all build files, run `build.py clean`. Run `build.py tidy` to only remove built source files and leave built asset files alone. Run `build.py rebuild` to do tidying and building in one step.
