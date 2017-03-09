#include "Gem5_Parser.h"
#include "tinyxml.h"
#include <vector>
#include <string>
#include <map>
#include <deque>
#include <iostream>
#include <sstream>
using namespace std;
Gem5Parser::Gem5Parser(){
	instru_mod = Instru_Mod::Full_Program;
	archit_mod = Archit_Mod::Normal;
}

void Gem5Parser::SearchAllChildElement(TiXmlElement* element, vector<string>& vec_of_elem, Config_Element con_ele){
	TiXmlElement* child_element = element->FirstChildElement();
	for (; child_element != NULL; child_element = child_element->NextSiblingElement() ) {  
		//cout<<L1i_Assoc_Example_Element->Value()<<endl;
		if(child_element->FirstChild()){
		//cout<< L1i_Assoc_Example_Element->GetText()<<endl;
			vec_of_elem.push_back(child_element->GetText());   
		}
	} 
	if(!vec_of_elem.empty()){
		elements.insert(make_pair(con_ele, vec_of_elem));
		vec_of_elem.clear();
	}

}

void Gem5Parser::GetChildElement(TiXmlElement* element, vector<string>& temp, Config_Element con_ele){
	cout << element->Value() << " : "  << std::endl;
	if(element->FirstChild()){
		cout<<element->GetText()<<endl;
		temp.push_back(element->GetText());
		elements.insert(make_pair(con_ele, temp));
		temp.clear();
	}
}

SuccessEnum Gem5Parser::ReadXml(string xml_path){

	TiXmlDocument doc;
	if(!doc.LoadFile(xml_path.c_str()))
	{
		cerr << doc.ErrorDesc() << endl;
	    return FAILURE;
	}
	else{
		doc.Print();
	}
	    //TODO: CheckCombination(doc);    check the combination is legal or illegal
	TiXmlElement* root = doc.FirstChildElement();
	if(root == NULL)
	{
		cerr << "Failed to load file: No root element." << endl;
		doc.Clear();
	    return FAILURE;
	}
    vector<string> temp;  //store data from xml file.
    TiXmlElement* Instru_Mod_Element = root->FirstChildElement();
    //cout << Instru_Mod_Element->Value() << " : " << Instru_Mod_Element->GetText() << std::endl;
    stringstream ss;
    ss<<Instru_Mod_Element->GetText();
    unsigned int a;
    ss>>a;
    ss.clear();
    ss.str("");
    instru_mod = static_cast<Instru_Mod>(a);
    TiXmlElement* Archit_Mod_Element = Instru_Mod_Element->NextSiblingElement();
    cout << Archit_Mod_Element->Value() << " : " << Archit_Mod_Element->GetText() << std::endl;
    ss<< Archit_Mod_Element->GetText();
    ss>>a;
    archit_mod = static_cast<Archit_Mod>(a);
    TiXmlElement* Gem5_Path_Element = Archit_Mod_Element->NextSiblingElement();
    GetChildElement(Gem5_Path_Element, temp, Config_Element::Gem5_Path);
    TiXmlElement* Out_Path_Element = Gem5_Path_Element->NextSiblingElement();
    GetChildElement(Out_Path_Element, temp, Config_Element::Out_Path);
    TiXmlElement* Config_Path_Element = Out_Path_Element->NextSiblingElement();
    GetChildElement(Config_Path_Element, temp, Config_Element::Config_Path);
    //read data about L1 Cache
    TiXmlElement* L1_Cache_Element = Config_Path_Element->NextSiblingElement();
    TiXmlElement* L1d_Size_Element = L1_Cache_Element->FirstChildElement(); 
    SearchAllChildElement(L1d_Size_Element,temp,Config_Element::L1d_Size); 
    TiXmlElement* L1i_Size_Element = L1d_Size_Element->NextSiblingElement();
    SearchAllChildElement(L1i_Size_Element,temp, Config_Element::L1i_Size);    
    TiXmlElement* L1d_Assoc_Element = L1i_Size_Element->NextSiblingElement();
    SearchAllChildElement(L1d_Assoc_Element,temp, Config_Element::L1d_Assoc); 
    TiXmlElement* L1i_Assoc_Element = L1d_Assoc_Element->NextSiblingElement();
    SearchAllChildElement(L1i_Assoc_Element,temp, Config_Element::L1i_Assoc); 
    //read data about L2 Cache
    TiXmlElement* L2_Cache_Element = L1_Cache_Element->NextSiblingElement();
    TiXmlElement* L2_Size_Element = L2_Cache_Element->FirstChildElement(); 
    SearchAllChildElement(L2_Size_Element,temp, Config_Element::L2_Size); 
    TiXmlElement* L2_Assoc_Element = L2_Size_Element->NextSiblingElement();
    SearchAllChildElement(L2_Assoc_Element,temp,Config_Element::L2_Assoc); 
    //read data about L3 Cache
    TiXmlElement* L3_Cache_Element = L2_Cache_Element->NextSiblingElement();
    TiXmlElement* L3_Size_Element = L3_Cache_Element->FirstChildElement(); 
    SearchAllChildElement(L3_Size_Element,temp, Config_Element::L3_Size); 
    TiXmlElement* L3_Assoc_Element = L3_Size_Element->NextSiblingElement();
    SearchAllChildElement(L3_Assoc_Element,temp,Config_Element::L3_Assoc); 

    TiXmlElement* Cacheline_Size_Element = L3_Cache_Element->NextSiblingElement();
    SearchAllChildElement(Cacheline_Size_Element,temp, Config_Element::Cacheline_Size); 

    TiXmlElement* Simpoint_Option_Element = Cacheline_Size_Element->NextSiblingElement();
    GetChildElement(Simpoint_Option_Element, temp, Config_Element::Simpoint_Option);
    
    TiXmlElement* Restore_Simpoint_Checkpoint_Option_Element = Simpoint_Option_Element->NextSiblingElement();
    GetChildElement(Restore_Simpoint_Checkpoint_Option_Element, temp, Config_Element::Restore_Simpoint_Checkpoint_Option);
    
    TiXmlElement* Checkpoint_Path_Element = Restore_Simpoint_Checkpoint_Option_Element->NextSiblingElement();
    GetChildElement(Checkpoint_Path_Element, temp, Config_Element::Checkpoint_Path);
    
    TiXmlElement* Restore_With_Cpu_Element = Checkpoint_Path_Element->NextSiblingElement();
    GetChildElement(Restore_With_Cpu_Element, temp, Config_Element::Restore_With_Cpu);

    TiXmlElement* Program_Path_Element = Restore_With_Cpu_Element->NextSiblingElement();
    GetChildElement(Program_Path_Element, temp, Config_Element::Program_Path);

    TiXmlElement* Program_Option_Element = Program_Path_Element->NextSiblingElement();
    GetChildElement(Program_Option_Element, temp, Config_Element::Program_Option);

    TiXmlElement* Input_File_Element = Program_Option_Element->NextSiblingElement();
    GetChildElement(Input_File_Element, temp, Config_Element::Input_File);
    cout<<"read xml file finish!"<<endl;
    doc.Clear();
    return SUCCESS;
}

void Gem5Parser::PrintElementMap(){
	auto ite=elements.begin();   
  	for(;ite!=elements.end();++ite){
  		cout<<"key:"<<static_cast<unsigned int>(ite->first)<<endl;
  		for(auto sub_it_l= ite->second.begin(); sub_it_l!=  ite->second.end(); sub_it_l++){
  			cout<<"		value:"<<*sub_it_l<<endl;
  		} 
  	}   
          
  	return ;   
}