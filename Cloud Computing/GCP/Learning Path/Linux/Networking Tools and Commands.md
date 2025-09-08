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


## tcpdump 

`tcpdump` is a **packet analyzer**. It captures and displays network traffic going through your interfaces in real time.

### 🎯 Purpose

- Debugging **network problems**.
    
- Inspecting **traffic flow** (in/out of an interface).
    
- Security analysis (spot suspicious traffic, scanning, etc.).
    
- Learning how protocols (TCP, UDP, HTTP, DNS, etc.) actually work on the wire.

### ⚙️ Functions / Options (most useful)

- `tcpdump -i eth0` → Capture packets on `eth0`.
    
- `tcpdump -n` → Don’t resolve hostnames (show raw IPs).
    
- `tcpdump -nn` → Don’t resolve hostnames **or ports** (faster).
    
- `tcpdump -c 10` → Capture only 10 packets.
    
- `tcpdump -w file.pcap` → Save packets to a file for Wireshark analysis.
    
- `tcpdump -r file.pcap` → Read and display from a saved file.

### 🧩 Filters (the real power)

- `tcpdump port 80` → Capture only HTTP traffic.
    
- `tcpdump host 8.8.8.8` → Capture only traffic to/from Google DNS.
    
- `tcpdump src 192.168.1.10` → Capture traffic from a specific source.
    
- `tcpdump dst port 443` → Capture traffic going to HTTPS.
    
- `tcpdump tcp` → Only TCP packets.
    
- `tcpdump udp` → Only UDP packets.

### 💻 Examples

1. Capture all traffic on default interface:

```bash
sudo tcpdump -i eth0
```

2. Capture traffic to/from a specific ip:

```bash
sudo tcpdump -i eth0 host 8.8.8.8
```

3. Capture HTTP traffic and save it for later:

```bash
sudo tcpdump -i eth0 port 80 -w capture.pcap
```

4. Read back a capture file

```bash
tcpdump -r capture.pcap
```

### 🌍 Scenarios / When to Use It

- 🛠 **Troubleshooting** → Check if packets are actually leaving your server to the right destination.
    
- 🔐 **Security** → See if there’s strange traffic (like connections to unknown IPs).
    
- 🌐 **Performance** → Measure delays, retransmissions, or packet drops.
    
- 📡 **Learning** → Watch how DNS queries, TCP handshakes, or HTTP requests look in real life.
    

⚠️ **Note**: `tcpdump` usually requires **root privileges** (`sudo`) since it captures low-level packets.

### How to read the tcpdump output

#### 🧩 Example tcpdump output

```output
10:15:42.123456 IP 192.168.1.10.54321 > 172.217.165.196.80: Flags [S], seq 123456789, win 64240, length 0
10:15:42.234567 IP 172.217.165.196.80 > 192.168.1.10.54321: Flags [S.], seq 987654321, ack 123456790, win 65535, length 0
10:15:42.345678 IP 192.168.1.10.54321 > 172.217.165.196.80: Flags [.], ack 987654322, win 64240, length 0
```

#### 🔎 Breaking it down

Each line = one packet.

```bash
10:15:42.123456   → Timestamp
IP                → Protocol
192.168.1.10.54321 → Source IP + Port
172.217.165.196.80 → Destination IP + Port
Flags [S]          → TCP flag (here: SYN)
seq 123456789      → Sequence number
ack 123456790      → Acknowledgment number
win 64240          → Window size (buffer)
length 0           → Payload size
```

#### 🚦 Key TCP flags

- **[S] SYN** → Client wants to start a connection.
    
- **[S.] SYN-ACK** → Server replies, “Sure, let’s connect.”
    
- **[.] ACK** → Client acknowledges → **handshake complete**.
    
- **[P.] PSH-ACK** → Packet with data (like an HTTP request).
    
- **[F.] FIN** → Sender wants to close the connection.
    
- **[R] RST** → Reset → connection aborted (often errors).

## netcat

Netcat is one of the most powerful networking tools, security tools, and network monitoring tools. It is even considered a Swiss army knife of networking tools. It acts like a cat command over a network. It is generally used for the following reasons:

### 🎯 Purpose

- Operation related to TCP, UDP, or UNIX-domain sockets.
- Port Scanning
- Port Listening
- Port redirection
- open Remote connections
- Read/Write data across the network.
- Network debugging
- Network daemon testing
- Simple TCP proxies
- A Socks or HTTP Proxy Command for ssh

