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

# Extrae las propiedades nativas del vídeo original para que el de salida sea idéntico
fps_leido = int(camara.get(cv2.CAP_PROP_FPS))      # Cuadros por segundo
ancho = int(camara.get(cv2.CAP_PROP_FRAME_WIDTH))  # Resolución: Ancho en píxeles
alto = int(camara.get(cv2.CAP_PROP_FRAME_HEIGHT))  # Resolución: Alto en píxeles

# Control de seguridad: Si los FPS no se leen bien, asignamos 30 por defecto para evitar el fallo
fps = int(fps_leido) if fps_leido > 0 else 30

# Guardar video de salida
# Obtenemos la ruta absoluta de la carpeta donde se está ejecutando el script
directorio_actual = os.path.dirname(os.path.abspath(__file__))

# Extraemos solo el nombre del archivo de vídeo (eliminando rutas previas si las hay)
nombre_archivo_puro = os.path.basename(nombre_video)
nombre_base, _ = os.path.splitext(nombre_archivo_puro)

# Combinamos todo en una ruta absoluta limpia para Windows
video_salida = os.path.join(directorio_actual, f"resultado_{nombre_base}.avi") # Guarda en formato AVI para máxima compatibilidad con códecs en Windows

# Definimos el códec de compresión de vídeo.
fourcc = cv2.VideoWriter_fourcc(*'XVID')

# Instanciamos el objeto grabador con la ruta, el códec, los FPS y el tamaño de los fotogramas
grabador = cv2.VideoWriter(video_salida, fourcc, fps, (ancho, alto), isColor=True)

# Validación de que el grabador se haya inicializado correctamente en el sistema operativo
if not grabador.isOpened():
    print("[ERROR] No se pudo inicializar el grabador de vídeo. Revisa los permisos de la carpeta.")
    sys.exit(1)

print(f"\n[INFO] Procesando vídeo: '{nombre_video}' ({ancho}x{alto} a {fps} FPS)")
print(f"[INFO] El resultado con las detecciones se guardará en: '{video_salida}'")
print("[INFO] Presiona la tecla 'ESC' en la ventana gráfica para interrumpir el proceso.\n")

#Procesamiento frame a frame del vídeo
while camara.isOpened():
    # .read() devuelve un booleano (hay frame o no) y la matriz de píxeles del frame (img)
    hay_frame, img = camara.read()

    # Si 'hay_frame' es False, significa que el vídeo ha llegado a su fin
    if not hay_frame:
        print("[INFO] Fin del archivo de vídeo alcanzado.")
        break

    # Convertimos el frame a escala de grises para el algoritmo de Viola-Jones
    gris = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Detectamos rostros en el fotograma actual
    faces = modeloCara.detectMultiScale(gris, scaleFactor=1.3, minNeighbors=4)

    # Iteramos sobre cada rostro detectado en el fotograma actual
    for (x, y, w, h) in faces:
        # Dibujamos el rectángulo delimitador sobre el frame original a color (img)
        # Color: Azul (255, 0, 0) en formato BGR. Grosor de línea: 3 píxeles
        cv2.rectangle(img, (x, y), (x + w, y + h), (255, 0, 0), 3)

    # Escribimos el fotograma modificado (con los rectángulos ya pintados) en el archivo de salida
    grabador.write(img)

    # Desplegamos el frame en tiempo real en una ventana interactiva de Windows
    cv2.imshow('Ejercicio 2 - Detección Facial en Vídeo', img)

    # Escuchamos los eventos del teclado durante 1 milisegundo
    key = cv2.waitKey(1)
    # 27 es el código ASCII para la tecla 'Esc' (Escape)
    if key == 27:
        print("[INFO] Proceso interrumpido manualmente por el usuario.")
        break

# Liberar los descriptores para que Windows cierre correctamente los archivos de video
camara.release()
grabador.release()  # Al liberar el grabador se finaliza la escritura física del archivo nuevo
cv2.destroyAllWindows()
print(f"[ÉXITO] Archivo de vídeo exportado correctamente en la raíz del proyecto.\n")