#pragma once

#include "cpr/cpr.h"
#include "yyjson/yyjson.h"

namespace DB_API{
    struct IPOItem final {
    public:
        std::string Company;
        std::string Symbol;
        std::string Price;
        uint64_t Volume;
        std::string ExpectedDate;
    public:
        static void OutPut(std::vector<IPOItem> Items);
    };

    std::vector<IPOItem> DB_IPO_USA_IPOSCOOP();
};