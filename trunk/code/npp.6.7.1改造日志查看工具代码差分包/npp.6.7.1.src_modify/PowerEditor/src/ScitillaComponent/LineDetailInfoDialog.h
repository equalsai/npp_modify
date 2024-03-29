#ifndef LINE_DETAIL_INFO_DIALOG_H
#define LINE_DETAIL_INFO_DIALOG_H

#ifndef RESOURCE_H
#include "resource.h"
#endif //RESOURCE_H

#ifndef SCINTILLA_EDIT_VIEW_H
#include "ScintillaEditView.h"
#endif //SCINTILLA_EDIT_VIEW_H

class CLineDetailInfoDialog : public StaticDialog
{
public:
	CLineDetailInfoDialog() : StaticDialog() {};
	
	void init(HINSTANCE hInst, HWND hPere, ScintillaEditView **ppEditView) {
		Window::init(hInst, hPere);
		if (!ppEditView)
			throw std::runtime_error("CLineDetailInfoDialog::init : ppEditView is null.");
		_ppEditView = ppEditView;
	};
	
	virtual void create(int dialogID, bool isRTL = false) {
		StaticDialog::create(dialogID, isRTL);
	};
	
	void doDialog(bool isRTL = false) {
		if (!isCreated())
			create(IDD_LINE_DETAIL_INFO_DLG, isRTL);   //need to modify(ymj)
		display();
	};
	
    virtual void display(bool toShow = true) const {
        Window::display(toShow);
//         if (toShow)
//             ::SetFocus(::GetDlgItem(_hSelf, ID_GOLINE_EDIT));   //need to modify(ymj)
    };

	char *getLineContentBuf() { return m_lineContent; }

	void DisplayLineInfo(int lineLen = 0);
	
protected:

	virtual BOOL CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
	void generateDisplayText(TCHAR *Dest, char *sour);
	
private :

    ScintillaEditView **_ppEditView;

	char m_lineContent[1024 * 8];
	
};


#endif //LINE_DETAIL_INFO_DIALOG_H