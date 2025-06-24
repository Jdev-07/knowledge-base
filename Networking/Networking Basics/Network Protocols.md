
**ETHERNET | IP | TCP | HTTP**

## TCP/IP Model

Application. HTTP governs here.

Transport. Here is used the Transport Control Protocol

Internet. We is used the IP (source and destination IP)

Network Access, Ethernet protocol used for NIC card and communication.

Layered models help us visualize how the various protocols work together to enable network communications. A layered model depicts the operation of the protocols occurring within each layer, as well as the interaction with the layers above and below it. The layered model has many benefits:

- Assists in protocol design, because protocols that operate at a specific layer have defined information that they act upon and a defined interface to the layers above and below.
- Fosters competition because products from different vendors can work together.
- Enables technology changes to occur at one level without affecting the other levels.
- Provides a common language to describe networking functions and capabilities.

The first layered model for internetwork communications was created in the early 1970s and is referred to as the internet model. It defines four categories of functions that must occur in order for communications to be successful. The suite of TCP/IP protocols that are used for internet communications follows the structure of this model, as shown in the table. Because of this, the internet model is commonly referred to as the TCP/IP model.

| TCP/IP Model Layer | Description                                                             |
| ------------------ | ----------------------------------------------------------------------- |
| Application        | Represents data to the user, plus encoding and dialog control.          |
| Transport          | Supports communication between various devices across diverse networks. |
| Internet           | Determines the best path through the network.                           |
| Network Access     | Controls the hardware devices and media that make up the network.       |

## The OSI Model

There are two basic types of models that we use to describe the functions that must occur in order for network communications to be successful: protocol models and reference models.

- **Protocol model -** This model closely matches the structure of a particular protocol suite. A protocol suite includes the set of related protocols that typically provide all the functionality required for people to communicate with the data network. The TCP/IP model is a protocol model because it describes the functions that occur at each layer of protocols within the TCP/IP suite.
- **Reference model -** This type of model describes the functions that must be completed at a particular layer, but does not specify exactly how a function should be accomplished. A reference model is not intended to provide a sufficient level of detail to define precisely how each protocol should work at each layer. The primary purpose of a reference model is to aid in clearer understanding of the functions and processes necessary for network communications.

The most widely known internetwork reference model was created by the Open Systems Interconnection (OSI) project at the International Organization for Standardization (ISO). It is used for data network design, operation specifications, and troubleshooting. This model is commonly referred to as the OSI model.

| OSI Model Layer  | Description                                                                                                                                                                                                         |
| ---------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 7 - Application  | The application layer contains protocols used for process-to-process communications.                                                                                                                                |
| 6 - Presentation | The presentation layer provides for common representation of the data transferred between application layer services.                                                                                               |
| 5 - Session      | The session layer provides services to the presentation layer to organize its dialogue and to manage data exchange.                                                                                                 |
| 4 - Transport    | The transport layer defines services to segment, transfer, and reassemble the data for individual communications between the end devices.                                                                           |
| 3 - Network      | The network layer provides services to exchange the individual pieces of data over the network between identified end devices.                                                                                      |
| 2 - Data Link    | The data link layer protocols describe methods for exchanging data frames between devices over a common media.                                                                                                      |
| 1 - Physical     | The physical layer protocols describe the mechanical, electrical, functional, and procedural means to activate, maintain, and de-activate physical connections for a bit transmission to and from a network device. |

## OSI Model and TCP/IP Model Comparison

Because TCP/IP is the protocol suite in use for internet communications, why do we need to learn the OSI model as well?

The TCP/IP model is a method of visualizing the interactions of the various protocols that make up the TCP/IP protocol suite. It does not describe general functions that are necessary for all networking communications. It describes the networking functions specific to those protocols in use in the TCP/IP protocol suite. For example, at the network access layer, the TCP/IP protocol suite does not specify which protocols to use when transmitting over a physical medium, nor the method of encoding the signals for transmission. OSI Layers 1 and 2 discuss the necessary procedures to access the media and the physical means to send data over a network.

The protocols that make up the TCP/IP protocol suite can be described in terms of the OSI reference model. The functions that occur at the internet layer in the TCP/IP model are contained in the network layer of the OSI Model, as shown in the figure. The transport layer functionality is the same between both models. However, the network access layer and the application layer of the TCP/IP model are further divided in the OSI model to describe discrete functions that must occur at these layers.

![](https://www.netacad.com/content/nb/1.0/assets/zoom_in.svg)

The key similarities are in the transport and network layers; however, the two models differ in how they relate to the layers above and below each layer:

- OSI Layer 3, the network layer, maps directly to the TCP/IP internet layer. This layer is used to describe protocols that address and route messages through an internetwork.
- OSI Layer 4, the transport layer, maps directly to the TCP/IP transport layer. This layer describes general services and functions that provide ordered and reliable delivery of data between source and destination hosts.
- The TCP/IP application layer includes several protocols that provide specific functionality to a variety of end user applications. The OSI model Layers 5, 6, and 7 are used as references for application software developers and vendors to produce applications that operate on networks.
- Both the TCP/IP and OSI models are commonly used when referring to protocols at various layers. Because the OSI model separates the data link layer from the physical layer, it is commonly used when referring to these lower layers.