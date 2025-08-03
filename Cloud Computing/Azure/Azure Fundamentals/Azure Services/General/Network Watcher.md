What Is Azure Network Watcher?

Azure Network Watcher provides a suite of tools to monitor, diagnose, view metrics, and enable or disable logs for Azure IaaS (Infrastructure-as-a-Service) resources. It helps you visualize your network’s topology, track connectivity, and quickly troubleshoot issues without logging into each virtual machine.

Core Capabilities

- **Topology**: Generates an interactive map of your virtual networks, subnets, NICs, and their relationships across subscriptions and regions.
- **Connection Monitor**: Continuously tests and reports on end-to-end connectivity (latency, packet loss) between VMs, subnets, and endpoints inside or outside Azure.
- **Diagnostic Tools**:

- IP Flow Verify (checks if traffic is allowed/denied by NSG rules)
- NSG Diagnostics (analyzes security-group filtering issues)
- Next Hop (validates routing decisions)
- Connection Troubleshoot (ad hoc connectivity tests)
- Packet Capture (remote packet tracing on VMs)
- VPN Troubleshoot (diagnose VPN gateway issues)

- **Traffic Analysis**:

- Flow Logs (records IP traffic through NSGs or VNets)
- Traffic Analytics (visualizes and queries flow-log data for security auditing)

- **Usage + Quotas**: Views your deployed network resource counts and current limits per region, aiding capacity planning.

Key Benefits

- Gain a **bird’s-eye view** of your network design and dependencies.
- **Proactively monitor** connectivity and detect issues before users notice.
- **Troubleshoot remotely** without RDP/SSH into VMs.
- **Automate diagnostics** and integrate with Azure Monitor alerts.
- **Comply and audit** by retaining flow logs and analyzing traffic patterns.
- No additional agents for most tools—Network Watcher is enabled per region at no extra charge.

Getting Started in 4 Steps

1. In the Azure portal, go to **All Services** → **Network Watcher**.
2. Ensure **Network Watcher** is enabled in the regions where your VNets live.
3. Select a tool (Topology, Connection Monitor, Packet Capture, etc.) to configure settings.
4. Review results in the portal or export logs to Storage/Log Analytics for deeper analysis.
