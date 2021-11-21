# HOWTO use slotcar template in Ubuntu-based Linux

1. Download Atmel ATmega Series Device Support (1.7.374) from http://packs.download.atmel.com/

2. Rename Atmel Pack File (atpak) to ZIP:

```
cp Atmel.ATmega_DFP.1.7.374.atpak Atmel.ATmega_DFP.1.7.374.zip
```

3. Extract zip file to `/opt/` folder

```
sudo unzip Atmel.ATmega_DFP.1.7.374.zip -d /opt/Atmel.ATmega_DFP.1.7.374
```

4. Download AVR toolchain and extract it to `/opt/` folder

5. Clone repo

```
git clone https://github.com/tomas-fryza/arduino-slotcar
```

6. Change path to `arduino-slotcar/install` and run avrdude script

```
cd arduino-slotcar/install
sh ./copy-avrduderc-to-home.sh
```

7. Change path to `arduino-slotcar/firmware/arcar`

```
cd ../firmware/arcar
```

8. Change/verify Toolchain and DFP paths in Makefile

```
TOOLCHAIN_PATH = /opt/avr8-gnu-toolchain-linux_x86_64
DFP = /opt/Atmel.ATmega_DFP.1.7.374
```

9. Compile template

```
make all
```

10. Connect slot car to USB, compile and download firmware to AVR

```
make build_and_flash
```

Other useful commands:

```
make miniterm
make clean
```

12. Program your algorithm in `arduino-slotcar/firmware/arcar/src/main.cpp` file, compile and flash the firmware to AVR

### Notes

Default speed is set to 75%

```c
motor.forward(75);
```

All LEDs are turn on

```c
led.forward_left(true);
led.forward_right(true);
led.reverse_left(true);
led.reverse_right(true);
```

Sensor values are read by

```c
imu.readTemp();
imu.readMag();
imu.readGyro();
imu.readAccel();
```

Measured values are sent to UART terminal in 8N1 mode and 38400 Bd. You can view them by `make miniterm` or any terminal such as PuTTY.

```c
printf("deg/s: %3.0f %3.0f %3.0f  |  ", imu.calcGyro(imu.gx), imu.calcGyro(imu.gy), imu.calcGyro(imu.gz));
printf("a [g]: %2.1f %2.1f %2.1f  |  ", imu.calcAccel(imu.ax), imu.calcAccel(imu.ay), imu.calcAccel(imu.az));
printf("B [uT]: %4.0f %4.0f %4.0f  |  ", imu.calcMag(imu.mx) * 100, imu.calcMag(imu.my) * 100, imu.calcMag(imu.mz) * 100);
printf("T [C]: %2.1f\r\n", 25.0 + ((double) imu.temperature) / 16.0);
```
