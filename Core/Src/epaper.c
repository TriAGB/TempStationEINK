#include "epaper.h"
#include "epdfont.h"

EPD_PAINT EPD_Paint;

EPD_PINS epd_pins;

static uint8_t _hibernating = 1;

unsigned char ut_partial[] = { 0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x80, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x40, 0x40, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0A, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2,
    0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x0, 0x0, 0x0, };

void epd_res_set() {
  HAL_GPIO_WritePin(epd_pins.res_port, epd_pins.res_pin, GPIO_PIN_SET);
}

void epd_res_reset() {
  HAL_GPIO_WritePin(epd_pins.res_port, epd_pins.res_pin, GPIO_PIN_RESET);
}

void epd_dc_set() {
  HAL_GPIO_WritePin(epd_pins.dc_port, epd_pins.dc_pin, GPIO_PIN_SET);
}

void epd_dc_reset() {
  HAL_GPIO_WritePin(epd_pins.dc_port, epd_pins.dc_pin, GPIO_PIN_RESET);
}

void epd_cs_set() {
  HAL_GPIO_WritePin(epd_pins.cs_port, epd_pins.cs_pin, GPIO_PIN_SET);
}

void epd_cs_reset() {
  HAL_GPIO_WritePin(epd_pins.cs_port, epd_pins.cs_pin, GPIO_PIN_RESET);
}

uint8_t epd_is_busy() {
  return HAL_GPIO_ReadPin(epd_pins.busy_port, epd_pins.busy_pin) == GPIO_PIN_RESET ? 0 : 1;
}

void epd_io_init(void) {
  GPIO_InitTypeDef GPIO_InitStructure = { 0 };

  /* configure the epaper module res pin */
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Pin = epd_pins.res_pin;
  GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(epd_pins.res_port, &GPIO_InitStructure);

  /* configure the epaper module busy pin */
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  GPIO_InitStructure.Pin = epd_pins.busy_pin;
  HAL_GPIO_Init(epd_pins.busy_port, &GPIO_InitStructure);

  /* configure the epaper module d/c pin */
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Pin = epd_pins.dc_pin;
  GPIO_InitStructure.Pull = GPIO_PULLUP; // возможно
  GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(epd_pins.dc_port, &GPIO_InitStructure);

  /* configure the epaper module cs pin */
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Pin = epd_pins.cs_pin;
  GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(epd_pins.cs_port, &GPIO_InitStructure);

  /* configure the epaper module spi2 sck mosi pin */
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /* configure spi2 */
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
//
//  spiConfig.SPI_DataSize = SPI_DataSize_8b;
//  spiConfig.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
//  spiConfig.SPI_Direction = SPI_Direction_1Line_Tx;
//  spiConfig.SPI_FirstBit = SPI_FirstBit_MSB;
//  spiConfig.SPI_Mode = SPI_Mode_Master;
//  spiConfig.SPI_CPOL = SPI_CPOL_High;
//  spiConfig.SPI_CPHA = SPI_CPHA_2Edge;
//  spiConfig.SPI_NSS = SPI_NSS_Soft;
//  SPI_Init(SPI2, &spiConfig);
//  SPI_Cmd(SPI2, ENABLE);
}

/**
 * @brief Write bytes to display (command or data)
 * @param reg register code to write
 * @param *data pointer to write data
 * @param size size of data
 * @retval errorcode (HAL_OK - ok)
 */
uint8_t epdWriteBytes(uint8_t reg, uint8_t data[], uint16_t size) {
	HAL_GPIO_WritePin(epd_pins.cs_port, epd_pins.cs_pin, GPIO_PIN_RESET);
	__NOP();
	HAL_SPI_StateTypeDef result;
	result = HAL_SPI_GetState(epd_pins.hspi);
	if(result == HAL_SPI_STATE_READY) {
		HAL_GPIO_WritePin(epd_pins.cs_port, epd_pins.dc_pin, GPIO_PIN_RESET);
		__NOP();
		result = HAL_SPI_Transmit(epd_pins.hspi, &reg, 1, 1);
		HAL_GPIO_WritePin(epd_pins.cs_port, epd_pins.dc_pin, GPIO_PIN_SET);
		__NOP();
		if(result == HAL_OK) {
			result = HAL_SPI_Transmit(epd_pins.hspi, data, size, 1);
		}
	}
	HAL_GPIO_WritePin(epd_pins.cs_port, epd_pins.cs_pin, GPIO_PIN_SET);
	__NOP();
	return result;
}

uint8_t epd_wait_busy() {
  uint32_t timeout = 0;
  while (epd_is_busy()) {
    timeout++;
    if (timeout > 4000) {
      return 1;
    }
    HAL_Delay(1);
  }
  return 0;
}

