Google Cloud resources are organized hierarchically. All resources except for the highest resource in a hierarchy have exactly one parent. At the lowest level, service resources are the fundamental components that make up all Google Cloud services.

All users, including free trial users, free tier users, and Google Workspace and Cloud Identity customers, can create project resources.

Project resources can be the top of their hierarchy, but only if created by a free trial user or free tier user. Google Workspace and Cloud Identity customers have access to additional features of the Google Cloud resource hierarchy, such as organization and folder resources.

Project resources at the top of their hierarchy do not have parent resources, but they can be migrated into an organization resource once it has been created for the domain.

Google Workspace and Cloud Identity customers can create organization resources. Each Google Workspace or Cloud Identity account is associated with one organization resource. When an organization resource exists, it is the top of the Google Cloud resource hierarchy, and all resources that belong to an organization are grouped under the organization resource. This provides central visibility and control over every resource that belongs to an organization resource.

Folder resources are an additional, optional grouping mechanism between organization resources and project resources. An organization resource is required as a prerequisite to use folders. Folder resources and their child project resources are mapped under the organization resource.

The Google Cloud resource hierarchy, especially in its most complete form which includes an organization resource and folder resources, allows companies to map their organization resource onto Google Cloud and provides logical attachment points for access management policies (IAM) and organization policies. Allow, deny, and organization policies are inherited through the hierarchy, and the effective policy for each resource in the hierarchy is the result of policies directly applied on the resource and policies inherited from its ancestors.

![[gcp-001.png]]

## The organization resource

The organization resource represents an organization and is the root node in the Google Cloud resource hierarchy when present. The organization resource is the hierarchical ancestor of folder and project resources. The allow and deny policies applied on the organization resource apply throughout the hierarchy on all resources in the organization.

Google Cloud users are not required to have an organization resource, but some features of Resource Manager will not be usable without one. The organization resource is closely associated with a Google Workspace or Cloud Identity account. When a user with a Google Workspace or Cloud Identity account creates a Google Cloud project resource, an organization resource is automatically provisioned for them.

A Google Workspace or Cloud Identity account can have exactly one organization resource provisioned with it. Once an organization resource is created for a domain, all new Google Cloud project resources created by members of the account domain will by default belong to the organization resource. When a managed user creates a project resource, the requirement is that it must be in _some_ organization resource. If a user specifies an organization resource and they have the right permissions, the project is assigned to that organization. Otherwise, it will default to the organization resource the user is associated with. It is impossible for accounts associated with an organization resource to create project resources that aren't associated with an organization resource.

### Link with Google Workspace or Cloud Identity accounts

The Google Workspace or Cloud Identity account represents a company and is a prerequisite to have access to the organization resource. In the Google Cloud context, it provides identity management, recovery mechanism, ownership and lifecycle management. The picture below shows the link between the Google Workspace account, Cloud Identity, and the Google Cloud resource hierarchy.

![[gcp-002.png]]

The Google Workspace super admin is the individual responsible for domain ownership verification and the contact in cases of recovery. For this reason, the Google Workspace super admin is granted the ability to assign IAM roles by default. The Google Workspace super admin's main duty with respect to Google Cloud is to assign the Organization Administrator IAM role to appropriate users in their domain. This will create the separation between Google Workspace and Google Cloud administration responsibilities that users typically seek.
### Benefits of the organization resource 

With an organization resource, project resources belong to your organization instead of the employee who created the project. This means that the project resources are no longer deleted when an employee leaves the company; instead they will follow the organization resource's lifecycle on Google Cloud.

Furthermore, Organization Administrators have central control of all resources. They can view and manage all of your company's project resources. This enforcement means that there can no longer be shadow projects or rogue admins.

Also, you can grant roles at the organization level, which are inherited by all project and folder resource under the organization resource. For example, you can grant the Network Admin role to your networking team at the organization level, allowing them to manage all the networks in all project resources in your company, instead of granting them the role for all individual project resources.

An organization resource exposed by the Cloud Resource Manager API consists of the following:

- An organization resource ID, which is a unique identifier for an organization.
- A display name, which is generated from the primary domain name in Google Workspace or Cloud Identity.
- The creation time of the organization resource.
- The last modified time of the organization resource.
- The owner of the organization resource. The owner is specified when creating the organization resource. It cannot be changed once it is set. It is the Google Workspace customer ID that is specified in the [Directory API](https://developers.google.com/admin-sdk/directory/).

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

The initial allow policy for a newly created organization resource grants the Project Creator and Billing Account Creator roles to the entire Google Workspace domain. This means users will be able to continue creating project resources and billing accounts as they did before the organization resource existed. No other resources are created when an organization resource is created.
