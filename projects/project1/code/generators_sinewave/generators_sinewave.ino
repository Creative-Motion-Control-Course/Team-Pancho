/*
  UCSB MAT Creative Motion Control -- Generators example (sine wave mod)

  serial commands:
  {"name": "set_x_amplitude", "args": [10]}
  {"name": "set_x_frequency", "args": [2]}
*/

#define module_driver   // tells compiler we're using the Stepdance Driver Module PCB
                        // This configures pin assignments for the Teensy 4.1

#include "stepdance.hpp"  // Import the stepdance library

// -- Define Input Ports --
InputPort input_a;

// -- Define Output Ports --
OutputPort output_a;  // Axidraw left motor
OutputPort output_b;  // Axidraw right motor
OutputPort output_c;  // Z axis, a servo driver for the AxiDraw

// -- Define Motion Channels --
Channel channel_a;  // AxiDraw "A" axis --> left motor motion
Channel channel_b;  // AxiDraw "B" axis --> right motor motion
Channel channel_z;  // AxiDraw "Z" axis --> pen up/down

// -- Define Kinematics --
KinematicsCoreXY axidraw_kinematics;

// -- Define Encoders --
Encoder encoder_1;
Encoder encoder_2;

// -- Define Input Button --
Button button_d1;

// -- Position Generator for Pen Up/Down --
PositionGenerator position_gen;

// -- Define Potentiometer --
AnalogInput analog_a1;

// -- RPC Interface --
RPC rpc;

// -- Velocity Generator (Y axis) --
VelocityGenerator vertical_velocity_gen;

// -- Wave Generator for Z axis (pen up/down oscillation) --
WaveGenerator1D z_wave_gen;

// -- Wave Generator for X axis (sine wave drawing) --
WaveGenerator1D x_wave_gen;

// Position Generator to move to a certain posisition
PositionGenerator x_position_gen;
PositionGenerator y_position_gen;

void setup() {
  // -- Configure and start the output ports --
  output_a.begin(OUTPUT_A);
  output_b.begin(OUTPUT_B);
  output_c.begin(OUTPUT_C);

  enable_drivers();

  // -- Configure and start the channels --
  channel_a.begin(&output_a, SIGNAL_E);
  channel_b.begin(&output_b, SIGNAL_E);

  channel_a.set_ratio(25.4, 2032);
  channel_a.invert_output();
  channel_b.set_ratio(25.4, 2032);
  channel_b.invert_output();

  channel_z.begin(&output_c, SIGNAL_E);
  channel_z.set_ratio(1, 50);

  // -- Configure encoders --
  encoder_1.begin(ENCODER_1);
  encoder_1.set_ratio(24, 2400);
  // encoder_1 no longer mapped here; x_wave_gen drives X instead

  encoder_2.begin(ENCODER_2);
  encoder_2.set_ratio(24, 2400);
  encoder_2.output.map(&axidraw_kinematics.input_y);

  // -- Configure velocity generator (Y axis) --
  vertical_velocity_gen.begin();
  vertical_velocity_gen.speed_units_per_sec = 0.0;
  vertical_velocity_gen.output.map(&axidraw_kinematics.input_y);

  // -- Configure Z wave generator --
  z_wave_gen.setNoInput();
  z_wave_gen.frequency = 10.0;
  z_wave_gen.amplitude = 0.0;
  z_wave_gen.output.map(&channel_z.input_target_position);
  z_wave_gen.begin();

  // -- Configure X wave generator (sine wave on X axis) --
  x_wave_gen.setNoInput();       // use internal clock as time variable
  x_wave_gen.frequency = 1.0;   // frequency in Hz (change via serial)
  x_wave_gen.amplitude = 0.0;   // amplitude in mm (change via serial)
  x_wave_gen.output.map(&axidraw_kinematics.input_x);
  x_wave_gen.begin();

  // Configure the posistion generator
  x_position_gen.output.map(&axidraw_kinematics.input_x);
  x_position_gen.begin();

  y_position_gen.output.map(&axidraw_kinematics.input_y);
  y_position_gen.begin();

  // -- Configure kinematics --
  axidraw_kinematics.begin();
  axidraw_kinematics.output_a.map(&channel_a.input_target_position);
  axidraw_kinematics.output_b.map(&channel_b.input_target_position);

  // -- Configure Button --
  button_d1.begin(IO_D1, INPUT_PULLDOWN);
  button_d1.set_mode(BUTTON_MODE_TOGGLE);
  button_d1.set_callback_on_press(&next_line);
  
  // -- Analog input maps to X wave amplitude --
  analog_a1.set_floor(1, 25);
  analog_a1.set_ceiling(50, 1020);
  analog_a1.map(&x_wave_gen.amplitude);
  analog_a1.begin(IO_A1);


  // -- RPC Interface --
  rpc.begin();

  // Call example: {"name": "hello"}
  rpc.enroll("hello", hello_serial);

  // Call example: {"name": "set_speed_y", "args": [5]}
  rpc.enroll("set_speed_y", set_speed_y);

  // Call example: {"name": "set_z_amplitude", "args": [1]}
  rpc.enroll("set_z_amplitude", set_z_amplitude);

  // Call example: {"name": "set_x_amplitude", "args": [10]}
  // Sets the amplitude (in mm) of the X axis sine wave
  rpc.enroll("set_x_amplitude", set_x_amplitude);

  // Call example: {"name": "set_x_frequency", "args": [2]}
  // Sets the frequency (in Hz) of the X axis sine wave
  rpc.enroll("set_x_frequency", set_x_frequency);

  // -- Configure Position Generator --
  position_gen.output.map(&channel_z.input_target_position);
  position_gen.begin();

  // -- Start the stepdance library --
  dance_start();
}

LoopDelay overhead_delay;


void loop() {
  overhead_delay.periodic_call(&report_overhead, 500);
  dance_loop();
}

void pen_down(){
  position_gen.go(-4, ABSOLUTE, 100);
}

void pen_up(){
  position_gen.go(4, ABSOLUTE, 100);
}

void hello_serial(){
  Serial.print("hello!");
}

void set_speed_y(float32_t speed){
  vertical_velocity_gen.speed_units_per_sec = speed;
}

void set_z_amplitude(float32_t amplitude){
  z_wave_gen.amplitude = amplitude;
}

void set_x_amplitude(float32_t amplitude){
  x_wave_gen.amplitude = amplitude;
}

void set_x_frequency(float32_t frequency){
  x_wave_gen.frequency = frequency;
}

void report_overhead(){

}

void next_line() {
  float saved_speed = vertical_velocity_gen.speed_units_per_sec;
  vertical_velocity_gen.speed_units_per_sec = 0;

  position_gen.go(4, ABSOLUTE, 100);
  x_wave_gen.amplitude = 0;

  float64_t current_y = axidraw_kinematics.input_y.read_absolute();
  x_position_gen.go(0, ABSOLUTE, 100);
  y_position_gen.go(current_y + 10, ABSOLUTE, 50);

}
