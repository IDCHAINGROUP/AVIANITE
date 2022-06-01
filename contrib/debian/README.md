
Debian
====================
This directory contains files used to package avianitecoind/avianitecoin-qt
for Debian-based Linux systems. If you compile avianitecoind/avianitecoin-qt yourself, there are some useful files here.

## avianitecoin: URI support ##


avianitecoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install avianitecoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your avianitecoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/avianitecoin128.png` to `/usr/share/pixmaps`

avianitecoin-qt.protocol (KDE)

