# Linux Basics
## The Terminal

The terms “terminal,” “shell,” and “command line interface” are often used interchangeably, but there are subtle differences between them:

- A _terminal_ is an input and output environment that presents a text-only window running a shell.
- A _shell_ is a program that exposes the computer’s operating system to a user or program. In Linux systems, the shell presented in a terminal is a command line interpreter.
- A _command line interface_ is a user interface (managed by a command line interpreter program) which processes commands to a computer program and outputs the results.

When someone refers to one of these three terms in the context of Linux, they generally mean a terminal environment where you can run commands and see the results printed out to the terminal

- **Terminal** → Think of it as the "window" or "app" where you type commands. It’s just the environment where you interact.
    
- **Shell** → This is the actual program that takes what you type, understands it, and tells the computer what to do. (Examples: Bash, Zsh, PowerShell).
    
- **Command Line Interface (CLI)** → This is the style of interaction where you type text commands instead of clicking buttons.

---

# Linux Commands

## File and Directory Commands

| Command   | Description                             | Example                                    |
| --------- | --------------------------------------- | ------------------------------------------ |
| ls        | List directory contents.                | ls                                         |
| cd        | Change directory                        | cd /home/user                              |
| pwd       | Print working directory                 | pwd                                        |
| mkdir     | Create a new directory                  | mkdir Labs                                 |
| rmdir     | Remove an empty dir                     | rmdir Labs                                 |
| cat       | Display file contents                   | cat file.txt                               |
| **find**  | **Search for files in a dir hierarchy** | **find . -name "file.txt"**                |
| **grep**  | **Search text using patterns**          | **grep "pattern" file.txt**                |
| tar       | Archive and compress files              | tar -cvf archive.tar file.txt file.txt     |
| df        | Show disk usage of file system          | df -h (will show a human-readable output ) |
| du        | Show dir/file size                      | du -sh /home/user                          |
| **chmod** | **Change file permissions**             | **chmod 755 file.txt**                     |
| **chown** | **Change file owner**                   | **chown user:group file.txt**              |
| mount     | Mount a filesystem                      | mount /dev/sdv1 /mnt                       |
| umount    | Unmount a filesystem                    | umount /mnt                                |

### grep command

`grep` stands for **Global Regular Expression Print**.  
It’s a Linux command used to **search for text** inside files or output.

**📌 Basic examples**

1. **Search for a word in a file**:

```Bash
grep "error" logfile.txt
```

2. **Case-insensitive search**:

```Bash
grep -i "error" logfile.txt
```

3. **Search across multiple files**:

```Bash
grep "TODO" *.py
```

4. **Search in command output (using a pipe `|`)**:

```Bash
ps aux | grep "nginx"
```


 **🚀 Some useful options**

- `-i` → ignore case (no matter uppercase/lowercase).
    
- `-r` → search recursively inside folders.
    
- `-n` → show line numbers.
    
- `-v` → show lines that **don’t** match.

### find command

`find` is a Linux command used to **search for files and directories** in your system, based on conditions like name, type, size, or modification time.

**🛠️ Basic usage**

The structure is:

```Bash
find [where_to_search] [conditions]
```

**🔎 Examples**

1. **Find a file by name**:

```Bash
find . -name "notes.txt"
```

2. **Find files by extension**:

```Bash
find . -name "*.log"
```

3. **Find files bigger than 100MB**:

```Bash
find . -size +100M
```

4. **Find recently modified files (last 1 day)**:

```Bash
find . -mtime -1
```

**🚀 Key options**

- `-name` → match file name.
    
- `-iname` → case-insensitive match.
    
- `-type f` → files only.
    
- `-type d` → directories only.
    
- `-size` → match by file size.
    
- `-mtime` → match by modification time.
    
- `-exec` → run commands on matches.

## Networking commands


| Command          | Description                                                                                                                                                                                | Sample                                         |
| ---------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ---------------------------------------------- |
| ping             | Test connectivity to a host. Ping is a network command used to **check if a host (computer, server, website, etc.) is reachable** and how long it takes for data to travel there and back. | - ping www.google.com<br>- ping -c 4 127.0.0.1 |
| ifconfig / ip a  | Display network interfaces                                                                                                                                                                 | - ifconfig<br>- ip a                           |
| **netstat / ss** | **Show network connections**                                                                                                                                                               | **- netstat -tuln<br>- ss -tuln**              |
| **wget**         | **Download file via HTTP/FTP**                                                                                                                                                             | **wget http://example.com/file.zip**           |
| **curl**         | **Transfer data using URL syntax**                                                                                                                                                         | **curl -O http://example.com/file.zip**        |
| **nc (netcat)**  | **Network debugging and data transfer**                                                                                                                                                    | **nc -zv 192.168.1.1 80**                      |
| tcpdump          | Capture and analyze network packets                                                                                                                                                        | tcpdump -i eth0                                |
| iptables         | Configure firewall rules                                                                                                                                                                   | iptables -A INPUT -p tcp --dport 22 -j ACCEPT  |
| traceroute       | Trace the path packets take to a network host                                                                                                                                              | traceroute example.com                         |
| nslookup         | Query DNS to obtain domain name or IP address mapping                                                                                                                                      | nslookup www.saborarcense.com                  |
| ssh              | Securely connect to a remote host                                                                                                                                                          | ssh user@ipaddress                             |

### netstat

netstat (short for network statistics) is a command-line tool that shows network connections, routing tables, interface stats, and more.

Basically, it tells you what’s happening on your network:

- What connections are open
    
- Which ports are being used
    
- Which apps/processes are using the network

**💡 Uses**

1. List all listening ports

To list all listening ports, using both TCP and UDP, use `netstat -a`:

![[knowledge-base/Cloud Computing/GCP/Learning Path/Linux/images/linux-001.png]]

