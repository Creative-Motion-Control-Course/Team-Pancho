#define module_driver

#include "stepdance.hpp"

OutputPort output_a;
OutputPort output_b;
OutputPort output_c;
OutputPort output_d;

Channel channel_a;
Channel channel_b;
Channel channel_z;
Channel channel_e;

KinematicsPolarToCartesian polar_kinematics;

Encoder encoder_1; // stepper motor position
Encoder encoder_2; // z axis

VelocityGenerator velocity_gen;

const float64_t FIXED_RADIUS = 2.0; 
float64_t currentSpeed = 4.0;        // tune via serial

void setup() {
  Serial.begin(115200);

  output_a.begin(OUTPUT_A);
  output_b.begin(OUTPUT_B);
  output_c.begin(OUTPUT_C);
  output_d.begin(OUTPUT_D);

  enable_drivers();

  channel_a.begin(&output_a, SIGNAL_E);
  channel_a.set_ratio(1, 40);
  channel_a.invert_output();

  channel_b.begin(&output_b, SIGNAL_E);
  channel_b.set_ratio(1, 40);

  channel_z.begin(&output_c, SIGNAL_E);
  channel_z.set_ratio(1, 1201);
  channel_z.invert_output();

  channel_e.begin(&output_d, SIGNAL_E);
  channel_e.set_ratio(1, 2400);

  velocity_gen.begin();
  velocity_gen.speed_units_per_sec = currentSpeed;
  velocity_gen.output.map(&polar_kinematics.input_angle);

  encoder_1.begin(ENCODER_1);
  encoder_1.set_ratio(1, 2400);
  encoder_1.output.map(&channel_e.input_target_position);

  encoder_2.begin(ENCODER_2);
  encoder_2.set_ratio(1, 2400);
  encoder_2.output.map(&channel_z.input_target_position);
  encoder_2.invert();

  polar_kinematics.begin();
  polar_kinematics.input_radius.set(FIXED_RADIUS); 
  polar_kinematics.output_x.map(&channel_a.input_target_position);
  polar_kinematics.output_y.map(&channel_b.input_target_position);


  dance_start();
}

LoopDelay overhead_delay;

void loop() {
  overhead_delay.periodic_call(&report_overhead, 500);

  if (Serial.available()) { 
    float newSpeed = Serial.parseFloat();
    if (newSpeed > 0) {
      currentSpeed = newSpeed;
      velocity_gen.speed_units_per_sec = currentSpeed;
    }
  }

  dance_loop();
}

void report_overhead() {
  Serial.print("speed (rad/s): ");
  Serial.println(currentSpeed);
}