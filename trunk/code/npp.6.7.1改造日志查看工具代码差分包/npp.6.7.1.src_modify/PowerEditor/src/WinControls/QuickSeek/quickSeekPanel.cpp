#include "precompiledHeaders.h"
#include "quickSeekPanel.h"
#include "ScintillaEditView.h"
#include "localization.h"


#define QUICK_SEEK_CX_BITMAP         16
#define QUICK_SEEK_CY_BITMAP         16

#define QUICK_SEEK_INDEX_ROOT        0
#define QUICK_SEEK_INDEX_NODE        1
#define QUICK_SEEK_INDEX_LEAF        2


void CQuickSeekPanel::init(HINSTANCE hInst, HWND hPere, ScintillaEditView **ppEditView)
{
	DockingDlgInterface::init(hInst, hPere);
	_ppEditView = ppEditView;
}


void CQuickSeekPanel::reload(bool isConvertFile)
{
	//first: clean up
	_treeView.removeAllItems();

	const TCHAR *fn = ((*_ppEditView)->getCurrentBuffer())->getFileName();
	_treeView.addItem(fn, NULL, QUICK_SEEK_INDEX_ROOT, TEXT("-1"));

	if(isConvertFile != 1)
	{
		return;
	}

	//m_quickSeekMgr.init(_ppEditView);

	HTREEITEM itemParent = NULL;
	HTREEITEM itemParent2 = NULL;
	HTREEITEM itemParent3 = NULL;
	HTREEITEM itemParent4 = NULL;
	HTREEITEM itemParent5 = NULL;

	HTREEITEM root = _treeView.getRoot();

	TCHAR wtmpStr[72] = {0};
	generic_string tmpGeneStr;

	BufferID bufid = (*_ppEditView)->getCurrentBufferID();
	Buffer * buf = MainFileManager->getBufferByID(bufid);

	//层次名
	itemParent = _treeView.addItem(TEXT("层次名"), root, QUICK_SEEK_INDEX_NODE, TEXT("-1"));

	std::vector<string> *tmpVecLayerName = buf->getVecLayerName();
	for(unsigned int i = 0; i < tmpVecLayerName->size(); ++i)
	{
		memset(wtmpStr, 0x00, sizeof(wtmpStr));
		generateDisplayText(wtmpStr, (*tmpVecLayerName)[i].c_str());
		tmpGeneStr = wtmpStr;
		eraseSpace(tmpGeneStr);
		_treeView.addItem(tmpGeneStr.c_str(), itemParent, QUICK_SEEK_INDEX_LEAF, TEXT("LayerName"));
	}

	//日志类型
	itemParent2 = _treeView.addItem(TEXT("日志类型"), root, QUICK_SEEK_INDEX_NODE, TEXT("-1"));

	std::vector<string> *tmpVecLogType = buf->getVecLogType();
	for(unsigned int i = 0; i < tmpVecLogType->size(); ++i)
	{
		memset(wtmpStr, 0x00, sizeof(wtmpStr));
		generateDisplayText(wtmpStr, (*tmpVecLogType)[i].c_str());
		tmpGeneStr = wtmpStr;
		eraseSpace(tmpGeneStr);
		_treeView.addItem(tmpGeneStr.c_str(), itemParent2, QUICK_SEEK_INDEX_LEAF, TEXT("LogType"));
	}
	
	//文件名
	itemParent3 = _treeView.addItem(TEXT("文件名"), root, QUICK_SEEK_INDEX_NODE, TEXT("-1"));

	std::vector<string> *tmpVecFileName = buf->getVecFileName();
	for(unsigned int i = 0; i < tmpVecFileName->size(); ++i)
	{
		memset(wtmpStr, 0x00, sizeof(wtmpStr));
		generateDisplayText(wtmpStr, (*tmpVecFileName)[i].c_str());
		tmpGeneStr = wtmpStr;
		eraseSpace(tmpGeneStr);
		_treeView.addItem(tmpGeneStr.c_str(), itemParent3, QUICK_SEEK_INDEX_LEAF, TEXT("FileName"));
	}

	//函数名
	itemParent4 = _treeView.addItem(TEXT("函数名"), root, QUICK_SEEK_INDEX_NODE, TEXT("-1"));

	std::vector<string> *tmpVecFunName = buf->getVecFunName();
	for(unsigned int i = 0; i < tmpVecFunName->size(); ++i)
	{
		memset(wtmpStr, 0x00, sizeof(wtmpStr));
		generateDisplayText(wtmpStr, (*tmpVecFunName)[i].c_str());
		tmpGeneStr = wtmpStr;
		eraseSpace(tmpGeneStr);
		_treeView.addItem(tmpGeneStr.c_str(), itemParent4, QUICK_SEEK_INDEX_LEAF, TEXT("FunName"));
	}

	//线程号
	itemParent5 = _treeView.addItem(TEXT("线程号"), root, QUICK_SEEK_INDEX_NODE, TEXT("-1"));

	std::vector<string> *tmpVecThreadNo = buf->getVecThreadNo();
	for(unsigned int i = 0; i < tmpVecThreadNo->size(); ++i)
	{
		memset(wtmpStr, 0x00, sizeof(wtmpStr));
		generateDisplayText(wtmpStr, (*tmpVecThreadNo)[i].c_str());
		tmpGeneStr = wtmpStr;
		eraseSpace(tmpGeneStr);
		_treeView.addItem(tmpGeneStr.c_str(), itemParent5, QUICK_SEEK_INDEX_LEAF, TEXT("ThreadNo"));
	}


}


