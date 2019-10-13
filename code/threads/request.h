//Name: Omkar Buchade
// request class to generate requests
#include<iostream>
#include "list.h"
#include <set>

class request
{
private:
    int request_id; //unique request id for each request
    //static int requests_count;
    static int request_declined; //declined request count
    static int requests_count; //approved request count
    std::string source; 
    std::string dest;
    int departure_time;
    int noPassengers;
    std::string seatClass;
    static std::set<std::string> *station_names; //storing all the stations our train serves

public:
    void setStation_names(std::string); //store all the naems of stations our train serves in a set
    std::set <std::string>* getStation_names(); //get the station name
    void printStationList(); //prints station list
    void generateRequest(int); // generate new request
    void printRequest(); //prints generated request
    int getRequest_id();//get unique request id of request 
    void setRequest_approved();//set aproved request count
    void setRequests_count();//set total request count
    int getNoPassengers();//get number of passengers in this request/itineary
    std::string getSource();//get soruce station of request
    std::string getDest();//get destination station of request
    std::string getSeatClass(); //get seat class of passenger
    int getDeparture_time(); //get departure time of request
};