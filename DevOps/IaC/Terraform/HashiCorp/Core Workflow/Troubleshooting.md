The primary method for interacting with Terraform is the HashiCorp Configuration Language (HCL). When Terraform encounters an error in your configuration, it will report an error including line numbers and the type of issue found in the configuration.

## Review the Terraform troubleshooting model

![[terraform-013.png]]

There are four potential types of issues that you could experience with Terraform: language, state, core, and provider errors. Starting from the type of error closest to the user:

1. **Language errors**: The primary interface for Terraform is the HashiCorp Configuration Language (HCL), a declarative configuration language. The Terraform core application interprets the configuration language. When Terraform encounters a syntax error in your configuration, it prints out the line numbers and an explanation of the error.
2. **State errors**: The Terraform state file stores information on provisioned resources. It maps resources to your configuration and tracks all associated metadata. If state is out of sync, Terraform may destroy or change your existing resources. After you rule out configuration errors, review your state. Ensure your configuration is in sync by refreshing, importing, or replacing resources.
3. **Core errors**: The Terraform core application contains all the logic for operations. It interprets your configuration, manages your state file, constructs the resource dependency graph, and communicates with provider plugins. Errors produced at this level may be a bug. Later in this tutorial, you will learn best practices for opening a GitHub issue for the core development team.
4. **Provider errors**: The provider plugins handle authentication, API calls, and mapping resources to services. Later in this tutorial, you will learn best practices for opening a GitHub issue for the provider development team.

## Format the configuration

The format command scans the current directory for configuration files and rewrites your Terraform configuration files to the recommended format.

```Shell
terraform fmt
```

![[terraform-014.png]]

Terraform found problems that it could not parse, and output errors so you can fix the configuration manually.

## Validate your configuration

`terraform fmt` only parses your HCL for interpolation errors or malformed resource definitions, which is why you should use `terraform validate` after formatting your configuration to check your configuration in the context of the providers' expectations.

Initialize your Terraform directory to download the providers that your configuration requires.


```Bash
terraform init
```

Run `terraform validate` in your terminal. The output contains a cycle error that highlights a mutual dependency between two security group resources.

```
terraform validate
```

![[terraform-015.png]]

Cycle errors are instances of circular logic in the Terraform dependency tree. Terraform analyzes the dependencies between resources in your infrastructure configuration to determine the order to perform your operations.

## Correct a cycle error

Your `aws_security_group` resources reference one another in their `security_groups` attributes. AWS cannot create the security groups because their configurations each reference the other group, which would not exist yet.

Remove the mutually dependent security group rules in your configuration, leaving the two group resources without ingress attributes.

Instead of including the rules in the `aws_security_group` configuration, use the `aws_security_group_rule` resource and reference the security group IDs instead. This avoids a cycle error because the provider will have AWS create both of the `aws_security_group` resources first, without interdependent rules. It will create the rules next, and attach the rules to the groups last.

Terraform does not continue validating once it catches an error. Run the `terraform validate` command to catch new errors: an invalid reference a the `for_each` attribute because of a splat expression (`*`) in its value.

```
terraform validate
```

![[terraform-016.png]]
The `each` attribute in the `vpc_security_group_ids` cannot return the IDs because of the `for_each` error above it. Terraform did not return any security group IDs, so the `each` object is invalid.

Terraform cannot automatically convert types without additional functions.

In the next section, you will correct this expression and `for_each` error.

## Correct a `for_each` error

Terraform's `for_each` attribute allows you to create a set of similar resources based on the criteria you define.

In this example, you need to create a set of similar instances, each assigned to a different security group. Terraform cannot parse `aws_security_group.*.id` in this attribute because the splat expression `(*)` only interpolates list types, while the `for_each` attribute is reserved for map types. A local value can return a map type.

In `main.tf`, on line 44, replace the value of the `for_each` attribute with a local value. On line 47, replace the `vpc_security_group_ids` value with the value from the `for_each` attribute. Finally, update the `tags` attribute to give each instance a unique name.

now terraform validate again.

![[terraform-017.png]]

## Correct your outputs to return all values

To correct your outputs, you need the `for` expression to capture the elements of the multiple resources.

The `for` expression captures all of the elements of `aws_instance.web_app` in a temporary variable called `instance`. Then, Terraform returns all of the specified values of the `instance` elements. In this example, `instance.id`, `instance.public_ip`, and `instance.tags.Name` return every matching key value for each instance you created.

Open `outputs.tf` and update the output values with the `for` expression.

---
## Bug reporting best practices

You may experience errors due to provider or application issues. Once you eliminate the possibility of language misconfiguration, version mismatching, or state discrepancies, consider bringing your issue to the core Terraform team or Terraform provider community as a bug report.

To provide the development team or the community working on your issue with full context, here are some best practices for opening up a GitHub issue.

### Confirm versioning

Confirm the versions of the providers you are using and the version of Terraform you have in your environment. To confirm your provider and Terraform versions, run the version command.

```
terraform version
```

You can also validate that you are using the correct and most recent versions of your providers before reporting a bug. If your lock file specifies an older version, consider updating your providers and attempting to run your operation again.

### Enable Terraform logging

Terraform 0.15 and later allow you to generate logs from the Terraform provider and the core application separately. The Terraform development team needs the core logs for your attempted operation to troubleshoot core-related errors. To enable core logging, set the `TF_LOG_CORE` environment variable to the appropriate [log level](https://developer.hashicorp.com/terraform/internals/debugging). For bug reports, you should use the `TRACE` level.

```Bash
export TF_LOG_CORE=TRACE
```

`TRACE` provides the highest level of logging and contains all the information the development teams need. There are other logging levels, but are typically reserved for developers looking for specific information.

You can also generate provider logs by setting the `TF_LOG_PROVIDER` environment variable. By including these in your bug reports, the provider development team can reproduce and debug provider specific errors.

```Shell
export TF_LOG_PROVIDER=TRACE
```

Once you have configured your logging, set the path for your error logs as an environment variable. If your `TF_LOG_CORE` or `TF_LOG_PROVIDER` environment variables are enabled, the `TF_LOG_PATH` variable will create the specified file and append logs generated by Terraform.

```Shell
export TF_LOG_PATH=logs.txt
```

To remove a log stream, unset the environment variable you do not need. Unset Terraform core logging. When you re-run Terraform, Terraform will only log provider specific operations. When you close your terminal session, all environment variables unset.

```Shell
export TF_LOG_CORE=
```

We can also open a ticket

[Opening a ticket](https://developer.hashicorp.com/terraform/tutorials/configuration-language/troubleshooting-workflow#open-a-ticket)