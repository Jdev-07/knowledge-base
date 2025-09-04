# Managing User in Linux

## Type of Users in Linux

Linux supports two types of users: system users and regular users.

**System users** are created by the system during installation and are used to run system services and applications.

**Regular users** are created by the administrator and can access the system and its resources based on their permissions.

## How to Create Users

The System administrator needs to create user accounts for Jony, Ricardo, and Eduardo. The admin initiates the process using the `useradd` command. For example, to create Jony's account, Admin executes the command below:

```bash
useradd -u 1002 -d /home/john -s /bin/bash john
```

This command creates Jony's account with uid (`-u`) as 1005, the home directory (`-d`) as **/home/jony** and sets (`-s`) **/bin/bash** as his default shell.

Similarly, Jdev will create a user account for Ricardo and Eduardo using same format

Jdev can verify the new user account by running the `id` command:

```bash
id jony
```

![[linux-007.png]]


## User Account Properties

Within Linux environment, user accounts possess various properties that define their characteristics and access privileges. Let's explore these properties in the context of our use case.

1. **Username**: Each user is assigned a unique username that serves as their identifier within the Linux system. For example, John's username is "john".
2. **UID (User ID) and GID (Group ID)**: Every user account is associated with a UID and GID. The UID is a numerical value assigned to the user, while the GID represents the primary group to which the user belongs. For instance, John's UID may be `1002,` and his primary group's GID is `1002` as well.
3. **Home Directory**: Each user has a designated home directory where their personal files and settings reside. John's home directory is **/home/john**.
4. **Default Shell**: The default shell determines the command interpreter used when a user logs in. It defines the user's interactive environment. In our case, John's default shell is set to **/bin/bash**, which is a popular shell in Linux.
5. **Password**: User accounts require passwords to authenticate and access the system. CTechCo's users, including John, must create strong passwords to ensure security.
6. **Group**: The group membership determines which system resources the user can access, as well as which users can access the user's files.

Jdev could take a look at the users on their Linux by running the `cat /etc/passwd` command. The users will be displayed in this format:

![[linux-008.png]]

Here's what each of the fields in the format above represents:

- `john`: This is the username of the user account.
- `x`: This field contains the encrypted password of the user. It is replaced with an 'x' character to indicate that the password is stored in the `/etc/shadow` file for security reasons.
- `1005`: This is the UID (User ID) of the user account, which is a unique numerical identifier assigned to the user by the system.
- `1005`: This is the GID (Group ID) of the user account, which represents the primary group membership of the user.
- `,,,`: This is the GECOS field, which stands for "General Electric Comprehensive Operating System". This field is used to store additional information about the user, such as their full name or contact information. In this case, the field is empty, as no additional information was provided while creating the user account.
- `/home/jony`: This is the home directory of the user account, which is the location where the user's files and personal data are stored.
- `/bin/bash`: This is the default shell for the user account, which is the command interpreter used to process commands entered by the user in the terminal. In this case, the default shell is Bash, which is the most commonly used shell in Linux.

## How to Delete Users

Let's assume that Edu has left org. To remove her account and associated files, Jdev has to utilize the `userdel` command. For instance, to delete Lisa's account, Jdev runs:

```bash
sudo userdel lisa
```

This will delete the user account for `ed09`, along with their home directory and any files or directories owned by the user.

## How to Modify User Accounts

As TK workforce evolves, the IT team may need to make adjustments to user accounts. Let's explore how they can modify user accounts to accommodate changing needs and permissions.

For example, Jony (the developer), is assigned additional responsibilities within the company. To reflect this change, the IT team can modify Jony's account using the `usermod` command. Let's consider the following scenario:

### How to Modify User Groups in Linux

TK creates a new group called `development` to manage access to development-related resources. To add Jony to the `development` group, the following command can be used:

`sudo usermod -aG development john`

This command adds John to the `development` group, granting him the necessary access privileges.

### How to Change Default Shell in Linux

In a case where John prefers to use a different shell other than the default **/bin/bash** shell. The IT team can modify his account accordingly. For example, to change John's default shell to **/bin/zsh**, the following command can be used:

```Bash
sudo usermod -s /bin/zsh john
```

This command updates John's account to use the new default shell — **/bin/zsh**.

You can run the `cat /etc/passwd` again to see that the shell for john has changed from **/bin/bash** to **/bin/zsh**.

## Group Management

Effective group management is crucial for controlling access to resources within TK's Linux environment. Let's explore how the IT team can create and manage groups to ensure proper access control.

### How to Create a New Group in Linux

To create a new group, such as the `marketing` group, the following command can be used:

`sudo groupadd marketing`

The command above creates the `marketing` group, which can be used to grant specific permissions and access to marketing-related resources.

To view the group you just added, run the command below:

```Bash
cat /etc/group | grep "marketing"
```

This command will return the following:

![[linux-009.png]]

### How to Assign Users to Groups in Linux

Once a group is created, users can be added to it. For example, to add Ricardo (the marketing manager) to the `marketing` group, the following command can be used:

`sudo usermod -aG marketing ricardo`

This command adds Ricardo to the `marketing` group, enabling her to access the resources associated with that group.

## Password Management

Ensuring strong password management practices is essential for maintaining the security of user accounts within CTechCo's Linux environment. Let's explore how the IT team can enforce password policies and manage user passwords effectively.

**Setting Password Policies:** The IT team can establish password policies to enforce strong passwords, including complexity requirements, password expiration, and account lockouts. These policies can be configured in the **/etc/login.defs** file.

**Changing User Passwords:** Users should be encouraged to change their passwords periodically. They can do so using the `passwd` command. For example, John can change his password with the following command:

`sudo passwd john`

This command prompts John to enter his current password and then allows him to set a new, secure password.

## User Authentication

User authentication is a crucial aspect of user management in Linux, ensuring that only authorized users can access the system. CTechCo can employ various authentication mechanisms to safeguard their Linux environment.

### Password-Based Authentication

Password-based authentication is the most common method for user authentication in Linux. When users log in, they provide their username and corresponding password to authenticate their identity.

For example, John logs into the system by entering his username and password at the login prompt. The system then verifies the provided password against the stored password hash associated with John's account.

### SSH Key-Based Authentication

Secure Shell (SSH) key-based authentication provides a more secure alternative to password-based authentication. Users generate a public-private key pair, where the public key is stored on the server and the private key is kept securely on the user's device.

With SSH key-based authentication, users like Lisa, a system administrator at CTechCo, can authenticate without entering a password. Instead, the server verifies the user's identity based on the possession of the private key.

To configure SSH key-based authentication for Lisa, the following steps can be taken:

1. Generate an SSH key pair on Lisa's machine using the `ssh-keygen` command.
2. Copy the public key to the server's **/home/lisasmith/.ssh/authorized_keys** file.
3. Configure the server to allow SSH key-based authentication.

### Monitoring and Auditing

TK can implement monitoring and auditing mechanisms to track user activities and identify potential security breaches. They utilize tools like auditd to collect and analyze system logs, enabling them to detect suspicious activities and take appropriate actions.

For example, the IT team can configure auditd to monitor critical system files and directories, as well as user logins and administrative commands.

Also, to view system logs in Linux, Alex can use the `tail` command. For example, to view the last 10 lines of the system log file, you can use the following command:

```bash
sudo tail /var/log/syslog
```
