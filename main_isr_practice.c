#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

const int BTN_PIN_R = 28;

// ERRO: cppcheck unitvar
// ERRO: addon IsrVarVolatile
volatile int btn_flag;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge

    // ERRO: addon IsrPrintf
    // ERRO: addon IsrNoLoop
    while (!pio_get(BTN_PIN_R)) {
      // ERRO: addon IsrNoDelay
      sleep_ms(1);
    }

    // ERRO: addon IsrPrintf
    printf("btn released \n");

    // ERRO: addon IsrNoDelay
    sleep_ms(1);
    btn_flag = 1;
  }
}

int main() {
  stdio_init_all();
  gpio_init(BTN_PIN_R);
  gpio_set_dir(BTN_PIN_R, GPIO_IN);
  gpio_pull_up(BTN_PIN_R);
  gpio_set_irq_enabled_with_callback(BTN_PIN_R, GPIO_IRQ_EDGE_FALL, true,
                                     &btn_callback);

  volatile int capture_flag = 0;
  int a;
  while (1) {
    if (btn_flag) {
      capture_flag = 1;
      btn_flag = 0;
    }

    if (capture_flag) {
    }
    
  }
}