2. List only TCP port connections

If you found the `-a` option to be too verbose, try the `-t` flag with it:

![[knowledge-base/Cloud Computing/GCP/Learning Path/Linux/images/linux-002.png]]
3. List only UDP connections

The same filter can be used to pull UDP connections down. Seen here:

![[linux-003.png]]
4. List all actively listening ports

To list all actively listening ports (both TCP and UDP), use the following command:

5. Show all actively listening ports only

![[linux-004.png]]

6. Pull stats by protocol

7. Show routing table

8. Show numeric address/ports

### curl

curl stands for **Client URL**.  
It’s a command-line tool to **transfer data from or to a server**, using many protocols like HTTP, HTTPS, FTP, SFTP, etc.

👉 Unlike `wget` (mostly for downloading files), `curl` is more about **interacting with APIs and web servers**.

 **🚀 Common options**

- `-O` → save file with original name.
    
- `-o` → save file with custom name.
    
- `-L` → follow redirects.
    
- `-I` → show headers only.
    
- `-d` → send POST data.
    
- `-H` → add custom header.
    
- `-u` → username/password login.

### netcat

netcat is known as the **“Swiss army knife of networking”** 🛠️.  
It lets you **read and write data across network connections**, using TCP or UDP.

You can use it to:

- Test connectivity between machines
    
- Transfer files
    
- Open a chat between two computers
    
- Debug network services
    
- Create simple servers

Basic usage

```Bash
nc [options] <host> <port>
```

Will deep dive into Networking commands and tools in the following: [[Networking Tools and Commands]]

## Process and system Monitoring Commands


| Command        | Description                       | Example                              |
| -------------- | --------------------------------- | ------------------------------------ |
| **ps**         | **Show running processes**        | **ps aux**                           |
| **top**        | **Dynamic process viewer**        | **top**                              |
| **htop**       | **Enhanced version of top**       | **htop**                             |
| **kill**       | **Send a signal to a process**    | **kill `<PID>`**                     |
| **killall**    | **Kill processes by name**        | **killall `<process_name>`**         |
| uptime         | System uptime and load            | uptime                               |
| env            | Display environment variables     | env                                  |
| strace         | Trace system calls of a processs  | strace -p `<PID>`                    |
| **systemctl**  | **Managed systemd services**      | **systemct status `<service_name>`** |
| **journalctl** | **View system logs**              | **journalctl -xe**                   |
| **free**       | **Display memory usage**          | **free -h**                          |
| vmstat         | Report virtual memory stats       | vmstat 1                             |
| **iostat**     | **Report CPU and I/O stats**      | **iostat**                           |
| Isof           | List open files by process        | Isof                                 |
| dmesg          | Print kernel ring buffer messages | dmesg                                |

## User and Permission Management Commands


| Command           | Description                       | Example                                      |
| ----------------- | --------------------------------- | -------------------------------------------- |
| passwd            | Change password user              | passwd `<username>`                          |
| adduser / useradd | Add new user                      | adduser `<username>`<br>useradd `<useradd>`  |
| deluser / userdel | Delete a user                     | deluser `<username>`<br>userdel `<username>` |
| usermod           | Modify user account               | usermod -aG `<group>` `<username>`           |
| groups            | Show group memberships            | groups `<username>`                          |
| id                | Display user identity information | id `<username>`                              |
| newgrp            | Log in to a new group             | newgrp `<group>`                             |

## File and Transfer Commands


| Command | Description                           | Example                                                      |
| ------- | ------------------------------------- | ------------------------------------------------------------ |
| scp     | Securely copy file over SSH           | scp user@remote:/path/to/file/local/destination              |
| rsync   | Efficiently sync files and dirs       | rsync -avz /local/directory/user@remote:/path/to/destination |
| ftp     | Transfer files using the FTP          | ftp ftp.example.com                                          |
| sftp    | Securely transfer files using SSH FTP | sftp user@remote:/path/to/file<br>                           |

## Text Processing Commands

| Command | Description                                 | Example                          |
| ------- | ------------------------------------------- | -------------------------------- |
| sed     | Stream editor for filtering/modifying text. | `sed 's/old/new/g' file.txt<br>` |
| cut     | Remove sections from lines of text.         | `cut -d':' -f1 /etc/passwd`      |
| sort    | Sort lines of text                          | sort file.txt                    |
| grep    | Search for patterns in text                 | grep 'pattern' file.txt          |
| wc      | Count words, lines , and chars              | wc -l file.txt                   |
| paste   | Merge lines of files                        | past file1.txt file2.txt         |
| head    | Output the first part of files.             | head -n 10 file.txt              |
| tail    | Output the last part of files               | tail -n 10 file.txt              |
| join    | Join lines of two files on a common filed   | join file01.txt file02.txt       |

## Shell utilities


| Command  | Description                                                   | Example             |
| -------- | ------------------------------------------------------------- | ------------------- |
| alias    | Create shortcuts for commands                                 | alias ll='ls -la'   |
| unalias  | Remove an alias                                               | unalias=ll          |
| history  | previously entered commands                                   | history             |
| clear    | Clear the terminal screen                                     | clear               |
| reboot   | Reboot the system                                             | reboot              |
| shutdown | Power off the system                                          | shutdown now        |
| date     | Display or set the system date and time                       | date                |
| echo     | Display a line of text                                        | echo "Hello, world" |
| sleep    | Delay for a specified amount of time                          | sleep 5             |
| time     | Measure the duration of commands                              | time ls             |
| watch    | Execute a program periodically, showing the output fullscreen | watch -n 5 df -h    |

--- 

Check related content:
[[The Linux Filesystem]]
[[Networking Tools and Commands]]
[[Linux File Permissions and Ownership]]