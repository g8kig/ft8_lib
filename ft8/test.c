
#include <stdio.h>
#include <stdlib.h>

#ifndef _countof
#define _countof(arr) (sizeof(arr) / sizeof((arr)[0])
#endif

#include "pack.h"
#include "unpack.h"

static int test1()
{
    const char* inputs[] = {
        "",
        " ",
        "ABC",
        "ABC/P",
        "A9",
        "A9/P",
        "L9A",
        "L9A/P",
        "L7BC",
        "L7BC/P",
        "L0ABC",
        "L0ABC/P",
        "LL3JG",
        "LL3JG/P",
        "LL3AJG",
        "LL3AJG/P",
        "CQ ",
        "QRP ",
        "DX ",
        0
    };

    for (int i = 0; inputs[i]; ++i)
    {
        int32_t result = pack28(inputs[i]);
        printf("pack28(\"%s\") = %d\n", inputs[i], result);
    }
    return 1;
}

static int test2()
{
    const char* inputs[] = {
        "CQ LL3JG",
        "CQ LL3JG KO26",
        "CQ QRP LL3JG KO26",
        "CQ DX LL3JG KO26",
        "CQ POTA LL3JG KO26",
        "CQ SOTA LL3JG KO26",

        "CQ LL3JG/P",
        "CQ LL3JG/P KO26",
        "CQ QRP LL3JG/P KO26",
        "CQ DX LL3JG/P KO26",
        "CQ POTA LL3JG/P KO26",
        "CQ SOTA LL3JG/P KO26",

        "L0UAA LL3JG KO26",
        "L0UAA LL3JG +02",
        "L0UAA LL3JG RRR",
        "L0UAA LL3JG 73",
        "L0UAA LL3JG RR",
        "L0UAA LL3JG RR73",

        "GW8KIG GM8KIG KO26",
        "GW8KIG GM8KIG +02",
        "GW8KIG GM8KIG RRR",
        "GW8KIG GM8KIG 73",
        "GW8KIG GM8KIG RR",
        "GW8KIG GM8KIG RR73",

        "L0UAA/P LL3JG KO26",
        "L0UAA/P LL3JG +02",
        "L0UAA/P LL3JG RRR",
        "L0UAA/P LL3JG 73",
        "L0UAA/P LL3JG RR",
        "L0UAA/P LL3JG RR73",

        "L0UAA LL3JG/P KO26",
        "L0UAA LL3JG/P +02",
        "L0UAA LL3JG/P RRR",
        "L0UAA LL3JG/P 73",
        "L0UAA LL3JG/P RR",
        "L0UAA LL3JG/P RR73",

        "GW8KIG/P GM8KIG/P KO26",
        "GW8KIG/P GM8KIG/P +02",
        "GW8KIG/P GM8KIG/P RRR",
        "GW8KIG/P GM8KIG/P 73",
        "GW8KIG/P GM8KIG/P RR",
        "GW8KIG/P GM8KIG/P RR73",
        "G8QRP G8QRP 73",
        0
    };

    for (int i = 0; inputs[i]; ++i)
    {
        uint8_t result[10];
        int j;
        char output[64];
        int rc = pack77_1(inputs[i], result);
        printf("pack77_1(\"%s\") -> [", inputs[i]);
        for (j = 0; j < _countof(result) - 1; ++j)
        {
            printf("%02x ", result[j]);
        }
        printf("%02x] = %d \n", result[j], rc);
        if (rc != -1)
        {
            rc = unpack77(result, output);
            printf("unpack77() -> \"%s\" = %d\n", output, rc);
        }
        else
        {
            printf("Error\n");
        }
    }

    return 1;
}

static int test3()
{
    return 1;
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}
