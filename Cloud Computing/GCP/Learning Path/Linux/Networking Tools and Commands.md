# Commands

## netstat (Linux)

The network statistics (`netstat`) command is a networking tool used for troubleshooting and configuration, that can also serve as a monitoring tool for connections over the network. Both incoming and outgoing connections, routing tables, port listening, and usage statistics are common uses for this command. Let's take a look at some of the basic usage for `netstat` and the most used cases.

It’s mainly used to **monitor network activity** and **diagnose network-related issues** such as open ports, active connections, or routing problems.

### ⚙️ Functions / Options (most used)

- `netstat -a` → Shows all active connections and listening ports.
    
- `netstat -t` → Displays only TCP connections.
    
- `netstat -u` → Displays only UDP connections.
    
- `netstat -l` → Shows listening sockets (services waiting for connections).
    
- `netstat -p` → Shows the PID and program name for each connection.
    
- `netstat -r` → Displays the kernel routing table (like `route -n`).
    
- `netstat -i` → Displays a table of network interfaces.
    
- `netstat -s` → Shows protocol statistics (TCP, UDP, ICMP).

### 💻 Examples

1. Check all listening services:

````bash
netstat -tuln
````

![[linux-010.png]]

2. See which process is using port 80

```bash
netstat -tulnp | grep 80
```

3. Display routing table 

![[linux-011.png]]

### 🌍 Scenarios / When to Use It

- 🔎 **Check which ports are open** on your server.
    
- 🕵️ **Find suspicious connections** (like malware opening unknown ports).
    
- 📡 **Troubleshoot connectivity** (see if a service is listening).
    
- 🌐 **View routing information** when debugging why packets aren’t reaching a destination.
    

⚠️ **Note**: On modern Linux distros, `netstat` is considered **deprecated** in favor of the `ss` command, which is faster and more powerful. But you’ll still find `netstat` widely used in tutorials and older systems.




