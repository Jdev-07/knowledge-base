
# Inputs
## Input variables

Input variables let you customize module aspects without editing the module itself. This makes the modules composable and reusable. 

When you declare variables in the root module, you can set the values in the CLI. In the other side, for child modules you need to pass values in the module block. 

Terraform logic can be compared to traditional programming.

- input variable are like functions arguments
- output values are like function return values
- local values are like function's temporary local variables.

### Declaring an Input Variable

Each variable accepted by a module must be declared using the `variable` block.

```Go
variable "image_id" {
  type = string
}

variable "availability_zone_names" {
  type    = list(string)
  default = ["us-west-1a"]
}

variable "docker_ports" {
  type = list(object({
    internal = number
    external = number
    protocol = string
  }))
  default = [
    {
      internal = 8300
      external = 8300
      protocol = "tcp"
    }
  ]
}
```

The label after the `variable` keyword is the name of the variable. This must unique in that module level. This name is used to assign a value from outside (caller module)

The name can be any valid identifier, except the reserved keywords. 

### Arguments

Terraform CLI defines the following optional arguments for variable declaration

#### Default

If this argument is present, the variable is considered to be optional. If you do not set any value, the default will be used. This must be a literal value and cannot reference other objects.

#### Type Constraints

This argument in a `variable` block allows to restrict the type of value that will be accepted. If not specified, any type is accepted.

Specifying type constraints is helpful for users of the module, and allow Terraform to return an error message if the wrong type is used.

The supported keywords are: `string`, `number` and `bool`.

However, complex types such as collections can be specified: `list(<TYPE>)`, `set(<TYPE>)`, `map(<TYPE>)`, `object({})`, `tuple([<>.<>])`

The keyword `any` indicates that any type is acceptable.

If both `type` and `default` are specified, then make sure the provided value meet the constraint.

#### Input Variable  Documentation

Describing the purpose of each variable using the optional `description` helps users to understand much better.

```Go
variable "image_id" {
  type        = string
  description = "The id of the machine image (AMI) to use for the server."
}
```

The description must be concise an explain the purpose of the variable and what type of value is expected. 

#### Custom Validation Rules

Module author can specify custom validation rules for particular variable using a validation block nested within the corresponding `variable` block.

```Go
variable "image_id" {
  type        = string
  description = "The id of the machine image (AMI) to use for the server."

  validation {
    condition     = length(var.image_id) > 4 && substr(var.image_id, 0, 4) == "ami-"
    error_message = "The image_id value must be a valid AMI id, starting with \"ami-\"."
  }
}
```

The `condition` argument is an expression that must use the value of the variable to return true if the value is valid. 

If the failure of an expression is the basis of the validation decision, use the can function to detect such errors. For example:

```Go
variable "image_id" {
  type        = string
  description = "The id of the machine image (AMI) to use for the server."

  validation {
    # regex(...) fails if it cannot find a match
    condition     = can(regex("^ami-", var.image_id))
    error_message = "The image_id value must be a valid AMI id, starting with \"ami-\"."
  }
}
```

If `condition` evaluates to `false`. Terraform will produce an error message that includes the sentences given in `error_message`

#### Suppressing Values in CLI Output

Setting a variable as `sensitive` prevents Terraform from showing its value in the `plan` or `apply`  output. 

Terraform will still record sensitive values in the state, and so anyone who can access the state will have access to the sensitive values cleartext.

You must set `sensitive` argument as true

```Go
variable "user_information" {
  type = object({
    name    = string
    address = string
  })
  sensitive = true
}

resource "some_resource" "a" {
  name    = var.user_information.name
  address = var.user_information.address
}
```

Any expressions whose result depends on the sensitive variable will be treated as sensitive themselves, and so in the above example the two arguments of `resource "some_resource" "a"` will also be hidden in the plan output:

```Log
Terraform will perform the following actions:

  # some_resource.a will be created
  + resource "some_resource" "a" {
      + name    = (sensitive)
      + address = (sensitive)
    }

Plan: 1 to add, 0 to change, 0 to destroy.
```


