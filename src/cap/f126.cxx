// ----------------------------------------------------------------------------
// Copyright (C) 2014
//              David Freese, W1HKJ
//
// This file is part of flmsg
//
// flrig is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// flrig is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>

#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Sys_Menu_Bar.H>
#include <FL/x.H>
#include <FL/Fl_Help_Dialog.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_File_Icon.H>

#include "config.h"
#include "flmsg_config.h"

#include "flmsg.h"
#include "templates.h"
#include "debug.h"
#include "util.h"
#include "gettext.h"
#include "flmsg_dialog.h"
#include "flinput2.h"
#include "date.h"
#include "calendar.h"
#include "icons.h"
#include "fileselect.h"
#include "wrap.h"
#include "status.h"
#include "parse_xml.h"
#include "flmsg_strings.h"

#ifdef WIN32
#  include "flmsgrc.h"
#  include "compat.h"
#  define dirent fl_dirent_no_thanks
#endif

#include <FL/filename.H>
#include "dirent-check.h"

#include <FL/x.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Image.H>

std::string f126_base_filename = "";
std::string f126_def_filename = "";
std::string f126_def_template_name = "";

static std::string f126_buffer;

// f126_fields

const char *f126_s_prec[] = {"ROUTINE","PRIORITY","IMMEDIATE","FLASH"};
const char f126_prec_items[] = "ROUTINE|PRIORITY|IMMEDIATE|FLASH";

std::string f126_nbr      = ":msg nbr:";
std::string f126_prec     = ":prec:";
std::string f126_dtm      = ":dtm:";
std::string f126_from     = ":from:";
std::string f126_to       = ":to:";
std::string f126_info     = ":info:";
std::string f126_subj     = ":subj:";
std::string f126_grpcnt   = ":grpcnt:";
std::string f126_msg      = ":msgtxt:";
std::string f126_rcvd_fm  = ":rcvd_fm:";
std::string f126_sent_to  = ":sent_to:";
std::string f126_rcvd_dtm = ":rcvd_dtm:";
std::string f126_sent_dtm = ":sent_dtm:";
std::string f126_rcvop    = ":rcvop:";
std::string f126_sendop   = ":sendop:";

//struct FIELD { std::string f_type; std::string f_data; void **w; char w_type; };
FIELD f126_fields[] = {
{ f126_nbr,			"", (void **)&f126_txt_nbr,		't' },	// 0
{ f126_prec,		"", (void **)&f126_sel_prec,		's' },	// 1
{ f126_dtm,			"", (void **)&f126_txt_dtm,		't' },	// 2
{ f126_from,		"", (void **)&f126_txt_from,		't' },	// 3
{ f126_to,			"", (void **)&f126_txt_to,		't' },	// 4
{ f126_info,		"", (void **)&f126_txt_info,		't' },	// 5
{ f126_subj,		"", (void **)&f126_txt_subj,		't' },	// 6
{ f126_grpcnt,		"", (void **)&f126_txt_grpcnt,	't' },	// 7
{ f126_msg,			"", (void **)&f126_txt_msg,		'e' },	// 8
{ f126_rcvd_fm,		"", (void **)&f126_txt_rcvd_fm,	't' },	// 9
{ f126_sent_to,		"", (void **)&f126_txt_sent_to,	't' },	// 10
{ f126_rcvd_dtm,	"", (void **)&f126_txt_rcvd_dtm,	't' },	// 11
{ f126_sent_dtm,	"", (void **)&f126_txt_sent_dtm,	't' },	// 12
{ f126_rcvop,		"", (void **)&f126_txt_rcvop,		't' },	// 13
{ f126_sendop,		"", (void **)&f126_txt_sendop,	't' },	// 14
};

bool f126_using_template = false;

int f126_num_fields = sizeof(f126_fields) / sizeof(FIELD);

//======================================================================

void f126_cb_set_dtm()
{
	f126_txt_dtm->value(szCAPDateTime());
}

void f126_cb_set_rcvd_dtm()
{
	f126_txt_rcvd_dtm->value(szCAPDateTime());
}

void f126_cb_set_sent_dtm()
{
	f126_txt_sent_dtm->value(szCAPDateTime());
}

void f126_cb_nbr(Fl_Widget *wdg)
{
	Fl_Input2 *inp = (Fl_Input2 *)wdg;
	std::string s = inp->value();
	for (size_t n = 0; n < s.length(); n++)
		if (!isdigit(s[n])) s.erase(n,1);
	strip_leading_zeros(s);
	inp->value(s.c_str());
}

static char valid_input[] = "0123456789/,; ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";

