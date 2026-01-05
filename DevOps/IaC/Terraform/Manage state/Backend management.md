
# Backends


Briefly, a backend is where Terraform state snapshots are stored. You can define a specific backend inside of the `terraform` block, integrate with Terraform cloud or do neither  and default to storing state locally. 


## What Backends do


A backend determines where the Terraform state is stored so it can be persisted and used by Terraform to keep track of managed resources.

By default, Terraform stores the state file locally on disk, but most other backends store the state remotely so multiple users can access it.

Some backends act like remote disks for state files, while others also support state locking during Terraform operations.


## Local backend

The local backend stores state on the local filesystem, locks state using system APIs, and performs operations locally. 

Example configuration:


```Go
terraform {
  backend "local" {
    path = "relative/path/to/terraform.tfstate"
  }
}
```


Data source configuration:


```Go
data "terraform_remote_state" "foo" {
  backend = "local"

  config = {
    path = "${path.module}/../../terraform.tfstate"
  }
}
```

**Configuration variables**

- `path`: this variable is completely optional. This default to `"terraform.tfsate"` relative to root module
- `workspace_dir`: The path to non-default workspaces.


For configurations using the **local backend**, Terraform provides the flags `-state`, `-state-out`, and `-backup` to control where state files are read, written, and backed up. These options exist mainly for **backward compatibility** with older workflows that managed state files manually. Using them overrides Terraform’s normal workspace-based state handling and can cause all workspaces to share the same state unless different filenames are managed manually. These flags do **not** work with remote backends and are **not recommended for new systems**. Instead, Terraform recommends using a **remote backend** so state is automatically shared, locked, and managed consistently without special command-line options.

## Backend configuration

Each Terraform configuration can specify a backend, by setting the `backend` block. Although, if you are working with Terraform cloud, then you do not to specify any `backend` block. 

**Using a Backend Block**

Backends are configure with a nested `backend` block within `terraform` block:

```Go
terraform {
  backend "remote" {
    organization = "example_corp"

    workspaces {
      name = "my-app-prod"
    }
  }
}
```


**Backend types**

The label of the `backend` block specifies which backend type Terraform will use, and it must be supported by the Terraform version in use. Each backend type has its own configuration arguments that define how and where the state is stored and may control additional behavior. Although some backends allow credentials to be defined in the configuration, this is not recommended for normal use; instead, credentials should be provided through environment variables or standard credential files. Terraform documentation lists all supported backend types and their specific configuration options.

If a configuration includes no backend block, Terraform defaults to using the local backend, which stores state as a plain file in the current working directory.




