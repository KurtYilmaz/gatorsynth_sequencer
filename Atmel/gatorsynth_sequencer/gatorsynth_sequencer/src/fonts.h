/*
 * fonts.h
 *
 * Created: 11/11/2017 7:38:59 PM
 *  Author: Kurt
 */ 

 // Font structure and generation attributed to "The Dot Factory"

 #include <stdlib.h>
 #include <stdint.h>

#ifndef BIGFONT_H_
#define BIGFONT_H_

//________________________________________________________________________________
// Type defines
typedef struct _font_char_info
{
	uint8_t Charwidth;
	uint8_t Charheight;
	uint16_t Offset;
}FONT_CHAR_INFO;

typedef struct _font_info
{
	uint8_t CharacterHeight;
	char StartCharacter;
	char EndCharacter;
	const FONT_CHAR_INFO *Descriptors;
	const uint8_t *Bitmaps;
}FONT_INFO;

//_________________________________________________________________________________

// Font data for OCR A Extended 28pt
extern const uint8_t oCRAExtended_28ptBitmaps[];
extern const FONT_INFO oCRAExtended_28ptFontInfo;
extern const FONT_CHAR_INFO oCRAExtended_28ptDescriptors[];

// Font data for OCR A Extended 24pt
extern const uint8_t oCRAExtended_22ptBitmaps[];
extern const FONT_INFO oCRAExtended_22ptFontInfo;
extern const FONT_CHAR_INFO oCRAExtended_22ptDescriptors[];

// Font data for OCR A Extended 18pt
extern const uint8_t oCRAExtended_18ptBitmaps[];
extern const FONT_INFO oCRAExtended_18ptFontInfo;
extern const FONT_CHAR_INFO oCRAExtended_18ptDescriptors[];

//Functions
uint8_t getWidth_18(void);
uint8_t getWidth_22(void);
uint8_t getWidth_28(void);
uint8_t getByte_18(char input, uint16_t byte_offset);
uint8_t getByte_22(char input, uint16_t byte_offset);
uint8_t getByte_28(char input, uint16_t byte_offset);

#endif /* BIGFONT_H_ */