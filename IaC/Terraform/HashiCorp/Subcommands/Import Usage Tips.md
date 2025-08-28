# Importing existing resources

This topic describes how to use the `terraform import` command to import existing infrastructure resources so that you can manage them as code.

## Overview

Use the `terraform import` command to import existing infrastructure to Terraform state. The `terraform import` command can only import one resource at a time. It cannot simultaneously import an entire collection of resources, such as an AWS VPC.

Complete the following steps to import resources:

1. Add the resource you want to manage with Terraform to your Terraform configuration.
2. Run the `terraform import` command.

Warning: Terraform expects that each remote object it is managing will be bound to only one resource address, which is normally guaranteed by Terraform itself having created all objects. If you import existing objects into Terraform, be careful to import each remote object to only one Terraform resource address. If you import the same object multiple times, Terraform may exhibit unwanted behavior. For more information on this assumption, see [the State section](https://developer.hashicorp.com/terraform/language/state).

## Add the resource to your configuration

Write a resource block for the resource you want to import in your configuration. Provide a name for the resource, which is a unique ID that you can use to reference the resource elsewhere in the configuration.

In the following example, the imported resource is an AWS instance named `example`:

```Go
resource "aws_instance" "example" {
  # ...instance configuration...
}
```

You do not have to complete the body of the resource block. Instead, you can finish defining arguments after the instance is imported.

## Run the `terraform import` command

Run `terraform import` to attach an existing instance to the resource configuration:

```
$ terraform import aws_instance.example i-abcd1234
```

This command locates the AWS EC2 instance with ID `i-abcd1234`. Then it attaches the existing settings of the instance, as described by the EC2 API, to the name `aws_instance.example` of a module. In this example, the module path implies that the root module is used. Finally, the mapping is saved in the Terraform state.

It is also possible to import to resources in child modules, using their paths, and to single instances of a resource with `count` or `for_each` set. See [_Resource Addressing_](https://developer.hashicorp.com/terraform/cli/state/resource-addressing) for more details on how to specify a target resource.

The syntax of the given ID is dependent on the resource type being imported. For example, AWS instances use an opaque ID issued by the EC2 API, but AWS Route53 Zones use the domain name itself. Consult the documentation for each importable resource for details on what form of ID is required.

As a result of the above command, the resource is recorded in the state file. You can now run `terraform plan` to see how the configuration compares to the imported resource, and make any adjustments to the configuration to align with the current (or desired) state of the imported object.

### 🔹 1. Configuration file (HCL code)

- You **write a resource block** for the resource you want to import.
    
- At this stage, the block can even be empty (no arguments), because Terraform only needs a placeholder.`resource "aws_instance" "example" {}`
- Import **does not automatically fill this block**. You’ll need to later add arguments (`ami`, `instance_type`, tags, etc.) so that the config matches the real resource.
    

---

### 🔹 2. Real Infrastructure (your AWS, Azure, etc.)

- Import **does not create, modify, or delete** anything in the actual infrastructure.
    
- The existing resource (say EC2 instance `i-abcd1234`) stays exactly the same.
    
- Import just "links" it to Terraform, telling Terraform: _"This EC2 instance already exists, start tracking it under this resource address."_
    

---

### 🔹 3. Terraform State (`terraform.tfstate`)

- Import **adds a new mapping** in the state file.

## Complex Imports

The above import is considered a "simple import": one resource is imported into the state file. An import may also result in a "complex import" where multiple resources are imported. For example, an AWS network ACL imports an `aws_network_acl` but also one `aws_network_acl_rule` for each rule.

In this scenario, the secondary resources will not already exist in the configuration, so it is necessary to consult the import output and create a `resource` block in the configuration for each secondary resource. If this is not done, Terraform will plan to destroy the imported objects on the next run.

If you want to rename or otherwise move the imported resources, the [state management commands](https://developer.hashicorp.com/terraform/cli/commands/state) can be used.

### 🔹 What happens during a **complex import**

- Some resources (like `aws_network_acl`) are **composite**: when you import them, Terraform doesn’t just bring in one object — it also discovers **related dependent resources** (e.g., `aws_network_acl_rule` for each rule).
    
- The **state file** will now include **all those resources**.
    
- But your **configuration file** may not yet describe those secondary resources, which creates a mismatch.
    

---

### 🔹 State

- Terraform records **all resources** (primary + secondary) it detects during import.
    
- Example:
    
    - State will now have `aws_network_acl.example` and `aws_network_acl_rule.rule-1`, `aws_network_acl_rule.rule-2`, etc.
        
- If the config does not define the rules, Terraform thinks:
    
    > “These resources exist in state but not in config → they should be destroyed.”
    

---

### 🔹 Real Infrastructure

- Nothing is modified during import — Terraform is only **reading existing infrastructure**.
    
- But if you later run `terraform plan` without adding missing resource blocks to config, Terraform will propose **destroying those extra objects** (like ACL rules).
    

---

### 🔹 Configuration File

- You must **manually add resource blocks** for each secondary resource so Terraform can manage them properly.
    
- Example (after importing a network ACL with rules):

```Go
resource "aws_network_acl" "example" {
  vpc_id = "vpc-123456"
}

resource "aws_network_acl_rule" "allow_http" {
  network_acl_id = aws_network_acl.example.id
  rule_number    = 100
  protocol       = "tcp"
  rule_action    = "allow"
  cidr_block     = "0.0.0.0/0"
  from_port      = 80
  to_port        = 80
}
```

### ⚠️ If you don’t update config:

- Terraform sees resources in **state** that aren’t in **config** → it will destroy them.
    
- That’s why after a **complex import**, you must always align the config with state.
    

---

👉 So in summary:

- **State**: Stores everything imported (primary + secondary resources).
    
- **Infrastructure**: Not touched by import.
    
- **Configuration**: Must be updated to include all imported resources, otherwise Terraform will want to destroy them.