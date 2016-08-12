Meter Plugin SDK for C Tutorial
===============================

This is a tutorial on how to create a meter plugin using the meter plugin SDK for c.

This meter plugin will query the file system on the Raspberry Pi and output
the internal temperature of the hardware in either degrees Fahrenheit or Celsius

Prerequisites
-------------

- Meter Plugin SDK has been install per instructions provided in
[install](../install/index.md)
- Tooling is in place as described by [Tooling](../development/index.md)
- A [Raspberry Pi](https://www.raspberrypi.org/)
- TrueSight Pulse Meter Installed on Raspberry Pi
(see [Deploy meter on a Raspberry Pi](install_meter.md))

Overview
--------

Here is the high-level overview of the steps to create a meter plugin using
the meter plugin SDK in C.

1. Create a public repository in GitHub for storing the contents of the meter
plugin.
2. Define the metrics to be used by the plugin in `metrics.json`
3. Create the plugin manifest with metadata describing the plugin in `plugin.json`
4. Implement the code of the meter plugin (add callbacks).
5. Build the binary that represents your plugin
6. Add the plugin to your account as a private plugin
7. Install the meter plugin binary on the target system
8. Deploy the plugin to the target system meter

Create GitHub Repository
------------------------

A public GitHub repository is required to store the contents of the meter plugin.
If you need assistance in doing the step see the online tutorial
[here](https://guides.github.com/activities/hello-world/)

Clone the repository to the host where you plan to perform the development
steps. In this particular case it will be the Raspberry Pi.

Metric Definition
-----------------

For this meter plugin there will be a single metric definition that will be used
to display the internal temperature of the Raspberry Pi.

Create a file `metrics.json` in the clone repository using favorite editor with the following contents:

```
{
  "RASPBERRY_PI_TEMPERATURE": {
    "displayName": "Temperature",
    "displayNameShort": "Temperature",
    "description": "Internal temperature of a Raspberry Pi",
    "unit": "number",
    "defaultAggregate": "avg",
    "defaultResolutionMS": 1000
  }
}
```

Add a commit and commit this file to the repository.

Complete details on the format and fields, see
[Metrics Reference](http://boundary.github.io/meter-plugin-developer-guide/user-guide/reference/metrics/)

Plugin Manifest
---------------

The plugin manifest contains meta data about the plugin including how to configure
and run the plugin. In the plugin we developing in this tutorial there are
three input values to the plugin:

- A select that indicates that we want to output either: celsius or fahrenheit
- How often to measure the Raspberry Pi temperature
- Name of the source to be use in the graph display, which defaults to the hostname if
not specified.

For complete details on the format and fields of the plugin manifest `plugins.json`,
see [Plugin Manifest Reference](http://boundary.github.io/meter-plugin-developer-guide/user-guide/reference/manifest/)
