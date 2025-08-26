When you provision infrastructure, Terraform creates an execution plan before it applies any changes. Terraform creates the plan by comparing your Terraform configuration to the state of your infrastructure. The execution plan consists of a set of changes that create, update, or destroy resources. You can use the `terraform plan` command to compare your configuration to your resource's state, review changes before you apply them, or to refresh your workspace's state. Terraform plan supports automation workflows in CI/CD pipelines by guaranteeing that the infrastructure changes Terraform applies match the ones you or your team approve, even if the deploy process completes across different machines or at different times.

There are three commands that tell Terraform to generate an execution plan:

1. The `terraform plan` command creates a plan consisting of a set of changes that will make your resources match your configuration. This lets you preview the actions Terraform would take to modify your infrastructure before applying them. Terraform plan does not make any changes to your resources, you must apply a plan for Terraform to make changes.
    
    You can also save a plan with the `-out` flag. Later, you can apply the saved plan, and Terraform will only perform the changes listed in the plan. In an automated Terraform pipeline, applying a saved plan file ensures that Terraform only makes the changes you expect, even if your pipeline runs across multiple machines at different times.
    
2. The `terraform apply` command applies a Terraform plan. If you do not pass a saved plan, then Terraform will a create a plan and prompt you for approval before applying the plan.
    
3. The `terraform destroy` command creates an execution plan to delete all of the resources managed by your workspace.

Convert the saved plan into JSON, pass it to `jq` to format it, and save the output into a new file.

For windows

```Bash
winget install jqlang.jq
```

```Bash
$ terraform show "tfplan"
```

```Bash
terraform show -json "tfplan" | jq > tfplan.json
```

### Review plan configuration

The `.configuration` JSON object is a snapshot of your configuration at the time of the `terraform plan`.

This configuration snapshot captures the versions of the providers recorded in your `.terraform.lock.hcl` file, ensuring that you use the same provider versions that generated the plan to apply it. Note that the configuration accounts for both the provider version used by the root module and child modules.

```Bash
jq .configuration.provider_config tfplan.json
```

![[terraform-012.png]]

### Review planned resource changes

Review the planned resources changes to the `aws_instance` resource from the `ec2-instance` local module.

The representation includes:

- The `action` field captures the action taken for this resource, in this case `create`.
- The `before` field captures the resource state prior to the run. In this case, the value is `null` because the resource does not yet exist.
- The `after` field captures the state to define for the resource.
- The `after_unknown` field captures the list of values that will be computed or determined through the operation and sets them to `true`.
- The `before_sensitive` and `after_sensitive` fields capture a list of any values marked `sensitive`. Terraform will use these lists to determine which output values to redact when you apply your configuration.

```Bash
jq '.resource_changes[] | select( .address == "module.ec2-instance.aws_instance.main")' tfplan.json
```

```JSON
{
  "address": "module.ec2-instance.aws_instance.main",
  "module_address": "module.ec2-instance",
  "mode": "managed",
  "type": "aws_instance",
  "name": "main",
  "provider_name": "registry.terraform.io/hashicorp/aws",
  "change": {
    "actions": [
      "create"
    ],
    "before": null,
    "after": {
      "ami": "ami-055744c75048d8296",
      "credit_specification": [],
      "get_password_data": false,
      "hibernation": null,
      "instance_type": "t2.micro",
      "launch_template": [],
      "source_dest_check": true,
      "timeouts": null,
      "user_data_replace_on_change": false,
      "volume_tags": null
    },
    "after_unknown": {
      "arn": true,
      "associate_public_ip_address": true,
      "availability_zone": true,
## ...
    }
  }
}
```

### Review planned values

The `planned_values` object is a report of the differences between the "before" and "after" values of your resources, showing you the planned outcome for a run that would use this plan file.

In this example, the `module.ec2-instance.aws_instance` resource includes the address that you will use to reference the resource in your Terraform configuration, the provider name, and the values of all of the attributes as one object. This format resolves the differences between the prior and expected state in one object to demonstrate the planned outcomes for the configuration, which is easier to use for any downstream consumers of the plan data. For example, the Terraform Sentinel CLI tests policies against the planned outcomes recorded here. The cost estimation feature in HCP Terraform also relies on the `planned_values` data to determine changes to your infrastructure spend.

----
## Modify configuration

Input variables let you easily update configuration values without having to edit your configuration files.

Open the `variables.tf` file in the top-level configuration directory. Add the configuration below to define a new input variable to use for the `hello` module.

```Go
variable "secret_key" {
  type        = string
  sensitive   = true
  description = "Secret key for hello module"
}
```

```Warning
Never commit `.tfvars` files to version control.
```

Finally, update the `hello` module configuration in `main.tf` to reference the new input variable.

```Go
module "hello" {
  source  = "joatmon08/hello/random"
  version = "6.0.0"

  hellos = {
    hello        = random_pet.instance.id
    second_hello = "World"
  }

  some_key = var.secret_key
}
```

Although you marked the input variable as `sensitive`, Terraform still stores the value in plaintext in the plan file. Since Terraform plan files can contain sensitive information, you should keep them secure and never commit them to version control.

Unlike input variables, Terraform does not record the values of any environment variables used for your configuration in your plan files. Using environment variables is one of the recommended ways to pass sensitive values, such as provider credentials, to Terraform.

### Review plan `prior_state`

When you created this plan, Terraform determined that the working directory already contains a state file, and used that state to plan the resource changes. Unlike the first run's plan file, this file now contains a `prior_state` object, which captures the state file exactly as it was prior to the plan action.

```Shell
$ jq '.prior_state' tfplan-input-var.json
```

```JSON
{
  "address": "module.hello.random_pet.server",
  "module_address": "module.hello",
  "mode": "managed",
  "type": "random_pet",
  "name": "server",
  "provider_name": "registry.terraform.io/hashicorp/random",
  "change": {
    "actions": [
      "delete",
      "create"
    ],
    "before": {
      "id": "tidy-crawdad",
  ## ...
    "after": {
      "keepers": {
        "hello": "fun-possum",
        "secret_key": "TOPSECRET"
      },
## ...
  "action_reason": "replace_because_cannot_update"
}
```

Notice that the `actions` list is now set to `["delete","create"]` and that the `action_reason` is `"replace_because_cannot_update"` - the change to the `secret_key` for the resource is destructive, so Terraform must both delete and create this resource. Terraform determines whether it can update a resource in place or must recreate it based on which provider attributes you changed.

Once you have created resources in the working directory, Terraform uses the prior state, the data returned by a refresh operation, and the written configuration to determine the changes to make. Terraform supports additional flags that you can use to modify how it constructs an execution plan. For example, you can create a plan that only refreshes the state file without modifying resource configuration, or target only specific resources for either update or replacement.

----
## Clean up infrastructure

Now that you have completed this tutorial, destroy the resources created before moving on. Create and apply a destroy plan.

```Shell
terraform plan -destroy -out "tfplan-destroy"
```

```Shell
terraform apply "tfplan-destroy"
```

The terraform destroy command is a shortcut that creates a destroy plan and then waits for you to approve it. Saving a destroy plan allows you to review it before applying, just like a regular saved plan.

