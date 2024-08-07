#ifndef SPLITVIEW_H
#define SPLITVIEW_H

#include <Button.h>
#include <CheckBox.h>
#include <List.h>
#include <ListView.h>
#include <ScrollView.h>
#include <StringView.h>
#include <TextControl.h>
#include <View.h>

#include "CategoryButton.h"
#include "Fixed.h"
#include "Notifier.h"
#include "TransactionData.h"

enum {
	M_ADD_SPLIT = 'mads',
	M_REMOVE_SPLIT,
	M_ENTER_TRANSACTION = 'metr',
	M_EXPANDER_CHANGED,
	M_SELECT_SPLIT,
	M_SPLIT_CATEGORY_CHANGED,
	M_SPLIT_AMOUNT_CHANGED,
	M_SPLIT_MEMO_CHANGED,
	M_EDIT_KEY,
	M_NEXT_SPLIT,
	M_PREVIOUS_SPLIT,
	M_SHOW_CALENDER,
	M_SET_DATE
};

class SplitViewFilter;
class Category;
class DateBox;
class PayeeBox;
class CurrencyBox;
class CategoryBox;
class NavTextBox;
class HelpButton;

class SplitView : public BView, public Observer {
public:
	SplitView(const char* name, const TransactionData& trans, const int32& flags);
	~SplitView(void);
	void AttachedToWindow(void);
	void DetachedFromWindow(void);
	void MessageReceived(BMessage* msg);
	void SetFields(const char* date, const char* type, const char* payee, const char* amount,
		const char* category, const char* memo);

	void HandleNotify(const uint64& value, const BMessage* msg);
	void MakeEmpty(void);
	void MakeFocus(bool value = true);
	void FrameResized(float width, float height);

	bool IsSplitHidden(void) const { return fSplitContainer->IsHidden(); }

	void ToggleSplit(void);

private:
	friend SplitViewFilter;
	bool ValidateAllFields(void);
	//	bool ValidateDateField(void);
	//	bool ValidateAmountField(void);
	bool ValidateSplitAmountField(void);
	//	bool ValidateCategoryField(void);
	bool ValidateSplitItems(void);
	Fixed CalculateTotal(void);
	Category* MakeCategory(void);

	DateBox* fDate;
	PayeeBox* fPayee;
	CurrencyBox* fAmount;
	CategoryBox* fCategory;
	CategoryButton* fCategoryButton;
	NavTextBox* fMemo;
	SplitViewFilter* fKeyFilter;
	BMessenger* fMessenger;
	BButton *fEnter, *fTransfer;

	BCheckBox* fSplit;

	BView* fSplitContainer;
	CategoryBox* fSplitCategory;
	BTextControl *fSplitAmount, *fSplitMemo;
	BListView* fSplitItems;
	BScrollView* fSplitScroller;
	BButton *fAddSplit, *fRemoveSplit;
	BStringView* fSplitTotal;
	BCheckBox* fReconciled;

	time_t fCurrentDate;
	bool fStartExpanded;
	TransactionData fTransaction;
};

#endif
