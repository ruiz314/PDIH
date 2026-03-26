# Seminario Tesseract

## Instalación
Este seminario lo realizo en la terminal de WSL.

Primero actualizo la lista de paquetes ejecutando: `sudo apt update`

![img1](https://github.com/ruiz314/PDIH/blob/main/S-ocr-tesseract/img/1actualizacion.png)

Instalo el motor de Tesseract y el paquete de idioma español ejecutando: `sudo apt install tesseract-ocr tesseract-ocr-spa`

![img2](https://github.com/ruiz314/PDIH/blob/main/S-ocr-tesseract/img/2instalacion.png)

Pulso la tecla `Y` para que la instalación continue.

![img3](https://github.com/ruiz314/PDIH/blob/main/S-ocr-tesseract/img/3aceptar.png)

## Pruebas con noticias
### Ejemplo 1

![img](https://github.com/ruiz314/PDIH/blob/main/S-ocr-tesseract/img.png)

```bash
tesseract img.png stdout
tesseract img.png stdout -l spa
```

![img4](https://github.com/ruiz314/PDIH/blob/main/S-ocr-tesseract/img/4noticia1.png)

### Ejemplo2

![img](https://github.com/ruiz314/PDIH/blob/main/S-ocr-tesseract/img-T8.png)

```bash
tesseract img-T8.png stdout
tesseract img-T8.png stdout -l spa
```

![img5](https://github.com/ruiz314/PDIH/blob/main/S-ocr-tesseract/img/5noticia2.png)

## Pruebas con matriculas de coche
