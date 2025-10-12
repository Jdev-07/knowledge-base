
**Finding Modules**

You can search for any module (such as "vault", "vpc", "database") on the registry page, and it will list all modules that match with you search. To narrow the results, you can use filters. 

**Using Modules**

The Terraform Registry is directly integrated into Terraform, so you can refer to a module like this: `<NAMESPACE>/<NAME>/<PROVIDER>`. For example: `hashicorp/consul/aws`

```Go
module "consul" {
  source = "hashicorp/consul/aws"
  version = "0.1.0"
}
```


The `terraform init` command will download and cache any modules referenced by a configuration. 

**Private Registry Module Sources**

You can also use modules from a private registry using the following format: `<HOSTNAME>/<NAMESPACE>/<NAME>/<PROVIDED>`. It is just like the format for public registry, but adding the hostname:

```Go
module "vpc" {
  source = "app.terraform.io/example_corp/vpc/aws"
  version = "0.9.3"
}
```

Depending on the registry you're using, you might also need to configure credentials to access modules.

**Module versions**

Each module in the registry is versioned. These versions syntactically must follow semantic versioning. In addition to pure syntax, we encourage all modules to follow the full guidelines of semantic versioning.

# Module versioning

A module is container for multiple resources that are deployed together. 

Every Terraform configuration has at least one module, known as its _root module_, which consists of the resources defined in the `.tf` files in the main working directory.

A module can call other modules, which lets you include the child module's resources into the configuration in a concise way. Modules can also be called multiple times, either within the same configuration or in separate configurations, allowing resource configurations to be packaged and re-used.

## Calling a Child Module

To call a module means to include the contents of that module into the configuration with specific values. You include modules using the module block

```Go
module "servers" {
  source = "./app-cluster"

  servers = 5
}
```

- The calling module includes this block to include the child module.
- The label was `servers` is the local name, which the calling module can use to refer to the instance.
- Within the brackets are the arguments for the module:
	- The `source` argument is mandatory for all modules
	- The `version` is recommended for the registry
	- Most other argument correspond to input variables.
	- Terraform define a few other meta-arguments that can be used with all modules

**Source**

Required argument, which is a meta-argument  defined by Terraform. Its value is either a local directory or a remote module source. This value is a literal string with no template sequences. 

The same module can be called in multiple block to create multiple copies of the resources.

After adding, removing, or modifying module blocks. you must re-run `terraform init`. If you want to upgrade the already-installed module; use the flag `upgrade`.

**Version**

When using modules from registry, it is highly recommended to define version constraints to avoid unexpected or unwanted changes. 

```Go
module "consul" {
  source  = "hashicorp/consul/aws"
  version = "0.0.5"

  servers = 3
}
```

The `version` argument accepts a version constraint string. Terraform will always use newest version that meets the constraint. 

Version constraints are supported only for modules installed from a module registry, either public or private registry. Modules sourced from local file paths do not support version.

**Meta-arguments**

Along with source and version, Terraform defines a few more optional meta-arguments that have special meaning across all modules, described in more detail in the following pages:

- `count` - Creates multiple instances of a module from a single module block.
- `for_each` - Creates multiple instances of a module from a single module block. 
- `providers` - Passes provider configurations to a child module. If not specified, the child module inherits all of the default (un-aliased) provider configurations from the calling module.
- `depends_on` - Creates explicit dependencies between the entire module and the listed targets.

## Accessing Module Output Values

The resources defined in a module are encapsulated, so the calling module cannot access their attributes directly. However, the child module can declare output values so the calling module can interact with them. 

For example, if the `./app-cluster` module referenced in the example above exported an output value named `instance_ids` then the calling module can reference that result using the expression `module.servers.instance_ids`:

```Go
resource "aws_elb" "example" {
  # ...

  instances = module.servers.instance_ids
}
```

## Transferring Resource State Into Modules

Moving `resource` blocks from one module into several child modules causes Terraform to see the new location as an entirely different resource. As result, Terraform plans to replace them.

To preserve existing objects, you can use refactoring blocks to record the old and new addresses for each resource instance. This directs Terraform to treat existing objects at the old addresses as if they had originally been created at the corresponding new addresses.

## Replacing resource within a module

You may have an object that needs to be replaced with a new object for a reason that isn't automatically visible to Terraform, such as if a particular virtual machine is running on degraded underlying hardware. In this case, you can use [the `-replace=...` planning option](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#replace-address) to force Terraform to propose replacing that object.

If the object belongs to a resource within a nested module, specify the full path to that resource including all of the nested module steps leading to it. For example:

```Shell
terraform plan -replace=module.example.aws_instance.example
```

The above selects a `resource "aws_instance" "example"` declared inside a `module "example"` child module declared inside your root module.

Because replacing is a very disruptive action, Terraform only allows selecting individual resource instances. There is no syntax to force replacing _all_ resource instances belonging to a particular module.