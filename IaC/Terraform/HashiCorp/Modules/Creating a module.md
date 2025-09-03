# Build and use a local module
## Module structure

Terraform treats any local directory referenced in the `source` argument of a `module` block as a module. A typical file structure for a new module is:

```
.
├── LICENSE
├── README.md
├── main.tf
├── variables.tf
├── outputs.tf
```

None of these files are required, or have any special meaning to Terraform when it uses your module. You can create a module with a single `.tf` file, or use any other file structure you like.

Each of these files serves a purpose:

- [](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#)[`LICENSE`](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#license) will contain the license under which your module will be distributed. When you share your module, the `LICENSE` file will let people using it know the terms under which it has been made available. Terraform itself does not use this file.
- [](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#)[`README.md`](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#readme-md) will contain documentation describing how to use your module, in markdown format. Terraform does not use this file, but services like the Terraform Registry and GitHub will display the contents of this file to people who visit your module's Terraform Registry or GitHub page.
- [](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#)[`main.tf`](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#main-tf) will contain the main set of configuration for your module. You can also create other configuration files and organize them however makes sense for your project.
- [](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#)[`variables.tf`](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#variables-tf) will contain the variable definitions for your module. When your module is used by others, the variables will be configured as arguments in the `module` block. Since all Terraform values must be defined, any variables that are not given a default value will become required arguments. Variables with default values can also be provided as module arguments, overriding the default value.
- [](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#)[`outputs.tf`](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#outputs-tf) will contain the output definitions for your module. Module outputs are made available to the configuration using the module, so they are often used to pass information about the parts of your infrastructure defined by the module to other parts of your configuration.

There are also some other files to be aware of, and ensure that you don't distribute them as part of your module:

- [](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#)[`terraform.tfstate`](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#terraform-tfstate) and `terraform.tfstate.backup`: These files contain your Terraform state, and are how Terraform keeps track of the relationship between your configuration and the infrastructure provisioned by it.
- [](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#)[`.terraform`](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#terraform): This directory contains the modules and plugins used to provision your infrastructure. These files are specific to a specific instance of Terraform when provisioning infrastructure, not the configuration of the infrastructure defined in `.tf` files.
- [](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#)[`*.tfvars`](https://developer.hashicorp.com/terraform/tutorials/modules/module-create#tfvars): Since module input variables are set via arguments to the `module` block in your configuration, you don't need to distribute any `*.tfvars` files with your module, unless you are also using it as a standalone Terraform configuration.

If you are tracking changes to your module in a version control system, such as git, you will want to configure your version control system to ignore these files. For an example, see this [.gitignore file](https://github.com/github/gitignore/blob/main/Terraform.gitignore) from GitHub.

The files mentioned above will often include secret information such as passwords or access keys, which will become public if those files are committed to a public version control system such as GitHub.

Whenever you add a new module to a configuration, Terraform must install the module before it can be used. Both the `terraform get` and `terraform init` commands will install and update modules. The `terraform init` command will also initialize backends and install plugins.

Now install the module by running `terraform get`.

When installing a remote module, Terraform will download it into the `.terraform` directory in your configuration's root directory. When installing a local module, Terraform will instead refer directly to the source directory. Because of this, Terraform will automatically notice changes to local modules without having to re-run `terraform init` or `terraform get`.

---
# Customize modules with object attributes

## Object Attributes

Terraform modules let you organize and re-use Terraform configuration. They make your infrastructure deployments consistent and help your team adhere to your organization's best practices. Input variables let module users customize attributes of the module. You can define module attributes using strings, numbers, booleans, lists, maps, and objects.

Object type attributes contain a fixed set of named values of different types. Using objects in your modules lets you group related attributes together, making it easier for users to understand how to use your module. You can make attributes within objects optional, which make it easier for you to ship new module versions without changing the variables that module users need to define.

S3 stores data as objects, which are roughly equivalent to files on a local system. Web servers and browsers often use the term "document". For simplicity, this tutorial uses the generic term "file".

## Use a list of objects to configure CORS

Cross-Origin Resource Sharing (CORS) allows web developers to control where and how users access resources in their website. CORS configuration limits access to websites based on request headers, method, or originating domain. Add a new variable to `modules/aws-s3-static-website/variables.tf` to control your S3 bucket's CORS configuration.

modules/aws-s3-static-website/variables.tf

```
variable "cors_rules" {
  description = "List of CORS rules."
  type = list(object({
    allowed_headers = optional(set(string)),
    allowed_methods = set(string),
    allowed_origins = set(string),
    expose_headers  = optional(set(string)),
    max_age_seconds = optional(number)
  }))
  default = []
}
```

The `cors_rules` variable contains a list of objects. Since the default value is an empty list (`[]`), users do not need to set this input variable to deploy the module. When they do use it, they must set `allowed_methods` and `allowed_origins` for each object in the list; the other attributes are optional. This matches the behavior of the `aws_s3_bucket_cors_configuration` resource you will use to configure CORS.

Use the `cors_rules` variable by adding a new resource to `modules/aws-s3-static-website/main.tf`.

```Go
resource "aws_s3_bucket_cors_configuration" "web" {
  count = length(var.cors_rules) > 0 ? 1 : 0

  bucket = aws_s3_bucket.web.id

  dynamic "cors_rule" {
    for_each = var.cors_rules

    content {
      allowed_headers = cors_rule.value["allowed_headers"]
      allowed_methods = cors_rule.value["allowed_methods"]
      allowed_origins = cors_rule.value["allowed_origins"]
      expose_headers  = cors_rule.value["expose_headers"]
      max_age_seconds = cors_rule.value["max_age_seconds"]
    }
  }
}
```

This resource uses the `dynamic` block to create a `cors_rule` block for each item in the `var.cors_rules` list. When the list is empty, the `count` meta-argument will evaluate to `0`, and Terraform will not provision this resource. Otherwise, the `dynamic` block will create a CORS rule for each object in the list. Since optional object attributes default to `null`, Terraform will not set values for them unless the module user specifies them.

Update the module block in `main.tf` in the repository root directory to use the new variable. These example rules limit `PUT` and `POST` requests to an example domain, and permit `GET` requests from anywhere.

```Go
module "website_s3_bucket" {
  source = "./modules/aws-s3-static-website"

  bucket_prefix = "module-object-attributes-"

  files = {
    terraform_managed = true
    www_path          = "${path.root}/www"
  }

  cors_rules = [
    {
      allowed_headers = ["*"],
      allowed_methods = ["PUT", "POST"],
      allowed_origins = ["https://test.example.com"],
      expose_headers  = ["ETag"],
      max_age_seconds = 3000
    },
    {
      allowed_methods = ["GET"],
      allowed_origins = ["*"]
    }
  ]

  tags = {
    terraform     = "true"
    environment   = "dev"
    public-bucket = true
  }
}
```