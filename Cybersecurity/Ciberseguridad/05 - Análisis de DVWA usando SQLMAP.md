Evaluacion de sistemas y aplicaciones

Escaneo de red con zenmap/nmap 

Análisis de metadatos con FOCA

OWASP

Herramienta libre de seguridad global. 

Burp Suite

Esceneo de seguridad, intercepcion de solicitudes. 

ZAP (OWASP Zed Attack proxy)

## Docker as virtual environment 

### Process to install Docker in Kali Linux

Update applications
```BASH
sudo apt update
```

Install docker
```BASH
sudo apt install -y docker.io
```

Enable docker
```BASH
sudo systemctl enable docker
```

To check active containers 
```BASH
docker ps
```

Run DVWA
```BASH
docker run --rm -it -p 80:80 vulnerables/web-dvwa
```

Check who is a specific port
```BASH
sudo lsof -i :80
```

Then we need to type in the search bar "localhost" and enter the credentials:  admin/password

### Create a database for testing

Access to the container 
```BASH
sudo docker exec -it name bash
```

Access to MySQL
```BASH
mysql -u root -p
```

