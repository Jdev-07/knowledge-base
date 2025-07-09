
- **Fiber-optic cabling** uses **light signals** (instead of electrical signals in copper), making it **immune to electromagnetic interference (EMI) and radio frequency interference (RFI)**.
    
    - Critical in environments with heavy machinery, power lines, or radio transmitters.
        
- Copper cables suffer from EMI/RFI, degrading signal quality.

When a host sends a packet, it determines whether the destination is **local** or **remote** by:

1. **Applying the subnet mask** to its own IP address to find its **local network ID**.
    
2. **Applying the same subnet mask** to the destination IP address.
    
3. **Comparing the two network IDs**:
    
    - If they **match**, the destination is on the **same local network**.
        
    - If they **differ**, the destination is on a **remote network**, and the packet is sent to the **default gateway** (router).


In the context of an IPv4 routing table on a Cisco router, the code "C" represents a directly connected route. This means the network associated with that route is directly connected to one of the router's interfaces.