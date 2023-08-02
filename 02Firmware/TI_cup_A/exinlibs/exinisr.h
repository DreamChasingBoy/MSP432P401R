#ifndef _exinisr_h
#define _exinisr_h
#ifdef __cplusplus
extern "C"
{
#endif
extern float add_anglex,add_angley;
extern float eeprom_anglex_middle,eeprom_angley_middle,eeprom_anglex_left_up,eeprom_angley_left_up,eeprom_anglex_right_up,eeprom_angley_right_up;
extern float eeprom_anglex_left_down,eeprom_angley_left_down,eeprom_anglex_right_down,eeprom_angley_right_down;
extern uint8_t eeprom_flag;
extern uint8_t init_lock;
#ifdef __cplusplus
}
#endif

#endif
