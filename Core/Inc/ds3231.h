/*
 * DS3231.h
 *
 * DS3231 Real-Time Clock library
 * base on code by Eric Ayars 4/1/11 (updated John Hubert Feb 7, 2012)
 * adapted by STM32 (C HAL) abelov80 05/2023
 *
 */

#ifndef DS3231_h
#define DS3231_h

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

/* Description of register DS3231 */

#define DS3231_REG_SECOND 0x00
#define DS3231_REG_MINUTE 0x01
#define DS3231_REG_HOUR 0x02
#define DS3231_REG_DAY 0x03
#define DS3231_REG_DATE 0x04
#define DS3231_REG_MONTH 0x05
#define DS3231_REG_YEAR 0x06
#define DS3231_REG_ALM1_SEC 0x07
#define DS3231_REG_ALM1_MIN 0x08
#define DS3231_REG_ALM1_HOUR 0x09
#define DS3231_REG_ALM1_DATE 0x0A
#define DS3231_REG_ALM2_MIN 0x0B
#define DS3231_REG_ALM2_HOUR 0x0C
#define DS3231_REG_ALM2_DATE 0x0D
#define DS3231_REG_CTRL 0x0E
#define DS3231_REG_STAT 0x0F
#define DS3231_REG_OFFSET 0x10
#define DS3231_REG_MSBTEMP 0x11
#define DS3231_REG_LSBTEMP 0x12

#define byte unsigned char
#define bool unsigned char

/**
 * @brief Convert normal decimal numbers to binary coded decimal
 */
byte decToBcd(byte val);
/**
 * @brief Convert binary coded decimal to normal decimal numbers
 */
byte bcdToDec(byte val);
/**
 * @brief Read flag BUSY status register
 * @retval 1 - busy, 0 - free
 */
byte getBusy();
/**
 * @brief Read second value
 */
byte getSecond();
/**
 * @brief Read minute value
 */
byte getMinute();
/**
 * @brief Read hour value
 */
byte getHour();
/**
 * @brief Read day of week value
 */
byte getDoW();
/**
 * @brief Read day of month value
 */
byte getDate();
/**
 * @brief Read month value
 */
byte getMonth();
/**
 * @brief Read year value (only 2 digit 0..99)
 */
byte getYear();
/**
 * @brief Write second value
 */
void setSecond(byte Second);
/**
 * @brief Write minute value
 */
void setMinute(byte Minute);
/**
 * @brief Write hour value
 */
void setHour(byte Hour);
/**
 * @brief Write day of week value
 */
void setDoW(byte DoW);
/**
 * @brief Write day of month value
 */
void setDate(byte Date);
/**
 * @brief Write month value
 */
void setMonth(byte Month);
/**
 * @brief Write year value (only 2 digit 0..99)
 */
void setYear(byte Year);
/**
 * @brief Convert time to string. Format "00:00:00"
 * @retval errorcode (0 - no error)
 */
unsigned char timeToStr(char *strBuf, byte hour, byte minute, byte second);
/**
 * @brief Set second to first alarm
 * @param byte Number of second to set (0..59)
 * @param byte Flag alarm. If the alarm clock is on, consider the value of seconds in the comparison. (0..1)
 */
byte setAlarm_Sec(byte sec, byte alarmSet);
/**
 * @brief Set minute to alarm
 * @param byte Number of alarm to set (1..2)
 * @param byte Number of minutes to set (0..59)
 * @param byte Flag alarm. If the alarm clock is on, consider the value of minutes in the comparison. (0..1)
 */
byte setAlarm_Min(byte numA, byte min, byte alarmSet);
/**
 * @brief Set hour to alarm
 * @param byte Number of alarm to set (1..2)
 * @param byte Number of hours to set (0..59)
 * @param byte Flag alarm. If the alarm clock is on, consider the value of hour in the comparison. (0..1)
 */
byte setAlarm_Hour(byte numA, byte hour, byte alarmSet);
/**
 * @brief Set day to alarm
 * @param byte Number of alarm to set (1..2)
 * @param byte Number of days to set (0..7 or 0..31 depending on parameter Flag alarm)
 * @param byte Flag alarm. If the alarm clock is on, consider the value of minutes in the comparison. (0..3)
 * 				0 and 1 - not consider the value days
 * 				2 - consider the value with day of month
 * 				3 - consider the value with day of week
 */
