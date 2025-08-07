Compute refers to the processing power needed to run applications, manage data, and perform calculations. In the cloud, this power is available on-demand. You can access it remotely without owning or maintaining physical hardware. Essentially, _compute in the cloud_ means creating virtual machines with a cloud provider to run applications and tasks over the internet. In the following lessons, you will gain a thorough understanding of Amazon Elastic Compute Cloud (Amazon EC2), a powerful compute service from AWS, as you explore its flexibility, cost-effectiveness, and scalability.

**Amazon Elastic Compute Cloud EC2** is:
* Highly available 
* Cost-effective
* Quick 

With EC2, you only pay for your running instances.

EC2 instances are virtual machines or VMs. 

Multitenancy: Sharing underlying hardware between virtual machines

For EC2, AWS manages the underlying host, the  hypervisor and the isolation from instance to instance. 

In Amazon you can choose the OS: Windows or Linux. You decide which software run in your instance: Internal business app, web apps, databases and third-party software. You have the control about what happens inside of the VM. 

Vertically scaling, you can add or remove compute power (memory and CPU)

You control the networking aspect of Amazon EC2

## Amazon EC2

Amazon EC2 is more flexible, cost-effective, and faster than managing on-premises servers. It offers **on-demand compute** capacity that can be quickly launched, scaled, and terminated, with costs based only on active usage.

The flexibility of Amazon EC2 allows for faster development and deployment of applications. You can launch as many or as few virtual servers as needed and configure security, networking, and storage. You can also scale resources up or down based on usage, such as handling high traffic or compute-heavy tasks.

### Key takeaways : Comparing on-premises and cloud resources

When designing infrastructure for your business, selecting the right resources can significantly affect your efficiency, flexibility, and overall costs. Review the key differences between on-premises and cloud resource management.

#### Challenges of on-premises resources

Imagine that you're responsible for designing your company's infrastructure to support new websites. With traditional on-premises resources, you must purchase hardware upfront, wait for delivery, and handle installation and configuration. This process is time-consuming, costly, and inflexible because you're locked into a specific capacity that might not align with changing demands.

![[aws-005.png]]

#### Benefits of using Cloud Resource

In contrast, with Amazon EC2, you can quickly launch, scale, and stop instances based on your needs without the delays and upfront costs associated with traditional on-premises resources.

![[aws-006.png]]

### How Amazon EC2 works

You’ve learned that AWS manages complex infrastructure, offering on-demand compute capacity that’s available whenever you need it. You can request EC2 instances and have them ready to use within minutes. But how do you actually get started?

- Accessing on-demand compute capacity: With Amazon EC2, you can quickly launch, connect to, and use virtual instances in the cloud. Here's an overview of how the process works.
- Launch an instance: When launching an EC2 instance, you start by selecting an Amazon Machine Image (AMI), which defines the operating system and might include additional software. You also choose an instance type, which determines the underlying hardware resources, such as CPU, memory, and network performance.
- Connect to the instance: You can connect to an EC2 instance in various ways. Applications can interact with services running on the instance over the network.
  
  Users or administrators can connect using SSH for Linux instances or Remote Desktop Protocol (RDP) for Windows instances. Alternatively, AWS services like AWS Systems Manager offer a secure and simplified method for accessing instances.
- Use the instance: After you are connected to the instance, you can begin using it to run commands, install software, add storage, organize files, and perform other tasks.


# Amazon EC2 Instance Type

Amazon EC2 offers a broad range of instance types, each tailored to meet specific use case requirements. These instances come with varying combinations of CPU, memory, storage, and networking capabilities, so you can choose the right mix of resources to optimize performance for your applications.

Each Amazon EC2 instance type is grouped under an instance family. 

**General purpose**

General purpose instances provide a balanced mix of compute, memory, and networking resources. They are ideal for diverse workloads, like web services, code repositories, and when workload performance is uncertain.

**Compute optimized** 

Compute optimized instances are ideal for compute-intensive tasks, such as gaming servers, high performance computing (HPC), machine learning, and scientific modeling.

