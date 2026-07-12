// main code here!!

#include <main.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void user_setup(void)
    {
    }

    void user_loop(void)
    {
        const uint32_t now = HAL_GetTick();
        static uint32_t pre = now;

        if (now - pre >= 10)
        {
            pre = now;
        }
    }

#ifdef __cplusplus
}
#endif
