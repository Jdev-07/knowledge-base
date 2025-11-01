
Terraform enables the definition, preview, and deployment of cloud infrastructure. Using Terraform, you create configuration files using [HCL syntax](https://developer.hashicorp.com/terraform/language/syntax/configuration). The HCL syntax allows you to specify the cloud provider - such as Azure - and the elements that make up your cloud infrastructure. After you create your configuration files, you create an _execution plan_ that allows you to preview your infrastructure changes before they're deployed. Once you verify the changes, you apply the execution plan to deploy the infrastructure.

Terraform state is used to reconcile deployed resources with Terraform configurations. State allows Terraform to know what Azure resources to add, update, or delete.

By default, Terraform state is stored locally, which isn't ideal for the following reasons:

- Local state doesn't work well in a team or collaborative environment.
- Terraform state can include sensitive information.
- Storing state locally increases the chance of inadvertent deletion.

## Key points for configuring the remote state storage account

- Azure storage accounts require a globally unique name. 
- *Terraform state is stored in plain text and may contain secrets.* If the state is incorrectly secured, unauthorized access to systems and data loss can result.
- In this example, Terraform authenticates to the Azure storage account using an Access Key. In a production deployment, it's recommended to evaluate the available [authentication options](https://developer.hashicorp.com/terraform/language/settings/backends/azurerm) supported by the AzureRM backend and to use the most secure option for your use case.
- In this example, public network access is allowed to this Azure storage account. In a production deployment, it's recommended to restrict access to this storage account using a [storage firewall, service endpoint, or private endpoint](https://learn.microsoft.com/en-us/azure/storage/common/storage-network-security).


```shell
$rg_name = "tfstate"
$storage_name = "tfstate$(Get-Random)"
$container_name = "tfstate"
```

Example:

```SHELL
# Resource group creation
New-AzResourceGroup -Name $RG_NAME -Location canadacentral

# Storage account creation
$storageAccount = New-AzStorageAccount -ResourceGroupName $RG_NAME -Name $STORAGE_NAME -SkuName Standard_LRS canadacentral -AllowBlobPublicAccess $false

# Container creation
New-AzStorageContainer -Name $CONTAINER_NAME -Context $storageAccount.context

```
## Configure Terraform Backend State

To configure the backend state, you need the following Azure storage information

- **storage_account_name**: The name of the Azure Storage account.
- **container_name**: The name of the blob container.
- **key**: The name of the state store file to be created.
- **access_key**: The storage access key.

Each of these values can be specified in the Terraform configuration file or on the command line. We recommend that you use an environment variable for the `access_key` value. Using an environment variable prevents the key from being written to disk.

Run the following commands to get the storage access key and store it as an environment variable:

```SHELL
$ACCOUNT_KEY=(Get-AzStorageAccountKey -ResourceGroupName $RG_NAME -Name $STORAGE_NAME)
```

Can use a key vault for securely save the keys. However, if you are not going to use a Key vault, export the keys as follows:

```SHELL
 $env:ARM_ACCESS_KEY=$ACCOUNT_KEY[0].value
```

Then, we need to configure the backend configuration block

```C#
terraform {
  required_providers {
    azurerm = {
      source  = "hashicorp/azurerm"
      version = "~>3.0"
    }
  }
  backend "azurerm" {
      resource_group_name  = "tfstate"
      storage_account_name = "<storage_account_name>"
      container_name       = "tfstate"
      key                  = "terraform.tfstate"
  }

}

provider "azurerm" {
  features {}
}

resource "azurerm_resource_group" "state-demo-secure" {
  name     = "state-demo"
  location = "eastus"
}
```

Then we will to run the following commands:

```SHELL
# Initialize command
terraform init

# Run the configuration
terraform apply
```

## Understand state locking

Azure Storage blobs are automatically locked before any operation that writes state. This pattern prevents concurrent state operations, which can cause corruption.

For more information, see [State locking](https://www.terraform.io/docs/state/locking.html) in the Terraform documentation.

You can see the lock when you examine the blob through the Azure portal or other Azure management tooling.

![[azure-001.png]]

## Understand encryption-at-rest

Data stored in an Azure blob is encrypted before being persisted. When needed, Terraform retrieves the state from the backend and stores it in local memory. If you use this pattern, state is never written to your local disk.