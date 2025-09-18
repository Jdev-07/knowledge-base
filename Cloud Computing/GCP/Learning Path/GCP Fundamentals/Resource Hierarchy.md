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

#### Link with Google Workspace or Cloud Identity accounts

- Google Workspace or Cloud Identity account represents a company.
- A organization resource provide identity management, lifecycle management, ownership and recovery mechanisms. 
- By default a Google Workspace super admin has the ability to assign IAM roles. 
- The super admin main's duty is to assign the Organization Administrator role to the appropriate users.

Note: Org. Admin vs Workspace Super Admin

- **Org Admin (GCP)** = **Cloud resources manager** (who can create/secure/manage projects and infrastructure).
- **Workspace Super Admin** = **Identity & productivity manager** (who can create users, reset passwords, control email, and assign licenses).

#### Benefits of the organization resource

- Resources belong to the organization (company) instead of individuals. So, resources are not deleted when an employees leaves the company. 
- Organization Administrators can manage all resources in the company. 
- Granting roles is easier because the roles assigned at organization level are inherited by all resources (projects and folders) under the organization. 