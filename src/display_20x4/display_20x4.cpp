/* 
    THIS MODULE IS HARDWARE DEPENDENT
    IF YOU WANT TO CHANGE THE LCD YOU ARE USING
    YOU HAVE TO IMPLEMENT YOUR OWN FILE
    DONT CHANGE HEADER FILE SINCE THE UI WILL USE IT
*/
#include "display_20x4.h"
#include <LiquidCrystal_I2C.h>
#include "config.h"
static enum {
    DISPLAY_BOOT_SCREEN,
    DISPLAY_CURRENT_TIME,
    DISPLAY_MENU,
    DISPLAY_SETTING_TIME,
    DISPLAY_SETTING_TIMER_CHOOSE,
    DISPLAY_SETTING_TIMER_SETTING
} last_display;
#define LCD_I2C_ADDR 0x27 // just a random number now
#define LCD_PRINTF_LINE0(...) sprintf(lcd_buffer[0],__VA_ARGS__)
#define LCD_PRINTF_LINE1(...) sprintf(lcd_buffer[1],__VA_ARGS__)
#define LCD_PRINTF_LINE2(...) sprintf(lcd_buffer[2],__VA_ARGS__)
#define LCD_PRINTF_LINE3(...) sprintf(lcd_buffer[3],__VA_ARGS__)
LiquidCrystal_I2C lcd(LCD_I2C_ADDR, 20, 4); 

