## The Client-Server Relationship

Every day, we use the services available over networks and the internet to communicate with others and to perform routine tasks. We rarely think of the servers, clients, and networking devices that are necessary in order for us to receive an email, update our status on social media, or shop for the best bargains in an online store. Most of the commonly used internet applications rely on complicated interactions between various servers and clients.

The term server refers to a host running a software application that provides information or services to other hosts that are connected to the network. A well-known example of an application is a web server. There are millions of servers connected to the internet, providing services such as web sites, email, financial transactions, music downloads, etc. A crucial factor to enable these complex interactions to function is that they all use agreed upon standards and protocols.

### URI, URN and URL

Web resources and web services such as RESTful APIs are identified using a Uniform Resource Identifier (URI). A URI is a string of characters that identifies a specific network resource. As shown in the figure, a URI has two specializations:

- **Uniform Resource Name (URN)** - This identifies only the namespace of the resource (web page, document, image, etc.) without reference to the protocol.
- **Uniform Resource Locator (URL)** - This defines the network location of a specific resource on the network. HTTP or HTTPS URLs are typically used with web browsers. Other protocols such as FTP, SFTP, SSH, and others can be used as a URL. A URL using SFTP might look like: sftp://sftp.example.com.

These are the parts of a URI, as shown in the figure:

- **Protocol/scheme** - HTTPS or other protocols such as FTP, SFTP, mailto, and NNTP
- **Hostname** - w​ww.example.com
- **Path and file name** - /author/book.html
- **Fragment** - #page155

### Parts of a URI

![[network-019.png]]

## Network Application Services

### Common Network Application Services

What are the most common internet services that you use on a regular basis? For most people, the list includes services such as internet searches, social media sites, video and audio streaming, on-line shopping sites, email, and messaging. Each of these services relies on protocols from the TCP/IP protocol suite to reliably communicate the information between the clients and the servers.

Some of the most common servers that provide these services are shown in the figure. A brief description of each service is shown in the table.

![[network-020.png]]![[network-021.png]]

## Domain Name System

## Web Clients and Servers

When a web client receives the IP address of a web server, the client browser uses that IP address and port 80 to request web services. This request is sent to the server using the Hypertext Transfer Protocol (HTTP).

When the server receives a port 80 request, the server responds to the client request and sends the web page to the client. The information content of a web page is encoded using specialized 'mark-up' languages. The HyperText Markup Language (HTML) coding tells the browser how to format the web page and what graphics and fonts to use. HTML is the most commonly used language.

The HTTP protocol is not a secure protocol; information could easily be intercepted by other users as data is sent over the network. In order to provide security for the data, HTTP can be used with secure transport protocols. Requests for secure HTTP are sent to port 443. These requests use **https** in the site address in the browser, rather than **http**.

There are many different web servers and web clients available. The HTTP protocol and HTML standards make it possible for these servers and clients from many different manufacturers to work together seamlessly.

## FTP Clients and Servers

### File Transfer Protocol

In addition to web services, another common service used across the internet is one that allows users to transfer files.

The File Transfer Protocol (FTP) provides an easy method to transfer files from one computer to another. A host running FTP client software can access an FTP server to perform various file management functions including file uploads and downloads.

The FTP server enables a client to exchange files between devices. It also enables clients to manage files remotely by sending file management commands such as delete or rename. To accomplish this, the FTP service uses two different ports to communicate between client and server.

The example in the figure illustrates how FTP operates. To begin an FTP session, control connection requests are sent to the server using destination TCP port 21. When the session is opened, the server uses TCP port 20 to transfer the data files.

FTP client software is built into computer operating systems and into most web browsers. Stand-alone FTP clients offer many options in an easy-to-use GUI-based interface.

![[network-022.png]]
## Virtual Terminals

### Telnet

Long before desktop computers with sophisticated graphical interfaces existed, people used text-based systems which were often just display terminals physically attached to a central computer. After networks became available, people needed a way to remotely access the computer systems in the same manner that they did with the directly-attached terminals.

Telnet was developed to meet that need. Telnet dates back to the early 1970s and is among the oldest of the application layer protocols and services in the TCP/IP suite. Telnet provides a standard method of emulating text-based terminal devices over the data network. Both the protocol itself and the client software that implements the protocol are commonly referred to as Telnet. Telnet servers listen for client requests on TCP port 23.

Appropriately enough, a connection using Telnet is called a virtual terminal (vty) session, or connection. Rather than using a physical device to connect to the server, Telnet uses software to create a virtual device that provides the same features of a terminal session with access to the server’s command line interface (CLI).

