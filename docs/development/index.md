Development
===========

If desire to contribute to the development of the SDK this page will provide
some details to get started with respect:

- Code Design
- Code Layout
- Tooling

Each of the above topics will be covered in kind in sections below.

Code Design
-----------

The code is composed of several key abstractions with defined responsibilities
to implement the meter plugin framework.

They are as follows:

- Plugin
- Collector
- Parameter
- Measurement
- Event

### Plugin

Plugin is the overall coordinator of the program.

It is responsible for initiating all the key
features that each plugin is responsible for:

- Reading of plugin parameters
- Creating and starting of each of the _Collectors_(discussed later)
- Calling callbacks associated with the users plugin


### Collector

Responsible for collecting measurement data and sending
to a _Measurement_ sink


### Parameter

The plugin delegates the loading and reading to the
_Parameters_


### Measurement

_Measurement_ encapsulates the 4 values required to generate
a measurement:

- Metric Id
- Value
- Source
- Timestamp

Sends to a _Measurement Sink_ which can send a measurement
to standard out to the plugin manager, meter rpc(future), or api(future)

### Event

_Event_ encapsulates the values required required to send
event either to the plugin manager, meter rpc, or API.


To contribute to the SDK's development you can use the vagrant environment provided [here](https://github.com/boundary/vagrant-plugin-c).

Code Layout
-----------

Code layout is simple and naming mirrors the key abstractions:

```
├── AUTHORS
├── COPYING
├── ChangeLog
├── Doxyfile
├── INSTALL
├── LICENSE
├── Makefile.am
├── NEWS
├── README
├── README.md
├── autogen.sh
├── configure.ac
├── docs
│   ├── development
│   │   └── index.md
│   ├── examples
│   │   ├── hello.md
│   │   ├── random.md
│   │   ├── raspberry_pi.md
│   │   └── udp.md
│   ├── getting_started.md
│   ├── index.md
│   ├── install
│   │   └── index.md
│   └── tutorial
│       ├── index.md
│       └── install_meter.md
├── include
│   ├── Makefile.am
│   ├── collector.h
│   ├── common.h
│   ├── event.h
│   ├── log.h
│   ├── measurement.h
│   ├── metric.h
│   ├── param.h
│   └── plugin.h
├── lib
│   ├── Makefile.am
│   ├── collector.c
│   ├── common.c
│   ├── event.c
│   ├── log.c
│   ├── measurement.c
│   ├── metric.c
│   ├── param.c
│   └── plugin.c
└── mkdocs.yml
```

Tooling
-------

Development work requires the installation of the _autoconf_ and _libtools_.

These additional tools can help in with development:

- [jsonlint](https://github.com/zaach/jsonlint) - Validates and beautifies JSON documents
- [grip](https://github.com/joeyespo/grip) - Accurate preview of markdown files for documentation or READMEs
- [mkdocs](http://www.mkdocs.org/) - Documentation framework that uses markdown develop themed documentation

