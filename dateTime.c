#include <stdio.h>
#include <string.h>
#include "lcd.c"

struct dt{
	int hour24;
	int minute;
	int second;
	int daylight_savings;
};

void init_dt(struct dt * dt){
	dt -> hour24 = 16;
	dt -> minute = 30;
	dt -> second = 30;	
	dt -> daylight_savings = 0;
}

void init_alarm(struct dt * dt){
	dt -> hour24 = 16;
	dt -> minute = 30;
	dt -> second = 35;
	dt -> daylight_savings = 0;
}


void advanced_dt(struct dt * dt){
	++dt -> second;
    // minute
	if(60 == dt -> second){
		dt -> second = 0;
		++dt -> minute;

        // hours
		if(60 == dt -> minute){
			dt -> minute = 0;
			++dt -> hour24;

            // day
			if(24 == dt -> hour24){
				dt -> hour24 = 0;
			}
		}
	}
}

void advance_hour(struct dt * dt){
	++dt -> hour24;
	// day
	if(24 == dt -> hour24){
		dt -> hour24 = 0;
	}
}

void print_time_24hr(const struct dt * dt){
	char timeBuf[14];
	lcd_pos(0,0);
	sprintf(timeBuf, "   %02d:%02d:%02d",
		dt -> hour24,
		dt -> minute,
		dt -> second
	);
	lcd_puts(timeBuf);
}


void col_blink_print_time_24hr(const struct dt * dt){
	char timeBuf[14];
	lcd_pos(0,0);
	sprintf(timeBuf, "   %02d:%02d %02d",
	dt -> hour24,
	dt -> minute,
	dt -> second
	);
	lcd_puts(timeBuf);
}


void blink_time(const struct dt *dt){
	col_blink_print_time_24hr(dt);
}

void display_time(const struct dt *dt){
	print_time_24hr(dt);
}

void set_time(int hr, int min, int sec, struct dt *dt){
	dt -> hour24 = hr;
	dt -> minute = min;
	dt -> second = sec;
}

void edit_time_instruction(){
	char prompt_date[18];
	lcd_pos(0,0);
	sprintf(prompt_date, "   Set Alarm:");
	lcd_puts(prompt_date);
}

void edit_time_prompt(const int h,const int m,const int s){
	char timeBuf[20];
	lcd_pos(1,0);
	sprintf(timeBuf, "   %02d:%02d:%02d ",
		h,
		m,
		s
	);
	lcd_puts(timeBuf);
}

void INVALID_TIME(){
	char INVALID_PROMPT1[11];
	lcd_pos(0,0);
	sprintf(INVALID_PROMPT1,"   INVALID");
	lcd_puts(INVALID_PROMPT1);
	char INVALID_PROMPT2[8];
	lcd_pos(1,0);
	sprintf(INVALID_PROMPT2,"   TIME");
	lcd_puts(INVALID_PROMPT2);
}

void fill_time(int nkey, int count, int * h, int * m, int * s){
	switch(count)
	{
		case 0:
			*h += (nkey*10);
			break;
		case 1:
			*h += nkey;
			break;
		case 2:
			*m += (nkey*10);
			break;
		case 3:
			*m += nkey;
			break;
		case 4:
			*s += (nkey*10);
			break;
		case 5:
			*s += nkey;
			break;
		default:
			break;
	}
}

int checkTime(int h, int m, int s, struct dt *dt){
	if( h > 23 || m > 59 || s > 59){
		lcd_clr();
		INVALID_TIME();
		avr_wait(150);
		return 0;
	}
	else{
		set_time(h,m,s,dt);
		return 1;
	}
}

void EXIT_SETUP_PROMPT(){
	char EXIT_SETUP1[11];
	lcd_pos(0,0);
	sprintf(EXIT_SETUP1,"   EXITING");
	lcd_puts(EXIT_SETUP1);
	char EXIT_SETUP2[9];
	lcd_pos(1,0);
	sprintf(EXIT_SETUP2,"   SETUP");
	lcd_puts(EXIT_SETUP2);
}

void print_soundAlarm(){
	char alarmBuf[15];
	lcd_pos(1,0);
	sprintf(alarmBuf, "ALARM! ALARM!");
	lcd_puts(alarmBuf);
}

int isAlarm(const struct dt * curTime, const struct dt * alarm){
	if(curTime -> hour24 == alarm -> hour24 &&
	curTime -> minute == alarm -> minute &&
	curTime -> second == alarm -> second){
		return 1;
	}
	return 0;
}

void print_isAlarm(const int* alarmSet){
	char alarmBuf[15];
	lcd_pos(1,0);
	if(*alarmSet == 1){
		sprintf(alarmBuf, "   ALARM:On");
	}
	else{
		sprintf(alarmBuf, "   ALARM:Off");
	}
	lcd_puts(alarmBuf);
}