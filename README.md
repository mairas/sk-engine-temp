# engine-temp

This repo implements an engine temperature sensor for Signal K using
the SensESP library. Supported hardware is ESP8266 (Wemos d1 mini,
specifically). The temperature measure is done using one-wire DS18B20 sensors.

The code assumes there are three different one-wire sensors on the bus.
Initially, they get randomly assigned to different devices. The addresses then
need to be reassigned to correct devices via the SensESP REST API.
