//包含对应头文件
#include "Motor_Can.h"
#include <stdint.h>

#include "can.h"
#include "stm32f4xx_hal.h"


//接收电调回复报文

//结构体数组：将电调发送回来的数据进行拆分
static motor_receive_message receive_message[8];

//电调回复报文拆分
void Get_Motor_Can_Message(motor_receive_message *ptr, const uint8_t *data)
{
    ptr->last_ecd = ptr-> ecd;
    ptr->ecd = (uint16_t)((data[0] << 8) | data[1]);
    ptr->speed_rpm = (int16_t)((data[2] << 8) | data[3]);
    ptr->given_current = (int16_t)((data[4] << 8) | data[5]);
    ptr->temperate = data[6];
}

//CAN接收回调函数
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];

    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);

    switch (rx_header.StdId)
    {
        case motor_1:
        case motor_2:
        case motor_3:
        case motor_4:
        {
            static uint8_t i = 0;
            i = rx_header.StdId - motor_1;
            Get_Motor_Can_Message(&receive_message[i], rx_data);
            break;
        }

        default:
        {
            break;
        }
    }
}


//发送电调接收报文

//发送数据数组定义：can1
static  uint8_t motor_send_can_1[8] = {0};
static CAN_TxHeaderTypeDef  can_1_tx_message;

void CAN_cmd_can_1(int16_t motor_1_speed, int16_t motor_2_speed, int16_t motor_3_speed, int16_t motor_4_speed )
{
    uint32_t send_mail_box;
    can_1_tx_message.StdId = motor_can_1_all;
    can_1_tx_message.IDE = CAN_ID_STD;
    can_1_tx_message.RTR = CAN_RTR_DATA;
    can_1_tx_message.DLC = 0x08;
    motor_send_can_1[0] = (motor_1_speed >> 8);
    motor_send_can_1[1] = motor_1_speed;
    motor_send_can_1[2] = (motor_2_speed >> 8);
    motor_send_can_1[3] = motor_2_speed;
    motor_send_can_1[4] = (motor_3_speed >> 8);
    motor_send_can_1[5] = motor_3_speed;
    motor_send_can_1[6] = (motor_4_speed >> 8);
    motor_send_can_1[7] = motor_4_speed;
    HAL_CAN_AddTxMessage(&hcan1, &can_1_tx_message, motor_send_can_1, &send_mail_box);
}




extern CAN_HandleTypeDef hcan2;

void can_filter_init(void)
{
    CAN_FilterTypeDef can_filter_st;
    can_filter_st.FilterActivation = ENABLE;
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter_st.FilterIdHigh = 0x0000;
    can_filter_st.FilterIdLow = 0x0000;
    can_filter_st.FilterMaskIdHigh = 0x0000;
    can_filter_st.FilterMaskIdLow = 0x0000;
    can_filter_st.FilterBank = 0;
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;

    if (HAL_CAN_ConfigFilter(&hcan1, &can_filter_st) != HAL_OK) {
        Error_Handler();
    }

    if (HAL_CAN_Start(&hcan1) != HAL_OK) {
        Error_Handler();
    }

    if (HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
        Error_Handler();
    }
}
