## Why do we need `docker`?

When dev teams develop applications or projects, there may me different problems when using different tools needing multiple  configurations, having dependent libraries and different limitations. 

- Compatibility/Dependency 
- Long setup time.
- Different Dev/Test/Prod environments.

## What can it do?

To mitigate the dependency/compatibility problems without affecting the other components, we can use Docker to separate each component into a container with all their dependencies and configurations. 

### What are `containers`?

Containers are basically isolated environment that have their own processes or services, network and mounts. They do not depend on any OS, but share the same OS Kernel. 

## Operating systems

The operating systems such Ubuntu, Fedora, CentOS or any other consist of two thing: `OS kernel` and a set of software.

`OS kernel` is responsible for interacting with the underlying hardware. 

Keep in mind: `Docker containers are not ment to virtualize, instead to package and contanize applications, and ship them and run them anywere, anytime.`

## `containers` vs `virtual machines`

The `vms` make use of more underlying resources as they consume more compute power and higher disk space, measured in GB while containers only in MB. This make containers lightweight and portable, and lets docker to boot up faster them.  However, docker containers have less isolation as more resources are shared between containers , while VMs have complete isolation between them. 

## `containers` and `virtual machines`

It is not either `containers` or `virtual machines`. Instead its `containers` and `virtual machines`. In large organizations where running a 1000s of applications on 1000s of docker hosts, can use the benefits of both, using virtualization to easily provision or decommission Docker hosts as required. 

## How it is done?

Docker Hub - Docker store. These days you can find most of the most popular applications, OSs, services and etc. 

You can provision an application as easy a running a Docker run command. 

## `container` vs `image`

An image is a package or a template. Containers are running instances of images that are isolated and have their own environments and set of processes. 

However, when you do not find any image that meets your needs, you can create your owns. In companies development  and operations must work hand in hand to create the guide and convert it into a `dockerfile` and create a docker image,  so it can be run on everywhere. 