void epd_reset(void) {
  epd_res_reset();
  HAL_Delay(50);
  epd_res_set();
  HAL_Delay(50);
  _hibernating = 0;
}

uint8_t epd_init(void) {
  if (_hibernating) epd_reset();

  if (epd_wait_busy()) return 1;

  // SWRESET
  epdWriteBytes(0x12, (uint8_t []){0}, 0);

  if (epd_wait_busy()) return 1;

  // Driver output control
  epdWriteBytes(0x01, (uint8_t []){0x27, 0x01, 0x01}, 3);

  // data entry mode
  epdWriteBytes(0x11, (uint8_t []){0x01}, 1);

  // set Ram-X address start/end position
  // 0x0F-->(15+1)*8=128
  epdWriteBytes(0x44, (uint8_t []){0x00, 0x0F}, 2);

  // set Ram-Y address start/end position
  // 0x127-->(295+1)=296
  epdWriteBytes(0x45, (uint8_t []){0x27, 0x01, 0x00, 0x00}, 4);

  // BorderWavefrom
  epdWriteBytes(0x3C, (uint8_t []){0x05}, 1);

  //  Display update control
  epdWriteBytes(0x21, (uint8_t []){0x00, 0x80}, 2);

  //epd_write_reg(0x18); // Read built-in temperature sensor
  epdWriteBytes(0x18, (uint8_t []){0x80}, 1);

  // set RAM x address count to 0;
  epdWriteBytes(0x4E, (uint8_t []){0x00}, 1);

  // set RAM y address count to 0x127;
  epdWriteBytes(0x4F, (uint8_t []){0x27, 0x01}, 2);

  if (epd_wait_busy()) return 1;
  return 0;
}

uint8_t epd_init_partial(void) {
  if (epd_init()) return 1;
  return epdWriteBytes(0x32, ut_partial, sizeof(ut_partial));
}

void epd_enter_deepsleepmode(uint8_t mode) {
  epdWriteBytes(0x10, &mode, 1);
  _hibernating = 1;
}

void epd_init_internalTempSensor(void) {
	epdWriteBytes(0x18, (uint8_t []){0x80}, 1);
	epdWriteBytes(0x1A, (uint8_t []){0x7F, 0xF0}, 2);
}

void epd_update(uint8_t partial) {
  if(partial) epdWriteBytes(0x22, (uint8_t []){0xCC}, 1); // Display Update Control
  else epdWriteBytes(0x22, (uint8_t []){0xF7}, 1);
	epdWriteBytes(0x20, (uint8_t []){0x00}, 0); // Activate Display Update Sequence
  epd_wait_busy();
}

void epd_setpos(uint16_t x, uint16_t y) {
  epdWriteBytes(0x4E, (uint8_t []){x / 8}, 1); // set RAM x address count to 0;
  y = 295 - y;
  epdWriteBytes(0x4F, (uint8_t []){ y, y >> 8}, 2); // set RAM y address count to 0x127;
}

void epd_display(uint8_t *Image1, uint8_t partial) {
  //epd_setpos(0, 0);
  //epdWriteBytes(0x26, Image1, EPD_H * EPD_W_BUFF_SIZE);
  epd_setpos(0, 0);
  epdWriteBytes(0x24, Image1, EPD_H * EPD_W_BUFF_SIZE);
  epd_update(partial);
}

void epd_paint_newimage(uint8_t *image, uint16_t Width, uint16_t Height, uint16_t Rotate,
    uint16_t Color) {
  EPD_Paint.Image = 0x00;
  EPD_Paint.Image = image;

  EPD_Paint.WidthMemory = Width;
  EPD_Paint.HeightMemory = Height;
  EPD_Paint.Color = Color;
  EPD_Paint.WidthByte = (Width % 8 == 0) ? (Width / 8) : (Width / 8 + 1);
  EPD_Paint.HeightByte = Height;
  EPD_Paint.Rotate = Rotate;
  if (Rotate == EPD_ROTATE_0 || Rotate == EPD_ROTATE_180) {

    EPD_Paint.Width = Height;
    EPD_Paint.Height = Width;
  }
  else {
    EPD_Paint.Width = Width;
    EPD_Paint.Height = Height;
  }
}

