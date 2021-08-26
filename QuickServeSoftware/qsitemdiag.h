#pragma once

#include <wx/wx.h>
#include "qsorderdiag.h"

/**
 * Dialog for when a meal is selected either in the order manager, or in the preview 
 */
class QSItemDiag : public wxDialog
{
public:
	enum class TYPE {UNADDED, ADDED};

	QSItemDiag(const wxString& title);

	void IntializeDiag(TYPE type);
	
	bool ToAdd() { return _add; }
	bool ToRemove() { return _remove; }
	bool ToEdit() { return _edit; }
	bool ToAddMod() { return _add_mod; }

private:
	
	void OnClick(wxCommandEvent& e);

	bool _add, _edit, _add_mod, _remove;
	TYPE _type;
};

