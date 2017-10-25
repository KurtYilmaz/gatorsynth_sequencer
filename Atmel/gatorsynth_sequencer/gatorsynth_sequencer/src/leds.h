
#ifndef LEDS_H_
#define LEDS_H_


void leds_update_cursor(uint8_t curr_led);
void leds_update_note(uint8_t led_pos);
void leds_update_display(void);
void led_toggle(uint8_t top_row, uint8_t bottom_row);
int leds_status_get(uint8_t curr_step);


#endif /* LEDS_H_ */