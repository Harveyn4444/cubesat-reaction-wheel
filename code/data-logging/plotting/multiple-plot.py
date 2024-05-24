import pandas as pd
from matplotlib import pyplot as plt
from matplotlib.ticker import (MultipleLocator, AutoMinorLocator)

plt.rcParams["figure.figsize"] = [10.00, 5]
#plt.rcParams["figure.figsize"] = [25, 10.0]
plt.rcParams["figure.autolayout"] = True
#cols = ['Desired','Measured','RecordNumber']
#df = pd.read_csv("Code/LoggingData/PIDVelocity1.csv",skiprows=[2], nrows=1000, usecols=cols) #
cols = ['Time','Target','Measured', 'Error']
df1 = pd.read_csv("Code\LoggingData\Data\OpenLoopRC\OpenLoopVelocityFiltered01.csv",skiprows=[1], nrows=100, usecols=cols) #
df3 = pd.read_csv("Code\LoggingData\Data\OpenLoopRC\OpenLoopVelocityFiltered03.csv",skiprows=[1], nrows=100, usecols=cols)
df5 = pd.read_csv("Code\LoggingData\Data\OpenLoopRC\OpenLoopVelocityFiltered05.csv",skiprows=[1], nrows=100, usecols=cols)
df7 = pd.read_csv("Code\LoggingData\Data\OpenLoopRC\OpenLoopVelocityFiltered07.csv",skiprows=[1], nrows=100, usecols=cols)

#print("Contents in csv file:", df)
print("Contents in csv file:")
print(df1)
Time1 = df1['Time']
Target1 = df1['Target']
Measured1 = df1['Measured']
Time3 = df3['Time']
Target3 = df3['Target']
Measured3 = df3['Measured']
Time5 = df5['Time']
Target5 = df5['Target']
Measured5 = df5['Measured']

Time7 = df7['Time']
Target7 = df7['Target']
Measured7 = df7['Measured']



plt.rcParams['toolbar'] = 'None' # Remove tool bar (upper bar)
plt.figure('  | Individual Project | CubeSat Reaction Wheel | Open Loop Velocity Test')#,facecolor='black')
#plt.axhline(y=0.5, color='r', linestyle='-')
plt.plot(Time1, Target1, color = 'red')
plt.plot(Time1, Measured1, color = 'black')#, color = 'white')
plt.plot(Time3, Measured3)#, color = 'white')
plt.plot(Time5, Measured5)#, color = 'white')
plt.plot(Time7, Measured7)#, color = 'white')
#plt.plot(RecordNumber, df.Measures)
#plt.plot(df.RecordNumber, df.Measures)
#df.plot(figsize=(15,5), kind='line',x=2, y=1)
#df.plot(figsize=(15,5), kind='line',x=df.RecordNumber, y=df.Desired)


ax = plt.gca()
#fig, ax = plt.plot( facecolor='black') #Share the same x axis - e.g. time


#plt.xlabel("Time")
#plt.ylabel("Temperature / 0c")


plt.xlabel("Time / ms")
plt.ylabel("Angular Velocity / Rads-1")
plt.legend(['Target Velocity', 'RC = 0.1', 'RC = 0.3', 'RC = 0.5','RC = 0.7'])

ax.set_ylim([-30, 60])
ax.set_title('Target Velocity') 
ax.tick_params(axis='x')
ax.xaxis.set_major_locator(MultipleLocator(10))
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

plt.savefig('Code/LoggingData/Data/TestingRC.png', dpi = 400)

#mng = plt.get_current_fig_manager()
#mng.window.state('zoomed') 
#mng.window.wm_iconbitmap("Avionics\Freezer Test\Data\Logo.ico")
plt.show()