IAM is a tool to manage permissions in Google Cloud. Basically here is defined who can do what on which resources. 

## Access in Google Cloud

- To perform any action you would require appropriate permissions. Otherwise, IAM will deny your actions. 
- IAM involves three components: principal, roles and resource. 
- Granting the role on a resource (allow policy) enable principal to access the resource. 

### Principals

- Principals actually represent one or more identities authenticated to Google Cloud 
- The variety of types of principals are divided into two broad categories. 
	- Human users: represents humans users like employees
	- Workloads: represents workloads. You use these principals when managing workload's access.

### Permissions and Roles

- Permissions determine what actions can be performed on a resource. 
- Permissions are typically represented as `service.resource.verb`
- You grant roles instead of individual permissions. 
- Roles are collections of permissions.
- There are three types of roles: predefined, custom and basic roles
	- Predefined roles: roles supported and managed by google to perform common tasks
	- Custom roles: user-created roles over which you have the complete control. These roles are maintained by the user and also has a limit creation in project and an organization
	- Basic roles: permissive roles that provide broad access to Google Cloud services. Useful for testing purposes. 

### Resources

- Most Google Cloud service have their own resources.
- You grant roles on a resource
- You can grant roles on a subset of Google Cloud resources
- Google Cloud has several container resources, so granting the role on a container gives you the access both the container resource and the resources inside of it/

### Allow Policies

- You grant roles to principals using allow policies
- An allow policy is  YAML or JSON object attached to a Google Cloud resource

	![[iam-001.png]]

- Each allow policy contains a list of role bindings that associate IAM roles with principals who are granted those roles. 

## Policy Inheritance

- Google Cloud has container resources (organizations, folder and projects)
- If you set an allow policy on a container resource, the policy is also applied to all resources contained.
- You can use a single role binding to gran access to multiple resources.
- You can grant access to resources that do not have their own policies. Not all resources support allow policies but they inherit the policies from their parent resources. 
- To understand who can access resource you need to also view all of the allow policies that affect the resource. 

## Advanced Control

- IAM offers  other policy types: deny policies and principal access boundary (PAB) policies.
	- Deny policies: prevent principals from using some permissions even they are granted a role with the permissions.
	- PAB: these policies define and enforce resources a principal is eligible to access. Principal cannot access to resources if there are not eligible even if there are granted the necessary roles. 

- IAM conditions: lets you define and enforce conditional. you can define conditions in various policies types 
- Privileged Access Manager: let principals request and be given temporary, auditable access to resources 