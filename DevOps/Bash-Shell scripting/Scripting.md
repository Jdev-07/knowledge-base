## Bash Syntax for Scripting

Bash scripts are sequences of commands executed by the Bash shell. They automate tasks and can be used to perform complex operations. Understanding the bash syntax is crucial for writing effective scripts.

### Basic Syntax

There are some basic rules for using Bash in scripts

- **Comments:** Comments start with a `#` and Bash ignores them.
- **Command Order:** Commands run one after the other, from top to bottom.
- **Semicolons:** Use `;` to run multiple commands on the same line.

Below is an example of using `#` to comment and `;` to execute multiple commands in the same line.

```Bash
#!/usr/bin/env bash
# This is a bash script

echo "Hey there, I am working on Fedora OS"
echo "My name is Jony Morales"; echo "Today is friday, nice weekend!"
```

After writing the bash script, only need to execute the following

```Shell
chmod +x script01.sh
./scrip01.sh
```

Output:

```Output
└─$ ./script01.sh
Hey there, I am working on Fedora OS
My name is Jony Morales
Today is friday, nice weekend!
```

## Bash script

Bash scripts are files containing commands that you run in the terminal.

When creating a bash script file, always include the shebang `#!` followed by the path to bash. The path to bash can be under `/bin/bash` or `/usr/bin/env bash`

```Bash
#!/bin/bash

echo "Hey there! I am on vacations!"
```


Make sure the script file has appropriate permissions for execution.

```Bash
sudo chmod +x /filename.sh
```

A simple example of using `variables`

```C
#!/bin/bash
NAME="Jony"
echo "Hello, $NAME!"
```

Output:

```Output
jonmorales@vbox:~/Documents/Scripts$ ./script01.sh 
Hello, Jony!
```

### Variables

Variables in Bash are used to store data that can be used and manipulated throughput your bash script or command-line sessions. Bash variables are un-typed, meaning they can store any type of data.

**Declaring variables**

To declare variable only need to assign a value to a variable name. There must not be any spaces between the equal sign. Accessing to variable value only need to use the following $variable_name.

```Bash
NAME="Jony Morales"
AGE="24"
echo "Hey there, I am $NAME. I am $AGE"
```

#### Environment `variables`

This type of variable are special because the affect the way processes run on system. They are often used to store location of executable or the default editors.

#### Local vs. Global `variables`

Local variable in Bash exists only inside functions. Unlike global ones that are accessible  anywhere within the script. 

```Bash
#!/bin/bash

GLOBAL_VAR=15

greetingFunc(){
	local LOCAL_VAR=25
	echo $LOCAL_VAR
}

greetingFunc
echo $GLOBAL_VAR
```

**Common `variable` operations**

The variables can be used for various operations, such as concatenation (strings) and arithmetic for math operations.

Small example:

```Bash
#!/bin/bash
MESSAGE="Hey there, "
NAME="Vanessa"
echo "$MESSAGE$NAME"

#MATH
NUM01=8
NUM02=16
SUM=$((NUM01 + NUM02))
echo "The sum of the numbers is $SUM"
```

Output:

```Output
jonmorales@vbox:~/Documents/Scripts$ ./script04.sh 
Hey there, Vanessa
The sum of the numbers is 24
```


## Bash Data Types

Although the variables are `un-typed`, there are some data type available in bash.

### `string`

Strings are sequences of characters used to store text. They can manipulated for operations such concatenation and sub-string extraction.  

Concatenation:

```Bash
#!/bin/bash
greetings="Hey there pal!"
name="Randy, Right?"
fullText="$greetings$name"
echo "$fullText"
```

Sub-strings extraction:

```Bash
#!/bin/bash
file="backup.tar.gz"
echo "${file#backup.}"
```

### `numbers`

Numbers in bash can be used for arithmetic operations.

```Bash
#!/bin/bash
num01=15
num02=25
sum=$((num01 + num02))
difference=$((num02 - num01))
product=$((num01 * num02))
quotient=$((num02 / num01))
echo "Sum: $sum, Difference: $difference, Product: $product, Quotient: $quotient"
```


### `arrays`

Arrays are used to store multiple values in a single variable.Each element in an array is accessed using an index. You can iterate over arrays and modify elements.

```Bash
#!/bin/bash
fruits=("apple" "Banana" "Cherry")
for fruit in "${fruits[@]}"; do
	echo $fruit
done
```

### Associative `arrays`

Associative arrays allow you to use named keys to access values. They are similar to dictionaries in other programming languages. You can add or remove keys and values.

```Shell
#!/bin/bash
declare -A colors
colors[apple]="red"
colors[grape]="purple"
colors[banana]="yellow"
unset colors[banana]
echo "${colors[apple]}"
echo "${colors[grape]}"
```

## Bash operators

In bash there are many operators that are grouped by their functionality. 

### Comparison `operators`

- `-eq`: Equal to
- `-ne`: No equal to
- `-lt`: Less than
- `-le`: Less than or equal to
- `-qt`: Greater than
- `-ge`: Greater than or equal to

### String Comparison `operators`

- `=`: Equal to
- `!=`: Not equal to
- `<`: Less than, in ASCII alphabetical order.
- `>`: Greater than, in ASCII alphabetical order.

### Arithmetic `operators`

- `+`: Addition
- `-`: Subtraction
- `*`: Product
- `/`: Division
- `%`: Modulus (reminder of division)
- For exponentiation, user external tools like `bc` or `awk`.

### Logical  `operators`

- `&&`: Logical AND
- `||`: Logical OR
- `!`: Logical NOT

### File Test `operators`

- `-e`: Checks if a file exists
- `-d`: Checks if a directory exists
- `-f`: Checks if a file is a regular file
- `-s`: Checks if a file is not empty

## Bash `if-else`

For conditional statements we can use `if-else`

### `if` statements

"If statements" allow you to to execute a chunk of code based on a condition. If this condition is met, the block of code will run.

Example:

```Bash
#!/bin/bash
num=15
if [ $num -gt 10 ]; then
	echo "The number $num is greater than 10"
fi
```


The condition is enclosed in square brackets `[ ]` and the statements ends with `fi`.

### `if-else` statements

The `if-else` statements provides  a way to execute one block if the condition is met, and another one if does not.

```Bash
#!/bin/bash
num=5
if [ $num -gt 10 ]; then
	echo "The number $num is greater than 10"
else
	echo "The number $num is equal or less than"
fi
```

### `elif` statements

`elif` statements allow you to check multiple conditions in sequence. If the first condition is false, next one is checked. 

```Bash
#!/bin/bash
num=10
if [ $num -gt 10 ]; then
	echo "The number $num is greater than 10"
elif [ $num -eq 10 ]; then
	echo "The number $num is equal to 10"
else
	echo "The number $num is less than 10"
fi
```

### Nested `if` statements

Nested if statements allow you to place an if statement inside another if statement, enabling more complex logic. 

```Bash
#!/bin/bash
num=5
if [ $num -gt 0 ]; then
	if [ $num -lt 10 ]; then
		echo "Number is between 1 and 9"
	fi
fi
```