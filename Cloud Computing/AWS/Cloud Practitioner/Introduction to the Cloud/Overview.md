AWS is world's most comprehensive and broadly adopted cloud and millions of customer use AWS to be more agile, lower cost and innovate faster.

### AWS offers services like:

- Compute
- Generative AI 
- Database and  storage
- Content delivery
- Specialized services

### Main concepts 

- client-server model 
- You pay for what you use. You do not prepay for anything. Resources can be provisioned and de-provisioned

## What is Cloud Computing?

On-demand delivery of IT resources over the internet with pay-as-you-go pricing

- _On-demand delivery_ means that customers can access computing resources, such as storage or compute power, within seconds and as needed. Users can scale their resource usage up or down based on current requirements without lengthy provisioning processes.
- The _of IT resources_ aspect highlights the wide array of information technology assets in the cloud-computing space. These resources include servers, storage solutions, databases, networking components, artificial intelligence and machine learning (AI/ML) tools, and more. Customers can use these resources to build, deploy, and manage applications and services through the cloud infrastructure.
- _Over the internet_ signifies that cloud computing delivers IT resources through internet connectivity. This means that users access and use these resources through web-based services rather than maintaining local hardware or software. The internet acts as the conduit, which provides remote access to compute power, storage, and applications from anywhere in the world.
- Flexible pricing is a fundamental economic aspect of cloud computing. Users pay only for the resources they actually consume, rather than committing to fixed, long-term contracts. This usage-based pricing model offers cost efficiency and financial flexibility.

### Cloud deployment models

You can deploy cloud resources in multiple ways: cloud, on-premises, and hybrid. Each type offers unique benefits and considerations, and exploring these options can help you make informed decisions about your cloud strategy. To learn more about cloud deployment types, choose each of the following flashcards.

#### Cloud-based deployments

In a cloud-based deployment model, you have the flexibility to migrate your existing resources to the cloud, design and build new applications within the cloud environment, or use a combination of both.

For instance, a company might migrate data resources to the cloud, then develop an application comprised of virtual servers, databases, and networking components entirely hosted in the cloud.

#### On-premises deployments

Deploying resources on premises using virtualization and resource management tools does not provide many of the benefits of cloud computing. However, it is sometimes sought for its ability to provide dedicated resources and low latency.

In most cases this deployment model is the same as legacy IT infrastructure while using application management and virtualization technologies to try increasing resource utilization.

#### Hybrid deployment

In a hybrid deployment, cloud-based resources and on-premises infrastructure work together. This approach is ideal for situations where legacy applications must remain on premises due to maintenance preferences or regulatory requirements.

For instance, a company might choose to retain certain regulated legacy applications on-premises while using cloud services for advanced data processing and analytics.

Multi-cloud deployments can also be considered _hybrid deployments_.

## Benefits of the AWS cloud

- Trade fixed expense for variable expense. In AWS the bill will be variable from month to month as you consume. No need to come up with a big investment. 
- Benefit from massive economies of scale
- Stop guessing capacity. You do not to guess capacity. 
- Increase speed and agility. You have more bandwidth
- Stop spending money running and maintaining data centers. 
- Go global in minutes 

### Trade fixed expense for variable expense 

By using the AWS Cloud, businesses can transition from fixed investments to variable costs. With variable costs, customer expenses are better aligned with actual usage, thus creating more financial flexibility.

![[aws-001.png]]
### Benefit from massive economies of scale

Like buying a product in bulk can result in lower prices per unit, the vast global infrastructure of AWS can result in lower costs for customers. This means that AWS can be used by many organizations, from small startups to major corporations. Businesses big and small can access advanced technologies that were previously only accessible to large enterprises.

![[aws-002.png]]
### Stop guessing capacity

Customers can dynamically scale AWS Cloud resources up or down based on real-time demand. This means businesses can achieve optimal performance without provisioning more or less infrastructure than they need.

![[aws-003.png]]

### Increase speed and agility

With the cloud, businesses can rapidly deploy applications and services, accelerating time to market and facilitating quicker responses to changing business needs and market conditions.

### Stop spending money to run and maintain data center

The AWS Cloud eliminates the need for businesses to invest in physical data centers. This means customers aren't required to spend time and money on utilities and ongoing maintenance. With AWS taking care of the physical infrastructure of the cloud, customer resources can be reallocated to more strategic initiatives.

### Go global in minutes

Businesses don't need to set up their own infrastructure to expand internationally. AWS provides a robust global infrastructure that customers can use to deploy applications and services across multiple areas in minutes.

## Introduction to AWS Global Infrastructure


**High availability** is all about making sure your applications stay accessible with minimal downtime. 
**Fault tolerance** takes it a step further by designing a system to continue to operate even if multiple components fail. 

With each AWS region, there are availability zones (AZs). There are three or more AZs within a Region, for redundancy. 

If one region is experiencing outages for any reason, the operations can failover to another region. 

### AWS Regions and availability zones 

#### AWS Regions

AWS Regions are physical locations around the world that contain groups of data centers. These groups of data centers are called Availability Zones. Each AWS Region consists of a minimum of three physically separate Availability Zones within a geographic area.

#### Availability zones

An Availability Zone consists of one or more data centers with redundant power, networking, and connectivity. Regions and Availability Zones are designed to provide **low-latency, fault-tolerant access to services for users within a given area.**

### Achieving high availability with AWS Global Infrastructure

AWS infrastructure is designed with high availability and fault tolerance in mind. Availability Zones (AZs) are configured as isolated resources, and they are each equipped with independent power, networking, and connectivity.

It's recommended to distribute your resources across multiple AZs. That way, if one AZ encounters an outage, your business applications will continue to operate without interruption. With this approach of **redundancy and resource isolatio**n, AWS customers can achieve the benefits of high availability and fault tolerance.

## Shared responsibility

The AWS Shared Responsibility Model is a concept designed to help AWS and customers work together to create a secure, functional cloud environment. 

AWS in responsible for the security of the cloud. Customer in responsible for security in the cloud.

![[aws-004.png]]

### Components of the AWS Shared Responsibility


**Customer responsibility:** Customers are responsible for managing security requirements for their data, including which data they store on AWS and who has access to that data. Customers also control how access to the data is granted, managed, and revoked.

Additionally, customers are responsible for client-side encryption.

**Customer or AWS responsibility:** Depending on the service used, responsibilities might shift between the customer and AWS. Components such as server-side encryption, network traffic protection, platform and application management, and OS, network, and firewall configuration vary by service in terms of who is responsible for these items. As you learn more about different types of services, you will see specific examples of how these elements are divided between the customer and AWS.

**AWS Responsibility:** AWS is responsible for protecting the infrastructure that runs all of the services offered in the AWS Cloud. This infrastructure is composed of the hardware, software, networking, and facilities that run AWS Cloud services.


Documentation reference:

https://aws.amazon.com/what-is-cloud-computing/?nc1=f_cc

https://aws.amazon.com/compliance/shared-responsibility-model/

https://aws.amazon.com/about-aws/global-infrastructure/regions_az/

[[Compute in the Cloud]]