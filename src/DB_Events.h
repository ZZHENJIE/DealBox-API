#pragma once

#include "cpr/cpr.h"
#include "yyjson/yyjson.h"

namespace DB_API{

    struct EventItem final {
    public:
        std::string Country;
        std::string Title;
        time_t Time;
        int Importance;
        std::string Actual;
        std::string Forecast;
        std::string Previous;
    public:
        static void OutPut(std::vector<EventItem> Items);
    };

    std::vector<EventItem> DB_Events_Wallstreetcn(time_t Start_Timestamp,time_t End_Timestamp);
};