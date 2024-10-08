#include "oslib.h"
#include "intraFont/intraFont.h"

unsigned int intra_options = 0;

OSL_FONT *osl_curFont=NULL;
OSL_FONT *osl_sceFont=NULL;
int osl_consolePosX=0, osl_consolePosY=0; //, osl_consoleOk=0;
OSL_COLOR osl_textBkColor = 0xff000000, osl_textColor = 0xffffffff;

const unsigned char osl_sceFont_data[]=         {
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x3c, 0x42, 0xa5, 0x81, 0xa5, 0x99, 0x42, 0x3c,
	0x3c, 0x7e, 0xdb, 0xff, 0xff, 0xdb, 0x66, 0x3c,
	0x36, 0x7f, 0x7f, 0x7f, 0x3e, 0x1c, 0x8, 0x0,
	0x8, 0x1c, 0x3e, 0x7f, 0x3e, 0x1c, 0x8, 0x0,
	0x8, 0x1c, 0x2a, 0x7f, 0x2a, 0x8, 0x1c, 0x0,
	0x8, 0x1c, 0x3e, 0x7f, 0x7f, 0x8, 0x1c, 0x0,
	0x0, 0x0, 0x0, 0xc, 0xc, 0x0, 0x0, 0x0,
	0xff, 0xff, 0xff, 0xe7, 0xe7, 0xff, 0xff, 0xff,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xf0, 0xc0, 0xa0, 0x9e, 0x11, 0x11, 0x11, 0xe,
	0x1c, 0x22, 0x22, 0x22, 0x1c, 0x8, 0x3e, 0x8,
	0xc, 0x14, 0x24, 0x24, 0x14, 0x4, 0x7, 0x3,
	0x3c, 0x24, 0x3c, 0x24, 0x24, 0x27, 0x3b, 0x18,
	0x8, 0x2a, 0x1c, 0x77, 0x1c, 0x2a, 0x8, 0x0,
	0x8, 0x8, 0x8, 0x3e, 0x8, 0x8, 0x8, 0x8,
	0x8, 0x8, 0x8, 0xff, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0xff, 0x8, 0x8, 0x8, 0x8,
	0x8, 0x8, 0x8, 0xf, 0x8, 0x8, 0x8, 0x8,
	0x8, 0x8, 0x8, 0xf8, 0x8, 0x8, 0x8, 0x8,
	0x8, 0x8, 0x8, 0xff, 0x8, 0x8, 0x8, 0x8,
	0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8,
	0x0, 0x0, 0x0, 0xff, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0xf8, 0x8, 0x8, 0x8, 0x8,
	0x0, 0x0, 0x0, 0xf, 0x8, 0x8, 0x8, 0x8,
	0x8, 0x8, 0x8, 0xf8, 0x0, 0x0, 0x0, 0x0,
	0x8, 0x8, 0x8, 0xf, 0x0, 0x0, 0x0, 0x0,
	0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81,
	0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1,
	0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80,
	0x0, 0x8, 0x8, 0xff, 0x8, 0x8, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x4, 0x4, 0x4, 0x4, 0x0, 0x0, 0x4, 0x0,
	0xa, 0xa, 0xa, 0x0, 0x0, 0x0, 0x0, 0x0,
	0xa, 0xa, 0x1f, 0xa, 0x1f, 0xa, 0xa, 0x0,
	0x4, 0x1e, 0x5, 0xe, 0x14, 0xf, 0x4, 0x0,
	0x3, 0x13, 0x8, 0x4, 0x2, 0x19, 0x18, 0x0,
	0x2, 0x5, 0x2, 0x15, 0x9, 0x19, 0x6, 0x0,
	0x8, 0x4, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x8, 0x4, 0x2, 0x2, 0x2, 0x4, 0x8, 0x0,
	0x2, 0x4, 0x8, 0x8, 0x8, 0x4, 0x2, 0x0,
	0x4, 0x15, 0xe, 0x4, 0xe, 0x15, 0x4, 0x0,
	0x0, 0x4, 0x4, 0x1f, 0x4, 0x4, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x4, 0x4, 0x2,
	0x0, 0x0, 0x0, 0x1e, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x6, 0x0,
	0x0, 0x0, 0x10, 0x8, 0x4, 0x2, 0x1, 0x0,
	0xe, 0x11, 0x19, 0x15, 0x13, 0x11, 0xe, 0x0,
	0x4, 0x6, 0x5, 0x4, 0x4, 0x4, 0x1f, 0x0,
	0xe, 0x11, 0x10, 0x8, 0x6, 0x1, 0x1f, 0x0,
	0xe, 0x11, 0x10, 0xc, 0x10, 0x11, 0xe, 0x0,
	0x8, 0xc, 0xa, 0x9, 0x1f, 0x8, 0x8, 0x0,
	0x1f, 0x1, 0x7, 0x8, 0x10, 0x8, 0x7, 0x0,
	0xc, 0x2, 0x1, 0xf, 0x11, 0x11, 0xe, 0x0,
	0x1f, 0x11, 0x8, 0x4, 0x4, 0x4, 0x4, 0x0,
	0xe, 0x11, 0x11, 0xe, 0x11, 0x11, 0xe, 0x0,
	0xe, 0x11, 0x11, 0x1e, 0x10, 0x8, 0x6, 0x0,
	0x0, 0x0, 0x4, 0x0, 0x0, 0x4, 0x0, 0x0,
	0x0, 0x0, 0x4, 0x0, 0x0, 0x4, 0x4, 0x2,
	0x18, 0xc, 0x6, 0x3, 0x6, 0xc, 0x18, 0x0,
	0x0, 0x0, 0x1f, 0x0, 0x1f, 0x0, 0x0, 0x0,
	0x3, 0x6, 0xc, 0x18, 0xc, 0x6, 0x3, 0x0,
	0xe, 0x11, 0x10, 0x8, 0x4, 0x0, 0x4, 0x0,
	0xe, 0x11, 0x10, 0x16, 0x15, 0x15, 0xe, 0x0,
	0x4, 0xa, 0x11, 0x11, 0x1f, 0x11, 0x11, 0x0,
	0xf, 0x12, 0x12, 0xe, 0x12, 0x12, 0xf, 0x0,
	0xc, 0x12, 0x1, 0x1, 0x1, 0x12, 0xc, 0x0,
	0x7, 0xa, 0x12, 0x12, 0x12, 0xa, 0x7, 0x0,
	0x1f, 0x1, 0x1, 0xf, 0x1, 0x1, 0x1f, 0x0,
	0x1f, 0x1, 0x1, 0xf, 0x1, 0x1, 0x1, 0x0,
	0xe, 0x11, 0x1, 0x1d, 0x11, 0x11, 0xe, 0x0,
	0x11, 0x11, 0x11, 0x1f, 0x11, 0x11, 0x11, 0x0,
	0xe, 0x4, 0x4, 0x4, 0x4, 0x4, 0xe, 0x0,
	0x1c, 0x8, 0x8, 0x8, 0x9, 0x9, 0x6, 0x0,
	0x11, 0x9, 0x5, 0x3, 0x5, 0x9, 0x11, 0x0,
	0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1f, 0x0,
	0x11, 0x1b, 0x15, 0x15, 0x11, 0x11, 0x11, 0x0,
	0x11, 0x13, 0x13, 0x15, 0x19, 0x19, 0x11, 0x0,
	0xe, 0x11, 0x11, 0x11, 0x11, 0x11, 0xe, 0x0,
	0xf, 0x11, 0x11, 0xf, 0x1, 0x1, 0x1, 0x0,
	0xe, 0x11, 0x11, 0x11, 0x15, 0x9, 0x16, 0x0,
	0xf, 0x11, 0x11, 0xf, 0x5, 0x9, 0x11, 0x0,
	0xe, 0x11, 0x1, 0xe, 0x10, 0x11, 0xe, 0x0,
	0x1f, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0,
	0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0xe, 0x0,
	0x11, 0x11, 0x11, 0x11, 0xa, 0xa, 0x4, 0x0,
	0x11, 0x11, 0x11, 0x15, 0x15, 0x1b, 0x11, 0x0,
	0x11, 0x11, 0xa, 0x4, 0xa, 0x11, 0x11, 0x0,
	0x11, 0x11, 0x11, 0xe, 0x4, 0x4, 0x4, 0x0,
	0x1f, 0x10, 0x8, 0x4, 0x2, 0x1, 0x1f, 0x0,
	0xe, 0x2, 0x2, 0x2, 0x2, 0x2, 0xe, 0x0,
	0x0, 0x0, 0x1, 0x2, 0x4, 0x8, 0x10, 0x0,
	0xe, 0x8, 0x8, 0x8, 0x8, 0x8, 0xe, 0x0,
	0x4, 0xa, 0x11, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0x0,
	0x2, 0x4, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0xe, 0x10, 0x1e, 0x11, 0x1e, 0x0,
	0x1, 0x1, 0xd, 0x13, 0x11, 0x13, 0xd, 0x0,
	0x0, 0x0, 0xe, 0x11, 0x1, 0x11, 0xe, 0x0,
	0x10, 0x10, 0x16, 0x19, 0x11, 0x19, 0x16, 0x0,
	0x0, 0x0, 0xe, 0x11, 0x1f, 0x1, 0xe, 0x0,
	0x8, 0x14, 0x4, 0x1f, 0x4, 0x4, 0x4, 0x0,
	0x0, 0x0, 0x16, 0x19, 0x19, 0x16, 0x10, 0xe,
	0x1, 0x1, 0xf, 0x11, 0x11, 0x11, 0x11, 0x0,
	0x4, 0x0, 0x6, 0x4, 0x4, 0x4, 0xe, 0x0,
	0x8, 0x0, 0xc, 0x8, 0x8, 0x8, 0x9, 0x6,
	0x2, 0x2, 0x12, 0xa, 0x6, 0xa, 0x12, 0x0,
	0x6, 0x4, 0x4, 0x4, 0x4, 0x4, 0xe, 0x0,
	0x0, 0x0, 0xb, 0x15, 0x15, 0x15, 0x15, 0x0,
	0x0, 0x0, 0xd, 0x13, 0x11, 0x11, 0x11, 0x0,
	0x0, 0x0, 0xe, 0x11, 0x11, 0x11, 0xe, 0x0,
	0x0, 0x0, 0xd, 0x13, 0x13, 0xd, 0x1, 0x1,
	0x0, 0x0, 0x16, 0x19, 0x19, 0x16, 0x10, 0x10,
	0x0, 0x0, 0xd, 0x13, 0x1, 0x1, 0x1, 0x0,
	0x0, 0x0, 0x1e, 0x1, 0xf, 0x10, 0xf, 0x0,
	0x2, 0x2, 0xf, 0x2, 0x2, 0x12, 0xc, 0x0,
	0x0, 0x0, 0x9, 0x9, 0x9, 0x9, 0x16, 0x0,
	0x0, 0x0, 0x11, 0x11, 0x11, 0xa, 0x4, 0x0,
	0x0, 0x0, 0x11, 0x15, 0x15, 0x15, 0xa, 0x0,
	0x0, 0x0, 0x11, 0xa, 0x4, 0xa, 0x11, 0x0,
	0x0, 0x0, 0x11, 0x11, 0x19, 0x16, 0x10, 0xe,
	0x0, 0x0, 0x1f, 0x8, 0x4, 0x2, 0x1f, 0x0,
	0x18, 0x4, 0x4, 0x2, 0x4, 0x4, 0x18, 0x0,
	0x4, 0x4, 0x4, 0x0, 0x4, 0x4, 0x4, 0x0,
	0x3, 0x4, 0x4, 0x8, 0x4, 0x4, 0x3, 0x0,
	0x2, 0x15, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x4, 0xa, 0x1f, 0x0, 0x0, 0x0,
	0xe, 0x11, 0x1, 0x1, 0x11, 0xe, 0x4, 0x6,
	0x9, 0x0, 0x0, 0x9, 0x9, 0x9, 0x16, 0x0,
	0x8, 0x4, 0xe, 0x11, 0x1f, 0x1, 0xe, 0x0,
	0x4, 0xa, 0xe, 0x10, 0x1e, 0x11, 0x1e, 0x0,
	0x12, 0x0, 0xe, 0x10, 0x1e, 0x11, 0x1e, 0x0,
	0x4, 0x8, 0xe, 0x10, 0x1e, 0x11, 0x1e, 0x0,
	0x4, 0x0, 0xe, 0x10, 0x1e, 0x11, 0x1e, 0x0,
	0x0, 0xe, 0x1, 0x1, 0x1, 0xe, 0x8, 0x6,
	0x4, 0xa, 0xe, 0x11, 0x1f, 0x1, 0xe, 0x0,
	0xa, 0x0, 0xe, 0x11, 0x1f, 0x1, 0xe, 0x0,
	0x4, 0x8, 0xe, 0x11, 0x1f, 0x1, 0xe, 0x0,
	0xa, 0x0, 0x0, 0x6, 0x4, 0x4, 0xe, 0x0,
	0x4, 0xa, 0x0, 0x6, 0x4, 0x4, 0xe, 0x0,
	0x2, 0x4, 0x0, 0x6, 0x4, 0x4, 0xe, 0x0,
	0xa, 0x0, 0x4, 0xa, 0x11, 0x1f, 0x11, 0x0,
	0x4, 0x0, 0x4, 0xa, 0x11, 0x1f, 0x11, 0x0,
	0x8, 0x4, 0x1f, 0x1, 0xf, 0x1, 0x1f, 0x0,
	0x0, 0x0, 0x36, 0x48, 0x7e, 0x9, 0x76, 0x0,
	0x7c, 0xa, 0x9, 0x39, 0xf, 0x9, 0x79, 0x0,
	0x6, 0x9, 0x0, 0x6, 0x9, 0x9, 0x6, 0x0,
	0x9, 0x0, 0x0, 0x6, 0x9, 0x9, 0x6, 0x0,
	0x2, 0x4, 0x0, 0x6, 0x9, 0x9, 0x6, 0x0,
	0x2, 0x5, 0x0, 0x5, 0x5, 0x5, 0xa, 0x0,
	0x2, 0x4, 0x0, 0x5, 0x5, 0x5, 0xa, 0x0,
	0x9, 0x0, 0x9, 0x9, 0xd, 0xa, 0x8, 0x7,
	0xa, 0x0, 0xe, 0x11, 0x11, 0x11, 0xe, 0x0,
	0xa, 0x0, 0x11, 0x11, 0x11, 0x11, 0xe, 0x0,
	0x4, 0x4, 0x1e, 0x1, 0x1, 0x1e, 0x4, 0x4,
	0x18, 0x24, 0x4, 0x1f, 0x4, 0x47, 0x3a, 0x0,
	0x11, 0xa, 0x4, 0x1f, 0x4, 0x1f, 0x4, 0x0,
	0x3, 0x5, 0x5, 0x13, 0x39, 0x11, 0x11, 0x31,
	0x18, 0x4, 0x4, 0x1f, 0x4, 0x4, 0x4, 0x2,
	0x8, 0x4, 0xe, 0x10, 0x1e, 0x11, 0x1e, 0x0,
	0x8, 0x4, 0x0, 0x6, 0x4, 0x4, 0xe, 0x0,
	0x4, 0x2, 0x0, 0x6, 0x9, 0x9, 0x6, 0x0,
	0x4, 0x2, 0x0, 0x9, 0x9, 0x9, 0x16, 0x0,
	0xa, 0x5, 0x0, 0x5, 0xb, 0x9, 0x9, 0x0,
	0x14, 0xa, 0x0, 0x13, 0x15, 0x19, 0x11, 0x0,
	0x0, 0xe, 0x10, 0x1e, 0x11, 0x1e, 0x0, 0x1f,
	0x0, 0x6, 0x9, 0x9, 0x9, 0x6, 0x0, 0xf,
	0x4, 0x0, 0x4, 0x2, 0x1, 0x11, 0xe, 0x0,
	0x0, 0x0, 0x0, 0x1f, 0x1, 0x1, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x1f, 0x10, 0x10, 0x0, 0x0,
	0x21, 0x11, 0x9, 0x15, 0x2a, 0x21, 0x10, 0x38,
	0x21, 0x11, 0x9, 0x15, 0x1a, 0x15, 0x3c, 0x10,
	0x4, 0x0, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0,
	0x0, 0x0, 0x24, 0x12, 0x9, 0x12, 0x24, 0x0,
	0x0, 0x0, 0x9, 0x12, 0x24, 0x12, 0x9, 0x0,
	0x14, 0xa, 0x4, 0xa, 0x11, 0x1f, 0x11, 0x0,
	0x14, 0xa, 0xe, 0x10, 0x1e, 0x11, 0x1e, 0x0,
	0x14, 0xa, 0x0, 0xe, 0x4, 0x4, 0xe, 0x0,
	0x14, 0xa, 0x0, 0x4, 0x4, 0x4, 0xe, 0x0,
	0x14, 0xa, 0x0, 0xe, 0x11, 0x11, 0xe, 0x0,
	0xa, 0x5, 0x0, 0x6, 0x9, 0x9, 0x6, 0x0,
	0x14, 0xa, 0x0, 0x11, 0x11, 0x11, 0xe, 0x0,
	0xa, 0x5, 0x0, 0x5, 0x5, 0x5, 0xa, 0x0,
	0x3f, 0x12, 0x12, 0x12, 0x17, 0x10, 0xa, 0x4,
	0x0, 0xa, 0x0, 0xa, 0xa, 0xa, 0x8, 0x4,
	0x3, 0x22, 0x13, 0x2a, 0x37, 0x2a, 0x79, 0x20,
	0x8, 0x15, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x4, 0xa, 0x11, 0xa, 0x4, 0x0, 0x0,
	0x11, 0x8, 0x4, 0x2, 0x1, 0x14, 0x0, 0x0,
	0x3e, 0x15, 0x15, 0x16, 0x14, 0x14, 0x14, 0x0,
	0x1c, 0x2, 0xc, 0x12, 0x12, 0xc, 0x10, 0xe,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff,
	0xf, 0xf, 0xf, 0xf, 0xf0, 0xf0, 0xf0, 0xf0,
	0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x3c, 0x3c, 0x0, 0x0, 0x0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0,
	0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
	0xf0, 0xf0, 0xf0, 0xf0, 0xf, 0xf, 0xf, 0xf,
	0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f,
	0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
	0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc,
	0x88, 0x44, 0x22, 0x11, 0x88, 0x44, 0x22, 0x11,
	0x11, 0x22, 0x44, 0x88, 0x11, 0x22, 0x44, 0x88,
	0x7f, 0x3e, 0x1c, 0x8, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x8, 0x1c, 0x3e, 0x7f,
	0x1, 0x3, 0x7, 0xf, 0x7, 0x3, 0x1, 0x0,
	0x80, 0xc0, 0xe0, 0xf0, 0xe0, 0xc0, 0x80, 0x0,
	0xff, 0x7e, 0x3c, 0x18, 0x18, 0x3c, 0x7e, 0xff,
	0x81, 0xc3, 0xe7, 0xff, 0xff, 0xe7, 0xc3, 0x81,
	0xf, 0xf, 0xf, 0xf, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0xf0, 0xf0, 0xf0, 0xf0,
	0xf0, 0xf0, 0xf0, 0xf0, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0xf, 0xf, 0xf, 0xf,
	0xcc, 0xcc, 0x33, 0x33, 0xcc, 0xcc, 0x33, 0x33,
	0x0, 0x4, 0x4, 0xa, 0xa, 0x11, 0x1f, 0x0,
	0x4, 0x4, 0xe, 0x4, 0xe, 0x4, 0x4, 0x0,
	0x0, 0x0, 0x0, 0xa, 0x11, 0x15, 0xa, 0x0,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff,
	0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf,
	0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0,
	0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x16, 0x9, 0x9, 0x9, 0x16, 0x0,
	0xc, 0x12, 0x12, 0xe, 0x12, 0x12, 0xe, 0x3,
	0x1f, 0x11, 0x1, 0x1, 0x1, 0x1, 0x1, 0x0,
	0x1f, 0xa, 0xa, 0xa, 0xa, 0xa, 0x19, 0x0,
	0x1f, 0x11, 0x2, 0x4, 0x2, 0x11, 0x1f, 0x0,
	0x0, 0x0, 0x1e, 0x9, 0x9, 0x9, 0x6, 0x0,
	0x0, 0xa, 0xa, 0xa, 0xa, 0x16, 0x1, 0x1,
	0x0, 0xa, 0x5, 0x4, 0x4, 0x4, 0x4, 0x0,
	0x1f, 0x4, 0xe, 0x15, 0x15, 0xe, 0x4, 0x1f,
	0x4, 0xa, 0x11, 0x1f, 0x11, 0xa, 0x4, 0x0,
	0xe, 0x11, 0x11, 0x11, 0xa, 0xa, 0x1b, 0x0,
	0xc, 0x2, 0x2, 0x4, 0xa, 0xa, 0xa, 0x4,
	0x0, 0x0, 0x0, 0xa, 0x15, 0x15, 0xa, 0x0,
	0x10, 0xe, 0x15, 0x15, 0x15, 0xe, 0x1, 0x0,
	0x1c, 0x2, 0x1, 0x1f, 0x1, 0x2, 0x1c, 0x0,
	0xe, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0,
	0x0, 0x1f, 0x0, 0x1f, 0x0, 0x1f, 0x0, 0x0,
	0x4, 0x4, 0x1f, 0x4, 0x4, 0x0, 0x1f, 0x0,
	0x3, 0xc, 0x10, 0xc, 0x3, 0x0, 0x1f, 0x0,
	0x18, 0x6, 0x1, 0x6, 0x18, 0x0, 0x1f, 0x0,
	0x8, 0x14, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4,
	0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x5, 0x2,
	0x0, 0x4, 0x0, 0x1f, 0x0, 0x4, 0x0, 0x0,
	0x0, 0xa, 0x5, 0x0, 0xa, 0x5, 0x0, 0x0,
	0x0, 0x18, 0x24, 0x24, 0x18, 0x0, 0x0, 0x0,
	0x0, 0xc, 0x1e, 0x1e, 0xc, 0x0, 0x0, 0x0,
	0x0, 0x0, 0x0, 0x0, 0xc, 0x0, 0x0, 0x0,
	0x7c, 0x4, 0x4, 0x4, 0x5, 0x6, 0x4, 0x0,
	0x5, 0xa, 0xa, 0xa, 0x0, 0x0, 0x0, 0x0,
	0x2, 0x5, 0x4, 0x2, 0x7, 0x0, 0x0, 0x0,
	0x0, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x0,
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
};

