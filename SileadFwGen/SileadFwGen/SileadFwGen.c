// generate Silead touch controller gsl1680.fw firmware binfile for Linux given header file
// (c) Artem Moroz, 2023 artem.moroz@gmail.com

#include <stdio.h>
#include <stdint.h>

#define code
#include "gslX680_311_5_F.h"

int main()
{
    FILE* fp = fopen("gsl1680.fw", "wb");
    if (fp)
    {
        for (int i = 0; i < sizeof(GSLX680_FW) / sizeof(struct fw_data); i++)
        {
            const struct fw_data* pdata = &GSLX680_FW[i];
            printf("%08X - %08X\n", pdata->offset, pdata->val);

            uint32_t wOffset = pdata->offset;
            uint32_t wData = pdata->val;

            fwrite(&wOffset, 1, 4, fp);
            fwrite(&wData, 1, 4, fp);
        }

        printf("done!\n");

        fclose(fp);
    }
   
}
