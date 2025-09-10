# 🌐 The OSI Model

The **OSI Model (Open Systems Interconnection Model)** is a conceptual framework used in networking. It defines **how devices communicate** by dividing the process into **seven layers**, each with a **specific role**.

Its purpose:

- Standardize how networks function so devices of different types/vendors can communicate.
    
- Break down complex networking into **manageable chunks**.
    
- Allow troubleshooting step by step, layer by layer.
    

A key idea is **encapsulation**: at each layer, extra information (headers, sometimes trailers) is added to the data. At the destination, each layer removes its own part (**decapsulation**).

## Layer 1 - Physical Layer

**Role**: Concerned with the _physical transmission_ of data. It defines how **bits (0s and 1s)** move across the medium.

**Responsibilities**:

- Transmission media: copper cables, fiber, wireless signals.

- Electrical/optical/radio signals.

- Hardware: network adapters, hubs, repeaters.

- Defines bandwidth, voltage, connector types.

**Real example**: An Ethernet cable carrying electrical pulses, or Wi-Fi transmitting radio waves.

 **Without it**: Nothing can be transmitted.

**Encapsulation**

- **Action:** The frame is converted into a stream of **bits** (1s and 0s). These bits are then transmitted as electrical signals, light pulses (fiber), or radio waves (Wi-Fi) onto the physical medium.
- **PDU:** **Bits**

**Decapsulation**

- **Action:** The incoming electrical, optical, or radio signals are converted from **bits** back into a structured **frame** and passed up to the Data Link Layer.
- **PDU:** **Bits -> Frame**

## Layer 2 - Data Link Layer

**Function:** Provides **node-to-node** delivery on the _same local network segment_. It is responsible for framing, physical addressing, and error detection.

**Responsibilities**:

- Framing: Group raw bits into frames (structured chunks of data).

- Addressing: Use MAC addresses (hardware identifiers) to know “who is who” on a local network.

- Error detection/correction: Catch transmission errors (via CRC checksums).

- Flow control: Prevent fast senders from overwhelming slow receivers.

**Technical Details:** This layer takes packets from the network layer and encapsulates them into **frames**. It adds a header containing the source and destination **MAC addresses**. Switches use MAC addresses to make forwarding decisions within a LAN. It also adds a Frame Check Sequence (FCS) trailer for error detection.

**Encapsulation**

- **Action:** A **Data Link Header and Trailer** are added. The header contains the **Source and Destination MAC Addresses** for the _next hop_ on the local network. The trailer (typically a Frame Check Sequence - FCS) is used for error detection. This process creates a frame.

- **PDU:** **Frame**

**Decapsulation**

- **Action:** The frame's FCS trailer is checked for errors. If valid, the **Data Link Header and Trailer are stripped away**. The destination MAC address is verified to ensure the frame is intended for this device. The remaining **packet** is passed up to the Network Layer.
    
- **PDU:** **Frame -> Packet**

## Layer 3 - Network Layer

**Function:** Provides logical addressing and path determination between hosts on different networks (internetworking). Its job is to get packets from the source network to the destination network.

**Responsibilities**:

- Logical addressing: Assign and use IP addresses.

- Routing: Decide the path data takes between source and destination (routers work here).

- Packet forwarding: Move packets hop by hop through routers.

- Fragmentation: Split packets if the next link can’t handle large sizes (MTU issues).

**Key Protocols:**

- IP (Internet Protocol): The core protocol for logical addressing (IPv4, IPv6).

- ICMP: Used for diagnostics (ping, traceroute) and error reporting.

- OSPF, BGP, EIGRP: Routing protocols that routers use to build their routing tables.

**Technical Details**: Routers examine the destination IP address in the packet header, consult their routing table, and determine the next hop. The PDU at this layer is called a packet.

**Encapsulation**

Action: A Network Header is added. The core of this header is the Source and Destination IP Address. This header enables routers to make decisions on how to route the data across different networks to its final destination.

PDU: Packet

**Decapsulation**

Action: The Network Header is stripped away. The destination IP address is checked to confirm it matches the device's address. The resulting segment is passed up to the Transport Layer.

PDU: Packet -> Segment

## Layer 4 - Transport Layer

**Function**: Provides end-to-end communication services for applications. It is responsible for the reliability of the connection, flow control, and error correction.

**Responsibilities**:

- Segmentation: Break large messages into manageable segments/datagrams.

- Port addressing: Assign data to applications (port 80 = web, port 25 = email).

- Reliability:

	- TCP: Guarantees delivery, error checking, reordering, retransmission.
	
	- UDP: Faster but no guarantees (streaming, gaming).

- Flow control: Adjust sending rate to avoid congestion.