OSL_FONTINFO osl_sceFontInfo = {
	(void*)osl_sceFont_data, // Sony Computer Entertainment Font
	1,                    // 1 bit per pixel
	NULL,                 // Proportional
	7, 8, 1,              // 7x8 (1 byte per line)
	0, 0, 0, NULL         // Initialize ALL the fontinfo fields
};

// bitplanes: format (bits per pixel) of the font, imagePlanes: format of the texture to fill (power of two)
void oslDrawChar1BitToImage(OSL_IMAGE *img, int x0, int y0, int w, int h, int width, int bitPlanes, int imagePlanes, const unsigned char *font)
{
	unsigned char v, t, *data;
	int x, xx, y;
	// Number of pixels per byte depending on the format (only 1, 2, 4, and 8 supported)
	const u8 pixelsPerByte[] = {0, 8, 4, 0, 2, 0, 0, 0, 1};

	for (y = 0; y < h; y++)
	{
		data = (u8*)oslGetImagePixelAdr(img, x0, y + y0);
		for (xx = 0; xx < width;)
		{
			v = *font++;
			for (x = 0; x < 8; x += bitPlanes)
			{
				if (xx < w)
				{
					int offset = (xx + x0) & (pixelsPerByte[imagePlanes] - 1);
					t = v & ((1 << bitPlanes) - 1);
					if (t)
						*data |= t << (offset * imagePlanes);
					// Last pixel for this byte
					if (offset == pixelsPerByte[imagePlanes] - 1)
						data++;
				}
				v >>= bitPlanes;
				xx++;
			}
		}
	}
}

