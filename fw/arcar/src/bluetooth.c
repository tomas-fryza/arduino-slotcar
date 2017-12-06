#include "bluetooth.h"

void bluetooth_setup(void)
{
    bluetooth_cmd(BLT_START_CMD_MODE);
    bluetooth_cmd(BLT_SET_NAME);
    bluetooth_cmd(BLT_ADD_MAC);
    bluetooth_cmd(BLT_SET_SERVISE);
    bluetooth_cmd(BLT_ENABLE_UART);
    bluetooth_cmd(BLT_REBOOT);
}

void bluetooth_init(void)
{
    UBRR0 = 25;                       // 38400 bps
    UCSR0A = 1<<U2X0;                 // double speed mode
    UCSR0B = (1<<RXEN0) | (1<<TXEN0); // enable receiver and transmitter
    UCSR0C = 3<<UCSZ00;               // 8n1
    UCSR0B |= 1<<RXCIE0;              // receiver interrupt

}

/*void bluetooth_servise(void)
{
    DDRB = 0; PORTB = 0;
    DDRC = 0; PORTC = 0;
    DDRD = 0; PORTD = 0;
    DDRE = 0; PORTE = 0;

    DDRB = 1<<3; // USB TX
    DDRD = 1<<1; // BLT TX

    while (1)
    {
        if (PINB & (1<<4))
            PORTD |= 1<<1;
        else
            PORTD &= ~(1<<1);

        if (PIND & (1<<0))
            PORTB |= 1<<3;
        else
            PORTB &= ~(1<<3);
    }
}*/

void bluetooth_putc(unsigned char data)
{
    // wait to empty RN4871 buffer
    if (data == '\n')
        _delay_ms(160);
    // Wait for empty transmit buffer
    while ( !( UCSR0A & (1<<UDRE0)) );
    // Put data into buffer, sends the data
    UDR0 = data;
}

void bluetooth_puts(char str[])
{
    for (int i=0; str[i]; i++)
        bluetooth_putc(str[i]);
}

void bluetooth_cmd(char str[])
{
    for (int i=0; str[i]; i++)
    {
        bluetooth_putc(str[i]);
        bluetooth_delay();
    }
    bluetooth_putc('\r'); // CR
}
