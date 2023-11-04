#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

#include <spdlog/spdlog.h>
#include <json/json.h>

struct RecordInfo
{
	std::string source = "";
	int cash = 0;
	std::string description = "";
};

void logFlow(std::map<std::string, std::vector<RecordInfo>> map);

int main(int argc, char ** argv)
{
	spdlog::set_pattern("%v");

	spdlog::info("Start loading record from RecordInfo.json");
	
	Json::Value recVal;

	//========== Open file
	{
		std::string recSrc = "";

		std::ifstream file("RecordInfo.json", std::ios::in);
		if (!file.is_open())
		{
			spdlog::warn("Load RecordInfo.json error.");
			spdlog::warn("Use arg -generate to generate default RecordInfo.json");
			file.close();
			return -1;
		}

		for (std::string i = ""; std::getline(file, i); recSrc += i);
		file.close();
		
		Json::Reader reader;
		reader.parse(recSrc, recVal);
	}
	//==========

	//========== Source name, Cash date =========
	std::map<std::string, int> srcMap;

	//========== Date, details ==========
	std::map<std::string, std::vector<RecordInfo>> flowMap;

	//========== Json object to map/vector
	{
		Json::Value source = recVal["source"];
		Json::Value flow = recVal["flow"];
	
		//========== Source read
		for (int i = 0; i < source.size(); i++)
		{
			std::string name = source[i]["name"].asString();
			int cash = source[i]["cash"].asInt();
			srcMap.insert(std::pair(name, cash));
		}
		//==========

		//========== flow read
		for (int i = 0; i < flow.size(); i++)
		{
			std::string date;
			RecordInfo rec;
			std::vector<RecordInfo> info;
		
			date = flow[i]["date"].asString();
			rec.source = flow[i]["source"].asString();
			rec.cash = flow[i]["cash"].asInt();
			rec.description = flow[i]["description"].asString();

			std::map<std::string, std::vector<RecordInfo>>::iterator it = flowMap.find(date);
			if (it == flowMap.end())
			{
				info.push_back(rec);
				flowMap.insert(std::pair(date, info));
			}
			else
			{
				it->second.push_back(rec);
			}
		}
		//==========
	}
	//==========

	spdlog::info("Finish loading");

	logFlow(flowMap);

	return 0;
}


void logFlow(std::map<std::string, std::vector<RecordInfo>> map)
{
	std::stringstream out;
	for (std::pair data : map)
	{
		out << data.first << ":\n";
		
		for (RecordInfo info : data.second)
		{
			out << "\t" << "Source: " << info.source << "\n";
			out << "\t" << "Cash: " << info.cash << "\n";
			out << "\t" << "description: " << info.description << "\n";
			out << "\n";
		}
	}

	spdlog::info(out.str());
};