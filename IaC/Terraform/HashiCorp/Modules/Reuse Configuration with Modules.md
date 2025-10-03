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
