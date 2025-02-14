#ifndef PROJ100_ENCODER_H
#define PROJ100_ENCODER_H
#include "mbed.h"


class PROJ100_Encoder{

    #define ENC_LEFT                0
    #define ENC_RIGHT               1
    #define OUTPUT_RAW              0
    #define OUTPUT_DEBOUNCED        1
    
    private:
        
        InterruptIn _Encoder_Pin;
        DigitalOut* out_pin = nullptr;
        Timer _pulse_timer;
        Mutex lock;
        EventQueue equeue;
        Timeout _stationary_timer;
        
        Mail<uint32_t,4> timing_mail;

        volatile uint32_t _debounce_time_us = 26000;
        volatile uint32_t _last_pulse_time=0;
        volatile bool _new_timing_data_available = false;
        volatile bool _is_stationary = true;
        uint16_t _stationary_millis = 0;
        uint8_t out_interrupt_or_thread = 0;
        uint16_t _pulses_per_rotation;

        Thread _timing_thread;
        Thread _stationary_thread;
        void stationaryHandler();
        void setIsStationary(bool stat);
        void timingUpdateThreadFunc();
        void setLastPulseTimeUs(uint32_t time);
        void encoderISR();


    public:
        PROJ100_Encoder(PinName Output_Pin, uint16_t pulses_per_rotation = 20);
        ~PROJ100_Encoder();
        bool setDebounceTimeUs(uint32_t new_us);
        uint32_t getDebounceTimeUs();
        int32_t getLastPulseTimeUs();
        int8_t pulseReceived();
        bool isStationary();
        bool waitForPulse(uint32_t timeout_ms= osWaitForever);
        uint16_t getPulsesPerRotation();
        void setOutputPin(PinName pin, uint8_t pos=OUTPUT_DEBOUNCED);
        void removeOutputPin();
        void setOutputRaworDebounced(uint8_t pos);
        void start();
        void stop();
        void reset();
        
};

#endif