// static WNDPROC oldFunclstToolbarProc = NULL;
// static BOOL CALLBACK funclstToolbarProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
// {
// 	switch (message)
// 	{
// 	case WM_CTLCOLOREDIT :
// 		{
// 			return ::SendMessage(::GetParent(hwnd), WM_CTLCOLOREDIT, wParam, lParam);
// 		}
// 	}
// 	return oldFunclstToolbarProc(hwnd, message, wParam, lParam);
// }



BOOL CALLBACK CQuickSeekPanel::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		// Make edit field red if not found
// 	case WM_CTLCOLOREDIT :
// 		{
// 			// if the text not found modify the background color of the editor
// 			static HBRUSH hBrushBackground = CreateSolidBrush(BCKGRD_COLOR);
// 			TCHAR text2search[MAX_PATH] ;
// 			::SendMessage(_hSearchEdit, WM_GETTEXT, MAX_PATH, (LPARAM)text2search);
// 			if (text2search[0] == '\0')
// 			{
// 				return FALSE; // no text, use the default color
// 			}
// 
// 			HTREEITEM searchViewRoot = _treeViewSearchResult.getRoot();
// 			if (searchViewRoot)
// 			{
// 				if (_treeViewSearchResult.getChildFrom(searchViewRoot))
// 					return FALSE; // children on root found, use the default color
// 			}
// 			else
// 				return FALSE; // no root (no parser), use the default color
// 			// text not found
// 			SetTextColor((HDC)wParam, TXT_COLOR);
// 			SetBkColor((HDC)wParam, BCKGRD_COLOR);
// 			return (LRESULT)hBrushBackground;
// 		}
		case WM_COMMAND:
		{
			switch (wParam)
			{
				case NPPM_INTERNAL_MAKERLINE:
				{
					int styleID;
					if(!m_QSFindStr.compare(TEXT("WARNING")))
					{
						styleID = SCE_UNIVERSAL_FOUND_STYLE_EXT3;
					}
					else if(!m_QSFindStr.compare(TEXT("ERROR")))
					{
						styleID = SCE_UNIVERSAL_FOUND_STYLE_EXT2;
					}
					else
					{
						styleID = SCE_UNIVERSAL_FOUND_STYLE_EXT4;
					}

					ProcessMark((TCHAR *)m_QSFindStr.c_str(), styleID);
					break;
				}

				case NPPM_INTERNAL_CLEARMAKERLINE:
				{
					int styleID;
					if(!m_QSFindStr.compare(TEXT("WARNING")))
					{
						styleID = SCE_UNIVERSAL_FOUND_STYLE_EXT3;
					}
					else if(!m_QSFindStr.compare(TEXT("ERROR")))
					{
						styleID = SCE_UNIVERSAL_FOUND_STYLE_EXT2;
					}
					else
					{
						styleID = SCE_UNIVERSAL_FOUND_STYLE_EXT4;
					}

					(*_ppEditView)->clearIndicator(styleID);
					//(*_ppEditView)->execute(SCI_MARKERDELETEALL, MARK_BOOKMARK);

					break;
				}

				default:
				{
					return FALSE;
				}
			}

			break;
		}

		case WM_INITDIALOG:
		{

			//_treeViewSearchResult.init(_hInst, _hSelf, IDC_QUICK_SEEK_LIST_AUX);
			_treeView.init(_hInst, _hSelf, IDC_QUICK_SEEK_LIST);
			setTreeViewImageList(IDI_FUNCLIST_ROOT, IDI_FUNCLIST_NODE, IDI_FUNCLIST_LEAF);
			
			_treeView.display();
			return TRUE;
		}
		case WM_DESTROY:
		{
			_treeView.destroy();
			//_treeViewSearchResult.destroy();
			break;
		}

		case WM_NOTIFY:
		{
			notified((LPNMHDR)lParam);
		}
		return TRUE;

		case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			HWND hwnd = _treeView.getHSelf();
			if (hwnd)
				::MoveWindow(hwnd, 0, 2, width, height - 2, TRUE);

			//HWND hwnd_aux = _treeViewSearchResult.getHSelf();
			//if (hwnd_aux)
			//	::MoveWindow(hwnd_aux, 0, 2, width, height - 2, TRUE);

			break;
		}

		case WM_CONTEXTMENU:
		{
			TVITEM tvItem;
			tvItem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_PARAM;
			tvItem.hItem = _treeView.getSelection();
			TCHAR tmpTextName[108] = {0};
			tvItem.pszText = tmpTextName;
			tvItem.cchTextMax = 108;
			::SendMessage(_treeView.getHSelf(), TVM_GETITEM, 0,(LPARAM)&tvItem);

			m_QSFindStr = tmpTextName;

			if(!(tvItem.iImage == QUICK_SEEK_INDEX_ROOT || tvItem.iImage == QUICK_SEEK_INDEX_NODE))
			//if((HWND)wParam == _scintView.getHSelf())
			{
				POINT p;
				::GetCursorPos(&p);
				ContextMenu scintillaContextmenu;
				vector<MenuItemUnit> tmp;
				tmp.push_back(MenuItemUnit(NPPM_INTERNAL_MAKERLINE, TEXT("Maker")));
				tmp.push_back(MenuItemUnit(NPPM_INTERNAL_CLEARMAKERLINE, TEXT("Clear Maker")));

				scintillaContextmenu.create(_hSelf, tmp);

				scintillaContextmenu.display(p);
				return TRUE;
			}
			return ::DefWindowProc(_hSelf, message, wParam, lParam);
			//break;
		}

		default:
		{
			if(wParam == 0)
			{

			}

			if(lParam == 0)
			{

			}

			return DockingDlgInterface::run_dlgProc(message, wParam, lParam);
		}
	}

	return DockingDlgInterface::run_dlgProc(message, wParam, lParam);
}


