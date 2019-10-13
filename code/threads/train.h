//Name: Omkar Buchade
//train.h class is used to store information pertaining to each train

#include "station.h"
#include "list.h"
#include "request.h"
#include "bitmap.h"
#include "thread.h"

class train
{
private:
    List <station *> *trainStations = new List <station *>; // list to store the train route(stations)
    List <request *> *requestQueue = new List <request *>; //approved requests
    List <request *> *requestQueueRefused = new List <request *>; //refused requests
    List <request *> *CurrentlyOnTrain = new List <request *>; //passengers currently on train
    List <Thread *> *reqThreads=new List <Thread *>; //list to store pointers to approved request threads
    Bitmap *seatChart [10][40];
    Bitmap *seatChartBusiness [10][20];

    int noCseats;
    int noBseats;
    int trainId;
    int requests;
    int passengers;
    int requestsArrival;
    int passengersArrival;
    std::string stnName;
    int served_itineary;
    int total_passengers;
    int **busy_stn_matrix;


public:
    train();
    void BitmapInit(); //initialize the bitmap
    void init_matrix(); //initialize buzy station matrix
    void buzyStn(request *); //set buzy station matrix
    int getRequests(); // get number of approved requests
    int getPassengers();//get number of passengers 
    int getRequestsArrival(); //get number of arrival requests 
    int getPassengersArrival(); //get number of passengers arrived at a station
    std::string getStationName(); // get current station name
    void getBuzyStn(); //prints the busiest route
    bool BitmapSet(request *); //sets the bitmap (when passengers takes a seat)
    void BitmapUnset(request *); // unsets bitmap when a request is complete and passenger gets off train
    int getNoCseats(); // get number of coach seats
    void setNoCseats(int );// set number of coach seats
    int getNoBseats();// get number of business seats
    void setNoBseats(int );//set number of busiess seats
    int getTrainId();// get the train id for the train
    void setTrainId(int);//sets a train id
    void addTrainStation(station *);// add station to the route of the train
    List <station *>* getTrainStation();// gets the route
    void addRequest(request *);//add approved request to the queue
    void addRequestDecline(request *);// lists to keep a track of declined requests
    void addOnTrain(request *); //onboard a passenger of train 
    void addRequestThread(Thread *); //append the request thread pointer to a lsit
    List <Thread *> * getRequestThread();//get a list of request thread pointers of requests associated to this train
    List <request *>* getRequestQueue(); //get a list of approved requests
    void removeReqObj(request *); //remove a request when it is served
    bool printStnSummary(int); //prints the departure summary from a station for the train
    bool printStnSummaryArrival(int); //prints arrival stats of passsengers at a station

    int getServed_itineary(); //get served itineary count
    int getTotal_passengers(); //get total passengers 
    void incServed_itineary();//set served itineary count
    void incTotal_passengers(int);//set total passenger count
};