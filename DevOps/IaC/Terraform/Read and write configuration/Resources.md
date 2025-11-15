# Overview

Resources are the most important element in the Terraform language. Each resource block describes one or more infrastructure objects, such as virtual networks, compute instances or higher-level components such as DNS records.   

[Resources blocks]() documents the syntax for declaring resources

[Resource behavior]() explains more in detail how Terraform handles resource declarations when applying a configuration. 

The meta-arguments sections documents special arguments that can be used with every resource type. 

Provisioners documents configuring post-creation actions for a resource using the `provisioner` and `connection` blocks.

## Resource Blocks

### Resource Syntax

The resource declarations  can include a number of advanced  features, but only a small subset are required for initial use. 

```Go
resource "aws_instance" "web" {
  ami           = "ami-a1b2c3d4"
  instance_type = "t2.micro"
}
```

The `resource` block declares a resource type `aws_instance` and is given a local name `web` which is used locally elsewhere in the same module, having no significance  outside of the module's scope. The resource type and name together serve as identifier so mush be unique within a module. 

Within the brackets are located the configuration arguments for the resource itself. 

### Resource Types

Each resource is associated to a single resource type, which determines the type of infrastructure  object it manages and what arguments and other attributes the resource supports. 

**Providers**

Each resource type is implemented by a provider, which is a plugin for Terraform that offers a collection of resource types. In order to manage  resources, a Terraform module must specify which providers it requires. Make sure to provide the necessary configurations so Terraform can access to their remote APIs. 

**Resource Arguments**

Most of the arguments within the body of a `resource` block are specific to the selected resource type. The resource type's documentation lists which arguments are available and how their values must be formatted. 

## Resource behavior 

In a `resource` block we declare the infrastructure  object(s) that we want to exists with the given settings. If writing new configuration for first time, then the infrastructure object will only exist in the configuration, and will not represent any real infrastructure object.  Applying a Terraform configuration is the process of creating, updating, and destroying real infrastructure 

### How Terraform Applies a Configuration

When Terraform creates new infrastructure objects, all the related information is saved in the Terraform' s state, allowing to be updated or destroyed in future changes. For resource block that already have an associated infrastructure object in state, Terraform compares the actual configuration of the object with the arguments given in the configuration and, if necessary, updates the object to match the configuration.

In summary, applying a Terraform configuration will:

- _Create_ resources that exist in the configuration but are not associated with a real infrastructure object in the state.
- _Destroy_ resources that exist in the state but no longer exist in the configuration.
- _Update in-place_ resources whose arguments have changed.
- _Destroy and re-create_ resources whose arguments have changed but which cannot be updated in-place due to remote API limitations.

### Accessing Resource Attributes

Using expressions you can information about resource in the same module, and can help to configure other resources.  The syntax to refers to attributes is the following: `<RESOURCE_TYPE>.<NAME>.<ATTRIBUTE>`

Many read-only attributes with information obtained from the remote API after the creation are provided. 

Many providers also includes data sources, which are a special type of resource used only for looking up information. 

The list of attributes that a resource o data source provides, check their documentation. 
### Resource Dependencies

Most resources in a configuration don’t need explicitly defined relationships because Terraform can detect resource dependencies automatically. It analyzes expressions within resources to find references and use them for implicit ordering. However, some resources must be processed after specific ones due to how they are structured or how they work, and because some dependencies cannot be easily recognized. In these cases, we must use the `depends_on` meta-argument.

### Local-only Resources


While most resource types correspond to an infrastructure object type that is managed via a remote network API, there are certain specialized resource types that operate only within Terraform itself, calculating some results and saving those results in the state for future use.


## Meta-arguments

### `depends_on`

We must use this argument to handle hidden resource or module dependencies that Terraform cannot automatically infer.

Explicitly specifying a dependency is only necessary when a resource or module relies on some other resource's behavior but _doesn't_ access any of that resource's data in its arguments.

This argument is available in `module` blocks and in all `resource` blocks, regardless of resource type. For example:

