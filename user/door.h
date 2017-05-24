#ifndef _DOOR_H_
#define _DOOR_H_



#define OUTPUT1_IO_MUX     PERIPHS_IO_MUX_GPIO4_U
#define OUTPUT1_IO_NUM     4
#define OUTPUT1_IO_FUNC    FUNC_GPIO4

#define OUTPUT2_IO_MUX     PERIPHS_IO_MUX_GPIO5_U
#define OUTPUT2_IO_NUM     5
#define OUTPUT2_IO_FUNC    FUNC_GPIO5

#define OUTPUT3_IO_MUX     PERIPHS_IO_MUX_MTMS_U
#define OUTPUT3_IO_NUM     14
#define OUTPUT3_IO_FUNC    FUNC_GPIO14

void openBuildingDoor(void);

#endif