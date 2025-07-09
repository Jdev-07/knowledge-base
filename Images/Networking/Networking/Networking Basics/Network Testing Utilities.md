## Overview of TS commands

A number of software utility programs are available that can help identify network problems. Most of these utilities are provided by the operating system as command line interface (CLI) commands. The syntax for the commands may vary between operating systems.

Some of the available utilities include:

- **ipconfig** - Displays IP configuration information.
- **ping** - Tests connections to other IP hosts.
- **netstat** - Displays network connections.
- **tracert** - Displays the route taken to the destination.
- **nslookup** - Directly queries the name server for information on a destination domain.

### ipconfig

When a device does not get an IP address, or has an incorrect IP configuration, it cannot communicate on the network or access the internet. On Windows devices, you can view the IP configuration information with the **ipconfig** command at the command prompt. The **ipconfig** command has several options that are helpful including **/all**, **/release**, and **/renew**.

#### ipconfig

The **ipconfig** command is used to display the current IP configuration information for a host. Issuing this command from the command prompt will display the basic configuration information including IP address, subnet mask, and default gateway.

```
C:\> ipconfig

Windows IP Configuration

Ethernet adapter Ethernet:

   Media State . . . . . . . . . . . : Media disconnected

   Connection-specific DNS Suffix . :

Wireless LAN adapter Wi-Fi:

   Connection-specific DNS Suffix . : lan

   Link-local IPv6 Address . . . . . : fe80::a1cc:4239:d3ab:2675%6

   IPv4 Address. . . . . . . . . . . : 10.10.10.130

   Subnet Mask . . . . . . . . . . . : 255.255.255.0

   Default Gateway . . . . . . . . . : 10.10.10.1

C:\>

```

#### /all

The command **ipconfig /all** displays additional information including the MAC address, IP addresses of the default gateway, and the DNS servers. It also indicates if DHCP is enabled, the DHCP server address, and lease information.

How can this utility assist in the troubleshooting process? Without an appropriate IP configuration, a host cannot participate in communications on a network. If the host does not know the location of the DNS servers, it cannot translate names into IP addresses.

```

C:\> ipconfig/all

Windows IP Configuration

   Host Name . . . . . . . . . . . . : your-a9270112e3

   Primary Dns Suffix . . . . . . . :

   Node Type . . . . . . . . . . . . : Hybrid

   IP Routing Enabled. . . . . . . . : No

   WINS Proxy Enabled. . . . . . . . : No

   DNS Suffix Search List. . . . . . : lan

Ethernet adapter Ethernet:

   Media State . . . . . . . . . . . : Media disconnected

   Connection-specific DNS Suffix . :

   Description . . . . . . . . . . . : Realtek PCIe GBE Family Controller

   Physical Address. . . . . . . . . : 00-16-D4-02-5A-EC

   DHCP Enabled. . . . . . . . . . . : Yes

   Autoconfiguration Enabled . . . . : Yes

Wireless LAN adapter Wi-Fi:

   Connection-specific DNS Suffix . : lan

   Description . . . . . . . . . . . : Intel(R) Dual Band Wireless-AC 3165

   Physical Address. . . . . . . . . : 00-13-02-47-8C-6A

   DHCP Enabled. . . . . . . . . . . : Yes

   Autoconfiguration Enabled . . . . : Yes

   Link-local IPv6 Address . . . . . : fe80::a1cc:4239:d3ab:2675%6(Preferred)

   IPv4 Address. . . . . . . . . . . : 10.10.10.130(Preferred)

   Subnet Mask . . . . . . . . . . . : 255.255.255.0

   Lease Obtained. . . . . . . . . . : Wednesday, September 2, 2020 10:03:43 PM

   Lease Expires . . . . . . . . . . : Friday, September 11, 2020 10:23:36 AM

   Default Gateway . . . . . . . . . : 10.10.10.1

   DHCP Server . . . . . . . . . . . : 10.10.10.1

   DHCPv6 IAID . . . . . . . . . . . : 98604135

   DHCPv6 Client DUID. . . . . . . . : 00-01-00-01-1E-21-A5-84-44-A8-42-FC-0D-6F

   DNS Servers . . . . . . . . . . . : 10.10.10.1

   NetBIOS over Tcpip. . . . . . . . : Enabled

C:\>

```

#### /release and /renew

If IP addressing information is assigned dynamically, the command **ipconfig /release** will release the current DHCP bindings. **ipconfig /renew** will request fresh configuration information from the DHCP server. A host may contain faulty or outdated IP configuration information and a simple renewal of this information is all that is required to regain connectivity.

If, after releasing the IP configuration, the host is unable to obtain fresh information from the DHCP server, it could be that there is no network connectivity. Verify that the NIC has an illuminated link light, indicating that it has a physical connection to the network. If this does not solve the problem, it may be an issue with the DHCP server or network connections to the DCHP server.

