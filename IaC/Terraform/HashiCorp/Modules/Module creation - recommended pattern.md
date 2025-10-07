Terraform modules simplify infrastructure deployments by packaging reusable code. They make adoption easier for users and should follow best practices like clear organization and the DRY principle.

## Module creation workflow

The first step when creating a module is to find a early adopter team to refine the module functionality using input variables and outputs. This can help to onboard other teams with similar requirements and also, eliminates code duplication and speeds up the delivery. 

Once this step is completed, we can move forward with the following:

- Scope the requirements into appropriate modules
- Create the module minimum viable product (MVP)

**Scope the requirements into appropriate modules**

Deciding which infrastructure to include is one of the most challenging aspects, because a module must be well-structured and designed to perform its purpose effectively. A module should also be easy to explain; otherwise, it is probably too complex.

Always consider these areas:

- **Encapsulation:** group infrastructure that is always deployed together.
- **Privileges:** restrict modules to privileges boundaries,
- **Volatility:** separate long-lived infrastructure from short-lived. 

**Create the module MVP**

Modules are never complete, because there will always be new module requirements and changes. Aim for first module versions to meet the minimum viable product (MVP) standards. 

- Always aim to deliver a module that works for at least 80% of use cases.
- Never code for edge cases in modules. Don't be too specific 
- Avoid conditional expressions in an MVP
- The module should only expose the most commonly modified arguments as variables.

**Maximize outputs**

Output as much information as possible from your module MVP even if you do not currently have a use for it. This will make your module more useful for end users who will often use multiple modules, using outputs from one module as inputs for the next.
## Explore a scoping example

