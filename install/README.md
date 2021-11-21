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

4. Download AVR toolchain and extract it to `/opt/` folder

5. Clone repo

   ```shell
   git clone https://github.com/tomas-fryza/arduino-slotcar
   ```

6. Change path to `arduino-slotcar/install` and run avrdude script

   ```shell
   cd arduino-slotcar/install
   sh ./copy-avrduderc-to-home.sh
   ```

7. Change path to `arduino-slotcar/firmware`

   ```shell
   cd ../firmware
   ```

8. Change/verify Toolchain and DFP paths in Makefile

   ```shell
   PREFIX = /opt/avr8-gnu-toolchain-linux_x86_64
   DFP = /opt/Atmel.ATmega_DFP.1.7.374
   ```

9. Connect slot car to USB, compile and download firmware to AVR

   ```shell
   make build_and_flash
   ```
