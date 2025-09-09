
The OSI model (or Open System Interconnection Model) is an essential model used in networking. This critical model provides a framework dictating how all networked devices will send, received and interpret data.

One of the main benefits of the OSI model is that devices can have different functions and designs on a network while communicating with other devices. Data sent across a network that follows the uniformity of the OSI model can be understood by other devices.

The OSI model consists of seven layers which are illustrated in the diagram below. Each layer has a different set of responsibilities and is arranged from Layer 7 to Layer 1.

At every individual layer that data travels through, specific processes take place, and pieces of information are added to this data. However, for now, we only need to understand that this process is called encapsulation and what the OSI model looks like in the diagram below:

![[network-lan-06.png]]
## Physical Layer

This layer is one of the easiest layers to grasp. Put simply, this layer references the physical components of the hardware used in networking and is the lowest layer that you will find. Devices use electrical signals to transfer data between each other in a binary numbering system (1's and 0's).

For example, ethernet cables connecting devices, such as in the picture below:

![[network-lan-07.png]]
## Data Link

The data link layer focuses on the physical addressing of the transmission. It receives a packet from the network layer (including the IP address for the remote computer) and adds in the physical **MAC** (Media Access Control) address of the receiving endpoint. Inside every network-enabled computer is a **N**etwork **I**nterface Card (**NIC**) which comes with a unique MAC address to identify it.

MAC addresses are set by the manufacturer and literally burnt into the card; they can’t be changed – although they can be spoofed. When information is sent across a network, it’s actually the physical address that is used to identify where exactly to send the information.

Additionally, it’s also the job of the data link layer to present the data in a format suitable for transmission.

## Network 

The third layer of the OSI model (network layer) is where the magic of routing & re-assembly of data takes place (from these small chunks to the larger chunk). Firstly, **routing simply determines the most optimal path in which these chunks of data should be sent.**

Whilst some protocols at this layer determine exactly what is the "optimal" path that data should take to reach a device, we should only know about their existence at this stage of the networking module. Briefly, these protocols include **OSPF** (**O**pen **S**hortest **P**ath **F**irst) and **RIP** (**R**outing **I**nformation **P**rotocol). The factors that decide what route is taken is decided by the following:

- What path is the shortest? I.e. has the least amount of devices that the packet needs to travel across.
- What path is the most reliable? I.e. have packets been lost on that path before?
- Which path has the faster physical connection? I.e. is one path using a copper connection (slower) or a fibre (considerably faster)?

At this layer, everything is dealt with via IP addresses such as 192.168.1.100. Devices such as routers capable of delivering packets using IP addresses are known as Layer 3 devices — because they are capable of working at the third layer of the OSI model.

## Transport 

Layer 4 of the OSI model plays a vital part in transmitting data across a network and can be a little bit difficult to grasp. When data is sent between devices, it follows one of two different protocols that are decided based upon several factors

- TCP
- UDP

### TCP

The **T**ransmission **C**ontrol **P**rotocol (**TCP**). Potentially hinted by the name, this protocol is designed with reliability and guarantee in mind. This protocol reserves a constant connection between the two devices for the amount of time it takes for the data to be sent and received.

Not only this, but TCP incorporates error checking into its design. Error checking is how TCP can guarantee that data sent from the small chunks in the session layer (layer 5) has then been received and reassembled in the same order.

Let's summarize the advantages and disadvantages of TCP in the table below:


| Advantages                                                                               | Disadventages                                                                                                                                     |
| ---------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------- |
| Guarantees the accuracy of data.                                                         | Requires a reliable connection between the two devices. If one small chunk of data is not received, then the entire chunk of data cannot be used. |
| Capable of synchronizing two devices to prevent each other from being flooded with data. | A slow connection can bottleneck another device as the connection will be reserved on the receiving computer the whole time.                      |
| Performs a lot more processes for reliability.                                           | TCP is significantly slower than UDP because more work has to be done by the devices using this protocol.                                         |
TCP is used for situations such as **file sharing, internet browsing or sending an email.** This usage is because these services require the data to be accurate and complete (no good having half a file!).

