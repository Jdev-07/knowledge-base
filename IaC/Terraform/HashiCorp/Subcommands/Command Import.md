The `terraform import` command is used to [import existing resources](https://developer.hashicorp.com/terraform/cli/v1.1.x/import) into Terraform.

## Usage

Usage: `terraform import [options] ADDRESS ID`

Import will find the existing resource from ID and import it into your Terraform state at the given ADDRESS.

ADDRESS must be a valid [resource address](https://developer.hashicorp.com/terraform/cli/v1.1.x/state/resource-addressing). Because any resource address is valid, the import command can import resources into modules as well as directly into the root of your state.

ID is dependent on the resource type being imported. For example, for AWS instances it is the instance ID (`i-abcd1234`) but for AWS Route53 zones it is the zone ID (`Z12ABC4UGMOZ2N`). Please reference the provider documentation for details on the ID format. If you're unsure, feel free to just try an ID. If the ID is invalid, you'll just receive an error message.

Warning: Terraform expects that each remote object it is managing will be bound to only one resource address, which is normally guaranteed by Terraform itself having created all objects. If you import existing objects into Terraform, be careful to import each remote object to only one Terraform resource address. If you import the same object multiple times, Terraform may exhibit unwanted behavior. For more information on this assumption, see [the State section](https://developer.hashicorp.com/terraform/language/v1.1.x/state).

The command-line flags are all optional. The list of available flags are:

- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#)
    
    [`-config=path`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#config-path) - Path to directory of Terraform configuration files that configure the provider for import. This defaults to your working directory. If this directory contains no Terraform configuration files, the provider must be configured via manual input or environmental variables.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#)
    
    [`-input=true`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#input-true) - Whether to ask for input for provider configuration.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#)
    
    [`-lock=false`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#lock-false) - Don't hold a state lock during the operation. This is dangerous if others might concurrently run commands against the same workspace.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#)
    
    [`-lock-timeout=0s`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#lock-timeout-0s) - Duration to retry a state lock.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#)
    
    [`-no-color`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#no-color) - If specified, output won't contain any color.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#)
    
    [`-parallelism=n`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#parallelism-n) - Limit the number of concurrent operation as Terraform [walks the graph](https://developer.hashicorp.com/terraform/internals/v1.1.x/graph#walking-the-graph). Defaults to 10.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#)
    
    [`-provider=provider`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#provider-provider) - **Deprecated** Override the provider configuration to use when importing the object. By default, Terraform uses the provider specified in the configuration for the target resource, and that is the best behavior in most cases.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#)
    
    [`-var 'foo=bar'`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#var-foo-bar) - Set a variable in the Terraform configuration. This flag can be set multiple times. Variable values are interpreted as [literal expressions](https://developer.hashicorp.com/terraform/language/v1.1.x/expressions/types) in the Terraform language, so list and map values can be specified via this flag. This is only useful with the `-config` flag.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#)
    
    [`-var-file=foo`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/import#var-file-foo) - Set variables in the Terraform configuration from a [variable file](https://developer.hashicorp.com/terraform/language/v1.1.x/values/variables#variable-definitions-tfvars-files). If a `terraform.tfvars` or any `.auto.tfvars` files are present in the current directory, they will be automatically loaded. `terraform.tfvars` is loaded first and the `.auto.tfvars` files after in alphabetical order. Any files specified by `-var-file` override any values set automatically from files in the working directory. This flag can be used multiple times. This is only useful with the `-config` flag.
    

For configurations using the [Terraform Cloud CLI integration](https://developer.hashicorp.com/terraform/cli/v1.1.x/cloud) or the [`remote` backend](https://developer.hashicorp.com/terraform/language/v1.1.x/settings/backends/remote) only, `terraform import` also accepts the option [`-ignore-remote-version`](https://developer.hashicorp.com/terraform/cli/v1.1.x/cloud/command-line-arguments#ignore-remote-version).

For configurations using [the `local` backend](https://developer.hashicorp.com/terraform/language/v1.1.x/settings/backends/local) only, `terraform import` also accepts the legacy options [`-state`, `-state-out`, and `-backup`](https://developer.hashicorp.com/terraform/language/v1.1.x/settings/backends/local#command-line-arguments).

The **`terraform import`** command is used when you already have infrastructure created **outside of Terraform** (for example, an EC2 instance you launched manually in the AWS console) and you want Terraform to start managing it.

 **What happens when you run it**
    
    - Terraform updates its **state file** to include the resource.
        
    - It **does not create, modify, or destroy** the resource — it just starts tracking it.
        
    - Your `.tf` configuration file must contain a matching resource block. If not, Terraform will warn you.
        

---
**Flags / Options**  
    Some important ones:
    
    - `-config=path` → point to where your provider config is (defaults to current directory).
        
    - `-lock=false` → skips state locking (dangerous if multiple people work on the same state).
        
    - `-var` / `-var-file` → pass variables (useful if your config requires them).
        
    - `-parallelism=n` → control concurrency during import (default is 10).
        

---
 **Warnings / Gotchas**
    
    - ⚠️ One resource → one address. Don’t import the same resource into two places in Terraform; it confuses state.
        
    - Import only updates state, **not configuration** — you still need to write or adjust the `.tf` code so it matches the real resource.
        
    - If your `.tf` file doesn’t match the imported object, the next `terraform plan` will try to reconcile differences (possibly destroy/recreate!).


## Provider Configuration

Terraform will attempt to load configuration files that configure the provider being used for import. If no configuration files are present or no configuration for that specific provider is present, Terraform will prompt you for access credentials. You may also specify environmental variables to configure the provider.

The only limitation Terraform has when reading the configuration files is that the import provider configurations must not depend on non-variable inputs. For example, a provider configuration cannot depend on a data source.

As a working example, if you're importing AWS resources and you have a configuration file with the contents below, then Terraform will configure the AWS provider with this file.

```Go
variable "access_key" {}
variable "secret_key" {}

provider "aws" {
  access_key = "${var.access_key}"
  secret_key = "${var.secret_key}"
}
```

## Example: Import into Resource

This example will import an AWS instance into the `aws_instance` resource named `foo`:

```
$ terraform import aws_instance.foo i-abcd1234
```

## Example: Import into Module

The example below will import an AWS instance into the `aws_instance` resource named `bar` into a module named `foo`:

```
$ terraform import module.foo.aws_instance.bar i-abcd1234
```

## Example: Import into Resource configured with count

The example below will import an AWS instance into the first instance of the `aws_instance` resource named `baz` configured with [`count`](https://developer.hashicorp.com/terraform/language/v1.1.x/meta-arguments/count):

```
$ terraform import 'aws_instance.baz[0]' i-abcd1234
```

## Example: Import into Resource configured with for_each

The example below will import an AWS instance into the `"example"` instance of the `aws_instance` resource named `baz` configured with [`for_each`](https://developer.hashicorp.com/terraform/language/v1.1.x/meta-arguments/for_each):

Linux, Mac OS, and UNIX:

```
$ terraform import 'aws_instance.baz["example"]' i-abcd1234
```

PowerShell:

```
$ terraform import 'aws_instance.baz[\"example\"]' i-abcd1234
```

Windows `cmd.exe`:

```
$ terraform import aws_instance.baz[\"example\"] i-abcd1234
```


## Terraform import and move

### 🔹 `terraform import`

- **Purpose:** Bring an _existing resource in the real infrastructure_ (for example, an AWS EC2 instance that you created manually in the AWS Console) into Terraform’s **state file**.
    
- **Effect:** It updates the state so Terraform knows that the resource already exists, but it **does not write HCL code** for you. You still need to have the resource definition (`resource "aws_instance" "example" { ... }`) in your `.tf` files.
    
- **When to use:**
    
    - When you want to start managing an already-existing resource with Terraform.
        
    - Example:

```Bash
terraform import aws_instance.myserver i-0fc1520a3efb42663
```

### 🔹 `terraform state mv` (move)

- **Purpose:** Move a resource **inside Terraform state** from one address to another.
    
- **Effect:** It doesn’t touch real infrastructure; it only changes how Terraform tracks the resource.
    
- **When to use:**
    
    - When you rename a resource in code.
        
    - When you refactor your code (e.g., moving a resource into a module).
        
- **Example:**  
    Suppose your state has:

```Bash
aws_instance.old_name
```

But in your code you renamed it to:

```Bash
resource "aws_instance" "new_name" { ... }
```

Terraform will otherwise want to destroy `old_name` and create `new_name`.  
To fix this safely:

```Shell
terraform state mv aws_instance.old_name aws_instance.new_name
```