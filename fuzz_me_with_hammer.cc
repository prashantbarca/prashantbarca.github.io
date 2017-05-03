#include <stdint.h>
#include <stddef.h>
#include <hammer/hammer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const HParser* document = NULL;

void ProcessData(const uint8_t *Data, size_t DataSize)
{       
 bool result = DataSize >= 3 && Data[0] == 'F' &&
        Data[1] == 'U' &&
        Data[2] == 'Z' &&
        Data[3] == 'Z';  // :‑<
}

void ValidateInput(const uint8_t *Data, size_t DataSize) 
{
    HParser *parser = h_sequence(h_ch('F'),
            h_ch('U'),
            h_ch('Z'),
            h_ch('Z'),
            h_end_p(), NULL);
    const HParseResult *result;
    result = h_parse(parser, Data, 4); 
    if(result)
    {
        ProcessData(Data, DataSize);
    }
}


extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    ValidateInput(Data, Size);
    return 0;
}
