#ifndef _exinisr_h
#define _exinisr_h
#ifdef __cplusplus
extern "C"
{
#endif
extern uint8_t add_positionx,add_positiony;
extern uint8_t eeprom_positionx_middle,eeprom_positiony_middle,eeprom_positionx_left_up,eeprom_positiony_left_up,eeprom_positionx_right_up,eeprom_positiony_right_up;
extern uint8_t eeprom_positionx_left_down,eeprom_positiony_left_down,eeprom_positionx_right_down,eeprom_positiony_right_down;
extern uint8_t eeprom_flag;
extern uint8_t init_lock;
#ifdef __cplusplus
}
#endif

#endif
