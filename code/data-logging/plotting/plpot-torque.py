import pandas as pd
from matplotlib import pyplot as plt
from matplotlib.ticker import (MultipleLocator, AutoMinorLocator)

print("START")

plt.rcParams["figure.figsize"] = [7.00, 3.50]
#plt.rcParams["figure.figsize"] = [25, 10.0]
plt.rcParams["figure.autolayout"] = True
#cols = ['Desired','Measured','RecordNumber']
#df = pd.read_csv("Code/LoggingData/PIDVelocity1.csv",skiprows=[2], nrows=1000, usecols=cols) #
cols = ['Time','TargetVelocity','TargetTorque','Measured', 'Error', 'alpha', 'torque']
df = pd.read_csv("Code/LoggingData/Data/PIDTorque/MeasuredTorqueTEST2.csv",skiprows=[1], nrows=1000, usecols=cols) #

#print("Contents in csv file:", df)
print("Contents in csv file:")
print(df)
Time = df['Time']
TargetVelocity = df['TargetVelocity']
TargetTorque = df['TargetTorque']
Measured = df['Measured']
Error = df['Error']
alpha = df['alpha']
Measuredtorque = df['torque']


plt.rcParams['toolbar'] = 'None' # Remove tool bar (upper bar)
plt.figure('  | Individual Project | CubeSat Reaction Wheel | PID Torque Test')#,facecolor='black')

#plt.axhline(y=0, color='blue')
plt.plot(Time, TargetTorque, color = 'red')
plt.plot(Time, Measuredtorque, color = 'black')#, color = 'white')
#plt.plot(RecordNumber, df.Measures)
#plt.plot(df.RecordNumber, df.Measures)
#df.plot(figsize=(15,5), kind='line',x=2, y=1)
#df.plot(figsize=(15,5), kind='line',x=df.RecordNumber, y=df.Desired)

ax = plt.gca()
#fig, ax = plt.plot( facecolor='black') #Share the same x axis - e.g. time


#plt.xlabel("Time")
#plt.ylabel("Temperature / 0c")


plt.xlabel("Time / ms")
plt.ylabel("Torque")

ax.set_ylim([-0.25, 0.25])
ax.set_title('Target Torque') 
ax.tick_params(axis='x')
ax.xaxis.set_major_locator(MultipleLocator(100))
ax.set_xlim(xmin=0)

""" ax.set_title('Temperature', color = 'white')
ax.xaxis.label.set_color('white')
ax.tick_params(axis='x', colors='white')
ax.yaxis.set_major_locator(MultipleLocator(10))
ax.yaxis.set_major_formatter('{x:.0f}')
ax.tick_params(axis='y', colors='white')

ax.set_facecolor('black')

ax.spines['bottom'].set_color('#FF3E00AA')
ax.spines['top'].set_color('#FF3E00AA')
ax.spines['right'].set_color('#FF3E00AA')
ax.spines['left'].set_color('#FF3E00AA')
 """
#plt.figure.canvas.manager.set_window_title('  |Peryton Space | Weather Balloon Project | Data Dashboard Freezer Test')
#plt.figure.tight_layout()

#plt.savefig('Code/LoggingData/Data/PIDTorque/PID_torque_TEST2.png', dpi = 400)

#mng = plt.get_current_fig_manager()
#mng.window.state('zoomed') 
#mng.window.wm_iconbitmap("Avionics\Freezer Test\Data\Logo.ico")
plt.show()