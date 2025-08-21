Terraform is a tool for building, changing, and versioning infrastructure safely and efficiently. Terraform is built on a plugin-based architecture, enabling developers to extend Terraform by writing new plugins or compiling modified versions of existing plugins.

Terraform is logically split into two main parts: **Terraform Core** and **Terraform Plugins**. Terraform Core uses remote procedure calls (RPC) to communicate with Terraform Plugins, and offers multiple ways to discover and load plugins to use. Terraform Plugins expose an implementation for a specific service, such as AWS, or provisioner, such as bash.

## Terraform Core

Terraform Core is a [statically-compiled binary](https://en.wikipedia.org/wiki/Static_build#Static_building) written in the [Go programming language](https://golang.org/). The compiled binary is the command line tool (CLI) `terraform`, the entrypoint for anyone using Terraform. The code source is available at [github.com/hashicorp/terraform](https://github.com/hashicorp/terraform).

### The primary responsibilities of Terraform Core are:

- Infrastructure as code: reading and interpolating configuration files and modules
- Resource state management
- Construction of the [Resource Graph](https://developer.hashicorp.com/terraform/internals/graph)
- Plan execution
- Communication with plugins over RPC
## Terraform Plugins

Terraform Plugins are written in Go and are executable binaries invoked by Terraform Core over RPC. Each plugin exposes an implementation for a specific service, such as AWS, or provisioner, such as bash. All Providers and Provisioners used in Terraform configurations are plugins. They are executed as a separate process and communicate with the main Terraform binary over an RPC interface. Terraform has several Provisioners built-in, while Providers are discovered dynamically as needed (See **Discovery** below). Terraform Core provides a high-level framework that abstracts away the details of plugin discovery and RPC communication so developers do not need to manage either.

Terraform Plugins are responsible for the domain specific implementation of their type.

### The primary responsibilities of Provider Plugins are:

- Initialization of any included libraries used to make API calls
- Authentication with the Infrastructure Provider
- Define managed resources and data sources that map to specific services
- Define functions that enable or simplify computational logic for practitioner configurations

### The primary responsibilities of Provisioner Plugins are:

- Executing commands or scripts on the designated Resource after creation, or on destruction.
## Discovery

**Advanced topic:** This section describes Terraform's plugin discovery behavior at the level of detail a plugin developer might need. For instructions suited to normal Terraform use, see [Configuring Providers](https://developer.hashicorp.com/terraform/language/providers/configuration).

When `terraform init` is run, Terraform reads configuration files in the working directory to determine which plugins are necessary, searches for installed plugins in several locations, sometimes downloads additional plugins, decides which plugin versions to use, and writes a lock file to ensure Terraform will use the same plugin versions in this directory until `terraform init` runs again.

### Plugin Locations

The [Terraform CLI docs](https://developer.hashicorp.com/terraform/cli/config/config-file#provider-installation) have up-to-date and detailed information about where Terraform looks for plugin binaries as part of `terraform init`. Consult that documentation for [information on where to place binaries during development](https://developer.hashicorp.com/terraform/cli/config/config-file#development-overrides-for-provider-developers).

### Selecting Plugins

After locating any installed plugins, `terraform init` compares them to the configuration's [version constraints](https://developer.hashicorp.com/terraform/language/providers/configuration#provider-versions) and chooses a version for each plugin as follows:

- If any acceptable versions are installed, Terraform uses the newest _installed_ version that meets the constraint (even if the [Terraform Registry](https://registry.terraform.io/) has a newer acceptable version).
- If no acceptable versions are installed and the plugin is one of the [providers distributed by HashiCorp](https://developer.hashicorp.com/terraform/language/providers), Terraform downloads the newest acceptable version from the [Terraform Registry](https://registry.terraform.io/) and saves it in a subdirectory under `.terraform/providers/`.
- If no acceptable versions are installed and the plugin is not distributed in the [Terraform Registry](https://registry.terraform.io/), initialization fails and the user must manually install an appropriate version.

### Upgrading Plugins

When `terraform init` is run with the `-upgrade` option, it re-checks the [Terraform Registry](https://registry.terraform.io/) for newer acceptable provider versions and downloads them if available.

This behavior only applies to providers whose _only_ acceptable versions are in the correct subdirectories under `.terraform/providers/` (the automatic downloads directory); if any acceptable version of a given provider is installed elsewhere, `terraform init -upgrade` will not download a newer version of it.

### Quick analogy💡

- **Terraform Core** = The “manager” that knows the plan but doesn’t do the actual work.
    
- **Provider Plugins** = The “specialists” that know how to work with AWS, Azure, etc.
    
- **Provisioner Plugins** = The “technicians” that run custom scripts inside resources.
    
- **terraform init** = The “HR department” making sure the right specialists are available, hiring them if needed, and recording their version in a file for future