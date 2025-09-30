Cloud Storage is a service for storing objects in Google Cloud. Can store data of any format in containers called buckets. 

All buckets are associated with a project and can group projects under a organization. 

### Google Cloud Hierarchy 

- **Organization**: You have a company and creates a Google Cloud organization called example.org
- **Project**: The company is building several apps, and each app is associated with a project. Each project has its own set of Cloud Storage APIs, as well as other resources. 
- **Bucket**: Each project can contain multiple buckets, where you store the objects. An example can be that you create a bucket named `profile_pic` for the users' profile in your app.
- **Object**: Essentially each bucket contain an unlimited number of objects. 
- **Managed folder**: Each bucket can also contain multiple managed folders, which grant additional access beyond granted to the overall bucket. These managed folders basically provide granularity. Instead of store directly into the bucket, can create a managed folder named animals/ and store animals/golden.png 
- Hierarchical namespace enabled buckets:  Buckets can have hierarchical namespace enabled. Buckets with hierarchical namespace enabled can store your data in a logical file system structure.

### Basic tools for Cloud Storage

- Console: The Google Cloud console provides a visual interface for interacting with the data.
- Google Cloud CLI: gcloud cli allows you to interact with  Cloud Storage via terminal using the gcloud storage commands
- Client Libraries: Cloud Storage client libraries allow you to manage your data using a language
- Rest APIs: Can manage the data using JSON or XML API.
- Terraform: You can use terraform to provision infrastructure for cloud storage.
- Cloud Storage FUSE: This tool lets you mount Cloud Storage buckets to your local file systems. This enables your applications to read from a bucket or write to bucket by suing standard file system semantics. 
- gRPC: gRPC lets you interact with Cloud Storage.  gRPC is a high performance, open source universal RPC framework developed by Google that you can use to define your services using Protocol Buffers.

### Securing data

There are some ways to maintain secure the data once uploaded to buckets. 

- IAM: You can control who has access to resources in your Google Cloud project.
- Data encryption: Google cloud uses server-side encryption to encrypt data by default.
- Authentication: Ensure that everyone who accesses your data has proper credentials.
- Bucket lock: Define how long object in buckets can be retained with a retention policy. 
- Soft delete: prevent permanent loss of data against accidental or malicious deletion by retaining recently deleted object sand buckets 
- Objects versioning: when a live version of an object is replaced or deleted, it can be retained as a noncurrent version if you enable Object Versioning.
- Bucket IP filtering: You can restrict access to a bucket based on the source IP of the request. 

#### Resource names

Each resource has a unique name that identifies it, much like a filename. Buckets have a resource name in the form of `projects/_/buckets/BUCKET_NAME, where BUCKET_NAME` is the ID of the bucket. Objects have a resource name in the form of `projects/_/buckets/BUCKET_NAME/objects/OBJECT_NAME`, where OBJECT_NAME is the ID of the object.

A #NUMBER appended to the end of the resource name indicates a specific generation of the object. #0 is a special identifier for the most recent version of an object. #0 is useful to add when the name of the object ends in a string that would otherwise be interpreted as a generation number.