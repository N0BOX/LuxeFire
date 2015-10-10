# LuxeFire

This project's goal is to create a fiery orange glow/flicker to the inside of a computer case using WS2812 LEDs that respond in brightness, color, and intensity to the CPU or internal case temperature.  Ideas include reading the temperature values from the Linux kernel and passing them from a shell/python/perl script to the Teensy-LC via serial, or possibly by reading the output of the motherboard's PWM (4-pin) case or CPU fan controller output and using those fan speeds to infer the temperature.

As was already mentioned, this project targets the Teensy-LC, which has a 5V level output specifically for use with WS2812 LEDs.  The name "LuxeFire" comes from the case I own, the "Phanteks Enthoo Luxe".
