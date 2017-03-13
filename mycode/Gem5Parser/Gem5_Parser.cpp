#include "Gem5_Parser.h"
#include "tinyxml.h"
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <deque>
#include <iostream>
#include <sstream>
using namespace std;

Instruction::Instruction(const Instruction& a):instru_mod(a.instru_mod),archit_mod(a.archit_mod),config_elements(a.config_elements){

}

Instruction& Instruction::operator=(const Instruction& rhs){
	if(this == &rhs)
		return *this;
	this->instru_mod=rhs.instru_mod;
	this->archit_mod=rhs.archit_mod;
	this->config_elements=rhs.config_elements;
	return *this;
}

string Instruction::GenerateString(int postfix_of_outpath){
	//bool l1cache=false;
	//bool l2cache=false;
	stringstream ss;
	ss<<"nohup "<<config_elements[Config_Element::Gem5_Path]<<" --outdir="<<config_elements[Config_Element::Out_Path]<<postfix_of_outpath<<" "<<config_elements[Config_Element::Config_Path];
	if(archit_mod==Archit_Mod::Nehalem)
		ss<<" --nehalem ";
	if(config_elements.find(Config_Element::Cpu_Type)!=config_elements.end())
		ss<<" --cpu-type="<<config_elements[Config_Element::Cpu_Type]<<" ";
	if(config_elements.find(Config_Element::L1d_Size)!=config_elements.end())
		ss<<" --caches "<<" --l1d_size="<<config_elements[Config_Element::L1d_Size]<<" ";
	if(config_elements.find(Config_Element::L1i_Size)!=config_elements.end())
		ss<<" --l1i_size="<<config_elements[Config_Element::L1i_Size]<<" ";
	if(config_elements.find(Config_Element::L1d_Assoc)!=config_elements.end())
		ss<<" --l1d_assoc="<<config_elements[Config_Element::L1d_Assoc]<<" ";
	if(config_elements.find(Config_Element::L1i_Assoc)!=config_elements.end())
		ss<<" --l1i_assoc="<<config_elements[Config_Element::L1i_Assoc]<<" ";
	if(config_elements.find(Config_Element::L2_Size)!=config_elements.end())
		ss<<" --l2cache "<<" --l2_size="<<config_elements[Config_Element::L2_Size]<<" ";
	if(config_elements.find(Config_Element::L2_Assoc)!=config_elements.end())
		ss<<" --l2_assoc="<<config_elements[Config_Element::L2_Assoc]<<" ";
	if(config_elements.find(Config_Element::L3_Size)!=config_elements.end())
		ss<<" --l3_size="<<config_elements[Config_Element::L3_Size]<<" ";
	if(config_elements.find(Config_Element::L3_Assoc)!=config_elements.end())
		ss<<" --l3_assoc="<<config_elements[Config_Element::L3_Assoc]<<" ";
	if(config_elements.find(Config_Element::Cacheline_Size)!=config_elements.end())
		ss<<" --cacheline_size="<<config_elements[Config_Element::Cacheline_Size]<<" ";
	if(config_elements.find(Config_Element::Simpoint_Option)!=config_elements.end())
		ss<<" --take-simpoint-checkpoint="<<config_elements[Config_Element::Simpoint_Option]<<" ";	 
	if(config_elements.find(Config_Element::Restore_Simpoint_Checkpoint_Option)!=config_elements.end())
		ss<<" --restore-simpoint-checkpoint -r "<<config_elements[Config_Element::Restore_Simpoint_Checkpoint_Option]<<" ";	 
	if(config_elements.find(Config_Element::Checkpoint_Path)!=config_elements.end())
		ss<<" --checkpoint-dir="<<config_elements[Config_Element::Checkpoint_Path]<<" ";
	if(config_elements.find(Config_Element::Restore_With_Cpu)!=config_elements.end())
		ss<<" --restore-with-cpu="<<config_elements[Config_Element::Restore_With_Cpu]<<" ";	
	if(config_elements.find(Config_Element::Program_Path_Option)!=config_elements.end())
		ss<<" -c "<<config_elements[Config_Element::Program_Path_Option]<<" ";	 
	ss<<"1>"<<config_elements[Config_Element::Out_Path]<<postfix_of_outpath<<"/run.log "<<"2>&1 &";
	string result;
	result=ss.str();
	return result;
}

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
    TiXmlElement* Cpu_Type_Element = Config_Path_Element->NextSiblingElement();
    GetChildElement(Cpu_Type_Element, temp, Config_Element::Cpu_Type);
    //read data about L1 Cache
    TiXmlElement* L1_Cache_Element = Cpu_Type_Element->NextSiblingElement();
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
    SearchAllChildElement(Program_Path_Element, temp, Config_Element::Program_Path_Option);

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
void Gem5Parser::PrintAllInstruc(){
	for(auto i : instruc){
 		cout<<static_cast<unsigned int>(i.instru_mod)<<endl;
 		cout<<static_cast<unsigned int>(i.archit_mod)<<endl;
 		auto ite=i.config_elements.begin();   
  		for(;ite!=i.config_elements.end();++ite){
  			std::cout<<"key:"<<static_cast<unsigned int>(ite->first)<<std::endl;
  			std::cout<<"		value:"<<ite->second<<std::endl;
  		}
  	cout<<"~~~~~~~~~~~~~"<<endl;    
 	}
 	return ;
}

bool Gem5Parser::GenerateAllInstruc(){
	auto ite = elements.begin();
 	queue<Instruction> result;
 	Instruction one_instrc= Instruction(instru_mod, archit_mod);
 	result.push(one_instrc);
 	//generate all instructions. 
 	//use a queue to store all instructions in this level, for next level, pop the top element and push new elements.
 	//eg: current queue[(ab)]  next level element[c,d]. After generate queue become[(abc),(abd)]. 
 	for(; ite != elements.end(); ++ite){
 		int size_of_queue=result.size();
 		for(int i=0; i < size_of_queue; i++){
 			Instruction temp = result.front();
 			result.pop();
 			for(auto sub_it_l= ite->second.begin(); sub_it_l!=  ite->second.end(); sub_it_l++){
 				cout<<*sub_it_l<<endl;
 				temp.config_elements[ite->first] = *sub_it_l;
 				cout<<"temp.config_elements[ite->first]"<<temp.config_elements[ite->first]<<endl;
 				result.push(temp);
 			}
 		}
 	}
 	// move the elements in queue to vector
 	while(!result.empty()){
 		Instruction temp=result.front();
 		instruc.push_back(temp);
 		result.pop();
 	}
 	cout<<"GenerateAllInstruc() finishes"<<endl;
 	cout<<"instruc.size()="<<instruc.size()<<endl;
 	return true;
}

bool Gem5Parser::GenerateAllInstrucString(){
	int index=1;
	for(auto i : instruc){
		all_instruc.push_back(i.GenerateString(index));
		index++;
	}
	
	cout<<"GenerateAllInstrucString() finishes"<<endl;
	for(auto i : all_instruc){
		cout<< i<<endl;
	}
	
	return true;
}