# HOWTO use slotcar template in Ubuntu-based Linux

1. Download Atmel ATmega Series Device Support (1.7.374) from [Microchip Packs Repository](http://packs.download.atmel.com/)

2. Rename Atmel Pack File (atpak) to ZIP:

   ```shell
   cp Atmel.ATmega_DFP.1.7.374.atpak Atmel.ATmega_DFP.1.7.374.zip
   ```

3. Extract zip file to `/opt/` folder

   ```shell
   sudo unzip Atmel.ATmega_DFP.1.7.374.zip -d /opt/Atmel.ATmega_DFP.1.7.374
   ```

4. Install the following packages

   ```shell
   sudo apt-get install git make avrdude putty
   ```

5. Download the latest toolchain AVR 8-bit Toolchain - Linux 64-bit from [Microchip webpage](https://www.microchip.com/en-us/development-tools-tools-and-software/gcc-compilers-avr-and-arm) and extract all files to `/opt/` folder

   ```shell
   sudo tar -xzvf avr8-gnu-toolchain-3.6.2.1778-linux.any.x86_64.tar.gz -C /opt/
   ```

6. Clone this repo

   ```shell
   git clone https://github.com/tomas-fryza/arduino-slotcar
   ```

7. Change path to `arduino-slotcar/install` and run avrdude script

   ```shell
   cd arduino-slotcar/install
   sh ./copy-avrduderc-to-home.sh
   ```

8. Change path to `arduino-slotcar/firmware`

   ```shell
   cd ../firmware
   ```

9. Change / verify Toolchain and DFP paths in Makefile

   ```Makefile
   PREFIX = /opt/avr8-gnu-toolchain-linux_x86_64
   DFP    = /opt/Atmel.ATmega_DFP.1.7.374
   ```

10. Connect slot car to USB, compile and download firmware to AVR

   ```shell
   make build_and_flash
   ```
