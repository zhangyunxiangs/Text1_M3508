#ifndef TEXT1_M3508_MOTOR_CAN_H
#define TEXT1_M3508_MOTOR_CAN_H

#include <stdint.h>

//电机编号枚举
typedef enum {
    //can1
    motor_can_1_all = 0x200,
    motor_1 = 0x201,
    motor_2 = 0x202,
    motor_3 = 0x203,
    motor_4 = 0x204,

    // //can2
    // motor_can_2_all = 0x1FF,
    // motor_5 = 0x205,
    // motor_6 = 0x206,
    // motor_7 = 0x207,
    // motor_8 = 0x208,
  } motor_message_id;


//C620回复报文数据结构体
typedef struct {

    uint16_t ecd;             //电机角度
    int16_t speed_rpm;        //电机速度
    int16_t given_current;    //电机电流
    uint8_t temperate;        //电机温度
    uint16_t last_ecd;        //上一次电机角度

}motor_receive_message;

//函数声明

void Get_Motor_Can_Message(motor_receive_message *ptr, const uint8_t *data);
void CAN_cmd_can_1(int16_t motor_1_speed, int16_t motor_2_speed, int16_t motor_3_speed, int16_t motor_4_speed);

extern void can_filter_init(void);

#endif //TEXT1_M3508_MOTOR_CAN_H