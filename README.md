# RTOS
Real Time Operating Systems

[FreeRTOS API Reference](https://freertos.org/a00106.html)

## Get ESP-IDF[](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html#step-2-get-esp-idf)

To build applications for the ESP32, you need the software libraries provided by Espressif in [ESP-IDF repository](https://github.com/espressif/esp-idf).

To get ESP-IDF, navigate to your installation directory and clone the repository with `git clone`, following instructions below specific to your operating system.

Open Terminal, and run the following commands:

```bash
mkdir -p ~/esp
cd ~/esp
git clone --recursive https://github.com/espressif/esp-idf.git
```

ESP-IDF will be downloaded into `~/esp/esp-idf`.

## Set up the tools[](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html#step-3-set-up-the-tools)

Aside from the ESP-IDF, you also need to install the tools used by ESP-IDF, such as the compiler, debugger, Python packages, etc, for projects supporting ESP32.

```bash
cd ~/esp/esp-idf
./install.sh esp32
```

## Set up the environment variables[](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html#step-4-set-up-the-environment-variables)

The installed tools are not yet added to the PATH environment variable. To make the tools usable from the command line, some environment variables must be set. ESP-IDF provides another script which does that.

In the terminal where you are going to use ESP-IDF, run:

```bash
. $HOME/esp/esp-idf/export.sh
```

Note the space between the leading dot and the path!

If you plan to use esp-idf frequently, you can create an alias for executing `export.sh`:

1. Copy and paste the following command to your shell’s profile (`.profile`, `.bashrc`, `.zprofile`, etc.)

   ```bash
   alias get_idf='. $HOME/esp/esp-idf/export.sh'
   ```

   

2. Refresh the configuration by restarting the terminal session or by running `source [path to profile]`, for example, `source ~/.bashrc`.

Now you can run `get_idf` to set up or refresh the esp-idf environment in any terminal session.

## Compiling the Project

```bash
idf.py build
```

... will compile app, bootloader and generate a partition table based on the config.

## Flashing the Project

When the build finishes, it will print a command line to use esptool.py to flash the chip. However you can also do this automatically by running:

```bash
idf.py -p PORT flash
```

Replace PORT with the name of your serial port (like `COM3` on Windows, `/dev/ttyUSB0` on Linux, or `/dev/cu.usbserial-X` on MacOS. If the `-p` option is left out, `idf.py flash` will try to flash the first available serial port.

This will flash the entire project (app, bootloader and partition table) to a new chip. The settings for serial port flashing can be configured with `idf.py menuconfig`.

You don't need to run `idf.py build` before running `idf.py flash`, `idf.py flash` will automatically rebuild anything which needs it.

## Viewing Serial Output

The `idf.py monitor` target uses the [idf_monitor tool](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/idf-monitor.html) to display serial output from Espressif SoCs. idf_monitor also has a range of features to decode crash output and interact with the device. [Check the documentation page for details](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/idf-monitor.html).

Exit the monitor by typing Ctrl-].

To build, flash and monitor output in one pass, you can run:

```bash
idf.py flash monitor
```
