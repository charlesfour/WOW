UINT GetWordHint_New(LPCSTR lpInStr, char * lpOutStrs[128], UINT iMaxCount);

UINT GetPhraseHint_New(LPCSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount);

UINT GetSentenceHint_New(LPCSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount);//��ȡ������ʾ�����룬��� UINT CCompWindow::UpdateDicBuf()һ�ε���

UINT GetPhraseHint_Structure(LPCSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount);//�����û������룬�������ܵĽṹ��ʾ��

UINT GetPhraseHint_Fluent(LPCSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount);//������һ��Ӣ�ľ��ӣ�������ɸ���˼��ͬ����������ص��ľ���

UINT GetPhraseHint_Translate(LPCSTR lpInStr, LPSTR* lpOutStrs, UINT iMaxCount);//������һ�����ľ��ӣ�������ɸ���֮ƥ���Ӣ�ľ��ӣ�������

