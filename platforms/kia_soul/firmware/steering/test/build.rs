extern crate gcc;
extern crate bindgen;

use std::env;
use std::path::Path;

fn main() {
    gcc::Config::new()
        .flag("-w")
        .define("__STDC_LIMIT_MACROS", None)
        .include("include")
        .include("../include")
        .include("../../../../common/include")
        .include("../../../../common/libs/can")
        .include("../../../../common/libs/time")
        .include("../../../../common/libs/dac")
        .include("../../../../common/libs/pid")
        .include("/usr/lib/avr/include")
        .file("src/mocks/Arduino.cpp")
        .file("src/mocks/SPI.cpp")
        .file("src/mocks/mcp_can.cpp")
        .file("src/mocks/DAC_MCP49xx.cpp")
        .file("../src/communications.cpp")
        .file("../src/steering_control.cpp")
        .file("../src/globals.cpp")
        .file("../../../../common/libs/pid/oscc_pid.cpp")
        .file("../../../../common/libs/time/oscc_time.cpp")
        .file("../../../../common/libs/can/oscc_can.cpp")
        .file("../../../../common/libs/dac/oscc_dac.cpp")
        .cpp(true)
        .compiler("/usr/bin/g++")
        .compile("libcomm_test.a");
    
    let out_dir = env::var("OUT_DIR").unwrap();

    let _ = bindgen::builder()
        .header("include/wrapper.hpp")
        .generate_comments(false)
        .clang_arg("-Iinclude")
        .clang_arg("-I/usr/lib/avr/include")
        .clang_arg("-I../../../../common/libs/pid")
        .whitelisted_function("publish_reports")
        .whitelisted_function("check_for_incoming_message")
        .whitelisted_function("*register_callback*")
        .whitelisted_function("*register_signal_callbacks*")
        .whitelisted_function("*register_can_frame*")
        .whitelisted_function("check_for_operator_override")
        .whitelisted_var("g_steering_control_state")
        .whitelisted_var("OSCC_REPORT_STEERING_CAN_ID")
        .whitelisted_var("OSCC_REPORT_STEERING_CAN_DLC")
        .whitelisted_var("OSCC_COMMAND_STEERING_CAN_ID")
        .whitelisted_var("OSCC_COMMAND_STEERING_CAN_DLC")
        .whitelisted_var("OVERRIDE_WHEEL_THRESHOLD_IN_DEGREES_PER_USEC")
        .whitelisted_var("CAN_STANDARD")
        .whitelisted_var("g_control_can")
        .whitelisted_type("oscc_report_steering_data_s")
        .whitelisted_type("oscc_report_steering_s")
        .whitelisted_type("oscc_command_steering_data_s")
        .whitelisted_type("oscc_command_steering_s")
        .whitelisted_type("can_frame_s")
        .generate().unwrap()
        .write_to_file(Path::new(&out_dir).join("communications.rs"))
        .expect("Unable to generate bindings");
}