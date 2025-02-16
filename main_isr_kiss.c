#include "asf.h"

volatile int g_cnt = 0;
volatile char g_but_flag = 0;

// This code creates a progress bar on an OLED screen that
// increases when the button is pressed.

void btn_callback(uint gpio, uint32_t events) {
  g_but_flag = 1; 
}


void update_display(void) {
  char g_str[10];
  if (g_but_flag){
    
    g_but_flag = 0;
    if (g_cnt >= 8){
      g_cnt = 0;
    }else{
      g_cnt = 2;
    }

    for (i = 0; i < g_cnt; i++) {
        g_str[i] = '*';
      }
    g_str[g_cnt] = '\0';
    gfx_mono_draw_string(g_str, 0, 0, &sysfont);
  }
  
  
}

void main(void) {
  // ...
  gpio_set_irq_enabled_with_callback(BOTAO, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
  while (1) {
    update_display(); 
  }
}
