Installing a meter on a Raspberry Pi
====================================

At the time of this writing there existed a meter package that is capable
of running on the Raspbian in a Raspberry Pi. The standard setup_meter.sh
calls upon a back end repository that is currently not equiped to deploy
the meter using the this script.

The current working around is run the following commands on the Raspberry Pi:

1. Set the environment variable `INSTALLTOKEN` and export your accounts API key:

    ```
    export INSTALLTOKEN=051c18f6-b143-4b4f-8010-746f6a67fde7 # Replace with your accounts API token
    ```

2. Run the following command to install the meter:

    ```
    $ curl -fsS 'https://gist.githubusercontent.com/jdgwartney/07cb3eab201755245f2905b6bc45ecd2/raw/a5733275cc9259a0453030863bb21cff1850c790/pi-install.sh | bash 
    ```