It is designed by keeping in mind that it should be a flexible "back-end" tool that can be used directly or driven by any other program.

### ⚙️ Key Functions / Options

- `nc <option> <host> <port>` → connect to a host on a port.
    
- `nc -l <port>` → listen on a port (server mode).
    
- `-u` → use UDP instead of TCP.
    
- `-v` → verbose (show more info).
    
- `-z` → scan mode (just check if port is open, no data sent).
	 
* `-U` → use Unix domain sockets
	
- `-w` → set a timeout for connections
	
- `-p` → specifies the source port number
	
- `nc -k -l` → continue listening after disconnection
	
- `-n` → skip DNS lookups

### ⚡ Netcat Working Modes

#### 🔹 1. Connect Mode (Client)

- Netcat **initiates a connection** to a remote service (like a browser connecting to a website).
    
- You must provide a **host** (IP or domain) and a **port**.
    
- Useful for:
    
    - Testing if a port is open.
        
    - Sending/receiving data manually (HTTP requests, SMTP commands, etc).
        
    - Debugging connectivity.
        
- Example:

```bash
nc example.com 80
```

#### 🔹 2. Listen Mode (Server)

- Netcat **waits for incoming connections** on a given port (like a web server does).
    
- Optionally bind to a specific IP/interface (default: all).
    
- Useful for:
    
    - Creating a simple server or backdoor.
        
    - Receiving files/data.
        
    - Testing client connections.
        
- Example:

```bash
nc -lv 192.168.0.1 8080
```

##### ✅ Quick Recap

- **Connect mode = Client** → you start the connection.
    
- **Listen mode = Server** → you wait for connections.
    
- Together, they can simulate full client-server interactions.

### Scenarios

#### Client/Server Connection

A simple client/server connection is between two devices. One device acts as a server (listens) while the other acts as a client (connects).

1. On device 1, run the nc command in listen mode and provide a port:

```bash
nc -lv 1234
```

The **`-l`** option activates listen mode, making device 1 the server. The output shows the device listening for connections due to the **`-v`** option.

2. On device 2, run the **`nc`** command with the IP address of device 1 and the port:

```bash
nc -v 10.0.2.4 1234
```

Once the client/server connection establishes successfully you can send a message from either device. 

#### Ping Specific Port on Website

Use Netcat as an alternative to the ping command to test a specific port to a website. For example:

```bash
nc -zv google.com 443
```

```output
DNS fwd/rev mismatch: google.com != mia07s60-in-f14.1e100.net
google.com [142.250.217.174] 80 (http) open
```

If the ping succeeds, the output shows the successful connection message. The -z option ensures the connection does not persist.

Netcat does not give any specific information, and there are other methods to ping a specific port.

#### Scanning Ports

Use the **`nc`** command to scan for open ports.

1. Run **`nc`** on device 1 to listen on port 1234:

```bash
nc -lkv 1234
```

The **`-k`** option ensures the connection stays open after a disconnect.

2. Run the following command on device 2 to check whether port 1234 is open:

```bash
nc -zv 10.0.2.4 1234
```

If the port is open, the output shows a successful connection message.

3. Alternatively, scan multiple ports on device 2 by adding a port range. For example:

```bash
nc -zv 10.0.2.4 1230-1235
```

4. When scanning for port ranges, filter the results using grep:

```bash
nc -zv 10.0.2.4 1230-1235 2>&1 | grep 'succeeded'
```

For example, grepping for the word _**`succeeded`**_ only shows open ports in the output.

#### Transfer files

Netcat allows transferring files through established connections. To see how file transfers work, do the following:

1. Create a sample file on device 1 using the **`touch`** command:

```bash
touch file.txt
```

2. Create a listening connection on device 1 and redirect the file to the **`nc`** command:

```bash
nc -lv 1234 < file.txt
```

3. On device 2, connect to device 1 and redirect the file:

```bash
nc -zv 10.0.2.4 1234 > file.txt
```

#### Transfer Dirs

Netcat does not allow transferring directories in the same way as files. Use the tar command to send multiple files or directories and pipe the command to Netcat.

1. Create a directory on either device and add multiple files:

```bash
mkdir files; touch files/file{1..5}.txt
```

The command creates a files directory with five text files.

2. Navigate to the directory using the cd command:

```bash
cd files
```

3. On the other device, create and enter the destination directory:

```bash
mkdir files_destination && cd files_destination
```

4. Create a listening connection on port 1234 and pipe the **`tar`** command:

```bash
nc -lv 1234 | tar xfv -
```

