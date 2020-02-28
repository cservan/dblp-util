#include <iostream>
#include <string>
#include <set>
#include <tinyxml2.h>
#include <nlohmann/json.hpp>

using namespace std;


std::unordered_map<std::string,std::string> html_entities = {	{ "AElig;", "Æ" },
	{ "Aacute;", "Á" },
	{ "Acirc;", "Â" },
	{ "Agrave;", "À" },
	{ "Alpha;", "Α" },
	{ "Aring;", "Å" },
	{ "Atilde;", "Ã" },
	{ "Auml;", "Ä" },
	{ "Beta;", "Β" },
	{ "Ccedil;", "Ç" },
	{ "Chi;", "Χ" },
	{ "Dagger;", "‡" },
	{ "Delta;", "Δ" },
	{ "ETH;", "Ð" },
	{ "Eacute;", "É" },
	{ "Ecirc;", "Ê" },
	{ "Egrave;", "È" },
	{ "Epsilon;", "Ε" },
	{ "Eta;", "Η" },
	{ "Euml;", "Ë" },
	{ "Gamma;", "Γ" },
	{ "Iacute;", "Í" },
	{ "Icirc;", "Î" },
	{ "Igrave;", "Ì" },
	{ "Iota;", "Ι" },
	{ "Iuml;", "Ï" },
	{ "Kappa;", "Κ" },
	{ "Lambda;", "Λ" },
	{ "Mu;", "Μ" },
	{ "Ntilde;", "Ñ" },
	{ "Nu;", "Ν" },
	{ "OElig;", "Œ" },
	{ "Oacute;", "Ó" },
	{ "Ocirc;", "Ô" },
	{ "Ograve;", "Ò" },
	{ "Omega;", "Ω" },
	{ "Omicron;", "Ο" },
	{ "Oslash;", "Ø" },
	{ "Otilde;", "Õ" },
	{ "Ouml;", "Ö" },
	{ "Phi;", "Φ" },
	{ "Pi;", "Π" },
	{ "Prime;", "″" },
	{ "Psi;", "Ψ" },
	{ "Rho;", "Ρ" },
	{ "Scaron;", "Š" },
	{ "Sigma;", "Σ" },
	{ "THORN;", "Þ" },
	{ "Tau;", "Τ" },
	{ "Theta;", "Θ" },
	{ "Uacute;", "Ú" },
	{ "Ucirc;", "Û" },
	{ "Ugrave;", "Ù" },
	{ "Upsilon;", "Υ" },
	{ "Uuml;", "Ü" },
	{ "Xi;", "Ξ" },
	{ "Yacute;", "Ý" },
	{ "Yuml;", "Ÿ" },
	{ "Zeta;", "Ζ" },
	{ "aacute;", "á" },
	{ "acirc;", "â" },
	{ "acute;", "´" },
	{ "aelig;", "æ" },
	{ "agrave;", "à" },
	{ "alefsym;", "ℵ" },
	{ "alpha;", "α" },
	{ "amp;", "&" },
	{ "and;", "∧" },
	{ "ang;", "∠" },
	{ "apos;", "'" },
	{ "aring;", "å" },
	{ "asymp;", "≈" },
	{ "atilde;", "ã" },
	{ "auml;", "ä" },
	{ "bdquo;", "„" },
	{ "beta;", "β" },
	{ "brvbar;", "¦" },
	{ "bull;", "•" },
	{ "cap;", "∩" },
	{ "ccedil;", "ç" },
	{ "cedil;", "¸" },
	{ "cent;", "¢" },
	{ "chi;", "χ" },
	{ "circ;", "ˆ" },
	{ "clubs;", "♣" },
	{ "cong;", "≅" },
	{ "copy;", "©" },
	{ "crarr;", "↵" },
	{ "cup;", "∪" },
	{ "curren;", "¤" },
	{ "dArr;", "⇓" },
	{ "dagger;", "†" },
	{ "darr;", "↓" },
	{ "deg;", "°" },
	{ "delta;", "δ" },
	{ "diams;", "♦" },
	{ "divide;", "÷" },
	{ "eacute;", "é" },
	{ "ecirc;", "ê" },
	{ "egrave;", "è" },
	{ "empty;", "∅" },
	{ "emsp;", "\xE2\x80\x83" },
	{ "ensp;", "\xE2\x80\x82" },
	{ "epsilon;", "ε" },
	{ "equiv;", "≡" },
	{ "eta;", "η" },
	{ "eth;", "ð" },
	{ "euml;", "ë" },
	{ "euro;", "€" },
	{ "exist;", "∃" },
	{ "fnof;", "ƒ" },
	{ "forall;", "∀" },
	{ "frac12;", "½" },
	{ "frac14;", "¼" },
	{ "frac34;", "¾" },
	{ "frasl;", "⁄" },
	{ "gamma;", "γ" },
	{ "ge;", "≥" },
	{ "gt;", ">" },
	{ "hArr;", "⇔" },
	{ "harr;", "↔" },
	{ "hearts;", "♥" },
	{ "hellip;", "…" },
	{ "iacute;", "í" },
	{ "icirc;", "î" },
	{ "iexcl;", "¡" },
	{ "igrave;", "ì" },
	{ "image;", "ℑ" },
	{ "infin;", "∞" },
	{ "int;", "∫" },
	{ "iota;", "ι" },
	{ "iquest;", "¿" },
	{ "isin;", "∈" },
	{ "iuml;", "ï" },
	{ "kappa;", "κ" },
	{ "lArr;", "⇐" },
	{ "lambda;", "λ" },
	{ "lang;", "〈" },
	{ "laquo;", "«" },
	{ "larr;", "←" },
	{ "lceil;", "⌈" },
	{ "ldquo;", "“" },
	{ "le;", "≤" },
	{ "lfloor;", "⌊" },
	{ "lowast;", "∗" },
	{ "loz;", "◊" },
	{ "lrm;", "\xE2\x80\x8E" },
	{ "lsaquo;", "‹" },
	{ "lsquo;", "‘" },
	{ "lt;", "<" },
	{ "macr;", "¯" },
	{ "mdash;", "—" },
	{ "micro;", "µ" },
	{ "middot;", "·" },
	{ "minus;", "−" },
	{ "mu;", "μ" },
	{ "nabla;", "∇" },
	{ "nbsp;", "\xC2\xA0" },
	{ "ndash;", "–" },
	{ "ne;", "≠" },
	{ "ni;", "∋" },
	{ "not;", "¬" },
	{ "notin;", "∉" },
	{ "nsub;", "⊄" },
	{ "ntilde;", "ñ" },
	{ "nu;", "ν" },
	{ "oacute;", "ó" },
	{ "ocirc;", "ô" },
	{ "oelig;", "œ" },
	{ "ograve;", "ò" },
	{ "oline;", "‾" },
	{ "omega;", "ω" },
	{ "omicron;", "ο" },
	{ "oplus;", "⊕" },
	{ "or;", "∨" },
	{ "ordf;", "ª" },
	{ "ordm;", "º" },
	{ "oslash;", "ø" },
	{ "otilde;", "õ" },
	{ "otimes;", "⊗" },
	{ "ouml;", "ö" },
	{ "para;", "¶" },
	{ "part;", "∂" },
	{ "permil;", "‰" },
	{ "perp;", "⊥" },
	{ "phi;", "φ" },
	{ "pi;", "π" },
	{ "piv;", "ϖ" },
	{ "plusmn;", "±" },
	{ "pound;", "£" },
	{ "prime;", "′" },
	{ "prod;", "∏" },
	{ "prop;", "∝" },
	{ "psi;", "ψ" },
	{ "quot;", "\"" },
	{ "rArr;", "⇒" },
	{ "radic;", "√" },
	{ "rang;", "〉" },
	{ "raquo;", "»" },
	{ "rarr;", "→" },
	{ "rceil;", "⌉" },
	{ "rdquo;", "”" },
	{ "real;", "ℜ" },
	{ "reg;", "®" },
	{ "rfloor;", "⌋" },
	{ "rho;", "ρ" },
	{ "rlm;", "\xE2\x80\x8F" },
	{ "rsaquo;", "›" },
	{ "rsquo;", "’" },
	{ "sbquo;", "‚" },
	{ "scaron;", "š" },
	{ "sdot;", "⋅" },
	{ "sect;", "§" },
	{ "shy;", "\xC2\xAD" },
	{ "sigma;", "σ" },
	{ "sigmaf;", "ς" },
	{ "sim;", "∼" },
	{ "spades;", "♠" },
	{ "sub;", "⊂" },
	{ "sube;", "⊆" },
	{ "sum;", "∑" },
	{ "sup1;", "¹" },
	{ "sup2;", "²" },
	{ "sup3;", "³" },
	{ "sup;", "⊃" },
	{ "supe;", "⊇" },
	{ "szlig;", "ß" },
	{ "tau;", "τ" },
	{ "there4;", "∴" },
	{ "theta;", "θ" },
	{ "thetasym;", "ϑ" },
	{ "thinsp;", "\xE2\x80\x89" },
	{ "thorn;", "þ" },
	{ "tilde;", "˜" },
	{ "times;", "×" },
	{ "trade;", "™" },
	{ "uArr;", "⇑" },
	{ "uacute;", "ú" },
	{ "uarr;", "↑" },
	{ "ucirc;", "û" },
	{ "ugrave;", "ù" },
	{ "uml;", "¨" },
	{ "upsih;", "ϒ" },
	{ "upsilon;", "υ" },
	{ "uuml;", "ü" },
	{ "weierp;", "℘" },
	{ "xi;", "ξ" },
	{ "yacute;", "ý" },
	{ "yen;", "¥" },
	{ "yuml;", "ÿ" },
	{ "zeta;", "ζ" },
	{ "zwj;", "\xE2\x80\x8D" },
	{ "zwnj;", "\xE2\x80\x8C" }};

        
