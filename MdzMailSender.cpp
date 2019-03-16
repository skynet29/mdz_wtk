// MdzMailSender.cpp: implementation of the MdzMailSender class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzMailSender.h"
#include "MdzWindow.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
enum
{
    MAIL_CONNECT,
    MAIL_HELO,
    MAIL_FROM,
    MAIL_RCPTTO,
    MAIL_DATA,
    MAIL_DOT,
    MAIL_QUIT
};

MdzMailSender::MdzMailSender()
{
	sock.SetOnDataReceived(MDZ_CBK1(MdzMailSender, OnDataReceived));
	timer.SetDelay(1000); // 1 sec
	timer.SetOnTimeout(MDZ_CBK1(MdzMailSender, OnTimeout));
}

MdzMailSender::~MdzMailSender()
{

}

void MdzMailSender::SetSmtpServer(LPSTR strHost)
{
	MEMBER_SET(strHost);
}

void MdzMailSender::SetTo(LPSTR strTo)
{
	MEMBER_SET(strTo);

}

void MdzMailSender::SetFrom(LPSTR strFrom)
{
	MEMBER_SET(strFrom);

}

void MdzMailSender::SetSubject(LPSTR strSubject)
{
	MEMBER_SET(strSubject);

}

void MdzMailSender::SetBody(LPSTR strBody)
{
	MEMBER_SET(strBody);

}

MdzString MdzMailSender::Send()
{
	iState = MAIL_CONNECT;
		
	if (! sock.Connect(strHost, 25))
		return MdzString("Unable to connect to SMTP server");

	timer.Start();

	bError = "";

	MdzWindow::MessageLoop();	
	return bError;
}

void MdzMailSender::OnDataReceived()
{
	MdzString strData = sock.GetData();

	if (strData.GetLength() == 0)
	{
		bError = "Bad data length";
		PostQuitMessage(0);
	}

	int iRet = strData.GetSubString(0, 3).ToInt();

	timer.Stop();

	switch (iRet)
	{
	case 220:
	case 221:
	case 250:
	case 354:
		break;
	default:
		bError = strData;
		PostQuitMessage(0);
		return;
	}

	switch (iState)
	{
	case MAIL_CONNECT:
		{
			sock.SendData(MdzString::Format("HELO %s\r\n", strHost));
				//(LPSTR) strFrom.GetSubString(0, strFrom.GetIndexOf("@"))));
			iState = MAIL_HELO;
			timer.Start();
		}
		break;

	case MAIL_HELO:
		{

			//sock.SendData(MdzString::Format("MAIL FROM:<%s>\n", (LPSTR) strFrom));
			sock.SendData(MdzString::Format("MAIL FROM: <%s>\r\n", (LPSTR) strFrom));
			iState = MAIL_FROM;
			timer.Start();
		}
		break;

	case MAIL_FROM:
		{
			//sock.SendData(MdzString::Format("RCPT TO:<%s>\n", (LPSTR) strTo));
			sock.SendData(MdzString::Format("RCPT TO: <%s>\r\n", (LPSTR) strTo));
			iState = MAIL_RCPTTO;
			timer.Start();
		}
		break;

	case MAIL_RCPTTO:
		{
			sock.SendData("DATA\r\n");
			iState = MAIL_DATA;
			timer.Start();
		}
		break;

	case MAIL_DATA:
		{			
			/*
			sock.SendData(MdzString::Format("From: %s <%s>\n", (LPSTR) strFrom, (LPSTR) strFrom));
			sock.SendData(MdzString::Format("Subject:%s\n\n", (LPSTR) strSubject));
			sock.SendData(MdzString::Format("%s\n", (LPSTR) strBody));
			*/
			sock.SendData(MdzString::Format("From: %s\r\n", (LPSTR) strFrom));
			sock.SendData(MdzString::Format("To: %s\r\n", (LPSTR) strTo));
			sock.SendData(MdzString::Format("Subject: %s\r\n\r\n", (LPSTR) strSubject));
			sock.SendData(MdzString::Format("%s", (LPSTR) strBody));
			sock.SendData("\r\n.\r\n");
			iState = MAIL_DOT;
			timer.Start();
		}
		break;

	case MAIL_DOT:
		{
			sock.SendData("QUIT\r\n");
			iState = MAIL_QUIT;
			timer.Start();
		}
		break;

	case MAIL_QUIT:
		{
			sock.Close();
			PostQuitMessage(0);
		}
		break;

	}
}

void MdzMailSender::OnTimeout()
{
	bError = "Timeout";
	PostQuitMessage(0);
}



void MdzMailSender::SetTimeout(UINT iTimeout)
{
	timer.SetDelay(iTimeout * 1000);
}
