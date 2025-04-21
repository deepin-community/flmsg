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

#include "templates.h"

const char f126_html_template[] =
"<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">\n\
<html>\n\
<head><meta content=\"text/html; charset=UTF-8\" http-equiv=\"content-type\">\n\
<title>:TITLE:</title>\n\
</head>\n\
<body>\n\
<table cellpadding=\"0\" cellspacing=\"0\" width=\"800\">\n\
<col width=\"90\"><col width=\"10\"><col width=\"250\">\n\
<col width=\"90\"><col width=\"10\"><col width=\"250\">\n\
<tbody>\n\
<tr>\n\
<td colspan=\"6\" style=\"border-style: solid solid none solid; border-color: rgb(0, 0, 10) rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px; padding: 0in 0.08in;\" valign=\"top\">\n\
<p align=\"center\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
<b>RAFAC F126</b>\n\
</font></font>\n\
</p>\n\
</td>\n\
</tr>\n\
<tr>\n\
<td colspan=\"6\" align= \"right\" style=\"border-style: solid solid none solid; border-color: rgb(0, 0, 10) rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px; padding: 0in 0.08in;\" valign=\"top\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
Page :pg: of :npgs: Pages\n\
</font></font>\n\
</td>\n\
</tr>\n\
</tbody>\n\
<tbody>\n\
<tr valign=\"top\">\n\
<td align=\"right\" style=\"border-style: solid none none solid; border-color: rgb(0, 0, 10) rgb(0, 0, 10); border-width: 1px 1px 1px 1px; padding: 0in 0in 0in 0.08in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
MSG NUMBER: \n\
</font></font>\n\
</td>\n\
<td style=\"border-style: solid none none none;  border-width: 1px 1px 1px 1px; padding-bottom: 0in; padding-left: 0in; padding-right: 0in;\"></td>\n\
<td align=\"left\" colspan=\"4\" style=\"border-style: solid solid none none; border-color: rgb(0, 0, 10) rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px 1px; padding: 0in 0.08in 0in 0in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
:msg nbr:\n\
</font></font>\n\
</td>\n\
</tr>\n\
<tr valign=\"top\">\n\
<td align=\"right\" style=\"border-style: none none none solid; border-width: 1px 1px 1px 1px; padding: 0in 0in 0in 0.08in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
PRECEDENCE:\n\
</font></font>\n\
</td>\n\
<td style=\"border-style: none none none none;  border-width: 1px 1px 1px 1px; padding-bottom: 0in; padding-left: 0in; padding-right: 0in;\"></td>\n\
<td align=\"left\" colspan=\"4\" style=\"border-style: none solid none none; border-color: rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px 1px; padding: 0in 0.08in 0in 0in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
:prec:\n\
</font></font>\n\
</td>\n\
</tr>\n\
<tr valign=\"top\">\n\
<td align=\"right\" style=\"border-style: none none none solid; border-width: 1px 1px 1px 1px; padding: 0in 0in 0in 0.08in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
DTG:\n\
</font></font>\n\
</td>\n\
<td style=\"border-style: none none none none;  border-width: 1px 1px 1px 1px; padding-bottom: 0in; padding-left: 0in; padding-right: 0in;\"></td>\n\
<td align=\"left\" colspan=\"4\" style=\"border-style: none solid none none; border-color: rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px 1px; padding: 0in 0.08in 0in 0in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
:dtm:</font></font>\n\
</td>\n\
</tr>\n\
<tr valign=\"top\">\n\
<td align=\"right\" style=\"border-style: none none none solid; border-width: 1px 1px 1px 1px; padding: 0in 0in 0in 0.08in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
FROM:\n\
</font></font>\n\
</td>\n\
<td style=\"border-style: none none none none;  border-width: 1px 1px 1px 1px; padding-bottom: 0in; padding-left: 0in; padding-right: 0in;\"></td>\n\
<td align=\"left\" colspan=\"4\" style=\"border-style: none solid none none; border-color: rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px 1px; padding: 0in 0.08in 0in 0in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
:from:\n\
</font></font>\n\
</td>\n\
</tr>\n\
<tr valign=\"top\">\n\
<td align=\"right\" style=\"border-style: none none none solid; border-width: 1px 1px 1px 1px; padding: 0in 0in 0in 0.08in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
TO:\n\
</font></font>\n\
</td>\n\
<td style=\"border-style: none none none none;  border-width: 1px 1px 1px 1px; padding-bottom: 0in; padding-left: 0in; padding-right: 0in;\"></td>\n\
<td align=\"left\" colspan=\"4\" style=\"border-style: none solid none none; border-color: rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px 1px; padding: 0in 0.08in 0in 0in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
:to:\n\
</font></font>\n\
</td>\n\
</tr>\n\
<tr valign=\"top\">\n\
<td align=\"right\" style=\"border-style: none none none solid; border-width: 1px 1px 1px 1px; padding: 0in 0in 0in 0.08in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
INFO: \n\
</font></font>\n\
</td>\n\
<td style=\"border-style: none none none none;  border-width: 1px 1px 1px 1px; padding-bottom: 0in; padding-left: 0in; padding-right: 0in;\"></td>\n\
<td align=\"left\" colspan=\"4\" style=\"border-style: none solid none none; border-color: rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px 1px; padding: 0in 0.08in 0in 0in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
:info:\n\
</font></font>\n\
</td>\n\
</tr>\n\
<tr valign=\"top\">\n\
<td align=\"right\" style=\"border-style: none none none solid; border-width: 1px 1px 1px 1px; padding: 0in 0in 0in 0.08in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
SUBJ: \n\
</font></font>\n\
</td>\n\
<td style=\"border-style: none none none none;  border-width: 1px 1px 1px 1px; padding-bottom: 0in; padding-left: 0in; padding-right: 0in;\"></td>\n\
<td align=\"left\" colspan=\"4\" style=\"border-style: none solid none none; border-color: rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px 1px; padding: 0in 0.08in 0in 0in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
:subj:\n\
</font></font>\n\
</td>\n\
</tr>\n\
<tr><td colspan=\"6\" style=\"border-style: none solid none solid; border-color: rgb(0, 0, 10) rgb(0, 0, 10) rgb(0, 0, 10); border-width: 1px 1px 1px 1pt; padding: 0in 0in 0in 0.08in;\"><br></td>\n\
</tr>\n\
<tr valign=\"top\">\n\
<td align=\"right\" style=\"border-style: none none none solid; border-color: rgb(0, 0, 10) rgb(0, 0, 10); border-width: 1px 1px 0px 1px; padding: 0in 0in 0in 0in;\" >\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
GROUP COUNT: \n\
</font></font>\n\
</td>\n\
<td style=\"border-style: none none none none;  border-width: 1px 1px 1px 1px; padding-bottom: 0in; padding-left: 0in; padding-right: 0in;\"></td>\n\
<td align=\"left\" colspan=\"4\" style=\"border-style: none solid solid none; border-color: rgb(0, 0, 10) rgb(0, 0, 10) -moz-use-text-color; border-width: 0px 1px 0px 1px; padding: 0in 0.08in 0in 0in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
:grpcnt:\n\
</font></font>\n\
</td>\n\
</tr>\n\
</tbody>\n\
<tbody>\n\
<tr>\n\
<td colspan=\"6\" style=\"border-style: solid solid none solid; border-color: rgb(0, 0, 10) rgb(0, 0, 10) rgb(0, 0, 10); border-width: 1px 1px 1px 1pt; padding: 0in 0in 0in 0.08in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
BREAK\n\
</font></font>\n\
</td>\n\
</tr>\n\
</tbody>\n\
<tbody>\n\
<tr valign=\"top\">\n\
<td colspan=\"2\" valign=\"top\" height=\"600px\" style=\"border-style: solid none none solid; border-color: rgb(0, 0, 10) rgb(0, 0, 10) rgb(0, 0, 10); border-width: 1px 1px 1px 1px; padding: 0in 0in 0in 0.08in;\"></td>\n\
<td align=\"justify\" colspan=\"4\" style=\"border-style: solid solid none none; border-color: rgb(0, 0, 10) rgb(0, 0, 10) rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px 1px; padding: 0in 0.08in 0in 0in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
:msgtxt:\n\
</font></font>\n\
</td>\n\
</tr>\n\
</tbody>\n\
<tbody>\n\
<tr>\n\
<td colspan=\"6\" style=\"border-style: solid solid none solid; border-color: rgb(0, 0, 10) rgb(0, 0, 10) rgb(0, 0, 10); border-width: 1px 1px 1px 1px; padding: 0in 0in 0in 0.08in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
BREAK\n\
</font></font>\n\
</td>\n\
</tr>\n\
</tbody>\n\
<tbody>\n\
<tr>\n\
<td colspan=\"3\" style=\"border-style: solid solid solid solid; border-color: rgb(0, 0, 10) rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px 1px; padding: 0in 0.08in;\" bgcolor=\"#bfbfbf\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
MESSAGE RECEIVED\n\
</font></font>\n\
</td>\n\
<td colspan=\"3\" style=\"border-style: solid solid solid none; border-color: rgb(0, 0, 10) rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px 1px; padding: 0in 0in 0in 0.08in;\" bgcolor=\"#bfbfbf\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
MESSAGE SENT\n\
</font></font>\n\
</td>\n\
</tr>\n\
<tr>\n\
<td style=\"border-style: none none none solid; border-width: 1px 1px 1px 1px; padding: 0in 0in 0in 0.08in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
FROM:\n\
</font></font>\n\
</td>\n\
<td colspan=\"2\" style=\"border-style: none solid none none; border-color: rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px 1px; padding: 0in 0.08in 0in 0in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
:rcvd_fm:\n\
</font></font>\n\
</td>\n\
<td style=\"border-style: none none none none; border-width: 1px 1px 1px 1px; padding: 0in 0in 0in 0.08in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
TO:\n\
</font></font>\n\
</td>\n\
<td colspan=\"2\" style=\"border-style: none solid none none; border-color: rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px 1px; padding: 0in 0.08in 0in 0in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
:sent_to:\n\
</font></font>\n\
</td>\n\
</tr>\n\
<tr>\n\
<td style=\"border-style: none none none solid; border-width: 1px 1px 1px 1px; padding: 0in 0in 0in 0.08in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
DTG:\n\
</font></font>\n\
</td>\n\
<td colspan=\"2\" style=\"border-style: none solid none none; border-color: rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px 1px; padding: 0in 0.08in 0in 0in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
:rcvd_dtm:\n\
</font></font>\n\
</td>\n\
<td style=\"border-style: none none none none; border-width: 1px 1px 1px 1px; padding: 0in 0in 0in 0.08in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
DTG:\n\
</font></font>\n\
</td>\n\
<td colspan=\"2\" style=\"border-style: none solid none none; border-color: rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px 1px; padding: 0in 0.08in 0in 0in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
:sent_dtm:\n\
</font></font>\n\
</td>\n\
</tr>\n\
<tr>\n\
<td colspan=\"3\" style=\"border-style: none solid solid solid; border-color: rgb(0, 0, 10) rgb(0, 0, 10); border-width: 1px 1px 1px 1px; padding: 0in 0.08in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
RECEIVING OPERATOR INITIALS: :rcvop:\n\
</font></font>\n\
</td>\n\
<td colspan=\"3\" style=\"border-style: none solid solid none; border-color: rgb(0, 0, 10) rgb(0, 0, 10) -moz-use-text-color; border-width: 1px 1px 1px 1px; padding: 0in 0in 0in 0.08in;\">\n\
<font face=\"Arial, serif\"><font style=\"font-size: 11pt;\">\n\
SENDING OPERATOR INITIALS: :sendop:\n\
</font></font>\n\
</td>\n\
</tr>\n\
</tbody>\n\
</table>\n\
<table cellpadding=\"0\" cellspacing=\"0\" width=\"800\">\n\
<col width=\"450\"><col width=\"450\">\n\
<tbody>\n\
<tr>\n\
<font face=\"Arial, serif\">\n\
<td align=\"left\"><b>Flmsg RAFAC F126 FORM</b></td>\n\
</font>\n\
</tr>\n\
</tbody>\n\
</table>\n\
</body>\n\
</html>\n\
";

const char f126_txt_template[] =
"Flmsg RAFAC F126 FORM\n\n\
MSG NUMBER:  :msg nbr:\n\
PRECEDENCE:  :prec:\n\
DTG:         :dtm:\n\
FROM:        :from:\n\
TO:          :to:\n\
INFO:        :info:\n\
SUBJ:        :subj:\n\
\n\
GROUP COUNT: :grpcnt:\n\
\n\
BREAK\n\n\
:msgtxt:\n\n\
BREAK\n\n\
MESSAGE RECEIVED                        MESSAGE SENT\n\
FROM: :rcvd_fm:                         TO:   :sent_to:\n\
DTG:  :rcvd_dtm:                        DTG::sent_dtm:\n\
RECEIVING OPERATOR INITIALS: :rcvop:    SENDING OPERATOR INITIALS: :sendop:\n\
";

