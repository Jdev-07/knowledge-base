Terraform is an open-source IaC (Infrastructure as a Code) tool for configuring and deploying cloud infrastructure. It codifies infrastructure in configuration files that describe the desired state for your topology. 

There are several Terraform providers that enable the management of Azure infrastructure:
1. AzureRM
2. AzAPI
3. AzureAD
4. AzureDevops
5. AzureStack

## Benefits of Terraform with  Azure

### Common IaC tool

Terraform Azure providers enable you to manage all of your Azure infrastructure using the same declarative syntax and tooling. Using these providers you can:

1. Configure core platform capabilities such as management groups, policies, users, groups, and policies. For more information, see [Terraform implementation of Cloud Adoption Framework Enterprise-scale](https://github.com/Azure/terraform-azurerm-caf-enterprise-scale#readme).
2. Configure Azure DevOps projects and pipelines to automate regular infrastructure and application deployments.
3. Deploy Azure resources required by your applications.

### Automate infrastructure management

The Terraform template-based configuration file syntax enables you to configure Azure resources in a repeatable and predictable manner. Automating infrastructure includes the following benefits:

- Lowers the potential for human errors while deploying and managing infrastructure.
- Deploys the same template multiple times to create identical development, test, and production environments.
- Reduces the cost of development and test environments by creating them on-demand.

### Understand infrastructure changes before being applied

As a resource topology becomes complex, understanding the meaning and impact of infrastructure changes can be difficult.

The Terraform CLI enables users to validate and preview infrastructure changes before application of the plan. Previewing infrastructure changes in a safe manner has several benefits:

- Team members can collaborate more effectively by understanding proposed changes and their impact.
- Unintended changes can be caught early in the development process.