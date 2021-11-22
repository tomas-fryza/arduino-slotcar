# HOWTO use slot car template in Microchip Studio

1. Start Microchip Studio and create a new `GCC C++ Exacutable Project`.

   ![Microchip Studio new project](images/new_project_type.png)

2. Select `ATmega328PB` device.

   ![Microchip Studio device](images/new_project_device.png)

3. To the newly created project folder, copy all source and header files from this repository. In **Solution Explorer** click on the project name, then in menu **Project**, select **Add Existing Item... Shift+Alt+A** and add all source and header files.

   ![Microchip Studio add items](images/new_project_add_items.png)

4. Build project in menu **Build > Build Solution F7**.

5. Connect a slot car to USB cabel and in menu **Tools** select **Send to Arduino SlotCar** to flash the firmware.

6. Start PuTTY, open serial communication with the slot car (mode 8N1, 38400 Bd) and receive sensor values.

   ![Configure PuTTY](../install/images/putty_config_serial.png)

7. Program your algorithm in `arduino-slotcar/firmware/main.cpp` file, compile and flash the firmware to AVR.

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
