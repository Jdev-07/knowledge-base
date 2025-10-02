A Virtual Private Cloud network is a virtual version of a traditional and physical network. The VPC provides connectivity to VM instances, connects to on-premises networks by using Cloud VPN tunnels and VLAN attachments and distributes the traffic from Google Cloud external load balancer to backends. 

A project can contain multiple VPC networks unless you specify otherwise with an organizational policy. 

### Networks and subnets

The terms subnet and subnetwork are synonymous.
A subnet is not the same thing as a VPC network. 

### Specifications 

- VPC networks, including their associated routes and firewalls rules, are global resources. 
- Subnets are regional resources
- Traffic to and from instances can be controlled with network firewall rules but rules are implemented on the VMs themselves, so traffic can be controlled as it arrives or leaves the VMs.
- Resources within the same VPC network can communicate each other. 
- Instances with internal IPv4 or IPv6 addresses can communicate with Google APIs and services. 
- Network administration can be secured by using IAM
- Organizations can use a Shared VPC to connect resources from different projects.
- Using VPC Network peering you can connect VPC networks in different projects or organizations. 
- VPC networks can securely connect to hybrid environments by using Cloud VPN or Cloud Interconnect
- VPC networks support GRE traffic, including traffic on Cloud VPN and Cloud Interconnect. However do not support GRE for Cloud NAT or for forwarding rules for load balancing and protocol forwarding. 
- VPC networks support ipv4 and ipv6 unicast addresses but broadcast or multicast addresses. 

Example

![[vpc-001.png]]

Because subnets are regional resources, instances can have their network interfaces associated with any subnet in the same region that contains their zones.

### Organization policy constraints 

Each new project starts with a default VPC Network, but it can be disable by creating an organization policy.

Also, you can disable some IPv6 configurations:
- Disable VPC External IPv6 usage
- Disable VPC Internal IPv6 usage
- Disable All IPv6 usage

## Subnets

There are two type of networks based on its subnet creation mode

- Auto mode VPC network: in this mode a subnet on each region is automatically created. The subnets use the IPv4 ranges that fit with the 10.128.0.0 CIDR block. If a new Google Cloud region added, a subnet is created. 
- Custom mode VPC Network: In this mode, no subnets are automatically added. The user has the complete control. 
- You can switch from auto mode to custom, but not the other way around. 

### Default network

Unless you specify otherwise, new projects start with a default network in auto mode. 

### Considerations 


Auto mode VPC networks are easy to set up and use, it will fit with these scenarios: 

- If you need a subnet on each google region available 
- If you want to avoid overlapping with IP ranges. 

However, If you want to have more control and it is a prod environment, use the custom mode would be a better option:

- If you do not want to have a subnet on all regions
- As new regions become available  could overlap IP addressees used by manually created subnets
- If you want to have the full control, including the subnet creation and IP address range selection.
- If you plan to connect a VPC network to another network because the auto mode VPC network use the same predefined range of IP addresses.
- Also if you want to use IPv6 ranges 

**About IPv4 ranges**

- Each subnet has a primary IPv4 address range
- Each primary or secondary IPv4 range must be a unique valid CIDR block. 
- IPv4 subnets do not need to form a predefined contiguous CIDR block.
- When creating a subnet in custom mode, you choose what IPv4 range to use. 
- There are four unusable IP addresses in every primary IPv4 subnet range. 
- The subnets automatically created in auto mode VPC network use ranges inside of the 10.128.0.0/9

**About IPv6 ranges**

- When creating a subnet in a custom mode VPC network, you choose whether the subnet is configured with an internal (ULAs) IPv6 subnet range or external (GUAs)
- Auto mode VPC and legacy networks do not support IPv6. however you can switch to custom mode and start using IPv6.

## Routes and firewalls rules

- Routes define paths for packets leaving instances (egress traffic)
- Each VPC network has an associated dynamic routing mode that control the behaviors of all of its Cloud Routers. Cloud Routers manage BGP sessions for Google Cloud products. 

**Route advertisements and internal IP addresses**

- If you connect VPC networks using VPC network peering, subnets ranges using IPv4 are always exchanged
- Global internal IPv4 addresses are never exchanged using peering.  

When connecting a VPC network to another network, such as on premise network you can:
- Advertise the VPC network's internal IP addresses to another network 
- Take extra care when advertising privately used public IP addresses to another network (such as an on-premises network), especially when the other network can advertise those public IP addresses to the internet.

**Firewall rules**

Both hierarchical firewall policies and VPC firewall rules apply to packets sent to and from VM instances and resources that depends on VMs. Both types of firewall rules control traffic even if it is between VMs in the same network.  

## Communications  and access

**Communication within the network**

- The system-defined subnet routes define the paths for sending traffic among instances within the network. However, should configure appropriate firewalls rules because every network  has a deny firewall rule for ingress traffic. 
- You must create higher priority ingress firewall rules to allow instances communicate each other. 
- The default network includes several firewall rules in addition to the implied ones that permits instance-to-instance communication within the networks. This default network also comes with some ingress rules allowing protocols such as RDP and SSH.

**Internet access requirements**

There are some criteria that must satisfied for an instance to have outgoing internet access.

- The network must have a valid internet gateway route or custom route whose destination IP range is the most general (0.0.0.0 or ::). This route defines the path to internet.
- Firewall rules must allow egress traffic from 
- Also, must meet one of this: The instance must have an external IP address or the instance must be able to use Cloud NAT.

**Communications and access for App Engine**

VPC firewall rules apply to resources running in the VPC networks. But for App Engine instances works as follows

- App Engine standard environment: Only App Engine firewall rules apply to ingress traffic. 
- App Engine Flexible environment: Both App Engine and VPC firewall rules apply to ingress traffic. 

**Traceroute to external IP addresses**

- Hops that are inside of Google's network might be hidden  when you send packets packets from Compute Engine instances to destinations on the internet. So `traceroute` and `mtr` might provide incomplete results.
- The number of hidden hops varies based on the instance's Network Service tier. However, missing hops from a `traceroute` or `mtr` result don't mean that outbound traffic is dropped.
- There is no workaround for this behavior.

**Egress throughput limits**

- Network throughput information is available on the network bandwidth page. 

**Packet size**

- You can find information about packet size in Maximum transmission unit. 

**Supported protocols**

- **IPv4 data packets between VMs:** all IPv4 protocols.
- **IPv4 data packets between VMs and the internet:** the ICMP, IPIP, TCP, UDP, GRE, ESP, AH, and SCTP protocols.
- **IPv6 data packets between VMs _and_ between VMs and the internet:** the AH, ESP, GRE, ICMP, ICMPv6, IPIP, SCTP, TCP, and UDP protocols and the Destination Options and Fragments extension headers. However, placing the Destination Options header after the Fragment header in an IPv6 data packet is not supported.
- **Protocol forwarding:** the AH, ESP, GRE, ICMP, ICMPv6, SCTP, TCP, and UDP protocols