void epd_paint_setpixel(uint16_t Xpoint, uint16_t Ypoint, uint16_t Color) {
  uint16_t X, Y;
  uint32_t Addr;
  uint8_t Rdata;
  switch (EPD_Paint.Rotate) {
  case 0:

    X = EPD_Paint.WidthMemory - Ypoint - 1;
    Y = Xpoint;
    break;
  case 90:
    X = EPD_Paint.WidthMemory - Xpoint - 1;
    Y = EPD_Paint.HeightMemory - Ypoint - 1;
    break;
  case 180:
    X = Ypoint;
    Y = EPD_Paint.HeightMemory - Xpoint - 1;
    break;
  case 270:
    X = Xpoint;
    Y = Ypoint;
    break;
  default:
    return;
  }
  Addr = X / 8 + Y * EPD_Paint.WidthByte;
  Rdata = EPD_Paint.Image[Addr];
  if (Color == EPD_COLOR_BLACK) {
    EPD_Paint.Image[Addr] = Rdata & ~(0x80 >> (X % 8));
  }
  else EPD_Paint.Image[Addr] = Rdata | (0x80 >> (X % 8));
}

void epd_paint_clear(uint16_t color) {
  uint16_t X, Y;
  uint32_t Addr;

  for (Y = 0; Y < EPD_Paint.HeightByte; Y++) {
    for (X = 0; X < EPD_Paint.WidthByte; X++) { // 8 pixel =  1 byte
      Addr = X + Y * EPD_Paint.WidthByte;
      EPD_Paint.Image[Addr] = color;
    }
  }
}

void epd_paint_selectimage(uint8_t *image) {
  EPD_Paint.Image = image;
}

void epd_paint_drawPoint(uint16_t Xpoint, uint16_t Ypoint, uint16_t Color) {
  epd_paint_setpixel(Xpoint - 1, Ypoint - 1, Color);
}

void epd_paint_drawLine(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend,
    uint16_t Color) {
  uint16_t Xpoint, Ypoint;
  int32_t dx, dy;
  int32_t XAddway, YAddway;
  int32_t Esp;
  char Dotted_Len;
  Xpoint = Xstart;
  Ypoint = Ystart;
  dx = (int) Xend - (int) Xstart >= 0 ? Xend - Xstart : Xstart - Xend;
  dy = (int) Yend - (int) Ystart <= 0 ? Yend - Ystart : Ystart - Yend;

  XAddway = Xstart < Xend ? 1 : -1;
  YAddway = Ystart < Yend ? 1 : -1;

  Esp = dx + dy;
  Dotted_Len = 0;

  for (;;) {
    Dotted_Len++;
    epd_paint_drawPoint(Xpoint, Ypoint, Color);
    if (2 * Esp >= dy) {
      if (Xpoint == Xend) break;
      Esp += dy;
      Xpoint += XAddway;
    }
    if (2 * Esp <= dx) {
      if (Ypoint == Yend) break;
      Esp += dx;
      Ypoint += YAddway;
    }
  }
}

void epd_paint_drawRectangle(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend,
    uint16_t Color, uint8_t mode) {
  uint16_t i;
  if (mode) {
    for (i = Ystart; i < Yend; i++) {
      epd_paint_drawLine(Xstart, i, Xend, i, Color);
    }
  }
  else {
    epd_paint_drawLine(Xstart, Ystart, Xend, Ystart, Color);
    epd_paint_drawLine(Xstart, Ystart, Xstart, Yend, Color);
    epd_paint_drawLine(Xend, Yend, Xend, Ystart, Color);
    epd_paint_drawLine(Xend, Yend, Xstart, Yend, Color);
  }
}

