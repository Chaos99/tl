# tl
#### Painless timelapsing to show off your productivity.

**tl** progressively captures and encodes screenshots to an MP4 file. Unlike
other timelapse tools, it doesn't store thousands and thousands of images only
to encode them later. **It captures and encodes in realtime!** It *won't* thrash
your disk with gigs upon gigs of screenshots, and it *won't* record at 30 fps
when you only really need 1.

It's a great way to show off how productive you are! Plus it looks cool! So
hit record and start up a coding session! Or boot up Photoshop (or more likely
Gimp) and start drawing!

Check out [this demo](https://vimeo.com/133315382).

## Compiling from scratch
#### Download the required libraries:

##### Arch Linux:
```bash
$ pacman -S ffmpeg libx11
```

(If you know the correct packages for your distro, please submit a pull
request and I'll add it.)

#### Then just run:
```bash
$ make
$ ./tl --help
$ ./tl
```

#### To install:
```bash
$ make install
# or...
$ make install PREFIX=/usr/local
```

# Contributing
Feel free to submit any ideas, questions, or problems by reporting an issue.
Or, if you're feeling bit brave, submit a pull request. :grimacing:

## Packages
Sorry, no packages are available yet.

## Todo
* ~~Figure out how to encode an h.264 stream directly into an MP4 container.~~
* Recompress the video at the end. (Basically `ffmpeg -i in.mp4 -c:v libx264 out.mp4` but using the API.)
* Maybe add a GUI?
* Somehow support Mac OS X *and* Windows...
* Support drawing a capture box (or even just defining a capture box.)

## Notes
There is a C++ branch that you can checkout. I prefer to stick with C, but we
may need to move to C++ in order to support other OSes or GUIs. The C++ branch
compiles fine, but as of now, is a little out of date.

## License
MIT License - see the [LICENSE](https://raw.githubusercontent.com/ryanmjacobs/tl/master/LICENSE)

Copyright (c) 2015 Ryan Jacobs