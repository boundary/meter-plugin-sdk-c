# Meter Plugin SDK for C

Provides a framework for building TrueSight Pulse meter plugins using the C
programming language.

version 0.2.0

## SDK Features

- Uses autoconf so that code should be portable to all [POSIX](https://en.wikipedia.org/wiki/POSIX) environments or
those that can be made a POSIX environment (e.g. [Cygwin](https://www.cygwin.com/) on Windows)
- Developed plugins register call backs for implementation. For example you register a
function to be called on regular basis for collecting measurements to be send to the plugin
manager
- First release is single-threaded, making it low overhead, but requires that when implementing
a plugin with multiple collectors that the be efficient in their collection since only a single
collectors is invoked at a time.


## Future Enhancements

- Ability to enable multi-threaded collection capability. This will require that the target
platform implement [POSIX threads](https://en.wikipedia.org/wiki/POSIX_Threads).
- Built in support for data sources that are able extract data from: REST endpoints, running a
command or script, TCP/UDP sockets, syslog, etc.
- Event driven collect where by the foreign system runs the collector when data is available
rather than polling.


