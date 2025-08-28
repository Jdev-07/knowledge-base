Terraform stores information about your infrastructure in a state file. This state file keeps track of resources created by your configuration and maps them to real-world resources.

Terraform compares your configuration with the state file and your existing infrastructure to create plans and make changes to your infrastructure. When you run `terraform apply` or `terraform destroy` against your initialized configuration, Terraform writes metadata about your configuration to the state file and updates your infrastructure resources accordingly. Occasionally, you may need to manipulate your projects state outside of the standard workflow. For example, you may want to remove a resource from your project without destroying the real-world resource associated with it.

You should not manually change information in your state file in a real-world situation to avoid unnecessary drift between your Terraform configuration, state, and infrastructure. Any change in state could result in your infrastructure being destroyed and recreated at your next `terraform apply`.

Warning

Do not manually modify state files.

When checking the state file The first key in this schema is the `mode`. Mode refers to the type of resource Terraform creates — either a resource (`managed`) or a data source (`data`). The `type` key refers to the resource type - in this case, the `aws_ami` type is a resource available in the `aws` provider.

Terraform also marks dependencies between resources in state with the built-in dependency tree logic.

Because your state file has a record of your dependencies, enforced by you with a `depends_on` attribute or by Terraform automatically, any changes to the dependencies will force a change to the dependent resource.

## Examine State with CLI

The Terraform CLI allows you to review resources in the state file without interacting with the `.tfstate` file itself. This is how you should interact with your state.

Run `terraform show` to get a human-friendly output of the resources contained in your state.

Run `terraform state list` to get the list of resource names and local identifiers in your state file. This command is useful for more complex configurations where you need to find a specific resource without parsing state with `terraform show`.

---

## Replace a resource with CLI

Terraform usually only updates your infrastructure if it does not match your configuration. You can use the `-replace` flag for `terraform plan` and `terraform apply` operations to safely recreate resources in your environment even if you have not edited the configuration, which can be useful in cases of system malfunction. Replacing a resource is also useful in cases where a user manually changes a setting on a resource or when you need to update a provisioning script. This allows you to rebuild specific resources and avoid a full `terraform destroy` operation on your configuration. The `-replace` flag allows you to target specific resources and avoid destroying all the resources in your workspace just to fix one of them.

