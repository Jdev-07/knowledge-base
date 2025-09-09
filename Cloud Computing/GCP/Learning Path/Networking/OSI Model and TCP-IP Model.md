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