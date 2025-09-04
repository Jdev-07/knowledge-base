As you manage your infrastructure with Terraform, you will create increasingly complex configurations. There is no intrinsic limit to the complexity of a single Terraform configuration file or directory, so it is possible to continue writing and updating your configuration files in a single directory. However, if you do, you may encounter one or more problems:

- Understanding and navigating the configuration files will become increasingly difficult.
    
- Updating the configuration will become **more risky**, as an update to one section may cause unintended consequences to other parts of your configuration.
    
- There will be an increasing amount of duplication of similar blocks of configuration, for instance when configuring separate dev/staging/production environments, which will cause an increasing burden when updating those parts of your configuration.
    
- You may wish to share parts of your configuration between projects and teams, and will quickly find that cutting and pasting blocks of configuration between projects is error prone and hard to maintain.
    
- Engineers will need more Terraform expertise to understand and modify your configuration. This makes self-service workflows for other teams more difficult, slowing down their development.
    

## What are modules for?

Here are some of the ways that modules help solve the problems listed above:

- Organize configuration - Modules make it easier to navigate, understand, and update your configuration by keeping related parts of your configuration together. Even moderately complex infrastructure can require hundreds or thousands of lines of configuration to implement. By using modules, you can organize your configuration into logical components.
    
- Encapsulate configuration - Another benefit of using modules is to encapsulate configuration into distinct logical components. Encapsulation can help prevent unintended consequences, such as a change to one part of your configuration accidentally causing changes to other infrastructure, and reduce the chances of simple errors like using the same name for two different resources.
    
- Re-use configuration - Writing all of your configuration from scratch can be time consuming and error prone. Using modules can save time and reduce costly errors by re-using configuration written either by yourself, other members of your team, or other Terraform practitioners who have published modules for you to use. You can also share modules that you have written with your team or the general public, giving them the benefit of your hard work.
    
- Provide consistency and ensure best practices - Modules also help to provide consistency in your configurations. Not only does consistency make complex configurations easier to understand, it also helps to ensure that best practices are applied across all of your configuration. For instance, cloud providers give many options for configuring object storage services, such as Amazon S3 or Google Cloud Storage buckets. There have been many high-profile security incidents involving incorrectly secured object storage, and given the number of complex configuration options involved, it's easy to accidentally misconfigure these services.
    
- Self service - Modules make your configuration easier for other teams to use. The HCP Terraform registry lets other teams find and re-use your published and approved Terraform modules. You can also build and publish no-code ready modules, which let teams without Terraform expertise provision their own infrastructure that complies with your organization's standards and policies.
    
    Using modules can help reduce these errors. For example, you might create a module to describe how all of your organization's public website buckets will be configured, and another module for private buckets used for logging applications. Also, if a configuration for a type of resource needs to be updated, using modules allows you to make that update in a single place and have it be applied to all cases where you use that module.

### 🔹 Why use modules?

1. **Organize configuration**
    
    - Instead of having one huge `main.tf`, you split infrastructure into logical components.
        
    - Example: one module for VPC, another for compute instances, another for monitoring.
        
2. **Encapsulate configuration**
    
    - Keeps resources bundled together, reducing the risk of accidental changes.
        
    - Example: changing the VPC module won’t mess with your storage module.
        
3. **Re-use configuration**
    
    - You don’t need to reinvent the wheel every time.
        
    - Example: use the official [Terraform Registry modules](https://registry.terraform.io/?utm_source=chatgpt.com) (like `terraform-aws-vpc`) instead of writing your own from scratch.
        
4. **Consistency & best practices**
    
    - Enforces standard patterns across environments.
        
    - Example: every S3 bucket in your org uses the same module → consistent security policies.
        
5. **Self-service for teams**
    
    - Other teams can consume your modules without needing deep Terraform knowledge.
        
    - Example: a dev team can launch a compliant database cluster by just calling your `db_cluster` module.

### 🔹 Example

Suppose you want to create an **S3 bucket** with logging enabled.  
Instead of repeating the same code for every bucket, you can wrap it in a module:

```Go
variable "bucket_name" {}
variable "logging_bucket" {}

resource "aws_s3_bucket" "main" {
  bucket = var.bucket_name

  logging {
    target_bucket = var.logging_bucket
    target_prefix = "logs/"
  }
}
```

Root module

```Go
module "app_bucket" {
  source        = "./modules/s3_bucket"
  bucket_name   = "my-app-bucket"
  logging_bucket = "my-logs-bucket"
}
```

⚡In short:  
**Modules = organization + reusability + consistency.**  
They’re the building blocks that make Terraform scalable and maintainable, especially in big infrastructures.


## What is a Terraform module?

A Terraform module is a set of Terraform configuration files in a single directory. Even a simple configuration consisting of a single directory with one or more `.tf` files is a module. When you run Terraform commands directly from such a directory, it is considered the **root module**. So in this sense, every Terraform configuration is part of a module. You may have a simple set of Terraform configuration files such as:

```
.
├── LICENSE
├── README.md
├── main.tf
├── variables.tf
├── outputs.tf
```

In this case, when you run terraform commands from within the `minimal-module` directory, the contents of that directory are considered the root module.

### Calling modules

Terraform commands will only directly use the configuration files in one directory, which is usually the current working directory. However, your configuration can use module blocks to call modules in other directories. When Terraform encounters a module block, it loads and processes that module's configuration files.

A module that is called by another configuration is sometimes referred to as a "child module" of that configuration.

### Local and remote modules

Modules can either be loaded from the local filesystem, or a remote source. Terraform supports a variety of remote sources, including the Terraform Registry, most version control systems, HTTP URLs, and HCP Terraform or Terraform Enterprise private module registries.
## Module best practices

In many ways, Terraform modules are similar to the concepts of libraries, packages, or modules found in most programming languages, and provide many of the same benefits. Just like almost any non-trivial computer program, real-world Terraform configurations should almost always use modules to provide the benefits mentioned above.

We recommend that every Terraform practitioner use modules by following these best practices:

1. Name your provider `terraform-<PROVIDER>-<NAME>`. You must follow this convention in order to [publish to the HCP Terraform or Terraform Enterprise module registries](https://developer.hashicorp.com/terraform/cloud-docs/registry/publish-modules).
    
2. Start writing your configuration with modules in mind. Even for modestly complex Terraform configurations managed by a single person, you'll find the benefits of using modules outweigh the time it takes to use them properly.
    
3. Use local modules to organize and encapsulate your code. Even if you aren't using or publishing remote modules, organizing your configuration in terms of modules from the beginning will significantly reduce the burden of maintaining and updating your configuration as your infrastructure grows in complexity.
    
4. Use the public Terraform Registry to find useful modules. This way you can more quickly and confidently implement your configuration by relying on the work of others to implement common infrastructure scenarios.
    
5. Publish and share modules with your team. Most infrastructure is managed by a team of people, and modules are important way that teams can work together to create and maintain infrastructure. As mentioned earlier, you can publish modules either publicly or privately. Module users can reference published child modules in a root module, or deploy no-code ready modules through the HCP Terraform UI.

## Understand how modules work

When using a new module for the first time, you must run either `terraform init` or `terraform get` to install the module. When you run these commands, Terraform will install any new modules in the `.terraform/modules` directory within your configuration's working directory. For local modules, Terraform will create a symlink to the module's directory. Because of this, any changes to local modules will be effective immediately, without having to reinitialize or re-run `terraform get`.

After following this tutorial, your `.terraform/modules` directory will look like the following.

```
.terraform/modules/
├── ec2_instances
├── modules.json
└── vpc
```