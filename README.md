kurukuru
========

Open-source clone of the GBA game 'KuruKuru Kuruin'. I still haven't decided if
it's going to be a straight-up clone or original levels, I'm leaning towards the
latter.

In the game you control a little rectangular helicopter, as you naviagte it
through various obstacle courses. The catch is that it's constantly rotating,
making fitting through small gaps hard. This [video](https://youtube.com/watch?v=78eHxHYUmjs)
explains better than I can.

I'd upload a screenshot here if it didn't look so ugly.

Installation
------------
The Makefile is dreadful because I'm really bad at writing them. I'll get 
around to fixing that one day. Typing 'make' should work, you'll need the
[SFML](www.sfml-dev.org/download/sfml/2.1/) development libraries (v2.x), which
might require compiling depending on your distro. I know I had to on Debian.

### TODO: ###
- [x] Fix collision detection because it sucks.
- [ ] Add stuff to put in levels - start and exit gates mostly.
- [ ] Start making actual levels (straight copy from the game or original ones?)
- [ ] Work on graphics (haha).
