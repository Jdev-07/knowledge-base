# Linux Filesystem 

![[linux-005.png]]

Linux has a **single tree-like filesystem** that starts at **`/`** (the _root directory_).  
Everything (files, folders, devices) lives under `/`.

## /bin

`/bin` (short for **binaries**) is one of the most important directories in Linux.  
It contains **essential programs** (executables) that both **the system and users** need to operate, even if the system is in a minimal or recovery state.

### 🔎 Why `/bin` exists

- When Linux boots, not all parts of the filesystem are immediately available.
    
- `/bin` contains the **basic tools** required before other directories (like `/usr`) can be mounted.
    
- These tools let you **navigate, inspect, and repair** the system if something goes wrong.
    

So if your Linux system was broken and only booted into emergency mode, `/bin` is where you’d find the programs to fix it.

### ⚙️ What lives in `/bin`

Inside `/bin`, you’ll find commands you already know and use every day:

- **Navigation & inspection** → `ls`, `pwd`
    
- **File handling** → `cp`, `mv`, `rm`, `mkdir`, `rmdir`, `touch`
    
- **Viewing/editing text** → `cat`, `echo`, `less`, `more`
    
- **Linking** → `ln`
    
- **Other basics** → `basename`, `date`, `uname`
    

These programs are small but powerful, they give you control over files, directories, and basic system info.

## /boot

The **`/boot`** directory is all about **starting your system**.  
It contains the files and programs the computer needs to **boot (start up) the operating system** before Linux itself is fully loaded.

### 🔎 Why `/boot` is important

When you press the power button:

1. Your computer’s **BIOS/UEFI firmware** starts first.
    
2. It looks for the **bootloader** (found in `/boot`).
    
3. The bootloader then loads the **Linux kernel** and initial files needed to bring the system to life.
    

So `/boot` is the **bridge between hardware and the Linux operating system**.

### ⚙️ What’s inside `/boot`

Typical files you’ll find here:

- **Linux kernel(s)** → files like `vmlinuz-6.2.0-34-generic`
    
    - This is the heart of the OS: it controls hardware and system processes.
        
- **Initramfs (initial RAM filesystem)** → files like `initrd.img-6.2.0-34-generic`
    
    - A temporary filesystem loaded into memory during boot.
        
    - It contains drivers and tools needed for mounting the real root filesystem (`/`).
        
- **Bootloader files** (GRUB, most common) →
    
    - `grub/` directory → configuration files for GRUB (the boot menu).
        
    - `grub.cfg` → the actual GRUB config script (which kernel to boot, advanced options, etc.).
        
- **System map** → `System.map-<kernel version>`
    
    - A lookup table that helps debugging and kernel processes.


## /dev

The **`/dev`** directory is where Linux represents **devices as files**.  
This is one of the fundamental Unix/Linux ideas: _“everything is a file.”_

That means instead of having a totally different system to handle hardware (like disks, terminals, or random number generators), Linux just makes a **special file** inside `/dev`. Interacting with that file is the same as interacting with the device.

👉 Example: reading from `/dev/sda` doesn’t read from a text file — it actually reads raw data from your hard drive.

### 🔎 Why `/dev` matters

- It gives Linux a **simple and consistent interface** for all hardware. Whether you’re working with a hard drive, a keyboard, or even just random numbers, the way you interact is the same: by reading/writing to files.
    
- This design makes Linux **flexible and powerful**: programs don’t need to know hardware details; they just talk to files.
    
- `/dev` is also **critical for system boot** — without it, the OS wouldn’t be able to talk to drives, terminals, or memory devices.
    
- Modern Linux systems use **udev**, which automatically creates or removes device files in `/dev` when you plug in or disconnect hardware (like a USB stick).
    

👉 In short: `/dev` is how Linux connects the **software world** to the **hardware world**.

### ✅ Easy summary

- `/dev` = **devices as files**.
    
- Lets Linux talk to hardware through simple read/write operations.
    
- Common examples:
    
    - `/dev/sda` → hard drive
        
    - `/dev/tty` → terminal
        
    - `/dev/null` → black hole for data
        
- Dynamically managed by **udev** when hardware is added or removed.
    

👉 Think of `/dev` as **Linux’s control panel for hardware, but in file form**.

## /etc

