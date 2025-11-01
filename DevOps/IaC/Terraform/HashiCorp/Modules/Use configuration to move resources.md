As your terraform setup grows in complexity,  updating resources becomes more risky. An action may cause unintended changes. To address this problem, you can separate the configuration in module to limit the scope of changes. 

When you move resources you must let terraform you intend to move resources only. Otherwise terraform will replace them.

The `moved` configuration block lets you track your resource moves in the configuration itself. With the `moved` configuration block, you can plan, preview, and validate resource moves, enabling you to safely refactor your configuration.

Documentation I followed: [Move resources](https://developer.hashicorp.com/terraform/tutorials/modules/move-config)
Repository: [Terraform move resources](https://github.com/hashicorp-education/learn-terraform-move)


