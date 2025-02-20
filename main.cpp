#define USER_BUTTON PC_13

#include "mbed.h"
#include "motor.h"
#include "tunes.h"
#include "pwm_tone.h"
#include "PROJ100_Encoder.h"
#include "PROJ100_Encoder_Tests.h"

#define TIME_PERIOD                 10      //Constant compiler Values here 10 equates to 10ms or 100Hz base Frequency
#define ENCODER_PIN_LEFT            D8
#define ENCODER_PIN_RIGHT           D6 
#define PULSES_PER_ROTATION         20
#define DEBOUNCE_US                 26000

DigitalIn microswitch1(D4);         //Instance of the DigitalIn class called 'microswitch1'
DigitalIn microswitch2(D3);         //Instance of the DigitalIn class called 'microswitch2'
DigitalIn myButton(USER_BUTTON);    //Instance of the DigitalIn class called 'myButton'   
DigitalOut greenLED(LED1);          //Instance of the DigitalOut class called 'greenLED'

Motor Wheel(D13,D11,D9,D10);      //Instance of the Motor Class called 'Wheel' see motor.h and motor.cpp

PROJ100_Encoder right_encoder (ENCODER_PIN_RIGHT,PULSES_PER_ROTATION);  //Instance of the PROJ100Encoder class called 'right_encoder'
PROJ100_Encoder left_encoder(ENCODER_PIN_LEFT,PULSES_PER_ROTATION);     //Instance of the PROJ100Encoder class called 'left_encoder'

UnbufferedSerial ser(USBTX,USBRX,115200);   // Serial object for printing info


int main ()
{

    // Clear the terminal and print an intro
    printf("\033[2J\033[1;1H\r\n");
    printf("Plymouth University PROJ100 2024/25 Optical Encoder Demonstration\n\r");

    // Set the PWM frequency
    Wheel.Period_in_ms(TIME_PERIOD);                

    // Ensure our motors and encoders are stopped at the beginning
    right_encoder.stop();
    left_encoder.stop();
    Wheel.Stop();

    // The encoder pulses can be noisy and so are debounced within the class
    // You can experiment with changing the debouce time if you wish
    left_encoder.setDebounceTimeUs(DEBOUNCE_US);
    right_encoder.setDebounceTimeUs(DEBOUNCE_US);

    // Wait for the blue button to be pressed
    printf("Press Blue Button To Begin\n\r");
    while (myButton == 0){greenLED = !greenLED; ThisThread::sleep_for(100ms);}

    // Start the encoders
    left_encoder.start();
    right_encoder.start();

  
    /*********************ENCODER TESTS***************/
    // These contain while(1) loops so ensure that they are removed or commented out when running your own code
    // If these lines are left in the lines below will never run
    // These are examples only, and not all functionality within them is required for your coursework
    // HINT: you don't need to measure speed
    // Check PROJ100_Encoder_Tests.cpp for the code for these functions
    /*************************************************/

    // simplest_test();
    // simple_test();
    rotations_test();
    // ave_pulse_time_test();
    // speed_test();
    


    //*******Demostration of the pwm_tune library***********//
    jingle_bells(2);
    close_encounter(2);



    while(true){


        // The following lines demostrate the use of the microswitches.
        // You should remove these from your final solution 
        // You could maybe find a better use for the switches(collision detection?)
        if(microswitch1.read()==1){
            // If the first switch is pressed print Hello
            printf("Hello\n");
        }
        if(microswitch2.read()==1){
            // If the second switch is pressed print Goodbye
            printf("Goodbye\n");
        }
        wait_us(500000);



        // Write the parts of your code which should run in a loop between here..
        



        // ..and here

    };
}