In older versions of Terraform, you may have used the `terraform taint` command to achieve a similar outcome. That command has now been deprecated in favor of the `-replace` flag, which allows for a simpler, less error-prone workflow. If you are using an older version of Terraform, consider upgrading or review the [`taint` documentation](https://developer.hashicorp.com/terraform/cli/commands/taint) for more information.

Tip

The `-replace` flag was introduced in Terraform 0.15.2. Ensure you are using the correct version of Terraform for this next step.

Run `terraform plan -replace="aws_instance.example"` to see the actions Terraform would take if you replaced the instance.

As shown in the output, when you apply this change, Terraform will destroy your running instance and create a new one.

Run `terraform apply` with the `-replace` flag to force Terraform to destroy and recreate the resource. Type `yes` when prompted to accept this update.

Using the `terraform apply` command with the `-replace` flag is the HashiCorp-recommended process for managing resources without manually editing your state file.

---
## Move a resource to a different state file

Some of the Terraform state subcommands are useful in very specific situations. HashiCorp recommends only performing these advanced operations as the last resort.

The `terraform state mv` command moves resources from one state file to another. You can also rename resources with `mv`. The move command will update the resource in state, but not in your configuration file. Moving resources is useful when you want to combine modules or resources from other states, but do not want to destroy and recreate the infrastructure.

The `new_state` subdirectory contains a new Terraform configuration. This configuration creates a new EC2 instance named `aws_instance.example_new` and uses a data resource to use the same security group from your root configuration file. Change into the subdirectory.

Move the new EC2 instance resource you just created, `aws_instance.example_new`, to the old configuration's file in the directory above your current location, as specified with the `-state-out` flag. Set the destination name to the same name, since in this case there is no resource with the same name in the target state file.

```Shell
terraform state mv -state-out=../terraform.tfstate aws_instance.example_new aws_instance.example_new
```

![[terraform-018.png]]

Note

Resource names _must_ be unique to the intended state file. The `terraform state mv` command can also rename resources to make them unique.

now check in the root directory 

```Shell
terraform state list
```

![[terraform-019.png]]

Without adding the EC2 resource you moved to your configuration files, create a Terraform plan. Because the new EC2 instance is present in state but not in the configuration, Terraform plans to destroy the moved instance, and remove the resource from the state file.

```Shell
terraform plan 
```

Now I pasted the configuration in the main.tf

```Go
resource "aws_instance" "example_new" {
  ami                    = data.aws_ami.ubuntu.id
  instance_type          = "t2.micro"
  vpc_security_group_ids = [aws_security_group.sg_8080.id]
  user_data              = <<-EOF
              #!/bin/bash
              apt-get update
              apt-get install -y apache2
              sed -i -e 's/80/8080/' /etc/apache2/ports.conf
              echo "Hello World" > /var/www/html/index.html
              systemctl restart apache2
              EOF
  tags = {
    Name = "terraform-learn-state-ec2"
  }
}
```

![[terraform-020.png]]

---

## Remove a resource from state

Use a `removed` block to remove specific resources from your state. This does not destroy the infrastructure itself, instead it indicates that your Terraform configuration will no longer manage the resource.

Change into your root directory.

Remove the `aws_instance.example_new` from your project's state.

Comment out the entire `resource "aws_instance" "example_new"` block from `main.tf` and add a `removed` block to instruct Terraform to remove the resource from state, but not destroy it.

The `removed` block was introduced in Terraform 1.7. Previous versions of Terraform used the `terraform state rm` command to remove resources from state. Ensure you are using the correct version of Terraform for this step.

Confirm the change by reviewing the state with `terraform state list`.

```bash
$ terraform state list
data.aws_ami.ubuntu
aws_instance.example
aws_security_group.sg_8080
```

The `aws_instance.example_new` resource does not exist in your project's state, but the resource still exists in your AWS account.

Import the instance back into your project. First, uncomment the `aws_instance.example_new` block, and comment out the `removed` block you added in the previous step.

```Go
# removed {
#   from = aws_instance.example_new

#   lifecycle {
#     destroy = false
#   }
# }

resource "aws_instance" "example_new" {
  ami                    = data.aws_ami.ubuntu.id
  instance_type          = "t2.micro"
  vpc_security_group_ids = [aws_security_group.sg_8080.id]
  user_data              = <<-EOF
              #!/bin/bash
              apt-get update
              apt-get install -y apache2
              sed -i -e 's/80/8080/' /etc/apache2/ports.conf
              echo "Hello World" > /var/www/html/index.html
              systemctl restart apache2
              EOF
  tags = {
    Name = "terraform-learn-state-ec2"
  }
}

```

Run `terraform import` to bring this instance back into your state file. Replace `<INSTANCE_ID>` with the id of the `aws_instance.example_new` resource from the output of the last step.

This tutorial uses `terraform import` to bring infrastructure under Terraform management. Terraform 1.5+ supports [configuration-driven import](https://developer.hashicorp.com/terraform/language/import), which lets you import multiple resources at once, review the import in your plan-and-apply workflow, and generate configuration for imported resources. Review the [import tutorial](https://developer.hashicorp.com/terraform/tutorials/state/state-import) to learn more.

Command:

```Bash
terraform import aws_instance.example_new <INSTANCE_ID>
```

---
## Refresh modified infrastructure

The `terraform refresh` command updates the state file when physical resources change outside of the Terraform workflow.

Delete the original EC2 instance from your AWS account using the AWS CLI or the [AWS Console](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/terminating-instances.html#terminating-instances-console). It may take a few moments for AWS to destroy your instance.

```Shell
aws ec2 terminate-instances --instance-ids $(terraform output -raw instance_id) --region $(terraform output -raw aws_region)
```

![[terraform-021.png]]By deleting this instance, you have created a difference between your state and the real-world resources mapped to it. The state file no longer reflects the reality of your environment. It may take up to five minutes for AWS to destroy your instance.

Run the `terraform refresh` command to update your state file.

```Shell
terraform refresh
```

```Output
data.aws_ami.ubuntu: Reading...
aws_security_group.sg_8080: Refreshing state... [id=sg-0cefa7398ff0ebe1f]
data.aws_ami.ubuntu: Read complete after 0s [id=ami-0fb0b230890ccd1e6]
aws_instance.example_new: Refreshing state... [id=i-086ff15e85bd0126c]
aws_instance.example: Refreshing state... [id=i-086ff15e85bd0126c]

Outputs:

aws_region = "us-east-1"
instance_id = "i-086ff15e85bd0126c"
public_ip = "54.234.50.52"
security_group = "sg-0cefa7398ff0ebe1f"
PS C:\Users\jony2\Desktop\Hands-on-Labs\Terraform\learn-terraform-state>
```
Run `terraform state list` to confirm Terraform deleted the original `aws_instance.example` resource from state.

Your state file now reflects reality. You deleted the `aws_instance.example` and the `terraform refresh` command removed it from state.

The `terraform refresh` command _does not_ update your configuration file. Run `terraform plan` to review the proposed infrastructure updates.