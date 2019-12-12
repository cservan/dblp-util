#include <iostream>
#include <string>
#include <set>
#include <tinyxml2.h>
#include <nlohmann/json.hpp>

int main(int argc, char** argv)
{
    // Obtain the path for the XML document
    if (argc != 2)
    {
        std::cerr << "Error" << std::endl;
        exit(1);
    }
    const std::string xml_path { argv[1] };
    
    // Load the XML document
    tinyxml2::XMLDocument doc;
    doc.LoadFile(xml_path.c_str());
    
    // Instantiate a JSON object
//     std::vector<json11::Json> list;
//     nlohmann::json to_print;
    long long_id=0;
    std::vector<std::string> entry_types={"article","phdthesis","inproceedings","proceedings","book","incollection","mastersthesis","www","person","data"};
//     "article","inproceedings","proceedings","book","incollection","phdthesis","mastersthesis","www","person","data"
    std::vector<std::string> entry_types_data={"author","editor","title","booktitle","pages","year","address","journal","volume","number","month","url","ee","cdrom","cite","publisher","note","crossref","isbn","series","school","chapter","publnr"};
    std::vector<std::string> l_entry_types_data_selected={"editor","title","booktitle","year","address","journal","volume","number","month","url","ee","cdrom","cite","publisher","note","crossref","isbn","series","school","chapter"};
    std::vector<std::string>::iterator iter_entry_types=entry_types.begin();
//    std::cout << "[" <<  std::endl;
    while (iter_entry_types != entry_types.end())
    {
      std::string l_type=(*iter_entry_types);
        for (tinyxml2::XMLElement* article_entry = doc.FirstChildElement()->FirstChildElement(l_type.c_str()); article_entry != nullptr; article_entry = article_entry->NextSiblingElement(l_type.c_str()))
        {
            long_id++;
            if (article_entry->FirstChildElement("author") == nullptr) { continue; }
            if (article_entry->FirstChildElement("title" ) == nullptr) { continue; }
            if (article_entry->FirstChildElement("title" )->FirstChild()->ToText() == nullptr) { continue; }
            
            // Convert to Json
            
            
            
            nlohmann::json authors = nlohmann::json::array();
            nlohmann::json data_json ; 
            
            std::vector<std::string>::iterator iter_entry_types_data=entry_types_data.begin();
            while (iter_entry_types_data != entry_types_data.end())
            {
                std::string l_type_data=(*iter_entry_types_data);
                if (article_entry->FirstChildElement(l_type_data.c_str()) == nullptr) { iter_entry_types_data++;continue; }
                if (l_type_data=="author")
                {
                    for (const auto* author = article_entry->FirstChildElement("author"); author != nullptr; author = author->NextSiblingElement("author"))
                    {
                        authors.push_back(author->GetText());
                    }
                    data_json.push_back(nlohmann::json::object_t::value_type(std::string("authors"), authors));
                }
                if (l_type_data=="title")
                {
                    const auto* l_data = article_entry->FirstChildElement("title"); 
                    data_json.push_back(nlohmann::json::object_t::value_type(std::string("title"), l_data));
                }
                if (l_type_data=="url" || l_type_data=="ee" || l_type_data=="cdrom")
                {
                    std::string l_string_data = article_entry->FirstChildElement(l_type_data.c_str())->GetText(); 
                    if ((int)l_string_data.size() > 1 ) data_json.push_back(nlohmann::json::object_t::value_type(std::string("url"), l_string_data));
                }
                if (l_type_data=="type") data_json.push_back(nlohmann::json::object_t::value_type("type",l_type));
                iter_entry_types_data++;
                
            }
            nlohmann::json data_json_item; 
            data_json_item.push_back(nlohmann::json::object_t::value_type("fields",data_json));
            std::string str_id=std::to_string(long_id);
            data_json_item.push_back(nlohmann::json::object_t::value_type("put","id:papers:paper::"+str_id));
            std::cout << data_json_item.dump() << std::endl;
//            std::cout << "," <<  std::endl;
//             to_print.push_back(data_json_item);
            
        }
        iter_entry_types++;
    }
//    std::cout << "]" <<  std::endl;
    // Dump the JSON object
//     std::cout << to_print.dump() << std::endl;
    
    return 0;
}
