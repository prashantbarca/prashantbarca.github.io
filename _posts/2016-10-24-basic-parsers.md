---
title: Chapter 1: Building the basic parser combinators

author:
  name: Prashant Anantharaman
  info: (@<a href="https://www.facebook.com/prashant.barca">Prashant Anantharaman</a>)
  
summary: We further dive into parser combinators, and go on build some basic parser combinators.
---

`This is a work in progress, please check again in a couple of days.`

In this post, we shall build some basic parsers to understand the functioning of parser combinators.

If you haven't installed the [hammer-parser ruby gem](https://rubygems.org/gems/hammer-parser), please go back to the previous post and install it first. 

- Fire your `irb` and include the hammer-parser gem.

```ruby
require 'hammer-parser'
```

### Basic hammer methods

- The hammer class `Hammer::Parser` has all the following methods that we need to make use of in our journey. We will see how the class is used in the individual examples below.

- `ch()` - This parser would be used to recognize a single character. For example, 

```ruby
@hammer = Hammer::Parser
parser = @hammer.ch('h')
```

The above parser 'parser' would be used to recognize the character 'h'. 

- `ch_change()` - This parser would be used to have characters in specific ranges. 

```ruby
@hammer = Hammer::Parser
parser = @hammer.ch_range('a','z')
```

The above parser would be used to recognize a single character in the range a-z. 

- `many()` - This parser would be used for 0 or more occurences of the parser included as an argument. 

```ruby
@hammer = Hammer::Parser
character = @hammer.ch_range('a','z')
parser = @hammer.many(character)
```

- `many1()` - Same as `many()` but includes 1 or more occurences instead of 0 or more.

- `end_p()`

- `sequence()`

- `token()`

- `optional()`

- `middle()`

- `choice()`

### Recognizing the input with the help of the parsers

We make use of the same parser as in the example of `many1()`.

```ruby
@hammer = Hammer::Parser
character = @hammer.ch_range('a','z')
parser = @hammer.many1(character)
if !parser.parse("abcd").nil?
   true
else
   false
end
```

If the input is recognized, then the `parse()` method would return an object of `HParseResult`. If the input is not recognized, then `nil` is returned.

