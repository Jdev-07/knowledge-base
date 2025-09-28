- A role is a set of permissions to perform actions on Google Cloud
- To make these permissions available you need to grant roles

## Role types

There are three types of roles: basic (broad access to GC resources), predefined roles (granular access for specific service) and custom roles (granular access according the user-defined permissions)

### Role components

- Title: a human readable name.
- Name: An identifier for the role:
	- Predefined: `roles/SERVICE.IDENTIFIER`
	- Project-level custom: `projects/PROJECT_ID/roles/IDENTIFIER`
	- Organization-level custom: `organization/ORG_ID/roles/IDENTIFIER`
- ID: a unique identifier for the role
- **Description**: A human-readable description of the role.
- Stage: The stage of the in the lunch lifecycle
- Permissions: the permissions included in the role. Permissions allow principals to perform specific actions on Google Cloud resources. Permissions follow the format `SERVICE.RESOURCE.VERB` 

### Basic roles

Basic roles are highly permissive because they give broad access. They are not recommended for production env. 

The basic roles in IAM are Admin (roles/admin), Writer (roles/writer), and Reader (roles/reader).  

* Reader: permissions for read-only
* Writer: Same permissions as reader, plus permissions for actions that modify state, such as changing existing resources.
* Admin: Same permissions as reader/writer plus permissions like completing sensitive tasks, managing roles and permissions and setting up billing for a project. 

You cannot assign these roles via GCP console. Instead API or gcloud CLI. 

#### Legacy roles

IAM also has three legacy basic roles that existed before IAM that are owner, editor and viewer. Are known as primitive roles. Unlike with other basic roles, we cannot add conditions to role bindings. 

Unlike basic roles, these roles can be granted using GCP console, gcloud CLI and API. However, they should be assigned when granting a role to a user who is not part of the org or granting role to a project outside of the org. 

These roles can be granted to Google Account,, Service Account or Google Groups. 

### Predefined roles

These roles provide granular access to specific Google Cloud resources. Roles managed and maintained by Google, therefore are automatically updated by them.

Multiple roles can be granted to a user at any level or scope. 

### Custom roles

* IAM also lets you to create custom IAM roles enforcing the principal of least privilege. 
* These roles are user-defined and allow you to add permissions to meet your specific needs. 
* When creating a custom role you need to choose an organization or project. 
* Can only create 300 roles per organization and 300 per project.
* You can only gran this role where it was created.
* You create a custom role  by combining one or more of the supported permissions

#### Supported permissions

You can include many IAM permissions but not all. There three levels for use: Supported, Testing (can include them but can have unexpected behaviors )and Not-Supported.

An organization-level custom role can include literally any IAM supported permission. A project can contain any permission except for organization permissions because they would not do anything when they are granted.   

#### Permissions dependencies

Some permissions work effectively only when they are granted together. An example is if you want update something, you must first view or read it. 

You can create custom roles based on predefined roles. Predefined roles are designed to perform specific task and contain all of the permissions to perform them. 

#### Lifecycle

**Creation**: when creating a customer roles, you should choose a role ID, title and description to identify it. 

**Launch**: custom roles include a launch stage in the metadata. The most common are `ALPHA`, `BETA`, and `GA`. Other times include a launch stage named `DISABLED`
- `ALPHA`: The role is still being developed or tested
- `BETA`: The role has been tested on a limited basis
- `GA`: The role has been widely tested, and all of its permissions are for Google service or features that are available
- `DEPRECATED`: The role is no longer in use

**Maintenance**: You are responsible for maintaining custom roles. This includes updating roles as the user responsibilities change, as well as updating roles to let users access to new features. If you base your custom role on predefined role, it is recommended to closely track the roles for any change. 

**Disabling**: If you no longer want any principals in your org to use a custom role, you can disable it. Disabled roles still appear in the IAM policies and can be granted to principals, but they do not have any effect. 