void CQuickSeekPanel::notified(LPNMHDR notification)
{
	if(notification->hwndFrom == _treeView.getHSelf())
	{
		switch(notification->code)
		{
			case NM_DBLCLK:
			{
				bool isOk = openSelectionDlg(_treeView);

				if(isOk)
				{
					findAllIn(CURRENT_DOC);
				}
			}
			break;
		}
	}
	else if (notification->code == DMN_SWITCHIN)
	{
		BufferID bufid = (*_ppEditView)->getCurrentBufferID();
		Buffer * buf = MainFileManager->getBufferByID(bufid);

		bool isConvert = buf->isConvertFile();

		reload(isConvert);
	}
	else if (notification->code == DMN_CLOSE)
	{
		::SendMessage(_hParent, WM_COMMAND, IDM_VIEW_QUICK_SEEK, 0);
	}
}


bool CQuickSeekPanel::openSelectionDlg(const TreeView &treeView)
{
	TVITEM tvItem;
	tvItem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_PARAM;
	tvItem.hItem = treeView.getSelection();
	TCHAR tmpTextName[108] = {0};
	tvItem.pszText = tmpTextName;
	tvItem.cchTextMax = 108;
	::SendMessage(treeView.getHSelf(), TVM_GETITEM, 0,(LPARAM)&tvItem);

	if (tvItem.iImage == QUICK_SEEK_INDEX_ROOT || tvItem.iImage == QUICK_SEEK_INDEX_NODE)
	{
		return false;
	}

	generic_string *posStr = (generic_string *)tvItem.lParam;
	if (!posStr)
	{
		return false;
	}

	m_QSFindStr = tmpTextName;
	//eraseSpace(m_QSFindStr);

	WcharMbcsConvertor *wmc = WcharMbcsConvertor::getInstance();
	unsigned int cp = (*_ppEditView)->execute(SCI_GETCODEPAGE);
	const char *tmpFindStr = wmc->wchar2char(m_QSFindStr.c_str(), cp);

	m_QSCHFindStr = tmpFindStr;
	m_QSCHFindStr = m_QSCHFindStr.insert(m_QSCHFindStr.length(), 1, ' ');
	//According to the Node, make sure the copy begin position
	if(posStr->compare(TEXT("LayerName")) == 0)
	{
		m_seekStartPos = 8;
		//m_seekLen = 12;
		m_seekLen = m_QSCHFindStr.length();
	}
	else if(posStr->compare(TEXT("LogType")) == 0)
	{
		m_seekStartPos = 8 + 12 + 2 + 24 + 2;// 58;
		//m_seekLen = 12;
		m_seekLen = m_QSCHFindStr.length();
	}
	else if(posStr->compare(TEXT("FileName")) == 0)
	{
		m_seekStartPos = 8 + 12 + 2 + 24 + 2 + 8 + 2;//73;
		//m_seekLen = 20;
		m_seekLen = m_QSCHFindStr.length();
	}
	else if(posStr->compare(TEXT("FunName")) == 0)
	{
		m_seekStartPos = 8 + 12 + 2 + 24 + 2 + 8 + 2 + 20 + 2 + 8 + 2;//107;
		//m_seekLen = 15;
		m_seekLen = m_QSCHFindStr.length();
	}
	else if(posStr->compare(TEXT("ThreadNo")) == 0)
	{
		m_seekStartPos = 8 + 12 + 2 + 24 + 2 + 8 + 2 + 20 + 2 + 8 + 2 + 15 + 2;//125;
		//m_seekLen = 8;
		m_seekLen = m_QSCHFindStr.length();
	}
	else
	{
		m_seekStartPos = 0;
		m_seekLen = 0;
	}

	return true;
}

