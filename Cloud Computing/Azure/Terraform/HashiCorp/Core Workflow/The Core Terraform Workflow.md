The core Terraform workflow has three steps

1. **Write** - Author infrastructure as code.
2. **Plan** - Preview changes before applying.
3. **Apply** - Provision reproducible infrastructure.

## Working as an Individual Practitioner

Let's first walk through how these parts fit together as an individual working on infrastructure as code.

### Write

You write Terraform configuration just like you write code: in your editor of choice. It's common practice to store your work in a version controlled repository even when you're just operating as an individual.

```Bash
# Create repository
$ git init my-infra && cd my-infra

Initialized empty Git repository in /.../my-infra/.git/

# Write initial config
$ vim main.tf

# Initialize Terraform
$ terraform init

Initializing provider plugins...
# ...
Terraform has been successfully initialized!
```

As you make progress on authoring your config, repeatedly running plans can help flush out syntax errors and ensure that your config is coming together as you expect.

```Bash
# Make edits to config
$ vim main.tf

# Review plan
$ terraform plan

# Make additional edits, and repeat
$ vim main.tf
```

This parallels working on application code as an individual, where a tight feedback loop between editing code and running test commands is useful.

### Plan

When the feedback loop of the Write step has yielded a change that looks good, it's time to commit your work and review the final plan.

```Bash
git add main.tf
git commit -m 'Managing infrastructure as code!'
```

Because `terraform apply` will display a plan for confirmation before proceeding to change any infrastructure, that's the command you run for final review.

```Bash
terraform apply
```

### Apply

After one last check, you are ready to tell Terraform to provision real infrastructure.

```Bash
Do you want to perform these actions?

  Terraform will perform the actions described above.
  Only 'yes' will be accepted to approve.
  Enter a value: yes

# ...

Apply complete! Resources: 1 added, 0 changed, 0 destroyed.
```

At this point, it's common to push your version control repository to a remote location for safekeeping.

```Bash
git remote add origin https://github.com/*user*/*repo*.git
git push origin main
```

This core workflow is a loop; the next time you want to make changes, you start the process over from the beginning.

Notice how closely this workflow parallels the process of writing application code or scripts as an individual? This is what we mean when we talk about Terraform enabling infrastructure as code.

## Working as a Team

Once multiple people are collaborating on Terraform configuration, new steps must be added to each part of the core workflow to ensure everyone is working together smoothly. You'll see that many of these steps parallel the workflow changes we make when we work on application code as teams rather than as individuals.

### Write

While each individual on a team still makes changes to Terraform configuration in their editor of choice, they save their changes to version control _branches_ to avoid colliding with each other's work. Working in branches enables team members to resolve mutually incompatible infrastructure changes using their normal merge conflict workflow.

```Bash
git checkout -b add-load-balancer
```

Running iterative plans is still useful as a feedback loop while authoring configuration, though having each team member's computer able to run them becomes more difficult with time. As the team and the infrastructure grows, so does the number of sensitive input variables (e.g. API Keys, SSL Cert Pairs) required to run a plan.

To avoid the burden and the security risk of each team member arranging all sensitive inputs locally, it's common for teams to migrate to a model in which Terraform operations are executed in a shared Continuous Integration (CI) environment. The work needed to create such a CI environment is nontrivial, and is outside the scope of this core workflow overview, but a full deep dive on this topic can be found in our [Running Terraform in Automation](https://developer.hashicorp.com/terraform/tutorials/automation/automate-terraform?utm_source=WEBSITE&utm_medium=WEB_IO&utm_offer=ARTICLE_PAGE&utm_content=DOCS) guide.

This longer iteration cycle of committing changes to version control and then waiting for the CI pipeline to execute is often lengthy enough to prohibit using speculative plans as a feedback loop while authoring individual Terraform configuration changes. Speculative plans are still useful before new Terraform changes are applied or even merged to the main development branch, however, as we'll see in a minute.  

### Plan

Once a pull request is ready for review, Terraform Cloud makes the process of reviewing a speculative plan easier for team members. First, the plan is automatically run when the pull request is created. Status updates to the pull request indicate while the plan is in progress.

Once the plan is complete, the status update indicates whether there were any changes in the speculative plan, right from the pull request view.

![[terraform-007.png]]

For certain types of changes, this information is all that's needed for a team member to be able to approve the pull request. When a teammate needs to do a full review of the plan, clicking the link to Terraform Cloud brings up a view that allows them to quickly analyze the full plan details.

![[terraform-008.png]]
This page allows the reviewer to quickly determine if the plan is matching the config author's intent and evaluate the risk of the change.

### Apply

After merge, Terraform Cloud presents the concrete plan to the team for review and approval.

![[terraform-009.png]]The team can discuss any outstanding questions about the plan before the change is made.

![[terraform-010.png]]Once the Apply is confirmed, Terraform Cloud displays the progress live to anyone who'd like to watch.

![[terraform-011.png]]

## Conclusion

There are many different ways to use Terraform: as an individual user, a single team, or an entire organization at scale. Choosing the best approach for the density of collaboration needed will provide the most return on your investment in the core Terraform workflow. For organizations using Terraform at scale, Terraform Cloud introduces new layers that build on this core workflow to solve problems unique to teams and organizations.