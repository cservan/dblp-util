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
    
    // Specify the target journal name whose entries will be extracted
    const std::string target_journal_name { "ACM Trans. Graph." };
    const std::string target_volume { "36" };
    const std::string target_number { "4" };
    
    // Load the XML document
    tinyxml2::XMLDocument doc;
    doc.LoadFile(xml_path.c_str());
    
    // Instantiate a JSON object
//     std::vector<json11::Json> list;
    nlohmann::json to_print;
    std::vector<std::string> entry_types={"article","phdthesis"};
//     "article","inproceedings","proceedings","book","incollection","phdthesis","mastersthesis","www","person","data"
    std::vector<std::string> entry_types_data={"author","editor","title","booktitle","pages","year","address","journal","volume","number","month","url","ee","cdrom","cite","publisher","note","crossref","isbn","series","school","chapter","publnr"};
    std::vector<std::string>::iterator iter_entry_types=entry_types.begin();
    while (iter_entry_types != entry_types.end())
    {
      std::string l_type=(*iter_entry_types);
        for (tinyxml2::XMLElement* article_entry = doc.FirstChildElement()->FirstChildElement(l_type.c_str()); article_entry != nullptr; article_entry = article_entry->NextSiblingElement(l_type.c_str()))
        {
            if (article_entry->FirstChildElement("author") == nullptr) { continue; }
            if (article_entry->FirstChildElement("title" ) == nullptr) { continue; }
            if (article_entry->FirstChildElement("title" )->FirstChild()->ToText() == nullptr) { continue; }
            
            // Convert to Json
            
            
            
            nlohmann::json authors = nlohmann::json::array();
            nlohmann::json data_json ; //= nlohmann::json==obj;
            
            
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
                else
                {
                    std::string l_data=article_entry->FirstChildElement(l_type_data.c_str())->GetText();
                    data_json.push_back(nlohmann::json::object_t::value_type(l_type_data, l_data));
                }
                iter_entry_types_data++;
                
            }
            data_json.push_back(nlohmann::json::object_t::value_type("type",l_type));
            to_print.push_back(data_json);
        }
        iter_entry_types++;
    }

    // Dump the JSON object
    std::cout << to_print.dump() << std::endl;
    
    return 0;
}
