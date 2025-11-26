## Overview

VPC Network Peering allows private connectivity across two VPC networks regardless of whether they belong to the same project or the same organization. 

VPC Network Peering is useful for organization with several network administrative  domains or that want to peer with other organization.

VPC Network Peering gives you several advantages  over using external IP addresses or VPC to connect networks:

- Network Latency: private networking offers lower latency
- Network Security: service owners do not have their services exposed to public internet.
- Network Cost: network that are peered can use internal IPs to communicate and save Google Cloud egress bandwidth costs.

When create a custom network thee instances on that network will not be reachable until firewall rules are created. As an example, you can allow all internal traffic between
instances as well as SSH, RDP, and ICMP by running:

```Bash
$ gcloud compute firewall-rules create <FIREWALL_NAME> --network network-a --allow tcp,udp,icmp --source-ranges <IP_RANGE>
```

```Bash
$ gcloud compute firewall-rules create <FIREWALL_NAME> --network network-a --allow tcp:22,tcp:3389,icmp
```


To successfully setup a VPC network peering session, the session must be separately configured in both sides, an example `peer-ab` and `peer-ba`.

Peer network-a with network-b:

![[gcp-networking-002.png]]

Peer network-b with network-a:

![[gcp-networking-001.png]]

The peering connecting will remain inactive until it finds a matching configuration in both sides. Once VPC Network Peering becomes active and routes are exchanged, the flow is setup:

- Between VM instances in the peered networks: Full mesh connectivity.
- From VM instances in one network to Internal Load Balancing endpoints in the peered network.

![[gcp-networking-003.png]]

