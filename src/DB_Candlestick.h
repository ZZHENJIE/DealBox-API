#pragma once

#include "DB_Core.h"

namespace DB_API{

    struct CandlestickItem final{
    public:
        std::string Time;
        float Open;
        float Close;
        float High;
        float Low;
        uint64_t Volume;
    public:
        static void OutPut(std::vector<CandlestickItem> Items);
    };
    
    CandlestickItem DB_Candlestick_Last_Day(std::string Symbol);
    std::vector<CandlestickItem> DB_Candlestick_Day(std::string Symbol,time_t Start_Timestamp,time_t End_Timestamp,int ItemCount = 30);
    std::vector<CandlestickItem> DB_Candlestick_Day(std::string Symbol,std::string Start_Time,std::string End_Time,int ItemCount = 30);


};