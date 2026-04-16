/*
  UCSB MAT Creative Motion Control -- Generators example (sine wave mod)

serial commands:
//   {"name": "set_x_amplitude", "args": [10]}
//   {"name": "set_x_frequency", "args": [2]}
*/

#define module_driver
#include "stepdance.hpp"

// -- Output Ports --
OutputPort output_a;  // Axidraw left motor
OutputPort output_b;  // Axidraw right motor
OutputPort output_c;  // Z axis servo

// -- Channels --
Channel channel_a;
Channel channel_b;
Channel channel_z;

// -- Kinematics --
KinematicsCoreXY axidraw_kinematics;

// -- Wave Generators --
WaveGenerator1D x_wave_gen;  // sine wave on X axis
WaveGenerator1D z_wave_gen;  // pen up/down oscillation

// -- Velocity Generator (Y axis) --
VelocityGenerator vertical_velocity_gen;

// -- Position Generator + Button (pen up/down) --
PositionGenerator position_gen;
Button button_d1;

// -- Potentiometer --
AnalogInput analog_a1;

// -- RPC --
RPC rpc;

// Storing the current x level 
float64_t current_line_y = 15;

// -- Time Based Interpolators for Pen XY --
TimeBasedInterpolator time_based_interpolator;

void setup() {
  Serial.begin(115200);

  // -- Output ports --
  output_a.begin(OUTPUT_A);
  output_b.begin(OUTPUT_B);
  output_c.begin(OUTPUT_C);
  enable_drivers();

  // -- Channels --
  channel_a.begin(&output_a, SIGNAL_E);
  channel_b.begin(&output_b, SIGNAL_E);
  channel_a.set_ratio(25.4, 2032);
  channel_a.invert_output();
  channel_b.set_ratio(25.4, 2032);
  channel_b.invert_output();

  channel_z.begin(&output_c, SIGNAL_E);
  channel_z.set_ratio(1, 50);

  // -- X wave generator --
  x_wave_gen.setNoInput();
  x_wave_gen.frequency = 1.0;  // Hz
  x_wave_gen.amplitude = 10.0; // mm
  x_wave_gen.output.map(&axidraw_kinematics.input_x);
  x_wave_gen.begin();

  // -- Y velocity generator --
  vertical_velocity_gen.begin();
  vertical_velocity_gen.speed_units_per_sec = 2.0; // mm/s
  vertical_velocity_gen.output.map(&axidraw_kinematics.input_y);

  // -- Z wave generator --
  z_wave_gen.setNoInput();
  z_wave_gen.frequency = 10.0;
  z_wave_gen.amplitude = 0.0;
  z_wave_gen.output.map(&channel_z.input_target_position);
  z_wave_gen.begin();

  // -- Kinematics --
  axidraw_kinematics.begin();
  axidraw_kinematics.output_a.map(&channel_a.input_target_position);
  axidraw_kinematics.output_b.map(&channel_b.input_target_position);

  // -- Button (pen up/down) --
  button_d1.begin(IO_D1, INPUT_PULLDOWN);
  button_d1.set_mode(BUTTON_MODE_TOGGLE);
  button_d1.set_callback_on_press(&pen_up);
  button_d1.set_callback_on_release(&pen_down);

  // -- Potentiometer maps to X amplitude --
  analog_a1.set_floor(1, 25);
  analog_a1.set_ceiling(50, 1020);
  analog_a1.map(&x_wave_gen.amplitude);
  analog_a1.begin(IO_A1);

  // -- Position generator --
  position_gen.output.map(&channel_z.input_target_position);
  position_gen.begin();

  // -- RPC --
  rpc.begin();
  rpc.enroll("set_speed_y", set_speed_y);
  rpc.enroll("set_x_amplitude", set_x_amplitude);
  rpc.enroll("set_x_frequency", set_x_frequency);
  rpc.enroll("set_z_amplitude", set_z_amplitude);


  // Time based interpolator (can be used to queue motions)
  time_based_interpolator.begin();
  time_based_interpolator.output_x.map(&axidraw_kinematics.input_x);
  time_based_interpolator.output_y.map(&axidraw_kinematics.input_y);
  time_based_interpolator.output_z.map(&channel_z.input_target_position);

  //...

  // Set up RPC etc...
  // {"name": "queue_xy_target", "args": [6, 5]}
  // args are: absolute X, absolute Y
  rpc.enroll("queue_xy_target", queue_xy_target);

  dance_start();
}

LoopDelay overhead_delay;

void loop() {
  overhead_delay.periodic_call(&report_overhead, 500);
  y_motion()
  
  dance_loop();
}

void pen_down() {
  position_gen.go(-4, ABSOLUTE, 100);
}

void pen_up() {
  position_gen.go(4, ABSOLUTE, 100);
}

void set_speed_y(float32_t speed) {
  vertical_velocity_gen.speed_units_per_sec = speed;
}

void set_x_amplitude(float32_t amplitude) {
  x_wave_gen.amplitude = amplitude;
}

void set_x_frequency(float32_t frequency) {
  x_wave_gen.frequency = frequency;
}

void set_z_amplitude(float32_t amplitude) {
  z_wave_gen.amplitude = amplitude;
}

void y_motion() {
  // Moves the header to the end of the page
  queue_xy_target(current_line_x, 218)
  queue_xy_target(current_line_x, 0)

}