OSL_FONT *oslLoadFont(OSL_FONTINFO *fi) {
	OSL_FONT *font;
	int i, x, y;
	int imageFormat;
	const int pixelPlaneWidth[4] = {3, 2, 2, 1}; // For different pixel formats

	// Allocate memory for the font structure
	font = (OSL_FONT*)malloc(sizeof(OSL_FONT));
	if (!font) {
		return NULL;
	}
	memset(font, 0, sizeof(OSL_FONT)); // Initialize the font structure

	font->fontType = OSL_FONT_OFT;

	// Allocate memory for character widths
	font->charWidths = (u8*)malloc(256 * sizeof(char));
	if (!font->charWidths) {
		free(font);
		return NULL;
	}

	// Initialize character widths
	if (fi->charWidths) {
		// Use provided character widths
		for (i = 0; i < 256; i++) {
			font->charWidths[i] = fi->charWidths[i];
		}
		font->isCharWidthConstant = 0;
	} else {
		// Set uniform character width
		for (i = 0; i < 256; i++) {
			font->charWidths[i] = fi->charWidth;
		}
		font->isCharWidthConstant = 1;
		font->charWidth = fi->charWidth;
	}

	// Allocate memory for character positions
	font->charPositions = (u16*)malloc(256 * sizeof(short));
	if (!font->charPositions) {
		free(font->charWidths);
		free(font);
		return NULL;
	}
	font->addedSpace = fi->addedSpace;

	// Calculate character positions
	x = y = 0;
	for (i = 0; i < 256; i++) {
		if (x + font->charWidths[i] + font->addedSpace >= OSL_TEXT_TEXWIDTH) {
			// Move to the next line if needed
			x = 0;
			y++;
		}
		font->charPositions[i] = x + (y << OSL_TEXT_TEXDECAL);
		x += font->charWidths[i] + font->addedSpace;
	}

	// Create the image for the font
	font->img = oslCreateImage(512, (y + 1) * fi->charHeight, OSL_IN_RAM, OSL_PF_4BIT);
	if (!font->img) {
		free(font->charPositions);
		free(font->charWidths);
		free(font);
		return NULL;
	}

	// Set image format
	imageFormat = 4;

	// Create and set up the palette
	font->img->palette = oslCreatePalette(16, OSL_PF_8888);
	if (!font->img->palette) {
		oslDeleteImage(font->img);
		free(font->charPositions);
		free(font->charWidths);
		free(font);
		return NULL;
	}

	// Initialize palette data
	if (fi->paletteCount) {
		for (i = 0; i < oslMin(fi->paletteCount, font->img->palette->nElements); i++) {
			((unsigned long*)font->img->palette->data)[i] = fi->paletteData[i];
		}
	} else {
		((unsigned long*)font->img->palette->data)[0] = RGBA(255, 255, 255, 0);
		((unsigned long*)font->img->palette->data)[1] = RGBA(255, 255, 255, 255);
	}

	// Invalidate the palette cache
	sceKernelDcacheWritebackInvalidateRange(font->img->palette->data, 16 * 4);

	// Set character height
	font->charHeight = fi->charHeight;

	// Clear the image data
	memset(font->img->data, 0, font->img->totalSize);

	// Draw characters onto the image
	for (i = 0; i < 256; i++) {
		oslDrawChar1BitToImage(font->img, OSL_TEXT_CHARPOSXY(font, i),
		                       font->charWidths[i] + font->addedSpace, font->charHeight, fi->lineWidth << pixelPlaneWidth[fi->pixelFormat - 1],
		                       fi->pixelFormat, imageFormat, (u8*)fi->fontdata + i * fi->lineWidth * fi->charHeight);
	}

	// Invalidate the image cache
	sceKernelDcacheWritebackInvalidateRange(font->img->data, font->img->totalSize);

	return font;
}

