# Share modules in the private registry

HCP Terraform allows users to create and confidentially share infrastructure modules within an organization using the private registry.

There are two publishing workflows: branch based and tag based.

Before deep dive here there are the documentation I followed:

****[Tag-based publishing](https://developer.hashicorp.com/terraform/tutorials/modules/module-private-registry-share?variants=module-workflow%3Atag)

**[Branch-based publishing](https://developer.hashicorp.com/terraform/tutorials/modules/module-private-registry-share?variants=module-workflow%3Abranch)**

Regardless the publishing workflow you choose, you must first connect/add the VCS Provider to bring you configuration. In my case I used GitHub and I set up the GitHub.com OAuth VCS provider. [Reference](https://developer.hashicorp.com/terraform/cloud-docs/vcs/github) 

**Prerequisites**

Before starting, make sure you have the following:
- A Terraform Cloud account
- A GitHub account
- A cloud provider account (AWS, Azure, or GCP) with properly configured credentials
- A VCS provider connected to your Terraform Cloud workspace

The core component of this setup is the Terraform configuration files, which must be uploaded to a GitHub repository. The repository should follow the naming convention:

```Shell
terraform-<PROVIDER>-<NAME>
```

The directory structure might looks like this:

```
.
└──terraform-aws-s3-webapp
  ├── main.tf
  ├── outputs.tf
  └── variables.tf
  └── assets
   └── index.html

```

For this lab, we can use any provider such as GCP, Azure, or AWS. In my case, I chose **AWS**. While attempting to use the **tag-based publishing workflow**, I encountered a persistent error:

![[terraform-022.png]] 

I verified my configuration and tested several workarounds, including changing repositories and trying with both Azure and GCP, but the issue persisted. As a result, I switched to the **branch-based publishing workflow**, which worked successfully:

![[terraform-023.png]]


```Go
module "s3-bucket" {
  source  = "app.terraform.io/jdevops/s3-bucket/aws"
  version = "1.0.0"
  # insert required variables here
}
```

Once the module is published in the **private registry**, it’s ready to be used.

## Add public providers and modules to a private registry 

Terraform uses **providers** and **modules** to build infrastructure. As your setup grows, it can be hard to find the right ones. **HCP Terraform’s private registry** helps by letting your organization keep an approved list of modules and providers. This makes it easier to:

- Find what’s allowed to use
- Access documentation in one place
- Track updates and new releases

Here is the documentation for reference: [Private registry](https://developer.hashicorp.com/terraform/tutorials/modules/private-registry-add)
## Refactor monolithic Terraform configuration

A monolithic Terraform configuration might work for simple setups to provision infrastructure, but as your environment grows and becomes more complex, restructuring your configuration into different files will make it easier to understand and manage.

The refactoring process apply to any modules (AWS, GCP, Azure and others)

Here is the documentation I used: [Refactor configuration](https://developer.hashicorp.com/terraform/tutorials/modules/organize-configuration)

I followed the suggested steps found in the documentation and  it successfully worked. 

Applying a monolithic Terraform configuration still works and can successfully provision the infrastructure, but defining two different environments in the same configuration is not best practice. This approach can cause unexpected behaviors over time and becomes difficult to manage.

Terraform uses a human-readable configuration language and supports multiple configuration files. Therefore, we can separate the configuration into two files, such as `dev.tf` and `prod.tf`. Although the working directory structure and configuration may seem fine, a new problem arises: any resource or provider with the same name in the working directory will cause a validation failure. This happens because Terraform loads all configuration files in the directory and appends them together. For this reason, we must carefully review the configuration.

Once we have mitigated this potential issue, we may still encounter a problem with hidden resource dependencies. For example, if we update the random pet name resource, we might assume that we are updating only one environment. However, if both environments reference that resource, both environments will be affected, which can lead to resources being destroyed and recreated unexpectedly. Therefore, it is recommended to run `terraform plan` before applying any configuration. This problem occurs because both environments are using a single Terraform state file.

To handle this type of scenarios we should separate the environments states, which is a safer approach to resolve these problems. There are two methods: directories and workspaces.

**Directories**

By creating separate directories for each environment, we can ensure that we modify only the intended infrastructure. Terraform will store the state files on disk in their corresponding directories.

This method basically relies on duplicating Terraform code, which can be useful if you want to test changes in _dev_ before promoting them to _prod_. However, over time, if you do not keep the _prod_ environment updated, it can create drift between environments.

A directory structure may look like this:

```
.
├── assets
│   ├── index.html
├── prod
│   ├── main.tf
│   ├── variables.tf
│   ├── terraform.tfstate
│   └── terraform.tfvars
└── dev
   ├── main.tf
   ├── variables.tf
   ├── terraform.tfstate
   └── terraform.tfvars
```

**Workspaces**

Workspace-separated environments use the same Terraform code but have different state files. This is useful if you want your environments to stay as similar as possible—for example, if you are providing development infrastructure to a team that wants to simulate running in production.

However, you must manage your workspaces through the CLI and always be aware of which workspace you are working in, to avoid accidentally performing operations on the wrong environment.

The configuration might look like this:

```
.
├── README.md
├── assets
│   └── index.html
├── dev.tfvars
├── main.tf
├── outputs.tf
├── prod.tfvars
├── terraform.tfstate.d
│   ├── dev
│   │   └── terraform.tfstate
│   ├── prod
│   │   └── terraform.tfstate
├── terraform.tfvars
└── variables.tf
```