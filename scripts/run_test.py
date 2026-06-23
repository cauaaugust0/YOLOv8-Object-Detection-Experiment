import time
import os

import cv2
import numpy as np

from PIL import ImageGrab
from ultralytics import YOLO

model = YOLO("model/best.pt")

OUTPUT_DIR = "new_results"

os.makedirs(OUTPUT_DIR, exist_ok=True)

count = 1

while True:
    screenshot = ImageGrab.grab()

    frame = cv2.cvtColor(
        np.array(screenshot),
        cv2.COLOR_RGB2BGR
    )

    results = model.predict(
        source=frame,
        conf=0.5,
        imgsz=320,
        verbose=False
    )

    annotated_frame = results[0].plot()

    output_path = os.path.join(
        OUTPUT_DIR,
        f"imagem{count}.jpg"
    )

    cv2.imwrite(output_path, annotated_frame)

    print(f"[OK] Salvo: {output_path}")

    count += 1

    time.sleep(5)