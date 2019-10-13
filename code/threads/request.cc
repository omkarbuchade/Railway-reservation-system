//Name: Omkar Buchade
//This file defines methods declared in the request class.
//Description for each method is given in the request.h class file
#include "request.h"
#include <set>
#include <cstdlib>
std::set<std::string> *request::station_names = new set<std::string>;
int request::requests_count=1;


std::set<string>* request::getStation_names()
{
    return station_names;
}

void request::printStationList()
{
    std::set<std::string>::iterator it = station_names->begin();
    while (it != station_names->end())
    {
    std::cout << (*it) << "\t";
    it++;
    }
}

int request::getRequest_id()
{
return request_id;
}

void request::generateRequest(int time)
{
    request_id=requests_count+1000;
    requests_count++;

    departure_time= time+ rand()%(1321-time);
    int sClass=rand()%2;
    if (sClass==0)
        seatClass="Coach"; 
    else
        seatClass="Business";
    
    noPassengers=1+rand()%8;

    int srcIndex= rand()%station_names->size();
    int destIndex=srcIndex;
    while (destIndex==srcIndex)
    {
        destIndex= rand()%station_names->size();
    }
    std::set<std::string>::iterator it = station_names->begin();

    for(int i=srcIndex; i>0;i--)
        it++;
    source=*it;

    it = station_names->begin();
    for(int i=destIndex; i>0;i--)
        it++;
    dest=*it;

    // departure_time=1000;
    // seatClass="Coach"; 
    // noPassengers=4;
    // source="Syracuse";
    // dest="Binghamton";
}

void request::printRequest()
{
    std::cout<<"req id: "<<request_id<<"\n";
    std::cout<<"departure time: "<<departure_time<<"\n";
    std::cout<<"seat class: "<<seatClass<<"\n";
    std::cout<<"no passengers: "<<noPassengers<<"\n";
    std::cout<<"source stn: "<<source<<"\n";
    std::cout<<"dest stn: "<<dest<<"\n";
}

std::string request::getSource()
{
    return source;
}

std::string request::getDest()
{
    return dest;
}

int request::getDeparture_time()
{
    return departure_time;
}

int request::getNoPassengers()
{
    return noPassengers;
}


std::string request::getSeatClass()
{
    return seatClass;
}

void request::setStation_names(std::string stn)
{
    station_names->insert(stn);
}

