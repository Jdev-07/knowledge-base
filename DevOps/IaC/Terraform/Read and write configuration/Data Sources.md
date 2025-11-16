# Overview

*Data sources* allow Terraform to use information defined outside of Terraform, defined by another separate Terraform configuration, or modified by functions. 

[Data Source - Terraform HCL](https://developer.hashicorp.com/terraform/language/v1.1.x/data-sources#selecting-a-non-default-provider-configuration)

## Using data sources

A data source is accessed via a kind of resource known as a data source, declared using a `data` block.

```Go
data "aws_ami" "example" {
  most_recent = true

  owners = ["self"]
  tags = {
    Name   = "app-server"
    Tested = "true"
  }
}
```

A `data` block tells to Terraform to read and retrieve information from a given data source and make it available using the local name. The local name and name together serve as an identifier, sou must be unique at module's scope.

Within the block are query constraints defined by the data source. Most arguments in this sections will depend on the data source. 

Managed resources (declared with a resource block) and data resources both accept arguments and expose attributes.
The difference is that managed resources create, update, and delete infrastructure, while data resources only read existing objects.
Usually, “resources” refers to managed resources when the context is clear.

## Data Source Arguments

Each data resource is associated with a single data source, which determines the kind of object to read o what query constraints arguments are available. Also, each data source belongs to a provider, which is a plugin that offers to Terraform with collections of resource types and data sources. 

Most arguments inside a data block depend on the specific data source and can use Terraform’s full expression features.
But Terraform also provides some meta-arguments that work for all data sources. These have special rules and limitations, which are explained in later sections.

## Data Resource Behavior

If a data resource uses only values that are known in advance, Terraform can read it early during the refresh phase. This lets Terraform retrieve the actual data before creating the plan, ensuring the plan uses real values.

Query constraint arguments can refer to values that are known until the apply phase, and any references to the results of the data resource will be known after the configuration has been applied.  

## Local-only Data Sources

Terraform has local-only data sources that run internally instead of calling external APIs. They work like regular data sources but their results are temporary and recalculated each time you create a plan.

## Data Resource Dependencies

Data resources dependencies have the same dependency behavior as defined for managed resources. Setting the `depends_on` meta-argument will defer reading of data source until all changes are applied. This behavior can be avoided when desired by indirectly referencing the managed resource values through a local value. 

## Multiple Resource Instances

Data resources also support `count` and `for_each` meta-arguments. As defined for managed resources is important to distinguish the resource itself from the multiple resources intensives it creates. Each instance will separately  read from its data source. 

## Lifecycle customizations

Data resources do not currently have any customization settings available for their lifecycle, but the `lifecycle` nested block is reserved in case any are added in future versions.

## Example

A data source configuration looks like the following:

```Go
# Find the latest available AMI that is tagged with Component = web
data "aws_ami" "web" {
  filter {
    name   = "state"
    values = ["available"]
  }

  filter {
    name   = "tag:Component"
    values = ["web"]
  }

  most_recent = true
}
```

## Description

A data block creates a uniquely named data instance with a specific type and configuration. The allowed configuration depends on the provider. Each data instance exposes attributes that can be referenced in other parts of the configuration using the `data.<type>.<name>.<attribute>` format.

```Go
resource "aws_instance" "web" {
  ami           = data.aws_ami.web.id
  instance_type = "t1.micro"
}
```

### Data Source Lifecycle

If a data instance uses only known arguments, Terraform reads it during the refresh phase so the plan can show the real values. If the arguments depend on computed values, Terraform waits until the apply phase to read it, and the plan will show those values as computed.