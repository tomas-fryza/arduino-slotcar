# HOWTO use slot car template in Ubuntu-based Linux

1. Start Visual Studio Code and open folder with local `arduino-slotcar` repository.

2. In menu **Terminal**, open **New Terminal Ctrl+Shift+;**, and change path to `arduino-slotcar/firmware`:

   ```bash
   cd firmware
   ```

3. Compile template:

   ```bash
   make all
   ```

   Connect slot car to USB, compile and download firmware to AVR:

   ```bash
   make build_and_flash
   ```

   Other useful commands:

   ```bash
   make clean
   make size
   make list
   ```

4. Program your algorithm in `arduino-slotcar/firmware/main.cpp` file, compile and flash the firmware to AVR.

## Notes to `main.cpp` code

Default motor speed is set to 75%:

```c
motor.forward(75);
```

All LEDs are turn on:

```c
led.forward_left (true);
led.forward_right(true);
led.reverse_left (true);
led.reverse_right(true);
```

Sensor values are read by:

```c
imu.readTemp();
imu.readMag();
imu.readGyro();
imu.readAccel();
```

Measured values are sent to UART terminal in 8N1 mode and 38400 Bd. You can view them by any terminal such as PuTTY.

```c
usb_printf("deg/s : %3.0f %3.0f %3.0f |  ", imu.calcGyro(imu.gx),    imu.calcGyro(imu.gy),    imu.calcGyro(imu.gz));
usb_printf("a [g] : %2.1f %2.1f %2.1f |  ", imu.calcAccel(imu.ax),   imu.calcAccel(imu.ay),   imu.calcAccel(imu.az));
usb_printf("B [uT]: %4.0f %4.0f %4.0f |  ", imu.calcMag(imu.mx)*100, imu.calcMag(imu.my)*100, imu.calcMag(imu.mz)*100);
usb_printf("T [C] : %2.1f\r\n", 25.0 + ((double) imu.temperature)/16.0);
```
