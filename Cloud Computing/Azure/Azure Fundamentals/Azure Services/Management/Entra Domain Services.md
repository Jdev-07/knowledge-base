Overview

Microsoft Entra Domain Services provides managed domain services—such as domain join, group policy, LDAP, and Kerberos/NTLM authentication—without the burden of deploying, managing, or patching domain controllers in Azure. It integrates with your existing Microsoft Entra ID tenant via one-way synchronization of users, groups, and password hashes, enabling lift-and-shift of legacy applications into the cloud with a familiar Active Directory-style experience.

Core Features

- Managed domain controllers automatically provisioned, patched, and backed up by Azure
- Domain join for Azure virtual machines without deploying your own DCs
- Group Policy support to enforce security, configuration, and software installation settings
- LDAP and Kerberos/NTLM authentication for legacy directory-aware applications
- Secure LDAP (LDAPS) endpoint for encrypted directory access
- One-way synchronization from Entra ID to populate users, groups, and credentials
- High availability with two domain controllers per replica set and optional zonal distribution
- Geo-distributed replica sets to provide disaster recovery across peered virtual networks

Core Capabilities

| Capability                   | Description                                                                                           |
| ---------------------------- | ----------------------------------------------------------------------------------------------------- |
| Managed DC Lifecycle         | Automatic provisioning, patching, backups, and monitoring of domain controllers in your Azure network |
| Domain Join                  | Join Azure VMs to the managed domain using corporate credentials without self-hosting DCs             |
| Group Policy                 | Centralized creation and enforcement of GPOs across all domain-joined machines                        |
| LDAP & Kerberos/NTLM         | Full support for LDAP binds and Kerberos/NTLM authentication for legacy apps                          |
| Secure LDAP (LDAPS)          | Certificate-based encryption of LDAP traffic for secure directory queries and binds                   |
| One-way Entra ID Sync        | Sync user accounts, groups, and password hashes from Entra ID to the managed domain                   |
| High Availability            | Two-node replica set per managed domain with optional Availability Zone placement for resilience      |
| Geo-distributed Replica Sets | Deploy additional replica sets in other regions or peered virtual networks for DR scenarios           |
| Forest Trusts                | Create one-way outbound trusts to on-premises AD DS (Enterprise SKU required)                         |