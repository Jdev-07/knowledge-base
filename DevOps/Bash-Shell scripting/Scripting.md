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


