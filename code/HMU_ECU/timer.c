///******************************************************************************
// *
// * Module: Timer
// *
// * File Name: timer.c
// *
// * Description: Source file for the Timer1 driver
// *
// * Author: Abdelrahman Mahalawy
// *
// ******************************************************************************/

#include "Timer.h"             // Include the Timer module's header file
#include "avr/io.h"             // Include AVR I/O header file
#include "common_macros.h" // Include common macros header file
#include "std_types.h"    // Include standard data types header file
#include "avr/interrupt.h"       // Include AVR interrupt handling header file

void (*CallBack_Ptr)(void) = NULL_PTR; // Initialize a function pointer to NULL

// Initialize Timer1 with the provided configuration
void Timer1_init(const Timer1_ConfigType *Config_Ptr)
{
    // Check if the mode is CTC Mode
    if (Config_Ptr->mode == CTC_Mode) {
        SET_BIT(TCCR1A, FOC1A);  // Set Force Output Compare A (FOC1A) bit
        SET_BIT(TCCR1B, WGM12);  // Set Waveform Generation Mode (WGM12) bit
        TCCR1B |= Config_Ptr->prescaler; // Set the prescaler value
        TCNT1 = Config_Ptr->intial_value; // Set the initial value of the timer
        OCR1A = Config_Ptr->compare_value; // Set the compare value for generating interrupts
        SET_BIT(TIMSK, OCIE1A); // Enable Output Compare A Match interrupt
    } else {
        SET_BIT(TCCR1A, FOC1A); // Set Force Output Compare A (FOC1A) bit
        TCCR1B |= Config_Ptr->prescaler; // Set the prescaler value
        TCNT1 = Config_Ptr->intial_value; // Set the initial value of the timer
        SET_BIT(TIMSK, TOIE1); // Enable Timer Overflow interrupt
    }
}

// Deinitialize Timer1 by resetting its registers and callback function pointer
void Timer1_deInit(void)
{
    TCCR1A = 0; // Reset Timer Control Register A
    TIMSK = 0;  // Reset Timer Interrupt Mask Register
    CallBack_Ptr = NULL_PTR; // Set the callback function pointer to NULL
}

// Set a callback function to be called on timer events
void Timer1_setCallBack(void(*a_ptr)(void))
{
    CallBack_Ptr = a_ptr; // Set the callback function pointer
}

// Interrupt Service Routine (ISR) for the Timer1 Output Compare A Match
ISR(TIMER1_COMPA_vect)
{
    TCNT1 = 0; // Reset the timer
    if (CallBack_Ptr != NULL_PTR) {
        CallBack_Ptr(); // Call the callback function if it is not NULL
    }
}

// Interrupt Service Routine (ISR) for the Timer1 Overflow
ISR(TIMER1_OVF_vect)
{
    TCNT1 = 0; // Reset the timer
    if (CallBack_Ptr != NULL_PTR) {
        CallBack_Ptr(); // Call the callback function if it is not NULL
    }
}
