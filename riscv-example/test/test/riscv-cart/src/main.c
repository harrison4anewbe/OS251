#include <stdint.h>

volatile int global = 42;
volatile uint32_t controller_status = 0;

uint32_t getTicks(void);
uint32_t getStatus(void);
uint32_t getMode(void);

// #define PALETTE (*((volatile uint32_t *)0x500FC000))
// #define background (*((volatile uint32_t *)0x50000000))
// #define backgroundcontrol (*((volatile uint32_t *)0x500FF100))

volatile uint32_t *SPRITE_PALETTE_0 = (volatile uint32_t *)(0x500FD000);
volatile char *VIDEO_MEMORY = (volatile char *)(0x50000000 + 0xFE800);

int main()
{
    int a = 4;
    int b = 12;
    int last_global = 42;
    int x_pos = 12;

    VIDEO_MEMORY[0] = 'H';
    VIDEO_MEMORY[1] = 'e';
    VIDEO_MEMORY[2] = 'l';
    VIDEO_MEMORY[3] = 'l';
    VIDEO_MEMORY[4] = 'o';
    VIDEO_MEMORY[5] = ' ';
    VIDEO_MEMORY[6] = 'W';
    VIDEO_MEMORY[7] = 'o';
    VIDEO_MEMORY[8] = 'r';
    VIDEO_MEMORY[9] = 'l';
    VIDEO_MEMORY[10] = 'd';
    VIDEO_MEMORY[11] = '!';
    VIDEO_MEMORY[12] = 'X';
    int cnt = 0;
    while (1)
    {
        global = getTicks();
        if (global != last_global)
        {
            controller_status = getStatus();
            if (controller_status)
            {
                int tmp;
                tmp = getMode();
                // Palette
                if (cnt % 2 == 0)
                {
                    for (int i = 0; i < 256; i++)
                    {
                        SPRITE_PALETTE_0[i] = 0xff000000 + i;
                    }

                    // Sprite Control
                    // ctr_bits = 0001 1111 1110 0001 0000 0000 0100 0000
                    (*((volatile uint32_t *)0x500FF214 + 0)) = 0x1fc10040;

                    // Sprite Memory Data
                    for (int sp_index = 0; sp_index < 128; sp_index++)
                    {
                        volatile char *SM_SPRITE_MEMORY_i = (volatile uint8_t *)(0x500F4000 + sp_index * 0x100);
                        for (int j = 0; j < 256; j++)
                        {
                            SM_SPRITE_MEMORY_i[j] = 255;
                        }
                    }
                }
                else
                {
                    if (tmp)
                    {
                        VIDEO_MEMORY[0] = '1';
                    }
                    VIDEO_MEMORY[1] = 'e';
                    VIDEO_MEMORY[2] = 'l';
                    VIDEO_MEMORY[3] = 'l';
                    VIDEO_MEMORY[4] = 'o';
                    VIDEO_MEMORY[5] = ' ';
                    VIDEO_MEMORY[6] = 'W';
                    VIDEO_MEMORY[7] = 'o';
                    VIDEO_MEMORY[8] = 'r';
                    VIDEO_MEMORY[9] = 'l';
                    VIDEO_MEMORY[10] = 'd';
                    VIDEO_MEMORY[11] = '!';
                    VIDEO_MEMORY[12] = 'X';
                }
                cnt += 1;
            }
            last_global = global;
        }
    }
    return 0;
}
