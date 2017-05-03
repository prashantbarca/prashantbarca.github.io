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

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  ProcessData(Data, Size);
  return 0;
}