The **`/etc`** directory is the **central hub for system configuration files** in Linux.  
Almost all of the system-wide settings and configurations for services, programs, and the operating system itself live here.

👉 If `/boot` is the ignition and `/dev` is the hardware translator, then `/etc` is the **rulebook**: it tells the system _how_ to behave.

### 🔎 Why `/etc` matters

- It contains the **configuration files** that define how the system works.
    
- Almost every service (networking, users, security, applications) looks in `/etc` for its setup.
    
- Admins (and sometimes power users) often edit these files to customize or fix the system.
    
- Without `/etc`, Linux wouldn’t know:
    
    - What users exist.
        
    - What your hostname is.
        
    - How to start network services.
        
    - What daemons (background services) to launch at boot.
        

Basically, `/etc` = **system’s brain for configuration**.

### ✅ Easy summary

- `/etc` = **system configuration directory**.
    
- Holds text files and subdirectories that define how Linux works.
    
- Common examples:
    
    - `/etc/passwd` → users
        
    - `/etc/hosts` → hostname mappings
        
    - `/etc/fstab` → disk mount points
        
- Without `/etc`, the system wouldn’t know how to boot, connect to networks, or manage users.
    

👉 Think of `/etc` as **Linux’s settings folder — the place where all the rules live**.

## /home

The **`/home`** directory is where Linux stores all **user-specific files and settings**.  
Each normal user on the system gets their own personal folder inside `/home`, which acts as their **workspace**.

## /lib

The **`/lib`** directory contains the **shared libraries** that programs and the operating system need to run.  
You can think of these libraries as the **building blocks** or **tools** that executables in `/bin` and `/sbin` rely on.

### 🔎 Why `/lib` matters

- Many programs don’t carry all the code they need inside themselves. Instead, they use **shared libraries** stored in `/lib`.
    
- This makes programs smaller, more efficient, and easier to update (fixing a bug in one library fixes it for every program using it).
    
- Without `/lib`, most essential commands and system processes would fail to run, even if the executables themselves exist.
    
- It also contains the **kernel modules** (in `/lib/modules/`), which are like plugins for the Linux kernel — they let it support extra hardware or features dynamically.
    

👉 In short: `/lib` provides the **support system** that makes executables and the kernel actually work.

### Easy summary

- `/lib` = **libraries and kernel modules**.
    
- Provides shared code (`.so` files) that executables in `/bin` and `/sbin` need.
    
- Stores kernel modules that extend Linux’s hardware and feature support.
    
- Without `/lib`, even basic commands like `ls` or `cp` wouldn’t run.

## /media

- `/media` is a **mount point directory** used to temporarily attach (mount) removable storage devices like USB drives, external hard drives, DVDs, or SD cards.
    
- Modern Linux distros automatically create a subdirectory inside `/media` when you plug in a device.

## /opt

`/opt` is a directory in Linux used for **optional software packages**.

It’s where third-party applications that aren’t part of the default system installation are often installed. For example, if you download and install software manually (instead of through the package manager), it may place its files under `/opt/appname/`.

- **Purpose**: Keep add-on or proprietary software separate from system files.
    
- **Typical contents**: Directories for each application (e.g., `/opt/google/chrome/`).
    
- **Benefit**: Keeps the system organized and avoids mixing vendor software with the OS’s native binaries (`/usr/bin`, `/bin`, etc.).
    

👉 Think of `/opt` as a special folder for "extra" software that doesn’t come with Linux by default.

## /proc

`/proc` is a **virtual filesystem** in Linux.

- It doesn’t store real files on disk — instead, it provides **runtime system information** from the kernel.
    
- Each running process gets its own directory under `/proc`, named by its **PID** (process ID). For example, `/proc/1234/` contains details about process 1234.
    
- It also has files and directories that expose kernel and hardware info (like `/proc/cpuinfo`, `/proc/meminfo`, `/proc/uptime`).
    

👉 Think of `/proc` as a **window into the kernel and processes**. It updates dynamically as the system runs.

## /root

`/root` is the home directory of the **root user**, the superuser in Linux with full administrative privileges. Unlike regular users, whose home directories are inside `/home/username`, the root user’s home is placed directly under `/` to ensure it’s always accessible, even if `/home` is on a separate partition that fails to mount. It’s mainly used to store the root user’s personal files, scripts, and configuration settings.

