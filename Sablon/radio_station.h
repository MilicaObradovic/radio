#pragma once
#include <string>
#ifndef STATION_H
#define STATION_H
enum SType{
    AM,
    FM
};

class RadioStation
{
public:
    SType StationType;
    std::string Name;
    int Frequency;
    RadioStation(std::string name, int freq, SType type);
};
#endif