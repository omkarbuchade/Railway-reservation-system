//Name: Omkar Buchade
//train.cc defines all methods defined in the train class in train.h file.
//Description for each method is available in the train.h file

#include "train.h"
#include "thread.h"
#include <set>


train::train()
{
    requests=0;
    passengers=0;
    served_itineary=0;
    total_passengers=0;
}

void train::init_matrix()
{
    int sz = int(trainStations->NumInList());
    busy_stn_matrix = new int* [sz];
    for(int i=0;i<sz;i++)
    {
        busy_stn_matrix[i]= new int [sz];
        for(int j=0; j<sz; j++)
        {
            busy_stn_matrix[i][j]=0;
        }
    }
}
void train::buzyStn( request *requestObj)
{
    std::set <std::string> stnNames;
    ListIterator<station *> *Stnitr = new ListIterator <station *>(trainStations);
    while(!Stnitr->IsDone())
    {
        station *stnObj=Stnitr->Item();
        stnNames.insert(stnObj->getStn_name());
        Stnitr->Next();
    }
      
    
    std::set<std::string>::iterator it = stnNames.begin();
    std::string srcStn=requestObj->getSource();
    std::string destStn=requestObj->getDest();

    int srcIndex=0;
    int destIndex=0;
    for(int i=0;i<stnNames.size();i++)
    {
        if(*it==srcStn)
            srcIndex=i;
        if(*it==destStn)
            destIndex=i;
        it++;
    }
    
    busy_stn_matrix[srcIndex][destIndex]= busy_stn_matrix[srcIndex][destIndex]+1; 
}


void train::getBuzyStn()
{
    std::string srcStn;
    std::string destStn;

    int max=-999;
    int maxI;
    int maxJ;
    request *requestObj=new request;

    std::set <std::string> stnNames;
    ListIterator<station *> *Stnitr = new ListIterator <station *>(trainStations);
    while(!Stnitr->IsDone())
    {
        station *stnObj=Stnitr->Item();
        stnNames.insert(stnObj->getStn_name());
        Stnitr->Next();
    }
      

    std::set<std::string>::iterator it = stnNames.begin();
    for(int i=0; i<int(trainStations->NumInList());i++)
    {
        for(int j=0; j<int(trainStations->NumInList()); j++)
        {
            if(max<busy_stn_matrix[i][j])
            {
                max= busy_stn_matrix[i][j];
                maxI=i;
                maxJ=j;
            }
        }
    } 

    for(int i=0;i<stnNames.size();i++)
    {
        if(i==maxI)
            srcStn=*it;
        if(i==maxJ)
            destStn=*it;
        it++;
    }
    if(srcStn!=destStn)
        std::cout<<"Busiest section is: "<<srcStn<<" to "<<destStn<<"\n \n";
}


int train::getServed_itineary()
{
    return served_itineary;
}
int train::getTotal_passengers()
{
    return total_passengers;
}

void train::incServed_itineary()
{
    served_itineary++;
}

void train::incTotal_passengers(int pass)
{
    total_passengers=total_passengers+pass;
}

void train::BitmapInit()
{
    for (int i = 0; i < trainStations->NumInList(); i++)
    {
        *seatChart[i]=new Bitmap(40);
        *seatChartBusiness[i]= new Bitmap(20);
    }
}
void train::addTrainStation(station *obj)
{
    trainStations->Append(obj);
}

List <station *>* train:: getTrainStation()
{
    return trainStations;
}

List <request *>* train:: getRequestQueue()
{
    return requestQueue;
}

void train::addRequest(request *obj)
{
    requestQueue->Append(obj);
}

void train::addRequestDecline(request *obj)
{
    requestQueueRefused->Append(obj);
}

void train::addOnTrain(request *obj)
{
    CurrentlyOnTrain->Append(obj);
}

void train::addRequestThread(Thread *t1)
{
    reqThreads->Append(t1);
}

List <Thread *> * train::getRequestThread()
{
    return reqThreads;
}


 int train::getNoCseats()
    {
        return noCseats;
    }


    void train::setNoCseats(int noCseats1)
    {
        noCseats = noCseats1;
    }


    int train::getNoBseats()
    {
        return noBseats;
    }

    void train::setNoBseats(int noBseats1)
    {
        noBseats = noBseats1;
    }

    int train::getTrainId()
    {
        return trainId;
    }

    void train::setTrainId(int trainId1)
    {
        trainId = trainId1;
    }

    bool train::BitmapSet(request * reqObj)
    { 
        ListIterator<station *> *Stnitr = new ListIterator <station *>(trainStations);
        int srcIndex;
        int destIndex;
        for (int i=0; i<trainStations->NumInList(); i++)
        {
            station *StnObj= Stnitr->Item();
            if(reqObj->getSource()==StnObj->getStn_name())
                srcIndex=i;
            if(reqObj->getDest()==StnObj->getStn_name())
            {
                destIndex=i;
                break;
            }
            Stnitr->Next();
        }
        int seats=0;
        //std::cout<<"Class is: "<<reqObj->getSeatClass()<<"\n";
        
        if(reqObj->getSeatClass()=="Coach")
        {
            int avail_seats=999;
            for(int i=srcIndex;i<destIndex;i++)
            {
                //std::cout<<"Available seats now at stn index "<<i<<" are: "<<seatChart[i][0]->NumClear()<<"\n";
                if(avail_seats>seatChart[i][0]->NumClear())
                {
                avail_seats=seatChart[i][0]->NumClear();
                }
            }
            //std::cout<<"Gross available seats for itineary "<<avail_seats<<"\n";
            if(avail_seats>=reqObj->getNoPassengers())
            {
                for(int i=srcIndex;i<destIndex;i++)
                {
                int passengers=reqObj->getNoPassengers();
                    while(passengers>0)
                    {
                        for (int j =0;j<40;j++)
                        {
                            if(!seatChart[i][0]->Test(j))
                            {
                                //std::cout<<"bitmap set \n";
                                seatChart[i][0]->Mark(j);
                                //std::cout<<"j value is: "<<j<<"\n";
                                break;
                            }
                        }
                        passengers--;
                    }
                }
                return true;
             }
            else
            {
                //std::cout<<"train full. No of passengs incoming:  "<<reqObj->getNoPassengers()<<"\n";
                return false;
            }
        }
        else
        {
        int avail_seats=999;
        for(int i=srcIndex;i<destIndex;i++)
        {
            //std::cout<<"Available Business seats at stn index "<<i<<" are: "<<seatChartBusiness[i][0]->NumClear()<<"\n";
            if(avail_seats>seatChartBusiness[i][0]->NumClear())
            {
            avail_seats=seatChartBusiness[i][0]->NumClear();
            }
        }
        //std::cout<<"Gross available seats for business itineary "<<avail_seats<<"\n";
        if(avail_seats>=reqObj->getNoPassengers())
        {
            for(int i=srcIndex;i<destIndex;i++)
            {
            int passengers=reqObj->getNoPassengers();
                while(passengers>0)
                {
                for (int j =0;j<20;j++)
                {
                    if(!seatChartBusiness[i][0]->Test(j))
                    {
                        //std::cout<<"bitmap set \n";
                        seatChartBusiness[i][0]->Mark(j);
                        //std::cout<<"j value is: "<<j<<"\n";
                        break;
                    }
                }
                passengers--;
                }
            }
            return true;
        }
        else
        {
            //std::cout<<"train full. No of business passengs incoming:  "<<reqObj->getNoPassengers()<<"\n";
            return false;
        }
    return false;
    } 

}

void train::removeReqObj(request *obj)
{
    requestQueue->Remove(obj);
}

void train::BitmapUnset(request *reqObj)
{ 
        ListIterator<station *> *Stnitr = new ListIterator <station *>(trainStations);
        int srcIndex;
        int destIndex;
        for (int i=0; i<trainStations->NumInList(); i++)
        {
            station *StnObj= Stnitr->Item();
            if(reqObj->getSource()==StnObj->getStn_name())
                srcIndex=i;
            if(reqObj->getDest()==StnObj->getStn_name())
            {
                destIndex=i;
                break;
            }
            Stnitr->Next();
        }
        //int seats=0;
        //std::cout<<"Class is: "<<reqObj->getSeatClass()<<"\n";
        
        if(reqObj->getSeatClass()=="Coach")
        {
            for(int i=srcIndex;i<destIndex;i++)
            {
            int passengers=reqObj->getNoPassengers();
                while(passengers>0)
                {
                    for (int j =0;j<40;j++)
                    {
                        if(seatChart[i][0]->Test(j))
                        {
                            //std::cout<<"bitmap unset \n";
                            seatChart[i][0]->Clear(j);
                            break;
                        }
                    }
                    passengers--;
                   
                }
                
            }
        }
        else
        {
            for(int i=srcIndex;i<destIndex;i++)
            {
            int passengers=reqObj->getNoPassengers();
                while(passengers>0)
                {
                    for (int j =0;j<20;j++)
                    {
                        if(seatChartBusiness[i][0]->Test(j))
                        {
                            //std::cout<<"bitmap unset \n";
                            seatChartBusiness[i][0]->Clear(j);
                            //std::cout<<"j value is: "<<j<<"\n";
                            break;
                        }
                    }
                    passengers--;

                }
            }
            return;
        }
}

bool train::printStnSummary(int time_ctr)
{
    ListIterator<station *> *Stnitr = new ListIterator <station *>(trainStations);
    //std::cout<<"num of stations are: "<<trainStations->NumInList()<<"\n";
    ListIterator<request *> *Reqitr = new ListIterator <request *>(requestQueue);
    bool flagHit=false;
    requests=0;
    //stnName="";
    while(!Stnitr->IsDone())
    {
        passengers=0;
        station *Stnobj= Stnitr->Item();
        if(Stnobj->getDeparture_time() ==time_ctr)
        {
            stnName=Stnobj->getStn_name();
            //std::cout<<"------------------> "<<stnName<< "\n";         
            while(!Reqitr->IsDone())
            {
                request *reqObj=Reqitr->Item();
                if(reqObj->getDest()==Stnobj->getStn_name())
                {
                    requests++;
                    passengers=passengers+reqObj->getNoPassengers();
                    flagHit=true;
                }
                Reqitr->Next();
            }
        }
        if(flagHit)
        {
            return true;
        }
        Stnitr->Next();
    }

}

bool train::printStnSummaryArrival(int time_ctr)
{
    ListIterator<station *> *Stnitr = new ListIterator <station *>(trainStations);
    ListIterator<request *> *Reqitr = new ListIterator <request *>(requestQueue);
    bool flagHitArrival=false;
    requestsArrival=0;
    while(!Stnitr->IsDone())
    {
        passengersArrival=0;
        station *Stnobj= Stnitr->Item();
        if(Stnobj->getArrival_time() ==time_ctr)
        {
            stnName=Stnobj->getStn_name();
            while(!Reqitr->IsDone())
            {
                request *reqObj=Reqitr->Item();
                if(reqObj->getSource()==Stnobj->getStn_name())
                {
                    requestsArrival++;
                    passengersArrival=passengersArrival+reqObj->getNoPassengers();
                    flagHitArrival=true;
                }
                Reqitr->Next();
            }
        }
        if(flagHitArrival)
        {
            return true;
        }
        Stnitr->Next();
    }

}


int train::getPassengers()
{
    return passengers;
}
int train::getRequests()
{
    return requests;
}

int train::getPassengersArrival()
{
    return passengersArrival;
}
int train::getRequestsArrival()
{
    return requestsArrival;
}

std::string train::getStationName()
{
    return stnName;
}