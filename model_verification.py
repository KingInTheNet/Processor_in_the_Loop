import numpy as np
import matplotlib.pyplot as plt
import matlab.engine

def process_output(data):
    res = []
    return res

def write_to_file(data, file_name):
    with open(file_name, "w") as txt_file:
        for line in data:
            txt_file.write(" ".join(line) + "\n") # works with any number of elements in a line

mle = matlab.engine.start_matlab(); # start the matlab engine

configureForDeployment = 0

# Allocate res list to hold the results from 4 calls to sim_the_model
res = [0]*4

res[0] = mle.start_func()
res[1] = mle.model_sim()
# res[2] = mle.model_sim('StopTime',10000)
print(np.array(res[1]["outAngularRate"]["Time"]).flatten().shape)
print(np.array(res[1]["sun_flag"]["Time"]).flatten().shape)
print(np.array(res[1]["w_b_rad_s"]["Data"]).flatten().shape)
data = [0] * 6
data[0] = np.array(res[1]["w_b_rad_s"]["Time"]).flatten()
data[1] = np.array(res[1]["w_b_rad_s"]["Data"]).flatten()[0::3]
data[2] = np.array(res[1]["w_b_rad_s"]["Data"]).flatten()[1::3]
data[3] = np.array(res[1]["w_b_rad_s"]["Data"]).flatten()[2::3]
data[4] = np.array(res[1]["outAngularRate"]["Data"]).flatten()
data[5] = np.array(res[1]["sun_flag"]["Data"]).flatten()
print(data[0].shape)
print(data[1][696969])
# print(data[1][0::3].shape)

plt.figure(1)
plt.plot(data[0],data[1],label="x")
plt.plot(data[0],data[2],label="y")
plt.plot(data[0],data[3],label="z")
plt.xlabel("Time")
plt.ylabel("W rate (rad/s)")

plt.figure(2)
plt.plot(data[0],data[4],label="Angular Rate(deg/s)")
plt.xlabel("Time")
plt.ylabel("Angular Rate(deg/s)")

plt.figure(3)
plt.plot(data[0],data[5],label="Sun_flag")
plt.xlabel("Time")
plt.ylabel("sun_flag")
plt.show()
input("Press enter to close the MATLAB figure and exit ...")
mle.quit() # stop the matlab engin1