void epd_paint_drawCircle(uint16_t X_Center, uint16_t Y_Center, uint16_t Radius, uint16_t Color,
    uint8_t mode) {
  uint16_t Esp, sCountY;
  uint16_t XCurrent, YCurrent;
  XCurrent = 0;
  YCurrent = Radius;
  Esp = 3 - (Radius << 1);
  if (mode) {
    while (XCurrent <= YCurrent) { // Realistic circles
      for (sCountY = XCurrent; sCountY <= YCurrent; sCountY++) {
        epd_paint_drawPoint(X_Center + XCurrent, Y_Center + sCountY, Color); // 1
        epd_paint_drawPoint(X_Center - XCurrent, Y_Center + sCountY, Color); // 2
        epd_paint_drawPoint(X_Center - sCountY, Y_Center + XCurrent, Color); // 3
        epd_paint_drawPoint(X_Center - sCountY, Y_Center - XCurrent, Color); // 4
        epd_paint_drawPoint(X_Center - XCurrent, Y_Center - sCountY, Color); // 5
        epd_paint_drawPoint(X_Center + XCurrent, Y_Center - sCountY, Color); // 6
        epd_paint_drawPoint(X_Center + sCountY, Y_Center - XCurrent, Color); // 7
        epd_paint_drawPoint(X_Center + sCountY, Y_Center + XCurrent, Color);
      }
      if ((int) Esp < 0) Esp += 4 * XCurrent + 6;
      else {
        Esp += 10 + 4 * (XCurrent - YCurrent);
        YCurrent--;
      }
      XCurrent++;
    }
  }
  else { // Draw a hollow circle
    while (XCurrent <= YCurrent) {
      epd_paint_drawPoint(X_Center + XCurrent, Y_Center + YCurrent, Color); // 1
      epd_paint_drawPoint(X_Center - XCurrent, Y_Center + YCurrent, Color); // 2
      epd_paint_drawPoint(X_Center - YCurrent, Y_Center + XCurrent, Color); // 3
      epd_paint_drawPoint(X_Center - YCurrent, Y_Center - XCurrent, Color); // 4
      epd_paint_drawPoint(X_Center - XCurrent, Y_Center - YCurrent, Color); // 5
      epd_paint_drawPoint(X_Center + XCurrent, Y_Center - YCurrent, Color); // 6
      epd_paint_drawPoint(X_Center + YCurrent, Y_Center - XCurrent, Color); // 7
      epd_paint_drawPoint(X_Center + YCurrent, Y_Center + XCurrent, Color); // 0
      if ((int) Esp < 0) Esp += 4 * XCurrent + 6;
      else {
        Esp += 10 + 4 * (XCurrent - YCurrent);
        YCurrent--;
      }
      XCurrent++;
    }
  }
}

void epd_paint_showChar(uint16_t x, uint16_t y, uint16_t chr, uint16_t size, uint16_t color) {
  uint16_t i, m, temp, size2, chr1;
  uint16_t x0, y0;
  x += 1, y += 1, x0 = x, y0 = y;
  if (x - size > EPD_H) return;
  if (size == 8) size2 = 6;
  else size2 = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);
  chr1 = chr - ' ';
  for (i = 0; i < size2; i++) {
    if (size == 8) {
      temp = asc2_0806[chr1][i];
    } // 0806
    else if (size == 12) {
      temp = asc2_1206[chr1][i];
    } // 1206
    else if (size == 16) {
      temp = asc2_1608[chr1][i];
    } // 1608
    else if (size == 24) {
      temp = asc2_2412[chr1][i];
    } // 2412
    else return;
    for (m = 0; m < 8; m++) {
      if (temp & 0x01) epd_paint_drawPoint(x, y, color);
      else epd_paint_drawPoint(x, y, !color);
      temp >>= 1;
      y++;
    }
    x++;
    if ((size != 8) && ((x - x0) == size / 2)) {
      x = x0;
      y0 = y0 + 8;
    }
    y = y0;
  }
}

void epd_paint_showString(uint16_t x, uint16_t y, uint8_t *chr, uint16_t size, uint16_t color) {
  while (*chr != '\0') {
    epd_paint_showChar(x, y, *chr, size, color);
    chr++;
    if (size == 8) {
      x += 6;
    }
    else {
      x += size / 2;
    }
  }
}

// m^n
static uint32_t _Pow(uint16_t m, uint16_t n) {
  uint32_t result = 1;
  while (n--) {
    result *= m;
  }
  return result;
}

void epd_paint_showNum(uint16_t x, uint16_t y, uint32_t num, uint16_t len, uint16_t size,
    uint16_t color) {
  uint8_t t, temp, m = 0;
  if (size == 8) m = 2;
  for (t = 0; t < len; t++) {
    temp = (num / _Pow(10, len - t - 1)) % 10;
    if (temp == 0) {
      epd_paint_showChar(x + (size / 2 + m) * t, y, '0', size, color);
    }
    else {
      epd_paint_showChar(x + (size / 2 + m) * t, y, temp + '0', size, color);
    }
  }
}

void epd_paint_showPicture(uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey,
    const uint8_t BMP[], uint16_t Color) {
  uint16_t j = 0;
  uint16_t i, n = 0, temp = 0, m = 0;
  uint16_t x0 = 0, y0 = 0;
  x += 1, y += 1, x0 = x, y0 = y;
  sizey = sizey / 8 + ((sizey % 8) ? 1 : 0);
  for (n = 0; n < sizey; n++) {
    for (i = 0; i < sizex; i++) {
      temp = BMP[j];
      j++;
      for (m = 0; m < 8; m++) {
        if (temp & 0x01) epd_paint_drawPoint(x, y, !Color);
        else epd_paint_drawPoint(x, y, Color);
        temp >>= 1;
        y++;
      }
      x++;
      if ((x - x0) == sizex) {
        x = x0;
        y0 = y0 + 8;
      }
      y = y0;
    }
  }
}