void CQuickSeekPanel::findAllIn(InWhat op)
{
	bool doSetMarkingStruct = false;
	if (!_pFinder->getInstance()->getIsInit())
	{
		//_pFinder = new Finder();
		_pFinder->getInstance()->init(_hInst, _hSelf, _ppEditView);

		tTbData	data = {0};
		_pFinder->getInstance()->create(&data, false);
		::SendMessage(_hParent, NPPM_MODELESSDIALOG, MODELESSDIALOGREMOVE, (WPARAM)_pFinder->getInstance()->getHSelf());
		// define the default docking behaviour
		data.uMask = DWS_DF_CONT_BOTTOM | DWS_ICONTAB | DWS_ADDINFO;
		data.hIconTab = (HICON)::LoadImage(_hInst, MAKEINTRESOURCE(IDI_FIND_RESULT_ICON), IMAGE_ICON, 0, 0, LR_LOADMAP3DCOLORS | LR_LOADTRANSPARENT);
		data.pszAddInfo = _findAllResultStr;

		data.pszModuleName = TEXT("dummy");

		// the dlgDlg should be the index of funcItem where the current function pointer is
		// in this case is DOCKABLE_DEMO_INDEX
		data.dlgID = 0;
		::SendMessage(_hParent, NPPM_DMMREGASDCKDLG, 0, (LPARAM)&data);

		_pFinder->getInstance()->_scintView.init(_hInst, _pFinder->getInstance()->getHSelf());

		// Subclass the ScintillaEditView for the Finder (Scintilla doesn't notify all key presses)
		//originalFinderProc = SetWindowLongPtr(_pFinder->getInstance()->_scintView.getHSelf(), GWLP_WNDPROC, (LONG_PTR)finderProc);

		_pFinder->getInstance()->setFinderReadOnly(true);
		_pFinder->getInstance()->_scintView.execute(SCI_SETCODEPAGE, SC_CP_UTF8);
		_pFinder->getInstance()->_scintView.execute(SCI_USEPOPUP, FALSE);
		_pFinder->getInstance()->_scintView.execute(SCI_SETUNDOCOLLECTION, false);	//dont store any undo information
		_pFinder->getInstance()->_scintView.execute(SCI_SETCARETLINEVISIBLE, 1);
		_pFinder->getInstance()->_scintView.execute(SCI_SETCARETWIDTH, 0);
		_pFinder->getInstance()->_scintView.showMargin(ScintillaEditView::_SC_MARGE_FOLDER, true);

		// get the width of FindDlg
		RECT findRect;
		::GetWindowRect(_pFinder->getInstance()->getHSelf(), &findRect);

		// overwrite some default settings
		_pFinder->getInstance()->_scintView.showMargin(ScintillaEditView::_SC_MARGE_SYBOLE, false);
		_pFinder->getInstance()->_scintView.setMakerStyle(FOLDER_STYLE_SIMPLE);

		_pFinder->getInstance()->_scintView.display();
		_pFinder->getInstance()->display();
		doSetMarkingStruct = true;
	}
	_pFinder->getInstance()->setFinderStyle();

	if (doSetMarkingStruct)
	{
		// Send the address of _MarkingsStruct to the lexer
		char ptrword[sizeof(void*)*2+1];
		sprintf(ptrword, "%p", &_pFinder->getInstance()->_MarkingsStruct);
		_pFinder->getInstance()->_scintView.execute(SCI_SETPROPERTY, (WPARAM)"@MarkingsStruct", (LPARAM)ptrword);
	}

	::SendMessage(_pFinder->getInstance()->getHSelf(), WM_SIZE, 0, 0);

	int cmdid = 0;
	if (op == ALL_OPEN_DOCS)
	{
		cmdid = WM_FINDALL_INOPENEDDOC;
	}
	else if (op == FILES_IN_DIR)
	{
		cmdid = WM_FINDINFILES;
	}
	else if (op == CURRENT_DOC)
	{
		cmdid = WM_QS_FINDALL_INCURRENTDOC;
	}

	if (!cmdid) return;

	if (::SendMessage(_hParent, cmdid, 0, 0))
	{
		if(_findAllResult == 1)
			wsprintf(_findAllResultStr, TEXT("1 hit"));
		else
			wsprintf(_findAllResultStr, TEXT("%d hits"), _findAllResult);
		if (_findAllResult) 
		{
			focusOnFinder();
		}
		else
		{
			// Show finder
			::SendMessage(_hParent, NPPM_DMMSHOW, 0, (LPARAM)_pFinder->getInstance()->getHSelf());
			getFocus(); // no hits
		}
	}
	//else // error - search folder doesn't exist
	//	::SendMessage(_hSelf, WM_NEXTDLGCTL, (WPARAM)::GetDlgItem(_hSelf, IDD_FINDINFILES_DIR_COMBO), TRUE);
}