void f126_cb_filter_input(Fl_Widget *wdg)
{
	Fl_Input2 *inp = (Fl_Input2 *)wdg;
	std::string s = inp->value();
	ucase(s);
	for (size_t n = 0; n < s.length(); n++)
		if (strchr(valid_input, s[n]) == NULL)
			s.erase(n,1);
	inp->value(s.c_str());
}

void f126_clear_fields()
{
	for (int i = 0; i < f126_num_fields; i++)
		f126_fields[i].f_data.clear();
}

static std::string numeric(int n)
{
	static char snum[12];
	snprintf(snum, sizeof(snum), "%d", n);
	return snum;
}

void f126_set_choices() {
	f126_sel_prec->clear();
	f126_sel_prec->add(f126_prec_items);
	f126_sel_prec->index(0);
}

bool f126_check_fields()
{
	for (int i = 0; i < f126_num_fields; i++) {
		if (f126_fields[i].w_type == 'd') {
			if (f126_fields[i].f_data != ((Fl_DateInput *)(*f126_fields[i].w))->value())
				return true;
		} else if (f126_fields[i].w_type == 't') {
			if (f126_fields[i].f_data != ((Fl_Input2 *)(*f126_fields[i].w))->value())
				return true;
		} else if (f126_fields[i].w_type == 's') {
			int choice = ((Fl_ListBox *)(*f126_fields[i].w))->index();
			if (choice >= 0) {
				if (f126_fields[i].f_data != numeric(choice))
					return true;
			}
		} else if (f126_fields[i].w_type == 'e') {
			if (f126_fields[i].f_data != ((FTextEdit *)(*f126_fields[i].w))->buffer()->text())
				return true;
		} else if (f126_fields[i].w_type == 'b') {
			std::string val = ((Fl_Button *)(*f126_fields[i].w))->value() ? "T" : "F";
			if (f126_fields[i].f_data != val)
				return true;
		}
	}
	return false;
}

void f126_update_fields()
{
	for (int i = 0; i < f126_num_fields; i++) {
		if (f126_fields[i].w_type == 'd') {
			f126_fields[i].f_data = ((Fl_DateInput *)(*f126_fields[i].w))->value();
		} else if (f126_fields[i].w_type == 't') {
			f126_fields[i].f_data = ((Fl_Input2 *)(*f126_fields[i].w))->value();
		} else if (f126_fields[i].w_type == 's') {
			int choice = ((Fl_ListBox *)(*f126_fields[i].w))->index();
			if (choice >= 0) {
				f126_fields[i].f_data = numeric(choice);
			}
		} else if (f126_fields[i].w_type == 'e') {
			f126_fields[i].f_data = ((FTextEdit *)(*f126_fields[i].w))->buffer()->text();
		} else if (f126_fields[i].w_type == 'b') {
			std::string val = ((Fl_Button *)(*f126_fields[i].w))->value() ? "T" : "F";
			f126_fields[i].f_data = val;
		}
	}
}

void f126_clear_form()
{
	f126_clear_fields();

	if (progStatus.rgnbr_fname)
		f126_txt_nbr->value(progStatus.rgnbr.c_str());
	else
		f126_txt_nbr->value("");

	for (int i = 1; i < f126_num_fields; i++)
		if (f126_fields[i].w_type == 'd')
			((Fl_DateInput *)(*f126_fields[i].w))->value("");
		else if (f126_fields[i].w_type == 't')
			((Fl_Input2 *)(*f126_fields[i].w))->value("");
		else if (f126_fields[i].w_type == 's')
			((Fl_ListBox *)(*f126_fields[i].w))->index(0);
		else if (f126_fields[i].w_type == 'e')
			((FTextEdit *)(*f126_fields[i].w))->clear();
		else if (f126_fields[i].w_type == 'b')
			((Fl_Button *)(*f126_fields[i].w))->value(0);
	f126_update_fields();
}

void f126_update_form()
{
	for (int i = 0; i < f126_num_fields; i++) {
		if (f126_fields[i].w_type == 'd')
			((Fl_DateInput *)(*f126_fields[i].w))->value(f126_fields[i].f_data.c_str());
		else if (f126_fields[i].w_type == 't')
			((Fl_Input2 *)(*f126_fields[i].w))->value(f126_fields[i].f_data.c_str());
		else if (f126_fields[i].w_type == 's')
			((Fl_ListBox *)(*f126_fields[i].w))->index(atoi(f126_fields[i].f_data.c_str()));
		else if (f126_fields[i].w_type == 'e') {
			((FTextEdit *)(*f126_fields[i].w))->clear();
			((FTextEdit *)(*f126_fields[i].w))->add(f126_fields[i].f_data.c_str());
		} else if (f126_fields[i].w_type == 'b')
			((Fl_Button *)(*f126_fields[i].w))->value(f126_fields[i].f_data == "T" ? 1 : 0);
	}
}

