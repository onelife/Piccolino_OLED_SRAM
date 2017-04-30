/* HZK 16x16 and HZK 12x12 font
 * Written by onelife (onelife.real(at)gmail.com)
 *
 * The font data is extracted from RT-Thread project <https://github.com/RT-Thread/rt-thread>. 
 * Due to the HZK fonts are not able to fit into the Arduino's flash memory, they have to be loaded 
 * from SD card (FONT_ON_SD).
 * 
 * Please copy file "hzk16font.fnt" or/and "hzk12font.fnt" to the SD card root directory.
 *
 * Reference #1: <https://github.com/RT-Thread/rt-thread/blob/master/components/gui/src/hz16font.c>
 * Reference #2: <https://github.com/RT-Thread/rt-thread/blob/master/components/gui/src/hz12font.c>
 * 
 * License of RT-Thread project: GNU General Public License <http://www.gnu.org/licenses/>
 * 
 * License: GNU General Public License <http://www.gnu.org/licenses/>
 */

#ifdef __AVR__
    #include <avr/io.h>
    #include <avr/pgmspace.h>
#else
    #define PROGMEM
#endif

#include "font.h"

#if defined(FONT_ON_SD)
#if defined(USE_FONT_SIZE_12)
Hkz_12_Font::Hkz_12_Font() {
    high    = 12;
    _start  = 0xa1a1;
    _end    = 0xf7fe;
    _offset = 0;
    _dft    = 0x021e;   // 0xa3bf - 0xa1a1
    //_idx    = _dft;
    _len    = 2;
}

boolean Hkz_12_Font::setChar(uint8_t *code, uint8_t len, File *fontFile) {
    if (len != _len) {
        return false;
    }
    uint16_t code16 = code[1] << 8 | code[0];
    if (code16 < _start || code16 > _end) {
        _offset = (94 * (uint32_t)(_dft >> 8) + (_dft & 0x00ff)) * 18;
    } else {
        _offset = (94 * (uint32_t)(code[1] - 0xa1) + (code[0] - 0xa1)) * 18;
    }
    _fontFile = fontFile;
    return true;
}

uint8_t Hkz_12_Font::getWidth() {
    return 12;
}

void Hkz_12_Font::getData(uint8_t *buff, uint8_t offset, uint8_t length) {
    _fontFile->seek(_offset + offset);
    _fontFile->read(buff, length);
    return;
}
#endif //USE_FONT_SIZE_12

#if defined(USE_FONT_SIZE_16)
Hkz_16_Font::Hkz_16_Font() {
    high    = 16;
    _start  = 0xa1a1;
    _end    = 0xf7fe;
    _offset = 0;
    _dft    = 0x021e;   // 0xa3bf - 0xa1a1
    //_idx    = _dft;
    _len    = 2;
}

boolean Hkz_16_Font::setChar(uint8_t *code, uint8_t len, File *fontFile) {
    if (len != _len) {
        return false;
    }
    uint16_t code16 = code[1] << 8 | code[0];
    if (code16 < _start || code16 > _end) {
        _offset = (94 * (uint32_t)(_dft >> 8) + (_dft & 0x00ff)) * 32;
    } else {
        _offset = (94 * (uint32_t)(code[1] - 0xa1) + (code[0] - 0xa1)) * 32;
    }
    _fontFile = fontFile;
    return true;
}

uint8_t Hkz_16_Font::getWidth() {
    return 16;
}

void Hkz_16_Font::getData(uint8_t *buff, uint8_t offset, uint8_t length) {
    _fontFile->seek(_offset + offset);
    _fontFile->read(buff, length);
    return;
}
#endif // USE_FONT_SIZE_16
#endif // FONT_ON_SD
