//BENCH TESTS

test_DACS() {
  // the two DACS have circuitry for measuring the output. Create a signal and
  // measure that the output is what is expected.
}

test_interrupt_relay() {
  // to test that the signal interrupt relay functions we can blink two
  // LEDS in an alternating pattering using the the switch relay.
}

test_CAN_send() {
  // send a CAN frame, to be recieved by some module on a CAN bus.
}

test_can_recieve() {
  // recieve a CAN frame sent from some module on a CAN bus.

}

//INSTALLATION TESTS

test_throttle_signal_sense() {
  // press the accelerator pedal while the car is on and check that the readings from
  // the APS are as expected.
}

test_APS_spoof() {
  // send spoofed throttle, slowly increase and decrease throttle
}

test_hard_power_off() {
  // while spoofing throttle, cut power and test that shutdown is
  // handled gracefully or throws the expected fault.
}

setup() {

}

loop() {
  // interactively run tests

}
