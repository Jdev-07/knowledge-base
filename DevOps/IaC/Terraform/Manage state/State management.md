# State locking 

Terraform will lock the state from any operation that could write the state only if backend support it. Regardless of you can disable the state locking, but is not recommended 

Terraform has a command to force unlock the state if the automatic unlocking process fails. This command must be used very carefully, because unlocking the state while another user still holds the lock can cause multiple writers and corrupt the state. It should only be used to unlock your own lock in situations where automatic unlocking has failed.

# Sensitive variables

When provisioning infrastructure, we often use sensitive information such as credentials or PII that we do not want to accidentally expose in any output.

Using a `.tfvars` file allows you to separate sensitive values from the rest of the configuration. If a variable is marked as sensitive, Terraform will not display its actual value and will instead show `sensitive` or `sensitive value`. However, this file should only be shared with authorized individuals and must not be committed to version control.

Another workaround for this situation is to use environment variables following the `TF_VAR_<VARIABLE_NAME>` pattern.

Regardless of these efforts, using sensitive variables, assigning values through `.tfvars` files, or defining them via environment variables, when using a local state file, Terraform stores the state in **plaintext**, including these values, even if they are marked as sensitive. Marking variables as sensitive is therefore **not sufficient** to fully secure them.

## Sensitive Data in State

Most of the time, the Terraform state contains sensitive data because it includes resource IDs and all their attributes. When using a local state file, the state is stored as a plain-text JSON file. When using remote state, the state is only held in memory while Terraform is operating on it, and it may be encrypted at rest depending on the remote state backend.

**Recommendations**

- If you are managing any sensitive data, treat the Terraform state as sensitive.
- Storing the state remotely can provide better security.