**Technical Details:** This layer segments data from the session layer and adds a header containing source and destination port numbers to enable multiplexing (multiple applications using the network simultaneously). The PDU at this layer is called a segment (TCP) or datagram (UDP).

**Encapsulation**

Action: This is a critical step. The data is segmented. A Transport Header is added, containing crucial information like the Source and Destination Port Numbers and sequence numbers (for TCP). This header dictates which application on the remote host should receive the data and ensures its reliability.

PDU: Segment (TCP) or Datagram (UDP)

**Decapsulation**

Action: The Transport Header is stripped away. Using the destination port number, the OS identifies which local application or service is waiting for this data. For TCP, segments are reordered and acknowledged. The reassembled data is passed to the appropriate session.

PDU: Segment -> Data

## Layer 5 - Session Layer

**Function**: Establishes, manages, synchronizes, and terminates sessions (ongoing dialogues) between two communicating hosts.

**Role**: The “coordinator” — sets up and maintains conversations (sessions) between applications.

**Responsibilities**:

- Session establishment, maintenance, and termination: the handshake process (e.g., TCP three-way handshake, though TCP is Layer 4, it serves this function).

- Synchronization: Insert checkpoints so long transfers can resume after failure.

- Dialog control: Manage who talks when (like half-duplex vs. full-duplex communication).

**Technical Details:** Protocols like NetBIOS, RPC, and PPTP operate at this layer. It manages the "conversation."

**Encapsulation**

Action: Information to manage the session (e.g., session control, synchronization points) is added as a header. The entire unit is passed down.

**Decapsulation**

Action: The Session Header is stripped away. The session is managed—if this is the end of the transmission, the session may be closed. The data is passed up.

PDU: Data

## Layer 6 - Presentation Layer

Function: Acts as the translator for the network. It ensures data from the application layer of one system is readable by the application layer of another.

Role: The “translator & security guard” — makes sure data is in a usable format.

**Three Primary Duties:**

**Translation**: Converting between different data formats (e.g., EBCDIC to ASCII, JSON to XML).

**Encryption/Decryption:** Applying cryptographic algorithms (TLS/SSL) to secure data for transmission.

**Compression/Decompression:** Reducing the size of the data to conserve bandwidth.

Technical Details: This layer is where certificates for SSL/TLS are processed. It handles the syntax and semantics of the information transmitted.

**Encapsulation**

Action: The data is encrypted (e.g., with TLS), compressed, or translated into a standard network format. The resulting data is passed down.

PDU: Data

**Decapsulation**

Action: The data is decrypted, decompressed, or translated from its standard network format back into a format the application layer can use.

PDU: Data

## Application Layer

Function: Provides network services directly to the end-user's applications. It is the interface between the application software and the network stack. Crucially, it is not the application itself (e.g., not Firefox), but the protocols the application uses to communicate (e.g., HTTP).

Key Protocols: HTTP/HTTPS (web), SMTP/POP3/IMAP (email), FTP/SFTP (file transfer), DNS (domain name resolution), DHCP (IP address assignment), SNMP (network management).

Technical Details: This layer handles user authentication, privacy, and determines resource availability. Services at this layer are identified by port numbers (e.g., port 80 for HTTP).

**Encapsulation**

Action: The user's data (e.g., an HTTP request for a webpage) is passed from the application to the network stack. This initial data block is the Payload.

PDU: Data

**Decapsulation**

Action: The original payload is delivered to the intended application (e.g., the web browser), which then displays the information to the user.

PDU: Data

## 🔑 The Flow of Roles

- **Layer 1–2**: Move data locally (hardware & MAC addresses).
    
- **Layer 3–4**: Enable communication between distant systems (IP, ports, reliability).
    
- **Layer 5–7**: Enable **user applications** to understand and use that communication.


**Note**:

Troubleshooting approach: Always go bottom-up:

Layer 1 → cable? power?

Layer 2 → switch? MAC conflict?

Layer 3 → routing? IP reachable?

Layer 4 → ports open? TCP working?

Layer 7 → app errors?

# TCP/IP Model

The **TCP/IP model** (Transmission Control Protocol/Internet Protocol) is a framework that describes how data is transmitted over a network. Unlike the theoretical OSI model, TCP/IP is a practical suite of protocols that defines how data is communicated across networks, ensuring it arrives safely and correctly at its destination by breaking it into packets.

The OSI model (which has 7 layers), and the TCP/IP model has **4 layers** and is the actual standard used in the Internet today.

Its purpose is to define **how devices communicate**, how data is split into packets, transmitted, routed, and reassembled correctly at the destination.

## Application Layer

This is the layer closest to the user, where network applications and their protocols operate.

Role: Acts as the bridge between user software (like a web browser or email client) and the underlying network. It defines how applications format and interpret data.

