When you apply changes to your infrastructure, Terraform uses the providers and modules installed during initialization to execute the steps stored in an execution plan. These steps create, update, and delete infrastructure to match your resource configuration.

If you did not provide a saved plan, Terraform created a plan and asked you to approve it before making any changes to your resources.

When you approve the plan and apply this configuration, Terraform will:

1. Lock your workspace's state, so that no other instances of Terraform will attempt to modify your state or apply changes to your resources. If Terraform detects an existing lock file (`.terraform.tfstate.lock.info`), it will report an error and exit.
2. Create a plan, and wait for you to approve it. Alternatively, you can provide a saved plan created with the `terraform plan` command, in which case Terraform will not prompt for approval.
3. Execute the steps defined in the plan using the providers you installed when you initialized your configuration. Terraform executes steps in parallel when possible, and sequentially when one resource depends on another.
4. Update your workspace's state with a snapshot of the new state of your resources.
5. Unlock your workspace's state.
6. Report the changes it made, as well as any output values defined in your configuration.

### Errors during apply

When Terraform encounters an error during an apply step, it will:

1. Log the error and report it to the console.
2. Update the state file with any changes to your resources.
3. Unlock the state file.
4. Exit.

Your infrastructure may be in an invalid state after a Terraform apply step errors out. Terraform does not support automatically rolling back a partially-completed apply. After you resolve the error, you must apply your configuration again to update your infrastructure to the desired state.

To review how Terraform handles errors, introduce an intentional error during an apply.

### Common reasons for apply errors include:

1. A change to a resource outside of Terraform's control.
2. Networking or other transient errors.
3. An expected error from the upstream API, such as a duplicate resource name or reaching a resource limit.
4. An unexpected error from the upstream API, such as an internal server error.
5. A bug in the Terraform provider code, or Terraform itself.

Depending on the cause of the error, you may need to resolve the underlying issue by either modifying your configuration or diagnosing and resolving the error from the cloud provider API. Your Terraform project is still tracking the image resource because Terraform has not yet refreshed your resource's state.

Terraform stores it's current understanding of the state of your resources, either locally in the `terraform.tfstate` file, or on a remote backend such as HCP Terraform. You can use the `terraform show` command to print out your state. This command does not refresh your state, so the information in your state can be out of date. In this case, your project's state reports the existence of the S3 bucket you manually deleted earlier in this tutorial. When you apply a plan, Terraform will only make changes defined in the plan. Because of this, changes to your resources between the time you plan you changes and attempt to apply them can cause Terraform to error if the plan can no longer be applied as writted. To resolve this error, you must create and apply a new plan that takes the missing bucket into account.

The next time you plan a change to this project, Terraform will update the current state of your resources from the underlying APIs using the providers you have installed. Terraform will notice that the bucket represented by the `aws_s3_bucket.example` resource no longer exists, and generate a plan to create it before creating the new `aws_s3_object.example` object.

Apply your configuration. Terraform will referesh your workspace's state to reflect the fact that the S3 bucket no longer exists. Next it will create a plan to reconcile your configuration with that state by creating both the S3 bucket and object. Resources can change outside of Terraform's control for any number of reasons. In most cases, Terraform can handle these differences automatically by creating, destroying, or updating resources to make them match your configuration. Terraform will create a plan to do so, and wait for you to confirm it.

## Replace Resources

When using Terraform, you will usually apply an entire configuration change at once. Terraform and its providers will determine the changes to make and the order to make them in. However, there are some cases where you may need to replace or modify individual resources. Terraform provides two arguments to the `plan` and `apply` commands that allow you to interact with specific resources: `-replace` and `-target`.

Use the `-replace` argument when a resource has become unhealthy or stops working in ways that are outside of Terraform's control. For instance, an error in your EC2 instance's OS configuration could require that the instance be replaced. There is no corresponding change to your Terraform configuration, so you want to instruct Terraform to reprovision the resource using the same configuration.

The `-replace` argument requires a resource address. List the resources in your configuration with `terraform state list`.

```Shell
terraform state list
```

```Shell
terraform apply -replace "aws_instance.main[1]"
```

The second case where you may need to partially apply configuration is when troubleshooting an error that prevents Terraform from applying your entire configuration at once. This type of error may occur when a target API or Terraform provider error leaves your resources in an invalid state that Terraform cannot resolve automatically. Use the `-target` command line argument when you apply to target individual resources rather than apply the entire configuration. Refer to the [Target resources](https://developer.hashicorp.com/terraform/tutorials/state/resource-targeting) tutorial for more information.
