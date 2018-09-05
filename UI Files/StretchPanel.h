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
#define  STRETCH_TABLE                    2       /* control type: table, callback function: (none) */
#define  STRETCH_TEXTMSG_11               3       /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG_12               4       /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG_13               5       /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG_15               6       /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG_10               7       /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG_9                8       /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG_16               9       /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG_8                10      /* control type: textMsg, callback function: (none) */
#define  STRETCH_TEXTMSG                  11      /* control type: textMsg, callback function: (none) */
#define  STRETCH_DELETE                   12      /* control type: textMsg, callback function: DeleteCallback */
#define  STRETCH_INSBLW                   13      /* control type: textMsg, callback function: InsblwCallback */
#define  STRETCH_PICTURE_5                14      /* control type: picture, callback function: InsabvCallback */
#define  STRETCH_TEXTMSG_14               15      /* control type: textMsg, callback function: (none) */
#define  STRETCH_INSABV                   16      /* control type: textMsg, callback function: InsabvCallback */
#define  STRETCH_NUMERIC_3                17      /* control type: numeric, callback function: (none) */
#define  STRETCH_NUMERIC_2                18      /* control type: numeric, callback function: (none) */
#define  STRETCH_PICTURE_6                19      /* control type: picture, callback function: (none) */
#define  STRETCH_PICTURE_4                20      /* control type: picture, callback function: InsblwCallback */
#define  STRETCH_NUMERIC                  21      /* control type: numeric, callback function: (none) */
#define  STRETCH_PICTURE_3                22      /* control type: picture, callback function: DeleteCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK DeleteCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK InsabvCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK InsblwCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
