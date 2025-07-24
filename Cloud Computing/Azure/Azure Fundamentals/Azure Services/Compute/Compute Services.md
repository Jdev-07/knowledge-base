Azure offers many ways to host apps code. The term compute refers to the hosting model for resources that your application runs on.

![[compute-001.png]]

## Understand basic features

- [Azure Virtual Machines](https://learn.microsoft.com/en-us/azure/virtual-machines): A service where you deploy and manage virtual machines (VMs) inside an Azure virtual network.
- [Azure App Service](https://learn.microsoft.com/en-us/azure/app-service): A managed service for hosting web apps, mobile app back ends, RESTful APIs, or automated business processes.
- [Azure Functions](https://learn.microsoft.com/en-us/azure/azure-functions/functions-overview): A service that provides managed functions that run based on a variety of trigger types for event-driven applications.
- [Azure Kubernetes Service (AKS)](https://learn.microsoft.com/en-us/azure/aks/intro-kubernetes): A managed Kubernetes service for running containerized applications.
- [Azure Container Apps](https://learn.microsoft.com/en-us/azure/container-apps): A managed service built on Kubernetes, which simplifies the deployment of containerized applications in a serverless environment.
- [Azure Container Instances](https://learn.microsoft.com/en-us/azure/container-instances/container-instances-overview): This service is a fast and simple way to run a single container or group of containers in Azure. Azure Container Instances doesn't provide full container orchestration, but you can implement them without having to provision any VMs or adopt a higher-level service.
- [Azure Red Hat OpenShift](https://learn.microsoft.com/en-us/azure/openshift): A fully managed OpenShift cluster for running containers in production with Kubernetes.
- [Azure Service Fabric](https://learn.microsoft.com/en-us/azure/service-fabric/service-fabric-overview): A distributed systems platform that can run in many environments, including Azure or on-premises.
- [Azure Batch](https://learn.microsoft.com/en-us/azure/batch/batch-technical-overview): A managed service for running large-scale parallel and high-performance computing (HPC) applications.
- [Azure VMware Solution](https://learn.microsoft.com/en-us/azure/azure-vmware/introduction): A managed service for running VMware workloads natively on Azure.

## Hosting models

For hosting models, cloud services fall into three categories:

- **Infrastructure as a service (IaaS)**: Lets you provision VMs along with the associated networking and storage components. Then you can deploy whatever software and applications you want onto those VMs. This model is the closest to a traditional on-premises environment. Microsoft manages the infrastructure. You still manage the VMs.
    
- **Platform as a service (PaaS)**: Provides a managed hosting environment where you can deploy your application without needing to manage VMs or networking resources. Azure App Service and Azure Container Apps are PaaS services.
    
- **Functions as a service (FaaS)**: Lets you deploy your code to the service, which automatically runs it. Azure Functions is a FaaS service.

## Services

##### [[1.0 Virtual Machines]]

##### [[2.0 Containers]]

##### [[3.0 App Services]]

##### [[4.0 Function Apps]]

##### [[5.0 Azure Logic Apps]]
