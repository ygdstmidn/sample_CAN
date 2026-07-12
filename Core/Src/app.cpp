// main code here!!

#include <main.h>
#include <usart.h>
#include <ukaikokko/ukaikokko.h>
#include <stdio.h>

ukaikokko::InterruptBufferedUART<256, 1024, 1024> pc(&huart2);
ukaikokko::GPOutput led(DebugLED_GPIO_Port, DebugLED_Pin);

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

        pc.begin();

        led.write(0);
        setupDone = true;
    }

    void user_loop(void)
    {
        const uint32_t now = HAL_GetTick();
        static uint32_t pre = now;

        if (now - pre >= 10)
        {
            static int count = 0;
            count++;
            if (count >= 100)
            {
                led.toggle();
                printf(">now:%lu\r\n", now);
                count = 0;
            }

            while (pc.available() > 0)
            {
                uint8_t data = static_cast<uint8_t>(pc.read());
                putchar(data);
                fflush(NULL);
            }

            pc.periodic();

            pre = now;
        }
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
