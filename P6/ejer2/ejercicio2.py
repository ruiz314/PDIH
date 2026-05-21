import cv2
import sys
import os

# Validación del número de argumentos en la línea de comandos
if len(sys.argv) < 2:
    print("\n[ERROR] Uso correcto: python ejercicio2.py <nombre_video.mp4>\n")
    sys.exit(1)

# Captura del parámetro del archivo de video
nombre_video = sys.argv[1]

#Carga el modelo classificador de Haar:
modeloCara = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
  
# Inicializa la captura del archivo de vídeo pasado por parámetro
camara = cv2.VideoCapture(nombre_video)

# Valida que el archivo realmente exista y OpenCV pueda decodificarlo
if not camara.isOpened():
    print(f"\n[ERROR] No se pudo abrir el archivo de vídeo: '{nombre_video}'\n")
    sys.exit(1)
