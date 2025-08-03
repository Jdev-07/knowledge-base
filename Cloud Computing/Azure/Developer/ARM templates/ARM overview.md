
To automate deployment and use the practice of IaC. In code, you define the infrastructure that needs to be deployed. The infrastructure code is part of your project. Just like application code, store the infrastructure code in a source repository and version it. Anyone on your team can run the code and deploy similar environments.

To implement infrastructure as code for your Azure solutions, use Azure Resource Manager templates (ARM templates). The template is a JavaScript Object Notation (JSON) file that defines the infrastructure and configuration for your project. The template uses declarative syntax, which lets you state what you intend to deploy without having to write the sequence of programming commands to create it. In the template, you specify the resources to deploy and the properties for those resources. You can also specify in which resource group those resources are deployed.

## Why choose ARM templates? 

Azure Resource Manager (ARM) templates offer  the following advantages

- **Declarative syntax**: ARM templates allow you to create and deploy an entire Azure infrastructure declaratively. For example, you can deploy not only virtual machines, but also the network infrastructure, storage systems, and any other resources you need.

- **Repeatable results**: Repeatedly deploy your infrastructure throughout the development lifecycle and have confidence your resources are deployed in a consistent manner. Templates are idempotent, which means you can deploy the same template many times and get the same resource types in the same state. You can develop one template that represents the desired state, rather than developing lots of separate templates to represent updates.

- **Orchestration**: You don't have to worry about the complexities of ordering operations. Resource Manager orchestrates the deployment of interdependent resources so they're created in the correct order. When possible, Resource Manager deploys resources in parallel, so your deployments finish faster than serial deployments. You deploy the template through one command, rather than through multiple imperative commands.

- **Modular files**: You can break your templates into smaller, reusable components and link them together at deployment time. You can also nest one template inside another template.

- **Create any Azure resource**: You can immediately use new Azure services and features in templates. As soon as a resource provider introduces new resources, you can deploy those resources through templates. You don't have to wait for tools or modules to be updated before using the new services.

- **Extensibility**: With [deployment scripts](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/deployment-script-template), you can add PowerShell or Bash scripts to your templates. The deployment scripts extend your ability to set up resources during deployment. You can include a script in the template or store it in an external source and reference it in the template. With deployment scripts, you can complete your end-to-end environment setup in a single ARM template.

- **Testing**: To ensure your template follows recommended guidelines, test it with the ARM template tool kit (arm-ttk). This test kit is a PowerShell script that you can download from [GitHub](https://github.com/Azure/arm-ttk). The tool kit makes it easier for you to develop expertise using the template language.

- **Preview changes**: Use the [what-if operation](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/deploy-what-if) to preview changes before deploying the template. With what-if, you see which resources to create, update, or delete, and any resource properties to change. The what-if operation checks the current state of your environment and eliminates the need to manage state.

- **Built-in validation**: Your template is deployed only after passing validation. Resource Manager checks the template before starting the deployment to make sure it succeeds. Your deployment is less likely to stop in a half-finished state.

- **Tracked deployments**: In the Azure portal, you can review the deployment history and get information about the template deployment. You can see the template that was deployed, the parameter values passed in, and any output values. Other infrastructure as code services aren't tracked through the portal.

- **Policy as code**: [Azure Policy](https://learn.microsoft.com/en-us/azure/governance/policy/overview) is a policy as code framework to automate governance. If you're using Azure policies, policy remediation is done on noncompliant resources when deployed through templates.

- **Deployment Blueprints**: You can take advantage of [Blueprints](https://learn.microsoft.com/en-us/azure/governance/blueprints/overview) provided by Microsoft to meet regulatory and compliance standards. These blueprints include prebuilt templates for various architectures.

- **CI/CD integration**: You can integrate templates into your continuous integration and continuous deployment (CI/CD) tools. This integration automates your release pipelines for fast and reliable application and infrastructure updates. By using Azure DevOps and Resource Manager template task, you can use Azure Pipelines to continuously build and deploy ARM template projects. To learn more, see [VS project with pipelines](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/add-template-to-azure-pipelines) and [Tutorial: Continuous integration of Azure Resource Manager templates with Azure Pipelines](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/deployment-tutorial-pipeline).

- **Exportable code**: You can get a template for an existing resource group by either exporting the current state of the resource group or viewing the template used for a particular deployment. Viewing the [exported template](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/export-template-portal) is a helpful way to learn about the template syntax.

- **Authoring tools**: You can author templates with [Visual Studio Code](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/quickstart-create-templates-use-visual-studio-code) and the template tool extension. You get IntelliSense, syntax highlighting, in-line help, and many other language functions. In addition to Visual Studio Code, you can also use [Visual Studio](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/create-visual-studio-deployment-project).