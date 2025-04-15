# Entornos de Virtualización 

La virtualización es una tecnología que permite la creación de entornos virtuales aislados, lo que posibilita la ejecución de multiples sistemas operativos y aplicaciones en único servidor físico.

## VMWARE

[Download](https://www.vmware.com/products/desktop-hypervisor/workstation-and-fusion#product-overview)

- **Versiones**: 

o    **Gratuita (VMware Workstation Player)**: Permite ejecutar máquinas virtuales, pero con funcionalidades limitadas (no tiene snapshots avanzados, clonación, etc.). 

o    **De pago (VMware Workstation Pro, vSphere, ESXi)**: Ofrece características avanzadas como snapshots, clonación, migración en caliente, gestión centralizada y alta disponibilidad. 

- **Sistemas operativos soportados**: Puede ejecutar casi cualquier sistema operativo (Windows, Linux, macOS, BSD, etc.). 

- **Seguridad**: 

o    **Aislamiento de recursos**: Cada máquina virtual funciona de manera independiente, sin afectar al sistema host ni a otras máquinas virtuales. 

o    **Snapshots**: Son "fotos" del estado de una máquina virtual en un momento dado. Permiten revertir cambios en caso de errores o ataques. 

o    **Cifrado**: Protege los datos de las máquinas virtuales para que no sean accesibles sin autorización. 

- **Beneficios para auditorías**: 

o    **Entornos aislados**: Permite crear redes virtuales para pruebas de penetración sin afectar sistemas reales. 

o    **Monitorización**: Herramientas para analizar el tráfico de red y detectar anomalías.

## VirtualBox 

- **Tipo**: Open source (gratuito). 

- **Versiones**: 

o    **Gratuita**: Ofrece todas las funcionalidades básicas y avanzadas (snapshots, clonación, redes virtuales, etc.). 

o    **Extension Pack (opcional, gratis para uso personal)**: Añade soporte para USB 2.0/3.0, cifrado de disco, etc. 

- **Sistemas operativos soportados**: Windows, Linux, macOS, Solaris, BSD, etc. 

- **Seguridad**: 

o    **Aislamiento de máquinas virtuales**: Cada máquina virtual funciona de manera independiente. 

o    **Redes virtuales**: Permite simular redes complejas para pruebas de seguridad. 

- **Beneficios para auditorías**: 

o    **Laboratorios de seguridad**: Ideal para crear entornos de prueba para análisis de vulnerabilidades. 

o    **Fácil de usar**: No requiere licencias costosas, ideal para principiantes.

## HyperV

- **Tipo: Gratuito (incluido en Windows Pro y Enterprise) y de pago (en versiones de servidor).** 

- **Versiones:** 

o    **Gratuita (Hyper-V en Windows 10/11 Pro): Funcionalidades básicas de virtualización.** 

o    **De pago (Windows Server con Hyper-V): Ofrece características avanzadas como replicación, migración en caliente y alta disponibilidad.** 

- **Sistemas operativos soportados: Windows, Linux (con soporte limitado), y otros sistemas compatibles.** 

- **Seguridad:** 

o    **Shielded VMs: Máquinas virtuales blindadas que protegen contra accesos no autorizados.** 

o    **Integración con Windows Defender: Herramienta de seguridad de Microsoft para proteger contra malware.** 

- **Beneficios para auditorías:** 

o    **Entornos Windows: Ideal para pruebas de seguridad en sistemas Windows.** 

o    **Monitorización: Herramientas integradas para analizar el tráfico de red.**

## **AWS (Amazon Web Services)** 

- **Tipo: De pago (modelo de pago por uso).** 

- **Sistemas operativos soportados: Cualquier sistema operativo (Windows, Linux, etc.).** 

- **Seguridad:** 

- **IAM (Identity and Access Management): Herramienta para gestionar permisos y accesos.** 

- **VPC (Virtual Private Cloud): Redes virtuales aisladas para mayor seguridad.** 

- **GuardDuty: Servicio de detección de amenazas en tiempo real.** 

- **Beneficios para auditorías:** 

- **Escalabilidad: Permite crear entornos grandes para pruebas de seguridad.** 

- **CloudWatch: Herramienta para monitorear y analizar logs y tráfico de red.** 

## **Docker** 

- **Tipo: Open source (gratuito) y de pago (Docker Enterprise).** 

- **Sistemas operativos soportados: Linux, Windows (con contenedores Linux o Windows).** 

- **Seguridad:** 

- **Namespaces y cgroups: Tecnologías de Linux que aíslan los contenedores entre sí.** 

- **Escaneo de imágenes: Herramienta para detectar vulnerabilidades en las imágenes de Docker.** 

- **Beneficios para auditorías:** 

- **Contenedores ligeros: Permiten crear entornos de prueba rápidos y eficientes.** 

- **Microservicios: Ideal para analizar aplicaciones modernas basadas en contenedores.**

