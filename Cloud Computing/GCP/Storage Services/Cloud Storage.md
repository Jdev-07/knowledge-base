## Overview

Cloud Storage is a  service for storing `objects` in Google Cloud. An `object` is an immutable piece of data of any format. These objects are stored in containers called Buckets. All buckets are associated with a project. 

Here's how the Cloud Storage structure can apply to a real-world case:

- **Organization**: Your company, called Example Inc., creates a Google Cloud organization called `exampleinc.org`.
    
- **Project**: Example Inc. is building several applications, and each one is associated with a project. Each project has its own set of Cloud Storage APIs, as well as other resources.
    
- **Bucket**: Each project can contain multiple buckets, which are containers to store your objects. For example, you might create a `photos` bucket for all the image files your app generates and a separate `videos` bucket.
    
- **Object**: Each bucket can contain essentially unlimited individual objects, such as an image called `puppy.png`.
    
- **Hierarchical namespace enabled buckets**: Buckets can have [hierarchical namespace](https://cloud.google.com/storage/docs/hns-overview) enabled. Buckets with hierarchical namespace enabled can store your data in a logical file system structure. The folder management operations provide reliability and management capabilities, including creating, deleting, listing, and renaming folders. Hierarchical namespace is beneficial for data-intensive tasks like analytics, AI, and ML workloads as they offer up to 8 times higher initial QPS limits for reading and writing objects compared to buckets without hierarchical namespace enabled.
    
- **Managed folder**: Each bucket can also contain multiple [managed folders](https://cloud.google.com/storage/docs/managed-folders), which grant additional access beyond the access granted to the overall bucket. This additional access applies to objects that have a prefix matching the managed folder name. For example, you might create an `animals/` managed folder, which gives designated users additional access to objects such as `animals/puppy.png` and `animals/kitten.png`.


### Basic Tools

There are some ways to interact with Cloud Storage:

- Console
- Google Cloud CLI
- Client Libraries 
- REST APIs
- Terraform
- gRPC
- Cloud Storage FUSE

#### Securing your data

Once you upload objects to Cloud Storage, you have fine-grained control over how you secure and share your data.

-  Identity and Access Management: Control who can access to your resources
	
- Data encryption: cloud storage by default encrypts your data in the server side, but you can implement data encryption.
	
- Authentication 
	
- Soft delete: prevent loss of data against accidental or malicious deletion by detaining recently  deleted objects.
	
- Object versioning
	
- Bucket IP filtering
	
- Bucket Lock

## Buckets

`Buckets` are containers that holds our data as objects. We can se buckets to organize our data and control access, but we cannot nest buckets.

There is no limit to number of buckets we can have, however, there is a limit to the rate to create or delete buckets. The buckets need to have a globally unique name, and its name cannot be changed once created. However, you can create a new bucket and move the content to the new bucket. 

### Access data in buckets by using folders or directories

Although cloud storage stores unstructured data in form of objects, it lets you access and manage your data using folders or directories

- **Hierarchical  namespaces**: When create buckets you can enable hierarchical namespaces for the bucket, which lets you to use folders to store your objects in a file system manner. Organizing your objects into folders makes it easier to run operation on large scale of data, improving performance, consistency, and ease of management.
- **Cloud Storage  FUSE**: This a FUSE adapter that lets you mount and access critical buckets as local file systems, so applications can read and write objects in  your buckets using standard file system semantics. 

### Storage Classes

A storage class is a piece of metadata being used by every object. The storage class set for an object will affect the availability and pricing model.  

Also, when you create a bucket, you can specify a default storage class for the bucket, then, all new objects being added will inherit the storage class unless explicitly set otherwise. 

#### Available storage classes

**Standard Storage**

This class is the best for frequently accessed data, as well as data that is stored for a brief periods of time. 

- **In a single region:** Best when your data and compute resources (GKE, Compute Engine) are in the _same region_. This gives highest performance and can reduce network costs.
    
- **In a dual-region:** Still provides strong performance when accessing services in either of the paired regions, **plus higher availability** due to geographic separation.
    
- **In a multi-region:** Ideal for **global access**, serving websites, streaming content, interactive apps, mobile or gaming workloads that need low-latency access worldwide.

**Nearline Storage**

This class is low-cost, highly durable storage service for infrequently accessed data. Nearline storage has a minimum storage duration of 30 days, and costs for data access are acceptable.

This class works for data you plan to read or modify on average once per month or less. 

**Coldline Storage**

Coldline storage is very-low-cost, highly durable storage service for storing infrequently accessed data. This class has a minimum storage duration of 90-days, but higher costs for data access, although they are acceptable.

Coldline storage is ideal for data you expect to read or modify at most once per quarter. Note that although Coldline storage can be used for data kept solely for backup or archiving purposes, Archive storage is usually a better option.

**Archive Storage**

Archive storage class is the lowest-cost, highly durable storage service for data archiving, online backup and disaster recovery. Unlike "coldest" storage service offered by other cloud providers, the data is available  is milliseconds, not hours or days. 

Archive storage has higher costs for data access and operations, as well as a 365-day minimum storage duration. This class is the best if you plan to manage the data less than once a year. 