## /run

`/run` is a **temporary filesystem** in Linux that **stores runtime data** needed by the system and applications after boot. It’s typically mounted as a `tmpfs` (kept in RAM), meaning its contents exist only while the system is running and are cleared at reboot. You’ll find things like process IDs (`/run/*.pid`), lock files, sockets, and other state information that programs use to communicate or track their status. In short, `/run` is where Linux keeps **volatile runtime information** that should not persist across reboots.

**Summary:** `/run` is a temporary storage space for active system and service information, helping processes communicate and track runtime data while the system is on.
## /sbin

`/sbin` is a directory in Linux that contains **system binaries**—essential programs needed for system administration and maintenance. **These include tools for managing filesystems**, networking, booting, and repairing the system (e.g., `fsck`, `ifconfig`, `reboot`). Unlike `/bin`, which holds essential commands for all users, `/sbin` mostly has commands intended to be run by the **root user** or with elevated privileges.

## /usr

`/usr` in Linux stands for **Unix System Resources**, and it contains the bulk of user-space applications and files. Inside, you’ll find things like user commands (`/usr/bin`), system administration tools (`/usr/sbin`), libraries (`/usr/lib`), shared resources (`/usr/share`), and sometimes source code or documentation. Unlike `/bin` or `/sbin`, which hold essential programs for booting and minimal system recovery, `/usr` is for the **main operating system utilities, applications, and libraries** that are not needed until after the system has fully booted. In modern Linux systems, `/usr` often holds the majority of installed software.

## /srv

The `/srv` directory is used to store **data for services provided by the system**. Its name comes from “service,” and it typically contains files and directories related to services like web servers, FTP servers, or other network services. The **purpose** of `/srv` is to provide a dedicated location for service-specific data that the system actively serves to users or other systems, making it easier to manage and maintain. Its **functionality** lies in organizing persistent service data separately from logs, caches, or temporary files, ensuring that service content is accessible, structured, and ready for delivery.

`/srv` = where services put their stuf

**Example:** A web server like Apache might store website files in `/srv/www`, while an FTP server could keep uploaded files in `/srv/ftp`.

## /sys

The `/sys` directory is a **virtual filesystem** that provides a view into the **kernel’s device and system information**. It doesn’t contain real files on disk; instead, it exposes kernel data structures as files and directories that you can read or sometimes write to configure the system. The **purpose** of `/sys` is to allow administrators and programs to **interact with hardware devices, drivers, and kernel subsystems** in a structured way. Its **functionality** includes showing information about CPUs, memory, buses, and devices, and enabling configuration of certain device parameters without needing to reboot.

**Example:** You can check CPU information via `/sys/devices/system/cpu/` or adjust device power settings for USB devices in `/sys/bus/usb/devices/`.

**Summary:** `/sys` provides a real-time interface to the Linux kernel and hardware, allowing observation and control of system components in a safe, organized manner.

`/sys` = live system info about your hardware and kernel.

## /tmp

The `/tmp` directory is used to store **temporary files** created by the system and applications. Its **purpose** is to provide a space where programs can safely write data that is only needed **short-term**, such as session data, caches, or temporary processing files. The **functionality** of `/tmp` is that it is typically cleared automatically on system reboot (depending on the distribution), ensuring that temporary data does not accumulate and consume disk space unnecessarily.

**Example:** When you extract a `.zip` file or open a document in a text editor, temporary copies might be stored in `/tmp` while you work with them.

**Summary:** `/tmp` is a temporary storage space for short-lived files, helping applications and the system manage transient data without cluttering permanent storage.

## /var

The `/var` directory stands for **“variable”** and is used to store **data that changes frequently** during system operation. Its **purpose** is to provide a place for files that grow or change in size, such as logs, caches, mail, spool files, and temporary application data. The **functionality** of `/var` is to keep dynamic system data separate from static files in directories like `/bin` or `/etc`, helping maintain system organization and stability.

**Example:** Log files are stored in `/var/log/`, print jobs in `/var/spool/cups/`, and package caches in `/var/cache/apt/` (on Debian/Ubuntu systems).

**Summary:** `/var` is the directory for storing variable, frequently updated files, such as logs, caches, and spools, keeping the system organized and manageable.

![[linux-006.png]]