**Memory optimized**

Memory optimized instances are used for memory-intensive tasks like processing large datasets, data analytics, and databases. They provide fast performance for memory-heavy workloads.

**Accelerated computing**

Accelerated computing instances use hardware accelerators, like graphics processing units (GPUs), to efficiently handle tasks, such as floating-point calculations, graphics processing, and machine learning.

**Storage optimized**

Storage optimized instances are designed for workloads that require high performance for locally stored data, such as large databases, data warehousing, and I/O-intensive applications.

Instance types are named based on their _instance family_ and _instance size_. For information about these naming conventions, refer to [Amazon EC2 instance type naming conventions(opens in a new tab)](https://docs.aws.amazon.com/ec2/latest/instancetypes/instance-type-names.html).

# How to provision AWS Resources

In AWS, tasks such as launching an EC2 instance, stopping an instance, or modifying instance settings are done through API requests. APIs provide predefined methods to interact with, manage, and configure AWS resources efficiently.

API: Application programming interface. APIs are the way to interact AWS resources

Interacting with AWS services: AWS Management console, AWS Command Line Interface (CLI) and AWS Software Developer Kit SDK

![[aws-007.png]]

**AWS Management Console**

* Se up test environments
* View AWS bills
* View monitoring
* Work with non-technical resources

The AWS Management Console is a web interface for managing AWS services, offering quick access to services, search functionality, and simplified workflows. With the mobile app, you monitor resources, view alarms, and check billing, supporting multiple logged-in identities at once.

**Good for**: Users who prefer a visual, easy-to-use interface for managing and configuring AWS services

**AWS  CLI**

Make API calls using the terminal on your machine. Can user Amazon cloud shell.

With the AWS CLI, you manage multiple AWS services directly from the command line across Windows, macOS, and Linux. You can automate tasks through scripts, such as launching EC2 instances.

**Good for**: Advanced users and developers who need to automate tasks, script actions, and manage AWS resources efficiently from the command line

**AWS SDK**

Interact with AWS resources though various programming languages

The AWS SDK simplifies integrating AWS services into your applications by providing APIs for various programming languages. AWS offers documentation and sample code for languages like C++, Java, and .NET to help you get started.

**Good for**: Developers looking to integrate AWS services into their applications using language-specific APIs

### Compute and shared responsibility

The AWS Shared Responsibility Model outlines the division of duties between the customer and AWS. AWS handles the security _of_ the cloud (hardware and infrastructure), whereas the customer is responsible for security _in_ the cloud (applications, data, and access control).

An _unmanaged_ service like Amazon EC2 requires you to perform all of the necessary security configuration and management tasks. When you deploy an EC2 instance, you are responsible for configuring security, managing the guest operating system (OS), applying updates, and setting up firewalls (security groups). You will learn more about managed and unmanaged services later.

![[aws-008.png]]

## Amazon Machine Images

**AMI components**

An AMI includes the operating system, storage setup, architecture type, permissions for launching, and any extra software that is already installed. You can use one AMI to launch several EC2 instances that all have the same setup.

![[aws-009.png]]

**Three ways to use AMIs**

AMIs can be used in three ways. First, you can create your own by building a custom AMI with specific configurations and software tailored to your needs. Second, you can use pre-configured AWS AMIs, which are set up for common operating systems and software. Lastly, you can purchase AMIs from the AWS Marketplace, where third-party vendors offer specialized software designed for specific use cases.

**AMI repeatability**

AMIs provide repeatability through a consistent environment for every new instance. Because configurations are identical and deployments automated, development and testing environments are consistent. This helps when scaling, reduces errors, and streamlines managing large-scale environments.

![[aws-010.png]]

# Amazon EC2 pricing

By understanding the different Amazon EC2 pricing options, you can make more informed decisions and optimize your costs based on your specific usage needs. 

**On-Demand Instances**

Pay only for the compute capacity you consume with no upfront payments or long-term commitments required.

**Savings plans**

Save up to 72 percent across a variety of instance types and services by committing to a consistent usage level for 1 or 3 years.

**Reserved Instances**

Get a savings of up to 75 percent by committing to a 1-year or 3-year term for **predictable workloads** using specific instance families and AWS Regions.

**Dedicated hosts**

Reserve an entire physical server for your exclusive use. This option offers full control and is ideal for workloads with strict security or licensing needs.

**Spot  Instances**

Bid on spare compute capacity at up to 90 percent off the On-Demand price, with the flexibility to be interrupted when AWS reclaims the instance.

**Dedicated Instances**

Pay for instances running on hardware dedicated solely to your account. This option provides isolation from other AWS customers.

## Dedicated Instances

Dedicated Hosts provide exclusive use of physical servers, offering full control over instance placement and resource allocation. This makes them ideal for security- or compliance-driven workloads. But what if you don’t need that level of control?

You could use Dedicated Instances, which offer physical isolation from other AWS accounts while still benefiting from the flexibility and cost savings of shared infrastructure.

The key difference is that Dedicated Instances provide isolation without you choosing which physical server they run on. Dedicated Hosts give you an entire physical server for exclusive use, providing complete control over instance placement and resource allocation.

Ultimately, the right choice depends on your specific workload requirements and the level of control you need over your infrastructure.

![[aws-011.png]]
Dedicated Hosts offer exclusive use of a server with full control, whereas Dedicated Instances provide isolation without server control.

### More about cost optimization 

To optimize costs and resource allocation, AWS offers a range of pricing options including Savings Plans, Amazon EC2 Capacity Reservations, and Reserved Instances (RIs). Each of these is tailored to meet different workload and capacity needs.

**Savings plans**

**Good for**: Predictable workloads

Savings Plans offer discounts compared to On-Demand rates in exchange for a commitment to use a specified amount of compute power (measured per hour) over a one-year or three-year period. They provide flexible pricing for Amazon EC2, AWS Fargate, AWS Lambda, and Amazon SageMaker AI usage, regardless of instance type or AWS Region. Payment options include All upfront, Partial upfront, or No upfront.

For more information, refer to [What are Savings Plans?](https://docs.aws.amazon.com/savingsplans/latest/userguide/what-is-savings-plans.html)

**Capacity Reservations**

**Good for**: Critical workloads with strict capacity requirements

With Amazon EC2 Capacity Reservations, you reserve compute capacity in a specific Availability Zone for critical workloads. Reservations are charged at the On-Demand rate, whether used or not. You only pay for the instances you run. This is ideal for strict capacity requirements for current or future business-critical workloads.

For more information, refer to [Reserve compute capacity with EC2 On-Demand Capacity Reservations(opens in a new tab)](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/ec2-capacity-reservations.html).

**Reserved Instance Flexibility**

**Good for**: Steady-state workloads with predictable usage

RIs offer up to 75 percent savings over On-Demand pricing by applying discounts across instance sizes and multiple Availability Zones within a Region. When you purchase a Reserved Instance (RI), AWS automatically applies the discount to other instance sizes within the same family based on the instance size footprint. It also applies the discount across multiple Availability Zones for enhanced resource distribution and fault tolerance.

For more information, refer to [How Reserved Instance discounts are applied](https://docs.aws.amazon.com/AWSEC2/latest/UserGuide/apply_ri.html)

# Auto Scaling and Load Balancing 

Scalability is about a system’s potential to grow over time, whereas elasticity is about the dynamic, on-demand adjustment of resources.

**Scalability**

Scalability refers to the ability of a system to handle an increased load by adding resources. You can scale up by adding more power to existing machines, or you can scale out by adding more machines. Scalability focuses on long-term capacity planning to make sure that the system can grow and accommodate more users or workloads as needed.

![[aws-012.png]]

**Elasticity**

Elasticity is the ability to automatically scale resources up or down in response to real-time demand. A system can then rapidly adjust its resources, scaling out during periods of high demand and scaling in when the demand decreases. Elasticity provides cost efficiency and optimal resource usage at any given moment.

![[aws-013.png]]

### Amazon EC2 Auto Scaling

Amazon EC2 Auto Scaling automatically adjusts the number of EC2 instances based on changes in application demand, providing better availability. It offers two approaches. _Dynamic scaling_ adjusts in real time to fluctuations in demand. _Predictive scaling_ preemptively schedules the right number of instances based on anticipated demand.

With EC2 Auto Scaling, you maintain the desired amount of compute capacity for your application by dynamically adjusting the number of EC2 instances based on demand. You can create Auto Scaling groups, which are collections of EC2 instances that can scale in or out to meet your application’s needs.

An Auto Scaling group is configured with the following three key settings.

**Minimum capacity**

The _minimum capacity_ defines the least number of EC2 instances required to keep the application running. This makes sure that the system never scales below this threshold. It's the number of EC2 instances that launch immediately after you have created the Auto Scaling group.

![[aws-014.png]]

**Desired Capacity**

The _desired capacity_ is the ideal number of instances needed to handle the current workload, which Auto Scaling aims to maintain. If you do not specify the desired number of EC2 instances in an Auto Scaling group, the desired capacity defaults to your minimum capacity.

![[aws-015.png]]

**Maximum capacity**

The _maximum capacity_ sets an upper limit on the number of instances that can be launched, preventing over-scaling and controlling costs. For example, you might configure the Auto Scaling group to scale out in response to increased demand.

In this example, a maximum of 12 EC2 instances can be launched. Amazon EC2 Auto Scaling will scale between the minimum and maximum number of instances.

![[aws-016.png]]

Because Amazon EC2 Auto Scaling uses EC2 instances, you pay for only the instances you use, when you use them. This gives you a cost-effective architecture that provides the best customer experience while reducing expenses.

# Directing Traffic with Elastic Load Balancing

## Elastic Load Balancing

Elastic Load Balancing (ELB) automatically distributes incoming application traffic across multiple resources, such as EC2 instances, to optimize performance and reliability. A load balancer serves as the single point of contact for all incoming web traffic to an Auto Scaling group. As the number of EC2 instances fluctuates in response to traffic demands, incoming requests are first directed to the load balancer. From there, the traffic is distributed evenly across the available instances.

Although ELB and Amazon EC2 Auto Scaling are distinct services, they work in tandem to enhance application performance and ensure high availability. Together, they enable applications running on Amazon EC2 to scale effectively while maintaining consistent performance.

### ELB benefits

**Efficient traffic distribution**

ELB evenly distributes traffic across EC2 instances, preventing overload on any single instance and optimizing resource utilization.

**Automatic scaling**

ELB scales with traffic and automatically adjusts to changes in demand for a seamless operation as backend instances are added or removed.

**Simplified management**

ELB decouples front-end and backend tiers and reduces manual synchronization. It also handles maintenance, updates, and failover to ease operational overhead.

### Routing methods

To optimize traffic distribution, ELB uses several routing methods: Round Robin, Least Connections, IP Hash, and Least Response Time. These routing strategies work together for efficient traffic management and optimal application performance.

![[aws-017.png]]

### Example

**Initial setup**

**Low-demand period**: At the beginning of the day, only a few patients are accessing the system to book appointments or view medical records. The existing web servers are sufficient to handle the low traffic. This matches the demand, with no need for additional resources at this point.

![[aws-018.png]]

**Scaling up**

**High-demand period**: As the day progresses, especially during peak hours, such as early mornings or just before the weekend, more patients access the portal to book appointments, view test results, or contact medical professionals. To handle this surge in demand, the healthcare system automatically scales up the number of servers to help ensure that the system remains responsive and available for all users.

![[aws-019.png]]

**Load Balancing**

A load balancer directs the incoming traffic to different web servers based on their current load. For instance, if one server starts receiving too many requests, the load balancer will route new requests to a less busy server. This makes sure that no single server becomes overwhelmed. The traffic is evenly distributed across available EC2 instances.

![[aws-020.png]]

# Messaging and queuing 

