# frigg

Frigg is a headless browser library project currently in it's very (extremely) early stages designed to introduce a browser like objects for easy control over an underlying chromium browser. The project will be extented to binding with other languages to introduce simple integrations. Frigg is based exclusively off of the chromium embedded framework created by Marshall Greenblatt and if you wish to get a better insight into how to utilize the underlying technologies for your own project feel free to explore [Here](https://bitbucket.org/chromiumembedded/cef).

In this documentation I will give a brief explanation of how to run the project at it's current state and where to look for examples. We'll make an effort to slowly develop this as our own needs evolve so stay tuned.

## Tutorial
The project consists of three folders libcef3/, src/ and samples/. The samples folder contains examples of how to write applications utilzing frigg library to feel free to look through it for functionality examples. the src/ folder contains all of the compilation code and the libcef3/ folder contains a copy of the cef3 library which we just use for compilation.

In order to compile the sampel application and the frigg library for the three instructions bellow. Please refer to the cmake file in order to identify the linking procedures when working on your own application. Also note that currently this library will compile and work exclusively on linux however we will make it compatible with other infrastructures as soon as we get some time to develop it a little better.

```
mkdir build && cd build
cmake ..
make
```
