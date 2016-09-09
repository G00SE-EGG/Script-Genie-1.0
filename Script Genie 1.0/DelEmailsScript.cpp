#include "DelEmailsScript.h"

using namespace std;

DelEmailsScript::DelEmailsScript(int x, int y, int width, int height, char* title)
	:ScriptWindow(x, y, width, height, title)
{
	begin();

	input_stream.open("delete_emails_temp.txt");

	btn_generate = new Fl_Button(275, 420, 70, 40, "Generate");
	btn_generate->callback(cb_generate_i, this);

	psq_number = new Fl_Multiline_Input(130, 35, 70, 30, "PSQ:");
	date = new Fl_Multiline_Input(248, 35, 70, 30, "Date:");
	user_name = new Fl_Multiline_Input(393, 35, 70, 30, "Username:");


	buff = new Fl_Text_Buffer();
	msg_que_log_id = new Fl_Text_Editor(120, 140, 350, 250, "Message Queue Log Id's");
	msg_que_log_id->buffer(buff);

	end();
	show();
}


DelEmailsScript::~DelEmailsScript()
{
}

void DelEmailsScript::cb_generate()
{
	/*
	Read in each line into a vector, then print each out in rows of 10, 
	similar to comma separator program
	*/


	string line;
	string lines = "";
	string temp_lines;
	string words = buff->text();
	int line_count = 0;

	script_name = "wweb_delete_emails_PSQ";
	script_name += psq_number->value();
	script_name += "_";
	script_name += date->value();
	script_name += ".sql";

	//read buffer input into temporary file, then read contents of file to line
	msg_output_stream.open("temp_msg_file.txt");
	msg_output_stream << words;
	msg_output_stream.close();

	//read file contents into a vector
	msg_input_stream.open("temp_msg_file.txt");
	while (getline(msg_input_stream, temp_lines))
	{
		msg_log_ids.push_back(temp_lines);
	}


	//for (int i = 0; i < msg_log_ids.size(); i++)
	//{
	//	//cout << msg_log_ids[i] << endl;

	//	line_count++;

	//	if (line_count == 10)
	//	{
	//		cout << endl;
	//	}
	//	else if (i == (msg_log_ids.size() - 1))
	//	{
	//		cout << msg_log_ids[i];
	//	}
	//	else
	//	{
	//		cout << msg_log_ids[i] << ",";
	//		
	//	}
	//}

	msg_input_stream.close();


	//read input into string
	while (getline(input_stream, line))
	{
		if (line == "SPOOL wweb_delete_emails_")
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
		else if (line == "            IN")
		{
			line += "(";
			for (int i = 0; i < msg_log_ids.size(); i++)
			{
				
				line_count++;
				cout << line_count << endl;
				if (line_count == 10)
				{
					line += "\n";
					line_count = 0;
				}
				else if (i == (msg_log_ids.size() - 1))
				{
					line += msg_log_ids[i];
				}
				else
				{
					line += msg_log_ids[i] += ",";

				}
			}
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
