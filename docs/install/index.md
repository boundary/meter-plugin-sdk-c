Installing the SDK
==================

Prerequisites
-------------

- `wget` to download the tar bundle
- `gcc` to compile meter plugins using the SDK
-  `tar` (GNU tar) to extract the downloaded software bundle

Downloading the SDK
-------------------

**NOTE**: In the instructions that follow at the time of the writing the currently release version of the SDK
was 0.2.0. Check the [release page](https://github.com/boundary/meter-plugin-sdk-c/releases)
for the latest release version.

1. Change directory to a suitable location to download and build the SDK
2. Download a release from GitHub by using `wget` to download the compressed tar file:

    ```
    $ wget https://github.com/boundary/meter-plugin-sdk-c/releases/download/v0.2.0/meter-plugin-0.2.0.tar.gz
    ```

Extracting the SDK
------------------

We use the GNU tar to extract the compressed tar file so that we can build
and installed the SDK

1. Extract the software by running the following:

    ```
    $ tar xvf meter-plugin-0.2.0.tar.gz
    ```
    
Install Dependent Libraries
---------------------------

The SDK depends on a third-party library for handling the parsing of
[JSON](https://en.wikipedia.org/wiki/JSON) configuration files: `plugin.json` and `param.json`.

### Centos/RHEL

```
$ sudo yum install -y jansson-devel
```

### Debian/Ubuntu

```
$ sudo apt-get install -y libjansson-dev
```

### Mac OS X

```
$ brew install jansson 
```

Build and Install the SDK
-------------------------

The meter SDK in C uses the autoconf tools and as such should be able to build on any
[POSIX](https://en.wikipedia.org/wiki/POSIX) environment even Windows using
[Cygwin](https://en.wikipedia.org/wiki/Cygwin) if the prerequisite third-party libraries
are available.

1. Change directory to location where the SDK distribution was previously.

    ```
    $ cd meter-plugin-0.2.0
    ```
    
2. Configure the SDK for the target distribution by running the following:

    ```
    $ ./configure --prefix=/usr
    ```
    
3. Compile meter plugin SDK shared library:

    ```
    $ make
    ```
    
4. Install the meter plugin SDK shared library and include files:

    ```
    $ sudo make install
    ```

