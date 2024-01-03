// Wokwi Custom Chip - For docs and examples see:
// https://docs.wokwi.com/chips-api/getting-started
//
// SPDX-License-Identifier: MIT
// Copyright 2023 Saad Imam

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
  pin_t FIN0;
  pin_t FIN1;
  pin_t FIN2;
  pin_t FIN3;
  pin_t FIN4;
  pin_t FIN5;
  pin_t FIN6;
  pin_t FIN7;
  
  
  // outputs
  pin_t SIN0;
  pin_t SIN1;
  pin_t SIN2;
  pin_t SIN3;
  pin_t SIN4;
  pin_t SIN5;
  pin_t SIN6;
  pin_t SIN7;

  
  pin_t OUT0;
  pin_t OUT1;
  pin_t OUT2;
  pin_t OUT3;
  pin_t OUT4;
  pin_t OUT5;
  pin_t OUT6;
  pin_t OUT7;
 

  // pin_t IN[16];

  // // Outputs
  // pin_t OUT[16];

  // Read and write pins
  pin_t EN;
 
  // Internal state
  int register_value;
} chip_state_t;

void chip_update(chip_state_t *chip) {
  int enable = pin_read(chip->EN);
  const pin_t* OUT[] = {&chip->OUT0, &chip->OUT1, &chip->OUT2, &chip->OUT3, &chip->OUT4, &chip->OUT5, &chip->OUT6, &chip->OUT7};
  const pin_t* FIN[] = {&chip->FIN0, &chip->FIN1, &chip->FIN2, &chip->FIN3, &chip->FIN4, &chip->FIN5, &chip->FIN6, &chip->FIN7};    
  const pin_t* SIN[] = {&chip->SIN0, &chip->SIN1, &chip->SIN2, &chip->SIN3, &chip->SIN4, &chip->SIN5, &chip->SIN6, &chip->SIN7};    
  
  if(enable == 0)
  {
    for (int i = 0; i < 8; i++)
    {
    pin_write(*OUT[i], pin_read(*FIN[i]));
    }
  }
  else{
   
    for (int i = 0; i < 8; i++) 
    {
    pin_write(*OUT[i], pin_read(*SIN[i]));
    }
  }

}
void chip_pin_change(void *user_data, pin_t pin, uint32_t value) 
{
  chip_state_t *chip = (chip_state_t*)user_data;
  // Update the register value or handle other pin change logic if needed
  chip_update(chip);
}
void chip_init() {
chip_state_t *chip = malloc(sizeof(chip_state_t));

  // Initialize inputs
  chip->FIN0 = pin_init("FIN0", INPUT_PULLDOWN);
  chip->FIN1 = pin_init("FIN1", INPUT_PULLDOWN);
  chip->FIN2 = pin_init("FIN2", INPUT_PULLDOWN);
  chip->FIN3 = pin_init("FIN3", INPUT_PULLDOWN);
  chip->FIN4 = pin_init("FIN4", INPUT_PULLDOWN);
  chip->FIN5 = pin_init("FIN5", INPUT_PULLDOWN);
  chip->FIN6 = pin_init("FIN6", INPUT_PULLDOWN);
  chip->FIN7 = pin_init("FIN7", INPUT_PULLDOWN);

  
  chip->SIN0 = pin_init("SIN0", INPUT_PULLDOWN);
  chip->SIN1 = pin_init("SIN1", INPUT_PULLDOWN);
  chip->SIN2 = pin_init("SIN2", INPUT_PULLDOWN);
  chip->SIN3 = pin_init("SIN3", INPUT_PULLDOWN);
  chip->SIN4 = pin_init("SIN4", INPUT_PULLDOWN);
  chip->SIN5 = pin_init("SIN5", INPUT_PULLDOWN);
  chip->SIN6 = pin_init("SIN6", INPUT_PULLDOWN);
  chip->SIN7 = pin_init("SIN7", INPUT_PULLDOWN);
  
  
  
  chip->OUT0 = pin_init("OUT0", OUTPUT);
  chip->OUT1 = pin_init("OUT1", OUTPUT);
  chip->OUT2 = pin_init("OUT2", OUTPUT);
  chip->OUT3 = pin_init("OUT3", OUTPUT);
  chip->OUT4 = pin_init("OUT4", OUTPUT);
  chip->OUT5 = pin_init("OUT5", OUTPUT);
  chip->OUT6 = pin_init("OUT6", OUTPUT);
  chip->OUT7 = pin_init("OUT7", OUTPUT);
  
  chip->EN = pin_init("EN", INPUT_PULLDOWN);

  const pin_watch_config_t watch_config = 
  {
    .edge = BOTH,
    .pin_change = chip_pin_change,
    .user_data = chip
  };
  pin_watch(chip->FIN0, &watch_config);
  pin_watch(chip->FIN1, &watch_config);
  pin_watch(chip->FIN2, &watch_config);
  pin_watch(chip->FIN3, &watch_config);
  pin_watch(chip->FIN4, &watch_config);
  pin_watch(chip->FIN5, &watch_config);
  pin_watch(chip->FIN6, &watch_config);
  pin_watch(chip->FIN7, &watch_config);
  

  pin_watch(chip->SIN0, &watch_config);
  pin_watch(chip->SIN1, &watch_config);
  pin_watch(chip->SIN2, &watch_config);
  pin_watch(chip->SIN3, &watch_config);
  pin_watch(chip->SIN4, &watch_config);
  pin_watch(chip->SIN5, &watch_config);
  pin_watch(chip->SIN6, &watch_config);
  pin_watch(chip->SIN7, &watch_config);
  
  pin_watch(chip->EN, &watch_config);
  // Internal state

  chip->register_value = 0;
  // TODO: Additional initialization logic as needed

  // Update the initial state
  chip_update(chip);
}