int CQuickSeekPanel::findInCurFile(const TCHAR *fileName)
{
	int tmpLineCount = (*_ppEditView)->execute(SCI_GETLINECOUNT);

	int tmpLineNo = 0;
	int tmpLineLen = 0;
	char tmpLineInfo[1024 * 8] = {0};
	char *ptmpLineInfo = tmpLineInfo;

	int lineStartPos = 0;
	int targetStart = 0;
	int targetEnd = 0;

	SearchResultMarking srm;

	bool findAllFileNameAdded = false;
	_findAllResult = 0;

	WcharMbcsConvertor *wmc = WcharMbcsConvertor::getInstance();
	unsigned int cp = (*_ppEditView)->execute(SCI_GETCODEPAGE);

	while(tmpLineNo < tmpLineCount)
	{
		if(!findAllFileNameAdded)
		{
			_pFinder->getInstance()->addFileNameTitle(fileName);
			findAllFileNameAdded = true;
		}

		tmpLineLen = (*_ppEditView)->execute(SCI_LINELENGTH, tmpLineNo);

		memset(tmpLineInfo, 0x00, sizeof(tmpLineInfo));
		(*_ppEditView)->execute(SCI_GETLINE, (LPARAM)tmpLineNo, (WPARAM)tmpLineInfo);



		targetStart = lineStartPos;
		targetEnd = lineStartPos;

		if(!strncmp(ptmpLineInfo + m_seekStartPos, m_QSCHFindStr.c_str(), m_seekLen))
		{
			targetStart += m_seekStartPos;
			targetEnd += (m_seekStartPos + m_seekLen);

			srm._start = m_seekStartPos;
			srm._end = (m_seekStartPos + m_seekLen);

			const TCHAR *tmpWLineInfo = wmc->char2wchar(tmpLineInfo, cp);
			generic_string line = tmpWLineInfo;
			//line += TEXT("\r\n");

			_pFinder->getInstance()->add(FoundInfo(targetStart, targetEnd, fileName), srm, line.c_str(), tmpLineNo + 1);

			_findAllResult++;
		}

		lineStartPos += tmpLineLen;

		tmpLineNo++;
	}

	return _findAllResult;
}


