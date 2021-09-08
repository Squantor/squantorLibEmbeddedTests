/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2021 Bart Bilos
 * For conditions of distribution and use, see LICENSE file
 */

#include <datastream.h>
#include <string.h>
#include <queue.h>

#define MOCKDSCHARBUFSIZE   128

result mockDsCharWrite(const char *c);
result mockDsCharRead(char *c);

const char testDsCharName[] = "char stream";
datastreamChar_t testDsChar = 
{
    mockDsCharWrite,
    mockDsCharRead,
    testDsCharName,
};

// data queue written by the DUT
char dsCharWriteBuf[MOCKDSCHARBUFSIZE];
queueChar_t writeQueue = {MOCKDSCHARBUFSIZE, 0, 0, dsCharWriteBuf};
// data queue read by the DUT
char dsCharReadBuf[MOCKDSCHARBUFSIZE];
queueChar_t readQueue = {MOCKDSCHARBUFSIZE, 0, 0, dsCharReadBuf};

void mockDsCharReset()
{
    memset(dsCharWriteBuf, 0, sizeof(dsCharWriteBuf));
    memset(dsCharReadBuf, 0, sizeof(dsCharReadBuf));
    queueInit(&writeQueue);
    queueInit(&readQueue);
}

result mockDsPutReads(char *buf, size_t size)
{
    for(size_t i = 0; i < size; i++)
    {
        result r = queueEnqueue(&readQueue, buf[i]);
        if(r != noError)
            return r;
    }
    return noError;
}

result mockDsPutReadsString(char *buf)
{
    size_t strSize = strlen(buf);
    return mockDsPutReads(buf, strSize);
}

result mockDsGetWrites(char *buf, size_t size)
{
    for(size_t i = 0; i < size; i++)
    {
        result r = queueDequeue(&writeQueue, &buf[i]);
        if(r != noError)
            return r;
    }
    return noError;
}

result mockDsGetWriteStatus(void)
{
    return queueState(&writeQueue);
}


result mockDsCharWrite(const char *c)
{
    result r = queueEnqueue(&writeQueue, *c);
    if(r == queueFull)
        return streamFull;
    else if(r == noError)
        return noError;
    else
        return r;
}

result mockDsCharRead(char *c)
{
    result r = queueDequeue(&readQueue, c);
    if(r == queueEmpty)
        return streamEmtpy;
    else if(r == noError)
        return noError;
    else
        return r;
}