byte setAlarm_Date(byte numA, byte date, byte alarmSet);
/**
 * @brief Set frequency on pin INT/SQW when the alarm is turn on.
 * @param byte: 0 - 1KHz, 1 - 1.024kHz, 2 - 4.096kHz, 3 - 8.192kHz
 */
byte setAlarmFrequency(byte value);
/**
 * @brief Turn on alarm
 * @param byte Number of alarm to set (1 - Turn On alarm 1, 2 - .. alarm 2, 3 - .. alarm 1 and 2)
 */
byte setAlarm(byte numAlarm);
/**
 * @brief Enable oscillator (run clock)
 */
byte clockEnable(void);

// Temperature function
//float getTemperature();

// Alarm functions
//void getA1Time(byte& A1Day, byte& A1Hour, byte& A1Minute, byte& A1Second, byte& AlarmBits, bool& A1Dy, bool& A1h12, bool& A1PM);
	/* Retrieves everything you could want to know about alarm
	 * one.
	 * A1Dy true makes the alarm go on A1Day = Day of Week,
	 * A1Dy false makes the alarm go on A1Day = Date of month.
	 *
	 * byte AlarmBits sets the behavior of the alarms:
	 *	Dy	A1M4	A1M3	A1M2	A1M1	Rate
	 *	X	1		1		1		1		Once per second
	 *	X	1		1		1		0		Alarm when seconds match
	 *	X	1		1		0		0		Alarm when min, sec match
	 *	X	1		0		0		0		Alarm when hour, min, sec match
	 *	0	0		0		0		0		Alarm when date, h, m, s match
	 *	1	0		0		0		0		Alarm when DoW, h, m, s match
	 *
	 *	Dy	A2M4	A2M3	A2M2	Rate
	 *	X	1		1		1		Once per minute (at seconds = 00)
	 *	X	1		1		0		Alarm when minutes match
	 *	X	1		0		0		Alarm when hours and minutes match
	 *	0	0		0		0		Alarm when date, hour, min match
	 *	1	0		0		0		Alarm when DoW, hour, min match
	 */
//	void getA2Time(byte& A2Day, byte& A2Hour, byte& A2Minute, byte& AlarmBits, bool& A2Dy, bool& A2h12, bool& A2PM);
// Same as getA1Time();, but A2 only goes on seconds == 00.
//	void setA1Time(byte A1Day, byte A1Hour, byte A1Minute, byte A1Second,
//	byte AlarmBits, bool A1Dy, bool A1h12, bool A1PM);
// Set the details for Alarm 1
//	void setA2Time(byte A2Day, byte A2Hour, byte A2Minute, byte AlarmBits,
//			bool A2Dy, bool A2h12, bool A2PM);
// Set the details for Alarm 2
//	void turnOnAlarm(byte Alarm);
// Enables alarm 1 or 2 and the external interrupt pin.
// If Alarm != 1, it assumes Alarm == 2.
//	void turnOffAlarm(byte Alarm);
// Disables alarm 1 or 2 (default is 2 if Alarm != 1);
// and leaves the interrupt pin alone.
//	bool checkAlarmEnabled(byte Alarm);
// Returns T/F to indicate whether the requested alarm is
// enabled. Defaults to 2 if Alarm != 1.
//	bool checkIfAlarm(byte Alarm);
// Checks whether the indicated alarm (1 or 2, 2 default);
// has been activated.

// Oscillator functions

//	void enableOscillator(bool TF, bool battery, byte frequency);
// turns oscillator on or off. True is on, false is off.
// if battery is true, turns on even for battery-only operation,
// otherwise turns off if Vcc is off.
// frequency must be 0, 1, 2, or 3.
// 0 = 1 Hz
// 1 = 1.024 kHz
// 2 = 4.096 kHz
// 3 = 8.192 kHz (Default if frequency byte is out of range);
//	void enable32kHz(bool TF);
// Turns the 32kHz output pin on (true); or off (false).
//	bool oscillatorCheck();
// Checks the status of the OSF (Oscillator Stop Flag);.
// If this returns false, then the clock is probably not
// giving you the correct time.
// The OSF is cleared by function setSecond();
// Time-retrieval functions

// the get*() functions retrieve current values of the registers.
// If you only need one element, use that one for simplicity; but
// if you need the whole passel then use getTime() to avoid
// the chance of rollover between reads of the different components.
//	void getTime(byte& year, byte& month, byte& date, byte& DoW, byte& hour, byte& minute, byte& second);

#ifdef __cplusplus
}
#endif

#endif
