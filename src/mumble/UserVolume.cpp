/* Copyright (C) 2015, Fredrik Nordin <freedick@github>

   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.
   - Neither the name of the Mumble Developers nor the names of its
     contributors may be used to endorse or promote products derived from this
     software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "mumble_pch.hpp"

#include "UserVolume.h"
#include "Global.h"
#include "ClientUser.h"
UserVolume::UserVolume(QWidget *p, QString title, unsigned int sessionId)
	: QDialog(p),
	m_clientSession(sessionId) {
	setupUi(this);
	ClientUser *user = ClientUser::get(sessionId);
	if(user) {
		qsUserVolume->setValue(round(log2(user->fLocalVolume)*6.0f));
	}
	setWindowTitle(title);
}

void UserVolume::on_qsUserVolume_valueChanged(int v) {
	QString text;
	text.sprintf("%+i",v);
	qlUserVolume->setText(tr("%1 dB").arg(text));
	ClientUser *user = ClientUser::get(m_clientSession);
	if(user) {
		user->fLocalVolume = pow(2.0f,v/6.0f);//Decibel formula +6db = *2
	}
}


bool UserVolume::eventFilter(QObject *obj, QEvent *evt) {
	return false;
}

