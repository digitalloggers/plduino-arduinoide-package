# plduino-arduinoide-package
A package for Arduino IDE adding better PLDuino PLC support.

To use:

- Install the latest Arduino IDE.
- Run Arduino IDE, open Settings, then add two items into *Additional Boards Manager URLs*:
    https://raw.githubusercontent.com/ddrd/tmp-plduino-arduino/master/dist/package_PLDuino_index.json
    http://arduino.esp8266.com/stable/package_esp8266com_index.json
- Open *Tools > Board > Boards Manager...*
- Install **esp8266** package. Please choose v2.3.0.
- Install **PLDuino/ESP-02** and **PLDuino/Mega2560** packages.

Two boards: **PLDuino/ESP-02** and **PLDuino/Mega2560** must appear in *Tools > Board* list.

It supports Windows, OSX/macOS and Linux (i686, x86_64) operating systems.
