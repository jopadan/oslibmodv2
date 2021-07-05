#ifndef _OSL_DRAWING_H_
#define _OSL_DRAWING_H_

#ifdef __cplusplus
extern "C" {
#endif


#ifndef PSP
	#undef RGB
#endif
typedef unsigned long OSL_COLOR;
extern void oslInitGfx(int pixelFormat, int bDoubleBuffer);
extern void oslStartDrawing();
extern void oslEndDrawing();
extern void oslSyncDrawing();

extern void oslSwapBuffers();
extern void oslEndGfx();

extern void oslSetSysDisplayListSize(int newSize);

extern void oslClearScreen(int backColor);

extern void oslSetScreenClipping(int x0, int y0, int x1, int y1);

extern void oslSetDepthTest(int enabled);

#define oslResetScreenClipping()					oslSetScreenClipping(0, 0, osl_curBuf->sizeX, osl_curBuf->sizeY);

extern void oslSetAlpha2(u32 effect, u32 coeff1, u32 coeff2);

/** See oslSetAlpha2. */
extern inline void oslSetAlpha(u32 effect, u32 coeff1)			{
	oslSetAlpha2(effect, coeff1, 0xffffffff);
}


/** Structure containing a special alpha effect data. */
typedef struct		{
	int effect;								//!< Current alpha special effect
	int coeff1;								//!< First coefficient
	int coeff2;								//!< Second coefficient
} OSL_ALPHA_PARAMS;

extern int osl_currentAlphaEffect;
extern OSL_COLOR osl_currentAlphaCoeff, osl_currentAlphaCoeff2;

/** Stores the current alpha parameters to an OSL_ALPHA_PARAMS structure. */
extern inline void oslGetAlphaEx(OSL_ALPHA_PARAMS *alpha)		{
	alpha->effect = osl_currentAlphaEffect;
	alpha->coeff1 = osl_currentAlphaCoeff;
	alpha->coeff2 = osl_currentAlphaCoeff2;
}

/** Sets the current alpha parameters using an OSL_ALPHA_PARAMS structure. */
extern inline void oslSetAlphaEx(OSL_ALPHA_PARAMS *alpha)		{
	oslSetAlpha2(alpha->effect, alpha->coeff1, alpha->coeff2);
}

extern void oslSetBilinearFilter(int enabled);
extern void oslSetDithering(int enabled);

extern void oslSetTransparentColor(OSL_COLOR color);
extern void oslDisableTransparentColor();

/** Holds whether bilinear filetering is currently turned on. */
extern int osl_bilinearFilterEnabled;
/** Holds whether dithering is currently turned on. */
extern int osl_ditheringEnabled;
/** Holds whether color keying is enabled. */
extern int osl_colorKeyEnabled;

//Undocumented (see oslSetAlpha for more information).
enum {OSL_FX_NONE=0, OSL_FX_FLAT, OSL_FX_ALPHA, OSL_FX_ADD, OSL_FX_SUB};
#define OSL_FX_DEFAULT OSL_FX_RGBA
#define OSL_FX_OPAQUE OSL_FX_NONE
#define OSL_FX_TINT				(OSL_FX_ALPHA | OSL_FX_COLOR)
//Cumulable avec les autres pour définir l'utilisation du canal alpha.
#define OSL_FX_RGBA 0x100
//Coefficients alpha à trois canaux
#define OSL_FX_COLOR 0x1000


//Don't access them!
//extern int osl_currentResolutionBPP;
//Couleur transparente utilisée au chargement des images.
extern int osl_colorKeyValue;

/** Creates a 32-bit opaque color. */
#define RGB(r,v,b)		((r) | ((v)<<8) | ((b)<<16) | (0xff<<24))
/** Creates a 32-bit color. 32-bit colors is what all OSLib calls asking for a color want. Use RGB if you don't want to bother about alpha (semi transparency). */
#define RGBA(r,v,b,a)	((r) | ((v)<<8) | ((b)<<16) | ((a)<<24))
/** Creates a 12-bit color with 3 coefficients (red, green, blue). Alpha is set to the maximum (opaque). The r, v, b values can be from 0 to 255, they're divided to match the 12-bit pixel format. */
#define RGB12(r,v,b)	((((b)>>4)<<8) | (((v)>>4)<<4) | ((r)>>4) | (0xf<<12))
/** Creates a 12-bit color with 4 coefficients (red, green, blue, alpha). */
#define RGBA12(r,v,b,a)	((((a)>>4)<<12) | (((b)>>4)<<8) | (((v)>>4)<<4) | ((r)>>4))
/** Creates a 15-bit opaque color. */
#define RGB15(r,v,b)	((((b)>>3)<<10) | (((v)>>3)<<5) | ((r)>>3) | (1<<15))
/** Creates a 15-bit color with alpha. */
#define RGBA15(r,v,b,a)	((((a)>>7)<<15) | (((b)>>3)<<10) | (((v)>>3)<<5) | ((r)>>3))
/** Creates a 16-bit color. */
#define RGB16(r,v,b)	((((b)>>3)<<11) | (((v)>>2)<<5) | ((r)>>3))

#define oslRgbaGet8888(data, r, g, b, a)		((r)=((data)&0xff), (g)=(((data)>>8)&0xff), (b)=(((data)>>16)&0xff), (a)=(((data)>>24)&0xff))
/** Gets R, G, B, A values from a 4444 color. The values are always 8 bit, so they are expanded with a multiplication!
	Example:
	\code
u32 color = RGBA12(255, 128, 0, 1);
u8 red, green, blue, alpha;

oslRgbGet4444(color, red, green, blue, alpha);

oslPrintf("%i %i %i %i", red, green, blue, alpha);
	\endcode

	This will print 240 128 0 0. The alpha was 1 but was lost because of precision in 12-bit mode (it can only store coefficients from 0 to 15 instead of 0 to 255). The red color was 255 but it has lost
	precision due to 12-bit conversion. It has passed from 255 to 15 (integer division by 16), and then was multiplicated by 16, making it 240 instead of 255. This can be problematic because you will no
	more get bright and vibrant color after conversion. However you can use the 'f' alternate routines which give more precise results (but they are slightly slower), in this case the result of
	oslRgbaGet4444f would be 255 136 0 0, which is brighter and nicer.
*/
#define oslRgbaGet4444(data, r, g, b, a)		((r)=((data)&0xf)<<4, (g)=(((data)>>4)&0xf)<<4, (b)=(((data)>>8)&0xf)<<4, (a)=(((data)>>12)&0xf)<<4)
/** Get components from a 5551 (15-bit) color. Same remarks as oslRgbGet4444 apply. */
#define oslRgbaGet5551(data, r, g, b, a)		((r)=((data)&0x1f)<<3, (g)=(((data)>>5)&0x1f)<<3, (b)=(((data)>>10)&0x1f)<<3, (a)=(((data)>>15)&0x1)<<7)
/** Get components from a 5650 (16-bit) color. Same remarks as oslRgbGet4444 apply. */
#define oslRgbGet5650(data, r, g, b)			((r)=((data)&0x1f)<<3, (g)=(((data)>>5)&0x3f)<<2, (b)=(((data)>>11)&0x1f)<<3)

//Précises - vieilles et lentes
/*#define oslRgbGet5650f(data, r, g, b)			((r)=(((data)&0x1f)*255)/31, (g)=((((data)>>5)&0x3f)*255)/63, (b)=((((data)>>11)&0x1f)*255)/31)
#define oslRgbaGet5551f(data, r, g, b, a)		((r)=(((data)&0x1f)*255)/31, (g)=((((data)>>5)&0x1f)*255)/31, (b)=((((data)>>10)&0x1f)*255)/31, (a)=(((data)>>15)&0x1)*255)
#define oslRgbaGet4444f(data, r, g, b, a)		((r)=(((data)&0xf)*255)/15, (g)=((((data)>>4)&0xf)*255)/15, (b)=((((data)>>8)&0xf)*255)/15, (a)=((((data)>>12)&0xf)*255)/15)*/

//Encore autre chose...
/*#define oslRgbGet5650f(data, r, g, b)			((r)=(((data)&0x1f)*264)>>5, (g)=((((data)>>5)&0x3f)*260)>>6, (b)=((((data)>>11)&0x1f)*264)>>5)
#define oslRgbaGet5551f(data, r, g, b, a)		((r)=(((data)&0x1f)*264)>>5, (g)=((((data)>>5)&0x1f)*264)>>5, (b)=((((data)>>10)&0x1f)*264)>>5, (a)=(((data)>>15)&0x1)*255)
#define oslRgbaGet4444f(data, r, g, b, a)		((r)=(((data)&0xf)*272)>>4, (g)=((((data)>>4)&0xf)*272)>>4, (b)=((((data)>>8)&0xf)*272)>>4, (a)=((((data)>>12)&0xf)*272)>>4)*/

//Meilleur compromis taille - vitesse
/** Look at oslRgbaGet4444 to find out why these are useful. */
#define oslRgbaGet4444f(data, r, g, b, a)		((r)=((data)&0xf)<<4 | ((data)&0xf), (g)=(((data)>>4)&0xf)<<4 | (((data)>>4)&0xf), (b)=(((data)>>8)&0xf)<<4 | (((data)>>8)&0xf), (a)=(((data)>>12)&0xf)<<4 | (((data)>>12)&0xf))
/** Same remark as oslRgbaGet4444f. */
#define oslRgbaGet5551f(data, r, g, b, a)		((r)=((data)&0x1f)<<3 | ((data)&0x1f)>>2, (g)=(((data)>>5)&0x1f)<<3 | (((data)>>5)&0x1f)>>2, (b)=(((data)>>10)&0x1f)<<3 | (((data)>>10)&0x1f)>>2, (a)=(((data)>>15)&0x1)*255)
/** Same remark as oslRgbaGet4444f. */
#define oslRgbGet5650f(data, r, g, b)			((r)=((data)&0x1f)<<3 | ((data)&0x1f)>>2, (g)=(((data)>>5)&0x3f)<<2 | (((data)>>5)&0x3f)>>4, (b)=(((data)>>11)&0x1f)<<3 | (((data)>>10)&0x1f)>>2)

/** Draws a line from (x0, y0) to (x1, y1). */
extern void oslDrawLine(int x0, int y0, int x1, int y1, OSL_COLOR color);
/** Draws an empty rectangle from (x0, y0) to (x1, y1). */
extern void oslDrawRect(int x0, int y0, int x1, int y1, OSL_COLOR color);
/** Draws a filled rectangle from (x0, y0) to (x1, y1). */
extern void oslDrawFillRect(int x0, int y0, int x1, int y1, OSL_COLOR color);
/** Draws a gradient rectangle from (x0, y0) to (x1, y1).
	\param x0, y0
		Top-left position of the rectangle.
	\param x1, y1
		Bottom-right position of the rectangle.
	\param c1
		Color of the top-left corner.
	\param c2
		Color of the top-right corner.
	\param c3
		Color of the bottom-left corner.
	\param c4
		Color of the bottom-right corner.
*/
extern void oslDrawGradientRect(int x0, int y0, int x1, int y1, OSL_COLOR c1, OSL_COLOR c2, OSL_COLOR c3, OSL_COLOR c4);

//Undocumented
extern void oslSwizzleTexture(u8* out, const u8* in, unsigned int width, unsigned int height);
extern void oslUnswizzleTexture(u8* out, const u8* in, unsigned int width, unsigned int height);
extern void oslDrawTile(int u, int v, int x, int y, int tX, int tY);

#define OSL_PALETTEDATA16 unsigned short __attribute__((aligned(16)))
#define OSL_PALETTEDATA32 unsigned long __attribute__((aligned(16)))

/** Palette type. */
typedef struct			{
	short pixelFormat;						//!< Pixel format of palette entries
	short nElements;						//!< Number of entries
	short location;							//!< Location of the palette (always use OSL_IN_RAM)
	void *data;								//!< Actual (raw) data, representing color entries in their pixel format
} OSL_PALETTE;

/** Constants for the flags member of OSL_IMAGE. */
enum OSL_IMAGE_FLAGS {
	OSL_IMAGE_SWIZZLED = 1,					//!< Image is swizzled
	OSL_IMAGE_COPY = 2,						//!< Image is a copy
	OSL_IMAGE_AUTOSTRIP = 4					//!< Image can be automatically stripped (let it one)
};

/** Structure of an image loaded in memory. */
typedef struct		{
	//protected
	u16 sizeX, sizeY;						//!< Displayable size
	u16 sysSizeX, sysSizeY;					//!< Size aligned to the next power of two
	u16 realSizeX, realSizeY;				//!< Actual buffer size (never write outside of these dimensions!)
	void *data;								//!< Raw image data in memory
	u8 flags;								//!< Special image flags
	int totalSize;							//!< Total image size in bytes
	short location;							//!< Image location (OSL_IN_RAM or OSL_IN_VRAM)
	short pixelFormat;						//!< Image pixel format

	//public
	OSL_PALETTE *palette;					//!< Palette for 4 and 8 bit modes
	u16 frameSizeX, frameSizeY;				//!< Size of a frame in the image

	//Special
	int x, y;								//!< Image positions
	int stretchX, stretchY;					//!< Final image size when drawn (stretched)
	//Morceau
	float offsetX0, offsetY0, offsetX1, offsetY1;		//!< Offset in the texture
	//Rotation
	int centerX, centerY;					//!< Rotation center
	int angle;								//!< Angle (rotation) in degrees
	//Paramètres
//	bool autoStrip;							//!< Automatic stripping (let it one)
} OSL_IMAGE;

/** Places where to place an image. Values for the argument "location" of some loading routines. */
typedef enum OSL_LOCATION_FLAGS {
	OSL_IN_NONE=0,								//!< Doesn't exist
	OSL_IN_VRAM=1,								//!< In VRAM
	OSL_IN_RAM=2,								//!< In RAM
	OSL_LOCATION_MASK=7,						//!< There will probably never be more than 8 locations...
	OSL_SWIZZLED=8,								//!< Directly swizzle image (only works for oslLoadImage[...] functions!)
	OSL_UNSWIZZLED=16							//!< Force no swizzling (oslLoadImage[...])
} OSL_LOCATION_FLAGS;

/** Pixelformats (color types / modes). */
enum OSL_PIXELFORMATS		{
	OSL_PF_5650=GU_PSM_5650,					//!< 16 bits, 5 bits per component, except green which has 6, no alpha
	OSL_PF_5551=GU_PSM_5551,					//!< 15 bits, 5 bits per component, 1 alpha bit
	OSL_PF_4444=GU_PSM_4444,					//!< 12 bits, 4 bits per component, 4 alpha bits
	OSL_PF_8888=GU_PSM_8888,					//!< 32 bits, 8 bits per component, 8 alpha bits
	OSL_PF_4BIT=GU_PSM_T4,						//!< Paletted format, 4 bits (16 colors), cannot be set as drawbuffer
	OSL_PF_8BIT=GU_PSM_T8						//!< Paletted format, 8 bits (256 colors), cannot be set as drawbuffer
};

extern OSL_IMAGE *oslCreateImage(int larg, int haut, short location, short pixelFormat);
/** Deletes an image previously created or loaded. */
extern void oslDeleteImage(OSL_IMAGE *img);

extern OSL_IMAGE *oslLoadImageFile(char *filename, int location, int pixelFormat);

/** Loads a PNG file. Same remark as for oslLoadImageFile apply. */
extern OSL_IMAGE *oslLoadImageFilePNG(char *filename, int location, int pixelFormat);
/** Loads a JPG file. Same remark as for oslLoadImageFile apply.

Note: The actual JPG decompressor is very simple, and doesn't support JPG files of a too high quality (it will crash in this case). Avoid using JPG files with a quality factor of
more than 90%. Also, if you let users the choice of using JPG files, you should specify this limitation in your instructions. */
extern OSL_IMAGE *oslLoadImageFileJPG(char *filename, int location, int pixelFormat);
/** Loads a GIF file. Same remark as for oslLoadImageFile apply. */
extern OSL_IMAGE *oslLoadImageFileGIF(char *filename, int location, int pixelFormat);

//Wrapped to by oslSetImageAutoSwizzle.
extern int osl_autoSwizzleImages;

extern inline void oslSetImageAutoSwizzle(int enabled)		{
	osl_autoSwizzleImages = enabled;
}

extern int osl_alignBuffer;

//Undocumented
extern void *oslAllocImageData(OSL_IMAGE *img, int location);
extern void oslFreeImageData(OSL_IMAGE *img);

#define oslAddVramPrefixPtr(adr)			((void*)((int)(adr)|0x04000000))
#define oslRemoveVramPrefixPtr(adr)			((void*)((int)(adr)&(~0x04000000)))

//Don't use
extern int oslImageLocationIsSwizzled(int location);

#ifdef PSP
	/** Draws an image at positions px, py. */
	#define oslDrawImageXY(img,px,py)				({ (img)->x=(px), (img)->y=(py); oslDrawImage(img); })
	/** Here for backward compatibility, don't use it. */
	#define oslDrawImageSimpleXY(img,px,py)	({ (img)->x=(px), (img)->y=(py); oslDrawImageSimple(img); })
#else
	#define oslDrawImageXY(img,px,py)				{ (img)->x=(px), (img)->y=(py); oslDrawImage(img); }
	#define oslDrawImageSimpleXY(img,px,py)			{ (img)->x=(px), (img)->y=(py); oslDrawImageSimple(img); }
#endif

/** Draws an image. */
extern void oslDrawImage(OSL_IMAGE *img);
/** Here for backward compatibility, don't use it. */
extern void oslDrawImageSimple(OSL_IMAGE *img);
/** Don't use this routine, it will probably do something else in the next OSLib release. */
extern void oslDrawImageBig(OSL_IMAGE *img);

/** @} */ // end of image_drawing


/** @defgroup image_placement Image placement

	Image placement in OSLib.
	@{
*/

#ifdef PSP
	/** Sets the source rectangle of the image to be displayed. Let's imagine you've got a big image (e.g. 128x128). This image contains in fact 16 "sprites" of 32x32 each. You can set it to display
	one of these with:
\code
oslSetImageTile(image, 0, 0, 32, 32);
oslDrawImage(image);
\endcode
	This means "display the part of the image beginning at (0,0) (top-left) and finishing at (32,32) (bottom-right) excluded, rendering a 32x32 sprite. For the next one to the right you'd call
	oslSetImageTile(image, 32, 0, 64, 32); */
	#define oslSetImageTile(img,x0,y0,x1,y1)		({ (img)->offsetX0=(float)x0, (img)->offsetY0=(float)y0, (img)->offsetX1=(float)x1, (img)->offsetY1=(float)y1; (img)->stretchX = oslAbs((int)((float)((img)->offsetX1) - (float)((img)->offsetX0))), (img)->stretchY = oslAbs((int)((float)((img)->offsetY1) - (float)((img)->offsetY0))); })
	/** Same as oslSetImageTile except that x1 and y1 parameters are the size of the image rectangle. In case of 32x32 sprites it would always be 32, 32, and you would just set the x0, y0 coordinates to
	the beginning (top-left corner) of your sprite in the image. */
	#define oslSetImageTileSize(img,x0,y0,x1,y1)		({ (img)->offsetX0=(float)(x0), (img)->offsetY0=(float)(y0), (img)->offsetX1=(float)(x0)+(float)(x1), (img)->offsetY1=(float)(y0)+(float)(y1), (img)->stretchX = (int)(x1), (img)->stretchY = (int)(y1); })
	/** Resets the image rectangle to its full (original) size. */
	#define oslResetImageTile(img)					({ (img)->offsetX0=0, (img)->offsetY0=0, (img)->offsetX1=(img)->sizeX, (img)->offsetY1=(img)->sizeY; (img)->stretchX = (img)->sizeX, (img)->stretchY = (img)->sizeY; })
	/** Mirrors an image (or an image tile) horizontally. Note that mirroring twice reverts the image to its normal orientation. If you are calling this in a loop, don't forget to reset it after the
	image is drawn, else your image will be mirrored once per loop iteration and will appear ugly. */
	#define oslMirrorImageH(img)					({ float ___tmp;  ___tmp = (img)->offsetX0; (img)->offsetX0 = (img)->offsetX1; (img)->offsetX1 = ___tmp; })
	/** Mirrors an image vertically. Same remarks as oslMirrorImageH apply. */
	#define oslMirrorImageV(img)					({ float ___tmp;  ___tmp = (img)->offsetY0; (img)->offsetY0 = (img)->offsetY1; (img)->offsetY1 = ___tmp; })
#else
	#define oslSetImageTile(img,x0,y0,x1,y1)		{ (img)->offsetX0=(float)x0, (img)->offsetY0=(float)y0, (img)->offsetX1=(float)x1, (img)->offsetY1=(float)y1; (img)->stretchX = oslAbs((int)((float)((img)->offsetX1) - (float)((img)->offsetX0))), (img)->stretchY = oslAbs((int)((float)((img)->offsetY1) - (float)((img)->offsetY0))); }
	#define oslSetImageTileSize(img,x0,y0,x1,y1)	{ (img)->offsetX0=(float)(x0), (img)->offsetY0=(float)(y0), (img)->offsetX1=(float)(x0)+(float)(x1), (img)->offsetY1=(float)(y0)+(float)(y1), (img)->stretchX = (int)(x1), (img)->stretchY = (int)(y1); }
	#define oslResetImageTile(img)					{ (img)->offsetX0=0, (img)->offsetY0=0, (img)->offsetX1=(img)->sizeX, (img)->offsetY1=(img)->sizeY; (img)->stretchX = (img)->sizeX, (img)->stretchY = (img)->sizeY; }
	#define oslMirrorImageH(img)					{ float ___tmp;  ___tmp = (img)->offsetX0; (img)->offsetX0 = (img)->offsetX1; (img)->offsetX1 = ___tmp; }
	#define oslMirrorImageV(img)					{ float ___tmp;  ___tmp = (img)->offsetY0; (img)->offsetY0 = (img)->offsetY1; (img)->offsetY1 = ___tmp; }

#endif

/** Return true if the image was mirrored horizontally. */
#define oslImageIsMirroredH(img)				((img)->offsetX1 > (img)->offsetX0)
/** Return true if the image was mirrored vertically. */
#define oslImageIsMirroredV(img)				((img)->offsetY1 > (img)->offsetY0)


//Donne les coordonnées d'une image de manière à ce qu'avec un angle de 0 le haut-gauche de l'image se trouve à la la position x,y indiquée
/** Moves the image so that its top-left corner appears at the specified x and y coordinates when angle is 0, taking in account rotation parameters. */
#define oslImageRotMoveX(img,x)			((((x)+(img)->centerX*(img)->stretchX)/(img)->sizeX))
/** Same as oslImageRotMoveX but for the y coordinate. */
#define oslImageRotMoveY(img,y)			((((y)+(img)->centerY*(img)->stretchY)/(img)->sizeY))
/** Sets the rotation center (centerX, centerY properties) to the center of the image. Useful for rotation as it seems usually normal that the rotation center is the middle of the image in question. */
#define oslSetImageRotCenter(img)		((img)->centerX=(int)oslAbs((img)->offsetX1-(img)->offsetX0)>>1, (img)->centerY=(int)oslAbs((img)->offsetY1-(img)->offsetY0)>>1)
/** Alias for oslSetImageRotCenter. */
#define oslImageSetRotCenter			oslSetImageRotCenter


/** Awful hacky routine, which crops 0.5 pixel to each image corner.
This is useful if bilinear filtering is turned on and the image is stretched. In this case, by interpolation, the GPU may add a border to the image, which looks bad.
This routine will make sure that this border won't be displayed. */
#define oslCorrectImageHalfBorder(img)			((img)->offsetX0 = (img)->offsetX0 + 0.5f, (img)->offsetY0 = (img)->offsetY0 + 0.5f, (img)->offsetX1 = (img)->offsetX1 - 0.5f, (img)->offsetY1 = (img)->offsetY1 - 0.5f, img->stretchX--, img->stretchY--)
/** Undoes the effect of oslCorrectImageHalfBorder. Rather use oslResetImageTile, this one will mess your image up if you're calling it twice or if you call without having called oslCorrectImageHalfBorder before. */
#define oslResetImageHalfBorder(img)			((img)->offsetX0 = (img)->offsetX0 - 0.5f, (img)->offsetY0 = (img)->offsetY0 - 0.5f, (img)->offsetX1 = (img)->offsetX1 + 0.5f, (img)->offsetY1 = (img)->offsetY1 + 0.5f, img->stretchX++, img->stretchY++)

/** Returns the image width, taking in account the frame (tile). You can retrieve the full image width with image->sizeX. */
#define oslGetImageWidth(img)			((int)oslAbs((img)->offsetX1-(img)->offsetX0))
/** Returns the image height, taking in account the frame (tile). You can get the full image height with image->sizeY. */
#define oslGetImageHeight(img)			((int)oslAbs((img)->offsetY1-(img)->offsetY0))

#define oslGetImageSizeX				oslGetImageWidth
#define oslGetImageSizeY				oslGetImageHeight

extern OSL_IMAGE *oslCreateImageTile(OSL_IMAGE *img, int offsetX0, int offsetY0, int offsetX1, int offsetY1);
/** Same but you specify the width and height of the image part to be displayed instead of the box coordinates. */
extern OSL_IMAGE *oslCreateImageTileSize(OSL_IMAGE *img, int offsetX0, int offsetY0, int width, int height);

/** Converts an image to another pixel format (and places it to another location). The image may have moved, so you must not try to use the original image anymore but the returned image instead!
\code
image = oslConvertImageTo(image, OSL_IN_RAM, OSL_PF_5551);
\endcode
*/
extern OSL_IMAGE *oslConvertImageTo(OSL_IMAGE *imgOriginal, int newLocation, int newFormat);

/** Creates a copy of an image. The image data is copied as well, so the returned image is a completely new instance, and both are not linked together. */
extern OSL_IMAGE *oslCreateImageCopy(OSL_IMAGE *src, int newLocation);

/** Creates a copy of an image, just like oslCreateImageCopy, but new one will be swizzled. */
extern OSL_IMAGE *oslCreateSwizzledImage(OSL_IMAGE *src, int newLocation);

/** Copies an image to another (copies the image data). Both images must have the same format (width, height, pixelformat) else the copy will fail! */
extern void oslCopyImageTo(OSL_IMAGE *imgDst, OSL_IMAGE *imgSrc);

/** Swizzles an image. A swizzled image is then drawn a lot faster, but the problem is that you cannot modify it then because it gets a special format. However you can still unswizzle it, but it's slow if
you do it often.

Hint: You should always swizzle images stored in RAM. Use the OSL_SWIZZLED bit when loading them for more facility. */
extern void oslSwizzleImage(OSL_IMAGE *img);

/** Does the exact opposite of oslSwizzleImage. Call this after your image has been swizzled to restore its original state and make it accessible for raw reading and writing. */
extern void oslUnswizzleImage(OSL_IMAGE *img);


/** Swizzles imgSrc and writes the result to imgDst. Old and bad routine. Use oslSwizzleImage instead (swizzles a single image). */
extern void oslSwizzleImageTo(OSL_IMAGE *imgDst, OSL_IMAGE *imgSrc);

/** Moves an image to a new location, which can be either OSL_IN_RAM or OSL_IN_VRAM. */
extern bool oslMoveImageTo(OSL_IMAGE *img, int newLocation);

extern void oslClearImage(OSL_IMAGE *img, int color);				//A tester!!!

extern int oslWriteImageFile(OSL_IMAGE *img, const char* filename, int flags);
extern int oslWriteImageFilePNG(OSL_IMAGE *img, const char* filename, int flags);

/** Resets the properties of an image (position, image tile, angle, rotation center, stretching). */
extern void oslResetImageProperties(OSL_IMAGE *img);

/** Draws srcImg to dstImg with being scaled. */
extern void oslScaleImage(OSL_IMAGE *dstImg, OSL_IMAGE *srcImg, int newX, int newY, int newWidth, int newHeight);

/** Creates a scaled copy of an image. */
extern OSL_IMAGE *oslScaleImageCreate(OSL_IMAGE *img, short newLocation, int newWidth, int newHeight, short newPixelFormat);

/** Look at oslWriteImageFilePNG for more information. */
enum OSL_WRITE_FLAGS	{
	OSL_WRI_ALPHA = 1							//!< Writes the alpha channel of the image.
};

extern inline void oslSetImageFrameSize(OSL_IMAGE *img, u16 width, u16 height)			{
	img->frameSizeX = width, img->frameSizeY = height;
}

extern void oslSetImageFrame(OSL_IMAGE *img, int frame);

extern OSL_PALETTE *oslCreatePaletteEx(int size, int location, short pixelFormat);

/** Creates a palette. Simpler function without the \e location argument. */
extern inline OSL_PALETTE *oslCreatePalette(int size, short pixelFormat)		{
	return oslCreatePaletteEx(size, OSL_IN_RAM, pixelFormat);
}

/** Creates a palette from existing data. Please note that data is not copied to a new location but used as is! You just have to specify the palette size and pixelFormat. */
extern OSL_PALETTE *oslCreatePaletteFrom(void *data, int size, short pixelFormat);

/** Deletes an existing palette. If the palette was created with oslCreatePaletteFrom, the data is not freed or anything, it's left as it was before, only the OSL_PALETTE structure is freed. */
extern void oslDeletePalette(OSL_PALETTE *p);

/** Returns a color entry from a palette. The color will be in the same pixelformat as the palette (16 or 32 bits). */
extern int oslGetPaletteColor(OSL_PALETTE *p, int index);

/** Uncaches a palette. As with oslUncacheData, always uncache a palette after you've accessed it in a cached way (pal->data). Look at oslCreatePalette for more info. */
extern void oslUncachePalette(OSL_PALETTE *pal);

Note: this routine does not flush the associated image palette data! Call oslUncacheImage instead if you need it! */
extern inline void oslUncacheImageData(OSL_IMAGE *img)		{
    if (img != NULL)
        sceKernelDcacheWritebackInvalidateRange(img->data, img->totalSize);
}
/** Uncache a whole image, including its associated palette (image->palette). */
extern void oslUncacheImage(OSL_IMAGE *img);

extern int oslGetImagePixel(OSL_IMAGE *img, unsigned int x, unsigned int y);

extern void oslSetImagePixel(OSL_IMAGE *img, unsigned int x, unsigned int y, int pixelValue);

#define oslGetImageLine(img,y)			((char*)((img)->data) + (y)*(((img)->realSizeX * osl_pixelWidth[(img)->pixelFormat])>>3))
#define oslGetImagePixelAddr(img,x,y)	((char*)((img)->data) + ((((y)*(img)->realSizeX + (x)) * osl_pixelWidth[(img)->pixelFormat])>>3))

//For backward compatibility
#define oslGetImagePixelAdr				oslGetImagePixelAddr

/** Returns the address of a pixel, working even if the image is swizzled. This implementation is slower but works in every case. */
void *oslGetSwizzledPixelAddr(OSL_IMAGE *img, unsigned int x, unsigned int y);

/** Converts a color.
	\param pfDst
		Destination pixel format.
	\param pfSrc
		Source pixel format.
	\param color
		Color (in the source pixel format).
*/
extern int oslConvertColor(int pfDst, int pfSrc, int color);
/** Converts a color but using a palette if either the source or destination pixel format are paletted. See oslGetImagePixel for an example of use. */
extern int oslConvertColorEx(OSL_PALETTE *p, int pfDst, int pfSrc, int color);
extern void oslLockImage(OSL_IMAGE *img);
/** Unlock the image after you've finished with it. */
extern void oslUnlockImage(OSL_IMAGE *img);


/** List of pixel widths (in bits) for each pixel format. */
extern const int osl_pixelWidth[];
/** List of palette sizes (in powers of two). For non-paletted formats, it is zero. Else you can get the palette size by doing 1 << osl_paletteSizes[pixelFormat]. */
extern const u8 osl_paletteSizes[];

/** Returns the current drawbuffer as an OSL_IMAGE. You can save it to restore it later. */
#define oslGetDrawBuffer()			osl_curBuf

/** An image representing the primary buffer image, which is the buffer to which you are currently writing (see oslSwapBuffers for more information). */
#define OSL_DEFAULT_BUFFER			(&osl_defaultBufferImage)
/** An image representing the secondary buffer image, which is the buffer currently displayed to the user (see oslSwapBuffers for more information). In single buffering mode, OSL_DEFAULT_BUFFER is
identical to OSL_SECONDARY_BUFFER. */
#define OSL_SECONDARY_BUFFER		(&osl_secondaryBufferImage)

/** Returns the width of the current drawbuffer. On the default drawbuffer (i.e. the screen) it will be the resolution of the PSP LCD, that is 480 pixels. By taking these values in account you can make
game that automatically adapt to another resolution. */
#define OSL_SCREEN_WIDTH		(osl_curBuf->sizeX)
/** Returns the height of the current drawbuffer. On the default drawbuffer (i.e. the screen) it will be the resolution of the PSP LCD, that is 272 pixels. */
#define OSL_SCREEN_HEIGHT		(osl_curBuf->sizeY)

extern void oslSetDrawBuffer(OSL_IMAGE *img);
extern void oslSetAlphaWrite(int action, int value1, int value2);
extern void oslSetAlphaTest(int condition, int value);

/** Disables alpha testing. */
extern void oslDisableAlphaTest();

/** Holds whether alpha testing is currently enabled. */
extern int osl_alphaTestEnabled;

/** Available effects for #oslSetAlphaWrite. */
enum OSL_FX_ALPHAWRITE		{
	OSL_FXAW_NONE,								//!< Does not write alpha
	OSL_FXAW_SET,								//!< Sets alpha to value1 if the alpha channel of the pixel is not equal to value2.
};

/** Alpha test comparision operators. See #oslSetAlphaTest. */
enum OSL_FX_ALPHATEST		{
	OSL_FXAT_NEVER = GU_NEVER,
	OSL_FXAT_ALWAYS = GU_ALWAYS,
	OSL_FXAT_EQUAL = GU_EQUAL,
	OSL_FXAT_NOTEQUAL = GU_NOTEQUAL,
	OSL_FXAT_LESS = GU_LESS,
	OSL_FXAT_LEQUAL = GU_LEQUAL,
	OSL_FXAT_GREATER = GU_GREATER,
	OSL_FXAT_GEQUAL = GU_GEQUAL
};

/** Returns a nonzero value if the image is a copy of another, 0 if it's an original. */
#define oslImageIsCopy(img)						(img->flags & OSL_IMAGE_COPY)
/** Returns a nonzero value if the image is swizzled, 0 else. */
#define oslImageIsSwizzled(img)					(img->flags & OSL_IMAGE_SWIZZLED)
/** Returns a nonzero value if the image is swizzled, 0 else. */
#define oslImageGetAutoStrip(img)				(img->flags & OSL_IMAGE_AUTOSTRIP)

/** Defines if an image is a copy. For internal use only. */
extern inline void oslImageIsCopySet(OSL_IMAGE *img, bool enabled)			{
	if (enabled)
		img->flags |= OSL_IMAGE_COPY;
	else
		img->flags &= ~OSL_IMAGE_COPY;
}

/** Defines if an image is swizzled. For internal use only */
extern inline void oslImageIsSwizzledSet(OSL_IMAGE *img, bool enabled)			{
	if (enabled)
		img->flags |= OSL_IMAGE_SWIZZLED;
	else
		img->flags &= ~OSL_IMAGE_SWIZZLED;
}


/** Defines if an image should be automatically stripped (divided in stripes to be blitted faster if it's very big). You shouldn't care about this. */
extern inline void oslImageSetAutoStrip(OSL_IMAGE *img, bool enabled)			{
	if (enabled)
		img->flags |= OSL_IMAGE_AUTOSTRIP;
	else
		img->flags &= ~OSL_IMAGE_AUTOSTRIP;
}

#ifdef PSP
	/** Disables texturing (the image will be drawn opaque using vertex colors). */
	#define oslEnableTexturing()	({ if (!osl_textureEnabled)  sceGuEnable(GU_TEXTURE_2D), osl_textureEnabled = 1; })
	/** Enables texturing. You should not call this function by yourself, as oslSetTexture does it by itself. */
	#define oslDisableTexturing()	({ if (osl_textureEnabled)  sceGuDisable(GU_TEXTURE_2D), osl_textureEnabled = 0; })
#else
	/** Disables texturing (the image will be drawn opaque using vertex colors). */
	#define oslEnableTexturing()	{ if (!osl_textureEnabled)  sceGuEnable(GU_TEXTURE_2D), osl_textureEnabled = 1; }
	/** Enables texturing. You should not call this function by yourself, as oslSetTexture does it by itself. */
	#define oslDisableTexturing()	{ if (osl_textureEnabled)  sceGuDisable(GU_TEXTURE_2D), osl_textureEnabled = 0; }
#endif

/** Don't forget about stripping when you're drawing images by yourself, else it will be slower! The thing to know is: never draw an image wider than 64 pixels. If the image is, say, 256 pixels wide, you
can draw it in 4 stripes of 64 each (setting u, v coordinates to 0, 64, 128, 192, etc.). */
#define OSL_SLICE_SIZE 64

/** Don't use it! It's internally used by oslDrawImageSimple. Look at the source code for more information. */
extern int oslVerifyStripBlit(OSL_IMAGE *img);


/** Holds the current texture wrap state (see #oslSetTextureWrap). */
extern int osl_currentTexWrapU;
/** Same for the v state. */
extern int osl_currentTexWrapV;

/** Sets the behaviour of images when their bounds are reached. For example let's say you have a 128x128 image and you draw a 200x200 region. This is larger than the image itself and thus the part to the
left or the right will be either repeated or clamped depending on the parameter.
	\param u, v
		OSL_TW_CLAMP: Clamp (the same pixel is repeated indefinitely)
		OSL_TW_REPEAT: The image texture is tiled.
*/
extern inline void oslSetTextureWrap(int u, int v)		{
	sceGuTexWrap(u, v), osl_currentTexWrapU = u, osl_currentTexWrapV = v;
}

/** Available values for #oslSetTextureWrap. */
enum OSL_TEXWRAP_MODES		{
	OSL_TW_REPEAT = GU_REPEAT,					//!< Repeats the texture.
	OSL_TW_CLAMP = GU_CLAMP,					//!< Clamps the texture (the last image pixel is repeated indefinitely).
};



/** Defines the current texture, useful for low level image drawing. */
extern void oslSetTexture(OSL_IMAGE *img);
/** Same but also defines the beginning coordinate in the texture. Useful for tricks meant to display an image bigger than 512x512.
	\param img
		Texture to set
	\param x, y
		Beginning (top-left corner) of the image. Should be a multiple of 512. The (x, y) corner will become the (u, v) = (0, 0) coordinate when drawing a texture, and a 512x512 range (to the right and down)
		will be accessible.
*/
extern void oslSetTexturePart(OSL_IMAGE *img, int x, int y);

//Do NOT use this one
OSL_COLOR oslBlendColors(OSL_COLOR c1, OSL_COLOR c2);

/** Applies the alpha parameters to a color, tinting it. This is needed as alpha is not applied to vertex color but only to textures. */
extern inline OSL_COLOR oslBlendColor(OSL_COLOR c)		{
	return oslBlendColors(c, osl_currentAlphaCoeff);
}

/** System display list. */
extern unsigned int *osl_list;
/** Holds whether texturing is currently enabled. */
extern int osl_textureEnabled;

//Undocumented - avoid use of them
//Current texture, current palette. They are used to avoid setting texture and uploading a palette too much times (which is slow) if it's the same than before.
extern void *osl_curTexture, *osl_curPalette;
extern void *osl_curDrawBuf, *osl_curDispBuf;
extern OSL_IMAGE osl_defaultBufferImage, osl_secondaryBufferImage, *osl_curBuf;
extern int osl_isDrawingStarted;

/** Precise vertex with texture. Uses float coordinates. */
typedef struct
{
	float u, v;
	float x, y, z;
} OSL_PRECISE_VERTEX;

/** Fast vertex with texture. Uses 16-bit coordinates. */
typedef struct
{
	unsigned short u, v;
	short x, y, z;
} OSL_FAST_VERTEX;

/** Fast vertex with texture and 16-bit color. Uses 16-bit coordinates. */
typedef struct
{
	unsigned short u, v;
	unsigned long color;
	short x, y, z;
} OSL_FAST_VERTEX_COLOR32;

/** Untextured vertex. Uses 16-bit coordinates with 32-bit color. */
typedef struct
{
	unsigned long color;
	short x, y, z;
} OSL_LINE_VERTEX;

/** Untextured vertex. Uses 16-bit coordinates and 16-bit color. */
typedef struct
{
	unsigned long color;
	short x, y, z;
} OSL_LINE_VERTEX_COLOR32;


/** Precise texture vertex. Uses 16-bit coordinates XYZ and float UV. */
typedef struct
{
	float u, v;
	short x, y, z;
} OSL_UVFLOAT_VERTEX;

#ifdef __cplusplus
}
#endif

#endif

