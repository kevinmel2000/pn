/**
 * @file projectview.h
 * @brief View to display project trees.
 * @author Simon Steele
 * @note Copyright (c) 2002-2003 Simon Steele <s.steele@pnotepad.org>
 *
 * Programmers Notepad 2 : The license file (license.[txt|html]) describes 
 * the conditions under which this source may be modified / distributed.
 */

#ifndef projectview_h__included
#define projectview_h__included

class CProjectTreeCtrl : public CWindowImpl<CProjectTreeCtrl, CTreeViewCtrl>
{
	typedef CWindowImpl<CProjectTreeCtrl, CTreeViewCtrl> baseClass;
public:
	DECLARE_WND_CLASS(_T("ProjectTree"))

	CProjectTreeCtrl();

	void SetWorkspace(Projects::Workspace* ws);

	BEGIN_MSG_MAP(CProjectTreeCtrl)
		REFLECTED_NOTIFY_CODE_HANDLER(TVN_SELCHANGED, OnSelChanged)
		REFLECTED_NOTIFY_CODE_HANDLER(NM_RCLICK, OnRightClick)
		COMMAND_ID_HANDLER(ID_PROJECT_OPEN, OnOpenFile)
	END_MSG_MAP()

	Projects::File* GetSelectedFile();

protected:
	void buildTree();
	void buildProject(HTREEITEM hParentNode, Projects::Project* pj);
	HTREEITEM buildFolders(HTREEITEM hParentNode, const Projects::FOLDER_LIST& folders);
	HTREEITEM buildFiles(HTREEITEM hParentNode, HTREEITEM hInsertAfter, const Projects::FILE_LIST& files);
	void clearTree();

	LRESULT OnSelChanged(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/);
	LRESULT OnRightClick(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/);

	LRESULT OnOpenFile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

protected:
	Projects::File*			lastFile;
	Projects::Workspace*	workspace;
};

class CProjectDocker : public CPNDockingWindow<CProjectDocker>
{
	typedef CProjectDocker thisClass;
	typedef CPNDockingWindow<CProjectDocker> baseClass;

public:
	DECLARE_WND_CLASS(_T("CProjectDocker"))

	CProjectDocker();
	~CProjectDocker();

	BEGIN_MSG_MAP(thisClass)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		COMMAND_ID_HANDLER(ID_OUTPUT_HIDE, OnHide)
		NOTIFY_ID_HANDLER(100, OnTreeNotify)
		REFLECT_NOTIFICATIONS()
		CHAIN_MSG_MAP(baseClass)
	END_MSG_MAP()

	void SetWorkspace(Projects::Workspace* ws);

protected:
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/);
	LRESULT OnHide(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	LRESULT OnTreeNotify(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/);

	void buildTree();

	Projects::Workspace*	workspace;
	CProjectTreeCtrl		m_view;
};

#endif