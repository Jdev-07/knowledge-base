# File permissions

Every file and directory in Linux has **three types of permissions** for **three types of users**:

1. **User (u)** – The owner of the file.
    
2. **Group (g)** – Other users in the same group as the file.
    
3. **Others (o)** – Everyone else.
    

**Permissions** determine what these users can do:

- **r = read** → You can open or view the file.
    
- **w = write** → You can modify or delete the file.
    
- **x = execute** → You can run the file as a program (or enter a directory if it’s a folder).

## How permissions look?

When you run `ls -l`, you might see something like that:

```Bash
-rwxr-xr--
```

**Here’s what it means:**

1. **The first character**:
    
    - `-` = regular file
        
    - `d` = directory
        
    - `l` = symbolic link


Next 9 characters (split into 3 sets of 3)

```Bash
rwx | r-x | r--
 u    g     o
```

- **User (owner)**: `rwx` → can read, write, and execute
    
- **Group**: `r-x` → can read and execute, but not write
    
- **Others**: `r--` → can only read

## What are octal values?

When Linux file permissions are represented by numbers, it's called numeric mode. In numeric mode, a three-digit value represents specific file permissions (for example, 744.) These are called octal values. The first digit is for owner permissions, the second digit is for group permissions, and the third is for other users. Each permission has a numeric value assigned to it:

- r (read): 4
- w (write): 2
- x (execute): 1

For example, a file might have read, write, and execute permissions for its owner, and only read permission for all other users. That looks like this:

- Owner: rwx = 4+2+1 = 7
- Group: r-- = 4+0+0 = 4
- Others: r-- = 4+0+0 = 4

## What do Linux file permissions actually do?

### Read (r)

Read permission is used to access the file's contents. You can use a tool like `cat` or `less` on the file to display the file contents. You could also use a text editor like Vi or `view` on the file to display the contents of the file. Read permission is required to make copies of a file, because you need to access the file's contents to make a duplicate of it.

### Write (w)

Write permission allows you to modify or change the contents of a file. Write permission also allows you to use the redirect or append operators in the shell (`>` or `>>`) to change the contents of a file. Without write permission, changes to the file's contents are not permitted.

### Execute (x)

Execute permission allows you to execute the contents of a file. Typically, executables would be things like commands or compiled binary applications. However, execute permission also allows someone to run Bash shell scripts, Python programs, and a variety of interpreted languages.

## How do directory permissions work?

Directory file types are indicated with `d`. Conceptually, permissions operate the same way, but directories interpret these operations differently.

### Read (r)

Like regular files, this permission allows you to read the contents of the directory. However, that means that you can view the contents (or files) stored within the directory. This permission is required to have things like the `ls` command work.

### Write (w)

As with regular files, this allows someone to modify the contents of the directory. When you are changing the contents of the directory, you are either adding files to the directory or removing files from the directory. As such, you must have write permission on a directory to move (`mv`) or remove (`rm`) files from it. You also need write permission to create new files (using `touch` or a file-redirect operator) or copy (`cp`) files into the directory.

### Execute (x)

This permission is very different on directories compared to files. Essentially, you can think of it as providing access to the directory. Having execute permission on a directory authorizes you to look at extended information on files in the directory (using `ls -l`, for instance) but also allows you to change your working directory (using `cd`) or pass through this directory on your way to a subdirectory underneath.

## Summary

### 📌 File Permissions (on normal files)

- **Read (r):** You can **open and look at** the file’s content.  
    👉 Example: read a text file with `cat file.txt`.
    
- **Write (w):** You can **change the file’s content**.  
    👉 Example: edit it with `nano file.txt` or overwrite with `echo "hi" > file.txt`.
    
- **Execute (x):** You can **run the file** as a program or script.  
    👉 Example: run `./script.sh` if it’s executable.
    

---

### 📌 Directory Permissions (on folders)

- **Read (r):** You can **see the list of files** inside.  
    👉 Example: run `ls` to view what’s in the folder.
    
- **Write (w):** You can **add, delete, or rename** files in the folder.  
    👉 Example: create a file with `touch new.txt` or delete one with `rm old.txt`.
    
- **Execute (x):** You can **enter the folder** and access its contents.  
    👉 Example: use `cd folder/` or look at details with `ls -l`.
    

---

### 🎯 Super Simple Way to Remember

- On **files**:
    
    - **r** = look at it
        
    - **w** = change it
        
    - **x** = run it
        
- On **directories**:
    
    - **r** = see what’s inside
        
    - **w** = add/remove stuff
        
    - **x** = enter and use it

## How to modify Linux Permissions?

### Using `chmod` (change mode)

There are **two ways**:

1. **Numeric mode (octal values):**
    
    - Example:

```Bash
chmod 744 example.txt
```

- 👉 User = read/write/execute, Group = read only, Others = read only.
    
- Numbers map to permissions:
    
    - `4` = read (r)
        
    - `2` = write (w)
        
    - `1` = execute (x)
        
    - Add them up → e.g., `7 = rwx`.

**Symbolic mode (letters):**

- Example:

```Bash
chmod ug+rwx example.txt   # add rwx to user and group
chmod o+r example2.txt     # add read for others
chmod a-x script.sh        # remove execute for all
```
- **u = user**, **g = group**, **o = others**, **a = all**.

### Changing Ownership

- **`chown`** → change owner:

```Bash
chown jony file.txt
chown jony:devs file.txt   # owner = jony, group = devs
```

**`chgrp`** → change group only:

```Bash
chgrp devs file.txt
```

