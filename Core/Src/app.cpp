// main code here!!

#include <main.h>
#include <usart.h>
#include <can.h>
#include <ukaikokko/ukaikokko.h>
#include <stdio.h>

ukaikokko::InterruptBufferedUART<256, 1024, 1024> pc(&huart2);
ukaikokko::GPOutput led(DebugLED_GPIO_Port, DebugLED_Pin);
ukaikokko::BufferedCAN<256, 1024, 1024> can(&hcan1);

static bool setupDone = false;

#ifdef __cplusplus
extern "C"
{
#endif

    void user_setup(void)
    {
        led.write(1);
        printf("sample_CAN\r\n");
        printf(__DATE__ "\r\n");
        printf(__TIME__ "\r\n");

        setbuf(stdout, NULL);
        pc.begin();
        {
            CAN_FilterTypeDef filter;
            filter.FilterIdHigh = 0x0000;
            filter.FilterIdLow = 0x0000;
            filter.FilterMaskIdHigh = 0x0000;
            filter.FilterMaskIdLow = 0x0000;
            filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
            filter.FilterBank = 0;
            filter.FilterMode = CAN_FILTERMODE_IDMASK;
            filter.FilterScale = CAN_FILTERSCALE_32BIT;
            filter.FilterActivation = ENABLE;
            filter.SlaveStartFilterBank = 14; // meaningless for single CAN instance
            can.configFilter(&filter);
        }
        can.begin();

        led.write(0);
        setupDone = true;
    }

    void user_loop(void)
    {
        const uint32_t now = HAL_GetTick();
        static uint32_t pre = now;

        if (now - pre >= 10)
        {
            while (pc.available() > 0)
            {
                const uint8_t data = static_cast<uint8_t>(pc.read());
                ukaikokko::CANMessage msg;
                msg.ide = CAN_ID_STD;
                msg.id = 0x123;
                msg.dlc = 1;
                msg.data[0] = data;
                can.write(&msg);
            }

            ukaikokko::CANMessage msg;
            while (can.read(&msg))
            {
                if (msg.ide == CAN_ID_STD && msg.id == 0x124 && msg.dlc == 1)
                {
                    putchar(msg.data[0]);
                }
            }

            can.periodic();
            pc.periodic();

            pre = now;
        }
        can.TxCplt(&hcan1);
        can.RxCplt(&hcan1, CAN_RX_FIFO0);
    }

    int _write(int file, char* ptr, int len)
    {
        if (!setupDone)
        {
            HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, 10); // ブロッキング
            return len;
        }
        else
        {
            pc.write((uint8_t*)ptr, len);
            return len;
        }
    }

    void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
    {
        pc.RxCplt(huart);
    }

    void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
    {
        pc.TxCplt(huart);
    }

#ifdef __cplusplus
}
#endif