int updateIntraFontCharWidth(OSL_FONT *font, intraFont *intra) {
	if (font == NULL || intra == NULL) {
		return 0;
	}

	font->charHeight = intra->texYSize;

	if (font->charWidths == NULL) {
		font->charWidths = (u8 *)malloc(256 * sizeof(u8));
		if (font->charWidths == NULL) {
			return -1;
		}
	}

	char character[2] = {0, 0}; // Initialize character array with null terminator
	for (int i = 0; i < 256; i++) {
		character[0] = (char)i;
		font->charWidths[i] = (u8)intraFontMeasureText(intra, character);
	}

	return 0;
}

OSL_FONT *oslLoadIntraFontFile(const char *filename, unsigned int options) {
	// Allocate memory for the OSL_FONT structure
	OSL_FONT *font = (OSL_FONT *)malloc(sizeof(OSL_FONT));
	if (font == NULL) {
		return NULL;
	}

	// Initialize the OSL_FONT structure
	memset(font, 0, sizeof(OSL_FONT));
	font->fontType = OSL_FONT_INTRA;

	// Load the intraFont
	font->intra = intraFontLoad(filename, options);
	if (font->intra == NULL) {
		// Free allocated memory and handle the error if the font loading fails
		free(font);
		oslHandleLoadNoFailError(filename);
		return NULL;
	}

	// Set intraFont style
	intraFontSetStyle(font->intra, 1.0f, 0xFFFFFFFF, 0xFF000000, 0.f, INTRAFONT_ALIGN_LEFT);

	// Initialize charWidths and update char widths
	font->charWidths = NULL;
	if (updateIntraFontCharWidth(font, font->intra) != 0) {
		// Free allocated memory and handle the error if updating char widths fails
		intraFontUnload(font->intra);
		free(font);
		return NULL;
	}

	// Set the character height
	font->charHeight = font->intra->texYSize;

	return font;
}

