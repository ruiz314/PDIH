import cv2
import sys
import os
 
# Validación del número de argumentos en la línea de comandos
if len(sys.argv) < 2:
    print("\n[ERROR] Uso correcto: python ejercicio3.py <nombre_video.mp4>\n")
    sys.exit(1)

# Captura del parámetro del archivo de video
nombre_video = sys.argv[1]

# Carga el modelo classificador de Haar:
modeloGato = cv2.CascadeClassifier('haarcascade_frontalcatface_extended.xml') 

# Inicializa la captura del archivo de vídeo pasado por parámetro
camara = cv2.VideoCapture(nombre_video)

if not camara.isOpened():
    print(f"\n[ERROR] No se pudo abrir el archivo de vídeo: '{nombre_video}'\n")
    sys.exit(1)

# Guarda el vídeo resultante con los gatos detectados
fps = int(camara.get(cv2.CAP_PROP_FPS))         
ancho = int(camara.get(cv2.CAP_PROP_FRAME_WIDTH))  
alto = int(camara.get(cv2.CAP_PROP_FRAME_HEIGHT))  

nombre_base, extension = os.path.splitext(nombre_video)
video_salida = f"resultado_gatos_{nombre_base}{extension}"
fourcc = cv2.VideoWriter_fourcc(*'mp4v')
grabador = cv2.VideoWriter(video_salida, fourcc, fps, (ancho, alto))

print(f"\n Buscando gatos en: '{nombre_video}'")

# Procesa el vídeo mientras esté abierto
while camara.isOpened(): 
    hay_frame, img = camara.read() 

    if not hay_frame:
        print("Fin del archivo de vídeo alcanzado.")
        break

    # Convierte el fotograma a escala de grises
    imagen_gris = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY) 

    # Busca los rostros de gatos
    gatos = modeloGato.detectMultiScale(imagen_gris, scaleFactor=1.1, minNeighbors=6)

    # Recorre el array 'gatos' y dibuja los rectángulos
    for (x, y, ancho_rect, alto_rect) in gatos: 
        # Dibujamos en color rojo (0,0,255) con grosor 3
        cv2.rectangle(img, (x, y), (x + ancho_rect, y + alto_rect), (0, 0, 255), 3) 

    # Guarda el fotograma modificado en el archivo de salida
    grabador.write(img)

    # Muestra el resultado en una ventana
    cv2.imshow('Ejercicio 3 - Deteccion de Gatos', img) 

    # Condición de salida con la tecla ESC (27)
    if cv2.waitKey(1) == 27: 
        print("Proceso interrumpido manualmente.")
        break

# Libera recursos
camara.release() 
grabador.release()  
cv2.destroyAllWindows()
print(f"Vídeo exportado correctamente como: '{video_salida}'\n")
