The `terraform plan` command creates an execution plan, which lets you preview the changes that Terraform plans to make to your infrastructure. By default, when Terraform creates a plan it:

- Reads the current state of any already-existing remote objects to make sure that the Terraform state is up-to-date.
- Compares the current configuration to the prior state and noting any differences.
- Proposes a set of change actions that should, if applied, make the remote objects match the configuration.

The plan command alone will not actually carry out the proposed changes, and so you can use this command to check whether the proposed changes match what you expected before you apply the changes or share your changes with your team for broader review.

If Terraform detects that no changes are needed to resource instances or to root module output values, `terraform plan` will report that no actions need to be taken.

If you are using Terraform directly in an interactive terminal and you expect to apply the changes Terraform proposes, you can alternatively run [`terraform apply`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply) directly. By default, the "apply" command automatically generates a new plan and prompts for you to approve it.

You can use the optional `-out=FILE` option to save the generated plan to a file on disk, which you can later execute by passing the file to [`terraform apply`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply) as an extra argument. This two-step workflow is primarily intended for when [running Terraform in automation](https://developer.hashicorp.com/terraform/tutorials/automation/automate-terraform?utm_source=WEBSITE&utm_medium=WEB_IO&utm_offer=ARTICLE_PAGE&utm_content=DOCS).

If you run `terraform plan` without the `-out=FILE` option then it will create a _speculative plan_, which is a description of the effect of the plan but without any intent to actually apply it.

In teams that use a version control and code review workflow for making changes to real infrastructure, developers can use speculative plans to verify the effect of their changes before submitting them for code review. However, it's important to consider that other changes made to the target system in the meantime might cause tahe final effect of a configuration change to be different than what an earlier speculative plan indicated, so you should always re-check the final non-speculative plan before applying to make sure that it still matches your intent.

### Speculative Plan (when you don’t use `-out=FILE`)

- If you just run:
```Bash
terraform plan
```

- Terraform shows you what it _would_ do, but there’s no guarantee you’ll actually apply it later.
    
- This is called a **speculative plan** → it’s “for your eyes only,” just a preview.

### How teams use speculative plans

- In teams, developers often propose changes to infrastructure (like code changes in GitHub).
    
- Before merging, they run `terraform plan` and share that **speculative plan** so reviewers can see _what’s going to happen if this is applied_.
    
- This helps catch mistakes before changes go live.
    

Example:

- Dev A changes a VM size from `Standard_B2s` → `Standard_B4ms`.
    
- They run `terraform plan`, see the change, and share it in a pull request for review.

- A **speculative plan** = preview only, good for review, not guaranteed to match reality later.
    
- A **saved plan (`-out`)** = “locked-in” plan you can apply later to ensure consistency.

## Usage

Usage: `terraform plan [options]`

The `plan` subcommand looks in the current working directory for the root module configuration.

Because the plan command is one of the main commands of Terraform, it has a variety of different options, described in the following sections. However, most of the time you should not need to set any of these options, because a Terraform configuration should typically be designed to work with no special additional options for routine work.

The remaining sections on this page describe the various options:

- **[Planning Modes](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#planning-modes)**: There are some special alternative planning modes that you can use for some special situations where your goal is not just to change the remote system to match your configuration.
- **[Planning Options](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#planning-options)**: Alongside the special planning modes, there are also some options you can set in order to customize the planning process for unusual needs.
    - **[Resource Targeting](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#resource-targeting)** is one particular special planning option that has some important caveats associated with it.
- **[Other Options](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#other-options)**: These change the behavior of the planning command itself, rather than customizing the content of the generated plan.

## Planning Modes

The previous section describes Terraform's default planning behavior, which changes the remote system to match the changes you make to your configuration. Terraform has two alternative planning modes, each of which creates a plan with a different intended outcome. These options are available for both `terraform plan` and [`terraform apply`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply).

- **Destroy mode:** creates a plan whose goal is to destroy all remote objects that currently exist, leaving an empty Terraform state. This can be useful for situations like transient development environments, where the managed objects cease to be useful once the development task is complete.
    
    Activate destroy mode using the `-destroy` command line option.
    
- **Refresh-only mode:** creates a plan whose goal is only to update the Terraform state and any root module output values to match changes made to remote objects outside of Terraform. This can be useful if you've intentionally changed one or more remote objects outside of the usual workflow (e.g. while responding to an incident) and you now need to reconcile Terraform's records with those changes.
    
    Activate refresh-only mode using the `-refresh-only` command line option.
    

In situations where we need to discuss the default planning mode that Terraform uses when none of the alternative modes are selected, we refer to it as "Normal mode". Because these alternative modes are for specialized situations only, some other Terraform documentation only discusses the normal planning mode.

The planning modes are all mutually-exclusive, so activating any non-default planning mode disables the "normal" planning mode, and you can't use more than one alternative mode at the same time.

- **Normal mode** = “Sync my infra with my config.”
    
- **Destroy mode** = “Delete everything.”
    
- **Refresh-only mode** = “Don’t change infra, just update Terraform’s memory.”

#### 1. Destroy mode (`-destroy`)

- Goal → Wipe out everything Terraform manages.
    
- After running, your infra = nothing, and your state file is empty.
    
- Use case: temporary environments (like a dev/test environment you don’t need anymore).
    

Think of it as saying:  
_"I’m done with this setup, remove everything Terraform created."_

#### 2. Refresh-only mode (`-refresh-only`)

- Goal → Don’t change infra. Just update Terraform’s state file.
    
- Example: Let’s say you changed something manually in the cloud (like scaling an Azure VM from 2 to 4 CPUs). Terraform doesn’t know about it yet.
    
- Running in this mode will **refresh Terraform’s state** so it now matches the real-world infra.
    

Think of it as saying:  
_"Terraform, don’t touch anything, just update your notes to reflect reality."_

## Planning Options

In addition to alternate [planning modes](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#planning-modes), there are several options that can modify planning behavior. These options are available for both `terraform plan` and [`terraform apply`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply).

- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#)
    
    [`-refresh=false`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#refresh-false) - Disables the default behavior of synchronizing the Terraform state with remote objects before checking for configuration changes. This can make the planning operation faster by reducing the number of remote API requests. However, setting `refresh=false` causes Terraform to ignore external changes, which could result in an incomplete or incorrect plan. You cannot use `refresh=false` in refresh-only planning mode because it would effectively disable the entirety of the planning operation.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#)
    
    [`-replace=ADDRESS`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#replace-address) - Instructs Terraform to plan to replace the resource instance with the given address. This is helpful when one or more remote objects have become degraded, and you can use replacement objects with the same configuratation to align with immutable infrastructure patterns. Terraform will use a "replace" action if the specified resource would normally cause an "update" action or no action at all. Include this option multiple times to replace several objects at once. You cannot use `-replace` with the `-destroy` option, and it is only available from Terraform v0.15.2 onwards. For earlier versions, use [`terraform taint`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/taint) to achieve a similar result.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#)
    
    [`-target=ADDRESS`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#target-address) - Instructs Terraform to focus its planning efforts only on resource instances which match the given address and on any objects that those instances depend on.
    
    **Note:** Use `-target=ADDRESS` in exceptional circumstances only, such as recovering from mistakes or working around Terraform limitations. Refer to [Resource Targeting](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#resource-targeting) for more details.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#)
    
    [`-var 'NAME=VALUE'`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#var-name-value) - Sets a value for a single [input variable](https://developer.hashicorp.com/terraform/language/v1.1.x/values/variables) declared in the root module of the configuration. Use this option multiple times to set more than one variable. Refer to [Input Variables on the Command Line](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#input-variables-on-the-command-line) for more information.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#)
    
    [`-var-file=FILENAME`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#var-file-filename) - Sets values for potentially many [input variables](https://developer.hashicorp.com/terraform/language/v1.1.x/values/variables) declared in the root module of the configuration, using definitions from a ["tfvars" file](https://developer.hashicorp.com/terraform/language/v1.1.x/values/variables#variable-definitions-tfvars-files). Use this option multiple times to include values from more than one file.
    

There are several other ways to set values for input variables in the root module, aside from the `-var` and `-var-file` options. Refer to [Assigning Values to Root Module Variables](https://developer.hashicorp.com/terraform/language/v1.1.x/values/variables#assigning-values-to-root-module-variables) for more information.

##### 🔹 `-refresh=false`

👉 By default, Terraform **refreshes the state** (checks the real-world cloud resources to see if anything changed) before making a plan.

- If you set `-refresh=false`, it **skips that step**, making the plan faster.  
    ⚠️ Downside: If something changed outside Terraform, it won’t notice — so the plan may be wrong.


##### 🔹 `-replace=ADDRESS`

👉 Forces Terraform to **destroy and recreate** a specific resource, even if it doesn’t look like it needs changes.

- Helpful when a resource is **degraded** or broken.
    
- Replaces instead of updating in-place.

```Bash
terraform apply -replace="azurerm_virtual_machine.myvm"
```

##### 🔹 `-target=ADDRESS`

👉 Tells Terraform to only **plan/apply changes** to a specific resource (and its dependencies).  
⚠️ This is **not recommended** for normal use, only for recovery or debugging — because it can create inconsistencies.

```Bash
terraform plan -target="aws_s3_bucket.logs"
```

### Input Variables on the Command Line

You can use the `-var` command line option to specify values for [input variables](https://developer.hashicorp.com/terraform/language/v1.1.x/values/variables) declared in your root module.

However, to do so will require writing a command line that is parsable both by your chosen command line shell _and_ Terraform, which can be complicated for expressions involving lots of quotes and escape sequences. In most cases we recommend using the `-var-file` option instead, and write your actual values in a separate file so that Terraform can parse them directly, rather than interpreting the result of your shell's parsing.

To use `-var` on a Unix-style shell on a system like Linux or macOS we recommend writing the option argument in single quotes `'` to ensure the shell will interpret the value literally:

```Bash
terraform plan -var 'name=value'
```

If your intended value also includes a single quote then you'll still need to escape that for correct interpretation by your shell, which also requires temporarily ending the quoted sequence so that the backslash escape character will be significant:

```
terraform plan -var 'name=va'\''lue'
```

When using Terraform on Windows, we recommend using the Windows Command Prompt (`cmd.exe`). When you pass a variable value to Terraform from the Windows Command Prompt, use double quotes `"` around the argument:

```
terraform plan -var "name=value"
```

PowerShell on Windows cannot correctly pass literal quotes to external programs, so we do not recommend using Terraform with PowerShell when you are on Windows. Use Windows Command Prompt instead.

The appropriate syntax for writing the variable value is different depending on the variable's [type constraint](https://developer.hashicorp.com/terraform/language/v1.1.x/expressions/type-constraints). The primitive types `string`, `number`, and `bool` all expect a direct string value with no special punctuation except that required by your shell, as shown in the above examples. For all other type constraints, including list, map, and set types and the special `any` keyword, you must write a valid Terraform language expression representing the value, and write any necessary quoting or escape characters to ensure it will pass through your shell literally to Terraform. For example, for a `list(string)` type constraint:

```Bash
# Unix-style shell
terraform plan -var 'name=["a", "b", "c"]'

# Windows Command Prompt (do not use PowerShell on Windows)
terraform plan -var "name=[\"a\", \"b\", \"c\"]"
```

****

### Resource Targeting

> **Hands-on:** Try the [Target resources](https://developer.hashicorp.com/terraform/tutorials/state/resource-targeting?utm_source=WEBSITE&utm_medium=WEB_IO&utm_offer=ARTICLE_PAGE&utm_content=DOCS) tutorial on HashiCorp Learn.

You can use the `-target` option to focus Terraform's attention on only a subset of resources. You can use [resource address syntax](https://developer.hashicorp.com/terraform/cli/v1.1.x/state/resource-addressing) to specify the constraint. Terraform interprets the resource address as follows:

- If the given address identifies one specific resource instance, Terraform will select that instance alone. For resources with either `count` or `for_each` set, a resource instance address must include the instance index part, like `aws_instance.example[0]`.
    
- If the given address identifies a resource as a whole, Terraform will select all of the instances of that resource. For resources with either `count` or `for_each` set, this means selecting _all_ instance indexes currently associated with that resource. For single-instance resources (without either `count` or `for_each`), the resource address and the resource instance address are identical, so this possibility does not apply.
    
- If the given address identifies an entire module instance, Terraform will select all instances of all resources that belong to that module instance and all of its child module instances.
    

Once Terraform has selected one or more resource instances that you've directly targeted, it will also then extend the selection to include all other objects that those selections depend on either directly or indirectly.

This targeting capability is provided for exceptional circumstances, such as recovering from mistakes or working around Terraform limitations. It is _not recommended_ to use `-target` for routine operations, since this can lead to undetected configuration drift and confusion about how the true state of resources relates to configuration.

Instead of using `-target` as a means to operate on isolated portions of very large configurations, prefer instead to break large configurations into several smaller configurations that can each be independently applied. [Data sources](https://developer.hashicorp.com/terraform/language/v1.1.x/data-sources) can be used to access information about resources created in other configurations, allowing a complex system architecture to be broken down into more manageable parts that can be updated independently.

### Resource Targeting with `-target`

- The `-target` option lets you tell Terraform to **focus only on specific resources** during `plan` or `apply`.
    
- You specify which resources using their **resource address** (the name Terraform gives them, like `aws_instance.example[0]`).

**Target one resource instance**  
Example:
```Bash
terraform apply -target=aws_instance.example[0]
```

**Target all instances of a resource**  
Example:
```Bash
terraform apply -target=aws_instance.example
```

- → If the resource uses `count` or `for_each`, Terraform selects **all instances**.

**Target a whole module**  
Example:
```Bash
terraform apply -target=module.network
```

### Important notes:

- Terraform also includes **dependencies** of your target automatically, so it won’t break things.
    
- This is meant for **exceptional cases only**:
    
    - Recovering from mistakes.
        
    - Working around Terraform limitations.
        
- 🚫 Don’t use `-target` for daily work — it can cause **drift** (resources not matching your config).
    
- Instead:
    
    - Break large configs into **smaller modules/configurations**.
        
    - Use **data sources** to connect them safely.

## Other Options

The `terraform plan` command also has some other options that are related to the input and output of the planning command, rather than customizing what sort of plan Terraform will create. These commands are not necessarily also available on `terraform apply`, unless otherwise stated in the documentation for that command.

The available options are:

- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#)
    
    [`-compact-warnings`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#compact-warnings) - Shows any warning messages in a compact form which includes only the summary messages, unless the warnings are accompanied by at least one error and thus the warning text might be useful context for the errors.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#)
    
    [`-detailed-exitcode`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#detailed-exitcode) - Returns a detailed exit code when the command exits. When provided, this argument changes the exit codes and their meanings to provide more granular information about what the resulting plan contains:
    
    - 0 = Succeeded with empty diff (no changes)
    - 1 = Error
    - 2 = Succeeded with non-empty diff (changes present)
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#)
    
    [`-input=false`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#input-false) - Disables Terraform's default behavior of prompting for input for root module input variables that have not otherwise been assigned a value. This option is particularly useful when running Terraform in non-interactive automation systems.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#)
    
    [`-json`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#json) - Enables the [machine readable JSON UI](https://developer.hashicorp.com/terraform/internals/machine-readable-ui) output. This implies `-input=false`, so the configuration must have no unassigned variable values to continue.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#)
    
    [`-lock=false`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#lock-false) - Don't hold a state lock during the operation. This is dangerous if others might concurrently run commands against the same workspace.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#)
    
    [`-lock-timeout=DURATION`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#lock-timeout-duration) - Unless locking is disabled with `-lock=false`, instructs Terraform to retry acquiring a lock for a period of time before returning an error. The duration syntax is a number followed by a time unit letter, such as "3s" for three seconds.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#)
    
    [`-no-color`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#no-color) - Disables terminal formatting sequences in the output. Use this if you are running Terraform in a context where its output will be rendered by a system that cannot interpret terminal formatting.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#)
    
    [`-out=FILENAME`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#out-filename) - Writes the generated plan to the given filename in an opaque file format that you can later pass to `terraform apply` to execute the planned changes, and to some other Terraform commands that can work with saved plan files.
    
    Terraform will allow any filename for the plan file, but a typical convention is to name it `tfplan`. **Do not** name the file with a suffix that Terraform recognizes as another file format; if you use a `.tf` suffix then Terraform will try to interpret the file as a configuration source file, which will then cause syntax errors for subsequent commands.
    
    The generated file is not in any standard format intended for consumption by other software, but the file _does_ contain your full configuration, all of the values associated with planned changes, and all of the plan options including the input variables. If your plan includes any sort of sensitive data, even if obscured in Terraform's terminal output, it will be saved in cleartext in the plan file. You should therefore treat any saved plan files as potentially-sensitive artifacts.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#)
    
    [`-parallelism=n`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#parallelism-n) - Limit the number of concurrent operations as Terraform [walks the graph](https://developer.hashicorp.com/terraform/internals/v1.1.x/graph#walking-the-graph). Defaults to 10.
    

For configurations using [the `local` backend](https://developer.hashicorp.com/terraform/language/v1.1.x/settings/backends/local) only, `terraform plan` accepts the legacy command line option [`-state`](https://developer.hashicorp.com/terraform/language/v1.1.x/settings/backends/local#command-line-arguments).

##### 🔹 `-compact-warnings`

- **What it does:** Makes warnings shorter and only shows summaries.
    
- **When to use:** If you’re in CI/CD and don’t want long warnings spamming logs.
    

`terraform plan -compact-warnings`

---

##### 🔹 `-detailed-exitcode`

- **What it does:** Makes Terraform return **different exit codes** to indicate results.
    
- **Why useful:** Great for automation pipelines, so scripts can know whether there are changes.
    
    - `0` → No changes.
        
    - `1` → Error.
        
    - `2` → Changes detected.
        

`terraform plan -detailed-exitcode`

Example: In CI, you can fail a build only if code 2 (changes) appears without approval.

---

### 🔹 `-input=false`

- **What it does:** Stops Terraform from asking you questions if variables are missing.
    
- **When useful:** In automation (Jenkins, GitHub Actions, etc.) where no human can type input.
    

`terraform plan -input=false`

---

### 🔹 `-json`

- **What it does:** Outputs the plan in **JSON format**.
    
- **Implication:** Automatically sets `-input=false`.
    
- **Why:** Lets other tools (like scripts, dashboards, or Terraform Cloud) parse the plan.
    

`terraform plan -json > plan.json`

---

### 🔹 `-lock=false`

- **What it does:** Disables the **state lock** (Terraform normally locks state so two people can’t edit it at once).
    
- **Warning:** Dangerous in teamwork! Only use in testing.
    

`terraform plan -lock=false`

---

### 🔹 `-lock-timeout=DURATION`

- **What it does:** Tells Terraform how long to wait for the lock before failing.
    
- **Example:** If someone else is running Terraform, wait 60s for them to finish.
    

`terraform plan -lock-timeout=60s`

---

### 🔹 `-no-color`

- **What it does:** Removes colors from the output.
    
- **Useful when:** Logs are sent to systems that can’t handle color (like plain-text CI logs).
    

`terraform plan -no-color`

---

### 🔹 `-out=FILENAME`

- **What it does:** Saves the plan to a file, which you can later `terraform apply`.
    
- **Important:** This file can contain **sensitive data in plain text**.
    

`terraform plan -out=tfplan terraform apply "tfplan"`

---

### 🔹 `-parallelism=n`

- **What it does:** Limits how many resources Terraform works on at the same time.
    
- **Default:** 10.
    
- **Why:** If your provider (like Azure or AWS) throttles API requests, you may lower it.
    

`terraform plan -parallelism=5`

---

✅ **In summary**:  
These options are mostly about **automation, safety, and output formatting**. For real work, the most common ones you’ll see are:

- `-detailed-exitcode` (for CI/CD pipelines)
    
- `-input=false` (automation)
    
- `-out=tfplan` (review changes before applying)
    
- `-parallelism` (performance control)