The listening connection expects a file that tar extracts.

5. On the other device, send the directory with:

```bash
tar -cf - . | nc -v 10.0.2.5 1234
```

The connection establishes and sends the tar file.

### References

[nc Command (Netcat) with Examples](https://phoenixnap.com/kb/nc-command)

[practical uses of netcat](https://www.geeksforgeeks.org/linux-unix/practical-uses-of-ncnetcat-command-in-linux/)

[how to use netcat: commands](https://www.varonis.com/blog/netcat-commands#create-a-chat-or-web-server)


## curl

`curl` = **Client URL**.  
It’s a command-line tool to **transfer data to/from a server** using many protocols (HTTP, HTTPS, FTP, SMTP, etc).

### 🎯 Purpose

- Test APIs and web servers.
    
- Download files from the internet.
    
- Send requests (GET, POST, PUT, DELETE).
    
- Debug headers, authentication, redirects.

### ⚙️ Common Options

- `-v` → verbose, show request + response details.
    
- `-I` → fetch only HTTP headers (HEAD request).
    
- `-L` → follow redirects.
    
- `-o file` → save output to file.
    
- `-d` → send data (POST).
    
- `-H` → add custom header.

### 💻 Examples

1. Simple GET request

```bash
curl https://example.com
```

Fetches and prints the HTML content 

```html
<!doctype html>
<html>
<head>
    <title>Example Domain</title>

    <meta charset="utf-8" />
    <meta http-equiv="Content-type" content="text/html; charset=utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1" />
    <style type="text/css">
    body {
        background-color: #f0f0f2;
        margin: 0;
        padding: 0;
        font-family: -apple-system, system-ui, BlinkMacSystemFont, "Segoe UI", "Open Sans", "Helvetica Neue", Helvetica, Arial, sans-serif;

    }
    div {
        width: 600px;
        margin: 5em auto;
        padding: 2em;
        background-color: #fdfdff;
        border-radius: 0.5em;
        box-shadow: 2px 3px 7px 2px rgba(0,0,0,0.02);
    }
    a:link, a:visited {
        color: #38488f;
        text-decoration: none;
    }
    @media (max-width: 700px) {
        div {
            margin: 0 auto;
            width: auto;
        }
    }
    </style>
</head>

<body>
<div>
    <h1>Example Domain</h1>
    <p>This domain is for use in illustrative examples in documents. You may use this
    domain in literature without prior coordination or asking for permission.</p>
    <p><a href="https://www.iana.org/domains/example">More information...</a></p>
</div>
</body>
</html>

```

2. Show response headers only

```bash
curl -I https://example.com
```

```http
HTTP/2 200
content-type: text/html
etag: "84238dfc8092e5d9c0dac8ef93371a07:1736799080.121134"
last-modified: Mon, 13 Jan 2025 20:11:20 GMT
cache-control: max-age=86000
date: Mon, 08 Sep 2025 01:51:10 GMT
alt-svc: h3=":443"; ma=93600,h3-29=":443"; ma=93600
```

3. Verbose mode (debugging)

```bash
curl -v https://example.com
```

4. Follow redirects

```bash
curl -L http://example.com
```

5. Send POST request with data

```bash
curl -X POST -d "username=jony&password=1234" https://example.com/login
```

6. Add customer header (common for APIs)

```bash
curl -H "Authorization: Bearer <token>" https://api.example.com/data
```

### 🌍 Scenarios

- 🕵️ **Debugging APIs** → check responses, headers, authentication.
    
- 📥 **File downloads** → quick and scriptable.
    
- 🛠 **Testing servers** → is a website up? is HTTPS working?
    
- 🔐 **Security checks** → see raw responses, cookies, redirections.

## systemctl

`systemctl` is the main command-line tool to **manage systemd services and system state** on Linux. It’s used to **start, stop, enable, disable, restart, or check the status of services**, as well as manage system targets (like boot mode).

### ⚙️ Common uses

- Start a service:

```bash
sudo systemctl start nginx
```

- Stop a service:

```bash
sudo systemctl stop nginx
```

- Restart a service

```bash
sudo systemctl restart nginx
```

- Enable at boot

```bash
sudo systemctl enable nginx
```

- Check service status

```bash
systemctl status nginx
```

### 🌍 Scenarios

- 🛠 **Troubleshooting** → check if a service is running (like `systemctl status ssh`).
    
- ⚡ **Administration** → restart services after configuration changes.
    
- 🔄 **Automation** → enable critical services to auto-start at boot.