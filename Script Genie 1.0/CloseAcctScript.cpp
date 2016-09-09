#include "CloseAcctScript.h"

using namespace std;

CloseAcctScript::CloseAcctScript(int x, int y, int width, int height, char* title)
	:ScriptWindow(x,y,width, height,title)
{
	begin();
	//open template
	input_stream.open("close_accounts_temp.txt");

	//draw input button and input boxes onto window
	btn_generate = new Fl_Button(155, 110, 70, 30, "Generate");
	btn_generate->callback(cb_generate_i, this);

	psq_number = new Fl_Multiline_Input(60, 5, 70, 30, "PSQ:");
	date = new Fl_Multiline_Input(178, 5, 70, 30, "Date:");

	user_name = new Fl_Multiline_Input(323, 5, 70, 30, "Username:");
	member_account_id = new Fl_Multiline_Input(60, 70, 70, 30, "Acct ID:");

	end();
	show();
}


CloseAcctScript::~CloseAcctScript()
{
}


void CloseAcctScript::cb_generate()
{
	string line;
	string lines = "";

	script_name = "wwsa_close_accounts_PSQ";
	script_name += psq_number->value();
	script_name += "_";
	script_name += date->value();
	script_name += ".log";


	while (getline(input_stream, line))
	{
		if (line == "SPOOL wwsa_close_accounts_")
		{
			line += "PSQ";
			line += psq_number->value();
			line += "_";
			line += date->value();
			line += ".sql";
		}
		else if (line == "   gc_developer    CONSTANT VARCHAR2 (30) :=")
		{
			line += "'";
			line += user_name->value();
			line += "';";
		}
		else if (line == "   gc_run_user     CONSTANT VARCHAR2 (30) :=")
		{
			line += "'";
			line += user_name->value();
			line += "';";
		}
		else if (line == "   v_script_name")
		{
			line += " VARCHAR2 (100) := '";
			line += script_name;
			line += "';";
		}
		else if (line == "   v_psq_it_number          NUMBER :=")
		{
			line += psq_number->value();
			line += ";";
		}
		else if (line == "			IN")
		{
			line += "(";
			line += member_account_id->value();
			line += ");";
		}

		lines += line + "\n";
	}

	output_stream.open(script_name);

	output_stream << lines;
	output_stream.close();

	cb_close();
}