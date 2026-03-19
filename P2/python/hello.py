#!/usr/bin/env python
import curses

scr = curses.initscr()
scr.keypad(0)
curses.noecho()

scr.addstr("hola hola\n")
scr.addstr("un programa Python con ncurses")
scr.refresh()
scr.getch()

curses.endwin()
