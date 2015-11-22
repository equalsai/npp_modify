#ifndef QUICK_SEEK_PANEL_H
#define QUICK_SEEK_PANEL_H

//#include <windows.h>
#ifndef DOCKINGDLGINTERFACE_H
#include "DockingDlgInterface.h"
#endif //DOCKINGDLGINTERFACE_H

#include "quickSeekPanel_rc.h"
#include "TreeView.h"

#include "FindReplaceDlg.h"

#define QS_PANELTITLE     TEXT("Quick Seek")

#define QS_FUCTIONLISTROOTNODE "LogInfoList"
#define QS_SORTLOCALNODENAME   "SortTip"
#define QS_RELOADLOCALNODENAME "ReloadTip"

class ScintillaEditView;
//class Finder;

class CQuickSeekMgr
{
public:
	CQuickSeekMgr() {};

	~CQuickSeekMgr() {};

	void init(ScintillaEditView **ppEditView);

	std::vector<generic_string>* getVecLayerName()
	{
		return &m_vecLayerName;
		//(*_ppEditView)->
	}

	std::vector<generic_string>* getVecLogType()
	{
		return &m_vecLogType;
	}

	std::vector<generic_string>* getVecFileName()
	{
		return &m_vecFileName;
	}

	std::vector<generic_string>* getVecFunName()
	{
		return &m_vecFunName;
	}

	std::vector<generic_string>* getVecThreadNo()
	{
		return &m_vecThreadNo;
	}


private:

	void generateLogInfo();

	void generateLogInfo2();

	void generateDisplayText(TCHAR *Dest, char *sour);

private:

	std::vector<generic_string> m_vecLayerName;
	std::vector<generic_string> m_vecLogType;
	std::vector<generic_string> m_vecFileName;
	std::vector<generic_string> m_vecFunName;
	std::vector<generic_string> m_vecThreadNo;


	ScintillaEditView **_ppEditView;

};


class CQuickSeekPanel : public DockingDlgInterface
{
public:
	CQuickSeekPanel() : DockingDlgInterface(IDD_QUICK_SEEK_PANEL), _ppEditView(NULL)
	{
		_findAllResult = 0;
	};
	
	void init(HINSTANCE hInst, HWND hPere, ScintillaEditView **ppEditView);

    virtual void display(bool toShow = true) const {
        DockingDlgInterface::display(toShow);
	};
	
	void setParent(HWND parent2set){
        _hParent = parent2set;
    };

	void beginNewFilesSearch()
	{
		_pFinder->getInstance()->beginNewFilesSearch();
		_pFinder->getInstance()->addSearchLine(m_QSFindStr.c_str());
	}

	void finishFilesSearch(int count)
	{
		_pFinder->getInstance()->finishFilesSearch(count);
	}

	void reload(bool isConvertFile);

	void focusOnFinder() {
		// Show finder and set focus
		if (_pFinder->getInstance()->getIsInit()) 
		{
			::SendMessage(_hParent, NPPM_DMMSHOW, 0, (LPARAM)_pFinder->getInstance()->getHSelf());
			_pFinder->getInstance()->_scintView.getFocus();
		}
	};

	int findInCurFile(const TCHAR *fileName);
	

protected:
	virtual BOOL CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);

private:



	//void generateFirstNode();
	BOOL setTreeViewImageList(int root_id, int node_id, int leaf_id);
	void notified(LPNMHDR notification);
	bool openSelectionDlg(const TreeView &treeView);
	
	void findAllIn(InWhat op);

	
	void eraseSpace(generic_string &str);
	void generateDisplayText(TCHAR *Dest, const char *sour);

	void ProcessMark(TCHAR *txt2find, int colourStyleID);
	void ProcessClearMark();

private:
	//HWND _hToolbarMenu;
	//HWND _hSearchEdit;

	//TreeView *_pTreeView;
	TreeView _treeView;
	//TreeView _treeViewSearchResult;

	//generic_string _sortTipStr;
	//generic_string _reloadTipStr;

	ScintillaEditView **_ppEditView;

	HIMAGELIST _hTreeViewImaLst;

	CQuickSeekMgr m_quickSeekMgr;

	Finder *_pFinder;

	int _findAllResult;
	TCHAR _findAllResultStr[1024];

	generic_string m_QSFindStr;
	string m_QSCHFindStr;
	int m_seekStartPos;
	int m_seekLen;

};


#endif //QUICK_SEEK_PANEL_H