std::string html_decode(std::string & str)
{
    std::string to_return=str;
    int l_start = (int)str.find("&");
    int l_end = (int)str.find(";");
    int l_length = l_end - l_start;
    int prev_start = l_start;
    while ( l_start > -1 && l_end > -1 && l_length > 0 )
    {
        std::string sub_str=str.substr(l_start+1,l_length);
        if (html_entities.find(sub_str) != html_entities.end())
        {
            to_return=to_return.replace(l_start,l_length+1,html_entities.find(sub_str)->second);
        }
        l_start = (int)str.find("&");
        l_end = (int)str.find(";");
        l_length = l_end - l_start;
        // To avoid nfinite loops...
        if (prev_start == l_start)
        {
            l_start= -1;
        }
        else
        {
            prev_start = l_start;
        }
    }
    return to_return;
}

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
    std::vector<std::string> entry_types={"article","phdthesis","inproceedings","proceedings","book","incollection","mastersthesis","www","data"};
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
                if (l_type != "www")
                {
                    if (l_type_data=="author")
                    {
                        for (const auto* author = article_entry->FirstChildElement("author"); author != nullptr; author = author->NextSiblingElement("author"))
                        {
                            std::string l_tmp(author->GetText());
                            nlohmann::json authors_data;
                            std::string str_first_name=l_tmp.substr(l_tmp.find(" "));
                            std::string str_last_name=l_tmp.substr(l_tmp.rfind(" "),l_tmp.size());
                            authors_data.push_back(nlohmann::json::object_t::value_type(std::string("first_name"), html_decode(str_first_name)));
                            authors_data.push_back(nlohmann::json::object_t::value_type(std::string("last_name"), html_decode(str_first_name)));
                            authors.push_back(authors_data);
                        }
                        data_json.push_back(nlohmann::json::object_t::value_type(std::string("authors"), authors));
                    }
                    if (l_type_data=="title" || l_type_data=="year" || l_type_data=="month")
                    {
                        std::string l_string_data = article_entry->FirstChildElement(l_type_data.c_str())->GetText(); 
                        data_json.push_back(nlohmann::json::object_t::value_type(std::string(l_type_data), html_decode(l_string_data)));
                    }
                    if (l_type_data=="booktitle" || l_type_data=="journal")
                    {
                        std::string l_string_data = article_entry->FirstChildElement(l_type_data.c_str())->GetText(); 
                        data_json.push_back(nlohmann::json::object_t::value_type(std::string("source"), html_decode(l_string_data)));
                    }
                    if (l_type_data=="url" || l_type_data=="ee" || l_type_data=="cdrom")
                    {
                        std::string l_string_data = article_entry->FirstChildElement(l_type_data.c_str())->GetText(); 
                        if ((int)l_string_data.find("http") > -1 || (int)l_string_data.find("www") > -1) data_json.push_back(nlohmann::json::object_t::value_type(std::string("url"), l_string_data));
                    }
                }
                else
                {
                    if (l_type_data=="author")
                    {
                        std::string l_string_data = article_entry->FirstChildElement(l_type_data.c_str())->GetText(); 
                        data_json.push_back(nlohmann::json::object_t::value_type(std::string("title"), html_decode(l_string_data)));
                    }
                    if (l_type_data=="url" || l_type_data=="ee" || l_type_data=="cdrom")
                    {
                        std::string l_string_data = article_entry->FirstChildElement(l_type_data.c_str())->GetText(); 
                        if ((int)l_string_data.find("http") > -1 || (int)l_string_data.find("www") > -1) data_json.push_back(nlohmann::json::object_t::value_type(std::string("url"), l_string_data));
                    }
                    if (l_type_data=="school" || l_type_data=="address")
                    {
                        std::string l_string_data = article_entry->FirstChildElement(l_type_data.c_str())->GetText(); 
                        data_json.push_back(nlohmann::json::object_t::value_type(std::string(l_type_data), html_decode(l_string_data)));
                    }
                }
                iter_entry_types_data++;
            }
            nlohmann::json data_json_item; 
            if (l_type != "www") data_json.push_back(nlohmann::json::object_t::value_type("type",l_type));
            else data_json.push_back(nlohmann::json::object_t::value_type("type","person"));
            if (data_json.find("url") == data_json.end()) data_json.push_back(nlohmann::json::object_t::value_type(std::string("url"), ""));
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
