import serial

arduino_port = "/dev/tty.usbmodem106736801" #serial port of Arduino
baud = 115200 #arduino uno runs at 9600 ba
#fileName="analog-data.csv" #name of the CSV file generated
#fileName="Code/LoggingData/Data/PIDTestx.csv" #name of the CSV file generated
fileName="Code/LoggingData/Data/PIDTorque/MeasuredTorqueTEST2.csv" #name of the CSV file generated

ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
file = open(fileName, "a")
#file.write("P 2.5, I 20, D 0, Tf 0.01, ramp 300" + "\n")
file.write("Time,TargetVelocity,TargetTorque,Measured,Error,alpha,torque" + "\n")
samples = 1000000 #how many samples to collect
print_labels = False
line = 0 #start at 0 because our header is 0 (not real data)
while line <= samples:
    # incoming = ser.read(9999)
    # if len(incoming) > 0:
    if print_labels:
        if line==0:
            print("Printing Column Headers")
        else:
            print("Line " + str(line) + ": writing...")
    getData=ser.readline()
    data=getData[0:][:-2]
    data = getData.decode('utf-8').strip('\r\n')
    print(data)

    file = open(fileName, "a")
    file.write(data + "\n") #write data with a newline
    line = line+1

print("Data collection complete!")
file.close()
