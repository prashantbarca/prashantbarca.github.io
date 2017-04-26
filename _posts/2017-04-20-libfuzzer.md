---
title: Chapter 2 - Testing the parser with libfuzzer

author:
  name: Prashant Anantharaman
  info: (@<a href="https://www.facebook.com/prashant.barca">Prashant Anantharaman</a>)
  
summary: We will be testing hammer parsers written in C with libfuzzer to expose common C stack overflows, buffer overflows, memory leaks, etc.
---

## Introduction

[libFuzzer](https://github.com/google/fuzzer-test-suite/blob/master/tutorial/libFuzzerTutorial.md) is a coverage guided fuzzing engine. In this tutorial we will see how to use libFuzzer with the Hammer parser-combinator toolkit.

Make sure you have hammer installed. You can install it using our [Hammer Installer](https://github.com/prashantbarca/hammer-installer).

## Setting up the environment

- This section is a mirror of the libFuzzer tutorial. You will find the instructions at [https://github.com/google/fuzzer-test-suite/blob/master/tutorial/libFuzzerTutorial.md](https://github.com/google/fuzzer-test-suite/blob/master/tutorial/libFuzzerTutorial.md).

- Install git
  ```shell
  sudo apt-get --yes install git
  ```
- Download the libfuzzer tutorial
  ```shell
  git clone https://github.com/google/fuzzer-test-suite.git FTS
  ```
  ```shell
   ./FTS/tutorial/install-deps.sh  # Get deps
  ```
  ```shell
  ./FTS/tutorial/install-clang.sh # Get fresh clang binaries
  ```
- Get libFuzzer sources and build it
  ```shell 
  svn co http://llvm.org/svn/llvm-project/llvm/trunk/lib/Fuzzer
  ```
  ```shell
  Fuzzer/build.sh
  ```

## Test the installation

- We now need to verify if the setup is right. We will make use of the test code given by the libFuzzer developers for this purpose.

   ```shell
   clang++ -g -fsanitize=address -fsanitize-coverage=trace-pc-guard FTS/tutorial/fuzz_me.cc libFuzzer.a
   ```
   ```shell
   ./a.out 2>&1 | grep ERROR
   ```

- If you see a "==ERROR: AddressSanitizer: heap-buffer-overflow on address.", your installation is valid.

## A simple hammer method

The input expected by this method is the word "FUZZ". We write a Hammer parser to validate the input. As per the requirements of libFuzzer, the method should take arguments of type (const uint8_t *Data, size_t DataSize). We can validate the size of the data expected (DataSize), as well as parse the *Data for compliance with the grammar in discussion.

We first write the method to process the input.

- Create a C file "test.cc"; and add the headers you need.

We add a method to process the data.

```c
void ProcessData(const uint8_t *Data, size_t DataSize)
 {       
   	   bool flag = DataSize == 4 &&
    	   Data[0] == 'F' &&
    	   Data[1] == 'U' &&
    	   Data[2] == 'Z' &&
    	   Data[3] == 'Z';  // :‑<
  	   printf("%d\n", flag);
 }
```

We now need to write a parser for this input. We first define an (HParser *) and set a parser combinator to it. We then need to parse "Data". The h_parse() method returns an HParseResult pointer, and we need to check if this pointer is null. A null return value means that the parsing was unsuccessful.

```c
void ValidateInput(const uint8_t *Data, size_t DataSize) 
  {
    HParser *parser = h_sequence(h_ch('F'),
    	    h_ch('U'),
            h_ch('Z'),
            h_ch('Z'),
            h_end_p(), NULL); # parse the word FUZZ
    const HParseResult *result;
    result = h_parse(parser, Data, 4); # result is nil if parse unsuccessful
    if(result)
    {
      ProcessData(Data, DataSize);
    }
  }
```

We now use the code below set the target method for the LLVMFuzzer to target. We set the target as the ValidateInput() method we just defined.

```c
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  ValidateInput(Data, Size);
  return 0;
}
```

# Compiling and Running

- Compiling a file called "test.cc"
```sh clang++ -o test -lhammer -g -fsanitize=address -fsanitize-coverage=trace-pc-guard test.cc libFuzzer.a```

- Running: Simply execute the executable generated. It would run the fuzzer and provide potential pitfalls.
```sh ./test```

