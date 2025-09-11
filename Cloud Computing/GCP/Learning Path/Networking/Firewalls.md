# Firewalls in-depth

A firewall is a network security device designed to monitor, filter, and control incoming and outgoing network traffic based on predetermined security rules. The primary purpose of a firewall is to establish a barrier between a trusted internal network and untrusted external networks.

Firewalls come in both hardware and software forms, and they work by inspecting data packets and determining whether to allow or block them based on a set of rules. Organizations can configure these rules to permit or deny traffic based on various criteria, such as source and destination IP addresses, port numbers, and protocol type. 

## Understanding firewalls and network security 

Firewalls are the bedrock of network security, shielding the network from unauthorized access. They prevent bad actors — hackers, bots, and other threats — from overloading or infiltrating a private network to steal sensitive data.

### Traditional Firewalls

In the past, firewalls focused on creating a **secure perimeter** around a network. They worked like digital walls—if you weren’t authorized, you simply couldn’t get inside the private network. This approach was effective when most resources were located in one place, like an office.

### Modern Challenges

Today’s networks are very different:

- **Cloud computing** means data and services often live outside the traditional perimeter.
    
- **Remote and hybrid work** make it harder to rely only on perimeter defenses.
    
- **Advanced cyber threats** can bypass simple firewall rules.
    

Because of this, firewalls are no longer enough by themselves—they need to be part of a **layered security strategy** that includes other defenses.

### The Future of Firewalls

Modern firewalls are much smarter. Many now use **AI, machine learning, and threat intelligence** to detect and stop sophisticated attacks. These **next-generation firewalls (NGFWs)** combine the strengths of traditional firewalls with new features like:

- Deep inspection of traffic.
    
- Detection of unusual behavior.
    
- Protection across cloud, on-premises, and hybrid environments.

## What Does A Firewall Do?

Firewalls protect against malicious traffic. They’re strategically positioned at the network edge or in a data center, allowing them to closely monitor anything attempting to cross this boundary.