In the figure, the client has remotely connected to the server via Telnet. The client is now able to execute commands as if it were locally connected to the server.

**Note:** Telnet is not considered to be a secure protocol. SSH should be used in most environments instead of Telnet. Telnet is used in several examples in this course for simplicity of configuration.

![[knowledge-base/Images/Networking/network-023.png]]

### Security Issues with Telnet

After a Telnet connection is established, users can perform any authorized function on the server, just as if they were using a command line session on the server itself. If authorized, they can start and stop processes, configure the device, and even shut down the system.

Although the Telnet protocol can require a user to login, it does not support transporting encrypted data. All data exchanged during Telnet sessions is transported as plaintext across the network. This means that the data can be easily intercepted and understood.

The Secure Shell (SSH) protocol offers an alternate and secure method for server access. SSH provides the structure for secure remote login and other secure network services. It also provides stronger authentication than Telnet and supports transporting session data using encryption. As a best practice, network professionals should always use SSH in place of Telnet, whenever possible.

The figure illustrates how SSH is more secure than Telnet. Notice how the data captured by the hacker when Telnet is used is clearly readable while the data captured when SSH is used is encrypted and therefore more secure.

![[network-024.png]]

## Email and messaging 

### Email Clients and Servers

Email is one of the most popular client/server applications on the internet. Email servers run server software that enables them to interact with clients and with other email servers over the network.

Each mail server receives and stores mail for users who have mailboxes configured on the mail server. Each user with a mailbox must then use an email client to access the mail server and read these messages. Many internet messaging systems use a web-based client to access email. Examples of this type of client include Microsoft 365, Yahoo, and Gmail.

Mailboxes are identified by the format: **user@c​ompany.domain**

Various application protocols used in processing email include SMTP, POP3, and IMAP4.

![[network-025.png]]

### Email Protocols

**Simple Mail Transfer Protocol (SMTP)**

SMTP is used by an email client to send messages to its local email server. The local server then decides if the message is destined for a local mailbox or if the message is addressed to a mailbox on another server.

If the server has to send the message to a different server, SMTP is used between those two servers as well. SMTP requests are sent to port 25.


**Post Office Protocol (POP3)**

A server that supports POP clients receives and stores messages addressed to its users. When the client connects to the email server, the messages are downloaded to the client. By default, messages are not kept on the server after they have been accessed by the client. Clients contact POP3 servers on port 110.

**Internet Message Access Protocol (IMAP4)**

A server that supports IMAP clients also receives and stores messages addressed to its users. However, unlike POP, IMAP keeps the messages in the mailboxes on the server, unless they are deleted by the user. The most current version of IMAP is IMAP4 which listens for client requests on port 143.

Many different email servers exist for the various network operating system platforms.

### Text Messaging

Text messaging, shown in the figure, is one of the most popular communication tools in use today. In addition, text messaging software is built into many online applications, smartphone apps, and social media sites.

![[network-026.png]]

Both clients can simultaneously send and receive messages.

Text messages may also be called instant messages, direct messages, private messages, and chat messages. Text messaging enables users to communicate or chat over the internet in real-time. Text messaging services on a computer are usually accessed through a web-based client that is integrated into a social media or information sharing site. These clients usually only connect to other users of the same site.

There are also a number of standalone text message clients such as Cisco Webex Teams, Microsoft Teams, WhatsApp, Facebook Messenger, and many others. These applications are available for a wide variety of operating systems and devices. A mobile version is typically offered. In addition to text messages, these clients support the transfer of documents, video, music, and audio files.

### Internet Phone Calls

Making telephone calls over the internet is becoming increasingly popular. An internet telephony client uses peer-to-peer technology similar to that used by instant messaging, as shown in the figure. IP telephony makes use of Voice over IP (VoIP) technology, which converts analog voice signals into digital data. The voice data is encapsulated into IP packets which carry the phone call through the network.

When the IP phone software has been installed, the user selects a unique name. This is so that calls can be received from other users. Speakers and a microphone, built-in or separate, are required. A headset is frequently plugged into the computer to serve as a phone.

Calls are made to other users of the same service on the internet, by selecting the username from a list. A call to a regular telephone (landline or cell phone) requires using a gateway to access the Public Switched Telephone Network (PSTN). Depending on the service, there may be charges associated with this type of call. The protocols and destination ports used by internet telephony applications can vary based on the software.

