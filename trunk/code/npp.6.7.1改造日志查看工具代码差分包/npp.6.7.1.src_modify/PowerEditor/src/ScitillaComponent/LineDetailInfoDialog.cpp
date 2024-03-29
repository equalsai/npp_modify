#include "precompiledHeaders.h"
#include "LineDetailInfoDialog.h"

BOOL CALLBACK CLineDetailInfoDialog::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_INITDIALOG:
		{
			goToCenter();
			return ::SendMessage((*_ppEditView)->getHSelf(), WM_COMMAND, IDD_LINE_DETAIL_INFO_DLG, 0);
		}
		case WM_COMMAND:
		{
			switch(wParam)
			{
				case IDCANCEL : // Close
					display(false);
					return TRUE;
				default:
					break;
			}
		}
			
		default:
		{
			if(wParam == 0)
			{

			}

			if(lParam == 0)
			{

			}
			break;
		}

	}


	return FALSE;
}

void CLineDetailInfoDialog::generateDisplayText(TCHAR *Dest, char *sour)
{
	WcharMbcsConvertor *wmc = WcharMbcsConvertor::getInstance();
	unsigned int cp = (*_ppEditView)->execute(SCI_GETCODEPAGE);
	const TCHAR * txtW = wmc->char2wchar(sour, cp);
	lstrcpy(Dest, txtW);
}

void CLineDetailInfoDialog::DisplayLineInfo(int lineLen)
{
	int tmpPos = 0;

	//RecordNo
	char tmpStr[36] = {0};
	memcpy(tmpStr, m_lineContent, 8);
	TCHAR wtmpStr[72] = {0};
	memset(wtmpStr, 0x00, 72);

	generateDisplayText(wtmpStr, tmpStr);
	::SetDlgItemText(_hSelf, IDC_EDIT_RECORD_NO, wtmpStr);
	tmpPos += 8;


	//LayerName
	memset(tmpStr, 0x00, 36);
	memcpy(tmpStr, m_lineContent + tmpPos, 12);
	memset(wtmpStr, 0x00, 72);

	generateDisplayText(wtmpStr, tmpStr);
	::SetDlgItemText(_hSelf, IDC_EDIT_LAYER_NAME, wtmpStr);
	tmpPos += 12;
	tmpPos += 2;

	//OutputTime
	memset(tmpStr, 0x00, 36);
	memcpy(tmpStr, m_lineContent + tmpPos, 24);
	memset(wtmpStr, 0x00, 72);

	generateDisplayText(wtmpStr, tmpStr);
	::SetDlgItemText(_hSelf, IDC_EDIT_OUTPUT_TIME, wtmpStr);
	tmpPos += 24;
	tmpPos += 2;

	//LogType
	memset(tmpStr, 0x00, 36);
	memcpy(tmpStr, m_lineContent + tmpPos, 8);
	memset(wtmpStr, 0x00, 72);

	generateDisplayText(wtmpStr, tmpStr);
	::SetDlgItemText(_hSelf, IDC_EDIT_LOG_TYPE, wtmpStr);
	tmpPos += 8;
	tmpPos += 2;

	//FileName
	memset(tmpStr, 0x00, 36);
	memcpy(tmpStr, m_lineContent + tmpPos, 20);
	memset(wtmpStr, 0x00, 72);

	generateDisplayText(wtmpStr, tmpStr);
	::SetDlgItemText(_hSelf, IDC_EDIT_FILE_NAME, wtmpStr);
	tmpPos += 20;
	tmpPos += 2;

	//LineNo
	memset(tmpStr, 0x00, 36);
	memcpy(tmpStr, m_lineContent + tmpPos, 8);
	memset(wtmpStr, 0x00, 72);

	generateDisplayText(wtmpStr, tmpStr);
	::SetDlgItemText(_hSelf, IDC_EDIT_LINE_NO, wtmpStr);
	tmpPos += 8;
	tmpPos += 2;

	//Function Name
	memset(tmpStr, 0x00, 36);
	memcpy(tmpStr, m_lineContent + tmpPos, 15);
	memset(wtmpStr, 0x00, 72);

	generateDisplayText(wtmpStr, tmpStr);
	::SetDlgItemText(_hSelf, IDC_EDIT_FUN_NAME, wtmpStr);
	tmpPos += 15;
	tmpPos += 2;

	//ThreadNo
	memset(tmpStr, 0x00, 36);
	memcpy(tmpStr, m_lineContent + tmpPos, 8);
	memset(wtmpStr, 0x00, 72);

	generateDisplayText(wtmpStr, tmpStr);
	::SetDlgItemText(_hSelf, IDC_EDIT_THREAD_NO, wtmpStr);
	tmpPos += 8;
	tmpPos += 2;

	//LogContent
	TCHAR *pwtmpContent = new TCHAR[(lineLen - tmpPos) * 3];
	if(pwtmpContent != NULL)
	{
		memset(pwtmpContent, 0x00, (lineLen - tmpPos) * 3);

		//0x0d 0x0a <- [CRLF]
		//0x0d      <- [CR]
		//0x0a      <- [LF]
		//transform
		std::string tmplineContent = (m_lineContent + tmpPos);

		char EndStr[] = {0x0D, 0x0A, 0x00};
		char EndStr2[] = {0x0D, 0x00};
		char EndStr3[] = {0x0A, 0x00};

		char repEndStr[] = "[CRLF]";
		char repEndStr2[] = "[CR]";
		char repEndStr3[] = "[LF]";
		
		int tmpSedPos = 0;
		while((tmpSedPos = tmplineContent.find(repEndStr, tmpSedPos)) > 0)
		{
			tmplineContent.erase(tmpSedPos, 6);
			tmplineContent.insert(tmpSedPos, EndStr);
		}

		tmpSedPos = 0;
		while((tmpSedPos = tmplineContent.find(repEndStr2, tmpSedPos)) > 0)
		{
			tmplineContent.erase(tmpSedPos, 4);
			tmplineContent.insert(tmpSedPos, EndStr2);
		}

		tmpSedPos = 0;
		while((tmpSedPos = tmplineContent.find(repEndStr3, tmpSedPos)) > 0)
		{
			tmplineContent.erase(tmpSedPos, 4);
			tmplineContent.insert(tmpSedPos, EndStr3);
		}

		generateDisplayText(pwtmpContent, (char *)tmplineContent.c_str());
		::SetDlgItemText(_hSelf, IDC_EDIT_LOG_CONTENT, pwtmpContent);

		delete []pwtmpContent;
	}
	else
	{

	}

	pwtmpContent = NULL;
}