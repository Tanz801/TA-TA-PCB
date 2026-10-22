#pragma once

#include "u8g2.h"

typedef void (*face_element_fn)(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y);

typedef face_element_fn eye_element_fn;
typedef face_element_fn mouth_element_fn;

void draw_eye(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, int num);
void draw_mouth(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, int num);