---
title: Introduction and Installation

author:
  name: Prashant Anantharaman
  info: (@<a href="https://www.facebook.com/prashant.barca">Prashant Anantharaman</a>)
  
summary: Introduction to Hammer, LangSec and Installation
---

Language-theoretic security (LangSec) is a way of writing parsers that make them easier to audit, and enforces the validation of the input that is being received before doing any computation is performed on the input. We first fully recognize the input, and make sure it conforms with our specification. If not, we simply reject the input. The computation is completely separated from the input recognition phase.

Parser combinator libraries make it easier to write parsers, by specifying smaller parsers, and combining them later on to build the complete parser. We first decide on the language that has to be accepted by a particular protocol, which could be a regular expression, a context-free grammar, a context-sensitive grammar or a turing machine. Regular expressions and context-free grammars are easy to write and easy to enforce. Whereas the latter two are really hard to enforce.

We make use of the parser combinator library, [Hammer](https://github.com/UpstandingHackers/hammer). The hammer ruby library, which is available at [Hammer Ruby Library](https://rubygems.org/gems/hammer-parser) depends on `libhammer`.
