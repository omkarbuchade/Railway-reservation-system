# Railway-reservation-system
Railway ticket reservation system using the Nachos operating system which will help the passengers to book their tickets, search train between two stations and get details of particular train schedules including their fare details.

Assuming the followings:
1. Each train has its unique id and route.
2. Train schedule information includes the Train number, Route, arrival, departure time at each station, fares per class, between departure and destination stations, number of seats per class (20: Business, 40: Coach)
3. For each request, unique request id, departure/destination station should be randomly generated (cannot be same as the departure destination), departure time should be randomly generated (cannot be earlier than current time), the class of seat should be randomly generated (Business or Coach), the number of passengers should be randomly generated between 1 and 8, the requests are granted in first come first serve basis

</br>
Following are the important implementation details:

1. The List class is used to store the granted, refused and currently on train requests.

2. The Bitmap class under code/userprog/ to keep track of the availability of seats for trains.

3. Threads to simulate this train reservation system.
- **Admin thread** is responsible for simulating the reservation system, creating Train threads, and creating Reservation threads.
- **Reservation thread** is responsible for generating requests, assigning seats to a request, taking a train and getting a request off.
- **Train thread** is responsible for operating trains in accordance to their schedule, and making passengers to get in or out of the train (N number of threads based on your scheduled trains from the file)

4. The train schedule is in the file 'train_schedule.txt' file located in the root directory.

5. The total simulation summary of the number of granted, refused requests, busiest section for each train, etc can be viewed in the 'simulation summary.pdf' file located in the root directory.

</br>
Simulation details:

1. 5 requests every 10 min. (simulation time unit)

2. The railway ticket reservation simulation is from 6 am to 10 pm.

To start the Nachos OS and begin the simulation in Linux environment execute the following commands on the terminal:

```
navigate to the directory: /code/build.linux
make depend
make
./nachos -K
```
