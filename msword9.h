// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// _Application wrapper class

class _Application : public COleDispatchDriver
{
public:
	_Application() {}		// Calls COleDispatchDriver default constructor
	_Application(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Application(const _Application& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	LPDISPATCH GetDocuments();
	LPDISPATCH GetWindows();
	LPDISPATCH GetActiveDocument();
	LPDISPATCH GetActiveWindow();
	LPDISPATCH GetSelection();
	LPDISPATCH GetWordBasic();
	LPDISPATCH GetRecentFiles();
	LPDISPATCH GetNormalTemplate();
	LPDISPATCH GetSystem();
	LPDISPATCH GetAutoCorrect();
	LPDISPATCH GetFontNames();
	LPDISPATCH GetLandscapeFontNames();
	LPDISPATCH GetPortraitFontNames();
	LPDISPATCH GetLanguages();
	LPDISPATCH GetAssistant();
	LPDISPATCH GetBrowser();
	LPDISPATCH GetFileConverters();
	LPDISPATCH GetMailingLabel();
	LPDISPATCH GetDialogs();
	LPDISPATCH GetCaptionLabels();
	LPDISPATCH GetAutoCaptions();
	LPDISPATCH GetAddIns();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	CString GetVersion();
	BOOL GetScreenUpdating();
	void SetScreenUpdating(BOOL bNewValue);
	BOOL GetPrintPreview();
	void SetPrintPreview(BOOL bNewValue);
	LPDISPATCH GetTasks();
	BOOL GetDisplayStatusBar();
	void SetDisplayStatusBar(BOOL bNewValue);
	BOOL GetSpecialMode();
	long GetUsableWidth();
	long GetUsableHeight();
	BOOL GetMathCoprocessorAvailable();
	BOOL GetMouseAvailable();
	VARIANT GetInternational(long Index);
	CString GetBuild();
	BOOL GetCapsLock();
	BOOL GetNumLock();
	CString GetUserName_();
	void SetUserName(LPCTSTR lpszNewValue);
	CString GetUserInitials();
	void SetUserInitials(LPCTSTR lpszNewValue);
	CString GetUserAddress();
	void SetUserAddress(LPCTSTR lpszNewValue);
	LPDISPATCH GetMacroContainer();
	BOOL GetDisplayRecentFiles();
	void SetDisplayRecentFiles(BOOL bNewValue);
	LPDISPATCH GetCommandBars();
	LPDISPATCH GetSynonymInfo(LPCTSTR Word, VARIANT* LanguageID);
	LPDISPATCH GetVbe();
	CString GetDefaultSaveFormat();
	void SetDefaultSaveFormat(LPCTSTR lpszNewValue);
	LPDISPATCH GetListGalleries();
	CString GetActivePrinter();
	void SetActivePrinter(LPCTSTR lpszNewValue);
	LPDISPATCH GetTemplates();
	LPDISPATCH GetCustomizationContext();
	void SetCustomizationContext(LPDISPATCH newValue);
	LPDISPATCH GetKeyBindings();
	LPDISPATCH GetKeysBoundTo(long KeyCategory, LPCTSTR Command, VARIANT* CommandParameter);
	LPDISPATCH GetFindKey(long KeyCode, VARIANT* KeyCode2);
	CString GetCaption();
	void SetCaption(LPCTSTR lpszNewValue);
	CString GetPath();
	BOOL GetDisplayScrollBars();
	void SetDisplayScrollBars(BOOL bNewValue);
	CString GetStartupPath();
	void SetStartupPath(LPCTSTR lpszNewValue);
	long GetBackgroundSavingStatus();
	long GetBackgroundPrintingStatus();
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetWindowState();
	void SetWindowState(long nNewValue);
	BOOL GetDisplayAutoCompleteTips();
	void SetDisplayAutoCompleteTips(BOOL bNewValue);
	LPDISPATCH GetOptions();
	long GetDisplayAlerts();
	void SetDisplayAlerts(long nNewValue);
	LPDISPATCH GetCustomDictionaries();
	CString GetPathSeparator();
	void SetStatusBar(LPCTSTR lpszNewValue);
	BOOL GetMAPIAvailable();
	BOOL GetDisplayScreenTips();
	void SetDisplayScreenTips(BOOL bNewValue);
	long GetEnableCancelKey();
	void SetEnableCancelKey(long nNewValue);
	BOOL GetUserControl();
	LPDISPATCH GetFileSearch();
	long GetMailSystem();
	CString GetDefaultTableSeparator();
	void SetDefaultTableSeparator(LPCTSTR lpszNewValue);
	BOOL GetShowVisualBasicEditor();
	void SetShowVisualBasicEditor(BOOL bNewValue);
	CString GetBrowseExtraFileTypes();
	void SetBrowseExtraFileTypes(LPCTSTR lpszNewValue);
	BOOL GetIsObjectValid(LPDISPATCH Object);
	LPDISPATCH GetHangulHanjaDictionaries();
	LPDISPATCH GetMailMessage();
	BOOL GetFocusInMailHeader();
	void Quit(VARIANT* SaveChanges, VARIANT* OriginalFormat, VARIANT* RouteDocument);
	void ScreenRefresh();
	void LookupNameProperties(LPCTSTR Name);
	void SubstituteFont(LPCTSTR UnavailableFont, LPCTSTR SubstituteFont);
	BOOL Repeat(VARIANT* Times);
	void DDEExecute(long Channel, LPCTSTR Command);
	long DDEInitiate(LPCTSTR App, LPCTSTR Topic);
	void DDEPoke(long Channel, LPCTSTR Item, LPCTSTR Data);
	CString DDERequest(long Channel, LPCTSTR Item);
	void DDETerminate(long Channel);
	void DDETerminateAll();
	long BuildKeyCode(long Arg1, VARIANT* Arg2, VARIANT* Arg3, VARIANT* Arg4);
	CString KeyString(long KeyCode, VARIANT* KeyCode2);
	void OrganizerCopy(LPCTSTR Source, LPCTSTR Destination, LPCTSTR Name, long Object);
	void OrganizerDelete(LPCTSTR Source, LPCTSTR Name, long Object);
	void OrganizerRename(LPCTSTR Source, LPCTSTR Name, LPCTSTR NewName, long Object);
	// method 'AddAddress' not emitted because of invalid return type or parameter type
	CString GetAddress(VARIANT* Name, VARIANT* AddressProperties, VARIANT* UseAutoText, VARIANT* DisplaySelectDialog, VARIANT* SelectDialog, VARIANT* CheckNamesDialog, VARIANT* RecentAddressesChoice, VARIANT* UpdateRecentAddresses);
	BOOL CheckGrammar(LPCTSTR String);
	BOOL CheckSpelling(LPCTSTR Word, VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* MainDictionary, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, VARIANT* CustomDictionary5, 
		VARIANT* CustomDictionary6, VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
	void ResetIgnoreAll();
	LPDISPATCH GetSpellingSuggestions(LPCTSTR Word, VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* MainDictionary, VARIANT* SuggestionMode, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, 
		VARIANT* CustomDictionary5, VARIANT* CustomDictionary6, VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
	void GoBack();
	void Help(VARIANT* HelpType);
	void AutomaticChange();
	void ShowMe();
	void HelpTool();
	LPDISPATCH NewWindow();
	void ListCommands(BOOL ListAllCommands);
	void ShowClipboard();
	void OnTime(VARIANT* When, LPCTSTR Name, VARIANT* Tolerance);
	void NextLetter();
	short MountVolume(LPCTSTR Zone, LPCTSTR Server, LPCTSTR Volume, VARIANT* User, VARIANT* UserPassword, VARIANT* VolumePassword);
	CString CleanString(LPCTSTR String);
	void SendFax();
	void ChangeFileOpenDirectory(LPCTSTR Path);
	void GoForward();
	void Move(long Left, long Top);
	void Resize(long Width, long Height);
	float InchesToPoints(float Inches);
	float CentimetersToPoints(float Centimeters);
	float MillimetersToPoints(float Millimeters);
	float PicasToPoints(float Picas);
	float LinesToPoints(float Lines);
	float PointsToInches(float Points);
	float PointsToCentimeters(float Points);
	float PointsToMillimeters(float Points);
	float PointsToPicas(float Points);
	float PointsToLines(float Points);
	void Activate();
	float PointsToPixels(float Points, VARIANT* fVertical);
	float PixelsToPoints(float Pixels, VARIANT* fVertical);
	void KeyboardLatin();
	void KeyboardBidi();
	void ToggleKeyboard();
	long Keyboard(long LangId);
	CString ProductCode();
	LPDISPATCH DefaultWebOptions();
	void SetDefaultTheme(LPCTSTR Name, long DocumentType);
	CString GetDefaultTheme(long DocumentType);
	LPDISPATCH GetEmailOptions();
	long GetLanguage();
	LPDISPATCH GetCOMAddIns();
	BOOL GetCheckLanguage();
	void SetCheckLanguage(BOOL bNewValue);
	LPDISPATCH GetLanguageSettings();
	LPDISPATCH GetAnswerWizard();
	long GetFeatureInstall();
	void SetFeatureInstall(long nNewValue);
	void PrintOut(VARIANT* Background, VARIANT* Append, VARIANT* Range, VARIANT* OutputFileName, VARIANT* From, VARIANT* To, VARIANT* Item, VARIANT* Copies, VARIANT* Pages, VARIANT* PageType, VARIANT* PrintToFile, VARIANT* Collate, 
		VARIANT* FileName, VARIANT* ActivePrinterMacGX, VARIANT* ManualDuplexPrint, VARIANT* PrintZoomColumn, VARIANT* PrintZoomRow, VARIANT* PrintZoomPaperWidth, VARIANT* PrintZoomPaperHeight);
	VARIANT Run(LPCTSTR MacroName, VARIANT* varg1, VARIANT* varg2, VARIANT* varg3, VARIANT* varg4, VARIANT* varg5, VARIANT* varg6, VARIANT* varg7, VARIANT* varg8, VARIANT* varg9, VARIANT* varg10, VARIANT* varg11, VARIANT* varg12, VARIANT* varg13, 
		VARIANT* varg14, VARIANT* varg15, VARIANT* varg16, VARIANT* varg17, VARIANT* varg18, VARIANT* varg19, VARIANT* varg20, VARIANT* varg21, VARIANT* varg22, VARIANT* varg23, VARIANT* varg24, VARIANT* varg25, VARIANT* varg26, VARIANT* varg27, 
		VARIANT* varg28, VARIANT* varg29, VARIANT* varg30);
};
/////////////////////////////////////////////////////////////////////////////
// _Document wrapper class

class _Document : public COleDispatchDriver
{
public:
	_Document() {}		// Calls COleDispatchDriver default constructor
	_Document(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Document(const _Document& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetBuiltInDocumentProperties();
	LPDISPATCH GetCustomDocumentProperties();
	CString GetPath();
	LPDISPATCH GetBookmarks();
	LPDISPATCH GetTables();
	LPDISPATCH GetFootnotes();
	LPDISPATCH GetEndnotes();
	LPDISPATCH GetComments();
	long GetType();
	BOOL GetAutoHyphenation();
	void SetAutoHyphenation(BOOL bNewValue);
	BOOL GetHyphenateCaps();
	void SetHyphenateCaps(BOOL bNewValue);
	long GetHyphenationZone();
	void SetHyphenationZone(long nNewValue);
	long GetConsecutiveHyphensLimit();
	void SetConsecutiveHyphensLimit(long nNewValue);
	LPDISPATCH GetSections();
	LPDISPATCH GetParagraphs();
	LPDISPATCH GetWords();
	LPDISPATCH GetSentences();
	LPDISPATCH GetCharacters();
	LPDISPATCH GetFields();
	LPDISPATCH GetFormFields();
	LPDISPATCH GetStyles();
	LPDISPATCH GetFrames();
	LPDISPATCH GetTablesOfFigures();
	LPDISPATCH GetVariables();
	LPDISPATCH GetMailMerge();
	LPDISPATCH GetEnvelope();
	CString GetFullName();
	LPDISPATCH GetRevisions();
	LPDISPATCH GetTablesOfContents();
	LPDISPATCH GetTablesOfAuthorities();
	LPDISPATCH GetPageSetup();
	void SetPageSetup(LPDISPATCH newValue);
	LPDISPATCH GetWindows();
	BOOL GetHasRoutingSlip();
	void SetHasRoutingSlip(BOOL bNewValue);
	LPDISPATCH GetRoutingSlip();
	BOOL GetRouted();
	LPDISPATCH GetTablesOfAuthoritiesCategories();
	LPDISPATCH GetIndexes();
	BOOL GetSaved();
	void SetSaved(BOOL bNewValue);
	LPDISPATCH GetContent();
	LPDISPATCH GetActiveWindow();
	long GetKind();
	void SetKind(long nNewValue);
	BOOL GetReadOnly();
	LPDISPATCH GetSubdocuments();
	BOOL GetIsMasterDocument();
	float GetDefaultTabStop();
	void SetDefaultTabStop(float newValue);
	BOOL GetEmbedTrueTypeFonts();
	void SetEmbedTrueTypeFonts(BOOL bNewValue);
	BOOL GetSaveFormsData();
	void SetSaveFormsData(BOOL bNewValue);
	BOOL GetReadOnlyRecommended();
	void SetReadOnlyRecommended(BOOL bNewValue);
	BOOL GetSaveSubsetFonts();
	void SetSaveSubsetFonts(BOOL bNewValue);
	BOOL GetCompatibility(long Type);
	void SetCompatibility(long Type, BOOL bNewValue);
	LPDISPATCH GetStoryRanges();
	LPDISPATCH GetCommandBars();
	BOOL GetIsSubdocument();
	long GetSaveFormat();
	long GetProtectionType();
	LPDISPATCH GetHyperlinks();
	LPDISPATCH GetShapes();
	LPDISPATCH GetListTemplates();
	LPDISPATCH GetLists();
	BOOL GetUpdateStylesOnOpen();
	void SetUpdateStylesOnOpen(BOOL bNewValue);
	VARIANT GetAttachedTemplate();
	void SetAttachedTemplate(VARIANT* newValue);
	LPDISPATCH GetInlineShapes();
	LPDISPATCH GetBackground();
	void SetBackground(LPDISPATCH newValue);
	BOOL GetGrammarChecked();
	void SetGrammarChecked(BOOL bNewValue);
	BOOL GetSpellingChecked();
	void SetSpellingChecked(BOOL bNewValue);
	BOOL GetShowGrammaticalErrors();
	void SetShowGrammaticalErrors(BOOL bNewValue);
	BOOL GetShowSpellingErrors();
	void SetShowSpellingErrors(BOOL bNewValue);
	LPDISPATCH GetVersions();
	BOOL GetShowSummary();
	void SetShowSummary(BOOL bNewValue);
	long GetSummaryViewMode();
	void SetSummaryViewMode(long nNewValue);
	long GetSummaryLength();
	void SetSummaryLength(long nNewValue);
	BOOL GetPrintFractionalWidths();
	void SetPrintFractionalWidths(BOOL bNewValue);
	BOOL GetPrintPostScriptOverText();
	void SetPrintPostScriptOverText(BOOL bNewValue);
	LPDISPATCH GetContainer();
	BOOL GetPrintFormsData();
	void SetPrintFormsData(BOOL bNewValue);
	LPDISPATCH GetListParagraphs();
	void SetPassword(LPCTSTR lpszNewValue);
	void SetWritePassword(LPCTSTR lpszNewValue);
	BOOL GetHasPassword();
	BOOL GetWriteReserved();
	CString GetActiveWritingStyle(VARIANT* LanguageID);
	void SetActiveWritingStyle(VARIANT* LanguageID, LPCTSTR lpszNewValue);
	BOOL GetUserControl();
	void SetUserControl(BOOL bNewValue);
	BOOL GetHasMailer();
	void SetHasMailer(BOOL bNewValue);
	LPDISPATCH GetMailer();
	LPDISPATCH GetReadabilityStatistics();
	LPDISPATCH GetGrammaticalErrors();
	LPDISPATCH GetSpellingErrors();
	LPDISPATCH GetVBProject();
	BOOL GetFormsDesign();
	CString Get_CodeName();
	void Set_CodeName(LPCTSTR lpszNewValue);
	CString GetCodeName();
	BOOL GetSnapToGrid();
	void SetSnapToGrid(BOOL bNewValue);
	BOOL GetSnapToShapes();
	void SetSnapToShapes(BOOL bNewValue);
	float GetGridDistanceHorizontal();
	void SetGridDistanceHorizontal(float newValue);
	float GetGridDistanceVertical();
	void SetGridDistanceVertical(float newValue);
	float GetGridOriginHorizontal();
	void SetGridOriginHorizontal(float newValue);
	float GetGridOriginVertical();
	void SetGridOriginVertical(float newValue);
	long GetGridSpaceBetweenHorizontalLines();
	void SetGridSpaceBetweenHorizontalLines(long nNewValue);
	long GetGridSpaceBetweenVerticalLines();
	void SetGridSpaceBetweenVerticalLines(long nNewValue);
	BOOL GetGridOriginFromMargin();
	void SetGridOriginFromMargin(BOOL bNewValue);
	BOOL GetKerningByAlgorithm();
	void SetKerningByAlgorithm(BOOL bNewValue);
	long GetJustificationMode();
	void SetJustificationMode(long nNewValue);
	long GetFarEastLineBreakLevel();
	void SetFarEastLineBreakLevel(long nNewValue);
	CString GetNoLineBreakBefore();
	void SetNoLineBreakBefore(LPCTSTR lpszNewValue);
	CString GetNoLineBreakAfter();
	void SetNoLineBreakAfter(LPCTSTR lpszNewValue);
	BOOL GetTrackRevisions();
	void SetTrackRevisions(BOOL bNewValue);
	BOOL GetPrintRevisions();
	void SetPrintRevisions(BOOL bNewValue);
	BOOL GetShowRevisions();
	void SetShowRevisions(BOOL bNewValue);
	void Close(VARIANT* SaveChanges, VARIANT* OriginalFormat, VARIANT* RouteDocument);
	void SaveAs(VARIANT* FileName, VARIANT* FileFormat, VARIANT* LockComments, VARIANT* Password, VARIANT* AddToRecentFiles, VARIANT* WritePassword, VARIANT* ReadOnlyRecommended, VARIANT* EmbedTrueTypeFonts, VARIANT* SaveNativePictureFormat, 
		VARIANT* SaveFormsData, VARIANT* SaveAsAOCELetter);
	void Repaginate();
	void FitToPages();
	void ManualHyphenation();
	void Select();
	void DataForm();
	void Route();
	void Save();
	void SendMail();
	LPDISPATCH Range(VARIANT* Start, VARIANT* End);
	void RunAutoMacro(long Which);
	void Activate();
	void PrintPreview();
	LPDISPATCH GoTo(VARIANT* What, VARIANT* Which, VARIANT* Count, VARIANT* Name);
	BOOL Undo(VARIANT* Times);
	BOOL Redo(VARIANT* Times);
	long ComputeStatistics(long Statistic, VARIANT* IncludeFootnotesAndEndnotes);
	void MakeCompatibilityDefault();
	void Protect(long Type, VARIANT* NoReset, VARIANT* Password);
	void Unprotect(VARIANT* Password);
	void EditionOptions(long Type, long Option, LPCTSTR Name, VARIANT* Format);
	void RunLetterWizard(VARIANT* LetterContent, VARIANT* WizardMode);
	LPDISPATCH GetLetterContent();
	void SetLetterContent(VARIANT* LetterContent);
	void CopyStylesFromTemplate(LPCTSTR Template);
	void UpdateStyles();
	void CheckGrammar();
	void CheckSpelling(VARIANT* CustomDictionary, VARIANT* IgnoreUppercase, VARIANT* AlwaysSuggest, VARIANT* CustomDictionary2, VARIANT* CustomDictionary3, VARIANT* CustomDictionary4, VARIANT* CustomDictionary5, VARIANT* CustomDictionary6, 
		VARIANT* CustomDictionary7, VARIANT* CustomDictionary8, VARIANT* CustomDictionary9, VARIANT* CustomDictionary10);
	void FollowHyperlink(VARIANT* Address, VARIANT* SubAddress, VARIANT* NewWindow, VARIANT* AddHistory, VARIANT* ExtraInfo, VARIANT* Method, VARIANT* HeaderInfo);
	void AddToFavorites();
	void Reload();
	LPDISPATCH AutoSummarize(VARIANT* Length, VARIANT* Mode, VARIANT* UpdateProperties);
	void RemoveNumbers(VARIANT* NumberType);
	void ConvertNumbersToText(VARIANT* NumberType);
	long CountNumberedItems(VARIANT* NumberType, VARIANT* Level);
	void Post();
	void ToggleFormsDesign();
	void Compare(LPCTSTR Name);
	void UpdateSummaryProperties();
	VARIANT GetCrossReferenceItems(VARIANT* ReferenceType);
	void AutoFormat();
	void ViewCode();
	void ViewPropertyBrowser();
	void ForwardMailer();
	void Reply();
	void ReplyAll();
	void SendMailer(VARIANT* FileFormat, VARIANT* Priority);
	void UndoClear();
	void PresentIt();
	void SendFax(LPCTSTR Address, VARIANT* Subject);
	void Merge(LPCTSTR FileName);
	void ClosePrintPreview();
	void CheckConsistency();
	LPDISPATCH CreateLetterContent(LPCTSTR DateFormat, BOOL IncludeHeaderFooter, LPCTSTR PageDesign, long LetterStyle, BOOL Letterhead, long LetterheadLocation, float LetterheadSize, LPCTSTR RecipientName, LPCTSTR RecipientAddress, 
		LPCTSTR Salutation, long SalutationType, LPCTSTR RecipientReference, LPCTSTR MailingInstructions, LPCTSTR AttentionLine, LPCTSTR Subject, LPCTSTR CCList, LPCTSTR ReturnAddress, LPCTSTR SenderName, LPCTSTR Closing, LPCTSTR SenderCompany, 
		LPCTSTR SenderJobTitle, LPCTSTR SenderInitials, long EnclosureNumber, VARIANT* InfoBlock, VARIANT* RecipientCode, VARIANT* RecipientGender, VARIANT* ReturnAddressShortForm, VARIANT* SenderCity, VARIANT* SenderCode, VARIANT* SenderGender, 
		VARIANT* SenderReference);
	void AcceptAllRevisions();
	void RejectAllRevisions();
	void DetectLanguage();
	void ApplyTheme(LPCTSTR Name);
	void RemoveTheme();
	void WebPagePreview();
	void ReloadAs(long Encoding);
	CString GetActiveTheme();
	CString GetActiveThemeDisplayName();
	LPDISPATCH GetEmail();
	LPDISPATCH GetScripts();
	BOOL GetLanguageDetected();
	void SetLanguageDetected(BOOL bNewValue);
	long GetFarEastLineBreakLanguage();
	void SetFarEastLineBreakLanguage(long nNewValue);
	LPDISPATCH GetFrameset();
	VARIANT GetClickAndTypeParagraphStyle();
	void SetClickAndTypeParagraphStyle(VARIANT* newValue);
	LPDISPATCH GetHTMLProject();
	LPDISPATCH GetWebOptions();
	long GetOpenEncoding();
	long GetSaveEncoding();
	void SetSaveEncoding(long nNewValue);
	BOOL GetOptimizeForWord97();
	void SetOptimizeForWord97(BOOL bNewValue);
	BOOL GetVBASigned();
	void PrintOut(VARIANT* Background, VARIANT* Append, VARIANT* Range, VARIANT* OutputFileName, VARIANT* From, VARIANT* To, VARIANT* Item, VARIANT* Copies, VARIANT* Pages, VARIANT* PageType, VARIANT* PrintToFile, VARIANT* Collate, 
		VARIANT* ActivePrinterMacGX, VARIANT* ManualDuplexPrint, VARIANT* PrintZoomColumn, VARIANT* PrintZoomRow, VARIANT* PrintZoomPaperWidth, VARIANT* PrintZoomPaperHeight);
};
/////////////////////////////////////////////////////////////////////////////
// Selection wrapper class

class Selection : public COleDispatchDriver
{
public:
	Selection() {}		// Calls COleDispatchDriver default constructor
	Selection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Selection(const Selection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	LPDISPATCH GetFormattedText();
	void SetFormattedText(LPDISPATCH newValue);
	long GetStart();
	void SetStart(long nNewValue);
	long GetEnd();
	void SetEnd(long nNewValue);
	LPDISPATCH GetFont();
	void SetFont(LPDISPATCH newValue);
	long GetType();
	long GetStoryType();
	VARIANT GetStyle();
	void SetStyle(VARIANT* newValue);
	LPDISPATCH GetTables();
	LPDISPATCH GetWords();
	LPDISPATCH GetSentences();
	LPDISPATCH GetCharacters();
	LPDISPATCH GetFootnotes();
	LPDISPATCH GetEndnotes();
	LPDISPATCH GetComments();
	LPDISPATCH GetCells();
	LPDISPATCH GetSections();
	LPDISPATCH GetParagraphs();
	LPDISPATCH GetBorders();
	void SetBorders(LPDISPATCH newValue);
	LPDISPATCH GetShading();
	LPDISPATCH GetFields();
	LPDISPATCH GetFormFields();
	LPDISPATCH GetFrames();
	LPDISPATCH GetParagraphFormat();
	void SetParagraphFormat(LPDISPATCH newValue);
	LPDISPATCH GetPageSetup();
	void SetPageSetup(LPDISPATCH newValue);
	LPDISPATCH GetBookmarks();
	long GetStoryLength();
	long GetLanguageID();
	void SetLanguageID(long nNewValue);
	long GetLanguageIDFarEast();
	void SetLanguageIDFarEast(long nNewValue);
	long GetLanguageIDOther();
	void SetLanguageIDOther(long nNewValue);
	LPDISPATCH GetHyperlinks();
	LPDISPATCH GetColumns();
	LPDISPATCH GetRows();
	LPDISPATCH GetHeaderFooter();
	BOOL GetIsEndOfRowMark();
	long GetBookmarkID();
	long GetPreviousBookmarkID();
	LPDISPATCH GetFind();
	LPDISPATCH GetRange();
	VARIANT GetInformation(long Type);
	long GetFlags();
	void SetFlags(long nNewValue);
	BOOL GetActive();
	BOOL GetStartIsActive();
	void SetStartIsActive(BOOL bNewValue);
	BOOL GetIPAtEndOfLine();
	BOOL GetExtendMode();
	void SetExtendMode(BOOL bNewValue);
	BOOL GetColumnSelectMode();
	void SetColumnSelectMode(BOOL bNewValue);
	long GetOrientation();
	void SetOrientation(long nNewValue);
	LPDISPATCH GetInlineShapes();
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetDocument();
	LPDISPATCH GetShapeRange();
	void Select();
	void SetRange(long Start, long End);
	void Collapse(VARIANT* Direction);
	void InsertBefore(LPCTSTR Text);
	void InsertAfter(LPCTSTR Text);
	LPDISPATCH Next(VARIANT* Unit, VARIANT* Count);
	LPDISPATCH Previous(VARIANT* Unit, VARIANT* Count);
	long StartOf(VARIANT* Unit, VARIANT* Extend);
	long EndOf(VARIANT* Unit, VARIANT* Extend);
	long Move(VARIANT* Unit, VARIANT* Count);
	long MoveStart(VARIANT* Unit, VARIANT* Count);
	long MoveEnd(VARIANT* Unit, VARIANT* Count);
	long MoveWhile(VARIANT* Cset, VARIANT* Count);
	long MoveStartWhile(VARIANT* Cset, VARIANT* Count);
	long MoveEndWhile(VARIANT* Cset, VARIANT* Count);
	long MoveUntil(VARIANT* Cset, VARIANT* Count);
	long MoveStartUntil(VARIANT* Cset, VARIANT* Count);
	long MoveEndUntil(VARIANT* Cset, VARIANT* Count);
	void Cut();
	void Copy();
	void Paste();
	void InsertBreak(VARIANT* Type);
	void InsertFile(LPCTSTR FileName, VARIANT* Range, VARIANT* ConfirmConversions, VARIANT* Link, VARIANT* Attachment);
	BOOL InStory(LPDISPATCH Range);
	BOOL InRange(LPDISPATCH Range);
	long Delete(VARIANT* Unit, VARIANT* Count);
	long Expand(VARIANT* Unit);
	void InsertParagraph();
	void InsertParagraphAfter();
	void InsertSymbol(long CharacterNumber, VARIANT* Font, VARIANT* Unicode, VARIANT* Bias);
	void InsertCrossReference(VARIANT* ReferenceType, long ReferenceKind, VARIANT* ReferenceItem, VARIANT* InsertAsHyperlink, VARIANT* IncludePosition);
	void InsertCaption(VARIANT* Label, VARIANT* Title, VARIANT* TitleAutoText, VARIANT* Position);
	void CopyAsPicture();
	void SortAscending();
	void SortDescending();
	BOOL IsEqual(LPDISPATCH Range);
	float Calculate();
	LPDISPATCH GoTo(VARIANT* What, VARIANT* Which, VARIANT* Count, VARIANT* Name);
	LPDISPATCH GoToNext(long What);
	LPDISPATCH GoToPrevious(long What);
	void PasteSpecial(VARIANT* IconIndex, VARIANT* Link, VARIANT* Placement, VARIANT* DisplayAsIcon, VARIANT* DataType, VARIANT* IconFileName, VARIANT* IconLabel);
	LPDISPATCH PreviousField();
	LPDISPATCH NextField();
	void InsertParagraphBefore();
	void InsertCells(VARIANT* ShiftCells);
	void Extend(VARIANT* Character);
	void Shrink();
	long MoveLeft(VARIANT* Unit, VARIANT* Count, VARIANT* Extend);
	long MoveRight(VARIANT* Unit, VARIANT* Count, VARIANT* Extend);
	long MoveUp(VARIANT* Unit, VARIANT* Count, VARIANT* Extend);
	long MoveDown(VARIANT* Unit, VARIANT* Count, VARIANT* Extend);
	long HomeKey(VARIANT* Unit, VARIANT* Extend);
	long EndKey(VARIANT* Unit, VARIANT* Extend);
	void EscapeKey();
	void TypeText(LPCTSTR Text);
	void CopyFormat();
	void PasteFormat();
	void TypeParagraph();
	void TypeBackspace();
	void NextSubdocument();
	void PreviousSubdocument();
	void SelectColumn();
	void SelectCurrentFont();
	void SelectCurrentAlignment();
	void SelectCurrentSpacing();
	void SelectCurrentIndent();
	void SelectCurrentTabs();
	void SelectCurrentColor();
	void CreateTextbox();
	void WholeStory();
	void SelectRow();
	void SplitTable();
	void InsertRows(VARIANT* NumRows);
	void InsertColumns();
	void InsertFormula(VARIANT* Formula, VARIANT* NumberFormat);
	LPDISPATCH NextRevision(VARIANT* Wrap);
	LPDISPATCH PreviousRevision(VARIANT* Wrap);
	void PasteAsNestedTable();
	LPDISPATCH CreateAutoTextEntry(LPCTSTR Name, LPCTSTR StyleName);
	void DetectLanguage();
	void SelectCell();
	void InsertRowsBelow(VARIANT* NumRows);
	void InsertColumnsRight();
	void InsertRowsAbove(VARIANT* NumRows);
	void RtlRun();
	void LtrRun();
	void BoldRun();
	void ItalicRun();
	void RtlPara();
	void LtrPara();
	void InsertDateTime(VARIANT* DateTimeFormat, VARIANT* InsertAsField, VARIANT* InsertAsFullWidth, VARIANT* DateLanguage, VARIANT* CalendarType);
	void Sort(VARIANT* ExcludeHeader, VARIANT* FieldNumber, VARIANT* SortFieldType, VARIANT* SortOrder, VARIANT* FieldNumber2, VARIANT* SortFieldType2, VARIANT* SortOrder2, VARIANT* FieldNumber3, VARIANT* SortFieldType3, VARIANT* SortOrder3, 
		VARIANT* SortColumn, VARIANT* Separator, VARIANT* CaseSensitive, VARIANT* BidiSort, VARIANT* IgnoreThe, VARIANT* IgnoreKashida, VARIANT* IgnoreDiacritics, VARIANT* IgnoreHe, VARIANT* LanguageID);
	LPDISPATCH ConvertToTable(VARIANT* Separator, VARIANT* NumRows, VARIANT* NumColumns, VARIANT* InitialColumnWidth, VARIANT* Format, VARIANT* ApplyBorders, VARIANT* ApplyShading, VARIANT* ApplyFont, VARIANT* ApplyColor, 
		VARIANT* ApplyHeadingRows, VARIANT* ApplyLastRow, VARIANT* ApplyFirstColumn, VARIANT* ApplyLastColumn, VARIANT* AutoFit, VARIANT* AutoFitBehavior, VARIANT* DefaultTableBehavior);
	long GetNoProofing();
	void SetNoProofing(long nNewValue);
	LPDISPATCH GetTopLevelTables();
	BOOL GetLanguageDetected();
	void SetLanguageDetected(BOOL bNewValue);
	float GetFitTextWidth();
	void SetFitTextWidth(float newValue);
};

class CFont0 : public COleDispatchDriver
{
public:
	CFont0(){} // Calls COleDispatchDriver default constructor
	CFont0(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CFont0(const CFont0& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// _Font methods
public:
	LPDISPATCH get_Application()
	{
		LPDISPATCH result;
		InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Creator()
	{
		long result;
		InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Parent()
	{
		LPDISPATCH result;
		InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Duplicate()
	{
		LPDISPATCH result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Bold()
	{
		long result;
		InvokeHelper(0x82, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Bold(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x82, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Italic()
	{
		long result;
		InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Italic(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x83, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Hidden()
	{
		long result;
		InvokeHelper(0x84, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Hidden(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x84, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SmallCaps()
	{
		long result;
		InvokeHelper(0x85, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SmallCaps(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x85, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_AllCaps()
	{
		long result;
		InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_AllCaps(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x86, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_StrikeThrough()
	{
		long result;
		InvokeHelper(0x87, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_StrikeThrough(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x87, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_DoubleStrikeThrough()
	{
		long result;
		InvokeHelper(0x88, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_DoubleStrikeThrough(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x88, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ColorIndex()
	{
		long result;
		InvokeHelper(0x89, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ColorIndex(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x89, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Subscript()
	{
		long result;
		InvokeHelper(0x8a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Subscript(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Superscript()
	{
		long result;
		InvokeHelper(0x8b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Superscript(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Underline()
	{
		long result;
		InvokeHelper(0x8c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Underline(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_Size()
	{
		float result;
		InvokeHelper(0x8d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_Size(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x8d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x8e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Name(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x8e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Position()
	{
		long result;
		InvokeHelper(0x8f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Position(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_Spacing()
	{
		float result;
		InvokeHelper(0x90, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_Spacing(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x90, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Scaling()
	{
		long result;
		InvokeHelper(0x91, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Scaling(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x91, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Shadow()
	{
		long result;
		InvokeHelper(0x92, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Shadow(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x92, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Outline()
	{
		long result;
		InvokeHelper(0x93, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Outline(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x93, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Emboss()
	{
		long result;
		InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Emboss(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x94, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_Kerning()
	{
		float result;
		InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_Kerning(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x95, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Engrave()
	{
		long result;
		InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Engrave(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x96, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Animation()
	{
		long result;
		InvokeHelper(0x97, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Animation(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x97, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Borders()
	{
		LPDISPATCH result;
		InvokeHelper(0x44c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_Borders(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x44c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Shading()
	{
		LPDISPATCH result;
		InvokeHelper(0x99, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_EmphasisMark()
	{
		long result;
		InvokeHelper(0x9a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_EmphasisMark(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x9a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_DisableCharacterSpaceGrid()
	{
		BOOL result;
		InvokeHelper(0x9b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_DisableCharacterSpaceGrid(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x9b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_NameFarEast()
	{
		CString result;
		InvokeHelper(0x9c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_NameFarEast(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_NameAscii()
	{
		CString result;
		InvokeHelper(0x9d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_NameAscii(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_NameOther()
	{
		CString result;
		InvokeHelper(0x9e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_NameOther(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x9e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void Grow()
	{
		InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Shrink()
	{
		InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Reset()
	{
		InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetAsTemplateDefault()
	{
		InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long get_Color()
	{
		long result;
		InvokeHelper(0x9f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Color(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x9f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_BoldBi()
	{
		long result;
		InvokeHelper(0xa0, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_BoldBi(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ItalicBi()
	{
		long result;
		InvokeHelper(0xa1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ItalicBi(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_SizeBi()
	{
		float result;
		InvokeHelper(0xa2, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_SizeBi(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0xa2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_NameBi()
	{
		CString result;
		InvokeHelper(0xa3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_NameBi(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xa3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ColorIndexBi()
	{
		long result;
		InvokeHelper(0xa4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ColorIndexBi(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_DiacriticColor()
	{
		long result;
		InvokeHelper(0xa5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_DiacriticColor(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_UnderlineColor()
	{
		long result;
		InvokeHelper(0xa6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_UnderlineColor(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}

	// _Font properties
public:

};
// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

class CRange : public COleDispatchDriver
{
public:
	CRange(){} // Calls COleDispatchDriver default constructor
	CRange(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CRange(const CRange& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// Range methods
public:
	CString get_Text()
	{
		CString result;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Text(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_FormattedText()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_FormattedText(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Start()
	{
		long result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Start(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_End()
	{
		long result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_End(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Font()
	{
		LPDISPATCH result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_Font(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Duplicate()
	{
		LPDISPATCH result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_StoryType()
	{
		long result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Tables()
	{
		LPDISPATCH result;
		InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Words()
	{
		LPDISPATCH result;
		InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Sentences()
	{
		LPDISPATCH result;
		InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Characters()
	{
		LPDISPATCH result;
		InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Footnotes()
	{
		LPDISPATCH result;
		InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Endnotes()
	{
		LPDISPATCH result;
		InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Comments()
	{
		LPDISPATCH result;
		InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Cells()
	{
		LPDISPATCH result;
		InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Sections()
	{
		LPDISPATCH result;
		InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Paragraphs()
	{
		LPDISPATCH result;
		InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Borders()
	{
		LPDISPATCH result;
		InvokeHelper(0x44c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_Borders(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x44c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Shading()
	{
		LPDISPATCH result;
		InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_TextRetrievalMode()
	{
		LPDISPATCH result;
		InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_TextRetrievalMode(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x3e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Fields()
	{
		LPDISPATCH result;
		InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_FormFields()
	{
		LPDISPATCH result;
		InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Frames()
	{
		LPDISPATCH result;
		InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ParagraphFormat()
	{
		LPDISPATCH result;
		InvokeHelper(0x44e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_ParagraphFormat(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x44e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_ListFormat()
	{
		LPDISPATCH result;
		InvokeHelper(0x44, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Bookmarks()
	{
		LPDISPATCH result;
		InvokeHelper(0x4b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Application()
	{
		LPDISPATCH result;
		InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Creator()
	{
		long result;
		InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Parent()
	{
		LPDISPATCH result;
		InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Bold()
	{
		long result;
		InvokeHelper(0x82, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Bold(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x82, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Italic()
	{
		long result;
		InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Italic(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x83, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Underline()
	{
		long result;
		InvokeHelper(0x8b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Underline(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_EmphasisMark()
	{
		long result;
		InvokeHelper(0x8c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_EmphasisMark(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_DisableCharacterSpaceGrid()
	{
		BOOL result;
		InvokeHelper(0x8d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_DisableCharacterSpaceGrid(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x8d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Revisions()
	{
		LPDISPATCH result;
		InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	VARIANT get_Style()
	{
		VARIANT result;
		InvokeHelper(0x97, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_Style(VARIANT * newValue)
	{
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x97, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_StoryLength()
	{
		long result;
		InvokeHelper(0x98, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_LanguageID()
	{
		long result;
		InvokeHelper(0x99, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_LanguageID(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x99, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_SynonymInfo()
	{
		LPDISPATCH result;
		InvokeHelper(0x9b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Hyperlinks()
	{
		LPDISPATCH result;
		InvokeHelper(0x9c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ListParagraphs()
	{
		LPDISPATCH result;
		InvokeHelper(0x9d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Subdocuments()
	{
		LPDISPATCH result;
		InvokeHelper(0x9f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_GrammarChecked()
	{
		BOOL result;
		InvokeHelper(0x104, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_GrammarChecked(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x104, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_SpellingChecked()
	{
		BOOL result;
		InvokeHelper(0x105, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_SpellingChecked(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x105, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_HighlightColorIndex()
	{
		long result;
		InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_HighlightColorIndex(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Columns()
	{
		LPDISPATCH result;
		InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Rows()
	{
		LPDISPATCH result;
		InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_CanEdit()
	{
		long result;
		InvokeHelper(0x130, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_CanPaste()
	{
		long result;
		InvokeHelper(0x131, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL get_IsEndOfRowMark()
	{
		BOOL result;
		InvokeHelper(0x133, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	long get_BookmarkID()
	{
		long result;
		InvokeHelper(0x134, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_PreviousBookmarkID()
	{
		long result;
		InvokeHelper(0x135, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Find()
	{
		LPDISPATCH result;
		InvokeHelper(0x106, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_PageSetup()
	{
		LPDISPATCH result;
		InvokeHelper(0x44d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void put_PageSetup(LPDISPATCH newValue)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x44d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_ShapeRange()
	{
		LPDISPATCH result;
		InvokeHelper(0x137, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Case()
	{
		long result;
		InvokeHelper(0x138, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Case(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x138, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	VARIANT get_Information(long Type)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x139, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, Type);
		return result;
	}
	LPDISPATCH get_ReadabilityStatistics()
	{
		LPDISPATCH result;
		InvokeHelper(0x13a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_GrammaticalErrors()
	{
		LPDISPATCH result;
		InvokeHelper(0x13b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_SpellingErrors()
	{
		LPDISPATCH result;
		InvokeHelper(0x13c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Orientation()
	{
		long result;
		InvokeHelper(0x13d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Orientation(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x13d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_InlineShapes()
	{
		LPDISPATCH result;
		InvokeHelper(0x13f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_NextStoryRange()
	{
		LPDISPATCH result;
		InvokeHelper(0x140, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_LanguageIDFarEast()
	{
		long result;
		InvokeHelper(0x141, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_LanguageIDFarEast(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x141, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_LanguageIDOther()
	{
		long result;
		InvokeHelper(0x142, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_LanguageIDOther(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x142, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void Select()
	{
		InvokeHelper(0xffff, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetRange(long Start, long End)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Start, End);
	}
	void Collapse(VARIANT * Direction)
	{
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x65, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Direction);
	}
	void InsertBefore(LPCTSTR Text)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Text);
	}
	void InsertAfter(LPCTSTR Text)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x68, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Text);
	}
	LPDISPATCH Next(VARIANT * Unit, VARIANT * Count)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x69, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Unit, Count);
		return result;
	}
	LPDISPATCH Previous(VARIANT * Unit, VARIANT * Count)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x6a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Unit, Count);
		return result;
	}
	long StartOf(VARIANT * Unit, VARIANT * Extend)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x6b, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Unit, Extend);
		return result;
	}
	long EndOf(VARIANT * Unit, VARIANT * Extend)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x6c, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Unit, Extend);
		return result;
	}
	long Move(VARIANT * Unit, VARIANT * Count)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x6d, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Unit, Count);
		return result;
	}
	long MoveStart(VARIANT * Unit, VARIANT * Count)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x6e, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Unit, Count);
		return result;
	}
	long MoveEnd(VARIANT * Unit, VARIANT * Count)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x6f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Unit, Count);
		return result;
	}
	long MoveWhile(VARIANT * Cset, VARIANT * Count)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x70, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Cset, Count);
		return result;
	}
	long MoveStartWhile(VARIANT * Cset, VARIANT * Count)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x71, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Cset, Count);
		return result;
	}
	long MoveEndWhile(VARIANT * Cset, VARIANT * Count)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x72, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Cset, Count);
		return result;
	}
	long MoveUntil(VARIANT * Cset, VARIANT * Count)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x73, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Cset, Count);
		return result;
	}
	long MoveStartUntil(VARIANT * Cset, VARIANT * Count)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x74, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Cset, Count);
		return result;
	}
	long MoveEndUntil(VARIANT * Cset, VARIANT * Count)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x75, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Cset, Count);
		return result;
	}
	void Cut()
	{
		InvokeHelper(0x77, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Copy()
	{
		InvokeHelper(0x78, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Paste()
	{
		InvokeHelper(0x79, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InsertBreak(VARIANT * Type)
	{
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x7a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type);
	}
	void InsertFile(LPCTSTR FileName, VARIANT * Range, VARIANT * ConfirmConversions, VARIANT * Link, VARIANT * Attachment)
	{
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x7b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FileName, Range, ConfirmConversions, Link, Attachment);
	}
	BOOL InStory(LPDISPATCH Range)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x7d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Range);
		return result;
	}
	BOOL InRange(LPDISPATCH Range)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x7e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Range);
		return result;
	}
	long Delete(VARIANT * Unit, VARIANT * Count)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x7f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Unit, Count);
		return result;
	}
	void WholeStory()
	{
		InvokeHelper(0x80, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long Expand(VARIANT * Unit)
	{
		long result;
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x81, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Unit);
		return result;
	}
	void InsertParagraph()
	{
		InvokeHelper(0xa0, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InsertParagraphAfter()
	{
		InvokeHelper(0xa1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH ConvertToTableOld(VARIANT * Separator, VARIANT * NumRows, VARIANT * NumColumns, VARIANT * InitialColumnWidth, VARIANT * Format, VARIANT * ApplyBorders, VARIANT * ApplyShading, VARIANT * ApplyFont, VARIANT * ApplyColor, VARIANT * ApplyHeadingRows, VARIANT * ApplyLastRow, VARIANT * ApplyFirstColumn, VARIANT * ApplyLastColumn, VARIANT * AutoFit)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xa2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Separator, NumRows, NumColumns, InitialColumnWidth, Format, ApplyBorders, ApplyShading, ApplyFont, ApplyColor, ApplyHeadingRows, ApplyLastRow, ApplyFirstColumn, ApplyLastColumn, AutoFit);
		return result;
	}
	void InsertDateTimeOld(VARIANT * DateTimeFormat, VARIANT * InsertAsField, VARIANT * InsertAsFullWidth)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xa3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DateTimeFormat, InsertAsField, InsertAsFullWidth);
	}
	void InsertSymbol(long CharacterNumber, VARIANT * Font, VARIANT * Unicode, VARIANT * Bias)
	{
		static BYTE parms[] = VTS_I4 VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xa4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CharacterNumber, Font, Unicode, Bias);
	}
	void InsertCrossReference_2002(VARIANT * ReferenceType, long ReferenceKind, VARIANT * ReferenceItem, VARIANT * InsertAsHyperlink, VARIANT * IncludePosition)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_I4 VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xa5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ReferenceType, ReferenceKind, ReferenceItem, InsertAsHyperlink, IncludePosition);
	}
	void InsertCaptionXP(VARIANT * Label, VARIANT * Title, VARIANT * TitleAutoText, VARIANT * Position)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xa6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Label, Title, TitleAutoText, Position);
	}
	void CopyAsPicture()
	{
		InvokeHelper(0xa7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SortOld(VARIANT * ExcludeHeader, VARIANT * FieldNumber, VARIANT * SortFieldType, VARIANT * SortOrder, VARIANT * FieldNumber2, VARIANT * SortFieldType2, VARIANT * SortOrder2, VARIANT * FieldNumber3, VARIANT * SortFieldType3, VARIANT * SortOrder3, VARIANT * SortColumn, VARIANT * Separator, VARIANT * CaseSensitive, VARIANT * LanguageID)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xa8, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ExcludeHeader, FieldNumber, SortFieldType, SortOrder, FieldNumber2, SortFieldType2, SortOrder2, FieldNumber3, SortFieldType3, SortOrder3, SortColumn, Separator, CaseSensitive, LanguageID);
	}
	void SortAscending()
	{
		InvokeHelper(0xa9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SortDescending()
	{
		InvokeHelper(0xaa, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL IsEqual(LPDISPATCH Range)
	{
		BOOL result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0xab, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, Range);
		return result;
	}
	float Calculate()
	{
		float result;
		InvokeHelper(0xac, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GoTo(VARIANT * What, VARIANT * Which, VARIANT * Count, VARIANT * Name)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xad, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, What, Which, Count, Name);
		return result;
	}
	LPDISPATCH GoToNext(long What)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xae, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, What);
		return result;
	}
	LPDISPATCH GoToPrevious(long What)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xaf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, What);
		return result;
	}
	void PasteSpecial(VARIANT * IconIndex, VARIANT * Link, VARIANT * Placement, VARIANT * DisplayAsIcon, VARIANT * DataType, VARIANT * IconFileName, VARIANT * IconLabel)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xb0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, IconIndex, Link, Placement, DisplayAsIcon, DataType, IconFileName, IconLabel);
	}
	void LookupNameProperties()
	{
		InvokeHelper(0xb1, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long ComputeStatistics(long Statistic)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xb2, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Statistic);
		return result;
	}
	void Relocate(long Direction)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xb3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Direction);
	}
	void CheckSynonyms()
	{
		InvokeHelper(0xb4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SubscribeTo(LPCTSTR Edition, VARIANT * Format)
	{
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT ;
		InvokeHelper(0xb5, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Edition, Format);
	}
	void CreatePublisher(VARIANT * Edition, VARIANT * ContainsPICT, VARIANT * ContainsRTF, VARIANT * ContainsText)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xb6, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Edition, ContainsPICT, ContainsRTF, ContainsText);
	}
	void InsertAutoText()
	{
		InvokeHelper(0xb7, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InsertDatabase(VARIANT * Format, VARIANT * Style, VARIANT * LinkToSource, VARIANT * Connection, VARIANT * SQLStatement, VARIANT * SQLStatement1, VARIANT * PasswordDocument, VARIANT * PasswordTemplate, VARIANT * WritePasswordDocument, VARIANT * WritePasswordTemplate, VARIANT * DataSource, VARIANT * From, VARIANT * To, VARIANT * IncludeFields)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xc2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Format, Style, LinkToSource, Connection, SQLStatement, SQLStatement1, PasswordDocument, PasswordTemplate, WritePasswordDocument, WritePasswordTemplate, DataSource, From, To, IncludeFields);
	}
	void AutoFormat()
	{
		InvokeHelper(0xc3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CheckGrammar()
	{
		InvokeHelper(0xcc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CheckSpelling(VARIANT * CustomDictionary, VARIANT * IgnoreUppercase, VARIANT * AlwaysSuggest, VARIANT * CustomDictionary2, VARIANT * CustomDictionary3, VARIANT * CustomDictionary4, VARIANT * CustomDictionary5, VARIANT * CustomDictionary6, VARIANT * CustomDictionary7, VARIANT * CustomDictionary8, VARIANT * CustomDictionary9, VARIANT * CustomDictionary10)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xcd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, CustomDictionary, IgnoreUppercase, AlwaysSuggest, CustomDictionary2, CustomDictionary3, CustomDictionary4, CustomDictionary5, CustomDictionary6, CustomDictionary7, CustomDictionary8, CustomDictionary9, CustomDictionary10);
	}
	LPDISPATCH GetSpellingSuggestions(VARIANT * CustomDictionary, VARIANT * IgnoreUppercase, VARIANT * MainDictionary, VARIANT * SuggestionMode, VARIANT * CustomDictionary2, VARIANT * CustomDictionary3, VARIANT * CustomDictionary4, VARIANT * CustomDictionary5, VARIANT * CustomDictionary6, VARIANT * CustomDictionary7, VARIANT * CustomDictionary8, VARIANT * CustomDictionary9, VARIANT * CustomDictionary10)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xd1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, CustomDictionary, IgnoreUppercase, MainDictionary, SuggestionMode, CustomDictionary2, CustomDictionary3, CustomDictionary4, CustomDictionary5, CustomDictionary6, CustomDictionary7, CustomDictionary8, CustomDictionary9, CustomDictionary10);
		return result;
	}
	void InsertParagraphBefore()
	{
		InvokeHelper(0xd4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void NextSubdocument()
	{
		InvokeHelper(0xdb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PreviousSubdocument()
	{
		InvokeHelper(0xdc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ConvertHangulAndHanja(VARIANT * ConversionsMode, VARIANT * FastConversion, VARIANT * CheckHangulEnding, VARIANT * EnableRecentOrdering, VARIANT * CustomDictionary)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xdd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ConversionsMode, FastConversion, CheckHangulEnding, EnableRecentOrdering, CustomDictionary);
	}
	void PasteAsNestedTable()
	{
		InvokeHelper(0xde, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ModifyEnclosure(VARIANT * Style, VARIANT * Symbol, VARIANT * EnclosedText)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0xdf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Style, Symbol, EnclosedText);
	}
	void PhoneticGuide(LPCTSTR Text, long Alignment, long Raise, long FontSize, LPCTSTR FontName)
	{
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_BSTR ;
		InvokeHelper(0xe0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Text, Alignment, Raise, FontSize, FontName);
	}
	void InsertDateTime(VARIANT * DateTimeFormat, VARIANT * InsertAsField, VARIANT * InsertAsFullWidth, VARIANT * DateLanguage, VARIANT * CalendarType)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x1bc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DateTimeFormat, InsertAsField, InsertAsFullWidth, DateLanguage, CalendarType);
	}
	void Sort(VARIANT * ExcludeHeader, VARIANT * FieldNumber, VARIANT * SortFieldType, VARIANT * SortOrder, VARIANT * FieldNumber2, VARIANT * SortFieldType2, VARIANT * SortOrder2, VARIANT * FieldNumber3, VARIANT * SortFieldType3, VARIANT * SortOrder3, VARIANT * SortColumn, VARIANT * Separator, VARIANT * CaseSensitive, VARIANT * BidiSort, VARIANT * IgnoreThe, VARIANT * IgnoreKashida, VARIANT * IgnoreDiacritics, VARIANT * IgnoreHe, VARIANT * LanguageID)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x1e4, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ExcludeHeader, FieldNumber, SortFieldType, SortOrder, FieldNumber2, SortFieldType2, SortOrder2, FieldNumber3, SortFieldType3, SortOrder3, SortColumn, Separator, CaseSensitive, BidiSort, IgnoreThe, IgnoreKashida, IgnoreDiacritics, IgnoreHe, LanguageID);
	}
	void DetectLanguage()
	{
		InvokeHelper(0xcb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH ConvertToTable(VARIANT * Separator, VARIANT * NumRows, VARIANT * NumColumns, VARIANT * InitialColumnWidth, VARIANT * Format, VARIANT * ApplyBorders, VARIANT * ApplyShading, VARIANT * ApplyFont, VARIANT * ApplyColor, VARIANT * ApplyHeadingRows, VARIANT * ApplyLastRow, VARIANT * ApplyFirstColumn, VARIANT * ApplyLastColumn, VARIANT * AutoFit, VARIANT * AutoFitBehavior, VARIANT * DefaultTableBehavior)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x1f2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Separator, NumRows, NumColumns, InitialColumnWidth, Format, ApplyBorders, ApplyShading, ApplyFont, ApplyColor, ApplyHeadingRows, ApplyLastRow, ApplyFirstColumn, ApplyLastColumn, AutoFit, AutoFitBehavior, DefaultTableBehavior);
		return result;
	}
	void TCSCConverter(long WdTCSCConverterDirection, BOOL CommonTerms, BOOL UseVariants)
	{
		static BYTE parms[] = VTS_I4 VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x1f3, DISPATCH_METHOD, VT_EMPTY, NULL, parms, WdTCSCConverterDirection, CommonTerms, UseVariants);
	}
	BOOL get_LanguageDetected()
	{
		BOOL result;
		InvokeHelper(0x107, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_LanguageDetected(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x107, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_FitTextWidth()
	{
		float result;
		InvokeHelper(0x108, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_FitTextWidth(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x108, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_HorizontalInVertical()
	{
		long result;
		InvokeHelper(0x109, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_HorizontalInVertical(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x109, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_TwoLinesInOne()
	{
		long result;
		InvokeHelper(0x10a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_TwoLinesInOne(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x10a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_CombineCharacters()
	{
		BOOL result;
		InvokeHelper(0x10b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_CombineCharacters(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x10b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_NoProofing()
	{
		long result;
		InvokeHelper(0x143, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_NoProofing(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x143, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_TopLevelTables()
	{
		LPDISPATCH result;
		InvokeHelper(0x144, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Scripts()
	{
		LPDISPATCH result;
		InvokeHelper(0x145, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_CharacterWidth()
	{
		long result;
		InvokeHelper(0x146, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_CharacterWidth(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x146, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Kana()
	{
		long result;
		InvokeHelper(0x147, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Kana(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x147, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_BoldBi()
	{
		long result;
		InvokeHelper(0x190, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_BoldBi(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x190, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ItalicBi()
	{
		long result;
		InvokeHelper(0x191, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ItalicBi(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x191, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_ID()
	{
		CString result;
		InvokeHelper(0x195, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_ID(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x195, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_HTMLDivisions()
	{
		LPDISPATCH result;
		InvokeHelper(0x196, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_SmartTags()
	{
		LPDISPATCH result;
		InvokeHelper(0x197, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_ShowAll()
	{
		BOOL result;
		InvokeHelper(0x198, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_ShowAll(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x198, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Document()
	{
		LPDISPATCH result;
		InvokeHelper(0x199, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_FootnoteOptions()
	{
		LPDISPATCH result;
		InvokeHelper(0x19a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_EndnoteOptions()
	{
		LPDISPATCH result;
		InvokeHelper(0x19b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void PasteAndFormat(long Type)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x19c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Type);
	}
	void PasteExcelTable(BOOL LinkedToExcel, BOOL WordFormatting, BOOL RTF)
	{
		static BYTE parms[] = VTS_BOOL VTS_BOOL VTS_BOOL ;
		InvokeHelper(0x19d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, LinkedToExcel, WordFormatting, RTF);
	}
	void PasteAppendTable()
	{
		InvokeHelper(0x19e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH get_XMLNodes()
	{
		LPDISPATCH result;
		InvokeHelper(0x154, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_XMLParentNode()
	{
		LPDISPATCH result;
		InvokeHelper(0x155, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Editors()
	{
		LPDISPATCH result;
		InvokeHelper(0x157, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_XML(BOOL DataOnly)
	{
		CString result;
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x158, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, DataOnly);
		return result;
	}
	VARIANT get_EnhMetaFileBits()
	{
		VARIANT result;
		InvokeHelper(0x159, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GoToEditableRange(VARIANT * EditorID)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_PVARIANT ;
		InvokeHelper(0x19f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, EditorID);
		return result;
	}
	void InsertXML(LPCTSTR XML, VARIANT * Transform)
	{
		static BYTE parms[] = VTS_BSTR VTS_PVARIANT ;
		InvokeHelper(0x1a0, DISPATCH_METHOD, VT_EMPTY, NULL, parms, XML, Transform);
	}
	void InsertCaption(VARIANT * Label, VARIANT * Title, VARIANT * TitleAutoText, VARIANT * Position, VARIANT * ExcludeLabel)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x1a1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Label, Title, TitleAutoText, Position, ExcludeLabel);
	}
	void InsertCrossReference(VARIANT * ReferenceType, long ReferenceKind, VARIANT * ReferenceItem, VARIANT * InsertAsHyperlink, VARIANT * IncludePosition, VARIANT * SeparateNumbers, VARIANT * SeparatorString)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_I4 VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x1a2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ReferenceType, ReferenceKind, ReferenceItem, InsertAsHyperlink, IncludePosition, SeparateNumbers, SeparatorString);
	}

	// Range properties
public:

};
////////new 
class CWordWindow : public COleDispatchDriver
{
public:
	CWordWindow(){} // Calls COleDispatchDriver default constructor
	CWordWindow(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWordWindow(const CWordWindow& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// Window methods
public:
	LPDISPATCH get_Application()
	{
		LPDISPATCH result;
		InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Creator()
	{
		long result;
		InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Parent()
	{
		LPDISPATCH result;
		InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_ActivePane()
	{
		LPDISPATCH result;
		InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Document()
	{
		LPDISPATCH result;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Panes()
	{
		LPDISPATCH result;
		InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Selection()
	{
		LPDISPATCH result;
		InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Left()
	{
		long result;
		InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Left(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Top()
	{
		long result;
		InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Top(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Width()
	{
		long result;
		InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Width(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Height()
	{
		long result;
		InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Height(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Split()
	{
		BOOL result;
		InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Split(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SplitVertical()
	{
		long result;
		InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SplitVertical(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_Caption()
	{
		CString result;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Caption(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_WindowState()
	{
		long result;
		InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_WindowState(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_DisplayRulers()
	{
		BOOL result;
		InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_DisplayRulers(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_DisplayVerticalRuler()
	{
		BOOL result;
		InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_DisplayVerticalRuler(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_View()
	{
		LPDISPATCH result;
		InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Type()
	{
		long result;
		InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Next()
	{
		LPDISPATCH result;
		InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Previous()
	{
		LPDISPATCH result;
		InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_WindowNumber()
	{
		long result;
		InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL get_DisplayVerticalScrollBar()
	{
		BOOL result;
		InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_DisplayVerticalScrollBar(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_DisplayHorizontalScrollBar()
	{
		BOOL result;
		InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_DisplayHorizontalScrollBar(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_StyleAreaWidth()
	{
		float result;
		InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_StyleAreaWidth(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_DisplayScreenTips()
	{
		BOOL result;
		InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_DisplayScreenTips(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_HorizontalPercentScrolled()
	{
		long result;
		InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_HorizontalPercentScrolled(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_VerticalPercentScrolled()
	{
		long result;
		InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_VerticalPercentScrolled(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_DocumentMap()
	{
		BOOL result;
		InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_DocumentMap(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Active()
	{
		BOOL result;
		InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	long get_DocumentMapPercentWidth()
	{
		long result;
		InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_DocumentMapPercentWidth(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Index()
	{
		long result;
		InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_IMEMode()
	{
		long result;
		InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_IMEMode(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void Activate()
	{
		InvokeHelper(0x64, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Close(VARIANT * SaveChanges, VARIANT * RouteDocument)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x66, DISPATCH_METHOD, VT_EMPTY, NULL, parms, SaveChanges, RouteDocument);
	}
	void LargeScroll(VARIANT * Down, VARIANT * Up, VARIANT * ToRight, VARIANT * ToLeft)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x67, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Down, Up, ToRight, ToLeft);
	}
	void SmallScroll(VARIANT * Down, VARIANT * Up, VARIANT * ToRight, VARIANT * ToLeft)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x68, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Down, Up, ToRight, ToLeft);
	}
	LPDISPATCH NewWindow()
	{
		LPDISPATCH result;
		InvokeHelper(0x69, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void PrintOutOld(VARIANT * Background, VARIANT * Append, VARIANT * Range, VARIANT * OutputFileName, VARIANT * From, VARIANT * To, VARIANT * Item, VARIANT * Copies, VARIANT * Pages, VARIANT * PageType, VARIANT * PrintToFile, VARIANT * Collate, VARIANT * ActivePrinterMacGX, VARIANT * ManualDuplexPrint)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x6b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Background, Append, Range, OutputFileName, From, To, Item, Copies, Pages, PageType, PrintToFile, Collate, ActivePrinterMacGX, ManualDuplexPrint);
	}
	void PageScroll(VARIANT * Down, VARIANT * Up)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x6c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Down, Up);
	}
	void SetFocus()
	{
		InvokeHelper(0x6d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH RangeFromPoint(long x, long y)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x6e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, x, y);
		return result;
	}
	void ScrollIntoView(LPDISPATCH obj, VARIANT * Start)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_PVARIANT ;
		InvokeHelper(0x6f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, obj, Start);
	}
	void GetPoint(long * ScreenPixelsLeft, long * ScreenPixelsTop, long * ScreenPixelsWidth, long * ScreenPixelsHeight, LPDISPATCH obj)
	{
		static BYTE parms[] = VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_DISPATCH ;
		InvokeHelper(0x70, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ScreenPixelsLeft, ScreenPixelsTop, ScreenPixelsWidth, ScreenPixelsHeight, obj);
	}
	void PrintOut2000(VARIANT * Background, VARIANT * Append, VARIANT * Range, VARIANT * OutputFileName, VARIANT * From, VARIANT * To, VARIANT * Item, VARIANT * Copies, VARIANT * Pages, VARIANT * PageType, VARIANT * PrintToFile, VARIANT * Collate, VARIANT * ActivePrinterMacGX, VARIANT * ManualDuplexPrint, VARIANT * PrintZoomColumn, VARIANT * PrintZoomRow, VARIANT * PrintZoomPaperWidth, VARIANT * PrintZoomPaperHeight)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x1bc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Background, Append, Range, OutputFileName, From, To, Item, Copies, Pages, PageType, PrintToFile, Collate, ActivePrinterMacGX, ManualDuplexPrint, PrintZoomColumn, PrintZoomRow, PrintZoomPaperWidth, PrintZoomPaperHeight);
	}
	long get_UsableWidth()
	{
		long result;
		InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_UsableHeight()
	{
		long result;
		InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL get_EnvelopeVisible()
	{
		BOOL result;
		InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_EnvelopeVisible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_DisplayRightRuler()
	{
		BOOL result;
		InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_DisplayRightRuler(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_DisplayLeftScrollBar()
	{
		BOOL result;
		InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_DisplayLeftScrollBar(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Visible()
	{
		BOOL result;
		InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Visible(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x24, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void PrintOut(VARIANT * Background, VARIANT * Append, VARIANT * Range, VARIANT * OutputFileName, VARIANT * From, VARIANT * To, VARIANT * Item, VARIANT * Copies, VARIANT * Pages, VARIANT * PageType, VARIANT * PrintToFile, VARIANT * Collate, VARIANT * ActivePrinterMacGX, VARIANT * ManualDuplexPrint, VARIANT * PrintZoomColumn, VARIANT * PrintZoomRow, VARIANT * PrintZoomPaperWidth, VARIANT * PrintZoomPaperHeight)
	{
		static BYTE parms[] = VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT ;
		InvokeHelper(0x1bd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Background, Append, Range, OutputFileName, From, To, Item, Copies, Pages, PageType, PrintToFile, Collate, ActivePrinterMacGX, ManualDuplexPrint, PrintZoomColumn, PrintZoomRow, PrintZoomPaperWidth, PrintZoomPaperHeight);
	}
	void ToggleShowAllReviewers()
	{
		InvokeHelper(0x1be, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL get_Thumbnails()
	{
		BOOL result;
		InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Thumbnails(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x25, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}

	// Window properties
public:

};
