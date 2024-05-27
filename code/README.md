# Code

A collection of cude to use the hardware, and to log the sensor data written to the serial terminal by the micro controller. This was used as a reliable effective method top obtain data during testing. During operation data would be written to the SD card or Flash chip if required. The flash chip was used as the rotation may force the SD Card to come loose and the flash chip provides a more robust solution.

## [Testing](https://github.com/Harveyn4444/cubesat-reaction-wheel/tree/main/code/testing)
Code used by the Teensy to read data from sensors and communicate with the SimpleFOCShield.

## [Data Logging](https://github.com/Harveyn4444/cubesat-reaction-wheel/tree/main/code/data-logging)
The code reads the serial port the microcontroller is connected to (shown in Arduino IDE) and stores this data in a CSV file. This data/csv file is stored in the data directory and is called again within the scripts. This is to keep the data organised and seperated form the main scripts. The CSV files are manually renamed/adjusted to reflect the parameters of the code in which it is recording.

```
serial-to-csv.py
```
Reads the serial port created by the microcontroller and logs this data to the CSV file for plotting later. To end the process in the terminal press cntrl + C. serial-to-csv-torque.py performs the same tasks just saves the data as different files and was used seperately to keep things tidy.

```
plot.py
```
Plots a single graph and saves the figure under the name of the CSV file as an image. The same is for plot-alpha.py, this was just to plot the angular acceleration graphs.

```
multiple-plot.py
```
Plots multiple bits of data on one graph, used to show the change in filtering of the data by changing the RC value.
