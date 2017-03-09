#ifndef GEM5_PARSER_H
#define GEM5_PARSER_H
#include <vector>
#include <string>
#include <map>
#include <deque>
class TiXmlElement;
class TiXmlDocument;
using namespace std;
enum SuccessEnum {FAILURE, SUCCESS};
enum class Instru_Mod : unsigned int{
     Simpoint_To_Checkpoint=1,
     Checkpoint_To_Stats,
     Full_Program,
 }; 
enum class Archit_Mod : unsigned int {
	Normal=1,
	Nehalem,
};
enum class Config_Element : unsigned int{
	Gem5_Path=1,
	Out_Path,
	Config_Path,
	L1d_Size,
	L1i_Size,
	L2_Size,     
	L3_Size,
	L1d_Assoc,
	L1i_Assoc,
	L2_Assoc,
	L3_Assoc,
	Cacheline_Size,
	Simpoint_Option,  //  ./t.simpoints,./t.weights,100,100
	Restore_Simpoint_Checkpoint_Option, //   -r 2 或者2
	Checkpoint_Path,
	Restore_With_Cpu,  //detailed
	Program_Path,  //./gap_base.gcc4-high-opt
	Program_Option,   //-l ./ -q -m 1M
	Input_File,
};
class Instruction{
public:
	friend class Gem5Parser;
	string GenerateString();
private:
	Instru_Mod instru_mod;
	Archit_Mod archit_mod;
	string gem5_path;
	string out_path;
	string config_path;
	string l1d_size;
	string l1i_size;
	string l2_size;
	string l3_size;
	string l1d_assoc;
	string l1i_assoc;
	string l2_assoc;
	string l3_assoc;
	string cacheline_size;
	string Simpoint_Option;
	string restore_simpoint_checkpoint_option;
	string checkpoint_path;
	string restore_with_cpu;
	string program_path;
	string program_option;
	string input_file;

};

	
class Gem5Parser{
 public:
 	Gem5Parser();
 	SuccessEnum ReadXml(string xml_path);//read from xml and store data to elements
 	bool CheckCombination(TiXmlDocument doc); // check the combination is legal or illegal
 	bool GenerateAllInstruc(); 
 	void PrintElementMap();
 private:
 	void SearchAllChildElement(TiXmlElement* element, vector<string>& vec_of_elem, Config_Element con_ele);//vec_of_elem: store all values
 	void GetChildElement(TiXmlElement* element, vector<string>& temp, Config_Element con_ele); //for config which one have one value
 	Instru_Mod instru_mod;
	Archit_Mod archit_mod;
 	map<Config_Element, vector<string>> elements;
 	vector<Instruction*> instruc;
 	deque<string> all_instruc;
};

#endif /* GEM5_PARSER_H */