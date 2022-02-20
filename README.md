# Introduction:

This github was created part of the course MGT-555 Innovation & entrepreneurship in Engineering. The goal of the project is to create a prototype that can evaluate the health of the watch on the wrist
This github here contains the data collection and data post-processing steps.

# Data Collection

The file Signal Microphone.ino collects the signal recorded by the microphone of the Arduino and transforms it to a digital  signal.

#  Data  post-processing:

## Chronometry

The folder Chronometry contains the MATLAB Code Timegraph.m that detects the picks of the chronometry and outputs the beat error and the deviation. Graph examples of have been generated to illustrate the purpose of the file

## Noise Cancelling

The Notebook Noise Cancelling shows the different filters developed and used to perform the Noise Cancelling.

## Winding Speed

The notebook  Dataset Creation is the notebook that takes an input 20 seconds of a background of a watch and 10 clicks emitted by the winding speed and generate a dataset that we use for the later processing.

In order to avoid overfitting, we perform Data Augmentation techniques so we are able to generalize on different watches. 
Then, we build the model in our Model folder. Our model is a CNN Deep Learning Model that performs binary classification. Using the spectogram of one second recording of the watch, the model output whether the watch has recharged or not

## Report

In this folder, the Report Generate Notebook generate the report based on all the information that the other steps have gethered.

# Special Thanks

Special thanks to:

Paul Bertusi from Vacheron Constantin
Prof. Véronique Michaud
Prof. Thomas Weber
The Teaching Assistant team

 	 
