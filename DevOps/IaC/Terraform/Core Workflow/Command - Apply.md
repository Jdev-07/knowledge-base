The `terraform apply` command executes the actions proposed in a Terraform plan.

The most straightforward way to use `terraform apply` is to run it without any arguments at all, in which case it will automatically create a new execution plan (as if you had run `terraform plan`) and then prompt you to approve that plan, before taking the indicated actions.

Another way to use `terraform apply` is to pass it the filename of a saved plan file you created earlier with `terraform plan -out=...`, in which case Terraform will apply the changes in the plan without any confirmation prompt. This two-step workflow is primarily intended for when [running Terraform in automation](https://developer.hashicorp.com/terraform/tutorials/automation/automate-terraform?utm_source=WEBSITE&utm_medium=WEB_IO&utm_offer=ARTICLE_PAGE&utm_content=DOCS).

## Usage

Usage: `terraform apply [options] [plan file]`

The behavior of `terraform apply` differs significantly depending on whether you pass it the filename of a previously-saved plan file.

### Automatic Plan Mode

In the default case, with no saved plan file, `terraform apply` creates its own plan of action, in the same way that [`terraform plan`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan) would.

Terraform will propose the plan to you and prompt you to approve it before taking the described actions, unless you waive that prompt by using the `-auto-approve` option.

**Tip:** When you run `terraform apply` without a saved plan file, you can use all of the [planning modes](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#planning-modes) and [planning options](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#planning-options) available for `terraform plan`. This lets you customize how Terraform will create the plan.

### Saved Plan Mode

If you pass the filename of a previously-saved plan file, `terraform apply` performs exactly the steps specified by that plan file. It does not prompt for approval; if you want to inspect a plan file before applying it, you can use [`terraform show`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/show).

When using a saved plan, none of the planning modes or planning options linked above are supported; these options only affect Terraform's decisions about which actions to take, and the plan file contains the final results of those decisions.

### Plan Options

When run without a saved plan file, `terraform apply` supports all of `terraform plan`'s planning modes and planning options. For details, see:

- [Planning Modes](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#planning-modes)
- [Planning Options](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#planning-options)

### Apply Options

The following options allow you to change various details about how the apply command executes and reports on the apply operation.

- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#)
    
    [`-auto-approve`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#auto-approve) - Skips interactive approval of plan before applying. This option is ignored when you pass a previously-saved plan file, because Terraform considers you passing the plan file as the approval and so will never prompt in that case.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#)
    
    [`-compact-warnings`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#compact-warnings) - Shows any warning messages in a compact form which includes only the summary messages, unless the warnings are accompanied by at least one error and thus the warning text might be useful context for the errors.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#)
    
    [`-input=false`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#input-false) - Disables all of Terraform's interactive prompts. Note that this also prevents Terraform from prompting for interactive approval of a plan, so Terraform will conservatively assume that you do not wish to apply the plan, causing the operation to fail. If you wish to run Terraform in a non-interactive context, see [Running Terraform in Automation](https://developer.hashicorp.com/terraform/tutorials/automation/automate-terraform?utm_source=WEBSITE&utm_medium=WEB_IO&utm_offer=ARTICLE_PAGE&utm_content=DOCS) for some different approaches.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#)
    
    [`-json`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#json) - Enables the [machine readable JSON UI](https://developer.hashicorp.com/terraform/internals/machine-readable-ui) output. This implies `-input=false`, so the configuration must have no unassigned variable values to continue. To enable this flag, you must also either enable the `-auto-approve` flag or specify a previously-saved plan.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#)
    
    [`-lock=false`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#lock-false) - Don't hold a state lock during the operation. This is dangerous if others might concurrently run commands against the same workspace.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#)
    
    [`-lock-timeout=DURATION`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#lock-timeout-duration) - Unless locking is disabled with `-lock=false`, instructs Terraform to retry acquiring a lock for a period of time before returning an error. The duration syntax is a number followed by a time unit letter, such as "3s" for three seconds.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#)
    
    [`-no-color`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#no-color) - Disables terminal formatting sequences in the output. Use this if you are running Terraform in a context where its output will be rendered by a system that cannot interpret terminal formatting.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#)
    
    [`-parallelism=n`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply#parallelism-n) - Limit the number of concurrent operation as Terraform [walks the graph](https://developer.hashicorp.com/terraform/internals/v1.1.x/graph#walking-the-graph). Defaults to 10.
    

- All [planning modes](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#planning-modes) and [planning options](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan#planning-options) for `terraform plan` - Customize how Terraform will create the plan. Only available when you run `terraform apply` without a saved plan file.

For configurations using [the `local` backend](https://developer.hashicorp.com/terraform/language/v1.1.x/settings/backends/local) only, `terraform apply` also accepts the legacy options [`-state`, `-state-out`, and `-backup`](https://developer.hashicorp.com/terraform/language/v1.1.x/settings/backends/local#command-line-arguments).