void f126_make_buffer(bool compress)
{
	std::string mbuff;
	mbuff.clear();
	for (int i = 0; i < f126_num_fields; i++)
		mbuff.append( lineout( f126_fields[i].f_type, f126_fields[i].f_data ) );
	if (compress) compress_maybe(mbuff);
	f126_buffer.append(mbuff);
}

void f126_read_buffer(std::string data)
{
	clear_fields();
	read_header(data);

	for (int i = 0; i < f126_num_fields; i++)
		f126_fields[i].f_data = findstr(data, f126_fields[i].f_type);

	f126_update_form();
}

void f126_cb_new()
{
	if (f126_check_fields()) {
		if (fl_choice2(xMODIFIED, xNO, xYES, NULL) == 1) {
			update_header(CHANGED);
			f126_cb_save();
		}
	}
	f126_update_fields();
	f126_clear_form();
	clear_header();
	f126_def_filename = ICS_msg_dir;
	f126_def_filename.append(xNEW).append(F126_FILE_EXT);
	f126_using_template = false;
	show_filename(f126_def_filename);
}

void f126_cb_import()
{
	fl_alert2(xNOTIMPLEMENTED);
}

void f126_cb_export()
{
	fl_alert2(xNOTIMPLEMENTED);
}

void f126_cb_wrap_import(std::string wrapfilename, std::string inpbuffer)
{
	f126_clear_form();
	f126_read_buffer(inpbuffer);
	f126_def_filename = ICS_msg_dir;
	f126_def_filename.append(wrapfilename);
	show_filename(f126_def_filename);
	f126_using_template = false;
}

int eval_f126_fsize()
{
	Ccrc16 chksum;
	evalstr.assign("[WRAP:beg][WRAP:lf][WRAP:fn ");
	evalstr.append(f126_base_filename).append("]");
	f126_update_fields();
	update_header(FROM);
	evalstr.append(header("<f126>"));
	f126_buffer.clear();
	f126_make_buffer(true);
	if (f126_buffer.empty()) return 0;
	evalstr.append( f126_buffer );
	evalstr.append("[WRAP:chksum ").append(chksum.scrc16(evalstr)).append("][WRAP:end]");
	return evalstr.length();
}

void f126_cb_wrap_export()
{
	if (f126_check_fields()) {
		if (fl_choice2(xMODIFIED, xNO, xYES, NULL) == 0)
			return;
		update_header(CHANGED);
	}
	f126_update_fields();

	if (f126_base_filename == std::string(xNEW).append(F126_FILE_EXT) || 
		f126_base_filename == std::string(xDEFAULT).append(F126_FILE_EXT) )
		if (!f126_cb_save_as()) return;

	std::string wrapfilename = WRAP_send_dir;
	wrapfilename.append(f126_base_filename);
	wrapfilename.append(WRAP_EXT);
	const char *p = FSEL::saveas(
			xSAVEASWRAP,
			xWRAPFILE,
			wrapfilename.c_str());
	if (p) {
		std::string pext = fl_filename_ext(p);
		wrapfilename = p;

		update_header(FROM);
		f126_buffer.assign(header("<f126>"));
		f126_make_buffer(true);
		export_wrapfile(f126_base_filename, wrapfilename, f126_buffer, pext != WRAP_EXT);

		f126_buffer.assign(header("<f126>"));
		f126_make_buffer(false);
		f126_write(f126_def_filename);
	}
}

void f126_cb_wrap_autosend()
{
	if (f126_check_fields()) {
		if (fl_choice2(xMODIFIED, xNO, xYES, NULL) == 0)
			return;
		update_header(CHANGED);
	}
	f126_update_fields();

	if (f126_base_filename == std::string(xNEW).append(F126_FILE_EXT) || 
		f126_base_filename == std::string(xDEFAULT).append(F126_FILE_EXT) )
		if (!f126_cb_save_as()) return;

	update_header(FROM);
	f126_buffer.assign(header("<f126>"));
	f126_make_buffer(true);
	xfr_via_socket(f126_base_filename, f126_buffer);

	f126_buffer.assign(header("<f126>"));
	f126_make_buffer(false);
	f126_write(f126_def_filename);
}