void oslLoadAltIntraFontFile(OSL_FONT *font, const char *filename) {
	// Check if the font is valid and of type OSL_FONT_INTRA
	if (font == NULL || font->fontType != OSL_FONT_INTRA) {
		return;
	}

	// Load the alternate intraFont, with options excluding INTRAFONT_CACHE_ALL
	intraFont *alt = intraFontLoad(filename, font->intra->options & ~INTRAFONT_CACHE_ALL);
	if (alt == NULL) {
		// Handle the error if the alternate font loading fails
		oslHandleLoadNoFailError(filename);
		return;
	}

	// Set the style for the alternate intraFont
	intraFontSetStyle(alt, 1.0f, 0xFFFFFFFF, 0xFF000000, 0.f, INTRAFONT_ALIGN_LEFT);

	// Update the character height if the alternate font's height is greater
	if (font->charHeight < alt->texYSize) {
		font->charHeight = alt->texYSize;
	}

	// Set the alternate font for the primary intraFont
	intraFontSetAltFont(font->intra, alt);
}

OSL_FONT *oslLoadFontFile(const char *filename) {
	OSL_FONTINFO fi;
	OSL_FONT_FORMAT_HEADER fh;
	VIRTUAL_FILE *f;
	OSL_FONT *font = NULL;
	unsigned char tcTaillesCar[256], *tcCaracteres = NULL;
	const int FILENAME_MIN_LEN = 6;

	// Check if the filename is long enough
	if (strlen(filename) < FILENAME_MIN_LEN) {
		oslHandleLoadNoFailError(filename);
		return NULL;
	}

	const char *start = filename + (strlen(filename) - 4);
	const char *bwfon = filename + (strlen(filename) - 6);

	if (!strncmp(start, ".pgf", 4) || !strncmp(start, ".PGF", 4) ||
	    !strncmp(bwfon, ".bwfon", 6) || !strncmp(bwfon, ".BWFON", 6)) {
		font = oslLoadIntraFontFile(filename, intra_options);
	} else {
		f = VirtualFileOpen((void*)filename, 0, VF_AUTO, VF_O_READ);
		if (f) {
			// Read font header
			if (VirtualFileRead(&fh, sizeof(fh), 1, f) == 0) {
				VirtualFileClose(f);
				oslHandleLoadNoFailError(filename);
				return NULL;
			}
			// Verify header
			if (!strcmp(fh.strVersion, "OSLFont v01")) {
				fi.pixelFormat = fh.pixelFormat;
				// Verify pixel format
				if (fh.pixelFormat < 1 || fh.pixelFormat > 4) {
					VirtualFileClose(f);
					oslHandleLoadNoFailError(filename);
					return NULL;
				}

				if (fh.variableWidth) {
					if (VirtualFileRead(tcTaillesCar, 256 * sizeof(unsigned char), 1, f) == 0) {
						VirtualFileClose(f);
						oslHandleLoadNoFailError(filename);
						return NULL;
					}
					fi.charWidths = tcTaillesCar;
				} else {
					fi.charWidths = NULL;
				}

				fi.charWidth = fh.charWidth;
				fi.charHeight = fh.charHeight;
				fi.lineWidth = fh.lineWidth;
				fi.addedSpace = fh.addedSpace;

				// Allocate memory for character data
				tcCaracteres = (unsigned char*)malloc(fh.lineWidth * fi.charHeight * 256);
				if (!tcCaracteres) {
					VirtualFileClose(f);
					oslHandleLoadNoFailError(filename);
					return NULL;
				}

				// Read character data
				if (VirtualFileRead(tcCaracteres, fh.lineWidth * fi.charHeight * 256, 1, f) > 0) {
					fi.fontdata = tcCaracteres;
					fi.paletteCount = fh.paletteCount;
					fi.paletteData = NULL;

					// Check for palette data
					if (fi.paletteCount > 0) {
						fi.paletteData = (unsigned long*)malloc(fi.paletteCount * sizeof(unsigned long));
						if (fi.paletteData) {
							// Read palette entries
							if (VirtualFileRead(fi.paletteData, fi.paletteCount * sizeof(unsigned long), 1, f) == 0) {
								fi.paletteCount = 0;
								free(fi.paletteData);
								fi.paletteData = NULL;
							}
						}
					}

					// Load the font
					font = oslLoadFont(&fi);

					if (fi.paletteData) {
						free(fi.paletteData);
						fi.paletteData = NULL;
					}
				}
				free(tcCaracteres);
			}
			VirtualFileClose(f);
		}
		if (!font) {
			oslHandleLoadNoFailError(filename);
		} else {
			font->fontType = OSL_FONT_OFT;
		}
	}
	return font;
}

