
Azure Lighthouse enables multitenant management with scalability, higher automation, and enhanced governance across resources.

With Azure Lighthouse, service providers can deliver managed services using comprehensive and robust tooling built into the Azure platform. Customers maintain control over who has access to their tenant, which resources they can access, and what actions can be taken. Enterprise organizations managing resources across multiple tenants can use Azure Lighthouse to streamline management tasks.

Cross-tenant management experiences let you work more efficiently with Azure services such as Azure Policy, Microsoft Sentinel, Azure Arc, and many more. Users can see what changes were made and by whom in the activity log, which is stored in the customer's tenant and can be viewed by users in the managing tenant.

## Benefits

- **Management at scale**: Customer engagement and life-cycle operations to manage customer resources are easier and more scalable. Existing APIs, management tools, and workflows can be used with delegated resources, including [machines hosted outside of Azure](https://learn.microsoft.com/en-us/azure/lighthouse/how-to/manage-hybrid-infrastructure-arc), regardless of the regions in which they're located.

- **Greater visibility and control for customers**: Customers have precise control over the scopes they delegate and the permissions that are allowed. They can [audit service provider actions](https://learn.microsoft.com/en-us/azure/lighthouse/how-to/view-service-provider-activity) and remove access completely at any time.

- **Comprehensive and unified platform tooling**: Azure Lighthouse works with existing tools and APIs, [Azure managed applications](https://learn.microsoft.com/en-us/azure/lighthouse/concepts/managed-applications), and partner programs like the [Cloud Solution Provider (CSP) program](https://learn.microsoft.com/en-us/azure/lighthouse/concepts/cloud-solution-provider). This flexibility supports key service provider scenarios, including multiple licensing models such as EA, CSP and pay-as-you-go. You can integrate Azure Lighthouse into your existing workflows and applications, and track your impact on customer engagements by [linking your partner ID](https://learn.microsoft.com/en-us/azure/cost-management-billing/manage/link-partner-id).

## Capabilities

Azure Lighthouse includes multiple ways to streamline engagement and management:

- **Azure delegated resource management**: [Manage your customers' Azure resources securely from within your own tenant](https://learn.microsoft.com/en-us/azure/lighthouse/concepts/architecture), without having to switch context and control planes. Customer subscriptions and resource groups can be delegated to specified users and roles in the managing tenant, with the ability to remove access as needed.

- **New Azure portal experiences**: View cross-tenant information in the [**My customers** page](https://learn.microsoft.com/en-us/azure/lighthouse/how-to/view-manage-customers) in the Azure portal, or [work directly in the context of a delegated subscription](https://learn.microsoft.com/en-us/azure/lighthouse/how-to/view-manage-customers#work-in-the-context-of-a-delegated-subscription). Customers can view and manage provider access in the [**Service providers** page](https://learn.microsoft.com/en-us/azure/lighthouse/how-to/view-manage-service-providers).

- **Azure Resource Manager templates**: Use ARM templates to [onboard delegated customer resources](https://learn.microsoft.com/en-us/azure/lighthouse/how-to/onboard-customer) and [perform cross-tenant management tasks](https://learn.microsoft.com/en-us/azure/lighthouse/samples/).

- **Managed Service offers in Azure Marketplace**: [Offer your services to customers](https://learn.microsoft.com/en-us/azure/lighthouse/concepts/managed-services-offers) through private or public offers, and automatically onboard them to Azure Lighthouse.

## Pricing and availability 

There are no additional costs associated with using Azure Lighthouse to manage Azure resources. Any Azure customer or partner can use Azure Lighthouse.

## Cross-region and cloud considerations

Azure Lighthouse is a nonregional service. You can manage delegated resources that are located in different [regions](https://learn.microsoft.com/en-us/azure/cloud-adoption-framework/ready/azure-setup-guide/regions). However, you can't delegate resources across a [national cloud](https://learn.microsoft.com/en-us/entra/identity-platform/authentication-national-cloud) and the Azure public cloud, or across two separate national clouds.