**Key Protocols:**

- HTTP/HTTPS: For accessing websites.

- FTP: For transferring files.

- SMTP: For sending email.

- DNS: For translating domain names (e.g., google.com) into IP addresses.

Also handles data formatting, encryption, and session management.

Functionality: It handles data formatting, encryption for security, and manages the session for ongoing connections.

👉 **Example**: When you type `www.google.com` into Chrome, the application layer uses **DNS** to resolve the name to an IP address and **HTTP/HTTPS** to request the page.

## Transport Layer

This layer is responsible for reliable, end-to-end communication between two devices.

**Role**: It ensures data is delivered completely, in the correct order, and without errors. It breaks down the data from the application layer into smaller units called segments.

**Key Protocols:**

- TCP (Transmission Control Protocol): Connection-oriented and reliable. It establishes a connection, acknowledges received data, and retransmits any lost segments. Used for web browsing, email, and file downloads where accuracy is critical.

- UDP (User Datagram Protocol): Connectionless and fast. It sends data without guaranteeing delivery, making it ideal for live video, voice chat, and online gaming where speed is more important than perfect accuracy.

👉 Example:

- Sending an email with attachments → uses TCP (no missing parts allowed).

- Watching a live football match online → uses UDP (better to miss a frame than to lag).

## Internet Layer (Network Layer)

This layer is the core of the TCP/IP model, responsible for routing data across different networks to its final destination.

Decides where data should go and how to get there across multiple networks.

Adds IP addresses to packets (source + destination).

Role: Its main job is to address, package, and route data. It encapsulates segments from the Transport layer into packets.

**Key Protocol:**

IP (Internet Protocol): Assigns a unique IP address to every device on a network and is responsible for delivering packets to the destination host based on that address. It is connectionless and relies on higher layers (TCP) for reliability.

**Handles:**

- Routing (choosing best path)

- Packet forwarding (moving packets between networks)

- Fragmentation (breaking large packets if needed)

**Functionality**: This layer handles routing (finding the best path), packet forwarding, and fragmentation (breaking large packets into smaller ones for transmission).

👉 **Protocols**: IPv4, IPv6, ICMP (for error reporting like “ping”).
👉 **Example**: Your laptop (192.168.1.10) sending data to Google’s server (142.250.x.x). The Internet Layer ensures the packet finds its way through routers.

## Network Access Layer

This is the lowest layer, dealing with the physical connection between devices on the same local network.

Role: It defines how data is sent over the physical hardware, such as Ethernet cables or Wi-Fi signals.

Functionality: It encapsulates IP packets into frames for transmission. It uses MAC addresses to uniquely identify devices on a local network segment. This layer also handles error detection to ensure the data wasn't corrupted during transmission over the physical medium.

- Works at the hardware/network interface level.

- Responsible for sending and receiving frames over physical media (Ethernet, Wi-Fi, fiber, etc.).

- Uses MAC addresses to identify devices on the same local network.

- Detects errors in physical transmission (e.g., corrupted frames).

👉 Example: Your laptop sends a frame with the MAC address of your Wi-Fi router before it goes out to the Internet.

### How the TCP/IP Model Works: Sending and Receiving Data

The process of data communication can be broken into two parts: sending and receiving.

#### When Sending Data (Encapsulation):

1. **Application Layer:** The user's data (e.g., an HTTP request) is prepared using the appropriate protocol.
    
2. **Transport Layer:** Data is broken into **segments**. TCP or UDP adds a header with information like port numbers to ensure it reaches the right application on the destination device.
    
3. **Internet Layer:** Segments are encapsulated into **packets**. An IP header is added, containing the source and destination IP addresses for routing across the internet.
    
4. **Network Access Layer:** Packets are encapsulated into **frames**. A header with the source and destination MAC addresses is added, and the frame is converted into **bits** to be transmitted over the physical network (cable or Wi-Fi).
    

#### When Receiving Data (Decapsulation):

1. **Network Access Layer:** Bits are received from the network and reassembled into **frames**. The MAC address is checked, and the frame header is removed, revealing the **packet**.
    
2. **Internet Layer:** The IP address in the packet header is verified. The IP header is stripped off, and the resulting **segment** is passed up.
    
3. **Transport Layer:** The segment is processed. TCP reassembles the segments in order and performs error checking. The TCP/UDP header is removed, and the **data** is passed to the appropriate application based on the port number.
    
4. **Application Layer:** The raw data is delivered to the intended application (e.g., a web browser), which renders the webpage for the user.


### TCP/IP vs. OSI Model

