/*
 DS3231.c: DS3231 Real-Time Clock library
 base on code by Eric Ayars 4/1/11 (updated John Hubert Feb 7, 2012)
 adapted by STM32 (C HAL) abelov80 05/2023
 */

#include <DS3231.h>

#define CLOCK_ADDRESS 0x68

extern I2C_HandleTypeDef hi2c1;

byte decToBcd(byte val) {
	return (val / 10 * 16) + (val % 10);
}

byte bcdToDec(byte val) {
	return ((val & 0xF0) >> 4) * 10 + (val & 0x0F);
}

byte rwByte(bool write, byte reg, byte value) {
	if (write) {
		byte sendbuf[2] = { reg, value };
		HAL_I2C_Master_Transmit(&hi2c1, CLOCK_ADDRESS << 1, sendbuf,
				sizeof(byte) * 2, 100);
		return 0;
	}
	byte result = 0;
	HAL_I2C_Master_Transmit(&hi2c1, CLOCK_ADDRESS << 1, &reg, sizeof(byte),
			100);
	HAL_I2C_Master_Receive(&hi2c1, CLOCK_ADDRESS << 1, &result, sizeof(byte),
			100);
	return result;
}

byte getBusy() {
	byte value = DS3231_REG_STAT;
	HAL_I2C_StateTypeDef result;
	result = HAL_I2C_Master_Transmit(&hi2c1, CLOCK_ADDRESS << 1, &value,
			sizeof(byte), 1);
	if (result != HAL_I2C_STATE_READY)
		return 1;
	result = HAL_I2C_Master_Receive(&hi2c1, CLOCK_ADDRESS << 1, &value,
			sizeof(byte), 1);
	if (result != HAL_I2C_STATE_READY)
		return 1;
	return (value >> 2) & 0x01;
}

byte getSecond() {
	return bcdToDec(rwByte(0, DS3231_REG_SECOND, 0));
}

byte getMinute() {
	return bcdToDec(rwByte(0, DS3231_REG_MINUTE, 0));
}

byte getHour() {
	return bcdToDec(rwByte(0, DS3231_REG_HOUR, 0) & 0x3F);
}

byte getDoW() {
	return rwByte(0, DS3231_REG_DAY, 0);
}

byte getDate() {
	return bcdToDec(rwByte(0, DS3231_REG_DATE, 0));
}

byte getMonth() {
	return bcdToDec(rwByte(0, DS3231_REG_MONTH, 0) & 0x1F);
}

byte getYear() {
	return bcdToDec(rwByte(0, DS3231_REG_YEAR, 0));
}

void setSecond(byte Second) {
	rwByte(1, DS3231_REG_SECOND, decToBcd(Second));
	clockEnable();
}

void setMinute(byte Minute) {
	rwByte(1, DS3231_REG_MINUTE, decToBcd(Minute));
}

void setHour(byte Hour) {
	rwByte(1, DS3231_REG_HOUR, decToBcd(Hour) & 0x3F);
}

void setDoW(byte DoW) {
	rwByte(1, DS3231_REG_DAY, decToBcd(DoW));
}

void setDate(byte Date) {
	rwByte(1, DS3231_REG_DATE, decToBcd(Date));
}

void setMonth(byte Month) {
	rwByte(1, DS3231_REG_MONTH, decToBcd(Month));
}

void setYear(byte Year) {
	rwByte(1, DS3231_REG_YEAR, decToBcd(Year));
}

unsigned char timeToStr(char *strBuf, byte hour, byte minute, byte second) {
	if (hour < 10) {
		strBuf[0] = '0';
		strBuf[1] = hour + '0';
	} else {
		strBuf[0] = hour / 10 + '0';
		strBuf[1] = hour % 10 + '0';
	}
	strBuf[2] = ':';
	if (minute < 10) {
		strBuf[3] = '0';
		strBuf[4] = minute + '0';
	} else {
		strBuf[3] = minute / 10 + '0';
		strBuf[4] = minute % 10 + '0';
	}
	strBuf[5] = ':';
	if (second < 10) {
		strBuf[6] = '0';
		strBuf[7] = second + '0';
	} else {
		strBuf[6] = second / 10 + '0';
		strBuf[7] = second % 10 + '0';
	}
	return 0;
}

byte setAlarm_Sec(byte sec, byte alarmSet) {
	return rwByte(1, DS3231_REG_ALM1_SEC, decToBcd(sec | (alarmSet << 7)));
}

byte setAlarm_Min(byte numA, byte min, byte alarmSet) {
	switch (numA) {
		case 1:
			return rwByte(1, DS3231_REG_ALM1_MIN, decToBcd(min | (alarmSet << 7)));
			break;
		case 2:
			return rwByte(1, DS3231_REG_ALM2_MIN, decToBcd(min | (alarmSet << 7)));
			break;
		default:
			return HAL_ERROR;
			break;
	}
}

byte setAlarm_Hour(byte numA, byte hour, byte alarmSet) {
	switch (numA) {
		case 1:
			return rwByte(1, DS3231_REG_ALM1_HOUR, decToBcd(hour | (alarmSet << 7)));
			break;
		case 2:
			return rwByte(1, DS3231_REG_ALM2_HOUR, decToBcd(hour | (alarmSet << 7)));
			break;
		default:
			return HAL_ERROR;
			break;
	}
}

byte setAlarm_Date(byte numA, byte date, byte alarmSet) {
	switch (numA) {
			case 1:
				return rwByte(1, DS3231_REG_ALM1_DATE, decToBcd(date | (alarmSet << 6)));
				break;
			case 2:
				return rwByte(1, DS3231_REG_ALM2_DATE, decToBcd(date | (alarmSet << 6)));
				break;
			default:
				return HAL_ERROR;
				break;
		}
}