```Go
resource "aws_iam_role" "example" {
  name = "example"

  # assume_role_policy is omitted for brevity in this example. See the
  # documentation for aws_iam_role for a complete example.
  assume_role_policy = "..."
}

resource "aws_iam_instance_profile" "example" {
  # Because this expression refers to the role, Terraform can infer
  # automatically that the role must be created first.
  role = aws_iam_role.example.name
}

resource "aws_iam_role_policy" "example" {
  name   = "example"
  role   = aws_iam_role.example.name
  policy = jsonencode({
    "Statement" = [{
      # This policy allows software running on the EC2 instance to
      # access the S3 API.
      "Action" = "s3:*",
      "Effect" = "Allow",
    }],
  })
}

resource "aws_instance" "example" {
  ami           = "ami-a1b2c3d4"
  instance_type = "t2.micro"

  # Terraform can infer from this that the instance profile must
  # be created before the EC2 instance.
  iam_instance_profile = aws_iam_instance_profile.example

  # However, if software running in this EC2 instance needs access
  # to the S3 API in order to boot properly, there is also a "hidden"
  # dependency on the aws_iam_role_policy that Terraform cannot
  # automatically infer, so it must be declared explicitly:
  depends_on = [
    aws_iam_role_policy.example,
  ]
}

```

The `depends_on` meta-argument, if present, must be a list of references to other resources or child modules in the same calling module. Arbitrary expressions are not allowed in the `depends_on` argument value, because its value must be known before Terraform knows resource relationships and thus before it can safely evaluate expressions.

The `depends_on` argument should be used only as a last resort. When using it, always include a comment explaining why it is being used, to help future maintainers understand the purpose of the additional dependency.

### `count`

By default a `resource` block defines only one infrastructure object, but sometimes you might want to deploy several similar objects without writing a separate block for each one. Terraforms offers two ways to do this, `count` and `for_each`

**Basic Syntax**

`count` is a meta-argument defined by Terraform and can used with modules and with every resource type. This  meta-arguments accepts a whole number, and creates that many instances of the resource or module. Each instance has a distinct infrastructure object associated with it, and each is separately created, updated or destroyed. 

```Go
resource "aws_instance" "server" {
  count = 4 # create four similar EC2 instances

  ami           = "ami-a1b2c3d4"
  instance_type = "t2.micro"

  tags = {
    Name = "Server ${count.index}"
  }
}
```


#### The `count` Object

In blocks where `count` is set, an additional count object is available in expressions, so you can modify the configuration of each instance. 

#### Using Expressions in `count`

