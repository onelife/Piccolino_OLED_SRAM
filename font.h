#ifndef FONT_H
#define FONT_H

#define ASCII_12    (0x01)
#define ASCII_16    (0x02)
#define HZK_12      (0x03)
#define HZK_16      (0x04)
#define FONT_MASK   (0x0f)


#include "Arduino.h"
#include "font_config.h"
#if defined(FONT_ON_SD)
#include <SdFat.h>
#endif


class Font {
public:
    uint8_t     high;

#if defined(FONT_ON_SD)
    virtual boolean setChar(uint8_t *code, uint8_t len, File *fontFile) = 0;
    virtual void getData(uint8_t *buff, uint8_t offset, uint8_t length) = 0;
#else // FONT_ON_SD
    virtual boolean setChar(uint8_t *code, uint8_t len, uint8_t not_used) = 0;
    virtual void getData(uint8_t *buff, uint8_t offset) = 0;
#endif // FONT_ON_SD
    virtual uint8_t getWidth() = 0;

protected:
    uint16_t    _start;
    uint16_t    _end;
    uint32_t    _offset;
    uint16_t    _dft;
    uint16_t    _idx;
    uint8_t     _len;
#if defined(FONT_ON_SD)
    File        *_fontFile;
#else
    uint8_t     *_fontFile;
#endif // FONT_ON_SD
};

#if defined(USE_FONT_SIZE_12)
class Asscii_12_Font : public Font {
public:
    Asscii_12_Font();
#if defined(FONT_ON_SD)
    boolean setChar(uint8_t *code, uint8_t len, File *fontFile);
    void getData(uint8_t *buff, uint8_t offset, uint8_t length);
#else // FONT_ON_SD
    boolean setChar(uint8_t *code, uint8_t len, uint8_t not_used);
    void getData(uint8_t *buff, uint8_t offset);
#endif // FONT_ON_SD
    uint8_t getWidth();
};

#if defined(FONT_ON_SD)
class Hkz_12_Font: public Font {
public:
    Hkz_12_Font();
    boolean setChar(uint8_t *code, uint8_t len, File *fontFile);
    void getData(uint8_t *buff, uint8_t offset, uint8_t length);
    uint8_t getWidth();
};
#endif // FONT_ON_SD
#endif // USE_FONT_SIZE_12

#if defined(USE_FONT_SIZE_16)
class Asscii_16_Font : public Font {
public:
    Asscii_16_Font();
#if defined(FONT_ON_SD)
    boolean setChar(uint8_t *code, uint8_t len, File *fontFile);
    void getData(uint8_t *buff, uint8_t offset, uint8_t length);
#else // FONT_ON_SD
    boolean setChar(uint8_t *code, uint8_t len, uint8_t not_used);
    void getData(uint8_t *buff, uint8_t offset);
#endif // FONT_ON_SD
    uint8_t getWidth();
};

#if defined(FONT_ON_SD)
class Hkz_16_Font: public Font {
public:
    Hkz_16_Font();
    boolean setChar(uint8_t *code, uint8_t len, File *fontFile);
    void getData(uint8_t *buff, uint8_t offset, uint8_t length);
    uint8_t getWidth();
};
#endif // FONT_ON_SD
#endif // USE_FONT_SIZE_16

#endif // FONT_H