void oslDeleteFont(OSL_FONT *f) {
	if (f == NULL) {
		return;
	}

	if (f->fontType == OSL_FONT_INTRA) {
		// Unload the alternate intraFont if it exists
		if (f->intra->altFont) {
			intraFontUnload(f->intra->altFont);
			f->intra->altFont = NULL;
		}
		// Unload the primary intraFont
		intraFontUnload(f->intra);
		f->intra = NULL;
	} else if (f->fontType == OSL_FONT_OFT) {
		// Delete associated image and free allocated memory for charPositions and charWidths
		oslDeleteImage(f->img);
		free(f->charPositions);
		f->charPositions = NULL;
		free(f->charWidths);
		f->charWidths = NULL;
	}

	// Free the OSL_FONT structure itself and set the pointer to NULL
	free(f);
	f = NULL;
}

void oslDrawTextTileBack(int x, int y, int tX, int tY) {
	// Blend the text background color
	int color = oslBlendColor(osl_textBkColor);

	// Allocate memory for vertices
	OSL_LINE_VERTEX_COLOR32 *vertices = (OSL_LINE_VERTEX_COLOR32 *)sceGuGetMemory(2 * sizeof(OSL_LINE_VERTEX_COLOR32));

	// Adjust tile width by adding the extra space of the current font
	tX += osl_curFont->addedSpace;

	// Set the vertex colors and coordinates
	vertices[0].color = color;
	vertices[0].x = x;
	vertices[0].y = y;
	vertices[0].z = 0;

	vertices[1].color = color;
	vertices[1].x = x + tX;
	vertices[1].y = y + tY;
	vertices[1].z = 0;

	// Disable texturing if it is currently enabled
	int wasEnable = osl_textureEnabled;
	oslDisableTexturing();

	// Draw the vertices as a sprite
	sceGuDrawArray(GU_SPRITES, GU_COLOR_8888 | GU_VERTEX_16BIT | GU_TRANSFORM_2D, 2, 0, vertices);

	// Writeback the data cache to ensure it is correctly updated in memory
	sceKernelDcacheWritebackRange(vertices, 2 * sizeof(OSL_LINE_VERTEX_COLOR32));

	// Re-enable texturing if it was previously enabled
	if (wasEnable) {
		oslEnableTexturing();
	}
}

