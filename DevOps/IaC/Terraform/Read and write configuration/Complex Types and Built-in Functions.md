# Complex Types Overview

A complex type is a type that groups multiple values into a single value. Complex types are represented by type constructors, but several of them also have shorthand keyword versions.

There are two categories of complex types: collection type and structural types. 

## Collection Types

A collection type groups multiple values of one other type as a single one. The type of value within a collection is called `element type`. All collections must have an element type.

For example, the type `list(string)` means "list of strings". 

There are three kinds of collection type in the Terraform language

- `list(any)` 
- `map(any)`: a collection of values where each is identified by string label
- `set(any)`: a collection  of unique values that do not have any secondary identifiers or ordering. 

## Structural Types

A structural type allows multiple values of distinct types to be grouped together as a single value. Structural types require a schema as an argument to specify which types are allowed for which element

There are two kinds of structural type in the Terraform language:

- `object(any)`: a collection of named attributes that each have their type
- `tuple(any)`: a sequence of elements identified by consecutive whole numbers starting with zero, where each element has its own type.

Example of object:

```HCL
{
  name = "John"
  age  = 52
}
```

Example of a tuple

```HCL
["a", 15, true]
```


# Built-in Functions

Terraform includes a number of built-in functions that can be called from your configuration, just like follows:

```Go
max(5, 12, 9)
```


The Terraform language does not support user-defined functions.

## Perform dynamic operations with functions

Terraform allows you to write declarative expressions to create infrastructure. While Terraform is not a programming language, it lets you to use built in functions to perform operations dynamically. 

There are three main function we can use to perform operations dynamically:

- `templatefile:` generates a script with interpolated values
- `lookup` retrieves the values of a single element from a map, given its key. 
- `file:` this functions lets you to use the contents of a file as-is within configuration.


## Dynamic Expressions

Terraform language supports complex expressions to allow you to compute or generate values for your infrastructure configuration. Expressions can be simple string or integer values, or more complex values to make your configuration more dynamic. 

**Conditional Expressions**

The conditional expressions will make your configuration more dynamic, it will select a value based on whether the expression evaluates to true or false. 

Code example:

```Go
resource "random_id" "id" {
  byte_length = 8
}

locals {
  name  = (var.name != "" ? var.name : random_id.id.hex)
  owner = var.team
  common_tags = {
    Owner = local.owner
    Name  = local.name
  }
}
```

The syntax of a conditional expression first defines the condition, then the outcomes for true and false evaluations. In this example, if `var.name` is not empty (`!= ""`), `local.name` is set to the `var.name` value; otherwise, the name is the `random_id`.

The example shown above can be a little bit simple, but you can create more complex expressions. 

The follow example is a conditional count criteria to  deploy VM instances

```Go
variable "high_availability" {
  type        = bool
  description = "If this is a multiple instance deployment, choose `true` to deploy 3 instances"
  default     = true
}
```

`main.tf`:

```Go
resource "aws_instance" "ubuntu" {
  count                       = (var.high_availability == true ? 3 : 1)
  ami                         = data.aws_ami.ubuntu.id
  instance_type               = "t2.micro"
  associate_public_ip_address = (count.index == 0 ? true : false)
  subnet_id                   = aws_subnet.subnet_public.id
  tags                        = merge(local.common_tags)
}
```

Analysis:

| Condition                                 | ?    | true value                            | :    | false value                        |
| ----------------------------------------- | ---- | ------------------------------------- | ---- | ---------------------------------- |
| If `var.high_availability` is set to true | then | Create three `aws_instance` resources | else | Create one `aws_instance` resource |
| If `count.index` is 0                     | then | Assign public IP                      | else | Do not assign public IP            |

**Splat expression**

Now that we have defined a conditional count criteria, we will deploy three `aws_instance`. In order to return the private IP of all of the instances, must use a splat `*` expression to create an output value.

The `splat` expression captures all objects in a list that share an attribute. The special `*` symbol iterates over all of the elements of a given list and returns information based on the shared attribute you define.

Without the splat expression, Terraform would not be able to output the entire array of your instances and would only return the first item in the array.

Configuration:

```Go
output "private_addresses" {
  description = "Private DNS for AWS instances"
  value       = aws_instance.ubuntu[*].private_dns
}
```

This expression mirrors capturing a specific element in an array. If you only wanted to return the third instance IP in the array of instances, you could do that by replacing the `*` with `2`.

The current `tags` output will error because there are multiple instances.

**Replace** the `tags` output block with the following `first_tags` output, which will return the first instance's tags.

```Go
output "first_tags" {
  description = "Instance tags for first instance"
  value       = aws_instance.ubuntu[0].tags
}
```

Open `main.tf` to add the new instances to the ELB configuration.

```Go
resource "aws_elb" "learn" {
##...
  instances                   = aws_instance.ubuntu[*].id
  idle_timeout                = 400
  connection_draining         = true
  connection_draining_timeout = 400
  tags                        = local.common_tags
}
```
