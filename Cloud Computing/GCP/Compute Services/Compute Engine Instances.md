
# Compute Engine overview

Compute Engine is an Infrastructure  as a Service (IaaS) offering that provide self-managed virtual machine (VM) instances and bare metal instances. Compute Engine offers  VMs with a KVM hypervisor, operating system for both Linux and Windows, and durable storage options. 

Compute Engine offers many benefits, but some of them are the following: 

- Extensibility: Compute Engine lets you to integrate with other Google Cloud technologies to build more complex and sophisticated  applications.
- Scalability: Can scale the number of compute resource as needed without  having to managed your own infrastructure.
- Reliability
- Cost-effectiveness: compute engine offers a variety  of prancing options and you pay for the resources that you use. 

Compute Engine provides a set of machine families. Each family is comprised of machine series and predefined machine types within each series. Compute Engine offers general-purpose, compute-optimized etc but if any meets your constraints, then you can create a custom one. 

**Operating systems**

Compute Engine provides many preconfigured public operating system images for both Linux and windows. 

**Storage Options**

- Local SSD: Physical drivers that offer the best performance, but are not durable.
- Hyperdisk: The fastest durable storage for compute engine. Data on hyperdisk is preserved even if you stop the instance. 
- Persistent Disk: If you need durable storage for a machine series that does not support hyperdisk, then use Persistent Disk. 

## Compute Engine instances

A compute engine instance can be either a virtual machine or bare metal instance hosted on Google's Infrastructure. You can create a single VM or a managed instance group.

The terms _Compute Engine instance_, _compute instance_ or _instance_ are synonymous. Also, the terms _virtual machine instance_, _VM instance_, and _VM_ are synonymous.

Something very important to have into account is that each network interface is associated with a subnet of a unique VPC network.

## Regions and zones

Compute Engine resources are located in multiple locations around the world. These locations are composed of regions and zones. 

Regions are independent geographic areas that consists of zones. 

Resources that live in a zone, are referred to as zonal resources. Other resources, like static external IP addresses, are regional. Putting resources in different zones in a region reduces the risk of an infrastructure  outage  affecting all resources simultaneously. Only certain resources are region or zone specific. Other resources, such as images are global resources. 


**Identifying  a region or zone**

Each region in Compute Engine contains a number of zones. Each zone name contains two parts that describe each zone in detail

- Region

Regions are collection of zones. Zones have high-bandwidth, low-latency network connections to other zones in the same region. In order to deploy fault-tolerant applications that have high availability, Google recommends  deploying applications across multiple zones and multiple regions. This helps protects against unexpected failures of components. 

- Zone
A zone is a deployment area within a region. The fully-qualified name for a zone is made up of `region-zone`. For example, the fully-qualified name for zone `a` in region `us-central` is `us-cetral1-a`

**Resource Quotas**

Certain resources, such as static IPs, images, firewall rules, and VPC networks, have defined project-wide quota limits and per-region quota limits. When you create these resources, it counts towards your total project-wide quota or your per-region quota, if applicable. If any of the affected quota limits are exceeded, you won't be able to add more resources of the same type in that project or region.

**Choosing a region and a zone**

You choose which region or zone hosts your resources, which controls where your data is stored and used. Choosing a region and zone is important for several reasons:

Handling failures:  Distribute resources across multiple zones and regions to tolerate outages. Google. If a zone becomes unavailable , you can transfer traffic to another zone in the same region to keep your resources running. Similarly. you can migrate the impact of a region outage on an application by running backup services in a different region.

Decreased network latency: To decrease network latency, you might want to choose a region or zone that is close to your point of service. 

When selecting zones yourself, there some things to keep in mind

- **Communication within and across regions will incur different costs.**
    
    Generally, communication within regions will always be cheaper and faster than communication across different regions.
    
- **Design important systems with redundancy across multiple zones or regions.**
    
    At some point in time, your instances might experience an unexpected failure. To mitigate the effects of these possible events, you should duplicate important systems in multiple zones and regions.