char lcd_buffer[4][25]; // buffer for our lcd, a little spare in case we write over buffer
/*                      PRIVATE FUNCTIONS PROTOTYPE         */
void display_display();
void display_clear();
/*                      PUBLIC FUNCTIONS                    */
void display_init(){
  //lcd.init() will re init I2C module, which affect previous setting
  lcd.init();
  lcd.noBacklight();
  lcd.backlight();
  for(int i = 0; i < 4;i++)
  {
    memset(lcd_buffer[i], 0x0, sizeof(lcd_buffer[i]));
  }
}
void display_boot_screen(){
  display_clear();
  last_display = DISPLAY_BOOT_SCREEN;
  LCD_PRINTF_LINE0("|------------------|");
  LCD_PRINTF_LINE1("|    Multi Timer   |");
  LCD_PRINTF_LINE2("|    Version %d.%d   |",CONFIG_MAJOR_VER, CONFIG_MINOR_VER);
  LCD_PRINTF_LINE3("|______by PHB______|");
  display_display();
}
#if 1
void display_current_time(time_t cur_time){
  if(last_display != DISPLAY_CURRENT_TIME){
      display_clear();
      last_display = DISPLAY_CURRENT_TIME;
  }
  static const char * weekday[7]={
      "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
  };
  /*
  LCD_PRINTF_LINE0("--------------------");
  LCD_PRINTF_LINE1("|      22:22:22    |");
  LCD_PRINTF_LINE2("|     10/12/2020   |");
  LCD_PRINTF_LINE3("---------SUN--------");
  */
  LCD_PRINTF_LINE0("--------------------");
  LCD_PRINTF_LINE1("|     %02d:%02d:%02d     |", cur_time.hour, cur_time.minute, cur_time.second);
  LCD_PRINTF_LINE2("|    %02d/%02d/%04d    |", cur_time.day, cur_time.month, cur_time.year);
  LCD_PRINTF_LINE3("------- %s --------", weekday[cur_time.weekday]);
  display_display();
}
#endif
void display_menu(const char * title[], uint8_t cursor, uint8_t max_cursor_pos){
    if(last_display != DISPLAY_MENU){
        display_clear();
        last_display = DISPLAY_MENU;
    }
    /*determine what item to be displayed */
    /*each page will have 3 item (3 lines) */
    //determine the page
    uint8_t page = cursor/3;
    // the last page may not have full 3 items(when the number of item is not multiply of 3)
    // but a page must have at least 1 item, so in 1st item we dont check
    const char * title1 = title[(page*3)];
    const char * title2 = (page*3 + 1) <= max_cursor_pos ? title[ (page*3 + 1)]:"               ";
    const char * title3 = (page*3 + 2) <= max_cursor_pos ? title[ (page*3 + 2)]:"               ";
    /*
    LCD_PRINTF_LINE0("--------MENU--------");
    LCD_PRINTF_LINE1("  16charmenutitle_  ");
    LCD_PRINTF_LINE2("> 16charmenutitle_  ");
    LCD_PRINTF_LINE3("  16charmenutitle_  ");
    */
    LCD_PRINTF_LINE0("--------MENU--------");
    LCD_PRINTF_LINE1("  %s  ",title1);
    LCD_PRINTF_LINE2("  %s  ",title2);
    LCD_PRINTF_LINE3("  %s  ",title3);
    /*display cursor*/
    lcd_buffer[(cursor%3)+1][0] = '>';
    display_display();
}
void display_setting_time(uint16_t * setting, uint8_t cursor){
    if(last_display != DISPLAY_SETTING_TIME){
        display_clear();
        last_display = DISPLAY_SETTING_TIME;
    }
    const char * weekday[7]={
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };
    const uint8_t cursor_map_pos[7] ={0,6,13,0,6,12,4};
    const uint8_t cursor_map_line[7]={1,1,1,2,2,2,3};
    /*
    LCD_PRINTF_LINE0("----SETTING TIME----");
    LCD_PRINTF_LINE1(" Hr:06 Min:23 Sec:20");
    LCD_PRINTF_LINE2(" DD:12 MM:06 YY:2012"); 
    LCD_PRINTF_LINE3("     Weekday:Sun    ");
    */
    LCD_PRINTF_LINE0("----SETTING TIME----");
    LCD_PRINTF_LINE1(" Hr:%02d Min:%02d Sec:%02d",setting[0],setting[1],setting[2]);
    LCD_PRINTF_LINE2(" DD:%02d MM:%02d YY:%04d",setting[5],setting[4],setting[3]); 
    LCD_PRINTF_LINE3("     Weekday:%s    ",weekday[setting[6]] );
    lcd_buffer[cursor_map_line[cursor]][cursor_map_pos[cursor]] = '>';
    display_display();
}
void display_setting_timer_choose(uint16_t timer_id){
    if(last_display != DISPLAY_SETTING_TIMER_CHOOSE){
        display_clear();
        last_display = DISPLAY_SETTING_TIMER_CHOOSE;
    }
    /*
    LCD_PRINTF_LINE0("----CHOOSE TIMER----");
    LCD_PRINTF_LINE1("                    ");
    LCD_PRINTF_LINE2("    < TIMER 10 >    ");
    LCD_PRINTF_LINE3("                    ");
    */ 
    LCD_PRINTF_LINE0("----CHOOSE TIMER----");
    LCD_PRINTF_LINE1("                    ");
    LCD_PRINTF_LINE2("    < TIMER %02d >    ",timer_id);
    LCD_PRINTF_LINE3("                    ");  
    display_display();
}
void display_setting_timer_setting(uint16_t * setting, uint8_t cursor){
    if(last_display != DISPLAY_SETTING_TIMER_SETTING){
        display_clear();
        last_display = DISPLAY_SETTING_TIMER_SETTING;
    }
    const uint8_t cursor_map_pos[7] ={1,7,13,0,14,0,11};
    const uint8_t cursor_map_line[7]={1,1,1,2,2,3,3};
    const char * state_string[2] = {"DIS","ENA"};
    const char yes_no_char[2] = {'N','Y'};
    /*
    LCD_PRINTF_LINE0("------SET TIMER-----");
    LCD_PRINTF_LINE1("  HR:01 MM:20 SS:12 ");
    LCD_PRINTF_LINE2(" Value:1201   Ch:12 ");
    LCD_PRINTF_LINE3(" 1shot:Y   State:Dis");
    */
    LCD_PRINTF_LINE0("------SET TIMER-----");
    LCD_PRINTF_LINE1("  HH:%02d MM:%02d SS:%02d ",setting[0],setting[1],setting[2]);
    LCD_PRINTF_LINE2(" Value:%04d   Ch:%02d ",setting[3],setting[4]);
    LCD_PRINTF_LINE3(" 1shot:%c   State:%s",yes_no_char[setting[6]],state_string[setting[5]]);
    lcd_buffer[cursor_map_line[cursor]][cursor_map_pos[cursor]] = '>';
    display_display();
}
/*                      PRIVATE FUNCTIONS                   */
/*  print the buffer to lcd   */
void display_display(){
  for(int i=0; i < 4; i++){
    lcd.setCursor(0,i);
    lcd.print(lcd_buffer[i]);
  }
}
void display_clear(){
  lcd.clear();
}

