The internet is one giant network that consists of many, many small networks within itself. 

The internet is made up of many small networks all joined together. These small networks are called private networks, where networks connecting these small networks are called public networks.

A network can be private or public. 

## Identifying a Devices on a Network

To communicate and maintain order, devices must be both identifying and identifiable on a network. Devices on a network are very similar to humans in the fact that we have two ways of being identified: our name and our fingerprints. On the other hand devices have two methods of identification:
* IP Address 
* A Media Access Control (MAC)
### IP Addresses 

An IP or Internet Protocol can be used as a way of identifying a host on a network for a period of time.

An IP address is a set of numbers that divided into four octets. The value of each octet will summarize to be the IP address of a device. This number is calculated using IP addressing and subnetting. 

IP follows a set of standards knows as protocols. These protocols are the backbone of networking and force many devices to communicate in the same language. 

A public address is used to identify the device on the internet, whereas a private address used to identify a device amongst other devices 

Two devices in the same private network will use the private IP addresses to communicate each other. However, data sent to the Internet from either of these devices will be identified by the same public IP address. Public IP addresses are given by your ISP.     

### MAC Addresses

Devices on a network will have a physical network interface. This network interface is assigned a unique address at the factory it was built at, called Media Access Control is a twelve-character split into two's and separated by a colon. The first six characters represent the company that made the NIC, and the last six is a unique number. 

However, the MAC can be faked or spoofed in a process known as spoofing. This spoofing occurs when a networked device pretends to identify as another using its MAC address. When this occurs, it can often break poorly implemented security designs that assume that devices talking on a network are trustworthy. Take the following scenario: A firewall is configured to allow any communication going to and from the MAC address of the administrator. If a device were to pretend or "spoof" this MAC address, the firewall would now think that it is receiving communication from the administrator when it isn't.

## Ping (ICMP)

Ping is one of the most fundamental network tools.  Pings uses ICMP (Internet Control Message Protocol) packets to determine the performance of a network connection between devices. 

The time taken for ICMP packets travelling between devices is measured by ping. This measuring is done using ICMP's echo packet and then ICMP's echo reply from the target device. 

```BASH
ping 192.168.1.1
```

We will dive into Networking Basics, the following topics are covered:

[[Intro to LAN]]
[[OSI Model]]
[[Packets and Frames]]]
[[Extending your Network]]