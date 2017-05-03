---
title: Chapter 2 - Testing the parser with libfuzzer

author:
  name: Prashant Anantharaman
  info: (@<a href="https://www.facebook.com/prashant.barca">Prashant Anantharaman</a>)
  
summary: We will be testing hammer parsers written in C with libfuzzer to expose common C stack overflows, buffer overflows, memory leaks, etc.
---

## Introduction

The goal of this tutorial is to provide a primer to fuzz-test parsers written in hammer. In order to go about this, we will look at 2 simple cpp files; one simply meant to test libfuzzer, and another with a hammer parser.

The LangSec philosophy is to completely recognize all input to conform to a formal language before performing any processing of the input. In order to achieve this, for an input, we define a parser to make sure the input conforms to the language.

<img src="/pattern.png" style="width:20%;"/>

[libFuzzer](https://github.com/google/fuzzer-test-suite/blob/master/tutorial/libFuzzerTutorial.md) is a coverage guided fuzzing engine. In this tutorial we will see how to use libFuzzer with the Hammer parser-combinator toolkit.

## Setting up the environment

- Make sure you have hammer installed. You can install it using our [Hammer Installer](https://github.com/prashantbarca/hammer-installer).

- Follow the instructions to set up and test the environment for libfuzzer at [https://github.com/google/fuzzer-test-suite/blob/master/tutorial/libFuzzerTutorial.md](https://github.com/google/fuzzer-test-suite/blob/master/tutorial/libFuzzerTutorial.md).

## Why Hammer

Download our sample CPP programs -- [fuzz_me.cc](/fuzz_me.cc) and [fuzz_me_with_hammer.cc](/fuzz_me_with_hammer.cc).

In the _fuzz_me.cc_ file, you should see the method below. As you may have noticed, there is a buffer overflow here and this is caught when we compile and run it.

```c
void ProcessData(const uint8_t *Data, size_t DataSize)
 {       
      return DataSize >= 3 &&
      Data[0] == 'F' &&
      Data[1] == 'U' &&
      Data[2] == 'Z' &&
      Data[3] == 'Z';
 }
```

We run the following commands to compile and run _fuzz_me.cc_.

```shell
clang++ -g -lhammer -fsanitize=address -fsanitize-coverage=trace-pc-guard fuzz_me.cc libFuzzer.a
./a.out -detect_leaks=0
```

Let us now look at the _fuzz_test_with_hammer.cc_. In this file, we want to make sure that we recognize the input fully before performing any processing. In order to do this, we write a simple hammer parser to recognize the input that is expected by this particular program.

```c
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
```

In the above method, the h_parse() method returns a _null_ if parsing was unsuccessful.

When we run the cpp file _fuzz_me_with_hammer.cc_, we see that nothing interesting happers here when we included a hammer parser to recognize the input strictly before any processing.

## Related Links

- [http://langsec.org/](http://langsec.org/).
- [Hammer Primer](https://github.com/sergeybratus/HammerPrimer).