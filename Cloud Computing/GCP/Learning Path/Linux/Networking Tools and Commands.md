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

## traceroute

`traceroute` maps the path that packets take from your machine to a destination host (like google.com). It shows each hop along the route and how long it takes to reach it.

### 🎯 Purpose

- Diagnose **network routing issues**.
    
- See **where latency or packet loss** happens.
    
- Verify if packets are reaching their destination.

### ⚙️ Functions / Options

- `traceroute <host>` → Basic usage, shows hops to a host.
    
- `traceroute -n <host>` → Skip DNS lookup, show only IPs (faster).
    
- `traceroute -I <host>` → Use ICMP instead of UDP packets.
    
- `traceroute -T <host>` → Use TCP SYN packets (useful when firewalls block UDP/ICMP).
    
- `traceroute -m <hops> <host>` → Set max hops (default: 30).

💻 **Examples**

1. Trace route to google.com:

```bash
traceroute google.com
```

```output
traceroute to www.google.com (172.217.165.196), 30 hops max, 60 byte packets
 1  jdev.mshome.net (x.x.x.x)  1.040 ms  0.972 ms  0.965 ms
 2  192.168.1.1 (192.168.1.1)  2.795 ms  2.764 ms  1.913 ms
 3  x.x.x.x (x.x.x.x)  7.228 ms  7.163 ms  7.075 ms
 4  * * *
 5  * * *
 6  * * *
 7  * 192.178.71.26 (192.178.71.26)  30.314 ms *
 8  192.178.96.229 (192.178.96.229)  42.431 ms 142.251.77.73 (142.251.77.73)  42.719 ms 192.178.96.229 (192.178.96.229)  42.186 ms
 9  142.250.239.63 (142.250.239.63)  42.549 ms  42.269 ms  42.122 ms
10  lax31s06-in-f4.1e100.net (172.217.165.196)  42.114 ms  42.093 ms  42.038 ms
```

2. Trace with TCP packets (mimics real traffic better)

```bash
sudo traceroute -T -p 80 google.com
```

```output
traceroute to google.com (142.250.217.174), 30 hops max, 60 byte packets
 1  jdev.mshome.net (x.x.x.x)  0.271 ms  0.243 ms *
 2  192.168.1.1 (192.168.1.1)  2.195 ms  2.191 ms *
 3  * * *
 4  * * *
 5  * * *
 6  * * *
 7  * * *
 8  192.178.99.149 (192.178.99.149)  42.227 ms 108.170.255.9 (108.170.255.9)  42.694 ms  41.777 ms
 9  142.250.61.131 (142.250.61.131)  41.461 ms  41.658 ms 108.170.232.201 (108.170.232.201)  41.860 ms
10  mia07s60-in-f14.1e100.net (142.250.217.174)  42.272 ms  41.205 ms  41.391 ms
```

### 🧩 How to read traceroute

Each **line** = one hop (a router along the path).  
Each **hop** shows:

- Hostname + IP
    
- 3 round-trip times (ms) for 3 probe packets

- By default, `traceroute` sends **3 probe packets** (usually UDP or ICMP, depending on options) **to each hop**.
    
- Each packet makes a round trip (from your machine → router → back).
    
- The numbers are the **response times (latency)** in **milliseconds (ms)** for those 3 packets.

#### 🎯 Purpose of sending 3 probes

1. **Accuracy** → One packet could get delayed randomly (due to congestion, CPU load, queueing, etc.), so having 3 gives a better average.
    
2. **Stability check** → If all 3 are close together → the path is stable.
    
    - Example: `42.1 ms 42.0 ms 42.2 ms` ✅ very consistent.
        
    - Example: `42.1 ms 110.5 ms 200.3 ms` ⚠️ unstable, something’s congested.
        
3. **Packet loss detection** → If one or more show as `*`, it means **no reply** came back for that probe (could be dropped or filtered).

#### 🌍 Scenarios

- If all 3 times are **similar and low** → hop is healthy.
    
- If one is much higher → temporary spike (usually fine).
    
- If all are high → consistent latency issue.
    
- If you see `* * *` → hop not replying (normal in some networks).

### 🌍 Scenarios / When to Use It

- 🌐 Internet seems slow → Use `traceroute` to see **which hop is causing delay**.
    
- 🚧 Troubleshoot firewalls → Some networks block ICMP, so using `-T` (TCP) helps.
    
- 🕵️ Detect routing loops → See if packets bounce between routers endlessly.
    
- 📡 Cloud/server debugging → Find out where connectivity breaks (local ISP, backbone, or target server)