In previous units, we covered what the Terraform HCL (HashiCorp Configuration Language) language is and the benefits that it provides for module authoring. Before you begin the process of writing Terraform modules to provision your resources, you want to learn more about how Terraform works.

In this unit, you learn about how Terraform works with providers and state files.

## Terraform CLI

What is Terraform? Fundamentally, Terraform is a CLI tool. It's free to use under the BSL (Business Source License) and can be downloaded [here](https://developer.hashicorp.com/terraform/install). The Terraform CLI is the only tool you need to deploy with Terraform.

There are two other related products called Terraform Enterprise or Terraform Cloud. These products are separate to the Terraform CLI. They provide features, such as state management and private module registry to simplify Terraform adoption. They embed the Terraform CLI, but still use the same version of the Terraform CLI that everyone else uses to deploy resources.

## Terraform providers

In the preceding unit, you learned that HCL is a domain-specific language designed for a specific scenario or _domain_. HCL is built to make it easy to deploy and configure any resource in any cloud or service with Terraform.

How does Terraform know about the specifics of Azure though? And how about Azure DevOps, GitHub, etc. for that matter. The Terraform CLI tool doesn't know anything about Azure or any other cloud or service, it only knows how to manage state and plan deployments. Terraform providers are responsible for bridging the gap between the Terraform CLI and the target API, in our case Azure. Terraform has a concept of plugins and providers are a type of plugin. Providers are loaded into the Terraform CLI during the init phase based on the requirements in your HCL code.

Microsoft curates many providers in collaboration with HashiCorp and the community. These providers include:

- [azurerm](https://registry.terraform.io/providers/hashicorp/azurerm): This provider is the most user friendly way to deploy resources into Azure. This provider may take time to support new Azure features.
- [azapi](https://registry.terraform.io/providers/Azure/azapi): This provider enables deployment of any Azure resource, including resources in preview. It's always up to date with the latest Azure features.
- [azuread](https://registry.terraform.io/providers/hashicorp/azuread): This provider is used to managed Microsoft Entra ID. It can manage many features, including user, groups, and service principals.
- [azuredevops](https://registry.terraform.io/providers/microsoft/azuredevops): This provider is used to manage all aspects of Azure DevOps, including repos, pipelines, and projects.
- [github](https://registry.terraform.io/providers/integrations/github): This provider is used to manage all aspects of GitHub, including organizations, repositories, and actions.

The Terraform CLI interacts with providers via a standard interface. This interface enables the Terraform CLI to build dependency graphs and manage state without needing to be aware of the provider implementation details.

Providers consist of _resources_ and _data sources_. Resources are managed with Terraform. Data sources are used to read the attributes of a resource without managing it.

It's possible to write your own providers to work with internal API endpoints, so you can essentially manage anything with Terraform. Providers must be written in the Go programming language.

## Terraform Workflow

When using the Terraform CLI, there a four fundamental steps in the workflow:

1. Write: Write the HCL code to define your desired state.
2. Init: Pull down providers and modules. Connect to remote state.
3. Plan: Generates a plan to bring actual state into line with desired state, by querying your deployed resources and comparing to the configuration.
4. Apply: Implement the plan and bring the target environment in line via API calls.

![[terraform-001.png]]

## Terraform LifeCycle

Terraform is designed and should be used to manage the lifecycle of your resources. By using a state file, Terraform can manage your resources through these stages:

1. Create: The resource is in desired state, but doesn't exist in actual state and is created in Azure.
2. Update: The desired state of the resource attributes doesn't match the actual state and the resource is updated to bring in line with desired state.
3. Destroy: The resource no longer exists in desired state and is deleted from Azure.

![[terraform-002.png]]

The update step can happen many times over the lifetime of a resource as the requirements alter over time. For example imagine you're managing Azure Firewall rules with Terraform, you may have to update these rules on a regular cadence to add new rules, adjust existing rules, and remove rules.

## Terraform State

Terraform state is required to support the Terraform lifecycle. Terraform has no insight into Azure or any of the other clouds or services it might manage. As such, it needs an agnostic way to know what it's managing. The state file is that mechanism.

Terraform maps the HCL configuration to a resource ID in Azure. Terraform is able to manage a resource, because it has the ID mapped. When a resource is removed from the HCL, Terraform plans to destroy that resource. Without a state file, Terraform would have no knowledge of that resource.

State files can contain sensitive data and must be stored securely. We recommend using Terraform Cloud / Enterprise or Azure Blob Storage to manage your state files.

# When to use Terraform

Many tool sets are available for infrastructure as code resource deployments. You want to learn more about when Terraform might be the right tool for you and your organization.

## Is Terraform the right tool?

Terraform is a great choice if you need a cloud / service agnostic solution. Terraform allows you to manage other Microsoft products in a consistent manner, including Azure DevOps and GitHub. Terraform has great ongoing community and Microsoft support and investment. Terraform fits well into an infrastructure as code DevOps process and supports the latest Azure identity solutions.

Whichever infrastructure as code solution you choose, know you are in good company. Simply making the choice to embrace infrastructure as code aligns you with our best practice guidance and our highest performing customers.

### When is Terraform the right tool?

If you use Azure as your cloud platform, consider these advantages of using Terraform:

- **Multicloud / Service Agnostic**: With Terraform, you're using a language that is agnostic of the clouds or services you use. You can even deploy resources to multiple providers within the same Terraform module.
    
- **Azure support**: With the azapi provider, when new Azure resources are released or updated, Terraform supports those features on day one.
    
- **Azure Verified Modules**: If you use [Azure Verified Modules](https://aka.ms/avm), you have a fully supported product with Microsoft Support.
    
- **State management**: Because of the state file, Terraform is effective at managing the lifecycle of your resource from creation through to decommissioning.
    
- **Skill sets**: When making your choice, take into account the skill set of your team and the skills available in your market.
    

### When is Terraform not the right tool?

Some situations might call for another tool set. Consider the following reasons not to use Terraform as your main tool set:

- **Existing tool set**: When you're determining when to use Terraform, the first question to ask is, _does my organization already have a tool set in use?_ Many tooling options are available that can be used for infrastructure as code resource provisioning. Sometimes, it makes sense to use existing financial and knowledge investments when you consider adopting a new process.
    
- **Single cloud**: If your organization only uses Azure and no other clouds or services, Bicep might be the right tool. Terraform supports the single cloud scenario, but you might wish to consider the trade-off in managing state files.