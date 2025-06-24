
Docker allows you to package an application with all of its dependencies into a standardized unit called a container. This makes it easier to deploy and run applications consistently across different environments.

## Docker concepts

1. Container:  A lightweight, standalone, and executable package that includes everything needed to run a piece of software.
2. Image:  Think of this as a template or blueprint for containers. It contains all the instructions needed to create a container.
3. Docker Hub: Like GitHub but for Docker images - it's where you can find and share container images.
4. Docker Engine: The core technology that runs and manages containers on your machine.

### Docker commands

```SHELL
docker run image-name
```

Here, we run a container based on the image name. The **run** command creates and starts a container from specified image. The command check if the image is available. If not found, it will download the image from Docker Hub. 

```SHELL
docker images
```

The command **docker images** allows to see the images available on our local system.
## Understanding Docker Images

An image is like a blueprint or a template for a container. It contains all the instructions needed to create a container.

When we run the command **docker images** we will see an output like the following

![[docker-001.png]]
W

- `REPOSITORY`: The name of the image. In this case, it's "hello-world".
- `TAG`: The version of the image. "latest" is the default tag if you don't specify one.
- `IMAGE ID`: A unique identifier for the image. This is useful when you need to refer to a specific image.
- `CREATED`: When the image was created. This helps you know if you have the most recent version.
- `SIZE`: The size of the image on disk. Docker images are designed to be lightweight, which is why the hello-world image is only 13.3kB.

## About Docker Hub

Docker Hub is a cloud-based registry service where Docker users and organizations can store and distribute their Docker images. It's like a GitHub for Docker images, serving as a central repository where you can find, share, and manage Docker images.

