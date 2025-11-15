## Overview

All resources except the highest (organization) resource in a hierarchy  have one parent. At the lowest level are located the service resources that make up all Google Cloud Services and all of these resources have project resources as their parent. 

All users, including free trial, free tier users, and Google Workspace and Cloud Identity, can create project resources, but only Google Workspace and Cloud Identity can create organization and folder resources. Projects can be de top resources but can be migrated once you are able to create an organization. 

An organization resource represents a company. If this exists is the top resource and all resources are created under the organization and belong to it. 

The Google Cloud resource hierarchy, especially in its most complete form which includes an organization resource and folder resources, allows companies to map their organization resource onto Google Cloud and provides logical attachment points for access management policies (IAM) and [organization policies](https://docs.cloud.google.com/resource-manager/docs/organization-policy/overview).

## Organization resource

The organization resource, actually represents an organization (or company) and is the root node when present. All the allow and deny policies applied on the organization resource apply throughout the hierarchy on all resources in the organization. 

Users are not required to have an organization resource, but to get all benefits and features from the google cloud resource hierarchy, then you might consider having one.

A google cloud account can have exactly one organization. Once an organization is associated with a domain, all google cloud project resources created by members of the account domain will by default belong to the organization.

Having an organization provides identity management , recovery mechanism, ownership and lifecycle  management

The Google Workspace super admin is granted the ability to assign IAM roles by default. The Google Workspace super admin's main duty with respect to Google Cloud is to assign the Organization Administrator IAM role to appropriate users in their domain

### Folder resource

Folder resource are an additional, optional grouping mechanism between organization resources and project resources. An organization is required for creating folders.

Folders can be as sub-organization within the organization resource. Also, can be used to model different legal entities, departments, and teams within a company.

Folder resources allow delegation of administration rights, so for example, each head of a department can be granted full ownership of all Google Cloud resources that belong to their departments. Similarly, access to resources can be limited by folder resource, so users in one department can only access and create Google Cloud resources within that folder resource.

### Project resource

The project resource is the base-level organizing entity. Organization and folder resources may contain multiple projects. A project resource is required to use Google Cloud, and forms the basis for creating, enabling, and using all Google Cloud services, managing APIs, enabling billing, adding and removing collaborators, and managing permissions.

Some things that you need to know about project resources:

- A project has two identifiers: project resource ID and a project resource number which is automatically  assigned when creates the project
- Has one mutable display name
- The lifecycle of the project resource are ACTIVE or DELETE_REQUESTED


