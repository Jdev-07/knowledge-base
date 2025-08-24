When you initialize a Terraform workspace, Terraform configures the backend, installs all providers and modules referred to in your configuration, and creates a version lock file if one doesn't already exist. In addition, you can use the `terraform init` command to change your workspace's backend and upgrade your workspace's providers and modules.


Initialize your Terraform workspace with `terraform init` when:

- You create new Terraform configuration and are ready to use it to create a workspace and provision infrastructure.
    
- You clone a version control repository containing Terraform configuration, and are ready to use it to create a workspace and provision infrastructure.
    
- You add, remove, or change the version of a module or provider in an existing workspace.
    
- You add, remove, or change the `backend` or `cloud` blocks within the `terraform` block of an existing workspace.