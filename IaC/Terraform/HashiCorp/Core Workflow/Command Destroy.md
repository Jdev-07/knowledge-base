The `terraform destroy` command is a convenient way to destroy all remote objects managed by a particular Terraform configuration.

While you will typically not want to destroy long-lived objects in a production environment, Terraform is sometimes used to manage ephemeral infrastructure for development purposes, in which case you can use `terraform destroy` to conveniently clean up all of those temporary objects once you are finished with your work.

## Usage

Usage: `terraform destroy [options]`

This command is just a convenience alias for the following command:

```
terraform apply -destroy
```

For that reason, this command accepts most of the options that [`terraform apply`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/apply) accepts, although it does not accept a plan file argument and forces the selection of the "destroy" planning mode.

You can also create a speculative destroy plan, to see what the effect of destroying would be, by running the following command:

```
terraform plan -destroy
```

This will run [`terraform plan`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/plan) in _destroy_ mode, showing you the proposed destroy changes without executing them.