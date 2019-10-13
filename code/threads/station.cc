//Name: Omkar Buchade
//This file implements all methods defined in the station.h class file.
//Description of each method is given in the station.h class file
#include "station.h"

 int station::getSt_id()
    {
        return st_id;
    }

    void station::setSt_id(int st_id1)
    {
        st_id = st_id1;
    }

    std::string station::getStn_name()
    {
        return stn_name;
    }

    void station::setStn_name(std::string stn_name1)
    {
        stn_name = stn_name1;
    }


    int station::getArrival_time()
    {
        return arrival_time;
    }


    void station::setArrival_time(int arrival_time1)
    {
        arrival_time = arrival_time1;
    }


    int station::getDeparture_time()
    {
        return departure_time;
    }


    void station::setDeparture_time(int departure_time1)
    {
        departure_time = departure_time1;
    }


    int station::getC_fare()
    {
        return c_fare;
    }


    void station::setC_fare(int c_fare1)
    {
        c_fare = c_fare1;
    }


    int station::getB_fare()
    {
        return b_fare;
    }


    void station::setB_fare(int b_fare1)
    {
        b_fare = b_fare1;
    }