// void CQuickSeekPanel::generateFirstNode()
// {
// //	const TCHAR *fn = ((*_ppEditView)->getCurrentBuffer())->getFileName();
// }


BOOL CQuickSeekPanel::setTreeViewImageList(int root_id, int node_id, int leaf_id)
{
	HBITMAP hbmp;
	COLORREF maskColour = RGB(192, 192, 192);
	const int nbBitmaps = 3;

	// Creation of image list
	if ((_hTreeViewImaLst = ImageList_Create(QUICK_SEEK_CX_BITMAP, QUICK_SEEK_CY_BITMAP, ILC_COLOR32 | ILC_MASK, nbBitmaps, 0)) == NULL) 
		return FALSE;

	// Add the bmp in the list
	hbmp = LoadBitmap(_hInst, MAKEINTRESOURCE(root_id));
	if (hbmp == NULL)
		return FALSE;
	ImageList_AddMasked(_hTreeViewImaLst, hbmp, maskColour);
	DeleteObject(hbmp);

	hbmp = LoadBitmap(_hInst, MAKEINTRESOURCE(node_id));
	if (hbmp == NULL)
		return FALSE;
	ImageList_AddMasked(_hTreeViewImaLst, hbmp, maskColour);
	DeleteObject(hbmp);

	hbmp = LoadBitmap(_hInst, MAKEINTRESOURCE(leaf_id));
	if (hbmp == NULL)
		return FALSE;
	ImageList_AddMasked(_hTreeViewImaLst, hbmp, maskColour);
	DeleteObject(hbmp);

	if (ImageList_GetImageCount(_hTreeViewImaLst) < nbBitmaps)
		return FALSE;

	// Set image list to the tree view
	TreeView_SetImageList(_treeView.getHSelf(), _hTreeViewImaLst, TVSIL_NORMAL);
	//TreeView_SetImageList(_treeViewSearchResult.getHSelf(), _hTreeViewImaLst, TVSIL_NORMAL);

	return TRUE;
}


void CQuickSeekPanel::eraseSpace(generic_string &str)
{
	TCHAR ch = ' ';
	unsigned int pos = 0;
	for(;;)
	{
		if(pos >= str.length())
		{
			break;
		}

		if(str[pos] == ch)
		{
			str.erase(pos, 1);
		}
		else
		{
			pos++;
		}
	}
}

void CQuickSeekPanel::generateDisplayText(TCHAR *Dest, const char *sour)
{
	WcharMbcsConvertor *wmc = WcharMbcsConvertor::getInstance();
	unsigned int cp = (*_ppEditView)->execute(SCI_GETCODEPAGE);
	const TCHAR * txtW = wmc->char2wchar(sour, cp);
	lstrcpy(Dest, txtW);
}