byte setAlarmFrequency(byte value) {
	byte result = rwByte(0, DS3231_REG_CTRL, 0); // Read Control register
	return rwByte(1, DS3231_REG_CTRL, (result & 0b11100111) | (value << 3)); // Insert Freq value and write
}

byte setAlarm(byte numAlarm) {
	byte result = rwByte(0, DS3231_REG_CTRL, 0); // Read Control register
	return rwByte(1, DS3231_REG_CTRL, (result & 0b11111100) | numAlarm); // Insert Alarm value and write
}

byte clockEnable(void) {
	byte result = rwByte(0, DS3231_REG_CTRL, 0); // Read Control register
	result = result | 0b00000100; // Enable INTCN bit (Enable INT/SQW pin on alarm)
	return rwByte(1, DS3231_REG_CTRL, result & 0b01111111); // Insert "Enable oscillator" and write
}

byte clearAlarmFlag(byte numAlarm) {
	byte result = rwByte(0, DS3231_REG_STAT, 0); // Read Status register
	return rwByte(1, DS3231_REG_CTRL, result & (numAlarm | 0b11111100)); // Write flag bit
}

/*
 float getTemperature() {
 // Checks the internal thermometer on the DS3231 and returns the
 // temperature as a floating-point value.
 byte temp;
 Wire.beginTransmission(CLOCK_ADDRESS);
 Wire.write(uint8_t(0x11));
 Wire.endTransmission();

 Wire.requestFrom(CLOCK_ADDRESS, 2);
 temp = Wire.read();	// Here's the MSB
 return float(temp) + 0.25*(Wire.read()>>6);
 }

 void getA1Time(byte& A1Day, byte& A1Hour, byte& A1Minute, byte& A1Second, byte& AlarmBits, bool& A1Dy, bool& A1h12, bool& A1PM) {
 byte temp_buffer;
 Wire.beginTransmission(CLOCK_ADDRESS);
 Wire.write(uint8_t(0x07));
 Wire.endTransmission();

 Wire.requestFrom(CLOCK_ADDRESS, 4);

 temp_buffer = Wire.read();	// Get A1M1 and A1 Seconds
 A1Second = bcdToDec(temp_buffer & 0b01111111);
 // put A1M1 bit in position 0 of DS3231_AlarmBits.
 AlarmBits = AlarmBits | (temp_buffer & 0b10000000)>>7;

 temp_buffer = Wire.read();// Get A1M2 and A1 minutes
 A1Minute = bcdToDec(temp_buffer & 0b01111111);
 // put A1M2 bit in position 1 of DS3231_AlarmBits.
 AlarmBits = AlarmBits | (temp_buffer & 0b10000000)>>6;

 temp_buffer = Wire.read();// Get A1M3 and A1 Hour
 // put A1M3 bit in position 2 of DS3231_AlarmBits.
 AlarmBits = AlarmBits | (temp_buffer & 0b10000000)>>5;
 // determine A1 12/24 mode
 A1h12 = temp_buffer & 0b01000000;
 if (A1h12) {
 A1PM = temp_buffer & 0b00100000;			// determine am/pm
 A1Hour = bcdToDec(temp_buffer & 0b00011111);// 12-hour
 } else {
 A1Hour = bcdToDec(temp_buffer & 0b00111111);	// 24-hour
 }

 temp_buffer = Wire.read();	// Get A1M4 and A1 Day/Date
 // put A1M3 bit in position 3 of DS3231_AlarmBits.
 AlarmBits = AlarmBits | (temp_buffer & 0b10000000)>>4;
 // determine A1 day or date flag
 A1Dy = (temp_buffer & 0b01000000)>>6;
 if (A1Dy) {
 // alarm is by day of week, not date.
 A1Day = bcdToDec(temp_buffer & 0b00001111);
 } else {
 // alarm is by date, not day of week.
 A1Day = bcdToDec(temp_buffer & 0b00111111);
 }
 }



 bool checkAlarmEnabled(byte Alarm) {
 // Checks whether the given alarm is enabled.
 byte result = 0x0;
 byte temp_buffer = readControlByte(0);
 if (Alarm == 1) {
 result = temp_buffer & 0b00000001;
 } else {
 result = temp_buffer & 0b00000010;
 }
 return result;
 }

 bool checkIfAlarm(byte Alarm) {
 // Checks whether alarm 1 or alarm 2 flag is on, returns T/F accordingly.
 // Turns flag off, also.
 // defaults to checking alarm 2, unless Alarm == 1.
 byte result;
 byte temp_buffer = readControlByte(1);
 if (Alarm == 1) {
 // Did alarm 1 go off?
 result = temp_buffer & 0b00000001;
 // clear flag
 temp_buffer = temp_buffer & 0b11111110;
 } else {
 // Did alarm 2 go off?
 result = temp_buffer & 0b00000010;
 // clear flag
 temp_buffer = temp_buffer & 0b11111101;
 }
 writeControlByte(temp_buffer, 1);
 return result;
 }

 void enable32kHz(bool TF) {
 // turn 32kHz pin on or off
 byte temp_buffer = readControlByte(1);
 if (TF) {
 // turn on 32kHz pin
 temp_buffer = temp_buffer | 0b00001000;
 } else {
 // turn off 32kHz pin
 temp_buffer = temp_buffer & 0b11110111;
 }
 writeControlByte(temp_buffer, 1);
 }

 bool oscillatorCheck() {
 // Returns false if the oscillator has been off for some reason.
 // If this is the case, the time is probably not correct.
 byte temp_buffer = readControlByte(1);
 bool result = true;
 if (temp_buffer & 0b10000000) {
 // Oscillator Stop Flag (OSF) is set, so return false.
 result = false;
 }
 return result;
 }
 */
