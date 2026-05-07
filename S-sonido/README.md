# Seminario. Manejo del sonido con R 
## Instalación de R
![img](https://github.com/ruiz314/PDIH/blob/main/S-sonido/images/1_instalacionR.png)

![img](https://github.com/ruiz314/PDIH/blob/main/S-sonido/images/2_instalacionR.png)

Una vez instalado RStudio, pasaremos a instalar ambas librerías: 
```
install.packages('tuneR', dep=TRUE) 
install.packages('seewave', dep=TRUE)
```

![img](https://github.com/ruiz314/PDIH/blob/main/S-sonido/images/3_instalacionLibreria1.png)

![img](https://github.com/ruiz314/PDIH/blob/main/S-sonido/images/4_instalacionLibreria11.png)

![img](https://github.com/ruiz314/PDIH/blob/main/S-sonido/images/5_instalacionLibreria2.png)

## Instalación de RStudio
![img](https://github.com/ruiz314/PDIH/blob/main/S-sonido/images/6_instalacionRStudio.png)

Cargar el ejemplo dado por el profesor:
![img](https://github.com/ruiz314/PDIH/blob/main/S-sonido/images/7_ejemploscript.png)

Cargar las librerias del script pulsando el botón `Run`:
![img](https://github.com/ruiz314/PDIH/blob/main/S-sonido/images/8_cargarLibrerias.png)

Establezco la carpeta de trabajo:
```
setwd("/Users/inesr/OneDrive/Documentos/GitHub/PDIH/P5/ejemplo")
```
![img](https://github.com/ruiz314/PDIH/blob/main/S-sonido/images/8_establecerRuta.png)

Cargar archivo de ladrido de perro:
![img](https://github.com/ruiz314/PDIH/blob/main/S-sonido/images/9_cargarPerro.png)

Ejecutar `perro` para obtener los datos del sonido:
![img](https://github.com/ruiz314/PDIH/blob/main/S-sonido/images/10_datosPerroGato.png)
También he cargado el _Gato_. 

Mostrar los campos de ambos archivos:

![img](https://github.com/ruiz314/PDIH/blob/main/S-sonido/images/11_camposArchivo.png)
Se puede observar que tienen dos canales cada uno, y que sus canales tienen la misma longitud. Además en el campo `pcm` podemos comprobar que es un  verdadero fichero de onda estándar.

Escuchar el audio en el reproductor por defecto de Windows con la función `listen`:
![img](https://github.com/ruiz314/PDIH/blob/main/S-sonido/images/12_listenGato.png)

Para mostrar la onda del sonido uso la función `plot`:
![img](https://github.com/ruiz314/PDIH/blob/main/S-sonido/images/13_plot.png)
