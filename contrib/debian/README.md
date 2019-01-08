
Debian
====================
This directory contains files used to package kazusilverd/kazusilver-qt
for Debian-based Linux systems. If you compile kazusilverd/kazusilver-qt yourself, there are some useful files here.

## kazusilver: URI support ##


kazusilver-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install kazusilver-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your kazusilver-qt binary to `/usr/bin`
and the `../../share/pixmaps/kazusilver128.png` to `/usr/share/pixmaps`

kazusilver-qt.protocol (KDE)