// Function to draw a tile of the selected texture. Avoid using this outside.
void oslDrawTextTile(int u, int v, int x, int y, int tX, int tY) {
	int color = oslBlendColor(osl_textColor);

	// If enabled, draw the background
	if (osl_textBkColor & 0xff000000) {
		oslDrawTextTileBack(x, y, tX, tY);
	}

	// Add additional space to the width of the tile
	tX += osl_curFont->addedSpace;

	// Allocate memory for vertex data
	OSL_FAST_VERTEX_COLOR32 *vertices;
	vertices = (OSL_FAST_VERTEX_COLOR32*)sceGuGetMemory(2 * sizeof(OSL_FAST_VERTEX_COLOR32));

	// Define the vertices for the tile
	vertices[0].u = u;
	vertices[0].v = v;
	vertices[0].color = color;
	vertices[0].x = x;
	vertices[0].y = y;
	vertices[0].z = 0;

	vertices[1].u = u + tX;
	vertices[1].v = v + tY;
	vertices[1].color = color;
	vertices[1].x = x + tX;
	vertices[1].y = y + tY;
	vertices[1].z = 0;

	// Store the previous state of texturing
	int wasEnabled = osl_textureEnabled;

	// Enable texturing
	oslEnableTexturing();

	// Draw the tile
	sceGuDrawArray(GU_SPRITES, GU_TEXTURE_16BIT | GU_COLOR_8888 | GU_VERTEX_16BIT | GU_TRANSFORM_2D, 2, 0, vertices);

	// Write back the cache to ensure the data is correctly updated
	sceKernelDcacheWritebackRange(vertices, 2 * sizeof(OSL_FAST_VERTEX_COLOR32)); //SAKYA

	// Restore the previous state of texturing
	if (!wasEnabled) {
		oslDisableTexturing();
	}
}

void oslDrawChar(int x, int y, unsigned char c) {
	// Check if the current font is valid
	if (!osl_curFont) {
		return;
	}

	// Handle OSL_FONT_OFT font type
	if (osl_curFont->fontType == OSL_FONT_OFT) {
		oslSetTexture(osl_curFont->img);
		// Draw the character tile
		oslDrawTextTile(OSL_TEXT_CHARPOSXY(osl_curFont, c), x, y, osl_curFont->charWidths[c], osl_curFont->charHeight);
	}
	// Handle OSL_FONT_INTRA font type
	else if (osl_curFont->fontType == OSL_FONT_INTRA) {
		char temp[2];
		snprintf(temp, sizeof(temp), "%c", c);
		y += (int)((float)osl_curFont->charHeight / 2.0) + 1;
		intraFontPrint(osl_curFont->intra, x, y, temp);
	}
}

void oslDrawString(int x, int y, const char *str) {
	// Check if the current font is valid
	if (!osl_curFont) {
		return;
	}

	// Handle OSL_FONT_OFT font type
	if (osl_curFont->fontType == OSL_FONT_OFT) {
		unsigned char c;
		oslSetTexture(osl_curFont->img);

		while (*str) {
			c = *(unsigned char*)str++;
			oslDrawTextTile(OSL_TEXT_CHARPOSXY(osl_curFont, c), x, y, osl_curFont->charWidths[c], osl_curFont->charHeight);
			x += osl_curFont->charWidths[c];
		}
	}
	// Handle OSL_FONT_INTRA font type
	else if (osl_curFont->fontType == OSL_FONT_INTRA) {
		y += (int)((float)osl_curFont->charHeight / 2.0) + 1;
		intraFontPrint(osl_curFont->intra, x, y, str);
	}
}

void oslDrawStringLimited(int x, int y, int width, const char *str) {
	// Check if the current font is valid
	if (!osl_curFont) {
		return;
	}

	int limitX = x + width;
	unsigned char c;

	// Handle OSL_FONT_OFT font type
	if (osl_curFont->fontType == OSL_FONT_OFT) {
		oslSetTexture(osl_curFont->img);

		while (*str) {
			c = *(unsigned char*)str++;

			// Break if the next character exceeds the limit width
			if (x + osl_curFont->charWidths[c] > limitX) {
				break;
			}

			// Draw the character tile
			oslDrawTextTile(OSL_TEXT_CHARPOSXY(osl_curFont, c), x, y, osl_curFont->charWidths[c], osl_curFont->charHeight);
			x += osl_curFont->charWidths[c];
		}
	}
	// Handle OSL_FONT_INTRA font type
	else if (osl_curFont->fontType == OSL_FONT_INTRA) {
		oslIntraFontPrintColumn(osl_curFont, x, y, width, str);
	}
}

void oslDrawTextBox(int x0, int y0, int x1, int y1, const char *text, int format) {
	// Check if the current font is valid and of type OSL_FONT_OFT
	if (!osl_curFont || osl_curFont->fontType != OSL_FONT_OFT) {
		return;
	}

	int x = x0, y = y0, x2;
	unsigned char c;
	const char *text2;

	while (*text) {
		c = *text;

		// Handle spaces
		if (c == ' ') {
			text2 = text;
			x2 = x;
			// Measure the width of the word
			do {
				x2 += osl_curFont->charWidths[(int)(*text2++)];
				if (x2 > x1) {
					text++;
					goto newline;
				}
			} while (*text2 != '\n' && *text2 != ' ' && *text2);
		}

		// Handle new lines and word wrapping
		if (x + osl_curFont->charWidths[c] > x1 || *text == '\n') {
newline:
			x = x0;
			y += osl_curFont->charHeight;
			// Stop if the text exceeds the box height
			if (y + osl_curFont->charHeight > y1) {
				break;
			}
			// Skip newline characters
			if (*text == '\n') {
				text++;
			}
			continue;
		}

		// Draw the character
		oslDrawChar(x, y, c);
		x += osl_curFont->charWidths[c];
		text++;
	}
}

void oslDrawTextBoxByWords(int x0, int y0, int x1, int y1, const char *text, int format) {
	char buffer[50];
	int charCount;
	unsigned char c;
	int x = x0, y = y0, x2;
	const char *text2 = text;

	while (*text2) {
		memset(buffer, '\0', sizeof(buffer));
		charCount = 0;
		x2 = 0;

		// Extract a word
		while (*text2 != '\n' && *text2 != ' ' && *text2) {
			charCount++;
			text2++;
		}

		if (charCount > 0) {
			strncpy(buffer, text, charCount);
			x2 = oslGetStringWidth(buffer);

			// Check if the word fits in the current line, else move to the next line
			if ((x + x2) > x1) {
				x = x0;
				y += osl_curFont->charHeight;
				if (y > y1) break;
			}

			// Draw the word
			oslDrawString(x, y, buffer);
			text += charCount;
			x += x2;
		}

		// Handle spaces
		if (*text2 == ' ') {
			c = *text;
			x += osl_curFont->charWidths[c];
			text2++;
			text++;
		}

		// Handle newlines
		if (*text2 == '\n') {
			x = x0;
			y += osl_curFont->charHeight;
			if (y > y1) break;
			text2++;
			text++;
		}
	}
}

