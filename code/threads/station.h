//Name: Omkar Buchade
//Station class to store info about trains arriving at this station
#include <iostream>
class station
{
private:
    int st_id; //unique station id 
    std::string stn_name;//station name
    int arrival_time;//arrival time at station
    int departure_time;//departure time at station
    int c_fare;//coach class fare
    int b_fare;//business class fare

public:
    int getSt_id(); //get the station id
    void setSt_id(int st_id);//set station id
    std::string getStn_name();//get station name
    void setStn_name(std::string stn_name);//set station name
    int getArrival_time();//get arrival time at station
    void setArrival_time(int arrival_time);//set arrival tiem at station
    int getDeparture_time();//get departure time from station
    void setDeparture_time(int departure_time);//set departure time from station
    int getC_fare();//get coach fare
    void setC_fare(int c_fare);//set coach fare
    int getB_fare();//get business fare
    void setB_fare(int b_fare);//set business fare
};