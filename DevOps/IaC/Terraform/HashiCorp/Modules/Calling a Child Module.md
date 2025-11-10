# Module Blocks

A module is a container for multiple resources that are used together.

Every Terraform configuration has at least one module, known as its _root module_, which consists of the resources defined in the `.tf` files in the main working directory.

A module can call other modules, which lets you include the child module's resources into the configuration in a concise way. Modules can also be called multiple times, either within the same configuration or in separate configurations, allowing resource configurations to be packaged and re-used.

## Calling a Child Module

Modules are called from within other models using the `module` blocks. When calling other modules, you need to include the content of that module into the configuration with specific  input values.

```Go
module "servers" {
  source = "./app-cluster"

  servers = 5
}
```

The module that includes the `module` block, is the calling module. The label after the `module` keyword is a local name to refer the child module. 

Within the brackets are the argument for the modules:

- The `source`is mandatory
- The `version` is recommended, specially if using modules from registry
- Most of the other arguments correspond to input variables
- Terraform defines a few other meta-arguments that can be used together, including `for_each` and `depends_on`

### `source`

All modules require a `source` argument, which is a meta-argument defined by Terraform. The source value is either the path to a local `dir` or a remote module source that Terraform should download when you run `terraform init`.

You can specify a source address in multiple `module` blocks to create multiple copies of the resources defined within. 
### `version`

When working with modules from registry, it is recommended to use the `version` argument to avoid unexpected  or unwanted changes.

```Go
module "consul" {
  source  = "hashicorp/consul/aws"
  version = "0.0.5"

  servers = 3
}
```

The `version` argument support a version constraint string. Terraform will use the newest installed version of the module that meets the constraints. if not acceptable are installed, it will download the newest version that meets the constraint.


### Meta-arguments

Along with `source` and `version`, Terraform defines a few more option meta-arguments that have special meaning across all modules. 

- `count`: creates multiple instances of a module from a single `module` block
- `for_each`: creates multiple instances of a module from a single `module` block
- `providers`: passes provider configurations to a child module
- `depends_on` creates explicit dependencies between the entire module and the listed targets.

## Accessing Module Output Values

The resources defined in a module are encapsulated, so the calling module cannot access their attributes directly. . However, the child module can declare output values to selectively export certain values to be accessed.

```Go
resource "aws_elb" "example" {
  # ...

  instances = module.servers.instance_ids
}

```


For more reference, access [[Calling a Child Module]]

