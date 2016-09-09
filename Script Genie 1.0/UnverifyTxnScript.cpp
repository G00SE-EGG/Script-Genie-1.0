#include "UnverifyTxnScript.h"

using namespace std;

UnverifyTxnScript::UnverifyTxnScript(int x, int y, int width, int height, char* title)
	:ScriptWindow(x, y, width, height, title)
{
	begin();
	//handle file process
	input_stream.open("unverify_card_txn_temp.txt");
	
	//adding button to window and attaching callback
	btn_generate = new Fl_Button(155, 110, 70, 30, "Generate");
	btn_generate->callback(cb_generate_i, this);

	//adding text boxes to window
	psq_number = new Fl_Multiline_Input(60, 5, 70, 30, "PSQ:");
	date = new Fl_Multiline_Input(178, 5, 70, 30, "Date:");

	user_name = new Fl_Multiline_Input(323, 5, 70, 30, "Username:");
	card_txn_id = new Fl_Multiline_Input(60, 70, 70, 30, "Txn ID:");

	end();

	show();
}


UnverifyTxnScript::~UnverifyTxnScript()
{
}

void UnverifyTxnScript::cb_generate()
{
	string line;
	string lines = "";

	script_name = "wwsa_unverify_card_txn_PSQ";
	script_name += psq_number->value();
	script_name += "_";
	script_name += date->value();
	script_name += ".sql";

	while (getline(input_stream, line))
	{
		if (line == "SPOOL wwsa_unverify_card_txn_")
		{
			line += "PSQ";
			line += psq_number->value();
			line += "_";
			line += date->value();
			line += ".log";
		}
		else if (line == "    gc_user                CONSTANT VARCHAR2(30) :=")
		{
			line += "'";
			line += user_name->value();
			line += "';";
		}
		else if (line == "    gc_developer           CONSTANT VARCHAR2(30) :=")
		{
			line += "'";
			line += user_name->value();
			line += "';";
		}
		else if (line == "    v_script_name")
		{
			line += " VARCHAR2 (100) := '";
			line += script_name;
			line += "';";
		}
		else if (line == "    v_psq_it_number        NUMBER                :=")
		{
			line += psq_number->value();
			line += ";";
		}
		else if (line == "		IN")
		{
			line += "(";
			line += card_txn_id->value();
			line += ");";
		}
		
		lines += line + "\n";
	}

	//create output file
	output_stream.open(script_name);

	output_stream << lines;
	output_stream.close();

	cb_close();
}
