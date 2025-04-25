
## Name Resolution for resources in Azure Virtual Networks

To enable communication between VMs and other resources in a Vnet, you should allow them to communicate each other. Using easily remembered and consistent names simplifies the communication process, rather than relying on IP addresses.  

When resources deployed in virtual networks need to resolve domain name to internal IP addresses, they can use on of four methods. 

- [Azure Private DNS zones](https://learn.microsoft.com/en-us/azure/dns/private-dns-overview)
- [Azure-provided name resolution](https://learn.microsoft.com/en-us/azure/virtual-network/virtual-networks-name-resolution-for-vms-and-role-instances?tabs=redhat#azure-provided-name-resolution)
- [Name resolution that uses your own Domain Name System (DNS) server](https://learn.microsoft.com/en-us/azure/virtual-network/virtual-networks-name-resolution-for-vms-and-role-instances?tabs=redhat#name-resolution-that-uses-your-own-dns-server) (which might forward queries to the Azure-provided DNS servers)
- [Azure DNS Private Resolver](https://learn.microsoft.com/en-us/azure/dns/dns-private-resolver-overview)

The type of name resolution you use depends on how your resources need to communicate each other. The following table illustrate scenarios and corresponding name resolutions solutions. 

Azure Private DNS zone are preferred solution and give you flexibility in managing your DNS zones and records. 

Note: If you use Azure-provided DNS, the appropriate DNS suffix is automatically applied to your VMs. For all other options, you must either use fully qualified domain names (FQDNs) or manually apply the appropriate DNS suffix to your VMs.

|Scenario|Solution|DNS suffix|
|---|---|---|
|Name resolution between VMs located in the same virtual network or Azure Cloud Services role instances in the same cloud service.|[Azure Private DNS zones](https://learn.microsoft.com/en-us/azure/dns/private-dns-overview) or [Azure-provided name resolution](https://learn.microsoft.com/en-us/azure/virtual-network/virtual-networks-name-resolution-for-vms-and-role-instances?tabs=redhat#azure-provided-name-resolution)|Hostname or FQDN|
|Name resolution between VMs in different virtual networks or role instances in different cloud services.|[Azure Private DNS zones](https://learn.microsoft.com/en-us/azure/dns/private-dns-overview), [Azure DNS Private Resolver](https://learn.microsoft.com/en-us/azure/dns/dns-private-resolver-overview), or customer-managed DNS servers forwarding queries between virtual networks for resolution by Azure (DNS proxy). See [Name resolution using your own DNS server](https://learn.microsoft.com/en-us/azure/virtual-network/virtual-networks-name-resolution-for-vms-and-role-instances?tabs=redhat#name-resolution-that-uses-your-own-dns-server).|FQDN only|
|Name resolution from an Azure App Service (web app, function, or bot) by using virtual network integration to role instances or VMs in the same virtual network.|[Azure DNS Private Resolver](https://learn.microsoft.com/en-us/azure/dns/dns-private-resolver-overview) or customer-managed DNS servers forwarding queries between virtual networks for resolution by Azure (DNS proxy). See [Name resolution using your own DNS server](https://learn.microsoft.com/en-us/azure/virtual-network/virtual-networks-name-resolution-for-vms-and-role-instances?tabs=redhat#name-resolution-that-uses-your-own-dns-server).|FQDN only|
|Name resolution from App Service web apps to VMs in the same virtual network.|[Azure DNS Private Resolver](https://learn.microsoft.com/en-us/azure/dns/dns-private-resolver-overview) or customer-managed DNS servers forwarding queries between virtual networks for resolution by Azure (DNS proxy). See [Name resolution using your own DNS server](https://learn.microsoft.com/en-us/azure/virtual-network/virtual-networks-name-resolution-for-vms-and-role-instances?tabs=redhat#name-resolution-that-uses-your-own-dns-server).|FQDN only|
|Name resolution from App Service web apps in one virtual network to VMs in a different virtual network.|[Azure DNS Private Resolver](https://learn.microsoft.com/en-us/azure/dns/dns-private-resolver-overview) or customer-managed DNS servers forwarding queries between virtual networks for resolution by Azure (DNS proxy). See [Name resolution using your own DNS server](https://learn.microsoft.com/en-us/azure/virtual-network/virtual-networks-name-resolution-for-vms-and-role-instances?tabs=redhat#name-resolution-that-uses-your-own-dns-server).|FQDN only|
|Resolution of on-premises computer and service names from VMs or role instances in Azure.|[Azure DNS Private Resolver](https://learn.microsoft.com/en-us/azure/dns/dns-private-resolver-overview) or customer-managed DNS servers (on-premises domain controller, local read-only domain controller, or a DNS secondary synced by using zone transfers, for example). See [Name resolution using your own DNS server](https://learn.microsoft.com/en-us/azure/virtual-network/virtual-networks-name-resolution-for-vms-and-role-instances?tabs=redhat#name-resolution-that-uses-your-own-dns-server).|FQDN only|
|Resolution of Azure hostnames from on-premises computers.|Forward queries to a customer-managed DNS proxy server in the corresponding virtual network. The proxy server forwards queries to Azure for resolution. See [Name resolution using your own DNS server](https://learn.microsoft.com/en-us/azure/virtual-network/virtual-networks-name-resolution-for-vms-and-role-instances?tabs=redhat#name-resolution-that-uses-your-own-dns-server).|FQDN only|
|Reverse DNS for internal IPs.|[Azure Private DNS zones](https://learn.microsoft.com/en-us/azure/dns/private-dns-overview), [Azure-provided name resolution](https://learn.microsoft.com/en-us/azure/virtual-network/virtual-networks-name-resolution-for-vms-and-role-instances?tabs=redhat#azure-provided-name-resolution), [Azure DNS Private Resolver](https://learn.microsoft.com/en-us/azure/dns/dns-private-resolver-overview), or [Name resolution using your own DNS server](https://learn.microsoft.com/en-us/azure/virtual-network/virtual-networks-name-resolution-for-vms-and-role-instances?tabs=redhat#name-resolution-that-uses-your-own-dns-server).|Not applicable|
|Name resolution between VMs or role instances located in different cloud services, not in a virtual network.|Not applicable. Connectivity between VMs and role instances in different cloud services isn't supported outside a virtual network.|Not applicable|
### Azure-provided name resolution

Azure-provided name resolution provides only basic authoritative DNS capabilities. Azure manages the DNS zone names and records if you use the DNS provided by Azure. You aren't able to control the DNS zone names or the life cycle of DNS records. If you need a fully featured DNS solution for your virtual networks, you can use [Azure Private DNS zones](https://learn.microsoft.com/en-us/azure/dns/private-dns-overview) with [Customer-managed DNS servers](https://learn.microsoft.com/en-us/azure/virtual-network/virtual-networks-name-resolution-for-vms-and-role-instances?tabs=redhat#name-resolution-that-uses-your-own-dns-server) or [Azure DNS Private Resolver](https://learn.microsoft.com/en-us/azure/dns/dns-private-resolver-overview).

Along with resolution of public DNS names, Azure provides internal name resolution for VMs and role instances that reside within the same virtual network or cloud service. VMs and instances in a cloud service share the same DNS suffix, so the hostname alone is sufficient. But in virtual networks deployed by using the classic deployment model, different cloud services have different DNS suffixes. In this situation, you need the FQDN to resolve names between different cloud services.

In virtual networks deployed by using the Azure Resource Manager deployment model, the DNS suffix is consistent across all the VMs within a virtual network, so the FQDN isn't needed. You can assign DNS names to both VMs and network interfaces. Although Azure-provided name resolution doesn't require any configuration, it isn't the appropriate choice for all deployment scenarios, as described in the previous table.


| Note | When you use Azure Cloud Services web and worker roles, you can also access the internal IP addresses of role instances by using the Azure Service Management REST API. For more information, see the [Service Management REST API reference](https://learn.microsoft.com/en-us/previous-versions/azure/ee460799\(v=azure.100\)). The address is based on the role name and instance number. |
| ---- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |

#### Features

Azure-provided name resolution includes the following features:



