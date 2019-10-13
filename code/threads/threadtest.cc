//Name: Omkar Buchade
//Lab: 2

#include "kernel.h"
#include "main.h"
#include "thread.h"
#include <fstream>
#include <sstream>
#include "list.h"
#include "train.h"
#include <vector>
#include <unistd.h>

List <Thread *> * TrainthreadList = new List <Thread *>(); //lsit to store train threads
int time_ctr=360; // time start value 360 (6.00 am) 
request *GReqObj;
train *currTrain =new train();
//flags and counters
bool Tfound= false;
bool train_arrived=false;
bool train_dep=false;
static int totRequests=0;
static int GrantRequest=0;
int ReqGrant=0;
int ReqRefused=0;
int reqFlag=0;

List <train *>* loadData(List <std::string> *tokenListMain) //load the data retrieved from train schedule file to train objects
{
    List <train *> *trainList = new List <train *>;
    List <std::string> *tokenList = tokenListMain;
    while(!tokenList->IsEmpty())
    {
        if(tokenList->Front()=="--")
        {
            cout<<tokenList->Front()<<"\n";
            train *trainObj=new train();

            tokenList->RemoveFront();
            trainObj->setTrainId(atoi(tokenList->RemoveFront().c_str()));
            trainObj->setNoBseats(atoi(tokenList->RemoveFront().c_str()));
            trainObj->setNoCseats(atoi(tokenList->RemoveFront().c_str()));

            while(!tokenList->IsEmpty() && tokenList->Front()!="--")
            {
                station *newStn = new station();
                newStn ->setSt_id(atoi(tokenList->RemoveFront().c_str()));
                newStn ->setStn_name(tokenList->RemoveFront().c_str());
                newStn ->setArrival_time(atoi(tokenList->RemoveFront().c_str()));
                newStn ->setDeparture_time(atoi(tokenList->RemoveFront().c_str()));
                newStn ->setC_fare(atoi(tokenList->RemoveFront().c_str()));
                newStn ->setB_fare(atoi(tokenList->RemoveFront().c_str()));
                trainObj->addTrainStation(newStn);
            }
            trainList->Append(trainObj);
            trainObj->BitmapInit();
        }
    }
    return trainList;
}


List <std::string> * fileParse() //parse all the file contents and store them in a list
{
List <std::string> *tokenList = new List <std::string>();
std::ifstream f;
    f.open("../../train_schedule.txt");
    char ch[255];    
    while (f.getline(ch,255,'\n')) 
        {
            std::istringstream sbStr(ch);
             for (std::string tokens; sbStr >> tokens; )
             {
                tokenList->AppendDup(tokens); 
             }
        }
    f.close();
return tokenList;
} 

void printTrainSummary(List <train *> *trainList)    //print train stations for each train
{
    ListIterator<train *> *itr = new ListIterator <train *>(trainList);
    //cout<<"Num in list "<<trainList->NumInList()<<"\n";
    while (!itr->IsDone())
    {
        train *obj=itr->Item();
        cout<<"train id is: "<<obj->getTrainId()<< "\n";

        List <station *> *trainStations = obj->getTrainStation();
        ListIterator<station *> *itrstation = new ListIterator <station *>(trainStations);
        while(!itrstation->IsDone())
        {
            station *stnObj = itrstation->Item();
            std::cout<<"  "<<stnObj->getStn_name() << "  ";

            itrstation->Next();
        }
        itr->Next();
        std::cout<<"\n"; 
    }
     
}

bool traincheck(train *train) //check if a train is available for a given request
{    
    List <station *> *trainStations = train->getTrainStation();
    ListIterator<station *> *Stnitr = new ListIterator <station *>(trainStations);
    bool srcFlag=FALSE;
    while(!Stnitr->IsDone())
    {
        station *Stnobj= Stnitr->Item(); 
        if(Stnobj->getStn_name()==GReqObj->getSource() && GReqObj->getDeparture_time() < Stnobj->getDeparture_time())
            srcFlag=TRUE;

        if(srcFlag && Stnobj->getStn_name()==GReqObj->getDest())
        {
            return TRUE;
        }
        Stnitr->Next();
    }
    return FALSE;
}




void threadInit(train *obj) //function which is executed by train threads
{
    kernel->interrupt->SetLevel(IntOff);
    kernel->currentThread->Sleep(FALSE); //sleep the train thread
    obj->init_matrix();
    
    while (true)
    {  
        if(obj->printStnSummaryArrival(time_ctr) && !train_dep)
        {
        std::cout<<"------------------- Departures -------------------\n";
        std::cout<<"Passengers boarding train id: "<<obj->getTrainId()<<" at station: "<<obj->getStationName()<<" at "<< (time_ctr/60)<<"."<<(time_ctr%60) <<"\n";
        obj->addOnTrain(GReqObj);

        std::cout<<"# of itineary: "<<obj->getRequestsArrival()<<"\n";
        std::cout<<"# of passengers boarding: "<<obj->getPassengersArrival()<<"\n \n";
        train_dep=true;
        }  

        if(obj->printStnSummary(time_ctr) && !train_arrived)
        {
        //obj->printStnSummaryArrival(time_ctr);
            std::cout<<"------------------- Arrivals -------------------\n";
        std::cout<<"Passengers getting of train id: "<<obj->getTrainId()<<" at station: "<<obj->getStationName()<<" at "<< (time_ctr/60)<<"."<<(time_ctr%60) <<"\n";
        std::cout<<"# of itineary: "<<obj->getRequests()<<"\n";
        std::cout<<"# of passengers getting off: "<<obj->getPassengers()<<"\n \n";
        train_arrived=true;
        }


        List <station *> *trainStations = obj->getTrainStation();
        List <request *> *requestQueue =  obj->getRequestQueue();
        ListIterator<station *> *Stnitr = new ListIterator <station *>(trainStations);
        ListIterator<request *> *Reqitr = new ListIterator <request *>(requestQueue);

        while(!Stnitr->IsDone())
        {
            station *Stnobj= Stnitr->Item();         
            if(time_ctr==Stnobj->getDeparture_time())
            {
                while(!Reqitr->IsDone())
                {
                    request *ReqObj=Reqitr->Item();
                    if(ReqObj->getDest()==Stnobj->getStn_name())
                    {
                        obj->BitmapUnset(ReqObj);
                    }
                    Reqitr->Next();
                }
            }
            Stnitr->Next();
        }
        if(!Tfound)
        {
            bool hit= traincheck(obj); // check if train available in the route
            if(hit)
            {
                //std::cout<<" ********* train id for time: "<<time_ctr<<" found: "<<obj->getTrainId()<<"\n";
                bool set=obj->BitmapSet(GReqObj); //check if there is availalbiility in the given train
                if(set)
                {
                    obj->addRequest(GReqObj);
                    Tfound= true;   
                    GrantRequest++;
                    ReqGrant++;
                    obj->incServed_itineary();
                    obj->incTotal_passengers(GReqObj->getNoPassengers());
                    std::cout<<"Request id: "<<GReqObj->getRequest_id()<<" train available: "<<obj->getTrainId()<<"\n";
                     obj->buzyStn(GReqObj);
                    currTrain=obj;
                    reqFlag=1;
                }
            }
            else{
                    obj->addRequestDecline(GReqObj);
                    ReqRefused++;
                }
        }
        kernel->currentThread->Sleep(FALSE); //sleep the train thread
    }   

}

void createTrainThread(List <train *> *trainList) //create train threads
{

    ListIterator<train *> *itr = new ListIterator <train *>(trainList);
    for (int i=0;i<trainList->NumInList();i++)
    {
        train *obj=itr->Item();  
        Thread *t1 = new Thread("train_thread ");  
        t1->Fork((VoidFunctionPtr) threadInit, obj);
        itr->Next();
        TrainthreadList->Append(t1);
    }


    kernel->currentThread->Yield(); //yield the admin thread

}

void createStationList(List <train *> *trainList) //create a set consisting of station names
{
    request *reqObj = new request();
    ListIterator<train *> *itr = new ListIterator <train *>(trainList);
    while (!itr->IsDone())
    {
        train *obj=itr->Item();
        List <station *> *trainStations = obj->getTrainStation();
        ListIterator<station *> *Stnitr = new ListIterator <station *>(trainStations);
        while (!Stnitr->IsDone())
        {
            station *stnObj=Stnitr->Item();
            std::string stn = stnObj->getStn_name();
            reqObj->setStation_names(stn);
            Stnitr->Next();
        }
        itr->Next();
    }   
}


void reservationInit() // method executed by reservation/request thread
{
    reqFlag=0;
    request *reqObj = new request();
    reqObj->generateRequest(time_ctr);
    totRequests++;
    Tfound= false;
    
    ListIterator <Thread *> *Threaditr = new  ListIterator <Thread *>(TrainthreadList);
    

    while (!Threaditr->IsDone())
    {
        Thread *currThread= Threaditr->Item();
        kernel->interrupt->SetLevel(IntOff); 
        kernel->scheduler->ReadyToRun(currThread);
        Threaditr->Next();
    }
    GReqObj=reqObj;
    kernel->currentThread->Yield();
    if(reqFlag=0)
        kernel->currentThread->Finish();
    else
    {
        currTrain->addRequestThread(kernel->currentThread);
        kernel->interrupt->SetLevel(IntOff);
        kernel->currentThread->Sleep(false);
    }

}

void createRequestThread() //create new request thread
{
    Thread *r1 = new Thread("reservation_thread ");
    r1->Fork((VoidFunctionPtr) reservationInit, NULL);
}


void
AdminThread() //admin thread
{
    List <std::string> *tokenList=fileParse();
    List <train *> *trainList=loadData(tokenList);
    std::cout<<"Train schedule is \n";
    printTrainSummary(trainList);
    createTrainThread(trainList);
    createStationList(trainList); 
    std::cout<<"\n";
    while(time_ctr<=1320) //1320 = 10.pm
    {
        train_arrived=false;
        train_dep=false;
        ReqGrant=0;
        ReqRefused=0;

        for(int i=0;i<5;i++)
        {
            createRequestThread();
            kernel->currentThread->Yield();
        }
        std::cout<<"------------ time now is: "<< (time_ctr/60)<<"."<<(time_ctr%60)<<"------------ \n";
        std::cout<<"Request granted: "<<ReqGrant<<"\n";
        std::cout<<"Request refused: "<<5-ReqGrant<<"\n \n";

        time_ctr=time_ctr+10;
    }

    std::cout<<"************** Entire simulation summary ************** \n";
    std::cout<<"Total # of requests: "<<totRequests<<"\n";
    std::cout<<"Total # of granted requests: "<<GrantRequest<<"\n";


    std::cout<<"\n ********** Train simulation summary ********** \n \n";

    ListIterator<train *> *itr = new ListIterator <train *>(trainList);
   while(!itr->IsDone())
    {
        train *obj=itr->Item();  
        std::cout<<"Train id: "<<obj->getTrainId()<<"\n";
        std::cout<<"Total # of served itineary: "<<obj->getServed_itineary()<<"\n";
        std::cout<<"Total # of passengers: "<<obj->getTotal_passengers()<<"\n";
        obj->getBuzyStn();
        itr->Next();
    }
}

void
ThreadTest()
{
    char name[20] ="admin_thread";
    Thread *t = new Thread(name);
    t->Fork((VoidFunctionPtr) AdminThread, NULL);
}