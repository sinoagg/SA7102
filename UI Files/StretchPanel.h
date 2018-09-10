/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  STRETCH                          1
#define  STRETCH_LOADTABLE                2       /* control type: table, callback function: (none) */
#define  STRETCH_STRAINTABLE              3       /* control type: table, callback function: (none) */
#define  STRETCH_TEXTMSG_11               4       /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG_12               5       /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG_13               6       /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG_15               7       /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG_10               8       /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG_9                9       /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG_16               10      /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG_8                11      /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG                  12      /* control type: textMsg, callback function: (none) */
#define  STRETCH_DELETE                   13      /* control type: textMsg, callback function: DeleteCallback */
#define  STRETCH_INSBLW                   14      /* control type: textMsg, callback function: InsblwCallback */
#define  STRETCH_PICTURE_5                15      /* control type: picture, callback function: InsabvCallback */
#define  STRETCH_TEXTMSG_14               16      /* control type: textMsg, callback function: (none) */
#define  STRETCH_INSABV                   17      /* control type: textMsg, callback function: InsabvCallback */
#define  STRETCH_NUMERIC_3                18      /* control type: numeric, callback function: (none) */
#define  STRETCH_NUMERIC_2                19      /* control type: numeric, callback function: (none) */
#define  STRETCH_PICTURE_6                20      /* control type: picture, callback function: (none) */
#define  STRETCH_PICTURE_4                21      /* control type: picture, callback function: InsblwCallback */
#define  STRETCH_NUMERIC                  22      /* control type: numeric, callback function: (none) */
#define  STRETCH_PICTURE_3                23      /* control type: picture, callback function: DeleteCallback */
#define  STRETCH_MODE                     24      /* control type: textMsg, callback function: ModeCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK DeleteCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK InsabvCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK InsblwCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ModeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
