The `terraform state` command is used for advanced state management. As your Terraform usage becomes more advanced, there are some cases where you may need to modify the [Terraform state](https://developer.hashicorp.com/terraform/language/v1.1.x/state). Rather than modify the state directly, the `terraform state` commands can be used in many cases instead.

This command is a nested subcommand, meaning that it has further subcommands. These subcommands are listed to the left.

## Inspecting State

Terraform includes some commands for reading and updating state without taking any other actions.

- [The `terraform state list` command](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/state/list) shows the resource addresses for every resource Terraform knows about in a configuration, optionally filtered by partial resource address.
    
- [The `terraform state show` command](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/state/show) displays detailed state data about one resource.
    
- [The `terraform refresh` command](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/refresh) updates state data to match the real-world condition of the managed resources. This is done automatically during plans and applies, but not when interacting with state directly.

### Command: state list

## Usage

Usage: `terraform state list [options] [address...]`

The command will list all resources in the state file matching the given addresses (if any). If no addresses are given, all resources are listed.

The resources listed are sorted according to module depth order followed by alphabetical. This means that resources that are in your immediate configuration are listed first, and resources that are more deeply nested within modules are listed last.

For complex infrastructures, the state can contain thousands of resources. To filter these, provide one or more patterns to the command. Patterns are in [resource addressing format](https://developer.hashicorp.com/terraform/cli/v1.1.x/state/resource-addressing).

The command-line flags are all optional. The list of available flags are:

- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/state/list#)[`-state=path`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/state/list#state-path) - Path to the state file. Defaults to "terraform.tfstate". [Legacy option for the local backend only](https://developer.hashicorp.com/terraform/language/v1.1.x/backend/local#command-line-arguments).
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/state/list#)[`-id=id`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/state/list#id-id) - ID of resources to show. Ignored when unset.

#### Example: All Resources

This example will list all resources, including modules:

```bash
terraform state list
```

```bash
aws_instance.foo
aws_instance.bar[0]
aws_instance.bar[1]
module.elb.aws_elb.main
```

#### Example: Filtering by Resource

This example will only list resources for the given name:

```
terraform state list aws_instance.bar
```

```
aws_instance.bar[0]
aws_instance.bar[1]
```

#### Example: Filtering by Module

This example will list resources in the given module and any submodules:

```Shell
terraform state list module.elb
```

```Shell
module.elb.aws_elb.main
module.elb.module.secgroups.aws_security_group.sg
```

#### Example: Filtering by ID

This example will only list the resource whose ID is specified on the command line. This is useful to find where in your configuration a specific resource is located.

```bash
terraform state list -id=sg-1234abcd
```

```Shell
module.elb.aws_security_group.sg
```

## Command state show

The `terraform state show` command is used to show the attributes of a single resource in the [Terraform state](https://developer.hashicorp.com/terraform/language/v1.1.x/state).

### Usage

Usage: `terraform state show [options] ADDRESS`

The command will show the attributes of a single resource in the state file that matches the given address.

This command requires an address that points to a single resource in the state. Addresses are in [resource addressing format](https://developer.hashicorp.com/terraform/cli/v1.1.x/state/resource-addressing).

The command-line flags are all optional. The list of available flags are:

- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/state/show#)[`-state=path`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/state/show#state-path) - Path to the state file. Defaults to "terraform.tfstate". [Legacy option for the local backend only](https://developer.hashicorp.com/terraform/language/v1.1.x/backend/local#command-line-arguments).

The output of `terraform state show` is intended for human consumption, not programmatic consumption. To extract state data for use in other software, use [`terraform show -json`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/show#json-output) and decode the result using the documented structure.

### Example: Show a Resource

The example below shows a `packet_device` resource named `worker`:

```Shell
terraform state show 'packet_device.worker'
```

```JSON
# packet_device.worker:
resource "packet_device" "worker" {
    billing_cycle = "hourly"
    created       = "2015-12-17T00:06:56Z"
    facility      = "ewr1"
    hostname      = "prod-xyz01"
    id            = "6015bg2b-b8c4-4925-aad2-f0671d5d3b13"
    locked        = false
}
```

### Example: Show a Module Resource

The example below shows a `packet_device` resource named `worker` inside a module named `foo`:

```
$ terraform state show 'module.foo.packet_device.worker'
```

### Example: Show a Resource configured with count

The example below shows the first instance of a `packet_device` resource named `worker` configured with [`count`](https://developer.hashicorp.com/terraform/language/v1.1.x/meta-arguments/count):

```
$ terraform state show 'packet_device.worker[0]'
```

### Example: Show a Resource configured with for_each

The example below shows the `"example"` instance of a `packet_device` resource named `worker` configured with [`for_each`](https://developer.hashicorp.com/terraform/language/v1.1.x/meta-arguments/for_each):

Linux, Mac OS, and UNIX:

```
$ terraform state show 'packet_device.worker["example"]'
```

PowerShell:

```
$ terraform state show 'packet_device.worker[\"example\"]'
```

Windows `cmd.exe`:

```
$ terraform state show packet_device.worker[\"example\"]
```

## Command Refresh

The `terraform refresh` command reads the current settings from all managed remote objects and updates the Terraform state to match.

_Warning:_ This command is deprecated, because its default behavior is unsafe if you have misconfigured credentials for any of your providers. See below for more information and recommended alternatives.

This won't modify your real remote objects, but it will modify the [Terraform state](https://developer.hashicorp.com/terraform/language/v1.1.x/state).

You shouldn't typically need to use this command, because Terraform automatically performs the same refreshing actions as a part of creating a plan in both the [`terraform plan`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan) and [`terraform apply`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply) commands. This command is here primarily for backward compatibility, but we don't recommend using it because it provides no opportunity to review the effects of the operation before updating the state.

## Usage

Usage: `terraform refresh [options]`

This command is effectively an alias for the following command:

```
terraform apply -refresh-only -auto-approve
```

Consequently, it supports all of the same options as [`terraform apply`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply) except that it does not accept a saved plan file, it doesn't allow selecting a planning mode other than "refresh only", and `-auto-approve` is always enabled.

Automatically applying the effect of a refresh is risky, because if you have misconfigured credentials for one or more providers then the provider may be misled into thinking that all of the managed objects have been deleted, and thus remove all of the tracked objects without any confirmation prompt.

Instead, we recommend using the following command in order to get the same effect but with the opportunity to review the changes that Terraform has detected before committing them to the state:

```
terraform apply -refresh-only
```

This alternative command will present an interactive prompt for you to confirm the detected changes.

The `-refresh-only` option for `terraform plan` and `terraform apply` was introduced in Terraform v0.15.4. For prior versions you must use `terraform refresh` directly if you need this behavior, while taking into account the warnings above. Wherever possible, avoid using `terraform refresh` explicitly and instead rely on Terraform's behavior of automatically refreshing existing objects as part of creating a normal plan.

#### 🔹 What `terraform refresh` does

- It **synchronizes Terraform’s state file** with the **real-world infrastructure**.
    
- It queries your cloud provider (e.g., AWS, Azure, GCP) to check if resources still exist, what their current settings are, and then updates the local/remote **Terraform state file** accordingly.
    
- It **does not** modify the actual infrastructure — only Terraform’s **state file**.
    

---

#### 🔹 Why it’s deprecated

- **Risk of accidental deletion:**  
    If your credentials are wrong or misconfigured, the provider might think resources don’t exist. Terraform would then assume they’ve been deleted and update the state file, potentially leading to future `terraform apply` destroying your real infrastructure.

## Remote State

The Terraform state subcommands all work with remote state just as if it was local state. Reads and writes may take longer than normal as each read and each write do a full network roundtrip. Otherwise, backups are still written to disk and the CLI usage is the same as if it were local state.

## Backups

All `terraform state` subcommands that modify the state write backup files. The path of these backup file can be controlled with `-backup`.

Subcommands that are read-only (such as [list](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/state/list)) do not write any backup files since they aren't modifying the state.

Note that backups for state modification _can not be disabled_. Due to the sensitivity of the state file, Terraform forces every state modification command to write a backup file. You'll have to remove these files manually if you don't want to keep them around.

## Command-Line Friendly

The output and command-line structure of the state subcommands is designed to be usable with Unix command-line tools such as grep, awk, and similar PowerShell commands.

For advanced filtering and modification, we recommend piping Terraform state subcommands together with other command line tools.

### 1. Remote State

- Normally, Terraform stores the _state file_ (`terraform.tfstate`) **locally** on your machine.
    
- But when you configure a **remote backend** (like S3, Azure Blob, GCS, Terraform Cloud, etc.), the state file is stored **remotely**.
    
- **Behavior:**
    
    - Terraform treats remote state _the same way_ as local state.
        
    - Reads/writes just take longer because every operation makes a **network request**.
        
    - Example: When you run `terraform plan`, Terraform has to fetch the state from the remote backend first.
        

---

### 2. Backups

- Anytime you run a **state-modifying command** (like `terraform state mv`, `rm`, `import`), Terraform creates a **backup file**.
    
- These backups are **always stored locally** on disk, even if your state is remote.
    
- You can control where the backup goes using the `-backup` flag.
    
- **Important:** You cannot disable backups. Terraform enforces this because the state file is **sensitive and critical**.
    

---

### 3. Read-only Subcommands

- Some commands (like `terraform state list`) only **read** the state.
    
- Since they don’t change the state, **no backup is written**.