In the diagram below, we can see how a picture of a cat is broken down into small pieces of data (known as packets) from the "webserver", where the "computer" re-constructs the picture of the cat into the correct order.

![[network-lan-08.png]]

### UDP

 **U**ser **D**atagram **P**rotocol (or  UDP for short). This protocol is not nearly as advanced as its brother - the TCP protocol. It doesn't boast the many features offered by TCP, such as error checking and reliability. In fact, any data that gets sent via UDP is sent to the computer whether it gets there or not. There is no synchronization between the two devices or guarantee; just hope for the best, and fingers crossed.

Whilst this sounds disadvantageous, it does have its merits, which we'll layout in the table below:


| Advantages                                                                                                            | Disadvantages                                                                       |
| --------------------------------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------------------- |
| UDP is much faster than TCP.                                                                                          | UDP doesn't care if the data is received.                                           |
| UDP leaves the application layer (user software) to decide if there is any control over how quickly packets are sent. | It is quite flexible to software developers in this sense.                          |
| UDP does not reserve a continuous connection on a device as TCP does.                                                 |  This means that unstable connections result in a terrible experience for the user. |
Using the same example as before, we can now see that only Packets #1 and #3 have been received by the "Computer", meaning that half of the image is missing.

![[network-lan-09.png]]

## Session

Once data has been correctly translated or formatted from the presentation layer (layer 6), the session layer (layer 5) will begin to create and maintain the connection to other computer for which the data is destined. When a connection is established, a session is created. Whilst this connection is active, so is the session.

The session layer is also responsible for closing the connection if it hasn't been used in a while or if it is lost. Additionally, a session _can_ contain "checkpoints," where if the data is lost, only the newest pieces of data are required to be sent, saving bandwidth. 

What is worthy of noting is that sessions are unique — meaning that data cannot travel over different sessions, but in fact, only across each session instead.

## Presentation

Layer 6 of the OSI model is the layer in which standardization starts to take place. Because software developers can develop any software such as an email client differently, the data still needs to be handled in the same way — no matter how the software works.

This layer acts as a translator for data to and from the application layer (layer 7). The receiving computer will also understand data sent to a computer in one format destined for in another format. For example, when you send an email, the other user may have another email client to you, but the contents of the email will still need to display the same.

Security features such as data encryption (like HTTPS when visiting a secure site) occur at this layer.

## Application 

The application layer of the OSI model is the layer that you will be most familiar with. This familiarity is because the application layer is the layer in which protocols and rules are in place to determine how the user should interact with data sent or received.

Everyday applications such as email clients, browsers, or file server browsing software such as FileZilla provide a friendly, **G**raphical **U**ser **I**nterface (**GUI**) for users to interact with data sent or received. Other protocols include **DNS** (**D**omain **N**ame **S**ystem), which is how website addresses are translated into IP addresses.

## Scenario

👉 **You type `www.google.com` in your web browser and hit Enter.**

---

## 🔎 Step-by-Step OSI Model Example

### Layer 7 – Application Layer

- Your browser (Chrome, Edge, etc.) wants to fetch Google’s homepage.
    
- It uses **HTTP/HTTPS protocol**.
    
- The browser also requests DNS resolution to find the IP of `www.google.com`.
    

**What happens here:** The request is prepared as application data → “Get me Google’s homepage!”

---

### Layer 6 – Presentation Layer

- If using HTTPS (which Google does), your browser and Google’s server agree on **encryption methods (TLS/SSL)**.
    
- Data (like your login cookies or search queries) will be **encrypted and compressed** before sending.
    

**What happens here:** Data becomes secure and ready for transmission.

---

### Layer 5 – Session Layer

- A **session** is created between your browser and Google’s server.
    
- Think of it as: “Keep this conversation open until I’m done browsing.”
    
- Session management ensures that if you send multiple requests, they all belong to the same ongoing interaction.
    

**What happens here:** A session is opened → the browser and server stay connected until you close the tab or log out.

---

### Layer 4 – Transport Layer

- Your browser uses **TCP** (Transmission Control Protocol) because HTTP/HTTPS requires reliable communication.
    
