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

#define  GRAPHDISP                        1
#define  GRAPHDISP_CANVAS                 2       /* control type: canvas, callback function: CANVAS_CB */
#define  GRAPHDISP_GRAPH2                 3       /* control type: graph, callback function: (none) */
#define  GRAPHDISP_GRAPH1_4               4       /* control type: graph, callback function: (none) */
#define  GRAPHDISP_GRAPH1_3               5       /* control type: graph, callback function: (none) */
#define  GRAPHDISP_GRAPH1_2               6       /* control type: graph, callback function: (none) */
#define  GRAPHDISP_GRAPH1                 7       /* control type: graph, callback function: (none) */
#define  GRAPHDISP_PICTURE                8       /* control type: picture, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK CANVAS_CB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
