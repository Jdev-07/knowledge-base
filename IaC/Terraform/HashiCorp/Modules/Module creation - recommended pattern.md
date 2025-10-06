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