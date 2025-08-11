# Understand the structure and syntax of ARM templates

## Template Format

In its simplest structure, a template has the following elements:

```JSON
{
  "$schema": "https://schema.management.azure.com/schemas/2019-04-01/deploymentTemplate.json#",
  "languageVersion": "",
  "contentVersion": "",
  "apiProfile": "",
  "definitions": { },
  "parameters": { },
  "variables": { },
  "functions": [ ],
  "resources": [ ], /* or "resources": { } with languageVersion 2.0 */
  "outputs": { }
}
```

| Element name                                                                                               | Required | Description                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    |
| ---------------------------------------------------------------------------------------------------------- | -------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| $schema                                                                                                    | Yes      | Location of the JavaScript Object Notation (JSON) schema file that describes the version of the template language. The version number you use depends on the scope of the deployment and your JSON editor.  <br>  <br>If you're using [Visual Studio Code with the Azure Resource Manager tools extension](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/quickstart-create-templates-use-visual-studio-code), use the latest version for resource group deployments:  <br>`https://schema.management.azure.com/schemas/2019-04-01/deploymentTemplate.json#`  <br>  <br>Other editors (including Visual Studio) may not be able to process this schema. For those editors, use:  <br>`https://schema.management.azure.com/schemas/2015-01-01/deploymentTemplate.json#`  <br>  <br>For subscription deployments, use:  <br>`https://schema.management.azure.com/schemas/2018-05-01/subscriptionDeploymentTemplate.json#`  <br>  <br>For management group deployments, use:  <br>`https://schema.management.azure.com/schemas/2019-08-01/managementGroupDeploymentTemplate.json#`  <br>  <br>For tenant deployments, use:  <br>`https://schema.management.azure.com/schemas/2019-08-01/tenantDeploymentTemplate.json#` |
| languageVersion                                                                                            | No       | Language version of the template. To view the enhancements of languageVersion 2.0, see [languageVersion 2.0](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/syntax#languageversion-20).                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
| contentVersion                                                                                             | Yes      | Version of the template (such as 1.0.0.0). You can provide any value for this element. Use this value to document significant changes in your template. When deploying resources using the template, this value can be used to make sure that the right template is being used.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                |
| apiProfile                                                                                                 | No       | An API version that serves as a collection of API versions for resource types. Use this value to avoid having to specify API versions for each resource in the template. When you specify an API profile version and don't specify an API version for the resource type, Resource Manager uses the API version for that resource type that is defined in the profile.  <br>  <br>The API profile property is especially helpful when deploying a template to different environments, such as Azure Stack and global Azure. Use the API profile version to make sure your template automatically uses versions that are supported in both environments. For a list of the current API profile versions and the resources API versions defined in the profile, see [API Profile](https://github.com/Azure/azure-rest-api-specs/tree/master/profile).  <br>  <br>For more information, see [Track versions using API profiles](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/template-cloud-consistency#track-versions-using-api-profiles).                                                                                                                                                                            |
| [definitions](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/syntax#definitions) | No       | Schemas that are used to validate array and object values. Definitions are only supported in [languageVersion 2.0](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/syntax#languageversion-20).                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        |
| [parameters](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/syntax#parameters)   | No       | Values that are provided when deployment is executed to customize resource deployment.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |
| [variables](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/syntax#variables)     | No       | Values that are used as JSON fragments in the template to simplify template language expressions.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              |
| [functions](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/syntax#functions)     | No       | User-defined functions that are available within the template.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| [resources](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/syntax#resources)     | Yes      | Resource types that are deployed or updated in a resource group or subscription.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               |
| [outputs](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/syntax#outputs)         | No       | Values that are returned after deployment.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     |

### Definitions

In the `definitions` section of the template, specify the schemas used for validating array and object values. `Definitions` can only be used with [languageVersion 2.0](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/syntax#languageversion-20).

```JSON
"definitions": {
  "<definition-name>": {
    "type": "<data-type-of-definition>",
    "allowedValues": [ "<array-of-allowed-values>" ],
    "minValue": <minimum-value-for-int>,
    "maxValue": <maximum-value-for-int>,
    "minLength": <minimum-length-for-string-or-array>,
    "maxLength": <maximum-length-for-string-or-array>,
    "prefixItems": <schema-for-validating-array>,
    "items": <schema-for-validating-array-or-boolean>,
    "properties": <schema-for-validating-object>,
    "additionalProperties": <schema-for-validating-object-or-boolean>,
    "discriminator": <schema-to-apply>,
    "nullable": <boolean>,
    "metadata": {
      "description": "<description-of-the-type-definition>"
    }
  }
}
```

|Element name|Required|Description|
|---|---|---|
|definition-name|Yes|Name of the type definition. Must be a valid JavaScript identifier.|
|type|Yes|Type of the type definition. The allowed types and values are **string**, **securestring**, **int**, **bool**, **object**, **secureObject**, and **array**. See [Data types in ARM templates](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/data-types).|
|allowedValues|No|Array of allowed values for the type definition to make sure that the right value is provided.|
|minValue|No|The minimum value for int type definitions, this value is inclusive.|
|maxValue|No|The maximum value for int type definitions, this value is inclusive.|
|minLength|No|The minimum length for string, secure string, and array type definitions, this value is inclusive.|
|maxLength|No|The maximum length for string, secure string, and array type definitions, this value is inclusive.|
|prefixItems|No|The schema for validating the element of an array at the same index.|
|items|No|The schema that is applied to all elements of the array whose index is greater than the largest index of the `prefixItems` constraint, or boolean for controlling the elements of the array whose index is greater than the largest index of the `prefixItems` constraint.|
|properties|No|The schema for validating object.|
|additionalProperties|No|The schema that is applied to all properties not mentioned in the `properties` constraint, or boolean for accepting any property not defined in the `properties` constraint.|
|discriminator|No|The schema to apply based on a discriminator property.|
|nullable|No|A boolean indicating that the value may be null or omitted.|
|description|No|Description of the type definition that is displayed to users through the portal. For more information, see [Comments in templates](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/syntax#comments).|

### Parameters

In the `parameters` section of the template, you specify which values you can input when deploying the resources. You're limited to [256 parameters](https://learn.microsoft.com/en-us/azure/azure-resource-manager/management/azure-subscription-service-limits#general-limits) in a template. You can reduce the number of parameters by using objects that contain multiple properties.

The available properties for a parameter are:

```JSON
"parameters": {
  "<parameter-name>" : {
    "type" : "<type-of-parameter-value>",
    "defaultValue": "<default-value-of-parameter>",
    "allowedValues": [ "<array-of-allowed-values>" ],
    "minValue": <minimum-value-for-int>,
    "maxValue": <maximum-value-for-int>,
    "minLength": <minimum-length-for-string-or-array>,
    "maxLength": <maximum-length-for-string-or-array>,
    "prefixItems": <schema-for-validating-array>,
    "items": <schema-for-validating-array-or-boolean>,
    "properties": <schema-for-validating-object>,
    "additionalProperties": <schema-for-validating-object-or-boolean>,
    "discriminator": <schema-to-apply>,
    "nullable": <boolean>,
    "metadata": {
      "description": "<description-of-the parameter>"
    }
  }
}
```

### Variables

In the `variables` section, you construct values that can be used throughout your template. You don't need to define variables, but they often simplify your template by reducing complex expressions. The format of each variable matches one of the [data types](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/data-types). You're limited to [256 variables](https://learn.microsoft.com/en-us/azure/azure-resource-manager/management/azure-subscription-service-limits#general-limits) in a template.

```JSON
"variables": {
  "<variable-name>": "<variable-value>",
  "<variable-name>": {
    <variable-complex-type-value>
  },
  "<variable-object-name>": {
    "copy": [
      {
        "name": "<name-of-array-property>",
        "count": <number-of-iterations>,
        "input": <object-or-value-to-repeat>
      }
    ]
  },
  "copy": [
    {
      "name": "<variable-array-name>",
      "count": <number-of-iterations>,
      "input": <object-or-value-to-repeat>
    }
  ]
}
```

### Functions

Within your template, you can create your own functions. These functions are available for use in your template. Typically, you define complicated expressions that you don't want to repeat throughout your template. You create the user-defined functions from expressions and [functions](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/template-functions) that are supported in templates.

When defining a user function, there are some restrictions:

- The function can't access variables.
- The function can only use parameters that are defined in the function. When you use the [parameters function](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/template-functions-deployment#parameters) within a user-defined function, you're restricted to the parameters for that function.
- The function can't call other user-defined functions.
- The function can't use the [reference function](https://learn.microsoft.com/en-us/azure/azure-resource-manager/templates/template-functions-resource#reference).
- Parameters for the function can't have default values.

```JSON
"functions": [
  {
    "namespace": "<namespace-for-functions>",
    "members": {
      "<function-name>": {
        "parameters": [
          {
            "name": "<parameter-name>",
            "type": "<type-of-parameter-value>"
          }
        ],
        "output": {
          "type": "<type-of-output-value>",
          "value": "<function-return-value>"
        }
      }
    }
  }
],
```

| Element name    | Required | Description                                                                                                                                                                                                        |
| --------------- | -------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| namespace       | Yes      | Namespace for the custom functions. Use to avoid naming conflicts with template functions.                                                                                                                         |
| function-name   | Yes      | Name of the custom function. When calling the function, combine the function name with the namespace. For example, to call a function named `uniqueName` in the namespace contoso, use `"[contoso.uniqueName()]"`. |
| parameter-name  | No       | Name of the parameter to be used within the custom function.                                                                                                                                                       |
| parameter-value | No       | Type of the parameter value. The allowed types and values are **string**, **securestring**, **int**, **bool**, **object**, **secureObject**, and **array**.                                                        |
| output-type     | Yes      | Type of the output value. Output values support the same types as function input parameters.                                                                                                                       |
| output-value    | Yes      | Template language expression that is evaluated and returned from the function.                                                                                                                                     |