- TCP:
    
    - Splits data into **segments**.
        
    - Adds **port numbers** (e.g., your browser uses a random high port, Google listens on port **443** for HTTPS).
        
    - Ensures **error-free delivery** and retransmits if packets are lost.
        

**What happens here:** “I’m sending this request from my port 49502 → to Google’s port 443.”

---

### Layer 3 – Network Layer

- The data is now a **packet**.
    
- Your PC adds **source IP** (e.g., `192.168.1.10`) and **destination IP** (Google’s server, e.g., `142.250.72.36`).
    
- Routers along the way decide the **best route** to get the packet from your ISP → Google’s data center.
    

**What happens here:** “Send this packet from my IP to Google’s IP, route it however you need.”

---

### Layer 2 – Data Link Layer

- The packet is placed inside a **frame**.
    
- The frame includes **MAC addresses**:
    
    - Source MAC = your network card.
        
    - Destination MAC = your router (next hop).
        
- Switches and routers use these MACs to forward data locally.
    

**What happens here:** “Send this frame from my laptop’s NIC to the router’s NIC.”

---

### Layer 1 – Physical Layer

- Finally, the frame is turned into **electrical signals, light pulses, or radio waves** depending on your medium:
    
    - Wi-Fi → radio waves.
        
    - Ethernet → electrical signals.
        
    - Fiber → light pulses.
        
- The signals travel across cables/air until they reach the router, then hop across the Internet.
    

**What happens here:** The **actual 1s and 0s** move across the wire/wireless medium.

## Examples

### 📨 Example 1 – Sending an Email

- **Layer 7 (Application):** You compose an email in Gmail or Outlook → uses **SMTP** to send the message.
    
- **Layer 6 (Presentation):** If the email contains attachments, they may be **encoded or compressed** (e.g., Base64, ZIP). Encryption (TLS) may also protect the transfer.
    
- **Layer 5 (Session):** A session is established with the mail server so your email doesn’t get cut off halfway.
    
- **Layer 4 (Transport):** **TCP** ensures the email is delivered reliably to the mail server on port **25** or **587**.
    
- **Layer 3 (Network):** The email is routed across networks using **IP addresses**.
    
- **Layer 2 (Data Link):** Each hop across switches/routers uses **MAC addresses**.
    
- **Layer 1 (Physical):** Actual bits travel through Wi-Fi, copper, or fiber.
    

---

### 📱 Example 2 – Making a WhatsApp Call

- **Layer 7:** WhatsApp app uses **VoIP protocols** to set up the call.
    
- **Layer 6:** Audio is **compressed and possibly encrypted** (end-to-end encryption).
    
- **Layer 5:** A session is established to keep the call active.
    
- **Layer 4:** **UDP** is used instead of TCP, since speed is more important than perfect reliability in voice calls.
    
- **Layer 3:** Packets containing voice data are routed across the Internet with IP.
    
- **Layer 2:** Frames move from your phone to your router and onward.
    
- **Layer 1:** Radio waves carry the call over 4G/Wi-Fi.
    

---

### 🎮 Example 3 – Online Gaming

- **Layer 7:** The game client communicates with the game server (e.g., Fortnite, Call of Duty).
    
- **Layer 6:** Game data may be encoded/compressed for faster transmission.
    
- **Layer 5:** A session is established between your console/PC and the game server.
    
- **Layer 4:** **UDP** is often used for real-time updates (position, movement), while **TCP** may handle chat or purchases.
    
- **Layer 3:** Player actions are encapsulated in packets with source/destination IPs.
    
- **Layer 2:** Frames are exchanged via your local network.
    
- **Layer 1:** Bits travel through your Internet connection to the server.
    

---

### 📂 Example 4 – File Sharing (SMB or FTP)

- **Layer 7:** You use FTP/SMB to download a file.
    
- **Layer 6:** Data may be encrypted (SFTP, FTPS).
    
- **Layer 5:** The file transfer session stays alive until the file is fully downloaded.
    
- **Layer 4:** **TCP** guarantees file integrity and retransmits if a packet is lost.
    
- **Layer 3:** The file is split into packets with IP addresses.
    
- **Layer 2 & 1:** Frames and signals deliver data across the LAN/Internet.