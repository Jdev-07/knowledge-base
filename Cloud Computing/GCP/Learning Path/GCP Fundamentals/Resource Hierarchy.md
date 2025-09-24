## Google Cloud Resource Hierarchy 

### Resource Hierarchy

* All resources (except root/organization) have one parent. 
* At the lowest level are located the services resources. 
* The first object/resource for holding related resources are the projects.
* A complete resource hierarchy can contain an organization, folders, projects and service resources. 
### Projects

- All users, even free trial and free tier users, can create projects. 
- Project resources can be at the top if created by free trial and free tiers users. However, projects can be moved into a organization. 
- Google Workspace and Cloud identity customers can create organization and projects

### Organization 

- The organization is the root node if exits, all resources that belong to a company are grouped under the organization resource by default.
- One organization resource per Google Workspace or Cloud Identity account. 

### Folder

- Folders is other resource for grouping resources, which is located between a organization and projects
- For creating folder resources, one organization is required. 

### Policy inheritance 

- IAM roles and organization policies flow down the hierarchy 

## Organization Resource

- The organization resource actually represents an organization.
- This resource is the root node if exits.
- Folder and project resources are located under an organization.
- If policies are applied at organization level, all resources will inherit them.
- To get all resource hierarchy features, an organization is required.
- When a Google Workspace account creates project resources, an organization is automatically created. 
- All accounts associated to an organization, can only create resources associated to that organization. However, if a managed user with enough permissions is creating a new project, can specify other organization.

### Link with Google Workspace or Cloud Identity accounts

- Google Workspace or Cloud Identity account represents a company.
- A organization resource provide identity management, lifecycle management, ownership and recovery mechanisms. 
- By default a Google Workspace super admin has the ability to assign IAM roles. 
- The super admin main's duty is to assign the Organization Administrator role to the appropriate users.

Note: Org. Admin vs Workspace Super Admin

- **Org Admin (GCP)** = **Cloud resources manager** (who can create/secure/manage projects and infrastructure).
- **Workspace Super Admin** = **Identity & productivity manager** (who can create users, reset passwords, control email, and assign licenses).

### Benefits of the organization resource

- Resources belong to the organization (company) instead of individuals. So, resources are not deleted when an employees leaves the company. 
- Organization Administrators can manage all resources in the company. 
- Granting roles is easier because the roles assigned at organization level are inherited by all resources (projects and folders) under the organization. 

Also, an organization resource exposed by the Cloud Resource Manager API consist of the following:

- An organization resource ID, which is a unique identifier for an organization.
- A display name, which is generated from the primary domain name in Google Workspace or Cloud Identity.
- The creation time of the organization resource.
- The last modified time of the organization resource.
- The owner of the organization resource. The owner is specified when creating the organization resource. It cannot be changed once it is set. It is the Google Workspace customer ID that is specified in the Directory API

The following code snippet shows the structure of an organization resource:

```JSON
{
  "creationTime": "2020-01-07T21:59:43.314Z",
  "displayName": "my-organization",
  "lifecycleState": "ACTIVE",
  "name": "organizations/34739118321",
  "owner": {
    "directoryCustomerId": "C012ba234"
  }
}
```

## Folder Resource 

- Folder resources are other optional resource for holding related resources and provide isolation between projects. 
- As folders can contain other folders and projects, the org. structure can be more granular. 
- You can view the folder resources from google cloud console if they exist and you have the right permissions.
- The following code snippet show the structure:

```JSON
{
  "createTime": "2030-01-07T21:59:43.314Z",
  "displayName": "Engineering",
  "lifecycleState": "ACTIVE",
  "name": "folders/634792535758",
  "parent": "organizations/34739118321"
}
```

## Project Resource

- Organization and folder can contain multiple project resources
- A project is required for using google cloud 
- The project is the base level entity
- A project is necessary for creating, enabling, and using all Google Cloud Services,  managing APIs, enabling billing, adding and removing collaborators and managing permissions. 
- Project resource consist of two identifiers, project resource ID and project resource number.  one mutable display name, lifecycle state, collection of labels and the time when project resource was creating. 

```JSON
{
  "createTime": "2020-01-07T21:59:43.314Z",
  "lifecycleState": "ACTIVE",
  "name": "my-project",
  "parent": {
    "id": "634792535758",
    "type": "folder"
  },
  "projectId": "my-project",
  "labels": {
     "my-label": "prod"
  },
  "projectNumber": "464036093014"
}
```

- To interact with most Google Cloud resources you must provide any of the two project identifiers (`projectId` or `projectNumber`)
- A project resource ID is the customized name you chose when create the project resource. 
- A project resource is required for activating some API, it can a new one or existing one. 
- The project number is automatically  created by google cloud.

## Allow and deny policy inheritance

- Google Cloud offers IAM roles, which lets you assign granular access to specific resources. 
- IAM lets define who has access to which resources by setting deny or allow policies
- We can assign roles on organization resources, folder resources and projects resources. Also on some service resources as well.
- The organization, folder and project resources act as a policy inheritance point, that means resource inherit policies of the parent resource.

	![[gcp-001.png]]