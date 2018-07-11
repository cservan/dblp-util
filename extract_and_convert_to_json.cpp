#include <iostream>
#include <string>
#include <tinyxml2.h>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cerr << "Error" << std::endl;
        exit(1);
    }
    
    const std::string xml_path { argv[1] };
    
    tinyxml2::XMLDocument doc;
    doc.LoadFile(xml_path.c_str());

    return 0;
}