void f126_cb_load_template()
{
	std::string f126_def_filename = f126_def_template_name;
	const char *p = FSEL::select(
			xOPENTEMPLATE,
			std::string(xTEMPLATEFILE).append(F126_TEMP_EXT).c_str(),
			f126_def_filename.c_str());
	if (p) {
		f126_clear_form();
		read_data_file(p);
		f126_def_template_name = p;
		show_filename(f126_def_template_name);
		f126_using_template = true;
	}
}

void f126_cb_save_template()
{
	if (!f126_using_template) {
		f126_cb_save_as_template();
		return;
	}
	std::string f126_def_filename = f126_def_template_name;
	const char *p = FSEL::saveas(
			xSAVEASTEMPLATE,
			std::string(xTEMPLATEFILE).append(F126_TEMP_EXT).c_str(),
			f126_def_filename.c_str());
	if (p) {
		update_header(CHANGED);
		f126_update_fields();
		f126_buffer.assign(header("<f126>"));
		f126_make_buffer();
		f126_write(p);
	}
}

void f126_cb_save_as_template()
{
	std::string f126_def_filename = f126_def_template_name;
	const char *p = FSEL::saveas(
			xSAVEASTEMPLATE,
			std::string(xTEMPLATEFILE).append(F126_TEMP_EXT).c_str(),
			f126_def_filename.c_str());
	if (p) {
		const char *pext = fl_filename_ext(p);
		f126_def_template_name = p;
		if (strlen(pext) == 0) f126_def_template_name.append(F126_TEMP_EXT);
		remove_spaces_from_filename(f126_def_template_name);

		clear_header();
		update_header(CHANGED);
		f126_update_fields();
		f126_buffer.assign(header("<f126>"));
		f126_make_buffer();
		f126_write(f126_def_template_name);

		show_filename(f126_def_template_name);
		f126_using_template = true;
	}
}

void f126_cb_open()
{
	const char *p = FSEL::select(
			_(xOPENDATAFILE), 
			std::string("f126\t*").append(F126_FILE_EXT).c_str(),
			f126_def_filename.c_str());
	if (!p) return;
	if (strlen(p) == 0) return;
	f126_clear_form();
	read_data_file(p);
	f126_using_template = false;
	f126_def_filename = p;
	show_filename(f126_def_filename);
}

void f126_write(std::string s)
{
	FILE *f126_file = fopen(s.c_str(), "w");
	if (!f126_file) return;

	fwrite(f126_buffer.c_str(), f126_buffer.length(), 1, f126_file);
	fclose(f126_file);
}

bool f126_cb_save_as()
{
	const char *p;
	std::string newfilename;

	std::string name = named_file();
	if (!name.empty()) {
		name.append(F126_FILE_EXT);
		newfilename = ICS_msg_dir;
		newfilename.append(name);
	} else
		newfilename = f126_def_filename;

	p = FSEL::saveas(_(xSAVEDATAFILE), 
				std::string("f126\t*").append(F126_FILE_EXT).c_str(),
				newfilename.c_str());

	if (!p) return false;
	if (strlen(p) == 0) return false;

	if (progStatus.rgnbr_fname) {
		int n = atoi(progStatus.rgnbr.c_str());
		n++;
		char szn[12];
		snprintf(szn, sizeof(szn), "%d", n);
		progStatus.rgnbr = szn;
		txt_rgnbr->value(szn);
		txt_rgnbr->redraw();
	} else if (progStatus.sernbr_fname)
		update_sernbr();

	const char *pext = fl_filename_ext(p);
	f126_def_filename = p;
	if (strlen(pext) == 0) f126_def_filename.append(F126_FILE_EXT);

	remove_spaces_from_filename(f126_def_filename);

	update_header(NEW);
	f126_update_fields();
	f126_buffer.assign(header("<f126>"));
	f126_make_buffer();
	f126_write(f126_def_filename);

	f126_using_template = false;
	show_filename(f126_def_filename);
	return true;
}

void f126_cb_save()
{
	if (f126_base_filename == std::string(xNEW).append(F126_FILE_EXT) || 
		f126_base_filename == std::string(xDEFAULT).append(F126_FILE_EXT) ||
		f126_using_template == true) {
		f126_cb_save_as();
		return;
	}

	if (f126_check_fields()) update_header(CHANGED);
	f126_update_fields();
	f126_buffer.assign(header("<f126>"));
	f126_make_buffer();
	f126_write(f126_def_filename);

	f126_using_template = false;
}

