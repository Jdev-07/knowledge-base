## Resource Graph Overview

Terraform builds a `dependecy graph` from the Terraform configuration, and walk this graph to generate plans, refresh state, and more. 

## `Graph` nodes

There only a few nodes types that exist within graph:

- `resource node:` a resource node represents a single resource. If you `count`, Terraform creates one node per instance. Each node keeps the resource's configuration, the planned changes and its current state.
- `provider configuration node:` represents the time to fully configure a provider.
- `resource meta-node:` this node represents a group of resource instances created with `count > 1`. It does not perform any action itself, and its purpose is just to organize dependencies and make the graph easier to read.

Can visualize the nodes using `terraform graph`

### Building the `graph`

This process is done in a series of sequential steps:

- Resources are added based on the configuration. If diff plan or state is present, the meta-data is attached to each resource. 
- Resources are mapped to provisioners if they have defined. This must be done after all resources nodes are created so resources with the same provisioner type can share the provisioner implementation.
- Explicit dependencies from the `depends_on` meta-parameter are used to create edges between resources.
- If a state is present, any "orphan" resources are added to the graph. Orphan resources are any resources that are no longer present in the configuration but are present in the state file. Orphans never have any configuration associated with them, since the state file does not store configuration.
- Resources are mapped to providers. Provider configuration nodes are created for these providers, and edges are created such that the resources depend on their respective provider being configured.
- Interpolations are parsed in resource and provider configurations to determine dependencies. References to resource attributes are turned into dependencies from the resource with the interpolation to the resource being referenced.
- Create a root node. The root node points to all resources and is created so there is a single root to the dependency graph. When traversing the graph, the root node is ignored.
- If a diff is present, traverse all resource nodes and find resources that are being destroyed. These resource nodes are split into two: one node that destroys the resource and another that creates the resource (if it is being recreated). The reason the nodes must be split is because the destroy order is often different from the create order, and so they can't be represented by a single graph node.
- Validate the graph has no cycles and has a single root.


## Waling the `graph`

Terraform walks its `dependecy graph` using a depth-first traversal and runs tasks in parallel. A node starts only after all its dependencies have finished. 

To avoid overloading the machine, Terraform limits concurrency with a semaphore, by default, it processes **up to 10 nodes at the same time**.  
You can change this with **`-parallelism`**, but it’s an advanced flag and usually not needed.

Some providers (like AWS) already handle rate-limiting internally, so Terraform’s parallelism is **not** meant to fix API rate-limit issues.

Terraform's walking and parallelism ensures resources are created in the correct order. Terraforms builds a dependency  graph so it knows what must happen first: "A VPC must exist before a subnet6 "