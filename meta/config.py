#!/usr/bin/env python3
# Copyright (C) 2022 Keyboard Slayer
#
# This file is part of WaifuOS.
#
# WaifuOS is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# WaifuOS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with WaifuOS.  If not, see <http://www.gnu.org/licenses/>.

""" 
Inspired from MUNIX 
https://github.com/cute-engineewing/munix/blob/main/tools/config.py
"""

import sys
import kconfiglib
import menuconfig
import argparse

kconfig = kconfiglib.Kconfig("Kconfig")


def generate_header(dest):
    kconfig.load_config(".config")
    kconfig.write_autoconf(dest, "#pragma once\n")


def generate_make(dest):
    kconfig.load_config(".config")
    kconfig.write_config(dest)


def defconfig():
    kconfig.load_config(".config")
    kconfig.write_config()


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--genheader", action="store", default=None)
    parser.add_argument("--genmake", action="store", default=None)
    parser.add_argument("--menuconfig", action="store_true")
    parser.add_argument("--defconfig", action="store_true")
    args = parser.parse_args()

    if args.genheader is not None:
        generate_header(args.genheader)

    if args.genmake is not None:
        generate_make(args.genmake)

    if args.menuconfig:
        menuconfig.menuconfig(kconfig)

    if args.defconfig:
        defconfig()
