# YOLO-Object-Detection (Development)

A real-time object detection project built using YOLO and custom screen capture pipelines.

This project was created to study computer vision, dataset creation, model training and real-time inference using custom-trained YOLO models.

The current version focuses on experimentation with object detection workflows, screen capture methods and performance considerations for desktop applications.

## Project Goals

The main purpose of this project is not only to train an object detection model, but also to understand the complete computer vision pipeline from data collection to real-time inference.

Technical goals include:

* Training custom YOLO models.
* Building and organizing datasets.
* Learning image annotation workflows.
* Understanding object detection metrics.
* Experimenting with real-time inference.
* Studying screen capture techniques.
* Optimizing image processing pipelines.
* Learning OpenCV integration.
* Exploring desktop computer vision applications.
* Improving software engineering and problem-solving skills.

## Current Features

* Custom-trained YOLO model.
* Real-time object detection.
* Automated screenshot collection.
* Bounding box visualization.
* Training metrics and evaluation results.
* Experimental WinAPI screen capture implementation.

## Technologies

* Python
* YOLO (Ultralytics)
* OpenCV
* NumPy
* Pillow
* PyAutoGUI
* C
* WinAPI

## Development Environment

The project is currently developed and tested on Windows.

## Project Structure

```text
dataset/
├── data.yaml
└── sample_images/

model/
├── best.pt
└── last.pt

results/
├── boxf1_curve.png
├── boxpr_curve.png
├── confusion_matrix.png
├── labels.jpg
├── results.png
└── train_batch0.jpg

scripts/
├── screenshot.py
├── run_ai_test.py
└── WinAPI_screenshot.c
```

## Training Pipeline

The current workflow consists of:

1. Capturing screenshots.
2. Creating image annotations.
3. Training a YOLO model.
4. Evaluating training metrics.
5. Running real-time inference on screen captures.

## Build / Run

Requirements:

* Python 3.x
* Ultralytics
* OpenCV
* NumPy
* Pillow
* PyAutoGUI

Install dependencies:

```bash
pip install ultralytics opencv-python numpy pillow pyautogui
```

Run inference:

```bash
python scripts/run_ai_test.py
```

Collect screenshots:

```bash
python scripts/screenshot.py
```

Compile the WinAPI experiment:

```bash
gcc scripts/WinAPI_screenshot.c -o main.exe -lgdi32
```

## Current State

**Status:** Prototype / Research Project

The project is currently focused on validating object detection workflows, improving dataset quality and experimenting with different capture and inference approaches.

## Planned Features

* Larger training dataset.
* Improved model accuracy.
* Faster inference pipeline.
* Region-of-interest capture.
* ONNX export support.
* Performance benchmarking.
* Integration into larger computer vision applications.
* Multi-class object detection.
* Automated dataset generation tools.

## Motivation

The primary motivation behind this project is to gain practical experience with computer vision and machine learning by implementing every stage of an object detection workflow.

Rather than relying solely on pretrained models, the project focuses on understanding how datasets are created, how models are trained and how real-time inference systems can be built from scratch.

The long-term goal is to evolve this prototype into a more complete computer vision framework that can be integrated into larger applications.

## Disclaimer

This project was developed exclusively for educational and research purposes related to computer vision, machine learning and real-time image processing.

The training data was collected from game screenshots solely as a controlled environment for object detection experiments. The project is not intended to provide competitive advantages, automation or gameplay assistance in online games.
