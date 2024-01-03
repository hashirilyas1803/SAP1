// Wokwi Custom Chip - For docs and examples see:
// https://docs.wokwi.com/chips-api/getting-started
//
// SPDX-LiceNse-IdeNtifier: MIT
// Copyright 2023 Saad Imam

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>

int value1 = 0;
int value2 = 0;

typedef struct {
  pin_t FOUT0;
  pin_t FOUT1;
  pin_t FOUT2;
  pin_t FOUT3;
  pin_t FOUT4;
  pin_t FOUT5;
  pin_t FOUT6;
  pin_t FOUT7;
  pin_t FOUT8;
  pin_t FOUT9;
  pin_t FOUTA;
  pin_t FOUTB;
  pin_t FOUTC;
  pin_t FOUTD;
  pin_t FOUTE;
  pin_t FOUTF;
  
  
  // outputs
  pin_t SOUT0;
  pin_t SOUT1;
  pin_t SOUT2;
  pin_t SOUT3;
  pin_t SOUT4;
  pin_t SOUT5;
  pin_t SOUT6;
  pin_t SOUT7;
  pin_t SOUT8;
  pin_t SOUT9;
  pin_t SOUTA;
  pin_t SOUTB;
  pin_t SOUTC;
  pin_t SOUTD;
  pin_t SOUTE;
  pin_t SOUTF;
  
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

  
  pin_t EN;
  pin_t S;
} chip_state_t;

void chip_update(chip_state_t *chip) {
  if (pin_read(chip->S)) {
    const pin_t* IN[] = {&chip->IN0, &chip->IN1, &chip->IN2, &chip->IN3, &chip->IN4, &chip->IN5, &chip->IN6, &chip->IN7, &chip->IN8, &chip->IN9, &chip->INA, &chip->INB, &chip->INC, &chip->IND, &chip->INE, &chip->INF};
    const pin_t* FOUT[] = {&chip->FOUT0, &chip->FOUT1, &chip->FOUT2, &chip->FOUT3, &chip->FOUT4, &chip->FOUT5, &chip->FOUT6, &chip->FOUT7, &chip->FOUT8, &chip->FOUT9, &chip->FOUTA, &chip->FOUTB, &chip->FOUTC, &chip->FOUTD, &chip->FOUTE, &chip->FOUTF};    
    const pin_t* SOUT[] = {&chip->SOUT0, &chip->SOUT1, &chip->SOUT2, &chip->SOUT3, &chip->SOUT4, &chip->SOUT5, &chip->SOUT6, &chip->SOUT7, &chip->SOUT8, &chip->SOUT9, &chip->SOUTA, &chip->SOUTB, &chip->SOUTC, &chip->SOUTD, &chip->SOUTE, &chip->SOUTF};    
    

    if(pin_read(chip->EN) == 0){
      value1 = 0;
      for (int i = 0; i < 16; i++) {
        value1 |= (pin_read(*IN[i]) & 1) << i;
      }
      for (int i = 0; i < 16; i++) {
        pin_write(*FOUT[i], (value1 >> i) & 1);
      }
    }
    else{
      value2 = 0;
      for (int i = 0; i < 16; i++) {
        value2 |= (pin_read(*IN[i]) & 1) << i;
      }
      for (int i = 0; i < 16; i++) {
        pin_write(*SOUT[i], (value2 >> i) & 1);
      }
      value1 = 0;
      value2 = 0;
    }
  }
  // int temp1 = 5;
  // int temp2 = 2;
  // for (int i = 0; i < 16; i++) {
  //   pin_write(*FOUT[i], (temp1 >> i) & 1);
  // }
  // for (int i = 0; i < 16; i++) {
  //   pin_write(*SOUT[i], (temp2 >> i) & 1);
  // }

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
  
  chip->SOUT0 = pin_init("SOUT0", OUTPUT);
  chip->SOUT1 = pin_init("SOUT1", OUTPUT);
  chip->SOUT2 = pin_init("SOUT2", OUTPUT);
  chip->SOUT3 = pin_init("SOUT3", OUTPUT);
  chip->SOUT4 = pin_init("SOUT4", OUTPUT);
  chip->SOUT5 = pin_init("SOUT5", OUTPUT);
  chip->SOUT6 = pin_init("SOUT6", OUTPUT);
  chip->SOUT7 = pin_init("SOUT7", OUTPUT);
  chip->SOUT8 = pin_init("SOUT8", OUTPUT);
  chip->SOUT9 = pin_init("SOUT9", OUTPUT);
  chip->SOUTA = pin_init("SOUTA", OUTPUT);
  chip->SOUTB = pin_init("SOUTB", OUTPUT);
  chip->SOUTC = pin_init("SOUTC", OUTPUT);
  chip->SOUTD = pin_init("SOUTD", OUTPUT);
  chip->SOUTE = pin_init("SOUTE", OUTPUT);
  chip->SOUTF = pin_init("SOUTF", OUTPUT);
  
  
  chip->FOUT0 = pin_init("FOUT0", OUTPUT);
  chip->FOUT1 = pin_init("FOUT1", OUTPUT);
  chip->FOUT2 = pin_init("FOUT2", OUTPUT);
  chip->FOUT3 = pin_init("FOUT3", OUTPUT);
  chip->FOUT4 = pin_init("FOUT4", OUTPUT);
  chip->FOUT5 = pin_init("FOUT5", OUTPUT);
  chip->FOUT6 = pin_init("FOUT6", OUTPUT);
  chip->FOUT7 = pin_init("FOUT7", OUTPUT);
  chip->FOUT8 = pin_init("FOUT8", OUTPUT);
  chip->FOUT9 = pin_init("FOUT9", OUTPUT);
  chip->FOUTA = pin_init("FOUTA", OUTPUT);
  chip->FOUTB = pin_init("FOUTB", OUTPUT);
  chip->FOUTC = pin_init("FOUTC", OUTPUT);
  chip->FOUTD = pin_init("FOUTD", OUTPUT);
  chip->FOUTE = pin_init("FOUTE", OUTPUT);
  chip->FOUTF = pin_init("FOUTF", OUTPUT);
  
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
  
  // Initialize Read and Write pins
  chip->EN = pin_init("EN", INPUT_PULLDOWN);
  chip->S = pin_init("S", INPUT_PULLDOWN);
  
  pin_watch(chip->EN, &watch_config);
  pin_watch(chip->S, &watch_config);
  
  

  // Internal state

  // TODO: Additional initialization logic as needed

  // Update the initial state
  chip_update(chip);
}