```
C:\> ipconfig/release

Windows IP Configuration

No operation can be performed on Ethernet while it has its media disconnected.

Ethernet adapter Ethernet:

   Media State . . . . . . . . . . . : Media disconnected

   Connection-specific DNS Suffix . :

Wireless LAN adapter Wi-Fi:

   Connection-specific DNS Suffix . :

   Link-local IPv6 Address . . . . . : fe80::a1cc:4239:d3ab:2675%6

   Default Gateway . . . . . . . . . :

C:\> ipconfig/renew

Windows IP Configuration

No operation can be performed on Ethernet while it has its media disconnected.

Ethernet adapter Ethernet:

   Media State . . . . . . . . . . . : Media disconnected

   Connection-specific DNS Suffix . :

Wireless LAN adapter Wi-Fi:

   Connection-specific DNS Suffix . : lan

   Link-local IPv6 Address . . . . . : fe80::a1cc:4239:d3ab:2675%6

   IPv4 Address. . . . . . . . . . . : 10.10.10.130

   Subnet Mask . . . . . . . . . . . : 255.255.255.0

   Default Gateway . . . . . . . . . : 10.10.10.1

C:\>

```

### The ping command

Probably the most commonly used network utility is ping. Most IP enabled devices support some form of the **ping** command in order to test whether or not network devices are reachable through the IP network.

If the IP configuration appears to be correctly configured on the local host, next, test network connectivity by using ping. The **ping** command can be followed by either an IP address or the name of a destination host. In the example, the user pings the default gateway at 10.10.10.1 and then pings ww​w.cisco.com.

```
C:\> ping 10.10.10.1

Pinging 10.10.10.1 with 32 bytes of data:

Reply from 10.10.10.1: bytes=32 time=1ms TTL=64

Reply from 10.10.10.1: bytes=32 time=1ms TTL=64

Reply from 10.10.10.1: bytes=32 time=1ms TTL=64

Reply from 10.10.10.1: bytes=32 time=1ms TTL=64

Ping statistics for 10.10.10.1:

    Packets: Sent = 4, Received = 4, Lost = 0 (0% loss),

Approximate round trip times in milli-seconds:

    Minimum = 1ms, Maximum = 1ms, Average = 1ms

C:\> ping www.cisco.com

Pinging e2867.dsca.akamaiedge.net [104.112.72.241] with 32 bytes of data:

Reply from 104.112.72.241: bytes=32 time=25ms TTL=53

Reply from 104.112.72.241: bytes=32 time=25ms TTL=53

Reply from 104.112.72.241: bytes=32 time=27ms TTL=53

Reply from 104.112.72.241: bytes=32 time=24ms TTL=53

Ping statistics for 104.112.72.241:

    Packets: Sent = 4, Received = 4, Lost = 0 (0% loss),

Approximate round trip times in milli-seconds:

    Minimum = 24ms, Maximum = 27ms, Average = 25ms

C:\>

```

When a ping is sent to an IP address, a packet known as an echo request is sent across the network to the IP address specified. If the destination host receives the echo request, it responds with a packet known as an echo reply. If the source receives the echo reply, connectivity is verified by the reply from the specific IP address. The ping is not successful if a message such as request timed out or general failure appears.

If a **ping** command is sent to a name, such as ww​w.cisco.com, a packet is first sent to a DNS server to resolve the name to an IP address. After the IP address is obtained, the echo request is forwarded to the IP address and the process proceeds. If a ping to the IP address succeeds, but a ping to the name does not, there is most likely a problem with DNS.

### Ping Results

If **ping** commands to both the name and IP address are successful, but the user is still unable to access the application, then the problem most likely resides in the application on the destination host. For example, it may be that the requested service is not running.

If neither ping is successful, then network connectivity along the path to the destination is most likely the problem. If this occurs, it is common practice to ping the default gateway. If the ping to the default gateway is successful, the problem is not local. If the ping to the default gateway fails, the problem resides on the local network.

In some cases, the ping may fail but network connectivity is not the problem. A ping may fail due to the firewall on the sending or receiving device, or a router along the path that is blocking the pings.

The basic **ping** command usually issues four echoes and waits for the replies to each one. It can, however, be modified to increase its usefulness. The options listed in the figure display additional features available.

```

C:\> ping

Usage: ping [-t] [-a] [-n count] [-l size] [-f] [-i TTL] [-v TOS]

            [-r count] [-s count] [[-j host-list] | [-k host-list]]

            [-w timeout] [-R] [-S srcaddr] [-c compartment] [-p]

            [-4] [-6] target_name

Options:

    -t             Ping the specified host until stopped.

                   To see statistics and continue - type Control-Break;

                   To stop - type Control-C.

    -a             Resolve addresses to hostnames.

    -n count       Number of echo requests to send.

    -l size        Send buffer size.

    -f             Set Don't Fragment flag in packet (IPv4-only).

    -i TTL         Time To Live.

    -v TOS         Type Of Service (IPv4-only. This setting has been deprecated

                   and has no effect on the type of service field in the IP

                   Header).

    -r count       Record route for count hops (IPv4-only).

    -s count       Timestamp for count hops (IPv4-only).

    -j host-list   Loose source route along host-list (IPv4-only).

    -k host-list   Strict source route along host-list (IPv4-only).

    -w timeout     Timeout in milliseconds to wait for each reply.

    -R             Use routing header to test reverse route also (IPv6-only).

                   Per RFC 5095 the use of this routing header has been

                   deprecated. Some systems may drop echo requests if

                   deprecated. Some systems may drop echo requests if

    -S srcaddr     Source address to use.

    -c compartment Routing compartment identifier.

    -p             Ping a Hyper-V Network Virtualization provider address.

    -4             Force using IPv4.

    -6             Force using IPv6.

C:\>

```