void CQuickSeekPanel::ProcessMark(TCHAR *txt2find, int colourStyleID)
{
	if(txt2find == NULL)
	{
		return;
	}

	int docLength = int((*_ppEditView)->execute(SCI_GETLENGTH));

	// Default : 
	//        direction : down
	//        begin at : 0
	//        end at : end of doc
	int startPosition = 0;
	int endPosition = docLength;

	int targetStart = 0;
	int targetEnd = 0;

	FindOption tmpOption;

	tmpOption._str2Search = txt2find;
	tmpOption._isInSelection = false;
	tmpOption._str4Replace = TEXT("");
	tmpOption._filters = TEXT("");
	tmpOption._directory = (*_ppEditView)->getCurrentBuffer()->getFullPathName();
	tmpOption._dotMatchesNewline = false;
	tmpOption._isWholeWord = false;
	tmpOption._isMatchCase = false;
	tmpOption._whichDirection = true;
	tmpOption._isWrapAround = true;
	tmpOption._doPurge = false;
	tmpOption._doMarkLine = true;
	tmpOption._isRecursive = false;
	tmpOption._isInHiddenDir = false;

	tmpOption._searchType = FindRegex;
	int flags = Searching::buildSearchFlags(&tmpOption) | SCFIND_REGEXP_SKIPCRLFASONE; 

	//Initial range for searching
	(*_ppEditView)->execute(SCI_SETSEARCHFLAGS, flags);

	TCHAR *pTextFind = NULL;
	int stringSizeFind = 0;

	stringSizeFind = lstrlen(txt2find);
	pTextFind = new TCHAR[stringSizeFind + sizeof(TCHAR) + 1];
	//memset(pTextFind, 0x00, stringSizeFind + 1);
	lstrcpy(pTextFind, txt2find);

	generic_string strTextFind = pTextFind;
	strTextFind.push_back(TCHAR(0x20));
	lstrcpy(pTextFind, strTextFind.c_str());
	stringSizeFind = strTextFind.length();

// 	TCHAR tmpCh = 0x20;
// 	pTextFind[stringSizeFind] = tmpCh;
// 	stringSizeFind += sizeof(TCHAR);

	while (targetStart != -1 && targetStart != -2)
	{
		targetStart = (*_ppEditView)->searchInTarget(pTextFind, stringSizeFind, startPosition, endPosition);

		// If we've not found anything, just break out of the loop
		if (targetStart == -1 || targetStart == -2)
			break;

		targetEnd = int((*_ppEditView)->execute(SCI_GETTARGETEND));

		if (targetEnd > endPosition) {	//we found a result but outside our range, therefore do not process it
			break;
		}

		int foundTextLen = targetEnd - targetStart;
		int replaceDelta = 0;




		if (foundTextLen > 0)
		{
			(*_ppEditView)->execute(SCI_SETINDICATORCURRENT,  colourStyleID);
			(*_ppEditView)->execute(SCI_INDICATORFILLRANGE,  targetStart, foundTextLen);
		}

// 		if (tmpOption._doMarkLine)
// 		{
// 			int lineNumber = (*_ppEditView)->execute(SCI_LINEFROMPOSITION, targetStart);
// 			int state = (*_ppEditView)->execute(SCI_MARKERGET, lineNumber);
// 
//  			if (!(state & (1 << MARK_BOOKMARK)))
//  				(*_ppEditView)->execute(SCI_MARKERADD, lineNumber, MARK_BOOKMARK);
// 		}



		//++nbProcessed;

		// After the processing of the last string occurence the search loop should be stopped
		// This helps to avoid the endless replacement during the EOL ("$") searching
		if( targetStart + foundTextLen == endPosition )
			break;

		startPosition = targetStart + foundTextLen + replaceDelta;		//search from result onwards
		endPosition += replaceDelta;	

	}

	delete []pTextFind;
}


void CQuickSeekPanel::ProcessClearMark()
{

}


