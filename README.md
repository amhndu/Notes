Notes
========
Notes is a simple musical notes player.
Within the window use the keyboard to play. The numeric row and
alphabetical rows are used.Using each row is equivalent, thus 1, Q, A and Z all play the same note.
The notes get higher from left to right

Command line options:
```
Usage ./notes [OPTIONS]
--help, -h                        Display this text and exit
--note-duration, -d <duration>    Set the note duration in milliseconds
                                  (default: 300)
--sample-rate, -r <rate>          Set the sample in samples per second, higher
                                  means higher quality but also higher load time
                                  (default: 441000)
--namednotesinput, -n             Input/play notes by their names instead.
                                  Available notes: C D E F G A B
                                  Don't use this option if you want more notes
                                  or the positional input (the default)

```

Compiling
==========
Dependencies

* SFML 2+

Build system: cmake 3.1+


On Linux/OS X:

```
cd Notes                        #Go the the project directory
mkdir build/ && cd build/
cmake -DCMAKE_BUILD_TYPE=Release .. && make
./notes                         #Launch
```
Similarly, it should work under Windows as well.

Songs
==========

Try these tunes!

**Twinkle Twinkle**
  ```
  QQTTYYT RREEWWQ TTRREEW TTRREEW QQTTYYT RREEWWQ
  ```
**Happy Birthday**
  ```
  1-1-2-1-4-3- -1-1-2-1-5-4- -1-1-8-6-4-3-2- -8-8-7-4-5-4
  ```
**Harry Potter theme**
  ```
  E-Y-I-U-Y-P-O-U-Y-I-U-Y-U-E
  ```

**Mary had a little lamb**

  In named input method, launch with -n (./notes -n)
  ```
  EDCDEEE DDDEEE EDCDEEE EDDEDC
  ```