The `count` meta-argument accepts numeric [expressions](https://developer.hashicorp.com/terraform/language/v1.1.x/expressions). However, unlike most arguments, the `count` value must be known _before_ Terraform performs any remote resource actions. This means `count` can't refer to any resource attributes that aren't known until after a configuration is applied (such as a unique ID generated by the remote API when an object is created).

#### Referring to Instances

When `count` is set, Terraform distinguishes between the block itself and the multiple _resource or module instances_ associated with it. Instances are identified by an index number, starting with `0`.

- [`<TYPE>.<NAME>`](https://developer.hashicorp.com/terraform/language/v1.1.x/meta-arguments/count#) or `module.<NAME>` (for example, `aws_instance.server`) refers to the resource block.
- [`<TYPE>.<NAME>[<INDEX>]`](https://developer.hashicorp.com/terraform/language/v1.1.x/meta-arguments/count#-1) or `module.<NAME>[<INDEX>]` (for example, `aws_instance.server[0]`, `aws_instance.server[1]`, etc.) refers to individual instances.

This is different from resources and modules without `count` or `for_each`, which can be referenced without an index or key.

Similarly, resources from child modules with multiple instances are prefixed with `module.<NAME>[<KEY>]` when displayed in plan output and elsewhere in the UI. For a module without `count` or `for_each`, the address will not contain the module index as the module's name suffices to reference the module.

#### When to use `for_each` Instead of `count`

If your instances are almost identical, `count` is appropriate. If some of their arguments need distinct values that can't be directly derived from an integer, it's safer to use `for_each`.

Before `for_each` was available, it was common to derive `count` from the length of a list and use `count.index` to look up the original list value:

```Go
variable "subnet_ids" {
  type = list(string)
}

resource "aws_instance" "server" {
  # Create one instance for each subnet
  count = length(var.subnet_ids)

  ami           = "ami-a1b2c3d4"
  instance_type = "t2.micro"
  subnet_id     = var.subnet_ids[count.index]

  tags = {
    Name = "Server ${count.index}"
  }
}

```


### `for_each`

`for_each` is a meta-argument defined by Terraform and can be used with modules and with every resource type. This meta-arguments accepts maps or a set of strings, and creates an instance for each item in the map or set. Each instance has a distinct infrastructure object associated with it, and each is separately created, updated and destroyed. 

Map:

```Go
resource "azurerm_resource_group" "rg" {
  for_each = {
    a_group = "eastus"
    another_group = "westus2"
  }
  name     = each.key
  location = each.value
}
```

Set of strings:

```Go
resource "aws_iam_user" "the-accounts" {
  for_each = toset( ["Todd", "James", "Alice", "Dottie"] )
  name     = each.key
}
```

Child module:

```Go
# my_buckets.tf
module "bucket" {
  for_each = toset(["assets", "media"])
  source   = "./publish_bucket"
  name     = "${each.key}_bucket"
}
```

```Go
# publish_bucket/bucket-and-cloudfront.tf
variable "name" {} # this is the input parameter of the module

resource "aws_s3_bucket" "example" {
  # Because var.name includes each.key in the calling
  # module block, its value will be different for
  # each instance of this module.
  bucket = var.name

  # ...
}

resource "aws_iam_user" "deploy_user" {
  # ...
}

```

#### The `each` Object

In blocks where `for_each` is set, an additional `each` object is available in expressions, so you can modify the configuration of each instance. This object has two attributes:

- [](https://developer.hashicorp.com/terraform/language/v1.1.x/meta-arguments/for_each#)[`each.key`](https://developer.hashicorp.com/terraform/language/v1.1.x/meta-arguments/for_each#each-key) — The map key (or set member) corresponding to this instance.
- [](https://developer.hashicorp.com/terraform/language/v1.1.x/meta-arguments/for_each#)[`each.value`](https://developer.hashicorp.com/terraform/language/v1.1.x/meta-arguments/for_each#each-value) — The map value corresponding to this instance. (If a set was provided, this is the same as `each.key`.)

#### Limitations on values used in `for_each`

- The keys of the maps must be known values, or you will get an error message that `for_each` has dependencies that cannot be determined before apply. 
- `for_each` keys cannot be the result (or rely on the result of) of impure functions, including `uuid`, `bcrypt`, or `timestamp`, as their evaluation is deferred during the main evaluation step.
- You cannot use **sensitive values** (like sensitive variables, outputs, or attributes) inside **`for_each`** in Terraform. This is because the values in `for_each` are used to name and identify resource instances, and Terraform always displays those identifiers in the UI. Since that would expose the sensitive data, Terraform blocks it and returns an error.
#### Using expressions in `for_each`

`for_each` accepts **maps** or **sets**, and Terraform must know its value **before** creating or changing any remote resources.  
Because of this, **`for_each` cannot use attributes that are only known after apply**, such as API-generated IDs.

You must provide `for_each` with a map or a set containing one element per desired resource instance. When using a set, you have to explicitly convert it (e.g., using `toset()`), because Terraform does **not automatically** convert lists or tuples to sets.

If your data is nested or comes from multiple sources, you can build a proper map/set using Terraform expressions, for example:

- Use **nested `for` + `flatten()`** to convert nested structures into a flat list.
    
- Use **`setproduct()`** to generate every combination of elements from multiple collections.

#### Chaining `for_each` between resources

When a resource is created using **`for_each`**, Terraform represents it as a **map of resource instances**. Because of that, you can use the output of one `for_each` resource **directly as the `for_each` of another resource**, as long as there is a **one-to-one relationship** between them.

If you create multiple `aws_vpc` resources using `for_each`, you can use that same map as the `for_each` for `aws_internet_gateway`, automatically creating one internet gateway per VPC.

```Go
variable "vpcs" {
  type = map(object({
    cidr_block = string
  }))
}

resource "aws_vpc" "example" {
  # One VPC for each element of var.vpcs
  for_each = var.vpcs

  # each.value here is a value from var.vpcs
  cidr_block = each.value.cidr_block
}

resource "aws_internet_gateway" "example" {
  # One Internet Gateway per VPC
  for_each = aws_vpc.example

  # each.value here is a full aws_vpc object
  vpc_id = each.value.id
}

output "vpc_ids" {
  value = {
    for k, v in aws_vpc.example : k => v.id
  }

  # The VPCs aren't fully functional until their
  # internet gateways are running.
  depends_on = [aws_internet_gateway.example]
}

```

This chaining pattern explicitly and concisely declares the relationship between the internet gateway instances and the VPC instances, which tells Terraform to expect the instance keys for both to always change together, and typically also makes the configuration easier to understand for human maintainers.

#### Referring to instances 

When `for_each` is set, Terraform distinguishes between the block itself and the multiple _resource or module instances_ associated with it. Instances are identified by a map key (or set member) from the value provided to `for_each`.

- [`<TYPE>.<NAME>`](https://developer.hashicorp.com/terraform/language/v1.1.x/meta-arguments/for_each#) or `module.<NAME>` (for example, `azurerm_resource_group.rg`) refers to the block.
- [`<TYPE>.<NAME>[<KEY>]`](https://developer.hashicorp.com/terraform/language/v1.1.x/meta-arguments/for_each#-1) or `module.<NAME>[<KEY>]` (for example, `azurerm_resource_group.rg["a_group"]`, `azurerm_resource_group.rg["another_group"]`, etc.) refers to individual instances.

This is different from resources and modules without `count` or `for_each`, which can be referenced without an index or key.

Similarly, resources from child modules with multiple instances are prefixed with `module.<NAME>[<KEY>]` when displayed in plan output and elsewhere in the UI. For a module without `count` or `for_each`, the address will not contain the module index as the module's name suffices to reference the module.

#### Using sets

The Terraform language doesn't have a literal syntax for [set values](https://developer.hashicorp.com/terraform/language/v1.1.x/expressions/type-constraints#collection-types), but you can use the `toset` function to explicitly convert a list of strings to a set:

```Go
locals {
  subnet_ids = toset([
    "subnet-abcdef",
    "subnet-012345",
  ])
}

resource "aws_instance" "server" {
  for_each = local.subnet_ids

  ami           = "ami-a1b2c3d4"
  instance_type = "t2.micro"
  subnet_id     = each.key # note: each.key and each.value are the same for a set

  tags = {
    Name = "Server ${each.key}"
  }
}

```

Conversion from list to set discards the ordering of the items in the list and removes any duplicate elements. `toset(["b", "a", "b"])` will produce a set containing only `"a"` and `"b"` in no particular order; the second `"b"` is discarded.

If you are writing a module with an [input variable](https://developer.hashicorp.com/terraform/language/v1.1.x/values/variables) that will be used as a set of strings for `for_each`, you can set its type to `set(string)` to avoid the need for an explicit type conversion:

```Go
variable "subnet_ids" {
  type = set(string)
}

resource "aws_instance" "server" {
  for_each = var.subnet_ids

  # (and the other arguments as above)
}
```

### `providers`

This meta-argument basically  specifies which provider configuration to use for the resource. Its value should be an unquoted `<PROVIDER>.<ALIAS>`  reference. You can optionally create multiple configuration for a single provider (usually to manage resources in different regions). Each provide can have a default configuration and any number of alternate configurations.

Terraform interprets the initial word in the resource type name, separated by underscores, as the local name of a provider, and uses that provider's default configuration. But setting alternate configurations allow selecting alternate configuration. 

```Go
# default configuration
provider "google" {
  region = "us-central1"
}

# alternate configuration, whose alias is "europe"
provider "google" {
  alias  = "europe"
  region = "europe-west1"
}

resource "google_compute_instance" "example" {
  # This "provider" meta-argument selects the google provider
  # configuration whose alias is "europe", rather than the
  # default configuration.
  provider = google.europe

  # ...
}
```

A resource always has an implicit dependency on its associated provider, to ensure that the provider is fully configured before any resource actions are taken.

### The lifecycle Meta-Argument

```Go
resource "azurerm_resource_group" "example" {
  # ...

  lifecycle {
    create_before_destroy = true
  }
}
```

The **`lifecycle` block** is a meta-argument available for any resource. It controls how Terraform creates, updates, or destroys resources. It supports three main options:


#### 1. `create_before_destroy` (bool)

- Normally, Terraform **destroys** a resource first and then **creates** a replacement if it cannot be updated in place.
    
- Setting `create_before_destroy = true` reverses this: Terraform **creates the new resource first**, then destroys the old one.
    
- Use carefully—some resources cannot exist twice due to naming or API constraints.
    
- **Destroy provisioners do NOT run** when this is enabled.

#### 2. `prevent_destroy` (bool)

- When set to `true`, Terraform **blocks any plan** that would destroy the resource.
    
- Useful for critical or expensive resources (e.g., databases).
    
- But it also prevents `terraform destroy` from working for that resource.
    
- If the resource block is removed from the configuration, the protection is removed too.

#### 3. `ignore_changes` (list of attribute names)

- Terraform normally updates a resource when the real-world state drifts.
    
- `ignore_changes` tells Terraform to **ignore specific attributes** during update planning.
    
- Good when:
    
    - External systems modify certain fields (e.g., tags managed by another agent).
        
    - Some inputs may change after creation but should not trigger updates.


## Resource addressing

