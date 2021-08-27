#include "qsitemdiag.h"
#include "qsconsts.h"

QSItemDiag::QSItemDiag(const wxString& title) : wxDialog(NULL, -1, title)
{

}

void QSItemDiag::IntializeDiag(TYPE type)
{
	_add = false;
	_edit = false;
	_remove = false;
	_add_mod = false;
	_type = type;

	auto* mainPanel = new wxPanel(this, wxID_ANY);
	auto* sizer = new wxBoxSizer(wxVERTICAL);

	wxButton* remove = nullptr;
	wxButton* add = nullptr;

	switch (_type) {
		case TYPE::ADDED:
			remove = new wxButton(mainPanel, qsc::ID_ITEM_OP_DIAG, "Remove");
			sizer->Add(remove, 1, wxEXPAND | wxALL, 2);
			break;
		case TYPE::UNADDED:
			add = new wxButton(mainPanel, qsc::ID_ITEM_OP_DIAG, "Add");
			sizer->Add(add, 1, wxEXPAND | wxALL, 2);
			break;
		default:
			break;
	}
	
	auto* edit = new wxButton(mainPanel, qsc::ID_ITEM_OP_DIAG, "Edit");
	auto* add_mod = new wxButton(mainPanel, qsc::ID_ITEM_OP_DIAG, "Add Modifier");

	Connect(qsc::ID_ITEM_OP_DIAG, wxEVT_BUTTON, wxCommandEventHandler(QSItemDiag::OnClick));

	sizer->Add(edit, 1, wxEXPAND | wxALL, 2);
	sizer->Add(add_mod, 1, wxEXPAND | wxALL, 2);

	mainPanel->SetSizer(sizer);

	ShowModal();
}

void QSItemDiag::OnClick(wxCommandEvent& e)
{
	auto label = ((wxButton*)e.GetEventObject())->GetLabel();

	if (label == "Add") {
		_add = true;
		this->Destroy();
	}
	else if (label == "Remove") {
		_remove = true;
		this->Destroy();
	}
	else if (label == "Edit") {
		_edit = true;
		this->Destroy();
	}
	else if (label == "Add Modifier") {
		_add_mod = true;
		this->Destroy();
	}
}


