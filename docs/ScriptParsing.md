# Code parsing, compilation and assembling process

Example source:
```
// Event "start" is performed when world is loaded
on:start
{
	// Lock super combination
	if (skillvalue("mySuperSkill") < 9000)
	{
		lockcombi "mySuperCombination";
	}

	// Setup some vars
	$foo = 1337;
	$bar = 228;
	//$baz = 420;
}
```

## Stage 1: Tokenizing

Comments are stripped away and whitespaces are removed when tokens are extracted

Tokenized example code (tokens, separated with spaces):
```
on : start { if ( skillvalue ( "mySuperSkill" ) < 9000) { lockcombi
"mySuperCombination" ; } $foo = 1337 ; $bar = 228 ; }
```

## Stage 2: Analyzing

Code is checked and analyzed.
  * Syntax check.
  * Function and method references are checked.
  * Types (Strings vs. Numbers) are checked.
  * String pool is created and strings are replaced with references to string
  pool.

Resulting example string pool:

|ID	|String					|
|---|-----------------------|
|0	| "start"				|
|1	| "skillvalue"			|
|2	| "mySuperSkill"		|
|3	| "lockcombi"			|
|4	| "mySuperCombination"	|
|5	| "foo"					|
|6	| "bar"					|

Resulting example code:
```
on : [0] { if ( [1] ( [2] ) < 9000) { [3] [4] ; } $[5] = 1337 ; $[6] = 228 ; }
```

## Stage 3: Assembling

Code is converted to reverse polish notation (postfix).
Arguments are pushed in a left-to-right order.

```
on [0]
	[2] f_[1] 9000 < if
		[4] p_[3]
	$[5] 1337 =
	$[6] 228 =
```

And then is assembled in a list of basic commands.

Resulting example code:
```
00:	on_event [0] 14
01: push [2]
02: call_f [1]
03: push 9000
04: compare
05: ifnle 8
06: push [4]
07: call_p [3]
08: get_var [5]
09: push 1337
10: write_var
11: get_var [6]
12: push 228
13: write_var
14: hlt
```

## Credits

This document is a part of [Stranded2pp](github.com/SMemsky/Stranded2pp)
