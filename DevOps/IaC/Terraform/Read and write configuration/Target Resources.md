## Overview

When you apply a plan, Terraform will include add, remove or modify resources as proposed by the plan, any differences between your configuration and the resources managed by the project will be included, if exist.

In special cases, you may need to apply only part of the plan, such as when Terraform's state has become out of the sync or has other problem. To address this problem, you can target specific resources using the option `-target`. This is very useful for troubleshooting errors. 

Targeting resources can introduce inconsistencies, so you should only use it in troubleshooting scenarios.  Apply changes to the entire working directory to make Terraform update your infrastructure to match the current configuration.

After using resource targeting to fix problems with a Terraform project, be sure to apply changes to the entire configuration to ensure consistency across all resources. Remember that you can use `terraform plan` to see any remaining proposed changes.

`-target` is a special Terraform option used only for specific situations, like fixing a single broken resource, bootstrapping something that must exist first, or debugging a failing apply. When you use it, Terraform updates **only** the targeted resource and ignores the rest of the infrastructure, which can leave the overall state **partially updated or out of sync** with your full configuration. Because of this, `-target` is not meant for normal use, and after using it, you should always run a regular `terraform apply` to bring the entire infrastructure back into a consistent and fully synchronized state.

`-replace` is the safer and more controlled option when a resource is broken or you need Terraform to recreate it, because it still performs a **full plan**, respects **all dependencies**, and shows you every change that will happen across your infrastructure. In contrast, `-target` only focuses on the specified resource and ignores the rest of the graph, which can leave your state **partially updated** and lead to inconsistencies. Use `-replace` when you want Terraform to properly destroy and recreate a resource within the full dependency context, and reserve `-target` only for very specific, surgical situations like bootstrapping or debugging where partial updates are acceptable.