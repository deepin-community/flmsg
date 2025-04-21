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

#include "gettext.h"
#include "status.h"
#include "util.h"

#include "flmsg_dialog.h"
#include "flmsg.h"
#include "combo.h"

Fl_Group	*tab_f126 = (Fl_Group *)0;
Fl_Tabs		*tabs_f126 = (Fl_Tabs *)0;
Fl_Group	*tab_f126_message = (Fl_Group *)0;
Fl_Group	*tab_f126_information = (Fl_Group *)0;

Fl_Input2 *f126_txt_nbr = (Fl_Input2 *)0;
Fl_ListBox *f126_sel_prec = (Fl_ListBox *)0;

Fl_Input2 *f126_txt_dtm = (Fl_Input2 *)0;
Fl_Button *f126_btn_dtm = (Fl_Button *)0;

Fl_Input2 *f126_txt_from = (Fl_Input2 *)0;
Fl_Input2 *f126_txt_to = (Fl_Input2 *)0;
Fl_Input2 *f126_txt_info = (Fl_Input2 *)0;

Fl_Input2 *f126_txt_subj = (Fl_Input2 *)0;

Fl_Input2 *f126_txt_grpcnt = (Fl_Input2 *)0;
Fl_Button *f126_btn_check = (Fl_Button *)0;

FTextEdit *f126_txt_msg = (FTextEdit *)0;

Fl_Input2 *f126_txt_rcvd_fm = (Fl_Input2 *)0;
Fl_Input2 *f126_txt_rcvd_dtm = (Fl_Input2 *)0;
Fl_Button *f126_btn_rcvd_dtm = (Fl_Button *)0;

Fl_Input2 *f126_txt_sent_to = (Fl_Input2 *)0;
Fl_Input2 *f126_txt_sent_dtm = (Fl_Input2 *)0;
Fl_Button *f126_btn_sent_dtm = (Fl_Button *)0;

Fl_Input2 *f126_txt_rcvop = (Fl_Input2 *)0;
Fl_Input2 *f126_txt_sendop = (Fl_Input2 *)0;

static void cb_f126_txt_nbr(Fl_Input2*, void*) {
  f126_cb_nbr(f126_txt_nbr);
  estimate();
}

static void cb_f126_txt_from(Fl_Input2*, void*) {
  f126_cb_filter_input(f126_txt_from);
  estimate();
}

static void cb_f126_txt_to(Fl_Input2*, void*) {
  f126_cb_filter_input(f126_txt_to);
  estimate();
}

static void cb_f126_txt_info(Fl_Input2*, void*) {
  f126_cb_filter_input(f126_txt_info);
  estimate();
}

static void cb_f126_txt_subj(Fl_Input2*, void*) {
  f126_cb_filter_input(f126_txt_subj);
  estimate();
}

static void cb_f126_txt_rcvop(Fl_Input2*, void*) {
  f126_cb_filter_input(f126_txt_rcvop);
  estimate();
}

static void cb_f126_txt_sendop(Fl_Input2*, void*) {
  f126_cb_filter_input(f126_txt_sendop);
  estimate();
}

static void cb_f126_txt_rcvd_fm (Fl_Input2*, void*) {
  f126_cb_filter_input(f126_txt_rcvd_fm);
  estimate();
}

static void cb_f126_txt_sent_to (Fl_Input2*, void*) {
  f126_cb_filter_input(f126_txt_sent_to);
  estimate();
}

static void cb_f126_btn_dtm(Fl_Button*, void*) {
  f126_cb_set_dtm();
  estimate();
}

static void cb_f126_btn_rcvd_dtm(Fl_Button*, void*) {
  f126_cb_set_rcvd_dtm();
  estimate();
}

static void cb_f126_btn_sent_dtm(Fl_Button*, void*) {
  f126_cb_set_sent_dtm();
  estimate();
}

static void cb_f126_txt_msg(FTextEdit*, void*) {
  f126_btn_check->labelcolor(FL_RED);
  f126_btn_check->redraw_label();
  estimate();
}

static void cb_f126_btn_check(Fl_Button*, void*) {
  f126_cb_check();
}

void f126_changed(Fl_Widget *, void *)
{
	estimate();
}