In some cases where you use a sensitive variable inside a nested block, Terraform may treat the entire block as redacted. This happens for resource types where all of the blocks of a particular type are required to be unique, and so disclosing the content of one block might imply the content of a sibling block.

```Log
  # some_resource.a will be updated in-place
  ~ resource "some_resource" "a" {
      ~ nested_block {
          # At least one attribute in this block is (or was) sensitive,
          # so its contents will not be displayed.
        }
    }
```

A provider can also declare an attribute as sensitive, which will cause Terraform to hide it from regular output regardless of how you assign it a value. 

If you use a sensitive value from as part of an output value then Terraform will require you to also mark the output value itself as sensitive, to confirm that you intended to export it.

**Cases where Terraform may disclose a sensitive variable**

A `sensitive` variable is hidden inside of Terraform itself. However, when this variable is sent to any provider, is no longer protected, because the providers would need the real value to create a resource. If the operation fails, the provider might accidentally return a message including the secret value.

You still need to handle secrets carefully,  for example, using a secret manager or keeping them out of IDs and error messages.

```Log
  # random_pet.animal will be created
  + resource "random_pet" "animal" {
      + id        = (known after apply)
      + length    = 2
      + prefix    = (sensitive)
      + separator = "-"
    }

Plan: 1 to add, 0 to change, 0 to destroy.

...

random_pet.animal: Creating...
random_pet.animal: Creation complete after 0s [id=jae-known-mongoose]
```

#### Disallowing Null Input Variables

The `nulleable` argument in variable block controls whether the module caller may assign the value `null` to the variable

```Go
variable "example" {
  type     = string
  nullable = false 
}
```


By default the value for `nulleable` is `true`. When this argument is set to true, is valid to set a `null` value. Therefore you must have into account the possibility of passing a `null` value. Setting `nulleable` as `false` ensures that the variable will never be `null`

The `nullable` argument only controls where the direct value of the variable may be `null`. For variables of collection or structural types, such as lists or objects, the caller may still use `null` in nested elements or attributes, as long as the collection or structure itself is not null.

### Using Input Variable Values

