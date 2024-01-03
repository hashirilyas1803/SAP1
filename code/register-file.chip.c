// Wokwi Custom Chip - For docs and examples see:
// https://docs.wokwi.com/chips-api/getting-started
//
// SPDX-License-Identifier: MIT
// Copyright 2023 Muhammad Hashir Ilyas

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  // TODO: Put your chip variables here
  //  inputs
  pin_t IN0;
  pin_t IN1;
  pin_t IN2;
  pin_t IN3;
  pin_t IN4;
  pin_t IN5;
  pin_t IN6;
  pin_t IN7;
  pin_t IN8;
  pin_t IN9;
  pin_t INA;
  pin_t INB;
  pin_t INC;
  pin_t IND;
  pin_t INE;
  pin_t INF;
  pin_t AB0;
  pin_t AB1;
  pin_t AB2;
  pin_t AB3;
  
  
  // outputs
  pin_t OUT0;
  pin_t OUT1;
  pin_t OUT2;
  pin_t OUT3;
  pin_t OUT4;
  pin_t OUT5;
  pin_t OUT6;
  pin_t OUT7;
  pin_t OUT8;
  pin_t OUT9;
  pin_t OUTA;
  pin_t OUTB;
  pin_t OUTC;
  pin_t OUTD;
  pin_t OUTE;
  pin_t OUTF;

  // pin_t IN[16];

  // // Outputs
  // pin_t OUT[16];

  // Read and write pins
  pin_t Read;
  pin_t Write;
  // Internal state
  int register_value;
} chip_state_t;
static int file[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void chip_update(chip_state_t *chip) {
const pin_t* OUT[] = {&chip->OUT0, &chip->OUT1, &chip->OUT2, &chip->OUT3, &chip->OUT4, &chip->OUT5, &chip->OUT6, &chip->OUT7, &chip->OUT8, &chip->OUT9, &chip->OUTA, &chip->OUTB, &chip->OUTC, &chip->OUTD, &chip->OUTE, &chip->OUTF};
const pin_t* IN[] = {&chip->IN0, &chip->IN1, &chip->IN2, &chip->IN3, &chip->IN4, &chip->IN5, &chip->IN6, &chip->IN7, &chip->IN8, &chip->IN9, &chip->INA, &chip->INB, &chip->INC, &chip->IND, &chip->INE, &chip->INF};  

int input = 
    pin_read(chip->AB0) * 1 +
    pin_read(chip->AB1) * 2 + 
    pin_read(chip->AB2) * 4 +
    pin_read(chip->AB3) * 8;  

int value = file[input];

if (pin_read(chip->Read)) {
  // Display the current state on LEDs
  for (int i = 0; i < 16; i++) {
    pin_write(*OUT[i], (value >> i) & 1);
    }
}

if (pin_read(chip->Write)) {
  chip->register_value = 0;
for (int i = 0; i < 16; i++) {
      chip->register_value |= (pin_read(*IN[i]) & 1) << i;
    }
    file[input] = chip->register_value;
}
// if (pin_read(chip->Write)) {
//   // Update the specific register in the file array
//   file[input] = value;
// }

//Read from the register file based on the address pins
}
void chip_pin_change(void *user_data, pin_t pin, uint32_t value) {
  chip_state_t *chip = (chip_state_t*)user_data;
  // Update the register value or handle other pin change logic if needed
  chip_update(chip);
}

void chip_init() {
  chip_state_t *chip = malloc(sizeof(chip_state_t));

  // Initialize inputs
  chip->IN0 = pin_init("IN0", INPUT_PULLDOWN);
  chip->IN1 = pin_init("IN1", INPUT_PULLDOWN);
  chip->IN2 = pin_init("IN2", INPUT_PULLDOWN);
  chip->IN3 = pin_init("IN3", INPUT_PULLDOWN);
  chip->IN4 = pin_init("IN4", INPUT_PULLDOWN);
  chip->IN5 = pin_init("IN5", INPUT_PULLDOWN);
  chip->IN6 = pin_init("IN6", INPUT_PULLDOWN);
  chip->IN7 = pin_init("IN7", INPUT_PULLDOWN);
  chip->IN8 = pin_init("IN8", INPUT_PULLDOWN);
  chip->IN9 = pin_init("IN9", INPUT_PULLDOWN);
  chip->INA = pin_init("INA", INPUT_PULLDOWN);
  chip->INB = pin_init("INB", INPUT_PULLDOWN);
  chip->INC = pin_init("INC", INPUT_PULLDOWN);
  chip->IND = pin_init("IND", INPUT_PULLDOWN);
  chip->INE = pin_init("INE", INPUT_PULLDOWN);
  chip->INF = pin_init("INF", INPUT_PULLDOWN);
  chip->AB0 = pin_init("AB0", INPUT_PULLDOWN);
  chip->AB1 = pin_init("AB1", INPUT_PULLDOWN);
  chip->AB2 = pin_init("AB2", INPUT_PULLDOWN);
  chip->AB3 = pin_init("AB3", INPUT_PULLDOWN);
  chip->OUT0 = pin_init("OUT0", OUTPUT);
  chip->OUT1 = pin_init("OUT1", OUTPUT);
  chip->OUT2 = pin_init("OUT2", OUTPUT);
  chip->OUT3 = pin_init("OUT3", OUTPUT);
  chip->OUT4 = pin_init("OUT4", OUTPUT);
  chip->OUT5 = pin_init("OUT5", OUTPUT);
  chip->OUT6 = pin_init("OUT6", OUTPUT);
  chip->OUT7 = pin_init("OUT7", OUTPUT);
  chip->OUT8 = pin_init("OUT8", OUTPUT);
  chip->OUT9 = pin_init("OUT9", OUTPUT);
  chip->OUTA = pin_init("OUTA", OUTPUT);
  chip->OUTB = pin_init("OUTB", OUTPUT);
  chip->OUTC = pin_init("OUTC", OUTPUT);
  chip->OUTD = pin_init("OUTD", OUTPUT);
  chip->OUTE = pin_init("OUTE", OUTPUT);
  chip->OUTF = pin_init("OUTF", OUTPUT);
  
  const pin_watch_config_t watch_config = {
    .edge = BOTH,
    .pin_change = chip_pin_change,
    .user_data = chip
  };
  pin_watch(chip->IN0, &watch_config);
  pin_watch(chip->IN1, &watch_config);
  pin_watch(chip->IN2, &watch_config);
  pin_watch(chip->IN3, &watch_config);
  pin_watch(chip->IN4, &watch_config);
  pin_watch(chip->IN5, &watch_config);
  pin_watch(chip->IN6, &watch_config);
  pin_watch(chip->IN7, &watch_config);
  pin_watch(chip->IN8, &watch_config);
  pin_watch(chip->IN9, &watch_config);
  pin_watch(chip->INA, &watch_config);
  pin_watch(chip->INB, &watch_config);
  pin_watch(chip->INC, &watch_config);
  pin_watch(chip->IND, &watch_config);
  pin_watch(chip->INE, &watch_config);
  pin_watch(chip->INF, &watch_config);
  pin_watch(chip->AB0, &watch_config);
  pin_watch(chip->AB1, &watch_config);
  pin_watch(chip->AB2, &watch_config);
  pin_watch(chip->AB3, &watch_config);
  // Initialize Read and Write pins
  chip->Read = pin_init("Read", INPUT_PULLDOWN);
  chip->Write = pin_init("Write", INPUT_PULLDOWN);
  pin_watch(chip->Read, &watch_config);
  pin_watch(chip->Write, &watch_config);
  

  // Internal state
  chip->register_value = 0;

  // TODO: Additional initialization logic as needed
  
  // Update the initial state
  chip_update(chip);
}