void create_f126_tab()
{
	int Y = tab_top;
	tab_f126 = new Fl_Group(0, Y, 570, 380);
	tab_f126->align(FL_ALIGN_TOP);

		Y += 4;
		f126_txt_nbr = new Fl_Input2(80, Y, 80, 22, _("MSG NR:"));
		f126_txt_nbr->tooltip(_("* Optional Field\nMessage number at station of origin"));
		f126_txt_nbr->box(FL_DOWN_BOX);
		f126_txt_nbr->color((Fl_Color)FL_BACKGROUND2_COLOR);
		f126_txt_nbr->selection_color((Fl_Color)FL_SELECTION_COLOR);
		f126_txt_nbr->labeltype(FL_NORMAL_LABEL);
		f126_txt_nbr->labelfont(0);
		f126_txt_nbr->labelsize(14);
		f126_txt_nbr->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
		f126_txt_nbr->callback((Fl_Callback*)cb_f126_txt_nbr);
		f126_txt_nbr->align(FL_ALIGN_LEFT);
		f126_txt_nbr->callback(f126_changed);
		f126_txt_nbr->when(FL_WHEN_CHANGED);

		Y += 24;
		f126_sel_prec = new Fl_ListBox(80, Y, 120, 22, _("PREC"));
		f126_sel_prec->tooltip(_("Message Precedence"));
		f126_sel_prec->align(FL_ALIGN_LEFT);

		Y += 24;
		f126_txt_dtm = new Fl_Input2(80, Y, 160, 22, _("DTG:"));
		f126_txt_dtm->tooltip(_("Date of filing"));
		f126_txt_dtm->box(FL_DOWN_BOX);
		f126_txt_dtm->color((Fl_Color)FL_BACKGROUND2_COLOR);
		f126_txt_dtm->selection_color((Fl_Color)FL_SELECTION_COLOR);
		f126_txt_dtm->labeltype(FL_NORMAL_LABEL);
		f126_txt_dtm->labelfont(0);
		f126_txt_dtm->labelsize(14);
		f126_txt_dtm->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
		f126_txt_dtm->align(FL_ALIGN_LEFT);
		f126_txt_dtm->callback(f126_changed);
		f126_txt_dtm->when(FL_WHEN_CHANGED);

		f126_btn_dtm = new Fl_Button(244, Y, 20, 20, _("..."));
		f126_btn_dtm->tooltip(_("Today's date time group"));
		f126_btn_dtm->callback((Fl_Callback*)cb_f126_btn_dtm);

		Y += 24;
		f126_txt_from = new Fl_Input2(80, Y, 250, 22, _("FROM:"));
		f126_txt_from->tooltip(_("Station call sign / name"));
		f126_txt_from->box(FL_DOWN_BOX);
		f126_txt_from->color((Fl_Color)FL_BACKGROUND2_COLOR);
		f126_txt_from->selection_color((Fl_Color)FL_SELECTION_COLOR);
		f126_txt_from->labeltype(FL_NORMAL_LABEL);
		f126_txt_from->labelfont(0);
		f126_txt_from->labelsize(14);
		f126_txt_from->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
		f126_txt_from->callback((Fl_Callback*)cb_f126_txt_from);
		f126_txt_from->align(FL_ALIGN_LEFT);
		f126_txt_from->when(FL_WHEN_CHANGED);

		Y += 24;
		f126_txt_to = new Fl_Input2(80, Y, 486, 22, _("TO"));
		f126_txt_to->tooltip(_("Addressee"));
		f126_txt_to->type(4);
		f126_txt_to->box(FL_DOWN_BOX);
		f126_txt_to->color((Fl_Color)FL_BACKGROUND2_COLOR);
		f126_txt_to->selection_color((Fl_Color)FL_SELECTION_COLOR);
		f126_txt_to->labeltype(FL_NORMAL_LABEL);
		f126_txt_to->labelfont(0);
		f126_txt_to->labelsize(14);
		f126_txt_to->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
		f126_txt_to->callback((Fl_Callback*)cb_f126_txt_to);
		f126_txt_to->align(FL_ALIGN_LEFT);
		f126_txt_to->when(FL_WHEN_CHANGED);

		Y += 24;
		f126_txt_info = new Fl_Input2(80, Y, 486, 22, _("INFO:"));
		f126_txt_info->tooltip(_("* Optional Field\nInfo addressee(s)"));
		f126_txt_info->type(4);
		f126_txt_info->box(FL_DOWN_BOX);
		f126_txt_info->color((Fl_Color)FL_BACKGROUND2_COLOR);
		f126_txt_info->selection_color((Fl_Color)FL_SELECTION_COLOR);
		f126_txt_info->labeltype(FL_NORMAL_LABEL);
		f126_txt_info->labelfont(0);
		f126_txt_info->labelsize(14);
		f126_txt_info->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
		f126_txt_info->callback((Fl_Callback*)cb_f126_txt_info);
		f126_txt_info->align(FL_ALIGN_LEFT);
		f126_txt_info->when(FL_WHEN_CHANGED);

		Y += 24;
		f126_txt_subj = new Fl_Input2(80, Y, 486, 22, _("SUBJ:"));
		f126_txt_subj->tooltip(_("* Optional Field\nMessage subject"));
		f126_txt_subj->type(4);
		f126_txt_subj->box(FL_DOWN_BOX);
		f126_txt_subj->color((Fl_Color)FL_BACKGROUND2_COLOR);
		f126_txt_subj->selection_color((Fl_Color)FL_SELECTION_COLOR);
		f126_txt_subj->labeltype(FL_NORMAL_LABEL);
		f126_txt_subj->labelfont(0);
		f126_txt_subj->labelsize(14);
		f126_txt_subj->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
		f126_txt_subj->callback((Fl_Callback*)cb_f126_txt_subj);
		f126_txt_subj->align(FL_ALIGN_LEFT);
		f126_txt_subj->when(FL_WHEN_CHANGED);

		Y += 24;
		f126_txt_grpcnt = new Fl_Input2(488, Y, 50, 22, _("GROUP COUNT"));
		f126_txt_grpcnt->tooltip(_("* Optional Field\n# words in message"));
		f126_txt_grpcnt->box(FL_DOWN_BOX);
		f126_txt_grpcnt->color((Fl_Color)FL_BACKGROUND2_COLOR);
		f126_txt_grpcnt->selection_color((Fl_Color)FL_SELECTION_COLOR);
		f126_txt_grpcnt->labeltype(FL_NORMAL_LABEL);
		f126_txt_grpcnt->labelfont(0);
		f126_txt_grpcnt->labelsize(14);
		f126_txt_grpcnt->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
		f126_txt_grpcnt->align(FL_ALIGN_LEFT);
		f126_txt_grpcnt->callback(f126_changed);
		f126_txt_grpcnt->when(FL_WHEN_CHANGED);

		f126_btn_check = new Fl_Button(544, Y, 22, 22, _("ck"));
		f126_btn_check->tooltip(_("* Optional Field\nCompute group count"));
		f126_btn_check->callback((Fl_Callback*)cb_f126_btn_check);

		Y += 24;
		f126_txt_msg = new FTextEdit(4, Y, 562, 118, _("MESSAGE"));
		f126_txt_msg->tooltip(_("Message contents"));
		f126_txt_msg->box(FL_DOWN_BOX);
		f126_txt_msg->color((Fl_Color)FL_BACKGROUND2_COLOR);
		f126_txt_msg->selection_color((Fl_Color)FL_SELECTION_COLOR);
		f126_txt_msg->labeltype(FL_NORMAL_LABEL);
		f126_txt_msg->labelfont(0);
		f126_txt_msg->labelsize(14);
		f126_txt_msg->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
		f126_txt_msg->callback((Fl_Callback*)cb_f126_txt_msg);
		f126_txt_msg->align(FL_ALIGN_TOP_LEFT);
		f126_txt_msg->callback(f126_changed);
		f126_txt_msg->when(FL_WHEN_CHANGED);

		Y += 122;
		f126_txt_rcvd_fm = new Fl_Input2(60, Y, 220, 22, _("FROM:"));
		f126_txt_rcvd_fm->tooltip(_("Call sign of sender"));
		f126_txt_rcvd_fm->box(FL_DOWN_BOX);
		f126_txt_rcvd_fm->color((Fl_Color)FL_BACKGROUND2_COLOR);
		f126_txt_rcvd_fm->selection_color((Fl_Color)FL_SELECTION_COLOR);
		f126_txt_rcvd_fm->labeltype(FL_NORMAL_LABEL);
		f126_txt_rcvd_fm->labelfont(0);
		f126_txt_rcvd_fm->labelsize(14);
		f126_txt_rcvd_fm->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
		f126_txt_rcvd_fm->align(FL_ALIGN_LEFT);
		f126_txt_rcvd_fm->callback((Fl_Callback*)cb_f126_txt_rcvd_fm);
		f126_txt_rcvd_fm->when(FL_WHEN_CHANGED);

		f126_txt_sent_to = new Fl_Input2(336, Y, 220, 22, _("TO:"));
		f126_txt_sent_to->tooltip(_("Call sign of sender"));
		f126_txt_sent_to->box(FL_DOWN_BOX);
		f126_txt_sent_to->color((Fl_Color)FL_BACKGROUND2_COLOR);
		f126_txt_sent_to->selection_color((Fl_Color)FL_SELECTION_COLOR);
		f126_txt_sent_to->labeltype(FL_NORMAL_LABEL);
		f126_txt_sent_to->labelfont(0);
		f126_txt_sent_to->labelsize(14);
		f126_txt_sent_to->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
		f126_txt_sent_to->align(FL_ALIGN_LEFT);
		f126_txt_sent_to->callback((Fl_Callback*)cb_f126_txt_sent_to);
		f126_txt_sent_to->when(FL_WHEN_CHANGED);

		Y += 24;
		f126_txt_rcvd_dtm = new Fl_Input2(60, Y, 160, 22, _("DTG:"));
		f126_txt_rcvd_dtm->tooltip(_("date of receipt"));
		f126_txt_rcvd_dtm->box(FL_DOWN_BOX);
		f126_txt_rcvd_dtm->color((Fl_Color)FL_BACKGROUND2_COLOR);
		f126_txt_rcvd_dtm->selection_color((Fl_Color)FL_SELECTION_COLOR);
		f126_txt_rcvd_dtm->labeltype(FL_NORMAL_LABEL);
		f126_txt_rcvd_dtm->labelfont(0);
		f126_txt_rcvd_dtm->labelsize(14);
		f126_txt_rcvd_dtm->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
		f126_txt_rcvd_dtm->align(FL_ALIGN_LEFT);
		f126_txt_rcvd_dtm->callback(f126_changed);
		f126_txt_rcvd_dtm->when(FL_WHEN_CHANGED);

		f126_btn_rcvd_dtm = new Fl_Button(224, Y, 20, 20, _("..."));
		f126_btn_rcvd_dtm->tooltip(_("Today's date time group"));
		f126_btn_rcvd_dtm->callback((Fl_Callback*)cb_f126_btn_rcvd_dtm);

		f126_txt_sent_dtm = new Fl_Input2(336, Y, 160, 22, _("DTG:"));
		f126_txt_sent_dtm->tooltip(_("date of receipt"));
		f126_txt_sent_dtm->box(FL_DOWN_BOX);
		f126_txt_sent_dtm->color((Fl_Color)FL_BACKGROUND2_COLOR);
		f126_txt_sent_dtm->selection_color((Fl_Color)FL_SELECTION_COLOR);
		f126_txt_sent_dtm->labeltype(FL_NORMAL_LABEL);
		f126_txt_sent_dtm->labelfont(0);
		f126_txt_sent_dtm->labelsize(14);
		f126_txt_sent_dtm->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
		f126_txt_sent_dtm->align(FL_ALIGN_LEFT);
		f126_txt_sent_dtm->callback(f126_changed);
		f126_txt_sent_dtm->when(FL_WHEN_CHANGED);

		f126_btn_sent_dtm = new Fl_Button(500, Y, 20, 20, _("..."));
		f126_btn_sent_dtm->tooltip(_("Today's date time group"));
		f126_btn_sent_dtm->callback((Fl_Callback*)cb_f126_btn_sent_dtm);

		Y += 24;
		f126_txt_rcvop = new Fl_Input2(200, Y, 80, 22, _("RCVG OPERATOR INIT'S:"));
		f126_txt_rcvop->tooltip(_(""));
		f126_txt_rcvop->box(FL_DOWN_BOX);
		f126_txt_rcvop->color((Fl_Color)FL_BACKGROUND2_COLOR);
		f126_txt_rcvop->selection_color((Fl_Color)FL_SELECTION_COLOR);
		f126_txt_rcvop->labeltype(FL_NORMAL_LABEL);
		f126_txt_rcvop->labelfont(0);
		f126_txt_rcvop->labelsize(14);
		f126_txt_rcvop->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
		f126_txt_rcvop->align(FL_ALIGN_LEFT);
		f126_txt_rcvop->callback((Fl_Callback*)cb_f126_txt_rcvop);
		f126_txt_rcvop->when(FL_WHEN_CHANGED);

		f126_txt_sendop = new Fl_Input2(476, Y, 80, 22, _("SNDG OPERATOR INIT'S:"));
		f126_txt_sendop->tooltip(_(""));
		f126_txt_sendop->box(FL_DOWN_BOX);
		f126_txt_sendop->color((Fl_Color)FL_BACKGROUND2_COLOR);
		f126_txt_sendop->selection_color((Fl_Color)FL_SELECTION_COLOR);
		f126_txt_sendop->labeltype(FL_NORMAL_LABEL);
		f126_txt_sendop->labelfont(0);
		f126_txt_sendop->labelsize(14);
		f126_txt_sendop->labelcolor((Fl_Color)FL_FOREGROUND_COLOR);
		f126_txt_sendop->align(FL_ALIGN_LEFT);
		f126_txt_sendop->callback((Fl_Callback*)cb_f126_txt_sendop);
		f126_txt_sendop->when(FL_WHEN_CHANGED);

	tab_f126->end();
	tab_f126->hide();
}

