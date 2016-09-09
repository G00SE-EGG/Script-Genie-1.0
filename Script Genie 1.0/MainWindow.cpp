#include "MainWindow.h"

using namespace std;


MainWindow::MainWindow()
	:
	Fl_Window(640, 480, "Script Genie")
{
	_screen_width = 640;
	_screen_height = 480;

	//everything between begin and end is added as children of the window
	begin();
	//color(fl_rgb_color(0,2,9));
	buff = new Fl_Text_Buffer();
	description = new Fl_Text_Display(140, 50, 380, 300, "");
	description->buffer(buff);


	script_choices = new Fl_Choice(294, 10, 150, 30, "Script Template:");
	buff->text("No script chosen");
	script_choices->add("choose a script");
	script_choices->add("Coverage Effective Date Update");
	script_choices->add("Coverage End Date Update");
	script_choices->add("Delete Stuck Emails");
	script_choices->add("Close Account");
	script_choices->add("Update Payment Status");
	script_choices->add("Wallet Change");
	script_choices->add("Unverify Card Txn");
	script_choices->add("Remove Term and Sep Dates");
	script_choices->add("Reactivate HSA");
	script_choices->add("AutoAdjudicate Txn");
	script_choices->add("Balance Adjustment");
	script_choices->callback(cb_choices_i, this);
	script_choices->value(0);



	//buttons add/callbacks
	btn_use_script = new Fl_Button(190, 400, 120, 30, "Use Script");
	btn_use_script->callback(cb_select_i, this);

	btn_add_new_script = new Fl_Button(315, 400, 120, 30, "Add New Script");
	end();

	show();
}


MainWindow::~MainWindow()
{
}

void MainWindow::cb_choices_i(Fl_Widget* w, void* v)
{
	((MainWindow*)v)->cb_choices();
}
void  MainWindow::cb_choices()
{

	switch (script_choices->value())
	{
	case 0:
		{
			buff->text("No script chosen");
		}		
		break;
	case 1:
		script_type = 1;
		buff->text(getDesc(script_type).c_str());
		break;
	case 2:
		script_type = 2;
		buff->text(getDesc(script_type).c_str());
		break;
	case 3:
		script_type = 3;
		buff->text(getDesc(script_type).c_str());
		break;
	case 4:
		script_type = 4;
		buff->text(getDesc(script_type).c_str());
		break;
	case 5:
		script_type = 5;
		buff->text(getDesc(script_type).c_str());
		break;
	case 6:
		script_type = 6;
		buff->text(getDesc(script_type).c_str());
		break;
	case 7:
		script_type = 7;
		buff->text(getDesc(script_type).c_str());
		break;
	case 8:
		script_type = 8;
		buff->text(getDesc(script_type).c_str());
		break;
	case 9:
		script_type = 9;
		buff->text(getDesc(script_type).c_str());
		break;
	case 10:
		script_type = 10;
		buff->text(getDesc(script_type).c_str());
		break;
	case 11:
		script_type = 11;
		buff->text(getDesc(script_type).c_str());
		break;
	default:
		break;
	}


}

void MainWindow::cb_select_i(Fl_Widget* w, void* v)
{
	((MainWindow*)v)->cb_select();
}

void MainWindow::cb_select()
{
	switch (script_choices->value())
	{
	case 1:
		script_window = new EffetDateScript(100, 100, 410, 150, "Coverage Effective Date");
		break;
	case 2:
		script_window = new EndDateScript(100, 100, 410, 150, "Coverage End Date");
		break;
	case 3:
		script_window = new DelEmailsScript(100, 100, 600, 500, "Delete Stuck Emails");
		break;
	case 4:
		script_window = new CloseAcctScript(100, 100, 410, 150, "Close Account");
		break;
	case 5:
		script_window = new UpdPmtStatScript(100, 100, 410, 150, "Update Payment Status");
		break;
	case 6:
		script_window = new WalletChangeScript(100, 100, 430, 150, "Wallet Change");
		break;
	case 7:
		script_window = new UnverifyTxnScript(100, 100, 430, 150, "Unverify Card Txn");
		break;
	case 8:
		script_window = new RmvTermSepScript(100, 100, 430, 150, "Remove Term/Sep Dates");
		break;
	case 9:
		script_window = new ReactHSAScript(100, 100, 430, 150, "Reactivate HSA");
		break;
	case 10:
		script_window = new AutoAdjScript(100, 100, 430, 150, "AutoAdjudicate Txn");
		break;
	case 11:
		script_window = new BalanceAdjScript(100, 100, 600, 400, "Balance Adjustment");
		break;
	default:
		break;
	}
}

string MainWindow::getDesc(int type)
{

	std::string line;
	std::string texxt = "";

	switch (type)
	{
	case 1:
	{
		script_desc_stream.open("cov_eff_date_desc.txt");
		while (std::getline(script_desc_stream, line))
		{
			texxt += line + "\n";
		}
		script_desc_stream.close();
	}
		break;
	case 2:
	{
		script_desc_stream.open("cov_end_date_desc.txt");
		while (std::getline(script_desc_stream, line))
		{
			texxt += line + "\n";
		}
		script_desc_stream.close();
	}
		break;
	case 3:
	{
		script_desc_stream.open("delete_stuck_emails_desc.txt");
		while (std::getline(script_desc_stream, line))
		{
			texxt += line + "\n";
		}
		script_desc_stream.close();
	}		
		break;
	case 4:
	{
		script_desc_stream.open("close_acct_desc.txt");
		while (std::getline(script_desc_stream, line))
		{
			texxt += line + "\n";
		}
		script_desc_stream.close();
	}
	break;
	case 5:
	{
		script_desc_stream.open("upd_pmt_status_desc.txt");
		while (std::getline(script_desc_stream, line))
		{
			texxt += line + "\n";
		}
		script_desc_stream.close();
	}
	break;
	case 6:
	{
		script_desc_stream.open("wallet_change_desc.txt");
		while (std::getline(script_desc_stream, line))
		{
			texxt += line + "\n";
		}
		script_desc_stream.close();
	}
	break;
	case 7:
	{
		script_desc_stream.open("unverify_card_txn_desc.txt");
		while (std::getline(script_desc_stream, line))
		{
			texxt += line + "\n";
		}
		script_desc_stream.close();
	}
	break;
	case 8:
	{
		script_desc_stream.open("remove_term_sep_dates_desc.txt");
		while (std::getline(script_desc_stream, line))
		{
			texxt += line + "\n";
		}
		script_desc_stream.close();
	}
	break;
	case 9:
	{
		script_desc_stream.open("reactivate_hsa_account_desc.txt");
		while (std::getline(script_desc_stream, line))
		{
			texxt += line + "\n";
		}
		script_desc_stream.close();
	}
	break;
	case 10:
	{
		script_desc_stream.open("autoadjudicate_card_txn_desc.txt");
		while (std::getline(script_desc_stream, line))
		{
			texxt += line + "\n";
		}
		script_desc_stream.close();
	}
	break;
	case 11:
	{
		script_desc_stream.open("create_manual_adjustment_desc.txt");
		while (std::getline(script_desc_stream, line))
		{
			texxt += line + "\n";
		}
		script_desc_stream.close();
	}
	break;
	default:
		break;
	}

	return texxt;
}