| Feature         | **TCP/IP Model**                                                              | **OSI Model**                                                                              |
| --------------- | ----------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------ |
| **Layers**      | **4 Layers** (Application, Transport, Internet, Network Access)               | **7 Layers** (Application, Presentation, Session, Transport, Network, Data Link, Physical) |
| **Development** | Developed based on existing protocols for practical implementation.           | Developed as a theoretical, comprehensive standard before protocols existed.               |
| **Usage**       | **The protocol suite of the actual internet.**                                | **A conceptual model** used for teaching, troubleshooting, and designing networks.         |
| **Design**      | Less rigid; the Application layer combines the functions of three OSI layers. | More rigidly defines the function of each layer.                                           |

In summary, the **TCP/IP model is the practical implementation that runs the modern internet**, while the **OSI model is a valuable theoretical tool** for understanding the concepts behind networking.

![[model-001.png]]

| Reason                             | Explanation                                                                                                               |
| ---------------------------------- | ------------------------------------------------------------------------------------------------------------------------- |
| **Simpler Structure**              | TCP/IP has only 4 layers, compared to 7 in OSI, making it easier to implement and understand in real systems.             |
| **Protocol-Driven Design**         | TCP/IP was designed based on working protocols, while the OSI model is more of a theoretical framework.                   |
| **Flexibility and Robustness**     | TCP/IP adapts well to different hardware and networks and includes error handling, routing, and congestion control.       |
| **Open Standard**                  | TCP/IP is open, free to use, and not controlled by any single organization, helping it gain universal acceptance.         |
| **Actual Use vs Conceptual Model** | The OSI model is great for education and design principles, but TCP/IP is the one actually used in real-world networking. |

### Advantages of TCP/IP Model

- **Interoperability** : The TCP/IP model allows different types of computers and networks to communicate with each other, promoting compatibility and cooperation among diverse systems.
- **Scalability** : TCP/IP is highly scalable, making it suitable for both small and large networks, from local area networks (LANs) to wide area networks (WANs) like the internet.
- **Standardization** : It is based on open standards and protocols, ensuring that different devices and software can work together without compatibility issues.
- **Flexibility** : The model supports various routing protocols, data types, and communication methods, making it adaptable to different networking needs.
- **Reliability** : TCP/IP includes error-checking and retransmission features that ensure reliable data transfer, even over long distances and through various network conditions.

### Disadvantages of TCP/IP Model

- **Security Concerns** : TCP/IP was not originally designed with security in mind. While there are now many security protocols available (such as SSL/TLS), they have been added on top of the basic TCP/IP model, which can lead to vulnerabilities.
- **Inefficiency for Small Networks** : For very small networks, the overhead and complexity of the TCP/IP model may be unnecessary and inefficient compared to simpler networking protocols.
- **Limited by Address Space** : Although IPv6 addresses this issue, the older IPv4 system has a limited address space, which can lead to issues with address exhaustion in larger networks.
- **Data Overhead** : TCP the transport protocol, includes a significant amount of overhead to ensure reliable transmission.

### How the Layers Map to Each Other

The key to understanding the relationship between the two models is seeing how their layers correspond. The TCP/IP model condenses the functions of the OSI model.

| TCP/IP Model Layer | Primary Function                                              | **Equivalent OSI Model Layers**                            | Explanation of Mapping                                                                                                                 |
| ------------------ | ------------------------------------------------------------- | ---------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------- |
| **Application**    | User interface, data formatting, encryption, session control. | **Application (7)  <br>Presentation (6)  <br>Session (5)** | The TCP/IP Application layer is a "catch-all" that handles all tasks related to representing data and managing communication sessions. |
| **Transport**      | End-to-end connections, reliability, flow control.            | **Transport (4)**                                          | This layer is **identical** in both models. TCP and UDP operate here.                                                                  |
| **Internet**       | Logical addressing (IP) and routing.                          | **Network (3)**                                            | This layer is **identical** in function. The IP protocol operates here.                                                                |
| **Network Access** | Physical addressing (MAC) and transmission on the medium.     | **Data Link (2)  <br>Physical (1)**                        | The TCP/IP model combines the framing, switching, and physical hardware aspects into a single layer.<br>                               |
### Key Takeaway: Why Both Models Matter

You often hear that the OSI model is the "reference model." This is absolutely true. Here’s why:

1. **The OSI Model is for Talking and Learning:** It provides a universal language. When a network engineer says, "The problem is at Layer 3," everyone knows they are talking about IP addressing and routing. Its granularity makes it perfect for **teaching concepts** and **troubleshooting** (e.g., a physical cable issue is Layer 1, a bad NIC is Layer 2, a firewall rule is Layer 3/4, etc.).
    
2. **The TCP/IP Model is for Doing:** It describes what **actually happens** on the internet. The internet wasn't built to fit the OSI model; it was built using the TCP/IP suite. When you configure your network adapter with an IP address, you are working directly with the TCP/IP model.