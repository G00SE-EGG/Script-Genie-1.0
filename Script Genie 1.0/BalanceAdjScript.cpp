#include "BalanceAdjScript.h"

using namespace std;


BalanceAdjScript::BalanceAdjScript(int x, int y, int width, int height, char* title)
	:ScriptWindow(x,y,width,height,title)
{
	begin();
	//handle file process
	input_stream.open("CREATE_FSA_MANUAL_ADJUSTMENT_temp.txt");

	//adding button to window and attaching callback
	btn_generate = new Fl_Button(235, 360, 70, 30, "Generate");
	btn_generate->callback(cb_generate_i, this);

	//adding text boxes to window
	psq_number = new Fl_Multiline_Input(130, 5, 70, 30, "PSQ:");
	date = new Fl_Multiline_Input(240, 5, 70, 30, "Date:");

	user_name = new Fl_Multiline_Input(393, 5, 70, 30, "Username:");
	
	//create buffers and add them to text fields
	buff_1 = new Fl_Text_Buffer();
	employee_id = new Fl_Text_Editor(30, 90, 100, 250, "EE Id's");
	employee_id->buffer(buff_1);

	buff_2 = new Fl_Text_Buffer();
	debit_acct = new Fl_Text_Editor(140, 90, 100, 250, "Debit Acct's");
	debit_acct->buffer(buff_2);

	buff_3 = new Fl_Text_Buffer();
	credit_acct = new Fl_Text_Editor(250, 90, 100, 250, "Credit Acct's");
	credit_acct->buffer(buff_3);

	buff_4 = new Fl_Text_Buffer();
	adj_type = new Fl_Text_Editor(360, 90, 100, 250, "Adjustment ID");
	adj_type->buffer(buff_4);

	buff_5 = new Fl_Text_Buffer();
	amount = new Fl_Text_Editor(470, 90, 100, 250, "Amount");
	amount->buffer(buff_5);

	end();

	show();
}


BalanceAdjScript::~BalanceAdjScript()
{
}

void BalanceAdjScript::cb_generate()
{
	//string temp_lines;

	string line;
	string lines = "";

	script_name = "WWSA_CREATE_FSA_MANUAL_ADJUSTMENT_PSQ";
	script_name += psq_number->value();
	script_name += "_";
	script_name += date->value();
	script_name += ".sql";

	//read buffers into strings
	emp_id = buff_1->text();
	deb_acct = buff_2->text();
	cre_acct = buff_3->text();
	adj_typ  = buff_4->text();
	amtt = buff_5->text();

	int line_count = 0;
	int item_line_count = 0;
	int cnt = 0;

	readString(eemp_id, emp_id);
	readString(ddeb_acct, deb_acct);
	readString(ccre_acct, cre_acct);
	readString(aadj_typ, adj_typ);
	readString(aamtt, amtt);

	if (compare())
	{
		for (int i = 0; i < eemp_id.size(); i++)
		{
			readlines.push_back(ReadLine(eemp_id[i], ddeb_acct[i], ccre_acct[i], aadj_typ[i], aamtt[i]));
		}
	}


	while (getline(input_stream, line))
	{
		if (line == "SPOOL WWSA_CREATE_FSA_MANUAL_ADJUSTMENT_")
		{
			line += "PSQ";
			line += psq_number->value();
			line += "_";
			line += date->value();
			line += ".log";
		}
		else if (line == "  gc_user                               CONSTANT VARCHAR2(30) :=")
		{
			line += "'";
			line += user_name->value();
			line += "';";
		}
		else if (line == "  gc_developer                          CONSTANT VARCHAR2(30) :=")
		{
			line += "'";
			line += user_name->value();
			line += "';";
		}
		else if (line == "  v_script_name")
		{
			line += " VARCHAR2 (100) := '";
			line += script_name;
			line += "';";
		}
		else if (line == "  v_psq_it_number                       NUMBER          :=")
		{
			line += psq_number->value();
			line += ";";
		}
		else if (line == "  IN ")
		{
			line += "( \n";
			for (int i = 0; i < readlines.size(); i++)
			{
				
				if (i == (readlines.size() - 1))
				{
					query_dual = " dual";
				}
				else
				{
					query_dual = "dual union all";
				}
				line += query_select + readlines[i].ee_id + query_employee_id + readlines[i].deb_acct + query_debit_member_account_id +
					readlines[i].cred_acct + query_credit_member_account_id + " NULL orig_card_txn_id, NULL orig_claim_id, NULL orig_pmp_instruction_id, " +
					readlines[i].adj_id + query_adjustment_type_id + readlines[i].amt + query_from + query_dual += "\n";
			}
			line += ")";
		}
		

		lines += line + "\n";
	}

	//create output file
	output_stream.open(script_name);
	//read string into file
	output_stream << lines;
	//close filestream
	output_stream.close();
	
	cb_close();
}


void BalanceAdjScript::readString(vector<string>& vect, string values)
{
	//create strings to read from file
	string line, lines = "";
	//name file to write to
	out_stream.open("temp.txt");
	out_stream << values;
	//close file 
	out_stream.close();
	//open file for reading
	inp_stream.open("temp.txt");
	//read file contents into vector
	while (getline(inp_stream, line))
	{
		vect.push_back(line);
	}
	inp_stream.close();
}

bool BalanceAdjScript::compare()
{
	if (eemp_id.size() == ddeb_acct.size() && ccre_acct.size() == aadj_typ.size() && aamtt.size() == aadj_typ.size())
	{
		return true;
	}
	else {
		return false;
	}
}