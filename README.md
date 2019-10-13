# Railway-reservation-system
Railway ticket reservation system using the Nachos operating system which will help the passengers to book their tickets, search train between two stations and get details of particular train schedules including their fare details.

Assuming the followings:
1. Each train has its unique id and route.
2. Train schedule information includes the following information:
   Train number
   Route (for example, station NYC (Penn st), … , Syracuse, … , Toronto)
   Arrival, departure time at each station
   Fares per class, between departure and destination stations
   Number of seats per class (20: Business, 40: Coach)
   There are two types of seats: business and coach.
   Among the same class, all seats are equally preferable to the passengers.
   20 seats for business class and 40 seats for coach class
   Each seat has unique number
3. 5 requests every 10 min. (simulation time unit)
4. For each request, 
   Unique request id
   Departure/Destination station should be randomly generated (cannot be same as the departure destination)
   Departure time should be randomly generated (cannot be earlier than current time)
   The class of seat should be randomly generated (Business or Coach)
   The number of passengers should be randomly generated between 1 and 8
   Each passenger in the same request has the same itinerary; all passengers in the same party will get off at the same station
   The requests are granted in first come first serve basis
   The system will display all available trains for the request
   One of them will be randomly selected
   If there is no match for departure and destination stations in any route of the system, the request will not be served (refused)
   If there are not enough seats to satisfy a request, that request will not be served (rejected)
  For a refused request, It will be discarded and next request will be examined until there is neither any seat nor request left

The railway ticket reservation simulation is from 6 am to 10 pm.

Following are the important implementation details:
1. The List class is used to store the granted, refused and currently on train requests.
2. The Bitmap class under code/userprog/ to keep track of the availability of seats for trains.
3. Threads to simulate this train reservation system.
    3.1 Admin thread is responsible for simulating the reservation system, creating Train threads, and creating Reservation threads. 
    3.2 Reservation thread is responsible for generating requests, assigning seats to a request, taking a train and getting a request off.
    3.3 Train thread is responsible for operating trains in accordance to their schedule, and making passengers to get in or out of the train (N number of threads based on your scheduled trains from the file)
4. The train schedule is in the file 'train_schedule.txt' file located in the root directory.
5. The total simulation summary of the number of granted, refused requests, busiest section for each train, etc can be viewed in the 'simulation summary.pdf' file located in the root directory.