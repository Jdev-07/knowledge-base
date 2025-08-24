The terraform init command is used to initialize a working directory containing Terraform configuration files. This is the first command that should be run after writing a new Terraform configuration or cloning an existing one from version control. It is safe to run this command multiple times.


## Usage

Usage: `terraform init [options]`

This command performs several different initialization steps in order to prepare the current working directory for use with Terraform. More details on these are in the sections below, but in most cases it is not necessary to worry about these individual steps.

This command is always safe to run multiple times, to bring the working directory up to date with changes in the configuration. Though subsequent runs may give errors, this command will never delete your existing configuration or state.

## General Options

The following options apply to all of (or several of) the initialization steps:

- 
    
    [`-input=true`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/init#input-true) Ask for input if necessary. If false, will error if input was required.
    
- 
    
    [`-lock=false`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/init#lock-false) Disable locking of state files during state-related operations.
    
- 
    
    [`-lock-timeout=<duration>`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/init#lock-timeout) Override the time Terraform will wait to acquire a state lock. The default is `0s` (zero seconds), which causes immediate failure if the lock is already held by another process.
    
- 
    
    [`-no-color`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/init#no-color) Disable color codes in the command output.
    
- 
    
    [`-upgrade`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/init#upgrade) Opt to upgrade modules and plugins as part of their respective installation steps. See the sections below for more details.


## Copy a Source Module

By default, `terraform init` assumes that the working directory already contains a configuration and will attempt to initialize that configuration.

Optionally, init can be run against an empty directory with the `-from-module=MODULE-SOURCE` option, in which case the given module will be copied into the target directory before any other initialization steps are run.

This special mode of operation supports two use-cases:

- Given a version control source, it can serve as a shorthand for checking out a configuration from version control and then initializing the working directory for it.
    
- If the source refers to an _example_ configuration, it can be copied into a local directory to be used as a basis for a new configuration.
    

For routine use it is recommended to check out configuration from version control separately, using the version control system's own commands. This way it is possible to pass extra flags to the version control system when necessary, and to perform other preparation steps (such as configuration generation, or activating credentials) before running `terraform init`.

### 🛠️ What `-from-module` does

It **copies a module** into your directory **before** running normal initialization.

Two main use cases:

1. **Shortcut for Git checkout**  
    Instead of doing this manually:

```Bash
git clone https://github.com/hashicorp/terraform-example
cd terraform-example
terraform init
```

```Bash
terraform init -from-module=https://github.com/hashicorp/terraform-example
```

- And Terraform will **copy the repo/module into your folder**, then run `init`.

**Start from an example**  
Suppose HashiCorp provides an example VPC configuration. You can grab it directly into your project like this:

```Bash
terraform init -from-module=hashicorp/example-vpc
```

Now you have a **ready-to-edit template** in your directory, instead of writing everything from scratch.

## Backend Initialization

During init, the root configuration directory is consulted for [backend configuration](https://developer.hashicorp.com/terraform/language/v1.1.x/settings/backends/configuration) and the chosen backend is initialized using the given configuration settings.

Re-running init with an already-initialized backend will update the working directory to use the new backend settings. Either `-reconfigure` or `-migrate-state` must be supplied to update the backend configuration.

The `-migrate-state` option will attempt to copy existing state to the new backend, and depending on what changed, may result in interactive prompts to confirm migration of workspace states. The `-force-copy` option suppresses these prompts and answers "yes" to the migration questions. This implies `-migrate-state`.

The `-reconfigure` option disregards any existing configuration, preventing migration of any existing state.

To skip backend configuration, use `-backend=false`. Note that some other init steps require an initialized backend, so it is recommended to use this flag only when the working directory was already previously initialized for a particular backend.

The `-backend-config=...` option can be used for [partial backend configuration](https://developer.hashicorp.com/terraform/language/v1.1.x/settings/backends/configuration#partial-configuration), in situations where the backend settings are dynamic or sensitive and so cannot be statically specified in the configuration file.

## 📌 First, what’s a backend?

- A **backend** is **where Terraform stores its state file** (`terraform.tfstate`).
    
- By default, it’s **local** (on your computer).
    
- But in real projects, you usually configure a **remote backend** (e.g., Azure Storage, AWS S3, GCS, Terraform Cloud) so the state is shared safely with your team.

## 🔄 Backend Initialization

When you run:

```bash
terraform init
```

Terraform looks at your root configuration (the folder with `.tf` files) and:

1. Finds the **backend settings** (like `"azurerm"`, `"s3"`, `"gcs"`, etc).
    
2. Initializes that backend so Terraform knows where to read/write the state.

## ⚙️ Changing the backend

If you change backend settings (e.g., from local → S3), you need to tell Terraform **how to handle the state migration**.

- `terraform init -reconfigure`  
    🔹 Throw away old backend settings.  
    🔹 No migration of existing state — you start fresh.
    
- `terraform init -migrate-state`  
    🔹 Terraform will **copy your existing state** into the new backend.  
    🔹 It may ask you for confirmation.
    
- `terraform init -migrate-state -force-copy`  
    🔹 Same as above, but **skips the prompts** (auto “yes”).

## 🛠️ Extra Options

- `terraform init -backend=false`  
    🔹 Skip backend setup.  
    🔹 Only use if you already initialized before — otherwise, some steps might fail.
    
- `terraform init -backend-config="key=value"`  
    🔹 Override backend settings **at init time** (useful for sensitive or dynamic values).  
    🔹 Example:

```Bash
terraform init \
  -backend-config="resource_group_name=myRG" \
  -backend-config="storage_account_name=mystorage" \
  -backend-config="container_name=tfstate" \
  -backend-config="key=prod.terraform.tfstate"
```

## Child Module Installation

During init, the configuration is searched for `module` blocks, and the source code for referenced [modules](https://developer.hashicorp.com/terraform/language/v1.1.x/modules/develop) is retrieved from the locations given in their `source` arguments.

Re-running init with modules already installed will install the sources for any modules that were added to configuration since the last init, but will not change any already-installed modules. Use `-upgrade` to override this behavior, updating all modules to the latest available source code.

To skip child module installation, use `-get=false`. Note that some other init steps can complete only when the module tree is complete, so it's recommended to use this flag only when the working directory was already previously initialized with its child modules.

## 📌 Child Module Installation

When you run:

```Bash
terraform init
```

Terraform looks at your `.tf` files and checks for **module blocks**, like this:

```Go
module "network" {
  source = "Azure/network/azurerm"
  version = "5.0.0"
}
```

- Terraform sees the `source` argument (could be from the Terraform Registry, GitHub, local path, etc).
    
- It **downloads that module’s code** into the `.terraform/modules/` folder.
    
- Now your root configuration can use the module.

## 🔄 Re-running `terraform init`

- If you run `terraform init` again, Terraform:  
    ✅ Installs **new modules** (if you added any).  
    ❌ Does **not** update already-installed modules (keeps same version).
    

If you want Terraform to fetch the **latest version** of all modules, you run:

```Bash
terraform init -upgrade
```

## ⚙️ Skipping module download

- `terraform init -get=false` → Skip downloading child modules.
    
- But ⚠️ some other init steps require modules, so use this only if:
    
    - You already initialized before,
        
    - and you just want to skip fetching again.

## Plugin Installation

Most Terraform providers are published separately from Terraform as plugins. During init, Terraform searches the configuration for both direct and indirect references to providers and attempts to install the plugins for those providers.

For providers that are published in either [the public Terraform Registry](https://registry.terraform.io/) or in a third-party provider registry, `terraform init` will automatically find, download, and install the necessary provider plugins. If you cannot or do not wish to install providers from their origin registries, you can customize how Terraform installs providers using [the provider installation settings in the CLI configuration](https://developer.hashicorp.com/terraform/cli/v1.1.x/config/config-file#provider-installation).

For more information about specifying which providers are required for each of your modules, see [Provider Requirements](https://developer.hashicorp.com/terraform/language/v1.1.x/providers/requirements).

After successful installation, Terraform writes information about the selected providers to [the dependency lock file](https://developer.hashicorp.com/terraform/language/v1.1.x/files/dependency-lock). You should commit this file to your version control system to ensure that when you run `terraform init` again in future Terraform will select exactly the same provider versions. Use the `-upgrade` option if you want Terraform to ignore the dependency lock file and consider installing newer versions.

You can modify `terraform init`'s plugin behavior with the following options:

- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/init#)
    
    [`-upgrade`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/init#upgrade-1) Upgrade all previously-selected plugins to the newest version that complies with the configuration's version constraints. This will cause Terraform to ignore any selections recorded in the dependency lock file, and to take the newest available version matching the configured version constraints.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/init#)
    
    [`-get-plugins=false`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/init#get-plugins-false) — Skip plugin installation.
    
    Note: Since Terraform 0.13, this option has been superseded by the [`provider_installation`](https://developer.hashicorp.com/terraform/cli/v1.1.x/config/config-file#provider-installation) and [`plugin_cache_dir`](https://developer.hashicorp.com/terraform/cli/v1.1.x/config/config-file#plugin_cache_dir) settings. It should not be used in Terraform versions 0.13+, and this option was removed in Terraform 0.15.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/init#)
    
    [`-plugin-dir=PATH`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/init#plugin-dir-path) — Force plugin installation to read plugins _only_ from the specified directory, as if it had been configured as a `filesystem_mirror` in the CLI configuration. If you intend to routinely use a particular filesystem mirror then we recommend [configuring Terraform's installation methods globally](https://developer.hashicorp.com/terraform/cli/v1.1.x/config/config-file#provider-installation). You can use `-plugin-dir` as a one-time override for exceptional situations, such as if you are testing a local build of a provider plugin you are currently developing.
    
- [](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/init#)
    
    [`-lockfile=MODE`](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands/init#lockfile-mode) Set a dependency lockfile mode.
    

The valid values for the lockfile mode are as follows:

- readonly: suppress the lockfile changes, but verify checksums against the information already recorded. It conflicts with the `-upgrade` flag. If you update the lockfile with third-party dependency management tools, it would be useful to control when it changes explicitly.

When you run `terraform init`:

1. Terraform checks your config for providers (like `azurerm`, `aws`, etc.).
    
2. It downloads those provider plugins from the **Terraform Registry** (or from another place you configure).
    
3. It saves info about which version you used in the **dependency lock file (`.terraform.lock.hcl`)**.

### 📂 Why the lock file matters

Imagine you and your teammate both run `terraform init`. Without the lock file:

- You could get provider version `3.0.0`
    
- They could get provider version `3.1.1`
    

This could cause different behavior.  
By **committing the lock file**, everyone installs the exact same provider version.

### ⚙️ Important flags

- `-upgrade` → tells Terraform: _“Forget the lock file, get me the newest version that fits my version constraints.”_
    
- `-get-plugins=false` → skip downloading providers (not recommended anymore).
    
- `-plugin-dir=PATH` → use providers only from a local directory (useful for testing or offline installs).
    
- `-lockfile=MODE` → controls how the lock file is updated or checked.
    
    - `readonly` = don’t change it, just verify integrity.

## Running `terraform init` in automation

For teams that use Terraform as a key part of a change management and deployment pipeline, it can be desirable to orchestrate Terraform runs in some sort of automation in order to ensure consistency between runs, and provide other interesting features such as integration with version control hooks.

There are some special concerns when running `init` in such an environment, including optionally making plugins available locally to avoid repeated re-installation. For more information, see the [Running Terraform in Automation](https://developer.hashicorp.com/terraform/tutorials/automation/automate-terraform?utm_source=WEBSITE&utm_medium=WEB_IO&utm_offer=ARTICLE_PAGE&utm_content=DOCS) tutorial on HashiCorp Learn.

- **Why automation matters**  
    Teams often integrate Terraform into pipelines (GitHub Actions, Azure DevOps, Jenkins, etc.) so every deployment is **consistent, repeatable, and version-controlled**.
    
- **Special considerations with automation**
    
    - If every automated run re-downloads providers and modules from the internet, it can slow down the pipeline and even cause failures if the registry is temporarily unavailable.
        
    - To solve this, teams **make plugins and modules available locally** (using caching or mirrors) so pipelines don’t waste time reinstalling the same things over and over.
        
- **Example real-world scenario**  
    Let’s say your company has a CI/CD pipeline in **Azure DevOps**:
    
    1. Developer commits Terraform code to GitHub.
        
    2. Azure DevOps pipeline triggers.
        
    3. Pipeline runs `terraform init` before plan/apply.
        
    4. Instead of downloading the Azure provider plugin from the registry every single run, the pipeline uses a **local cache** or an **internal registry mirror**. This saves time and ensures reliability.


## Passing a Different Configuration Directory

Terraform v0.13 and earlier also accepted a directory path in place of the plan file argument to `terraform apply`, in which case Terraform would use that directory as the root module instead of the current working directory.

That usage is still supported in Terraform v0.14, but is now deprecated and we plan to remove it in Terraform v0.15. If your workflow relies on overriding the root module directory, use [the `-chdir` global option](https://developer.hashicorp.com/terraform/cli/v1.1.x/commands#switching-working-directory-with-chdir) instead, which works across all commands and makes Terraform consistently look in the given directory for all files it would normally read or write in the current working directory.

If your previous use of this legacy pattern was also relying on Terraform writing the `.terraform` subdirectory into the current working directory even though the root module directory was overridden, use [the `TF_DATA_DIR` environment variable](https://developer.hashicorp.com/terraform/cli/v1.1.x/config/environment-variables#tf_data_dir) to direct Terraform to write the `.terraform` directory to a location other than the current working directory.