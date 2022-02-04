# rampig
Allocate the requested RAM from the heap and sleep until a signal is received.  Then, give it back and exit to the O/S.

One parameter is required: the amount of memory is expressed in Megabytes (MB).

_NOTE: This program runs only on POSIX systems i.e. Linux, Unix, and MacOS (probably)._

### Build Dependencies

- `gcc`
- MacOS: Xcode? Sorry, I am not a Mac user.
- Windows: Probably not applicable.  I am not a Windows user.

### Build

`make`

### Command Line Execution

`rampig {N}` # where `{N}` = the number of megabytes to allocate from the heap.

If you want rampig to run in background, use the usual ampersand (&) at the end of the command line.

### Termination in Forground

Ctrl-C (same as `kill -2`)

Then, you will see the following message followed by program exit to the O/S:
`rampig: Caught signal 2.`

### Termination in Background

When `rampig` starts, it announces its process identifier (pid) like this:
`rampig: Hello, my process ID = 42.`

So, to force that particular process to exit, do this:
`kill 42`

Another method of killing rampig in background: `killall rampig`

Then, you will see the following message followed by program exit to the O/S:
`rampig: Caught signal 15.`

### Sample Foreground Execution Stdout

`rampig 2000`
```
rampig: Hello, my process ID = 100694.
rampig: Allocating 2000 MB of RAM
rampig: Allocated & intialised 2000000000 bytes.
^C (Ctrl-C)
rampig: Caught signal 2.
rampig: Deallocating 2000 MB of RAM
```
