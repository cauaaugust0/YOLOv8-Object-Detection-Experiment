import time
import pyautogui
import os

output_dir = "screenshots"
os.makedirs(output_dir, exist_ok=True)

count = 1

while True:
    screenshot = pyautogui.screenshot()

    filename = os.path.join(output_dir, f"screenshot{count}.png")
    screenshot.save(filename)

    print(f"[+] Salvo: {filename}")

    count += 1
    time.sleep(2)