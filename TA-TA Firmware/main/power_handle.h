#pragma once


void power_setup(int button_one, int button_two);

void power_handle_main(void* args);

void gpio_isr_handle(void* args);