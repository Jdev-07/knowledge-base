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






