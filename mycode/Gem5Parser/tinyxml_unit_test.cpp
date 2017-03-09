#include <iostream>
#include "tinyxml.h"
#include "Gem5_Parser.h"
#include "gtest/gtest.h"
using namespace std;
/**
enum SuccessEnum {FAILURE, SUCCESS};

SuccessEnum loadXML()
{
    TiXmlDocument doc;
    if(!doc.LoadFile("./Gem5Parser/a.xml"))
    {
        cerr << doc.ErrorDesc() << endl;
        return FAILURE;
    }
    else{
        doc.Print();
    }

    TiXmlElement* root = doc.FirstChildElement();
    if(root == NULL)
    {
        cerr << "Failed to load file: No root element." << endl;
        doc.Clear();
        return FAILURE;
    }

    for(TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
    {
        string elemName = elem->Value();
        const char* attr;
        attr = elem->Attribute("priority");
        if(strcmp(attr,"1")==0)
        {
            TiXmlElement* e1 = elem->FirstChildElement("bold");
            TiXmlNode* e2=e1->FirstChild();
            cout<<"priority=1\t"<<e2->ToText()->Value()<<endl;

        }
        else if(strcmp(attr,"2")==0)
        {
            TiXmlNode* e1 = elem->FirstChild();
            cout<<"priority=2\t"<<e1->ToText()->Value()<<endl;
        }
    }
    doc.Clear();
    return SUCCESS;
}
**/


TEST(get_gem5_config, mormal){
    /**
    TiXmlDocument doc;
    if(!doc.LoadFile("./Gem5Parser/config.xml"))
    {
        cerr << doc.ErrorDesc() << endl;
        //return FAILURE;
    }
    else{
        doc.Print();
    }

    TiXmlElement* root = doc.FirstChildElement();
    if(root == NULL)
    {
        cerr << "Failed to load file: No root element." << endl;
        doc.Clear();
        //return FAILURE;
    }
    TiXmlElement* Instru_Mod_Element = root->FirstChildElement();
    cout << Instru_Mod_Element->Value() << " : " << Instru_Mod_Element->GetText() << std::endl;
    cout<<"~~~~~~"<<endl;
    TiXmlElement* Archit_Mod_Element = Instru_Mod_Element->NextSiblingElement();
    cout << Archit_Mod_Element->Value() << " : " << Archit_Mod_Element->GetText() << std::endl;
    cout<<"~~~~~~dddd"<<endl;
    TiXmlElement* Gem5_Path_Element = Archit_Mod_Element->NextSiblingElement();
    cout << Gem5_Path_Element->Value() << " : " << Gem5_Path_Element->GetText() << std::endl;
    cout<<"~~~~~~"<<endl;
    TiXmlElement* Out_Path_Element = Gem5_Path_Element->NextSiblingElement();
    cout << Out_Path_Element->Value() << " : "  << std::endl;
    if(Out_Path_Element->FirstChild())
        cout<<Out_Path_Element->GetText()<<endl;
    cout<<"~~~~~~"<<endl;
    TiXmlElement* Config_Path_Element = Out_Path_Element->NextSiblingElement();
    cout << Config_Path_Element->Value() << " : " << std::endl;
    if(Config_Path_Element->FirstChild())
        cout<<Config_Path_Element->GetText()<<endl;
    TiXmlElement* L1_Cache_Element = Config_Path_Element->NextSiblingElement();
    TiXmlElement* L1d_Size_Element = L1_Cache_Element->FirstChildElement();  
    TiXmlElement* L1d_Size_Example_Element = L1d_Size_Element->FirstChildElement();
        for (; L1d_Size_Example_Element != NULL; L1d_Size_Example_Element = L1d_Size_Example_Element->NextSiblingElement() ) {  
            cout<<L1d_Size_Example_Element->Value()<<endl;
            if(L1d_Size_Example_Element->FirstChild())
                cout<< L1d_Size_Example_Element->GetText()<<endl;          
        }   
    TiXmlElement* L1i_Size_Element = L1d_Size_Element->NextSiblingElement();
    TiXmlElement* L1i_Size_Example_Element = L1i_Size_Element->FirstChildElement();
        for (; L1i_Size_Example_Element != NULL; L1i_Size_Example_Element = L1i_Size_Example_Element->NextSiblingElement() ) {  
            cout<<L1i_Size_Example_Element->Value()<<endl;
            if(L1i_Size_Example_Element->FirstChild())
                cout<< L1i_Size_Example_Element->GetText()<<endl;          
        } 
    TiXmlElement* L1d_Assoc_Element = L1i_Size_Element->NextSiblingElement();
    TiXmlElement* L1d_Assoc_Example_Element = L1d_Assoc_Element->FirstChildElement();
        for (; L1d_Assoc_Example_Element != NULL; L1d_Assoc_Example_Element = L1d_Assoc_Example_Element->NextSiblingElement() ) {  
            cout<<L1d_Assoc_Example_Element->Value()<<endl;
            if(L1d_Assoc_Example_Element->FirstChild())
                cout<< L1d_Assoc_Example_Element->GetText()<<endl;          
        } 
    TiXmlElement* L1i_Assoc_Element = L1d_Assoc_Element->NextSiblingElement();
    TiXmlElement* L1i_Assoc_Example_Element = L1i_Assoc_Element->FirstChildElement();
        for (; L1i_Assoc_Example_Element != NULL; L1i_Assoc_Example_Element = L1i_Assoc_Example_Element->NextSiblingElement() ) {  
            cout<<L1i_Assoc_Example_Element->Value()<<endl;
            if(L1i_Assoc_Example_Element->FirstChild())
                cout<< L1i_Assoc_Example_Element->GetText()<<endl;          
        }   
**/
    Gem5Parser parser;
    string path="./Gem5Parser/config.xml";
    parser.ReadXml(path);
    parser.PrintElementMap();
}