void f126_cb_check()
{
	std::string temp = f126_txt_msg->buffer()->text();
	if (temp.empty()) {
		f126_txt_grpcnt->value("");
		f126_btn_check->labelcolor(FL_BLACK);
		f126_btn_check->redraw_label();
		return;
	}

	// convert to uppercase
	for (size_t n = 0; n < temp.length(); n++)
		temp[n] = toupper(temp[n]);
	// convert tabs to 5 spaces
	size_t pos = std::string::npos;
	while ((pos = temp.find("\t")) != std::string::npos)
		temp.replace(pos, 1, "     ");
	// return converted text to editor
	f126_txt_msg->clear();
	f126_txt_msg->addstr(temp.c_str());

// compute word count
// remove any user inserted end-of-lines
	while ((pos = temp.find('\n')) != std::string::npos) temp[pos] = ' ';
// only single spaces no trailing spaces, no leading spaces
	while ((pos = temp.find("  ")) != std::string::npos) temp.erase(pos,1);
	while (temp[temp.length() -1] == ' ') temp.erase(temp.length()-1, 1);
	if (temp[0] == ' ') temp.erase(0,1);
// count number of words in textf126_def_filename
	int numwords = 0;
	if (temp.length()) {
		pos = 0;
		numwords = 1;
		while ((pos = temp.find(" ", pos + 1)) != std::string::npos) numwords++;
	}

	char snum[15];
	snprintf(snum, sizeof(snum), "%d", numwords);
	f126_grpcnt = snum;
	f126_txt_grpcnt->value(snum);
	f126_update_fields();
	f126_btn_check->labelcolor(FL_BLACK);
	f126_btn_check->redraw_label();
}

void f126_cb_html()
{
	std::string f126_name;
	std::string html_text;
	unsigned int nbr;
	f126_name = ICS_dir;
	f126_name.append("f126.html");

	f126_update_fields();
	f126_cb_check();
	std::string form = f126_html_template;

std::string pg = ":pg:";
std::string pgnr = ":npgs:";
std::string pgone = "1";
	replacestr( form, pg, pgone);
	replacestr( form, pgnr, pgone);
	for (int i = 0; i < f126_num_fields; i++) {
		if (f126_fields[i].f_type == f126_prec) {
			sscanf(f126_fields[i].f_data.c_str(), "%u", &nbr);
			if (nbr >= 0 && nbr < (sizeof(f126_s_prec) / sizeof(*f126_s_prec)))
				html_text = f126_s_prec[nbr];
			else
				html_text = "";
			replacestr( form, f126_fields[i].f_type, html_text );
		} else if (f126_fields[i].w_type == 'b') {
			replacestr( form, f126_fields[i].f_type, f126_fields[i].f_data == "T" ? yes : no);
		} else if (f126_fields[i].w_type == 'e') {
			std::string temp = f126_fields[i].f_data;
			size_t p = 0;
			while ( (p = temp.find("\n")) != std::string::npos)
				temp.replace(p, 1, "<br>");
			replacestr( form, f126_fields[i].f_type, temp);
		} else
			replacestr( form, f126_fields[i].f_type, f126_fields[i].f_data );
	}

	std::string rxstr = "";
	rxstr.append(progStatus.my_call).append(" ").append(progStatus.my_tel);
	rxstr.append("<br>").append(progStatus.my_name);
	rxstr.append("<br>").append(progStatus.my_addr);
	rxstr.append("<br>").append(progStatus.my_city);
	html_text = ":rx:";
	replacestr( form, html_text, rxstr);

	html_text = ":exp:";
	std::string arlmsgs = "";
	if (progStatus.arl_desc)
		arlmsgs = expand_arl(f126_fields[10].f_data);
	replacestr( form, html_text, arlmsgs);

	FILE *f126_file = fopen(f126_name.c_str(), "w");
	fprintf(f126_file,"%s", form.c_str());
	fclose(f126_file);

	open_url(f126_name.c_str());
}

void f126_cb_textout()
{
	std::string f126_name;
	std::string lines;
	std::string str;
	int nbr = 0;
	f126_name = ICS_dir;
	f126_name.append("f126.txt");

	f126_update_fields();
	f126_cb_check();

	std::string form = f126_txt_template;

	for (int i = 0; i < f126_num_fields; i++) {
		str.clear();
		if (f126_fields[i].f_type == f126_prec) {
			sscanf(f126_fields[i].f_data.c_str(), "%d", &nbr);
			str = f126_s_prec[nbr];
			if (str.find("EMERGENCY") == std::string::npos)
				str = str[0];
			replacestr( form, f126_fields[i].f_type, str);
		} else {
			str = f126_fields[i].f_data;
//			strip_lfs(str);
			replacestr( form, f126_fields[i].f_type, str);
		}
	}

	FILE *f126_file = fopen(f126_name.c_str(), "w");
	fprintf(f126_file,"%s", form.c_str());
	fclose(f126_file);
	open_url(f126_name.c_str());
}