void CQuickSeekMgr::generateLogInfo()
{
	int tmpLineCount = (*_ppEditView)->execute(SCI_GETLINECOUNT);

	int tmpLineNo = 0;

	char tmpLineInfo[1024 * 8] = {0};
	char *ptmpLineInfo = tmpLineInfo;
	char tmpStr[36] = {0};
	TCHAR wtmpStr[72] = {0};

	int tmpLineLen = 0;
	int tmpPos = 0;
	std::vector<generic_string>::iterator iter;

	while(tmpLineNo < tmpLineCount)
	{
		//Get a line info
		tmpPos = 0;

		tmpLineLen = (*_ppEditView)->execute(SCI_LINELENGTH, tmpLineNo);

		memset(tmpLineInfo, 0x00, 1024 * 8);
		(*_ppEditView)->execute(SCI_GETLINE, (LPARAM)tmpLineNo, (WPARAM)tmpLineInfo);
		
		//LayerName
		memset(tmpStr, 0x00, sizeof(tmpStr));
		memset(wtmpStr, 0x00, sizeof(wtmpStr));
		memcpy(tmpStr, ptmpLineInfo + 16, 12);
		generateDisplayText(wtmpStr, tmpStr);

		iter = find(m_vecLayerName.begin(), m_vecLayerName.end(), generic_string(wtmpStr));
		if((iter == m_vecLayerName.end()) && (wtmpStr[0] != 0x00))
		{
			m_vecLayerName.push_back(wtmpStr);
		}
		

		//LogType
		memset(tmpStr, 0x00, sizeof(tmpStr));
		memset(wtmpStr, 0x00, sizeof(wtmpStr));
		tmpPos += 16;
		tmpPos += 15;
		tmpPos += 27;
		memcpy(tmpStr, ptmpLineInfo + tmpPos, 12);
		generateDisplayText(wtmpStr, tmpStr);

		iter = find(m_vecLogType.begin(), m_vecLogType.end(), generic_string(wtmpStr));
		if((iter == m_vecLogType.end()) && (wtmpStr[0] != 0x00))
		{
			m_vecLogType.push_back(wtmpStr);
		}
		

		//FileName
		memset(tmpStr, 0x00, sizeof(tmpStr));
		memset(wtmpStr, 0x00, sizeof(wtmpStr));
		tmpPos += 15;
		memcpy(tmpStr, ptmpLineInfo + tmpPos, 20);
		generateDisplayText(wtmpStr, tmpStr);

		iter = find(m_vecFileName.begin(), m_vecFileName.end(), generic_string(wtmpStr));
		if((iter == m_vecFileName.end()) && (wtmpStr[0] != 0x00))
		{
			m_vecFileName.push_back(wtmpStr);
		}
		

		//Function Name
		memset(tmpStr, 0x00, sizeof(tmpStr));
		memset(wtmpStr, 0x00, sizeof(wtmpStr));
		tmpPos += 23;
		tmpPos += 11;
		memcpy(tmpStr, ptmpLineInfo + tmpPos, 15);
		generateDisplayText(wtmpStr, tmpStr);

		iter = find(m_vecFunName.begin(), m_vecFunName.end(), generic_string(wtmpStr));
		if((iter == m_vecFunName.end()) && (wtmpStr[0] != 0x00))
		{
			m_vecFunName.push_back(wtmpStr);
		}
		

		//ThreadNo
		memset(tmpStr, 0x00, sizeof(tmpStr));
		memset(wtmpStr, 0x00, sizeof(wtmpStr));
		tmpPos += 18;
		memcpy(tmpStr, ptmpLineInfo + tmpPos, 8);
		generateDisplayText(wtmpStr, tmpStr);

		iter = find(m_vecThreadNo.begin(), m_vecThreadNo.end(), generic_string(wtmpStr));
		if((iter == m_vecThreadNo.end()) && (wtmpStr[0] != 0x00))
		{
			m_vecThreadNo.push_back(wtmpStr);
		}
		

		tmpLineNo++;
	}

}


void CQuickSeekMgr::generateLogInfo2()
{
	//get text length
// 	UINT textLen = (*_ppEditView)->execute(SCI_GETTEXTLENGTH, 0, 0) + 1;
// 
// 	UINT tmpBufLen = 1 * 1024 * 1024;
// 	char *tmpBuf = new char[tmpBufLen];
// 	if(tmpBuf == NULL)
// 	{
// 		return;
// 	}
// 
// 	memset(tmpBuf, 0x00, tmpBufLen);
// 	(*_ppEditView)->execute(SCI_GETTEXT, tmpBufLen, (LPARAM)tmpBuf);
// 
// 	string tmpstr = tmpBuf;
// 	int tmpPos = tmpstr.rfind('\n');
// 	memset(tmpBuf + tmpPos + 1, 0x00, (tmpBufLen - tmpPos));
	
}


void CQuickSeekMgr::init(ScintillaEditView **ppEditView)
{
	_ppEditView = ppEditView;

	//清除以前的内容
	m_vecLayerName.erase(m_vecLayerName.begin(), m_vecLayerName.end());
	m_vecFileName.erase(m_vecFileName.begin(), m_vecFileName.end());
	m_vecFunName.erase(m_vecFunName.begin(), m_vecFunName.end());
	m_vecLogType.erase(m_vecLogType.begin(), m_vecLogType.end());
	m_vecThreadNo.erase(m_vecThreadNo.begin(), m_vecThreadNo.end());


	generateLogInfo();
}


void CQuickSeekMgr::generateDisplayText(TCHAR *Dest, char *sour)
{
	WcharMbcsConvertor *wmc = WcharMbcsConvertor::getInstance();
	unsigned int cp = (*_ppEditView)->execute(SCI_GETCODEPAGE);
	const TCHAR * txtW = wmc->char2wchar(sour, cp);
	lstrcpy(Dest, txtW);
}
