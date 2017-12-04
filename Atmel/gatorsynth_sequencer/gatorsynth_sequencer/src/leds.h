
#ifndef LEDS_H_
#define LEDS_H_

uint16_t cursor_led_data1;
uint16_t cursor_led_data2;
uint16_t cursor_led_data3;

uint16_t note_led_data1;
uint16_t note_led_data2;
uint16_t note_led_data3;

uint8_t cursor_led_color;
uint8_t note_led_color;

#define off_led_data 0x0


void leds_update_cursor(uint8_t curr_led);
void leds_update_note(uint8_t led_pos);
void leds_update_display(void);
void led_toggle(uint8_t top_row, uint8_t bottom_row);
int leds_status_get(uint8_t curr_step);
void leds_update_status(void);
void led_init_colors(void);
void led_toggle_cursor(void);
void led_toggle_note(void);

#endif /* LEDS_H_ */