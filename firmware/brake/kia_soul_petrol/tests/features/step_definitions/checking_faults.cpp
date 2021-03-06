WHEN("^a sensor becomes temporarily disconnected$")
{
    g_mock_arduino_analog_read_return[0] = 0;
    g_mock_arduino_analog_read_return[1] = 0;

    g_mock_arduino_millis_return = 1;
    check_for_sensor_faults();

    g_mock_arduino_millis_return += FAULT_HYSTERESIS / 2;
    check_for_sensor_faults();
}


WHEN("^a sensor becomes permanently disconnected$")
{
    g_mock_arduino_analog_read_return[0] = 0;
    g_mock_arduino_analog_read_return[1] = 0;

    g_mock_arduino_millis_return = 1;
    check_for_sensor_faults();

    g_mock_arduino_millis_return += FAULT_HYSTERESIS * 2;
    check_for_sensor_faults();
}


WHEN("^the operator applies (.*) to the brake pedal for (\\d+) ms$")
{
    REGEX_PARAM(int, pedal_val);
    REGEX_PARAM(int, duration);

    g_mock_arduino_analog_read_return[10] = pedal_val;
    g_mock_arduino_analog_read_return[11] = pedal_val;

    g_mock_arduino_millis_return = 1;
    check_for_operator_override();

    g_mock_arduino_millis_return += duration;
    check_for_operator_override();
}


THEN("^control should remain enabled")
{
    assert_that(
        g_brake_control_state.enabled,
        is_equal_to(1));
}


THEN("^a fault report should be published$")
{
    assert_that(g_mock_mcp_can_send_msg_buf_id, is_equal_to(OSCC_FAULT_REPORT_CAN_ID));
    assert_that(g_mock_mcp_can_send_msg_buf_ext, is_equal_to(CAN_STANDARD));
    assert_that(g_mock_mcp_can_send_msg_buf_len, is_equal_to(OSCC_FAULT_REPORT_CAN_DLC));

    oscc_fault_report_s * fault_report =
        (oscc_fault_report_s *) g_mock_mcp_can_send_msg_buf_buf;

    assert_that(
        fault_report->magic[0],
        is_equal_to(OSCC_MAGIC_BYTE_0));

    assert_that(
        fault_report->magic[1],
        is_equal_to(OSCC_MAGIC_BYTE_1));

    assert_that(
        fault_report->fault_origin_id,
        is_equal_to(FAULT_ORIGIN_BRAKE));
}