This visibility also allows a network firewall to granularly [inspect and authenticate](https://www.fortinet.com/resources/cyberglossary/what-does-a-firewall-do) data packets in real time. This involves checking the data packet against predefined criteria to determine whether it poses a threat. If it fails to meet the criteria, the firewall blocks it from entering or leaving the network.

Firewalls regulate both inbound and outbound traffic, protecting the network from:

- **External threats** such as viruses, backdoors, phishing emails, and denial-of-service (DoS) attacks. Firewalls filter incoming traffic flows, preventing unauthorized access to sensitive data and thwarting potential malware infections.  
      
    
- **Insider threats** like known bad actors or risky applications. A firewall can enforce rules and policies to restrict certain types of outgoing traffic, which helps identify suspicious activity and mitigate data exfiltration.

### Firewall vs antivirus explained

What’s the difference between firewall and antivirus software? Firewalls focus on controlling network traffic and preventing unauthorized access. By contrast, antivirus programs target and eliminate threats at the device level. More specifically, their key differences include:

- **Scope:** Antivirus software is primarily an endpoint solution, meaning it’s installed on an individual device. Firewalls mainly deploy at the network level, but some organizations install hosted firewalls directly on an endpoint for extra protection.  
      
    
- **Functionality:** Firewalls monitor traffic, blocking malicious data before it enters the network (or endpoint). Antivirus tools scan the local environment for signs of malware, ransomware, and other infectious attacks.

Enterprises normally deploy both firewalls and antivirus programs. As complementary solutions, they each provide essential protective layers for safeguarding business assets.

## Firewall Functions: NAT And VPN

Network Address Translation (NAT) and Virtual Private Network (VPN) are two distinct technologies, each with its own set of functions related to network security and connectivity. While NAT is primarily associated with address translation for routing purposes, VPNs are used to create secure, encrypted connections over the internet.

### NAT

NAT changes the destination or source addresses of data packets as they pass through a firewall. This allows multiple devices to connect to the internet using the same IP address, which helps protect the private network from direct exposure to external threats.

In an office environment, each employee uses their own computer or mobile device to access the internet for browsing, emailing, and accessing cloud services. Despite each device having its own private IP address within the company's internal network, all outbound traffic appears to external networks as originating from the same public IP address assigned to the company. As a result, it’s harder for potential attackers to identify and target individual devices.

**Key Functions of NAT:**

- Allows multiple devices on a private network to share a **single public IP address**.
    
- Prevents direct exposure of private devices to the internet.
    
- Adds a layer of **anonymity and protection** since external entities only see the shared public IP.

**Example in Action:**  
In an office, every employee’s device has a **private IP address** (e.g., `192.168.x.x`). When they browse the internet, send emails, or access cloud services, NAT translates those requests so they all appear to come from the company’s **public IP address**. This makes it more difficult for attackers to target specific internal devices.

### VPN

A VPN is a type of [proxy server](https://www.fortinet.com/resources/cyberglossary/proxy-server). Therefore, it serves as a barrier between a computer or network and the internet, receiving all web requests before forwarding them to the network.

VPNs are common and extend the private network across a public one, such as the internet. This allows users to securely transmit data as if their devices were directly connected to the private network. The connection establishes an encrypted tunnel between remote devices and the corporate network, enabling secure access.

**This function is especially useful in a hybrid environment**. Remote employees can leverage VPNs to access corporate networks and critical applications regardless of where or how they’re working.

**Key Functions of VPNs:**

- Encrypts communications, making intercepted data unreadable.
    
- Extends a **private network across a public one** (like the internet).
    
- Allows remote users to securely access corporate systems and applications.
    

**Example in Action:**  
Remote employees working from home connect to the company’s VPN. The VPN encrypts their internet traffic and makes it appear as if they’re working **inside the corporate network**, giving them secure access to internal systems and sensitive resources.

## The evolution of firewalls

![[fws-001.png]]

Firewalls have evolved through four distinct phases:

1. **First-generation firewalls** began in 1989 with the packet filtering approach. These firewalls examine individual data packets, making decisions to allow or block them based on predefined rules. However, these were unable to identify if those packets contained malicious code (i.e., malware).  
      
    
2. **Second-generation firewalls** began in the early 2000s. Otherwise known as [stateful firewalls](https://www.fortinet.com/resources/cyberglossary/stateful-firewall), these track the state of active connections. By observing network traffic, they use context to identify and act on suspicious behavior. Unfortunately, this generation also has its limitations.  
      
    
3. **Third-generation firewalls** emerged in the latter half of the early 2000s. Often called proxy firewalls or application-level gateways, these act as intermediaries between a client and server, forwarding requests and filtering responses.  
      
    
4. **Fourth-generation firewall**, also known as next-generation firewall (NGFW), started in 2010. NGFWs combine traditional capabilities with new, advanced features such as intrusion prevention (IPS), application-layer filtering, and advanced threat detection.

Although each generation improved upon the last, many earlier iterations are still in use today. Let’s review the [benefits of each firewall](https://www.fortinet.com/resources/cyberglossary/benefits-of-firewall) in more detail.

## Type of Firewalls

### Stateless Firewalls

A **stateless firewall** is one of the simplest types of firewalls. It works at the **transport layer**. Rather than store information about the state of the network connection, it inspects traffic on a packet-by-packet basis.

#### How It Works

- Each data packet is inspected individually.
    
- The firewall looks only at the **packet header**, which contains details like:
    
    - Source and destination IP addresses.
        
    - Port numbers.
        
    - Protocol type.
        
- Based on **predefined rules**, the firewall either **allows** or **blocks** the packet.
    
- This process is known as **packet filtering**.

#### Strengths of Stateless Firewalls

- **Fast and efficient** — because they don’t track connection states.
    
- **Low cost** — simpler to implement and maintain.
    
- **Good for basic filtering** — effective against simple, well-defined threats.
    

#### Limitations

- **No session awareness:** They cannot track whether a packet is part of an established, legitimate session. For example, they may allow packets that don’t match any valid request.
    
- **Header-only inspection:** They only check header information, not the **payload (content)** of the packet. This means malware hidden inside the payload can pass through undetected.
    
- **Limited protection:** They cannot detect advanced attacks, like spoofing or payload-based exploits.

### Stateful Firewall

A **stateful firewall** is more advanced than a stateless one. Instead of inspecting packets individually, it keeps track of the **state of active network connections**. This allows it to make smarter decisions based on the **context** of traffic.

#### How It Works

- Maintains a **state table** that records details of ongoing sessions (such as source/destination IPs, ports, and connection status).
    
- Inspects not only the packet header, but also the **sequence and context** of packets in a connection.
    
- Can verify whether an incoming packet belongs to an existing, legitimate connection or is suspicious.

#### Strengths of Stateful Firewalls

- **Context-aware:** Understands the difference between new, established, and invalid connections.
    
- **Deeper inspection:** Looks beyond simple header rules to evaluate traffic behavior.
    
- **Better threat detection:** Can identify anomalies, such as unexpected packets or unusual patterns.

#### Limitations

- **Performance impact:** Because they track sessions and analyze context, they use more memory and processing power.
    
- **Vulnerabilities:** Attackers may exploit trusted protocols or trick the firewall into allowing malicious traffic by disguising it as part of a legitimate session.
    
- **Complexity:** More advanced configuration is required compared to stateless firewalls.

#### Example

If a user requests a web page, a **stateful firewall** remembers that request and only allows the related responses back in. If random packets pretending to be part of that session arrive, the firewall can block them as **illegitimate**.

### Application-Level Gateways (Proxy Firewalls)

An **application-level gateway (ALG)**, also called a **proxy firewall**, acts as a middleman between internal users and external services. Instead of allowing direct communication, the proxy **receives requests, inspects them, and forwards them on behalf of the user**.

#### How They Work

- Operate at **Layer 7 (Application Layer)** of the OSI model — the layer closest to the end user.
    
- Intercept all incoming and outgoing traffic.
    
- Apply **granular security rules** based on the type of application (e.g., web, email, messaging).
    
- Provide **deep packet inspection** to analyze not only headers but also the **contents** of data packets.
    

#### Capabilities

Application-level gateways can:

- Perform **packet filtering** and **application-level inspection**.
    
- Enforce **user authentication** before granting access.
    
- Apply **URL filtering** (block access to malicious or inappropriate sites).
    
- Detect and block **malicious payloads** hidden inside legitimate-looking traffic.
    

#### Example

If a user wants to visit a website, the request first goes to the proxy firewall. The firewall checks the URL, content, and policies. If it’s safe, the request is forwarded; if not, it’s blocked.


### Web Application Firewalls

A **Web Application Firewall (WAF)** is a specialized firewall designed to protect **web applications** from attacks that exploit vulnerabilities in websites or web services. Unlike traditional firewalls that focus on **network traffic (IP, ports, protocols)**, a WAF inspects **HTTP/HTTPS requests and responses** at the **application layer (Layer 7)**.

#### How a WAF Works

- Monitors all traffic between a **client (browser)** and a **web server**.
    
- Uses **rules and policies** to detect malicious activity, such as abnormal requests or patterns.
    
- Can **block, allow, or log** requests depending on the defined security policy.
    

####  What WAFs Protect Against

WAFs defend against **web-specific threats**, including:

- **SQL Injection (SQLi):** Attackers inserting malicious database queries.
    
- **Cross-Site Scripting (XSS):** Injecting scripts into webpages viewed by other users.
    
- **Cross-Site Request Forgery (CSRF):** Forcing a user to perform unintended actions.
    
- **Session hijacking:** Stealing or abusing session cookies.
    
- **Malicious bots and DDoS attacks** targeting web apps.
    

####  Deployment Options

- **Network-based WAFs:** Installed on-premises; fast but expensive.
    
- **Host-based WAFs:** Integrated into the web application’s software stack; flexible but resource-intensive.
    
- **Cloud-based WAFs:** Delivered as a service (e.g., AWS WAF, Azure WAF, Cloudflare WAF); easy to deploy and scalable.
    

####  Example in Action

Suppose an attacker tries to inject SQL code into a login form (`' OR '1'='1`).

- A **traditional firewall** wouldn’t catch this because it looks like normal HTTP traffic.
    
- A **WAF**, however, understands web application logic and blocks the request before it reaches the database.

### Next-Generation Firewalls (NGFWs)

A **Next-Generation Firewall (NGFW)** is the evolution of traditional firewalls, designed to defend businesses against today’s **sophisticated cyber threats**. NGFWs combine the core features of earlier firewalls with **advanced security capabilities** that address modern attack techniques.

#### Core Advanced Features of NGFWs

1. **Deep Packet Inspection (DPI):**
    
    - Goes beyond simple header checks.
        
    - Analyzes the **contents** of data packets as they pass through.
        
    - Detects hidden malware, exploits, and policy violations.
        
2. **Intrusion Prevention System (IPS):**
    
    - Monitors traffic in **real time**.
        
    - Identifies, blocks, and automatically responds to malicious activities.
        
3. **Data Loss Prevention (DLP):**
    
    - Prevents **accidental or intentional leaks** of sensitive data.
        
    - Ensures compliance with data protection policies.

#### Extended Capabilities

Modern NGFWs can unify multiple layers of protection and adapt to complex IT environments. Examples include:

- **IoT Security:** Detects and protects against rogue, shadow IT, or BYOD devices.
    
- **Network Sandboxing:** Runs suspicious files in an isolated environment to safely observe behavior.
    
- **Zero-Trust Network Access (ZTNA):** Grants access based on **user identity, device posture, and context** instead of trusting by default.
    
- **Operational Technology (OT) Security:** Protects industrial systems and SCADA applications with specialized inspection.
    
- **DNS Security:** Blocks and monitors **DNS-layer attacks**, like tunneling or domain hijacking.
    
- **SD-WAN Integration:** Provides secure and optimized wide-area networking with:
    
    - Dynamic path selection based on application/business policies.
        
    - Centralized management of VPNs and appliances.
        
    - Zero-touch provisioning for easy deployment.


### AI-Powered Firewalls

An **AI-powered firewall** is the next step in firewall evolution. It integrates **artificial intelligence (AI)** and **machine learning (ML)** to go beyond traditional rule-based filtering, making network defense more **adaptive, intelligent, and proactive**.

### Comparison

| Firewall Type                                  | OSI Layer / Focus                        | How It Works                                                                      | Key Strengths                                                                    | Limitations                                                            |
| ---------------------------------------------- | ---------------------------------------- | --------------------------------------------------------------------------------- | -------------------------------------------------------------------------------- | ---------------------------------------------------------------------- |
| **Stateless Firewall**                         | Transport Layer (Layer 4)                | Inspects **each packet individually** based on headers (IP, ports, protocol)      | Fast, simple, low-cost                                                           | No session awareness, cannot inspect payload, limited threat detection |
| **Stateful Firewall**                          | Transport Layer (Layer 4)                | Tracks **connection states** and context of packets                               | Context-aware, better detection of unauthorized sessions                         | More resource-intensive, can be tricked by attackers                   |
| **Application-Level Gateway (Proxy Firewall)** | Application Layer (Layer 7)              | Acts as a **middleman**, inspects and forwards requests for multiple applications | Deep inspection, user authentication, URL filtering                              | Can slow down traffic, complex setup                                   |
| **Web Application Firewall (WAF)**             | Application Layer (Layer 7, Web Traffic) | Protects **web applications** specifically, inspecting HTTP/HTTPS traffic         | Blocks SQLi, XSS, CSRF, DDoS, bot attacks                                        | Only protects web apps, doesn’t replace network firewall               |
| **Next-Generation Firewall (NGFW)**            | Network + Application Layers             | Combines **traditional firewall + IPS + DPI + DLP + advanced features**           | Unified enterprise protection, IoT/OT security, ZTNA, SD-WAN support             | Resource-intensive, complex deployment                                 |
| **AI-Powered Firewall**                        | Network + Application Layers             | Uses **AI/ML to analyze traffic, detect anomalies, automate policies**            | Real-time adaptive protection, predictive threat detection, reduces human errors | Requires continuous training, sophisticated infrastructure             |
## General Information About Firewalls

### 📜 Firewall Rules

Rules are like “if-then” conditions. Each rule typically checks:

1. **Source** → Where the traffic comes from (IP address, subnet, etc.).
    
2. **Destination** → Where the traffic is going (IP, port, service).
    
3. **Protocol** → Type of communication (TCP, UDP, ICMP, etc.).
    
4. **Action** → Allow (permit) or Deny (block).
    

**👉 Example Rule:**

- **Allow** traffic from `192.168.1.0/24` to port `443` (HTTPS) on the company’s web server.
    
- **Deny** everything else.

### 🌍 Firewall Placement

- **Network edge** → Between internal network and internet.
    
- **Between subnets** → To segment departments or workloads.
    
- **On hosts** → Host-based firewalls (like Windows Defender Firewall, iptables in Linux).

### 🚦 Common Ports to Know (often controlled by firewalls)

- **80 / 443** → HTTP / HTTPS
    
- **22** → SSH
    
- **25 / 587** → SMTP (email)
    
- **53** → DNS
    
- **1433 / 3306** → SQL Server / MySQL

## Firewalls command in Linux

