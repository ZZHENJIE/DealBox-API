#include "DB_Events.h"

using namespace DB_API;

void EventItem::OutPut(std::vector<EventItem> Items){
    printf("Country\tTime\tImportance\tActual\tForecast\tPrevious\tTitle\n");
	for(auto Item : Items){
        printf("%s\t%lld\t%d\t%s\t%s\t%s\t%s\n",
            Item.Country.c_str(),
            Item.Time,
            Item.Importance,
            Item.Actual.c_str(),
            Item.Forecast.c_str(),
            Item.Previous.c_str(),
            Item.Title.c_str()
        );
	}
}

std::vector<EventItem> DB_API::DB_Events_Wallstreetcn(time_t Start_Timestamp,time_t End_Timestamp){
    std::vector<EventItem> Container;
    Container.clear();

    cpr::Response Response = cpr::Get(
        cpr::Url{"https://api-one-wscn.awtmt.com/apiv1/finance/macrodatas"},
        cpr::Parameters{ 
            {"start",std::to_string(Start_Timestamp)},
            {"end",std::to_string(End_Timestamp)}
        }
    );

	yyjson_doc* Doc = yyjson_read(Response.text.c_str(), Response.text.size(), YYJSON_READ_NOFLAG);

    yyjson_val* Message = yyjson_obj_get(Doc->root, "message");

    if (strcmp(yyjson_get_str(Message), "OK") == 0) {

        yyjson_val* Items = yyjson_obj_get(yyjson_obj_get(Doc->root, "data"), "items");
        yyjson_val* Value;
        yyjson_arr_iter Iter = yyjson_arr_iter_with(Items);
        while ((Value = yyjson_arr_iter_next(&Iter))) {
            yyjson_val* country = yyjson_obj_get(Value, "country");
            yyjson_val* public_date = yyjson_obj_get(Value, "public_date");
            yyjson_val* title = yyjson_obj_get(Value, "title");
            yyjson_val* unit = yyjson_obj_get(Value, "unit");
            yyjson_val* importance = yyjson_obj_get(Value, "importance");
            yyjson_val* actual = yyjson_obj_get(Value, "actual");
            yyjson_val* forecast = yyjson_obj_get(Value, "forecast");
            yyjson_val* previous = yyjson_obj_get(Value, "previous");

            EventItem Item;

            Item.Country = yyjson_get_str(country);
            Item.Title = yyjson_get_str(title);
            Item.Time = yyjson_get_int(public_date);
            Item.Importance = yyjson_get_int(importance);

            if (strcmp(yyjson_get_str(actual), "") == 0) {
                Item.Actual = "--";
            }else {
                Item.Actual =  std::string(yyjson_get_str(actual)) + yyjson_get_str(unit);
            }

            if (strcmp(yyjson_get_str(forecast), "") == 0) {
                Item.Forecast = "--";
            }else {
                Item.Forecast = std::string(yyjson_get_str(forecast)) + yyjson_get_str(unit);
            }

            if (strcmp(yyjson_get_str(previous), "") == 0) {
                Item.Previous = "--";
            }else {
                Item.Previous = std::string(yyjson_get_str(previous)) + yyjson_get_str(unit);
            }

            Container.push_back(Item);
        }
    }

	yyjson_doc_free(Doc);
    
    return Container;
}