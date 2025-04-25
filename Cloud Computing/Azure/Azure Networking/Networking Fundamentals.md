
## Name Resolution for resources in Azure Virtual Networks

To enable communication between VMs and other resources in a Vnet, you should allow them to communicate each other. Using easily remembered and consistent names simplifies the communication process, rather than relying on IP addresses.  

When resources deployed in virtual networks need to resolve domain name to internal IP addresses, they can use on of four methods. 

- [Azure Private DNS zones](https://learn.microsoft.com/en-us/azure/dns/private-dns-overview)
- [Azure-provided name resolution](https://learn.microsoft.com/en-us/azure/virtual-network/virtual-networks-name-resolution-for-vms-and-role-instances?tabs=redhat#azure-provided-name-resolution)
- [Name resolution that uses your own Domain Name System (DNS) server](https://learn.microsoft.com/en-us/azure/virtual-network/virtual-networks-name-resolution-for-vms-and-role-instances?tabs=redhat#name-resolution-that-uses-your-own-dns-server) (which might forward queries to the Azure-provided DNS servers)
- [Azure DNS Private Resolver](https://learn.microsoft.com/en-us/azure/dns/dns-private-resolver-overview)

The type of name resolution you use depends on how your resources need to communicate each other. The following table illustrate scenarios and corresponding name resolutions solutions. 

Azure 

