Overview

Microsoft Entra ID Governance is an identity governance solution that helps organizations ensure the right people have the right access to the right resources for the right amount of time. It automates identity and access processes across both cloud and on-premises applications, improves security and compliance, and delegates routine decisions to business owners through rich workflows and reporting.

Core Features

- Entitlement management  
    Automate access packages for users and guests, define policies for who can request access and when it expires.
- Access reviews  
    Schedule recurring reviews of user, guest, and privileged access to confirm continued need or remove stale permissions.
- Lifecycle workflows  
    Create no-code/low-code workflows that react to HR events, attribute changes, or manual triggers for onboarding, offboarding, and role changes.
- Privileged Identity Management (PIM)  
    Just-in-time activation of admin roles, time-bound assignments, alerting, and multi-step approval for high-risk privileges.
- Governance dashboard  
    Single-pane view of identity landscape, coverage of governance features, and guided configuration for missing controls.
- Connector library  
    Out-of-the-box connectors (SCIM, LDAP, SQL) for hundreds of SaaS and on-premises apps to provision, deprovision, and enforce policy.

Core Capabilities

|Capability|Description|
|---|---|
|Identity lifecycle automation|Inbound provisioning from HR sources, automatic assignment policies, user provisioning via SCIM/LDAP|
|Access lifecycle management|Define and enforce separation of duties, automate group/app membership changes based on attributes|
|Privileged access lifecycle|Time-bound and approval workflows for admin roles, alerting, just-in-time access via PIM|
|Visibility & reporting|Risk-based insights, governance dashboard, detailed audit logs, integration with SIEM/XDR|
|Delegated governance|Assign review and approval tasks to business users, configure custom roles and access packages|
|Workflow extensibility|Custom task extensions via Logic Apps or Azure Functions for ticketing, notifications, and more|

Recommended Scenarios

- Automate employee onboarding/offboarding, ensuring accounts and entitlements match HR status.
- Govern B2B guest and partner access with expiration policies and periodic reviews.
- Recertify access for applications, groups, SharePoint sites, and roles to meet audit requirements.
- Enforce separation of duties for finance, HR, or security-critical applications.
- Delegate access review tasks to managers, resource owners, or external auditors.
- Manage privileged roles with time-bound, just-in-time activation and multi-step approvals.

Licensing & Roles

|Licensing Requirement|Description|
|---|---|
|Entra ID P2 or Entra Suite|Required for full entitlement management, reviews, workflows, and PIM features|
|Entra ID Governance add-on (for P1 users)|Enables governance features as standalone licenses|

|Role|Can View Reports|Can Configure Policies|Can Remediate & Review|
|---|---|---|---|
|Security Reader|Yes|No|No|
|Governance Administrator|Yes|Yes|No|
|Entitlement Manager|No|Yes (access packages)|Yes (approve requests)|
|Access Reviewer|Yes|No|Yes (conduct reviews)|
|Privileged Role Administrator (PIM)|Yes|Yes|Yes (activate roles)|
