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

#define  EXP_LIST                         1
#define  EXP_LIST_EXPLIST                 2       /* control type: tree, callback function: ExpListCallback */
#define  EXP_LIST_STRAINLIST              3       /* control type: tree, callback function: StrainListCallback */
#define  EXP_LIST_TEXTMSG                 4       /* control type: textMsg, callback function: (none) */
#define  EXP_LIST_TEXTMSG_2               5       /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ExpListCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StrainListCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
