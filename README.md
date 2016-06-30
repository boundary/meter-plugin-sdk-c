Implements a framework in the C programming language to create TrueSight Pulse meter plugins.

### Supported Platforms

Platforms that support a POSIX compiler chain.

### Prequisites

- gcc
- make
- [jansson JSON libary](http://www.digip.org/jansson/)

### Installing Prerequiste Libraries

#### RHEL/CentOs

```
$ yum install -y libjson-glib-dev
``` 

#### Ubuntu

```
$ sudo apt-get install -y libjson-glib-dev
``` 

### Mac OS X

```
$ brew install jansson 
```

### Installing the SDK

1. Download distribution to the target platform:

    ```bash
    $ wget https://github.com/boundary/meter-plugin-sdk-c/releases/download/v0.1.0/meter-plugin-sdk-c-0.2.tar.gz
    ```
2. Extract distribution:

   ```bash
   $ tar xvf meter-plugin-0.2.tar.gz
   ```

3. Change directory to extracted distribution:

   ```bash
   $ cd meter-plugin-0.1.0
   ```

4. Configure meter plugin SDK for compilation

   ```bash
   $ ./configure
   ```

5. Compile meter plugin SDK shared libary:

   ```bash
   $ make
   ```

6. Install plugin meter shared library and includes:

   ```bash
   $ sudo make install
   ```

### Plugin Development

See [Getting Started](getting_started.md)

### Development

To contribute to the SDK's development you can use the vagrant environment provided [here](https://github.com/boundary/vagrant-plugin-c).

