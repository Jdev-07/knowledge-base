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