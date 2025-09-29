A Compute Engine Instance can be either a Virtual Machine (VM ) or a  Bare Metal instance hosted in Google's Infrastructure.  You can create an instance or a managed instance group.

A Compute Engine instance can be created via Google Cloud console. the gcloud CLI or Compute Engine API. 

The terms Compute Engine instance, compute instance or instance are synonymous. There are two types of instances.

- If name of the instance ends in "-metal", is a bare metal instance. 
- Otherwise, an instance is a VM. The terms virtual machine instance, VM instance and VM can be used interchangeably 

Compute instance can run public images (Linux and Windows) that google provides.
Compute instances can also run custom images that you can create or import from your existing systems.
Can also deploy Docker Containers 
You can set the properties for your instances, by using predefined machine types or creating your owns. 

### Instances and projects

- A project can have multiple compute instances and each instance belong to a single project. 
- When creating a compute instance you specify the zone, the OS and machine type.
- When you delete a compute instance, it is removed from the project.

### Instances and storage options

- A compute instance is created with a small disk that contains the OS.
- You can add more disks to the instance when creating and even when running.

### Instances and Networks

Each network interface is associated to a subnet of a unique VPC. 

### Instances and Containers

Compute instances support declarative method for launching your apps using containers.
When creating an instance or an instance template, you can provide a Docker image name and launch the configuration 

### Tools to manage instances

- To create an instance can use the Google Console, gcloud cli and REST API.
- Can connect to the instance using SSH or RDP.

### Managing access to your instances

#### Linux instances

- Managing instance access using OS login. 
- Manage your SSH keys in project or instance metadata. 
- Connecting using the Google Cloud CLI or SSH from the console.

#### Windows Instances

- Generate credentials for windows instances