void oslInitConsole() {
	// Load and set the system font if it is not already loaded
	if (!osl_sceFont) {
		osl_sceFont = oslLoadFont(&osl_sceFontInfo);
	}
	oslSetFont(osl_sceFont);

	// Clear the screen
	oslCls();

	// osl_consoleOk = 1;
}

void oslMoveMem(void *dst, const void *src, int size) {
	unsigned long *fdst = (unsigned long *)dst;
	const unsigned long *fsrc = (const unsigned long *)src;

	// Copy memory in chunks of 4 bytes
	while (size > 0) {
		*fdst++ = *fsrc++;
		size -= 4;
	}
}

void oslConsolePrint(const char *str) {
	unsigned char c;
	OSL_FONT *oldFont = NULL;

//	if (osl_consoleOk == NULL)
//		return;

	// Save and switch to the default console font if needed
	if (osl_curFont != osl_sceFont) {
		oldFont = osl_curFont;
		oslSetFont(osl_sceFont);
	}

	// Iterate over each character in the string
	while (*str) {
		c = *(unsigned char *)str++;

		// Print the character if it is not a newline
		if (c != '\n') {
			oslDrawChar(osl_consolePosX, osl_consolePosY, c);
			osl_consolePosX += osl_curFont->charWidths[c];
		}

		// Handle line wrapping and screen scrolling
		if (osl_consolePosX + 7 > osl_curBuf->sizeX || c == '\n') {
			osl_consolePosY += osl_curFont->charHeight;

			// Scroll the screen if needed
			if (osl_consolePosY + osl_curFont->charHeight > osl_curBuf->sizeY) {
				osl_consolePosY -= osl_curFont->charHeight;
				oslSyncDrawing();

				// Move the buffer contents up to create space for new text
				oslMoveMem(
					oslAddVramPrefixPtr(oslGetImageLine(osl_curBuf, 0)),
					oslAddVramPrefixPtr(oslGetImageLine(osl_curBuf, osl_curFont->charHeight)),
					osl_curBuf->totalSize - (int)oslGetImageLine(osl_curBuf, osl_curFont->charHeight)
					);

				// Clear the bottom line of the buffer
				oslFlushDataCache();
				oslDrawFillRect(0, osl_consolePosY, osl_curBuf->sizeX, osl_curBuf->sizeY, 0);
			}

			// Reset position to the beginning of the line
			osl_consolePosX = 0;
		}
	}

	// Restore the previous font if it was changed
	if (oldFont != NULL) {
		oslSetFont(oldFont);
	}
}

void oslSetTextColor(OSL_COLOR color) {
	osl_textColor = color;
}

void oslSetBkColor(OSL_COLOR color) {
	osl_textBkColor = color;
}

int oslGetStringWidth(const char *str) {
	// Return 0 if the current font is not set
	if (osl_curFont == NULL) {
		return 0;
	}

	u32 width = 0;

	// Calculate string width based on font type
	if (osl_curFont->fontType == OSL_FONT_OFT) {
		// Iterate over each character in the string
		while (*str) {
			unsigned char c = (unsigned char)*str++;
			width += osl_curFont->charWidths[c];
		}
	} else if (osl_curFont->fontType == OSL_FONT_INTRA) {
		// Use intraFontMeasureText to calculate string width
		width = (int)intraFontMeasureText(osl_curFont->intra, str);
	}

	return width;
}

int oslGetTextBoxHeight(int width, int maxHeight, const char *text, int format) {
	// Check if the current font is valid and of type OSL_FONT_OFT
	if (osl_curFont == NULL || osl_curFont->fontType != OSL_FONT_OFT) {
		return 0;
	}

	int x = 0, y = 0, x2;
	unsigned char c;
	const char *text2;
	int newLine = 1;

	// Iterate over each character in the text
	while (*text) {
		c = *text;

		// Handle spaces and line wrapping
		if (c == ' ') {
			text2 = text;
			x2 = x;
			do {
				x2 += osl_curFont->charWidths[(int)(*text2++)];
				if (x2 > width) {
					text++;
					goto newline;
				}
			} while (*text2 != '\n' && *text2 != ' ' && *text2);
		}

		// Handle new lines and line wrapping
		if (x + osl_curFont->charWidths[c] > width || *text == '\n') {
newline:
			x = 0;
			if (newLine && *text == '\n') {
				y += osl_curFont->charHeight;
			}
			newLine = 1;

			// Skip the newline character
			if (*text == '\n') {
				text++;
			}
			continue;
		}

		// Check if the text box exceeds max height
		if (y + osl_curFont->charHeight > maxHeight && maxHeight > 0) {
			break;
		}

		if (newLine) {
			newLine = 0;
			y += osl_curFont->charHeight;
		}

		x += osl_curFont->charWidths[c];
		text++;
	}

	return y;
}

int oslIntraFontInit(unsigned int options) {
	// Set global options for intraFont
	intra_options = options;

	// Mark intraFont as initialized
	osl_intraInit = 1;

	// Initialize intraFont and return the result
	return intraFontInit();
}

void oslIntraFontShutdown() {
	// Mark intraFont as not initialized
	osl_intraInit = 0;

	// Reset global options for intraFont
	intra_options = 0;

	// Shut down intraFont
	intraFontShutdown();
}

void oslIntraFontSetStyle(OSL_FONT *font, float size, unsigned int color, unsigned int shadowColor, float angle, unsigned int options) {
	if (font->intra) {
		// Set the style for the main intraFont
		intraFontSetStyle(font->intra, size, color, shadowColor, angle, options);

		// Update character widths after setting the style
		updateIntraFontCharWidth(font, font->intra);

		// Set the style for the alternate intraFont if it exists
		if (font->intra->altFont) {
			intraFontSetStyle(font->intra->altFont, size, color, shadowColor, angle, options);
		}
	}
}

float oslIntraFontPrintColumn(OSL_FONT *font, float x, float y, float width, const char *text) {
	if (font->intra) {
		// Adjust vertical position based on font height
		y += (float)font->charHeight / 2.0f + 1.0f;

		// Print the text in a column using intraFont
		return intraFontPrintColumn(font->intra, x, y, width, text);
	}
	return 0;
}
