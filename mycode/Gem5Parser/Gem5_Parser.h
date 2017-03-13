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
	Cpu_Type,
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
	Restore_Simpoint_Checkpoint_Option, //   eg: 2
	Checkpoint_Path,
	Restore_With_Cpu,  //detailed
	Program_Path_Option,  //./gap_base.gcc4-high-opt -l ./ -q -m 1M <test.input
};
class Instruction{
public:
	Instruction(Instru_Mod a, Archit_Mod b):instru_mod(a),archit_mod(b){}
	Instruction(const Instruction& a);
	Instruction& operator=(const Instruction& rhs);
	~Instruction()= default;
	friend class Gem5Parser;
	string GenerateString(int postfix_of_outpath);
private:
	Instru_Mod instru_mod;
	Archit_Mod archit_mod;
	map<Config_Element, string> config_elements;

};

	
class Gem5Parser{
 public:
 	Gem5Parser();
 	SuccessEnum ReadXml(string xml_path);//read from xml and store data to elements
 	bool CheckCombination(TiXmlDocument doc); // check the combination is legal or illegal
 	bool GenerateAllInstruc();  //generate Instructions, store in vector<Instruction> instruc;
 	bool GenerateAllInstrucString();// generate all instruction strings, store in deque<string> all_instruc;
 	void PrintElementMap();
 	void PrintAllInstruc(); //cheak data;
 private:
 	void SearchAllChildElement(TiXmlElement* element, vector<string>& vec_of_elem, Config_Element con_ele);//vec_of_elem: store all values
 	void GetChildElement(TiXmlElement* element, vector<string>& temp, Config_Element con_ele); //for configs which only have one value
 	Instru_Mod instru_mod;
	Archit_Mod archit_mod;
 	map<Config_Element, vector<string>> elements;
 	vector<Instruction> instruc;
 	deque<string> all_instruc;
};

#endif /* GEM5_PARSER_H */