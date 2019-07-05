# qcc

A simple compiler that takes a small custom query language and generates SQL to work with a database employing tags using a [Toxi](http://howto.philippkeller.com/2005/04/24/Tags-Database-schemas/)-style approach.

## Installation & Usage
After cloning and ensuring you're in the right directory:

```
$ make
$ qcc <file with your query>
```

The resulting SQL will be printed to `stdout`.

## Query Language
The language is designed to be simple and intuitive. Keywords are `or`, `and`, and `not`, and expressions can be delineated with parentheses `()`. Like many other programming languages, `not` has higher precedence than `and`, which has higher precedence than `or`. String identifiers are assumed to be valid tags, and `--` is used to begin single-line comments.

## Examples
```
not reggae or hip-hop and (blues or country) and jazz
```

```
-- comment
(P and Q) or not not R and (S and not (T or P))
```
