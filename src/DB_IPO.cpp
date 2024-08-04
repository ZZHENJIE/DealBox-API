#include "DB_IPO.h"

using namespace DB_API;

void IPOItem::OutPut(std::vector<IPOItem> Items){
    printf("Symbol\tPrice\tVolume\tExpectedDate\tCompany\n");
	for(auto Item : Items){
        printf("%s\t%s\t%lld\t%s\t%s\n",
            Item.Symbol.c_str(),
            Item.Price.c_str(),
            Item.Volume,
            Item.ExpectedDate.c_str(),
            Item.Company.c_str()
        );
	}
}

std::vector<IPOItem> DB_API::DB_IPO_USA_IPOSCOOP(){
    std::vector<IPOItem> Container;
    Container.clear();

    cpr::Response Response = cpr::Get(
        cpr::Url{"http://114.132.47.35/stock/ipolist"}
    );

    yyjson_doc* Doc = yyjson_read(Response.text.c_str(), Response.text.size(), YYJSON_READ_NOFLAG);

    yyjson_val *val;
    yyjson_arr_iter iter = yyjson_arr_iter_with(Doc->root);
    while ((val = yyjson_arr_iter_next(&iter))) {
        yyjson_val * Company = yyjson_obj_get(val,"Company");
        yyjson_val * Symbol = yyjson_obj_get(val,"Symbol");
        yyjson_val * PriceLow = yyjson_obj_get(val,"PriceLow");
        yyjson_val * PriceHigh = yyjson_obj_get(val,"PriceHigh");
        yyjson_val * Shares = yyjson_obj_get(val,"Shares(Millions)");
        yyjson_val * ExpectedToTrade = yyjson_obj_get(val,"ExpectedToTrade");

        Container.push_back({
            yyjson_get_str(Company),
            yyjson_get_str(Symbol),
            std::string(yyjson_get_str(PriceLow)) + "-" + yyjson_get_str(PriceHigh),
            uint64_t(std::stof(yyjson_get_str(Shares)) * 1000000),
            yyjson_get_str(ExpectedToTrade)
        });
    }

    yyjson_doc_free(Doc);

    return Container;
}