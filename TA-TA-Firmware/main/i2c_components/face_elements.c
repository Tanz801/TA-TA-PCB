#include "u8g2.h"

#include "face_elements.h"

static const u8g2_uint_t CIRCLE_R = 12;
static const u8g2_uint_t line_thickness = 4;

static void draw_eye_round(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y) {
    u8g2_DrawEllipse(u8g2, x, y, CIRCLE_R, CIRCLE_R, U8G2_DRAW_ALL);
}

static void draw_eye_round_filled(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y) {
    u8g2_DrawFilledEllipse(u8g2, x, y, CIRCLE_R, CIRCLE_R, U8G2_DRAW_ALL);
}

static void draw_eye_happy_semicircle(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y) {
    u8g2_uint_t radius;
    for (u8g2_int_t line = 0; line < line_thickness; line++) {
        radius = CIRCLE_R - (line_thickness/2) + line;
        u8g2_DrawEllipse(u8g2, x, (int) (y + CIRCLE_R/2), radius, radius, U8G2_DRAW_UPPER_LEFT);
        u8g2_DrawEllipse(u8g2, x, (int) (y + CIRCLE_R/2), radius, radius, U8G2_DRAW_UPPER_RIGHT);
    }
}


eye_element_fn draw_eyes[] = {
    draw_eye_round,
    draw_eye_round_filled,
    draw_eye_happy_semicircle
};

void draw_eye(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, int num) {
    draw_eyes[num](u8g2, x, y);
}


static void draw_large_v_mouth (u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y) {

    const u8g2_uint_t half_width = 6;
    u8g2_uint_t start_y = y - 13;
    u8g2_uint_t end_y = y + 8;

    for (u8g2_int_t line = 0; line < line_thickness; line++) {
        u8g2_DrawLine(u8g2, (x - half_width) - (line_thickness/2) + line, start_y, x - (line_thickness/2) + line, end_y);
        //mirrored line
        u8g2_DrawLine(u8g2, (x + half_width) + (line_thickness/2) - line, start_y, x + (line_thickness/2) - line, end_y);
    }
}


mouth_element_fn draw_mouths[] = {
    draw_large_v_mouth
};

void draw_mouth(u8g2_t *u8g2, u8g2_uint_t x, u8g2_uint_t y, int num) {
    draw_mouths[num](u8g2, x, y);
}
