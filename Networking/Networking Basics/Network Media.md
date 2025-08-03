
Data is transmitted across a network on media. The media provides the channel over which the message travels from source to destination.

Modern networks primarily use three types of media to interconnect devices, as shown in the figure:

- **Metal wires within cables** - Data is encoded into electrical impulses.
- **Glass or plastic fibers within cables (fiber-optic cable)** - Data is encoded into pulses of light.
- **Wireless transmission** - Data is encoded via modulation of specific frequencies of electromagnetic waves.

The four main criteria for choosing network media are these:

- What is the maximum distance that the media can successfully carry a signal?
- What is the environment in which the media will be installed?
- What is the amount of data and at what speed must it be transmitted?
- What is the cost of the media and installation?

## Common Network Cables

The three most common network cables are twisted-pair, coaxial cable, and fiber-optic cable.

### Twisted-Pair cable

Ethernet technology generally uses twisted-pair cables to interconnect devices. Because Ethernet is the foundation for most local networks, twisted-pair is the most commonly encountered type of network cabling.

In twisted-pair, wires are grouped in pairs and twisted together to reduce interference. The pairs of wires are colored so that you can identify the same wire at each end. Typically, in each pair, one of the wires is a solid color and its partner is the same color striped onto a white background.

### Coaxial Cable

Coaxial was one of the earliest types of network cabling developed. Coaxial cable is the kind of copper cable used by cable TV companies. It is also used for connecting the various components which make up satellite communication systems. Coaxial cable has a single rigid copper core that conducts the signal. This core is typically surrounded by a layer of insulation, braided metal shielding, and a protective jacket. It is used as a high-frequency transmission line to carry high-frequency or broadband signals.

### Fiber-optic cable

Fiber-optic cable can be either glass or plastic with a diameter about the same as a human hair and it can carry digital information at very high speeds over long distances. Because light is used instead of electricity, electrical interference does not affect the signal. Fiber-optic cables have many uses as well as communications. They are also used in medical imaging, medical treatment, and mechanical engineering inspection.

They have a very high bandwidth, which enables them to carry very large amounts of data. Fiber is used in backbone networks, large enterprise environments, and large data centers. It is also used extensively by telephone companies.

### **1. Encapsulation (Sending Data)**

**Path:** _Application → Transport → Internet → Network Access → Physical Network_

| **Layer**             | **Action**                                                                            | **Protocol Example**         | **Data Unit Name**                     |
| --------------------- | ------------------------------------------------------------------------------------- | ---------------------------- | -------------------------------------- |
| **Application Layer** | Data generated (e.g., HTTP request, email).                                           | HTTP, FTP, SMTP              | **Message/Data**                       |
| **Transport Layer**   | Splits data into **segments**; adds TCP/UDP header (ports, sequence numbers).         | TCP (reliable) or UDP (fast) | **Segment (TCP)** / **Datagram (UDP)** |
| **Internet Layer**    | Adds IP header (source/dest IP addresses, TTL).                                       | IPv4/IPv6                    | **Packet**                             |
| **Network Access**    | Encapsulates into **frames**; adds MAC addresses (source/dest) and FCS (error check). | Ethernet, Wi-Fi              | **Frame**                              |
| **Physical Layer**    | Converts frames to **bits**; transmits as electrical/optical signals.                 | Cable, Fiber                 | **Bits**                               |

---

### **2. Decapsulation (Receiving Data)**

**Path:** _Physical Network → Network Access → Internet → Transport → Application_

|**Layer**|**Action**|
|---|---|
|**Physical Layer**|Receives bits; converts to frames.|
|**Network Access**|Checks FCS for errors; strips MAC header to extract **packet**.|
|**Internet Layer**|Removes IP header; forwards **segment** to Transport Layer based on IP.|
|**Transport Layer**|Uses TCP/UDP header to reassemble segments into **data**; sends to correct app via port numbers.|
|**Application Layer**|Delivers data to the receiving application (e.g., web browser).|
