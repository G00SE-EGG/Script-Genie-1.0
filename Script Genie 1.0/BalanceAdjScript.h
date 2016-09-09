#pragma once
#include "ScriptWindow.h"
#include <FL/Fl_Text_Editor.H>
#include <vector>

struct ReadLine
{
	ReadLine();
	ReadLine(std::string ee, std::string deb, std::string cred, std::string adj, std::string at)
		:ee_id(ee), deb_acct(deb), cred_acct(cred), adj_id(adj), amt(at)
	{
	}

	std::string ee_id;
	std::string deb_acct;
	std::string cred_acct;
	std::string adj_id;
	std::string amt;
};




class BalanceAdjScript : public ScriptWindow
{
public:
	BalanceAdjScript(int x, int y, int width, int height, char* title);
	~BalanceAdjScript();

private:
	inline void cb_generate();

	//create a field to input text
	Fl_Text_Buffer* buff_1;
	Fl_Text_Buffer* buff_2;
	Fl_Text_Buffer* buff_3;
	Fl_Text_Buffer* buff_4;
	Fl_Text_Buffer* buff_5;

	//create vector of ReadLines/input parameters
	std::vector<ReadLine> readlines;
	std::vector<std::string> eemp_id;
	std::vector<std::string> ddeb_acct;
	std::vector<std::string> ccre_acct;
	std::vector<std::string> aadj_typ;
	std::vector<std::string> aamtt;

	//create sql statements
	std::string query_select = "select ";
	std::string query_employee_id = " employee_id, ";
	std::string query_debit_member_account_id = " debit_member_account_id, ";
	std::string query_credit_member_account_id = " credit_member_account_id, ";
	std::string query_adjustment_type_id = " adjustment_type_id, ";
	std::string query_total_adjustment_amt = " total_adjustment_amt ";
	std::string query_from = " from ";
	std::string query_dual = "";
	/*
	read each parameter (ee_id, acct, etc) into its own 
	vector, then read vector contents into readline class
	vector 
	lines.push_back(ReadLine(emp_id[i], deb_acct[i], etc));
	read all into temp line
	if(str[i] == "\n")
	switch to the next vector (emp_id[i] moves to act[i])
	*/

	////create variables that read the text box data
	std::string emp_id;
	std::string deb_acct;
	std::string cre_acct;
	std::string adj_typ;
	std::string amtt;

	//create input boxes
	Fl_Multiline_Input* psq_number;
	Fl_Multiline_Input* user_name;
	Fl_Multiline_Input* date;
	Fl_Text_Editor* employee_id;
	Fl_Text_Editor* debit_acct;
	Fl_Text_Editor* credit_acct;
	Fl_Text_Editor* adj_type;
	Fl_Text_Editor* amount;

	//create streams to read and write
	std::ifstream inp_stream;
	std::ofstream out_stream;
	

	//test function 
	void readString(std::vector<std::string>& vect, std::string values);
	bool compare();
};

