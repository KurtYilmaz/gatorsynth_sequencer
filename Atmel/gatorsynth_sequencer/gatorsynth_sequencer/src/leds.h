
#ifndef LEDS_H_
#define LEDS_H_


void leds_update_cursor(uint8_t curr_led);
void leds_update_note(uint8_t led_pos);
void leds_update_display();
void leds_save_prev();

#endif /* LEDS_H_ */