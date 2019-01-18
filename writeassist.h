UINT GetWordHint_New(LPCSTR lpInStr, char * lpOutStrs[128], UINT iMaxCount);

UINT GetPhraseHint_New(LPCSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount);

UINT GetSentenceHint_New(LPCSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount);//获取句子提示，输入，输出 UINT CCompWindow::UpdateDicBuf()一次调用

UINT GetPhraseHint_Structure(LPCSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount);//根据用户的输入，给出可能的结构提示。

UINT GetPhraseHint_Fluent(LPCSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount);//输入是一个英文句子，输出若干个意思相同或者相近更地道的句子

UINT GetPhraseHint_Translate(LPCSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount);//输入是一个中文句子，输出若干个与之匹配的英文句子，及翻译

