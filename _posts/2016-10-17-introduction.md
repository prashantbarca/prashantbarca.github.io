---
title: Introduction to LangSec and Installing Hammer with Ruby bindings

author:
  name: Prashant Anantharaman
  info: (@<a href="https://www.facebook.com/prashant.barca">Prashant Anantharaman</a>)
  
summary: An introduction to LangSec, parser combinators and a step by step installation guide to the hammer library and the `hammer-parser` ruby gem.
---

Language-theoretic security (LangSec) is a way of writing parsers that make them easier to audit, and enforces the validation of the input that is being received before doing any computation is performed on the input. We first fully recognize the input, and make sure it conforms with our specification. If not, we simply reject the input. The computation is completely separated from the input recognition phase.

Parser combinator libraries make it easier to write parsers, by specifying smaller parsers, and combining them later on to build the complete parser. We first decide on the language that has to be accepted by a particular protocol, which could be a regular expression, a context-free grammar, a context-sensitive grammar or a turing machine. Regular expressions and context-free grammars are easy to write and easy to enforce. Whereas the latter two are really hard to enforce.

We make use of the parser combinator library, [Hammer](https://github.com/UpstandingHackers/hammer). The hammer ruby library, which is available at [Hammer Ruby Library](https://rubygems.org/gems/hammer-parser) depends on `libhammer`.


### Installing hammer ruby bindings

- Installing libhammer. We first clone the hammer code from github, and then go in the folder.

`$ git clone https://github.com/UpstandingHackers/hammer`

`$ cd hammer`

- We use scons to build it.

`$ scons bindings=ruby`  

`$ sudo scons bindings=ruby install`

- On linux you will also have to `sudo ldconfig`.

This will install hammer to `/usr/local`.

- You can find the gem on rubygems at [Hammer Parser Rubygems](https://rubygems.org/gems/hammer-parser). You can install it by, 

`gem install hammer-parser -v 0.2.0`

- In order to make sure that the gem installed correctly, let us fire up our `irb`, and then try to include the `hammer-parser` gem. 

`$ irb` 

```ruby
 > require 'hammer-parser'
 => true 
```

Thanks for reading the first part of the LangSec Ruby tutorial series. In the next post, we shall look at building basic regular expressions using the hammer-parser library.
