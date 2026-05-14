library(tuneR)
library(seewave)
library(audio)

# Establecer el path concreto en cada caso a la carpeta de trabajo
setwd("/Users/inesr/OneDrive/Documentos/GitHub/PDIH/P5")

# Cargar archivos de sonido (wav/mp3):
nombre <- readWave('nombre.wav')
nombre
apellidos  <- readWave('apellidos.wav')
apellidos


# Mostrar la onda del sonido:
plot( extractWave(nombre, from = 1, to = 32879) )

plot( extractWave(apellidos, from = 1, to = 49007) )