Within the module that declared a variable, its value can be accessed from within [expressions](https://developer.hashicorp.com/terraform/language/v1.1.x/expressions) as `var.<NAME>`, where `<NAME>` matches the label given in the declaration block:

```Go
resource "aws_instance" "example" {
  instance_type = "t2.micro"
  ami           = var.image_id
}
```

Note: Input variables are created by a variable block, but you reference them as attributes on an object named var.

The value assigned to a variable can only be accessed in expressions within the module where it was declared.

### Assigning Values to Root Module Variables

 When variables are declared in the root module of your configuration, they can be set in a number of ways:

- In a Terraform Cloud workspace.
- Individually, with the -var command line option.
- In variable definitions (.tfvars) files, either specified on the command line or automatically loaded.
- As environment variables.

**Variables on the Command Line**

To specify individual variables on the command line, use the `-var` option when running the `terraform plan` and `terraform apply` commands:

```Shell
terraform apply -var="image_id=ami-abc123"
terraform apply -var='image_id_list=["ami-abc123","ami-def456"]' -var="instance_type=t2.micro"
terraform apply -var='image_id_map={"us-east-1":"ami-abc123","us-east-2":"ami-def456"}'
```

The above examples show appropriate syntax for Unix-style shells, such as on Linux or macOS.

**Variable Definitions Files**

To set lots of variables, it is more convenient to specify their values in a _variable definitions file_ (with a filename ending in either `.tfvars` or `.tfvars.json`) and then specify that file on the command line with `-var-file`:

```Shell
terraform apply -var-file="testing.tfvars"
```

**Note:** This is how Terraform Cloud passes [workspace variables](https://developer.hashicorp.com/terraform/cloud-docs/workspaces/variables) to Terraform.

A variable definitions file uses the same basic syntax as Terraform language files, but consists only of variable name assignments:

```Go
image_id = "ami-abc123"
availability_zone_names = [
  "us-east-1a",
  "us-west-1c",
]
```

Terraform also automatically loads a number of variable definitions files if they are present:

- Files named exactly `terraform.tfvars` or `terraform.tfvars.json`.
- Any files with names ending in `.auto.tfvars` or `.auto.tfvars.json`.

Files whose names end with `.json` are parsed instead as JSON objects, with the root object properties corresponding to variable names:

```Go
{
  "image_id": "ami-abc123",
  "availability_zone_names": ["us-west-1a", "us-west-1c"]
}
```

**Environment  Variables**

This other way to set variables, using environment  variables (in the system, not inside of Terraform files).

This is useful when running multiple Terraform commands using the same variables, instead of retyping them or create a `.tfvars` file. 

Terraform finds variables with this format: `TF_VAR_<variable_name>` and automatically uses that value for that specific variable. 

```Shell
export TF_VAR_bucket_name="my-terraform-bucket"
```

Terraform will see that `TF_VAR_bucket_name` exists, and use `"my-terraform-bucket"` as the value for the variable `bucket_name`.

Terraform automatically checks your environment for variables that start with **`TF_VAR_`**,  
and uses them as input variables,  making automation and scripting easier.

**Complex-typed Values**

Setting variable values in a variable definition file is easier to assign complex-typed  values because you can use the Terraform's usual syntax. 

Some special rules apply to the `-var` command line option and to environment variables. For convenience, Terraform defaults to interpreting `-var` and environment variable values as literal strings, which need only shell quoting, and no special quoting for Terraform. For example, in a Unix-style shell:

```Bash
export TF_VAR_image_id='ami-abc123'
```

However, if a root module variable uses a [type constraint](https://developer.hashicorp.com/terraform/language/v1.1.x/values/variables#type-constraints) to require a complex value (list, set, map, object, or tuple), Terraform will instead attempt to parse its value using the same syntax used within variable definitions files, which requires careful attention to the string escaping rules in your shell:

```Shell
export TF_VAR_availability_zone_names='["us-west-1b","us-west-1d"]'
```

For readability, and to avoid the need to worry about shell escaping, we recommend always setting complex variable values via variable definitions files.

**Values for undeclared values**

There are some cases where you mistakenly provide/define a variable value for an undeclared `variable {}`. Deepening on the case you may get an error or warning. 

- If you set a variable value for undeclared variables defined as env variables, you will not get an error or warning. This is because the variable can be declared but never used.
- If you provide values  for undeclared variable defined in a file, you will get a warning. This is to help in cases where you have provided a variable value meant for a variable declaration,, but perhaps there is a mistake in the value definition.

```Go
variable "moose" {
  type = string
}
```

```Go
mosse = "Moose"
```

Will cause Terraform to warn you that there is no variable declared `"mosse"`, which can help you spot this mistake.

- If you provide values for undeclared variables on the command line, Terraform will error. To avoid this error, either declare a variable block for the value, or remove the variable value from your Terraform call.

**Variable Definition Precedence**

The mechanisms for setting variables can be used together in any combination. If the same variable is assigned multiple values, Terraform uses the _last_ value it finds, overriding any previous values. Note that the same variable cannot be assigned multiple values within a single source.

Terraform loads variables in the following order, with later sources taking precedence over earlier ones:

- Environment variables
- The `terraform.tfvars` file, if present.
- The `terraform.tfvars.json` file, if present.
- Any `*.auto.tfvars` or `*.auto.tfvars.json` files, processed in lexical order of their filenames.
- Any `-var` and `-var-file` options on the command line, in the order they are provided. (This includes variables set by a Terraform Cloud workspace.)

## Customize Terraform configuration with variables

Unlike variables found in programming languages, Terraform's input variables don't change values during a Terraform run such as plan, apply, or destroy. Instead, they allow users to more safely customize their infrastructure by assigning different values to the variables before execution begins, rather than editing configuration files manually.

In this tutorial, I used Terraform to deploy a web application on AWS. The supporting infrastructure includes a VPC, load balancer, and EC2 instances. I parameterized this configuration with Terraform input variables.

![[terraform-24.png]]

Repository I cloned: [Terraform variables](https://github.com/hashicorp-education/learn-terraform-variables)

After cloning the repo, I initialized the configuration:

```Shell
terraform init
```


Then I applied the configuration

```Shell
terraform apply
```

Once the terraform run has been completed, I got the following

```Log
Apply complete! Resources: 43 added, 0 changed, 0 destroyed.

Outputs:
```


**Parameterize the configuration**

Variable declarations can appear anywhere in your configuration files. However, we recommend putting them into a separate file called `variables.tf` to make it easier for users to understand how they can customize the configuration.

To parameterize an argument with an input variable, you must first define the variable, then replace the hardcoded value with a reference to that variable in your configuration.

```Go
variable "aws_region" {
  description = "AWS region"
  type        = string
  default     = "us-west-2"
}
```


Variable blocks have three optional arguments.

- **Description**: A short description to document the purpose of the variable.
- **Type**: The type of data contained in the variable.
- **Default**: The default value.

It is recommended to setting the description and type for all variables, and the default when necessary.

Terraform does not support unassigned variables, therefore you make sure assign all values before terraform can apply the configuration.

Variable values must be literal, and cannot use cannot use computed values like resource attributes, expressions, or other variables.

**Complex-typed values**

The variables you have used so far have all been single values. Terraform calls these types of variables _simple_. Terraform also supports _collection_ variable types that contain more than one value. Terraform supports several collection variable types.

- **List:** A sequence of values of the same type.
- **Map:** A lookup table, matching keys to values, all of the same type.
- **Set:** An unordered collection of unique values, all of the same type.

A good scenario to use list variables is when setting the `private_subnets` and `public_subnets` arguments for the VPC. Make this configuration easier to use and customizable by using lists and the `slice()` function.

Example

```Go
variable "public_subnet_count" {
  description = "Number of public subnets."
  type        = number
  default     = 2
}

variable "private_subnet_count" {
  description = "Number of private subnets."
  type        = number
  default     = 2
}

variable "public_subnet_cidr_blocks" {
  description = "Available cidr blocks for public subnets."
  type        = list(string)
  default     = [
    "10.0.1.0/24",
    "10.0.2.0/24",
    "10.0.3.0/24",
    "10.0.4.0/24",
    "10.0.5.0/24",
    "10.0.6.0/24",
    "10.0.7.0/24",
    "10.0.8.0/24",
  ]
}

variable "private_subnet_cidr_blocks" {
  description = "Available cidr blocks for private subnets."
  type        = list(string)
  default     = [
    "10.0.101.0/24",
    "10.0.102.0/24",
    "10.0.103.0/24",
    "10.0.104.0/24",
    "10.0.105.0/24",
    "10.0.106.0/24",
    "10.0.107.0/24",
    "10.0.108.0/24",
  ]
}
```

Each element in these lists must be a string. List elements must all be the same type, but can be any type, including complex types like `list(list)` and `list(map)`.

Like lists and arrays used in most programming languages, you can refer to individual items in a list by index, starting with 0. Terraform also includes several functions that allow you to manipulate lists and other variable types.

Use the [`slice()`](https://developer.hashicorp.com/terraform/language/functions/slice) function to get a subset of these lists.

The Terraform `console` command opens an interactive console that you can use to evaluate expressions in the context of your configuration. This can be very useful when working with and troubleshooting variable definitions.

```Log
PS C:\Users\jony2\Desktop\Hands-on-Labs\Terraform\learn-terraform-variables> terraform console
> var.private_subnet_cidr_blocks
tolist([
  "10.0.101.0/24",
  "10.0.102.0/24",
  "10.0.103.0/24",
  "10.0.104.0/24",
  "10.0.105.0/24",
  "10.0.106.0/24",
  "10.0.107.0/24",
  "10.0.108.0/24",
])
> var.private_subnet_cidr_blocks[1]
"10.0.102.0/24"
> slice(var.private_subnet_cidr_blocks, 0, 3)
tolist([
  "10.0.101.0/24",
  "10.0.102.0/24",
  "10.0.103.0/24",
])
> exit
```


Terraform also supports two _structural_ types. Structural types have a fixed number of values that can be of different types.

- **Tuple:** A fixed-length sequence of values of specified types.
- **Object:** A lookup table, matching a fixed set of keys to values of specified types.

**Interpolate variables in string**

Terraform configuration supports string interpolation — inserting the output of an expression into a string. This allows you to use variables, local values, and the output of functions to create strings in your configuration.

Update the names of the security groups to use the project and environment values from the `resource_tags` map.

**Validate Variables**

AWS load balancers have [naming restrictions](https://docs.aws.amazon.com/elasticloadbalancing/2012-06-01/APIReference/API_CreateLoadBalancer.html). Load balancer names must be no more than 32 characters long, and can only contain a limited set of characters.

Now, use variable validation to restrict the possible values for the project and environment tags.

Replace your existing `resource tags` variable in `variables.tf` with the below code snippet, which includes validation blocks to enforce character limits and character sets on both `project` and `environment` values.

```Go
variable "resource_tags" {
  description = "Tags to set for all resources"
  type        = map(string)
  default     = {
    project     = "my-project",
    environment = "dev"
  }

  validation {
    condition     = length(var.resource_tags["project"]) <= 16 && length(regexall("[^a-zA-Z0-9-]", var.resource_tags["project"])) == 0
    error_message = "The project tag must be no more than 16 characters, and only contain letters, numbers, and hyphens."
  }

  validation {
    condition     = length(var.resource_tags["environment"]) <= 8 && length(regexall("[^a-zA-Z0-9-]", var.resource_tags["environment"])) == 0
    error_message = "The environment tag must be no more than 8 characters, and only contain letters, numbers, and hyphens."
  }
}
```


This ensures that the length of the load balancer name does not exceed 32 characters, or contain invalid characters. Using variable validation can be a good way to catch configuration errors early.

# Output Values

Outputs basically make information about the infrastructure available in the command line, and can expose information for other Terraform configuration to use. These output values are similar to return values in programming languages. 

Output values have several uses: 

- A child module can expose some of its attributes to a parent module
- Print certain values in the CLI output after running `terraform apply`
- Outputs configured in a remote state can be  access by other configuration via `terraform remote state` data source.

Resource instances managed by Terraform each export attributes whose values can be used elsewhere in configuration. Output values are a way to expose some of that information to the user of your module.

## Declaring an Output Value

All output values must be declared using an `output` block as follows:

```Go
output "instance_ip_addr" {
  value = aws_instance.server.private_ip
}
```

The label `instance_ip_addr` is the name, which must be a valid ID. This name is displayed to the user. 

The `value` argument takes an expression whose result is to be returned to the user. 

Note: Outputs are only rendered when Terraform applies your plan. Running terraform plan will not render outputs.

## Access Child Module Outputs

In a parent module, outputs of child modules are available in expressions as module `<MODULE NAME>.<OUTPUT NAME>` For example, if a child module named `web_server` declared an output named `instance_ip_addr`, you could access that value as `module.web_server.instance_ip_addr`.

## Optional Arguments

`output` blocks can optionally include `description`, `sensitive`, and `depends_on` arguments, which are described in the following sections.

### `description` - Output Value Documentation

The description of an `output` lets the user know what kind of value to expect. Providing a concise explanation makes the interface more user-friendly.

The `description` should be written from the user’s perspective rather than the maintainer’s.

```Go
output "instance_ip_addr" {
  value       = aws_instance.server.private_ip
  description = "The private IP address of the main server instance."
}
```

### `sensitive` - Suppressing Values in CLI Output

An output can be marked as `sensitive` using the `sensitive` argument as follows:

```GO
output "db_password" {
  value       = aws_db_instance.db.password
  description = "The password for logging in to the database."
  sensitive   = true
}
```

