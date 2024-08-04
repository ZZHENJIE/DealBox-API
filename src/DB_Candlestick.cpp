#include "DB_Candlestick.h"

using namespace DB_API;

void CandlestickItem::OutPut(std::vector<CandlestickItem> Items){
    printf("Time\tOpen\tClose\tHigh\tLow\tVolume\n");
	for(auto Item : Items){
        printf("%s\t%f\t%f\t%f\t%f\t%lld\n",
            Item.Time.c_str(),
            Item.Open,
            Item.Close,
            Item.High,
            Item.Low,
            Item.Volume
        );
	}
}

CandlestickItem DB_API::DB_Candlestick_Last_Day(std::string Symbol){
    CandlestickItem Item;

    cpr::Response Response = cpr::Get(
        cpr::Url{"https://qt.gtimg.cn/q=us" + Symbol}
    );

    std::vector<std::string> result = SplitString(Response.text, '~');

    Item.Close = std::stof(result[3]);
    Item.Open = std::stof(result[5]);
    Item.Volume = std::stoi(result[6]);

    Item.Time = SplitString(result[30],' ')[0];
    Item.High = std::stof(result[33]);
    Item.Low = std::stof(result[34]);

    return Item;
}

std::vector<CandlestickItem> DB_API::DB_Candlestick_Day(std::string Symbol,time_t Start_Timestamp,time_t End_Timestamp,int ItemCount){
    std::vector<CandlestickItem> Container;
    Container.clear();

    tm StartTime,EndTime;
    gmtime_s(&StartTime,&Start_Timestamp);
    gmtime_s(&EndTime,&End_Timestamp);

    std::string Start = std::to_string(1900 + StartTime.tm_year) + "-";
    Start += std::to_string(StartTime.tm_mon + 1) + "-";
    Start += std::to_string(StartTime.tm_mday);

    std::string End = std::to_string(1900 + EndTime.tm_year) + "-";
    End += std::to_string(EndTime.tm_mon + 1) + "-";
    End += std::to_string(EndTime.tm_mday);

    std::string Param = "us" + Symbol + ".OQ,day," + Start + "," + End + "," + std::to_string(ItemCount) +",qfq";

    cpr::Response Response = cpr::Get(
        cpr::Url{"https://web.ifzq.gtimg.cn/appstock/app/fqkline/get?param=" + Param}
    );

    yyjson_doc* Doc = yyjson_read(Response.text.c_str(), Response.text.size(), YYJSON_READ_NOFLAG);

    yyjson_val * Code = yyjson_obj_get(Doc->root,"code");

    if(yyjson_get_int(Code) == 0){
        yyjson_val * data = yyjson_obj_get(Doc->root,"data");
        data = yyjson_obj_get(data,std::string("us" + Symbol + ".OQ").c_str());

        yyjson_val *val;
        yyjson_arr_iter iter = yyjson_arr_iter_with(yyjson_obj_get(data,"day"));
        while ((val = yyjson_arr_iter_next(&iter))) {
            CandlestickItem Item;
            yyjson_arr_iter Itemiter = yyjson_arr_iter_with(val);
            Item.Time = yyjson_get_str(yyjson_arr_iter_next(&Itemiter));
            Item.Open = std::stof(yyjson_get_str(yyjson_arr_iter_next(&Itemiter)));
            Item.Close = std::stof(yyjson_get_str(yyjson_arr_iter_next(&Itemiter)));
            Item.High = std::stof(yyjson_get_str(yyjson_arr_iter_next(&Itemiter)));
            Item.Low = std::stof(yyjson_get_str(yyjson_arr_iter_next(&Itemiter)));
            Item.Volume = std::stoi(yyjson_get_str(yyjson_arr_iter_next(&Itemiter)));

            Container.push_back(Item);
        }
    }

    yyjson_doc_free(Doc);

    return Container;
}

std::vector<CandlestickItem> DB_API::DB_Candlestick_Day(std::string Symbol,std::string Start_Time,std::string End_Time,int ItemCount){
    std::vector<CandlestickItem> Container;
    Container.clear();

    std::string Param = "us" + Symbol + ".OQ,day," + Start_Time + "," + End_Time + "," + std::to_string(ItemCount) +",qfq";

    cpr::Response Response = cpr::Get(
        cpr::Url{"https://web.ifzq.gtimg.cn/appstock/app/fqkline/get?param=" + Param}
    );

    yyjson_doc* Doc = yyjson_read(Response.text.c_str(), Response.text.size(), YYJSON_READ_NOFLAG);

    yyjson_val * Code = yyjson_obj_get(Doc->root,"code");

    if(yyjson_get_int(Code) == 0){
        yyjson_val * data = yyjson_obj_get(Doc->root,"data");
        data = yyjson_obj_get(data,std::string("us" + Symbol + ".OQ").c_str());

        yyjson_val *val;
        yyjson_arr_iter iter = yyjson_arr_iter_with(yyjson_obj_get(data,"day"));
        while ((val = yyjson_arr_iter_next(&iter))) {
            CandlestickItem Item;
            yyjson_arr_iter Itemiter = yyjson_arr_iter_with(val);
            Item.Time = yyjson_get_str(yyjson_arr_iter_next(&Itemiter));
            Item.Open = std::stof(yyjson_get_str(yyjson_arr_iter_next(&Itemiter)));
            Item.Close = std::stof(yyjson_get_str(yyjson_arr_iter_next(&Itemiter)));
            Item.High = std::stof(yyjson_get_str(yyjson_arr_iter_next(&Itemiter)));
            Item.Low = std::stof(yyjson_get_str(yyjson_arr_iter_next(&Itemiter)));
            Item.Volume = std::stoi(yyjson_get_str(yyjson_arr_iter_next(&Itemiter)));

            Container.push_back(Item);
        }
    }

    yyjson_doc_free(Doc);

    return Container;
}