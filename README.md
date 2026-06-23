# YOLO-Object-Detection (Development)

**Status:** Prototype / Research

Hands-on experimentation with computer vision, focused on the complete object detection pipeline: from screen capture and data annotation to training and real-time inference using custom YOLO models.

This project is not intended to be a final application, but rather a learning environment for understanding the challenges of data collection and model training on desktop systems (Windows).

## Current Functionality
- **Data Pipeline:** Automated screenshot collection and dataset organization.
- **Training:** Complete workflow for training YOLO models using Ultralytics.
- **Evaluation:** Generation of training metrics (confusion matrix, precision-recall curves).
- **Basic Inference:** Real-time bounding box visualization using OpenCV.

## Technologies
- **Languages:** Python 3.10.11, C
- **Core:** Ultralytics YOLO, OpenCV, NumPy, PyAutoGUI
- **Environment:** Windows (Development and Testing)

## Project Structure
```text
dataset/          # Images and annotations (YAML format)
model/            # Trained models (.pt)
results/          # Training metric graphs
scripts/          # Python (screenshot, inference, train) and C (WinAPI)
