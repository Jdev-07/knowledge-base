Infrastructure as Code (IaC) tools allow you to manage infrastructure with configuration files rather than through a graphical user interface. IaC allows you to build, change, and manage your infrastructure in a safe, consistent, and repeatable way by defining resource configurations that you can version, reuse, and share.

Terraform is HashiCorp's infrastructure as code tool. It lets you define resources and infrastructure in human-readable, declarative configuration files, and manages your infrastructure's lifecycle. Using Terraform has several advantages over manually managing your infrastructure:

- Terraform can manage infrastructure on multiple cloud platforms.
- The human-readable configuration language helps you write infrastructure code quickly.
- Terraform's state allows you to track resource changes throughout your deployments.
- You can commit your configurations to version control to safely collaborate on infrastructure.

## Manage any infrastructure

Terraform plugins called providers let Terraform interact with cloud platforms and other services via their application programming interfaces (APIs). HashiCorp and the Terraform community have written over 1,000 providers to manage resources on Amazon Web Services (AWS), Azure, Google Cloud Platform (GCP), Kubernetes, Helm, GitHub, Splunk, and DataDog, just to name a few. Find providers for many of the platforms and services you already use in the [Terraform Registry](https://registry.terraform.io/browse/providers). If you don't find the provider you're looking for, you can write your own.

## Standardize your deployment workflow

Providers define individual units of infrastructure, for example compute instances or private networks, as resources. You can compose resources from different providers into reusable Terraform configurations called modules, and manage them with a consistent language and workflow.

Terraform's configuration language is declarative, meaning that it describes the desired end-state for your infrastructure, in contrast to procedural programming languages that require step-by-step instructions to perform tasks. Terraform providers automatically calculate dependencies between resources to create or destroy them in the correct order.

![[terraform-005.png]]

To deploy infrastructure with Terraform:

- **Scope** - Identify the infrastructure for your project.
- **Author** - Write the configuration for your infrastructure.
- **Initialize** - Install the plugins Terraform needs to manage the infrastructure.
- **Plan** - Preview the changes Terraform will make to match your configuration.
- **Apply** - Make the planned changes.

## Track your infrastructure

Terraform keeps track of your real infrastructure in a state file, which acts as a source of truth for your environment. Terraform uses the state file to determine the changes to make to your infrastructure so that it will match your configuration.

## Collaborate

Terraform allows you to collaborate on your infrastructure with its remote state backends. When you use HCP Terraform (free for up to five users), you can securely share your state with your teammates, provide a stable environment for Terraform to run in, and prevent race conditions when multiple people make configuration changes at once.

You can also connect HCP Terraform to version control systems (VCSs) like GitHub, GitLab, and others, allowing it to automatically propose infrastructure changes when you commit configuration changes to VCS. This lets you manage changes to your infrastructure through version control, as you would with application code.

# Use Cases

HashiCorp Terraform is an infrastructure as code tool that lets you define infrastructure resources in human-readable configuration files that you can version, reuse, and share. You can then use a consistent workflow to safely and efficiently provision and manage your infrastructure throughout its lifecycle.

## Multi-Cloud Deployment

Provisioning infrastructure across multiple clouds increases fault-tolerance, allowing for more graceful recovery from cloud provider outages. However, multi-cloud deployments add complexity because each provider has its own interfaces, tools, and workflows. **Terraform lets you use the same workflow to manage multiple providers and handle cross-cloud dependencies.** This simplifies management and orchestration for large-scale, multi-cloud infrastructures.

### Resources

- Try our [Deploy Federated Multi-Cloud Kubernetes Clusters](https://developer.hashicorp.com/terraform/tutorials/networking/multicloud-kubernetes) tutorial to provision Kubernetes clusters in both Azure and AWS environments, configure Consul federation with mesh gateways across the two clusters, and deploy microservices across the two clusters to verify federation.
- Browse the [Terraform Registry](https://registry.terraform.io/browse/providers) to find thousands of publicly available providers.

## Application Infrastructure Deployment, Scaling, and Monitoring Tools

You can use Terraform to efficiently deploy, release, scale, and monitor infrastructure for multi-tier applications. N-tier application architecture lets you scale application components independently and provides a separation of concerns. An application could consist of a pool of web servers that use a database tier, with additional tiers for API servers, caching servers, and routing meshes. Terraform allows you to manage the resources in each tier together, and automatically handles dependencies between tiers. For example, Terraform will deploy a database tier before provisioning the web servers that depend on it.

### Resources

- Try our [Automate Monitoring with the Terraform Datadog Provider](https://developer.hashicorp.com/terraform/tutorials/applications/datadog-provider) tutorial to deploy a demo Nginx application to a Kubernetes cluster with Helm and install the Datadog agent across the cluster. The Datadog agent reports the cluster health back to your Datadog dashboard.
- Try our [Use Application Load Balancers for Blue-Green and Canary Deployments](https://developer.hashicorp.com/terraform/tutorials/aws/blue-green-canary-tests-deployments) tutorial. You will provision the blue and green environments, add feature toggles to your Terraform configuration to define a list of potential deployment strategies, conduct a canary test, and incrementally promote your green environment.

## Self-Service Clusters

At a large organization, your centralized operations team may get many repetitive infrastructure requests. You can use Terraform to build a "self-serve" infrastructure model that lets product teams manage their own infrastructure independently. You can create and use Terraform modules that codify the standards for deploying and managing services in your organization, allowing teams to efficiently deploy services in compliance with your organization’s practices. Terraform Cloud can also integrate with ticketing systems like ServiceNow to automatically generate new infrastructure requests.

### Resources

- Try the [Use Modules from the Registry](https://developer.hashicorp.com/terraform/tutorials/modules/module-use) tutorial to get started using public modules in your Terraform configuration. Try the [Build and Use a Local Module](https://developer.hashicorp.com/terraform/tutorials/modules/module-create) tutorial on HashiCorp Learn to create a module to manage AWS S3 buckets.
- Follow these [ServiceNow Service Catalog Integration Setup Instructions](https://developer.hashicorp.com/terraform/cloud-docs/integrations/service-now) to connect ServiceNow to Terraform Cloud.

## Policy Compliance and Management

Terraform can help you enforce policies on the types of resources teams can provision and use. Ticket-based review processes are a bottleneck that can slow down development. Instead, you can use Sentinel, a policy-as-code framework, to automatically enforce compliance and governance policies before Terraform makes infrastructure changes. Sentinel is available with the [Terraform Cloud team and governance](https://www.hashicorp.com/products/terraform/pricing) tier.

### Resources

- Try the [Control Costs with Policies](https://developer.hashicorp.com/terraform/tutorials/cloud-get-started/cost-estimation) tutorial on HashiCorp Learn to estimate the cost of infrastructure changes and define policy to limit it.
    
- The [Sentinel documentation](https://developer.hashicorp.com/terraform/docs/cloud/sentinel/index.html) provides more in-depth information and a list of example policies that you can adapt for your use cases.
    

## PaaS Application Setup

Platform as a Service (PaaS) vendors like Heroku allow you to create web applications and attach add-ons, such as databases or email providers. Heroku can elastically scale the number of dynos or workers, but most non-trivial applications need many add-ons and external services. You can use Terraform to codify the setup required for a Heroku application, configure a DNSimple to set a CNAME, and set up Cloudflare as a Content Delivery Network (CDN) for the app. Terraform can quickly and consistently do all of this without a web interface.

### Resources

Try the [Deploy, Manage, and Scale an Application on Heroku](https://developer.hashicorp.com/terraform/tutorials/applications/heroku-provider) tutorial on HashiCorp Learn manage an application’s lifecycle with Terraform.

## Software Defined Networking

Terraform can interact with Software Defined Networks (SDNs) to automatically configure the network according to the needs of the applications running in it. This lets you move from a ticket-based workflow to an automated one, reducing deployment times.

For example, when a service registers with [HashiCorp Consul](https://www.consul.io/), [Consul-Terraform-Sync](https://developer.hashicorp.com/consul/docs/nia) can automatically generate Terraform configuration to expose appropriate ports and adjust network settings for any SDN that has an associated Terraform provider. Network Infrastructure Automation (NIA) allows you to safely approve the changes that your applications require without having to manually translate tickets from developers into the changes you think their applications need.

### Resources

- Try the [Network Infrastructure Automation with Consul-Terraform-Sync Intro](https://developer.hashicorp.com/consul/tutorials/network-infrastructure-automation/consul-terraform-sync-intro) tutorial on HashiCorp Learn to install Consul-Terraform-Sync on a node. You will then configure it to communicate with a Consul datacenter, react to service changes, and execute an example task.
- Try the [Consul-Terraform-Sync and Terraform Enterprise/Cloud Integration](https://developer.hashicorp.com/consul/tutorials/network-infrastructure-automation/consul-terraform-sync-terraform-enterprise) tutorial on HashiCorp Learn to configure Consul-Terraform-Sync to interact with Terraform Enterprise and Terraform Cloud.

## Kubernetes

Kubernetes is an open-source workload scheduler for containerized applications. Terraform lets you both deploy a Kubernetes cluster and manage its resources (e.g., pods, deployments, services, etc.). You can also use the [Kubernetes Operator for Terraform](https://github.com/hashicorp/terraform-k8s) to manage cloud and on-prem infrastructure through a Kubernetes Custom Resource Definition (CRD) and Terraform Cloud.

### Resources

- Try the [Manage Kubernetes Resources via Terraform](https://developer.hashicorp.com/terraform/tutorials/kubernetes/kubernetes-provider) tutorial on HashiCorp Learn. You will use Terraform to schedule and expose a NGINX deployment on a Kubernetes cluster.
- Try the [Deploy Infrastructure with the Terraform Cloud Operator for Kubernetes](https://developer.hashicorp.com/terraform/tutorials/kubernetes/kubernetes-operator) tutorial on HashiCorp Learn. You will configure and deploy the Operator to a Kubernetes cluster and use it to create a Terraform Cloud workspace and provision a message queue for an example application.

## Parallel Environments

You may have staging or QA environments that you use to test new applications before releasing them in production. As the production environment grows larger and more complex, it can be increasingly difficult to maintain an up-to-date environment for each stage of the development process. Terraform lets you rapidly spin up and decommission infrastructure for development, test, QA, and production. Using Terraform to create disposable environments as needed is more cost-efficient than maintaining each one indefinitely.

## Software Demos

You can use Terraform to create, provision, and bootstrap a demo on various cloud providers. This lets end users easily try the software on their own infrastructure and even enables them to adjust parameters like cluster size to more rigorously test tools at any scale.