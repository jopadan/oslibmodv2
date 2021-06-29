#ifndef OSK_H
#define OSK_H

/** @defgroup OSK On-Screen Keyboard

	Functions to display Sony's On Screen Keyboard
	@{
*/
//<-- STAS: define the OSL_KEYBOARD structure and its methods for multithreaded environment

#ifdef PSP

typedef struct {
    SceUtilityOskParams oskParams;
//    SceUtilityOskData  *oskData;
} OSL_KEYBOARD;

#define OSL_OSK_RESULT_UNCHANGED	PSP_UTILITY_OSK_RESULT_UNCHANGED
#define OSL_OSK_RESULT_CANCELLED	PSP_UTILITY_OSK_RESULT_CANCELLED
#define OSL_OSK_RESULT_CHANGED		PSP_UTILITY_OSK_RESULT_CHANGED
#define OSL_OSK_CANCEL    		PSP_UTILITY_OSK_RESULT_CANCELLED
#define OSL_OSK_CHANGED    		PSP_UTILITY_OSK_RESULT_CHANGED
#define OSL_OSK_UNCHANGED    		PSP_UTILITY_OSK_RESULT_UNCHANGED

#else

typedef struct {
	int oskParams;	
} OSL_KEYBOARD;

enum OSL_OSK_RESULT {
	OSL_OSK_UNCHANGED        = 0,
	OSL_OSK_RESULT_UNCHANGED = 0,
	OSL_OSK_CANCEL           = 1,
	OSL_OSK_RESULT_CANCELLED = 1,
	OSL_OSK_RESULT_CHANGED   = 2,
	OSL_OSK_CHANGED          = 2,
};

#endif

extern OSL_KEYBOARD* osl_osk;

extern OSL_KEYBOARD* oslInitOskEx(int nData, int language);

extern int oslInitOskDataEx(OSL_KEYBOARD *kbd, int idx, unsigned short *desc,
                            unsigned short *intext, int textLimit, int linesNumber);

extern int oslActivateOskEx(OSL_KEYBOARD *kbd, int waitcycle);

extern int oslOskIsActiveEx(OSL_KEYBOARD *kbd);

extern void oslDeActivateOskEx(OSL_KEYBOARD *kbd);

extern int oslOskGetResultEx(OSL_KEYBOARD *kbd, int idx);

extern unsigned short* oslOskOutTextEx(OSL_KEYBOARD *kbd, int idx);

extern void oslEndOskEx(OSL_KEYBOARD *kbd);

void oslInitOsk(char *descStr, char *initialStr, int textLimit, int linesNumber, int language);

/** Draws the OSK
After drawing it you should check if the user closed it. Remember to call oslEndOsk.
\code
if (oslOskIsActive()){
    oslDrawOsk();
    if (oslGetOskStatus() == PSP_UTILITY_DIALOG_NONE){
        //The user closed the OSK
        oslEndOsk();
    }
}
\endcode
*/
void oslDrawOsk();

/** Checks if the OSK is active.
*/
int oslOskIsActive();

/**Returns the current OSK status
*/
int oslGetOskStatus();

/**Returns the OSK result (OSL_OSK_CHANGED, OSL_OSK_UNCHANGED or OSL_OSK_CANCEL)
*/
int oslOskGetResult();

/**Get the text inserted in the OSK
*/
void oslOskGetText(char *text);
void oslOskGetTextUCS2(unsigned short *text);

/**Ends the OSK
*/
void oslEndOsk();


/** @} */ // end of osk
#endif
