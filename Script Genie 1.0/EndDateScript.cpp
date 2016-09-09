#include "EndDateScript.h"

using namespace std;

EndDateScript::EndDateScript(int x, int y, int width, int height, char* title)
	:ScriptWindow(x, y, width, height, title)
{
	begin();
	input_stream.open("cov_end_date_upd_temp.txt");

	btn_generate = new Fl_Button(155, 110, 70, 30, "Generate");
	btn_generate->callback(cb_generate_i, this);

	//adding text boxes to window

	psq_number = new Fl_Multiline_Input(60, 5, 70, 30, "PSQ:");
	date = new Fl_Multiline_Input(178, 5, 70, 30, "Date:");

	user_name = new Fl_Multiline_Input(323, 5, 70, 30, "Username:");
	end_date = new Fl_Multiline_Input(64, 70, 70, 30, "End Date:");

	member_enrollment_id = new Fl_Multiline_Input(181, 70, 70, 30, "Enr ID:");
	member_account_id = new Fl_Multiline_Input(323, 70, 70, 30, "Acct ID:");

	end();
	show();
}


EndDateScript::~EndDateScript()
{
}

void EndDateScript::cb_generate()
{
	string line;
	string lines = "";

	script_name = "wwsa_cov_end_date_update_PSQ";
	script_name += psq_number->value();
	script_name += "_";
	script_name += date->value();
	script_name += ".sql";

	//username = gc_user->value();//create widget in constructor

	while (getline(input_stream, line))
	{
		if (line == "SPOOL wwsa_cov_end_date_update_")
		{
			line += "PSQ";
			line += psq_number->value();
			line += "_";
			line += date->value();
			line += ".log";
		}
		else if (line == "   gc_user         CONSTANT VARCHAR2 (30) :=")
		{
			line += "'";
			line += user_name->value();
			line += "';";
		}
		else if (line == "   gc_developer    CONSTANT VARCHAR2 (30) :=")
		{
			line += "'";
			line += user_name->value();
			line += "';";
		}
		else if (line == "   v_script_name            ")
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
		else if (line == "   v_member_enrollment_id   NUMBER :=")
		{
			line += " ";
			line += member_enrollment_id->value();
			line += ";";
		}

		else if (line == "   v_member_account_id      NUMBER :=")
		{
			line += " ";
			line += member_account_id->value();
			line += ";";
		}
		else if (line == "         SET COVERAGE_END_DATE")
		{
			line += " = '";
			line += end_date->value();
			line += "',";
		}
		else if (line == "             account_end_date")
		{
			line += " = '";
			line += end_date->value();
			line += "',";
		}

		lines += line + "\n";
	}


	//create output file
	output_stream.open(script_name);

	output_stream << lines;
	output_stream.close();

	cb_close();
}
