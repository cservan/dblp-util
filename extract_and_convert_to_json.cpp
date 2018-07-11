#include <iostream>
#include <string>
#include <set>
#include <tinyxml2.h>
#include <json11.hpp>

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
    
    // Load the XML document
    tinyxml2::XMLDocument doc;
    doc.LoadFile(xml_path.c_str());
    
    // Instantiate a JSON object
    std::vector<json11::Json> list;
    
    for (tinyxml2::XMLElement* article_entry = doc.FirstChildElement()->FirstChildElement("article"); article_entry != nullptr; article_entry = article_entry->NextSiblingElement("article"))
    {
        // Ignore articles from other than ACM Tranc. Graph.
        if (article_entry->FirstChildElement("journal") == nullptr) { continue; }
        if (std::string(article_entry->FirstChildElement("journal")->GetText()) != target_journal_name) { continue; }
        
        // Ignore invalid entries
        if (article_entry->FirstChildElement("author") == nullptr) { continue; }
        if (article_entry->FirstChildElement("title" ) == nullptr) { continue; }
        if (article_entry->FirstChildElement("title" )->FirstChild()->ToText() == nullptr) { continue; }
        
        // Convert to Json
        std::vector<json11::Json> authors;
        for (const auto* author = article_entry->FirstChildElement("author"); author != nullptr; author = author->NextSiblingElement("author"))
        {
            authors.push_back(author->GetText());
        }
        json11::Json json = json11::Json::object
        {
            { "authors", authors },
            { "title"  , article_entry->FirstChildElement("title")->GetText() }
        };
        list.push_back(json);
    }

    // Dump the JSON object
    std::cout << json11::Json{ list }.dump() << std::endl;
    
    return 0;
}
