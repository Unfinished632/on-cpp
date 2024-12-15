# On
On is a statically typed interpreted programming language I made with minimal prior knowledge.

# Syntax
On is made up of **statements** and statements are made up of **instructions** and **values**.

Instructions are declared with a colon, like this:
```Instruction:```

You can put values to a statement depending on which instruction it is.
```Instruction: value1, value2, ...```

All statements must end with a semicolon.
```Instruction: value;```

Some instructions don't need/take values. They are written like this:
```Instruction:;```

# Data Types
As of now On has 2 data types which are **strings** and **integers**.

Strings are series of characters and are written with a double quote(") at the end and at the start of the characters.
```"This is a string"```

Integers are numbers with a possible value of the 32 bit integer limit. They don't have special syntax.
```12```
```299999```

In On, *all* values have a data type. 

# Instructions
**Print**: Prints its value to the console.
Usage: ```Print: <string>;```
Example: ```Print: "Hello World!";```

**Println**: Prints its value to the console and creates a new line. If given no arguments it will only create a new line.
Usages:
```Println: <string>;```
```Println:;```

**Wait**: Stops the program for a given amount of time(milliseconds).
Usage: ```Wait: <integer>(time in milliseconds);```
Example: This statement stops the program for 5 seconds:
```Wait: 5000;```
