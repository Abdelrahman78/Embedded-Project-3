#include "Keypad.h"
#include <avr/io.h>


// Define the keypad dimensions
#define ROWS 4
#define COLS 4

// Define the keypad pins
#define KEYPAD_PORT PORTB
#define KEYPAD_PIN PINB
#define KEYPAD_DDR DDRB
// Keypad layout
char Keypad_Layout[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

void Keypad_Init() {
    // Set ROWS as input and enable pull-ups
    KEYPAD_DDR &= ~(0xF0);
    KEYPAD_PORT |= 0xF0;

    // Set COLS as output
    KEYPAD_DDR |= 0x0F;
}

char Keypad_ReadKey() {
    for (int col = 0; col < COLS; col++) {
        // Set the current column low
        KEYPAD_PORT &= ~(1 << (col + 4));

        // Check each row
        for (int row = 0; row < ROWS; row++) {
            if (!(KEYPAD_PIN & (1 << row))) {
                // Key is pressed, return the corresponding character
                return Keypad_Layout[row][col];
            }
        }

        // Reset the current column to high
        KEYPAD_PORT |= (1 << (col + 4));
    }

    // No key pressed
    return '\0';
}
