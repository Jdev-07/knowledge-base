# IP Address Ranges 

IP addresses are split into **classes (A, B, C, D, E)** mainly for historical reasons, but nowadays we usually focus on **private ranges**, **public ranges**, and **special addresses**.

### IP Classes

- **Class A**: `0.0.0.0 – 127.255.255.255`
    
- **Class B**: `128.0.0.0 – 191.255.255.255`
    
- **Class C**: `192.0.0.0 – 223.255.255.255`
    
- **Class D**: `224.0.0.0 – 239.255.255.255` (Multicast)
    
- **Class E**: `240.0.0.0 – 255.255.255.255` (Experimental / reserved)


### Private IP Ranges

These are **not routable on the internet**, only inside LANs:

- **Class A private**: `10.0.0.0 – 10.255.255.255`
    
- **Class B private**: `172.16.0.0 – 172.31.255.255`
    
- **Class C private**: `192.168.0.0 – 192.168.255.255`

###  Special Ranges

- **Loopback**: `127.0.0.0 – 127.255.255.255` (commonly `127.0.0.1`)
    
- **APIPA (Automatic Private IP Addressing)**: `169.254.0.0 – 169.254.255.255` (used when DHCP fails)
    
- **Link-local IPv6**: `fe80::/10`
    
- **Multicast**: `224.0.0.0 – 239.255.255.255`
    
- **Broadcast**: `255.255.255.255`