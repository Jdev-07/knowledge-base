# Networking Concepts

Latency, Bandwidth, Throughput, Packet, Packet Loss, Frame, Encapsulation and Decapsulation.
## Latency

Latency is the **time delay** it takes for data to travel from the source (like your computer) to the destination (like a server) across a network.

- Measured in **milliseconds (ms)**.
    
- It’s often called the “ping time.”
    
- Lower latency means faster responses (important for gaming, video calls, cloud apps).

## Bandwidth 

Bandwidth is the **maximum amount of data** that can be transmitted over a network link in a given period of time.

- Measured in **bits per second (bps)**, often shown as **Kbps, Mbps, Gbps, or Tbps**.
    
- Think of it as the **capacity** of the connection.

### ✅ Example

- A 100 Mbps internet connection means your link can carry up to 100 million bits per second under ideal conditions.

Note: 

Important: Having high bandwidth doesn’t always mean you get high performance—that also depends on **latency, throughput, and packet loss**.

## Throughput

Throughput is the **actual amount of data** successfully transmitted over a network in a given period of time.

- Measured in **bits per second (bps)**, just like bandwidth.
    
- Unlike bandwidth (the maximum capacity), throughput shows the **real performance** you experience.

### ✅ Example

- Your ISP plan = **100 Mbps bandwidth**.
    
- But due to congestion, errors, or protocol overhead, you only get **70 Mbps throughput** when downloading a file.

### ⚡ Analogy

Back to the highway:

- **Bandwidth** = 4-lane highway (capacity).
    
- **Throughput** = how many cars actually make it through per minute, considering traffic jams, accidents, or toll booths.

👉 **Key difference**:

- **Bandwidth = potential capacity**
    
- **Throughput = achieved capacity**

## Packet

A **packet** is the **basic unit of data** transmitted across a network. Instead of sending all the data at once, networks break it into smaller chunks (packets) for efficiency and reliability.

Each packet contains two main parts:

1. **Header** – control information (source & destination IP, protocol, sequencing, error-checking, etc.).
    
2. **Payload** – the actual data being transmitted (like part of a web page, video frame, or file).

### ✅ Example

When you send an email with a 1 MB attachment, it’s broken into many packets. Each packet travels through the network independently, and the receiver reassembles them to rebuild the file.

### ⚡ Analogy

Think of sending a book by mail:

- You don’t send the whole book in one package.
    
- You rip out the pages, put them into **individual envelopes (packets)**, label them with addresses (**headers**), and send them.
    
- At the destination, all the envelopes are collected and the book is put back together.

## Frame

A **frame** is a data unit used at the **Data Link Layer (Layer 2 of the OSI model)**.

- It’s the **encapsulated form of a packet** when it travels across a physical network (like Ethernet or Wi-Fi).
    
- Frames include addressing info for the local network (like **MAC addresses**) so devices know where to send the data within the same network segment.

### 📦 Structure of a Frame (simplified)

- **Header** → contains source & destination **MAC addresses**, error-checking info.
    
- **Payload** → the actual packet from the Network layer (e.g., an IP packet).
    
- **Trailer** → often includes error detection (CRC).

### ✅ Example

If your laptop sends a web request:

- At Layer 3 → it creates an **IP packet** with source/destination IPs.
    
- At Layer 2 → that packet is wrapped in an **Ethernet frame** with source/destination MACs.
    
- The switch uses the MAC addresses in the frame to forward it to the correct device.

### ⚡ Analogy

Think of a **packet as a letter** inside an **envelope (the frame)**:

- The **letter** has the recipient’s city and street (IP info).
    
- The **envelope** has local delivery info like the house number (MAC address).
    
- Postmen (switches) read the envelope (frame) to get it to the right neighborhood.

👉 In short:

- **Packet = Layer 3 (IP)**
    
- **Frame = Layer 2 (Ethernet/Wi-Fi, etc.)**

## Packet loss

**Packet loss** happens when one or more packets traveling across a network **fail to reach their destination**.

- It means data is either dropped, discarded, or corrupted along the way.
    
- Measured as a **percentage of packets lost** compared to the total sent.

### 🔹 Causes of Packet Loss

1. **Network Congestion** – too much traffic, buffers overflow, routers drop packets.
    
2. **Hardware Issues** – faulty cables, damaged network cards, overheating routers.
    
3. **Wireless Interference** – signal issues, distance, or obstacles in Wi-Fi.
    
4. **Software/Configuration Errors** – misconfigured firewalls, routing errors.
    
5. **Corruption** – if a packet fails error-checking (e.g., CRC mismatch), it gets dropped.

### ✅ Example

If you send **1,000 packets** and only **990 arrive**, you have a **1% packet loss**.

## Encapsulation

Encapsulation is the process of **wrapping data with protocol-specific headers (and sometimes trailers)** as it moves down the layers of the OSI or TCP/IP model.

Each layer adds its own information so the data can be properly transmitted, routed, and delivered.


### How Encapsulation Works (Step by Step)

1. **Application Layer** → data is created (e.g., an HTTP request).
    
2. **Transport Layer (L4)** → adds a **TCP/UDP header** (port numbers, sequencing).
    
3. **Network Layer (L3)** → adds an **IP header** (source/destination IPs).
    
4. **Data Link Layer (L2)** → wraps the packet in a **frame** (MAC addresses, error-checking).
    
5. **Physical Layer (L1)** → converts the frame into bits and sends it as signals.

### ⚡ Analogy

Think of sending a gift 🎁:

- You put the **gift** (data) in a **box** (TCP/UDP header).
    
- Then put the box in a **shipping package** with an address label (IP header).
    
- Then load it into a **truck** (frame/MAC info).
    
- Finally, it goes onto the **road as vehicles** (bits/signals).
    

Each wrapping ensures the delivery system knows how to handle the data.

## Decapsulation

Decapsulation is the **reverse process of encapsulation**: removing headers (and trailers) at each OSI/TCP-IP layer as data travels **up the stack** on the receiving device.

The goal is to strip away delivery instructions until only the **original application data** remains


### 🔹 How Decapsulation Works (Step by Step)

1. **Physical Layer (L1)** → receives raw bits/signals from the wire or air.
    
2. **Data Link Layer (L2)** → removes the **frame header/trailer** (MAC addresses, CRC).
    
3. **Network Layer (L3)** → removes the **IP header** (source/destination IP).
    
4. **Transport Layer (L4)** → removes the **TCP/UDP header** (ports, sequencing).
    
5. **Application Layer** → delivers the **original data** to the app (e.g., browser).

👉 In short:

- **Encapsulation = sender adds layers.**
    
- **Decapsulation = receiver removes layers.**