/**
 * @file init.cpp
 *
 */


#include <Arduino.h>

#include "can_protocols/steering_can_protocol.h"
#include "communications.h"
#include "debug.h"
#include "globals.h"
#include "init.h"
#include "oscc_can.h"
#include "oscc_serial.h"
#include "oscc_timer.h"


void init_globals( void )
{
    g_steering_control_state.enabled = false;
    g_steering_control_state.operator_override = false;
    g_steering_control_state.dtcs = 0;
}


void init_devices( void )
{
    pinMode( PIN_DAC_CHIP_SELECT, OUTPUT );
    pinMode( PIN_TORQUE_SENSOR_HIGH, INPUT );
    pinMode( PIN_TORQUE_SENSOR_LOW, INPUT );
    pinMode( PIN_TORQUE_SPOOF_HIGH, INPUT );
    pinMode( PIN_TORQUE_SPOOF_LOW, INPUT );
    pinMode( PIN_SPOOF_ENABLE, OUTPUT );

    cli();
    digitalWrite( PIN_DAC_CHIP_SELECT, HIGH );
    digitalWrite( PIN_SPOOF_ENABLE, LOW );
    sei();
}


void init_communication_interfaces( void )
{
    #ifdef DEBUG
    init_serial( );
    #endif

    DEBUG_PRINT( "init Control CAN - " );
    init_can( g_control_can );
}


void start_timers( void )
{
    timer1_init( OSCC_REPORT_STEERING_PUBLISH_FREQ_IN_HZ, publish_steering_report );
}