[Scenario ](https://developer.hashicorp.com/terraform/tutorials/modules/pattern-module-creation#explore-a-scoping-example)
## Module creation tips

When creating modules, design them so configuration authors can easily reuse and reference them in root modules. With HCP Terraform Standard Edition, you can also publish no-code modules that users deploy without writing Terraform code. 
### Nesting modules

A nested module is a module called from another module (root or otherwise). External ones are called **child modules**, while embedded ones are **submodules**. Nesting adds flexibility but should be used carefully to avoid errors.

For all types of nested modules, consider the following:

- Nesting modules can speed development, but can lead to unclear and unexpected outcomes. Clearly document the input variables, module behavior and outputs.
- Generally, do not nest primary modules more than two deep. Common and simple utility modules, like ones that define tags, are the exception to this rule.
- Nested modules should contain the necessary input variables to create specific resource configurations and outputs.
- Consistent naming conventions for input variables and outputs are highly recommended so modules can easily share and map input/output parameters.
- Nested modules can lead to code redundancy. Variable definitions and outputs need to be defined in nested and parent modules.

**External modules**

Nested external modules are useful for sharing standardized resources across teams and applications. They are usually **centrally managed and versioned**, ensuring new releases are validated before use. When using external child modules, specific considerations must be kept in mind.

- The external module must be maintained independently and made available to any module needing to invoke it. Using the Terraform registry is good way to ensure this.
- With the Terraform registry requirements, a nested module will have its own version controlled repository, which versions separately from its parent.
- A change to the nested module can affect the parent module with no changes to the parent's calling code or version, thereby breaking the calling code's trust.
- Document how parent modules use externally sourced modules so the behavior and invocation are easily understood.
- Revisions to external modules should be backwards compatible. If backwards-compatibility is impossible, changes that need to be made to any parent modules should be clearly documented and distributed to all module consumers to avoid surprises.

**Nesting submodules**

Embedding submodules in your code lets you separate logical parts of a module or create reusable blocks that can be called multiple times. For example, an `ec2-instance` submodule can be referenced by the root `main.tf`.

```
root-module-directory
├── README.md
├── main.tf
└── ec2-instances
   └── main.tf
```

If you need or desire to use submodules, here are some considerations:

- Adding the module to your "root" module means the submodule is versioned along with the called module.
- Any changes affecting the compatibility of the two modules is discovered quickly because they must be released and tested together.
- The submodule cannot be invoked by another module outside of the source tree so there may be increased code duplication. For example, if the embedded `ec2-instance` module is meant to create a standardized compute instance used in multiple places, it could **not** be shared in this format.

**Label and document module elements**

To get a higher module adoption and distribution, you should follow the naming convention to make it easier to understand for end-users.

- Use a module naming convention consistent and understandable by humans. For example:

| terraform | cloud provider | function        | full name                      |
| --------- | -------------- | --------------- | ------------------------------ |
| terraform | aws            | consul cluster  | `terraform-aws-consul_cluster` |
| terraform | aws            | security module | `terraform-aws-security`       |
| terraform | azure          | database        | `terraform-azure-database`     |

- Use a variable naming convention understandable by humans. Modules are code that will be written once and used many times
- Document all modules. Make sure the documentation includes:
	- **Required inputs**: These variables should be a deliberate choice. The module will fail if they are not defined. Only set defaults for variables that should have them.
	- **Optional inputs**: These should have a sensible default that will be acceptable in most use cases but may need adjusting.
	-  **Outputs**: List all the outputs of your module and wrap the important and informational ones in user-friendly output templates.

**Define and use a consistent module structure**

While module structure is a matter of taste, you should document the module structure and be consistent across all your modules. To keep your module structure consistent:

- Define a list of `.tf` files that must be in the module and what they should contain.
- Define a `.gitignore` (or similar) for modules.
- Create a standard way of providing examples of variables (such as a `terraform.tfvars.example`).
- Use a consistent directory structure with a defined set of directories, even if they may be empty.
- All modules directories should have a `README` detailing the purpose and use of the files within it.

## Collaborate on modules

As your team develops modules, streamline your collaboration.

1. **Create a roadmap for each module.**
2. **Gather requirements from your users and prioritize them by popularity**
	- The most common reason for not using a module is that "It does not do what I want." Gather these requirements and either add them to the roadmap or advise the user's workflow.
	- Check each requirement to determine if the use case it references is correct.
	- Publish and maintain the requirement list. Share it and involve users in the list curation process.
	- Don't prioritize edge-cases.
3. **Document every decision.**
4. **Adopt open-source community principles within the company.** Some users want to use the modules as efficiently as possible while others want to help create the modules.
	- Create a community,
	- Have a clearly defined and published contribution guide.
	- Eventually, you could allow trusted community members to own some modules.

## Use source control to track modules

A Terraform module should adhere to all good code practices.

- Place modules in source control to manage release versions, collaboration, and audit trail of changes (GitHub, GitLab, etc).
- Assign each module an owner.
- Select either the [tag-based](https://developer.hashicorp.com/terraform/cloud-docs/registry/publish-modules#tag-based-publishing-considerations) or [branch-based](https://developer.hashicorp.com/terraform/cloud-docs/registry/publish-modules#branch-based-publishing-considerations) publishing workflow.
- Use pull requests to review changes to your module before releasing them.
- Include documentation for your module, at minimum in the module's `README.md`, and publish a change log each version.


## Develop a module consumption workflow

Define and publicize a repeatable workflow that consuming teams should follow to use the modules.

### Make modules easy to use

- **Private Terraform registry**: The private Terraform registry provides a searchable, filterable way to manage your modules and allows consumers to browse and search for modules appropriate to their use case.
- **UI**: The Terraform Enterprise UI is less intimidating for Terraform novices and has a lower barrier to entry.
- **Configuration designer**: The configuration designer functions like interactive documentation for your private modules, or very advanced autocompletion. It results in the same Terraform code you would write in a text editor, and saves time by automatically discovering variables and searching module and workspace outputs for reusable values.

### Clarify how teams use modules

- **Devolved security**: If each module is versioned in its own repository, repository RBAC can be used to manage who has write access, allowing relevant teams to manage related infrastructure (such as the network team owning write access on network modules).
- **Fostering a code community**: The best practice for module development, given the above recommendations, is to allow pull requests on all module repositories for modules stored in the private module repository. This fosters a code community within the organization, keeps module content relevant and maximally flexible and helps maintain the registry's effectiveness in the long term.
- **Policy enforcement**: With Sentinel, you can assign policy criteria to all Terraform plans before execution. This allows for enforcement such that only modules from the private Terraform registry can be used; this provides greater control over collaboration and adoption of company policy and/or regulatory requirements.