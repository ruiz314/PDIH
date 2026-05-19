# PDIH. Práctica 5. Ejercicios de ampliación
library(tuneR)
library(seewave)
library(audio)

# Establecer el path concreto a la carpeta de trabajo
setwd("/Users/inesr/OneDrive/Documentos/GitHub/PDIH/P5")

# Cargar archivos de sonido:
nombre <- readWave('nombre.wav')
nombre
apellidos <- readWave('apellidos.wav')
apellidos

# Unir ambos sonidos. 
unido <- pastew(apellidos, nombre, output="Wave") # orden: nombre, apellidos

# Almacenar el sonido resultante en “basico.wav” 
writeWave(unido, file.path("basico.wav"))
basico <- readWave('basico.wav')
basico
listen(basico)

# -----------------------------------------------------------------------------------------
# Ejercicio 7. Pasarle un filtro de frecuencia para eliminar las frecuencias entre 10.000Hz 
# y 20.000Hz. Almacenar la señal obtenida como un fichero WAV denominado “filtrado.wav”

# Aplicar filtro
filtro <- bwfilter(basico, f=basico@samp.rate, from=10000, to=20000, bandpass= FALSE, output = "Wave")

# Escuchar el resultado
listen(filtro)

# Almacenar la señal en archivo
writeWave(filtro, file.path("filtrado.wav"))

# Ver información del sonido
str(filtro)
filtro

# Obtener gráfica de la onda
plot(extractWave(filtro, from = 1, to = 81886))

# -----------------------------------------------------------------------------------------
# Ejercicio 8. Tomar el sonido que se creó antes (lo tendremos en el archivo llamado “basico.wav”) 
# para aplicarle el efecto de eco. Guardar ese sonido en un archivo nuevo llamado “eco.wav”. 
# A continuación, se le debe dar la vuelta al sonido y almacenarlo como un fichero llamado “alreves.wav”
