
Overview

Microsoft Entra ID Protection helps organizations detect, investigate, and remediate identity-based risks in real time. It continuously analyzes trillions of signals—such as sign-in patterns, leaked credentials, and atypical locations—to generate risk scores for both sign-ins and users. These risk insights can then drive automated or policy-based actions through Conditional Access or be forwarded to SIEM and XDR tools for deeper investigation.

Core Features

- Detect risks during each sign-in or over time for user accounts
- Assign real-time sign-in risk levels (low/medium/high) based on anomalous behavior
- Track risk detections, risky sign-ins, and risky users in built-in reports
- Automate remediation via risk-based Conditional Access controls (MFA, block, password reset)
- Enable manual remediation workflows for admins to dismiss, confirm safe, or confirm compromise
- Export risk data to Log Analytics, Event Hubs, storage accounts, or SIEM/XDR solutions via Microsoft Graph APIs
- Integrate with other Microsoft Defender signals (Cloud Apps, Endpoint, Office 365) for richer detections

Core Capabilities

|Capability|Description|
|---|---|
|Risk Detection Catalog|Continuously updated detections (anonymous IPs, password spray, leaked credentials)|
|Reporting & Dashboards|Three key reports—Risk Detections, Risky Sign-Ins, Risky Users—and a visual attack graphic|
|Automated Remediation|Conditional Access policies triggered by sign-in or user risk levels|
|Manual Remediation|Admin portal and API actions to review, dismiss, or confirm risk events|
|Data Export & Integration|Microsoft Graph APIs, SIEM connectors, Log Analytics, Event Hubs|
|Licensing Enforcement|Entra ID P2 required for full feature access; mixed Defender licenses for signal sources|

Licensing & Roles

Microsoft Entra ID Protection requires an Entra ID P2 license. Key roles include:

|Role|Can View Reports|Can Configure Policies|Can Remediate Risks|
|---|---|---|---|
|Security Reader|Yes|No|No|
|Conditional Access Administrator|Yes|Yes|No|
|Security Operator|Yes|No|Yes|
|Security Administrator|Yes|Yes|Yes|