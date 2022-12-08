
/* Includes ----------------------------------------------------------*/
#include "settings.h"

#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC

#include "i2c.h"
#include "led.h"
#include "usb.h"
#include "motor.h"
#include "bluetooth.h"

#include "LSM9DS1.h"
#include "LSM9DS1_registers.h"

#include "wyk_stdio.h"

volatile uint8_t speed = 85;

/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Init communications, set default motor speed to 75%, 
 *           turn all LEDs, read sensor values, and send them via UART.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    LSM9DS1 imu;
    Motor motor;

    // bluetooth_servise();
    usb_init();
    bluetooth_init();
    i2c_init();
    _delay_ms(100);

    // Timer0: presc=1024, overflow enable, OVF=1/16M * 256 * 1024 = 16.4 msec
    TCCR0B |= (1<<CS02) | (1<<CS00);
    TIMSK0 |= (1<<0);

    // Timer1: presc=64, overflow enable, OVF=1/16M * 2^16 * 64 = 262 msec
    TCCR1B |= (1<<CS11) | (1<<CS10);
    // TIMSK1 |= (1<<0);

    // sei();

    // Set default speed
    motor.forward(speed);
    usb_printf("speed: %d\r\n", speed);

    // Turn on all LEDs
//    led.forward_left(true);
//    led.forward_right(true);
//    led.reverse_left(true);
//    led.reverse_right(true);

    // Init communication with sensors
    if (!imu.begin())
    {
        usb_puts((char *) "Failed to communicate with LSM9DS1.\n");
        while (1);
    }
    imu.calibrate();

    // Infinite loop
    while (1)
    {
        // motor.forward(speed);

        // Read values from sensors
        // imu.readTemp();
        // imu.readMag();
        imu.readGyro();
        imu.readAccel();

        // Just for testing. Use any terminal, such as PuTTY in 8N1 mode, 38400 Bd
        usb_printf("deg/s:  %3.0f %3.0f %3.0f  |  ", imu.calcGyro(imu.gx),    imu.calcGyro(imu.gy),    imu.calcGyro(imu.gz));
        usb_printf("a [g]:  %2.1f %2.1f %2.1f  |  \r\n", imu.calcAccel(imu.ax),   imu.calcAccel(imu.ay),   imu.calcAccel(imu.az));
        // usb_printf("B [uT]: %4.0f %4.0f %4.0f  |  ", imu.calcMag(imu.mx)*100, imu.calcMag(imu.my)*100, imu.calcMag(imu.mz)*100);
        // usb_printf("T [C]:  %2.1f\r\n", 25.0 + ((double) imu.temperature)/16.0);


        // Some speed tests:)
/*        speed++;
        if (speed >= 95)
            speed = 40;
        if (speed > 80) {
            led.forward_left (true);
            led.forward_right(true);
            led.reverse_left (true);
            led.reverse_right(true);
        } else if (speed > 60) {
            led.forward_left (true);
            led.forward_right(true);
            led.reverse_left (false);
            led.reverse_right(false);
        } else if (speed > 40) {
            led.forward_left (false);
            led.forward_right(false);
            led.reverse_left (false);
            led.reverse_right(false);
        }
        motor.forward(speed);
        _delay_ms(250);
*/
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: TIMER0_OVF_vect
 * Purpose:  TBD.
 **********************************************************************/
ISR(TIMER0_OVF_vect)
{
}

/**********************************************************************
 * Function: TIMER1_OVF_vect
 * Purpose:  TBD.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    static uint8_t number_of_overflows = 0;
    LED led;

    number_of_overflows++;

    if (number_of_overflows >= 2)
    {
        number_of_overflows = 0;
        led.reverse_left(true);
        led.reverse_right(true);
        // Just for testing. Use any terminal, such as PuTTY in 8N1 mode, 38400 Bd
        usb_printf("ON\r\n");
    }
    else
    {
        led.reverse_left(false);
        led.reverse_right(false);
        // Just for testing. Use any terminal, such as PuTTY in 8N1 mode, 38400 Bd
        usb_printf("OFF\r\n");
    }

    // speed++;
    // if (speed>=90)
    //     speed = 75;
    // Just for testing. Use any terminal, such as PuTTY in 8N1 mode, 38400 Bd
    // usb_printf("speed: %d\r\n", speed);
}

/**********************************************************************
 * Function: USART0_RX_vect
 * Purpose:  TBD.
 **********************************************************************/
ISR(BLUETOOTH_RX_vect)
{
    uint8_t tmp = BLUETOOTH_DATA;
    usb_putc(tmp);
}

/**********************************************************************
 * Function: USART1_RX_vect
 * Purpose:  TBD.
 **********************************************************************/
ISR(USB_RX_vect)
{
    uint8_t tmp = USB_DATA;
    bluetooth_putc(tmp);
}
