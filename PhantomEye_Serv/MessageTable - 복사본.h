// MessageTable.h : CMessageTable�� �����Դϴ�.

#pragma once

// �ڵ� ���� ��ġ 2012�� 12�� 6�� �����, ���� 3:49

class CMessageTableAccessor
{
public:
	TCHAR m_NTIME[27];
	TCHAR m_NIP[31];
	LONG m_NPORT;
	LONG m_NDELAY;
	// ISequentialStream* m_NPROCNAME;
	TCHAR m_NPROCNAME[8000];

	// ���� ������ ���� ������ �������  �� ���� �ش� 
	// �ʵ忡 ���� ���� ���� ��� �ֽ��ϴ�. �� ����
	// ����Ͽ� �����ͺ��̽�������ȯ�ϴ� NULL ����
	// �����ϰų� �����Ϸ����� ������ ��ȯ�� ��
	// ���� ������ ������ �� �ֽ��ϴ�. �̷��� �ʵ� ��뿡
	// ���� �ڼ��� ������ Visual C++ ������
	//  "������ ���� ������"���� "�ʵ� ���� ������ ���"�� �����Ͻʽÿ�.
	// ����: �����͸� ����/�����ϱ� ���� �̵� �ʵ带 �ʱ�ȭ�ؾ� �մϴ�.

	DBSTATUS m_dwNTIMEStatus;
	DBSTATUS m_dwNIPStatus;
	DBSTATUS m_dwNPORTStatus;
	DBSTATUS m_dwNDELAYStatus;
	DBSTATUS m_dwNPROCNAMEStatus;

	// ���� ������ ���� ������ ������� �� ���� �ش� �ʵ忡 ����
	// ���� ���� ��� �ֽ��ϴ�.
	// ����: ���� ���� ���� ��� �����͸� ����/�����ϱ� ���� 
//       �̷��� 	 �ʵ带 �ʱ�ȭ�ؾ� �մϴ�.

	DBLENGTH m_dwNTIMELength;
	DBLENGTH m_dwNIPLength;
	DBLENGTH m_dwNPORTLength;
	DBLENGTH m_dwNDELAYLength;
	DBLENGTH m_dwNPROCNAMELength;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		// pPropSet->AddProperty(DBPROP_ISequentialStream, true);
	}

	HRESULT OpenDataSource()
	{
		CDataSource _db;
		HRESULT hr;
//#error ���� ����: ���� ���ڿ��� ��ȣ�� ���ԵǾ� ���� �� �ֽ��ϴ�.
// �Ʒ� ���� ���ڿ��� �Ϲ� �ؽ�Ʈ ��ȣ ��/�Ǵ� 
// �ٸ� �߿��� ������ ���ԵǾ� ���� �� �ֽ��ϴ�.
// ���� ���� ������ �ִ��� ���� ���ڿ��� ������ �Ŀ� #error��(��) �����Ͻʽÿ�.
// �ٸ� �������� ��ȣ�� �����ϰų� �ٸ� ����� ������ ����Ͻʽÿ�.
		hr = _db.OpenFromInitializationString(L"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=DB_PhantomEye;Data Source=BP_MIKAARIEL-PC\\MIKAARIEL_DB;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=BP_MIKAARIEL-PC;Use Encryption for Data=False;Tag with column collation when possible=False");
		if (FAILED(hr))
		{
#ifdef _DEBUG
			AtlTraceErrorRecords(hr);
#endif
			return hr;
		}
		return m_session.Open(_db);
	}

	void CloseDataSource()
	{
		m_session.Close();
	}

	operator const CSession&()
	{
		return m_session;
	}

	CSession m_session;

	DEFINE_COMMAND_EX(CMessageTableAccessor, L" \
	SELECT \
		NTIME, \
		NIP, \
		NPORT, \
		NDELAY, \
		NPROCNAME \
		FROM dbo.MessageTable")

// �� ���̺�/��ɿ��� ISequentialStream �������̽��� ����
// �׼����� �� �ִ� ���� ��� �ֽ��ϴ�. �׷��� ��� �����ڰ�
// �� ����� �����ϴ� ���� �ƴϸ� �� ����� �����ϴ� �����ڵ�
// ���� �ϳ��� �� ���տ� �� �ϳ��� ISequentialStream�� �����ϵ��� ������ �޽��ϴ�.
// �� �������� ��Ʈ���� ����Ϸ��� �Ʒ��� ���� �ڵ带 ����ϰ�
// DBPROP_ISequentialStream �� ���� �Ӽ��� true�� �����Ͻʽÿ�.
// �׷��� Read() �޼��带 ����Ͽ� �����͸� �аų�
// Write() �޼��带 ����Ͽ� �����͸� �� �� �ֽ��ϴ�.
// �̷��� �Ϸ��� STGM_READ ��Ʈ�� �Ӽ��� STGM_WRITE �Ǵ� STGM_READWRITE��
// �����ؾ� �մϴ�.
// ISequentialStream ���ε��� ���� �ڼ��� ������ ������ �����Ͻʽÿ�.

	// �Ϻ� �����ڿ� ���õ� ��� �������� �ذ��ϱ� ���� �Ʒ� �ڵ忡���� 
	// �����ڰ� �����ϴ� �Ͱ� �ٸ� ������ ���� ���ε��� �� �ֽ��ϴ�.

	BEGIN_COLUMN_MAP(CMessageTableAccessor)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_NTIME, m_dwNTIMELength, m_dwNTIMEStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_NIP, m_dwNIPLength, m_dwNIPStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_NPORT, m_dwNPORTLength, m_dwNPORTStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_NDELAY, m_dwNDELAYLength, m_dwNDELAYStatus)
		// BLOB_ENTRY_LENGTH_STATUS(5, IID_ISequentialStream, STGM_READ, m_NPROCNAME, m_dwNPROCNAMELength, m_dwNPROCNAMEStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5, m_NPROCNAME, m_dwNPROCNAMELength, m_dwNPROCNAMEStatus)
	END_COLUMN_MAP()
};

class CMessageTableInsertAccessor
{
public:
	TCHAR m_NTIME[27];
	TCHAR m_NIP[31];
	LONG m_NPORT;
	LONG m_NDELAY;
	// ISequentialStream* m_NPROCNAME;
	TCHAR m_NPROCNAME[8000];

	// ���� ������ ���� ������ �������  �� ���� �ش� 
	// �ʵ忡 ���� ���� ���� ��� �ֽ��ϴ�. �� ����
	// ����Ͽ� �����ͺ��̽�������ȯ�ϴ� NULL ����
	// �����ϰų� �����Ϸ����� ������ ��ȯ�� ��
	// ���� ������ ������ �� �ֽ��ϴ�. �̷��� �ʵ� ��뿡
	// ���� �ڼ��� ������ Visual C++ ������
	//  "������ ���� ������"���� "�ʵ� ���� ������ ���"�� �����Ͻʽÿ�.
	// ����: �����͸� ����/�����ϱ� ���� �̵� �ʵ带 �ʱ�ȭ�ؾ� �մϴ�.

	DBSTATUS m_dwNTIMEStatus;
	DBSTATUS m_dwNIPStatus;
	DBSTATUS m_dwNPORTStatus;
	DBSTATUS m_dwNDELAYStatus;
	DBSTATUS m_dwNPROCNAMEStatus;

	// ���� ������ ���� ������ ������� �� ���� �ش� �ʵ忡 ����
	// ���� ���� ��� �ֽ��ϴ�.
	// ����: ���� ���� ���� ��� �����͸� ����/�����ϱ� ���� 
//       �̷��� 	 �ʵ带 �ʱ�ȭ�ؾ� �մϴ�.

	DBLENGTH m_dwNTIMELength;
	DBLENGTH m_dwNIPLength;
	DBLENGTH m_dwNPORTLength;
	DBLENGTH m_dwNDELAYLength;
	DBLENGTH m_dwNPROCNAMELength;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		// pPropSet->AddProperty(DBPROP_ISequentialStream, true);
	}

	HRESULT OpenDataSource()
	{
		CDataSource _db;
		HRESULT hr;
//#error ���� ����: ���� ���ڿ��� ��ȣ�� ���ԵǾ� ���� �� �ֽ��ϴ�.
// �Ʒ� ���� ���ڿ��� �Ϲ� �ؽ�Ʈ ��ȣ ��/�Ǵ� 
// �ٸ� �߿��� ������ ���ԵǾ� ���� �� �ֽ��ϴ�.
// ���� ���� ������ �ִ��� ���� ���ڿ��� ������ �Ŀ� #error��(��) �����Ͻʽÿ�.
// �ٸ� �������� ��ȣ�� �����ϰų� �ٸ� ����� ������ ����Ͻʽÿ�.
		hr = _db.OpenFromInitializationString(L"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=DB_PhantomEye;Data Source=BP_MIKAARIEL-PC\\MIKAARIEL_DB;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=BP_MIKAARIEL-PC;Use Encryption for Data=False;Tag with column collation when possible=False");
		if (FAILED(hr))
		{
#ifdef _DEBUG
			AtlTraceErrorRecords(hr);
#endif
			return hr;
		}
		return m_session.Open(_db);
	}

	void CloseDataSource()
	{
		m_session.Close();
	}

	operator const CSession&()
	{
		return m_session;
	}

	CSession m_session;

	DEFINE_COMMAND_EX(CMessageTableInsertAccessor, L" \
	INSERT INTO MessageTable(NTIME,NIP,NPORT,NDELAY,NPROCNAME) VALUES(?,?,?,?,?)")

// �� ���̺�/��ɿ��� ISequentialStream �������̽��� ����
// �׼����� �� �ִ� ���� ��� �ֽ��ϴ�. �׷��� ��� �����ڰ�
// �� ����� �����ϴ� ���� �ƴϸ� �� ����� �����ϴ� �����ڵ�
// ���� �ϳ��� �� ���տ� �� �ϳ��� ISequentialStream�� �����ϵ��� ������ �޽��ϴ�.
// �� �������� ��Ʈ���� ����Ϸ��� �Ʒ��� ���� �ڵ带 ����ϰ�
// DBPROP_ISequentialStream �� ���� �Ӽ��� true�� �����Ͻʽÿ�.
// �׷��� Read() �޼��带 ����Ͽ� �����͸� �аų�
// Write() �޼��带 ����Ͽ� �����͸� �� �� �ֽ��ϴ�.
// �̷��� �Ϸ��� STGM_READ ��Ʈ�� �Ӽ��� STGM_WRITE �Ǵ� STGM_READWRITE��
// �����ؾ� �մϴ�.
// ISequentialStream ���ε��� ���� �ڼ��� ������ ������ �����Ͻʽÿ�.

	// �Ϻ� �����ڿ� ���õ� ��� �������� �ذ��ϱ� ���� �Ʒ� �ڵ忡���� 
	// �����ڰ� �����ϴ� �Ͱ� �ٸ� ������ ���� ���ε��� �� �ֽ��ϴ�.
	
	BEGIN_PARAM_MAP(CMessageTableInsertAccessor)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_NTIME, m_dwNTIMELength, m_dwNTIMEStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_NIP, m_dwNIPLength, m_dwNIPStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_NPORT, m_dwNPORTLength, m_dwNPORTStatus)
		COLUMN_ENTRY_LENGTH_STATUS(4, m_NDELAY, m_dwNDELAYLength, m_dwNDELAYStatus)
		// BLOB_ENTRY_LENGTH_STATUS(5, IID_ISequentialStream, STGM_READ, m_NPROCNAME, m_dwNPROCNAMELength, m_dwNPROCNAMEStatus)
		COLUMN_ENTRY_LENGTH_STATUS(5, m_NPROCNAME, m_dwNPROCNAMELength, m_dwNPROCNAMEStatus)
	END_PARAM_MAP()
};

class CMessageTableMostValueAccessor
{
public:
	TCHAR m_NTIME[27];
	TCHAR m_NIP[31];
	LONG m_NPORT;
	LONG m_NDELAY;
	// ISequentialStream* m_NPROCNAME;
	TCHAR m_NPROCNAME[8000];

	// ���� ������ ���� ������ �������  �� ���� �ش� 
	// �ʵ忡 ���� ���� ���� ��� �ֽ��ϴ�. �� ����
	// ����Ͽ� �����ͺ��̽�������ȯ�ϴ� NULL ����
	// �����ϰų� �����Ϸ����� ������ ��ȯ�� ��
	// ���� ������ ������ �� �ֽ��ϴ�. �̷��� �ʵ� ��뿡
	// ���� �ڼ��� ������ Visual C++ ������
	//  "������ ���� ������"���� "�ʵ� ���� ������ ���"�� �����Ͻʽÿ�.
	// ����: �����͸� ����/�����ϱ� ���� �̵� �ʵ带 �ʱ�ȭ�ؾ� �մϴ�.

	DBSTATUS m_dwNTIMEStatus;
	DBSTATUS m_dwNIPStatus;
	DBSTATUS m_dwNPORTStatus;
	DBSTATUS m_dwNDELAYStatus;
	DBSTATUS m_dwNPROCNAMEStatus;

	// ���� ������ ���� ������ ������� �� ���� �ش� �ʵ忡 ����
	// ���� ���� ��� �ֽ��ϴ�.
	// ����: ���� ���� ���� ��� �����͸� ����/�����ϱ� ���� 
//       �̷��� 	 �ʵ带 �ʱ�ȭ�ؾ� �մϴ�.

	DBLENGTH m_dwNTIMELength;
	DBLENGTH m_dwNIPLength;
	DBLENGTH m_dwNPORTLength;
	DBLENGTH m_dwNDELAYLength;
	DBLENGTH m_dwNPROCNAMELength;


	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		// pPropSet->AddProperty(DBPROP_ISequentialStream, true);
	}

	HRESULT OpenDataSource()
	{
		CDataSource _db;
		HRESULT hr;
//#error ���� ����: ���� ���ڿ��� ��ȣ�� ���ԵǾ� ���� �� �ֽ��ϴ�.
// �Ʒ� ���� ���ڿ��� �Ϲ� �ؽ�Ʈ ��ȣ ��/�Ǵ� 
// �ٸ� �߿��� ������ ���ԵǾ� ���� �� �ֽ��ϴ�.
// ���� ���� ������ �ִ��� ���� ���ڿ��� ������ �Ŀ� #error��(��) �����Ͻʽÿ�.
// �ٸ� �������� ��ȣ�� �����ϰų� �ٸ� ����� ������ ����Ͻʽÿ�.
		hr = _db.OpenFromInitializationString(L"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=DB_PhantomEye;Data Source=BP_MIKAARIEL-PC\\MIKAARIEL_DB;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=BP_MIKAARIEL-PC;Use Encryption for Data=False;Tag with column collation when possible=False");
		if (FAILED(hr))
		{
#ifdef _DEBUG
			AtlTraceErrorRecords(hr);
#endif
			return hr;
		}
		return m_session.Open(_db);
	}

	void CloseDataSource()
	{
		m_session.Close();
	}

	operator const CSession&()
	{
		return m_session;
	}

	CSession m_session;

	DEFINE_COMMAND_EX(CMessageTableMostValueAccessor, L" \
	SELECT NIP, NPROCNAME, SUM(NDELAY) \
	FROM dbo.MessageTable \
	GROUP by NIP, NPROCNAME \
	ORDER by SUM(NDELAY) desc")

// �� ���̺�/��ɿ��� ISequentialStream �������̽��� ����
// �׼����� �� �ִ� ���� ��� �ֽ��ϴ�. �׷��� ��� �����ڰ�
// �� ����� �����ϴ� ���� �ƴϸ� �� ����� �����ϴ� �����ڵ�
// ���� �ϳ��� �� ���տ� �� �ϳ��� ISequentialStream�� �����ϵ��� ������ �޽��ϴ�.
// �� �������� ��Ʈ���� ����Ϸ��� �Ʒ��� ���� �ڵ带 ����ϰ�
// DBPROP_ISequentialStream �� ���� �Ӽ��� true�� �����Ͻʽÿ�.
// �׷��� Read() �޼��带 ����Ͽ� �����͸� �аų�
// Write() �޼��带 ����Ͽ� �����͸� �� �� �ֽ��ϴ�.
// �̷��� �Ϸ��� STGM_READ ��Ʈ�� �Ӽ��� STGM_WRITE �Ǵ� STGM_READWRITE��
// �����ؾ� �մϴ�.
// ISequentialStream ���ε��� ���� �ڼ��� ������ ������ �����Ͻʽÿ�.

	// �Ϻ� �����ڿ� ���õ� ��� �������� �ذ��ϱ� ���� �Ʒ� �ڵ忡���� 
	// �����ڰ� �����ϴ� �Ͱ� �ٸ� ������ ���� ���ε��� �� �ֽ��ϴ�.

	BEGIN_COLUMN_MAP(CMessageTableMostValueAccessor)
		COLUMN_ENTRY_LENGTH_STATUS(1, m_NIP, m_dwNIPLength, m_dwNIPStatus)
		COLUMN_ENTRY_LENGTH_STATUS(2, m_NPROCNAME, m_dwNPROCNAMELength, m_dwNPROCNAMEStatus)
		COLUMN_ENTRY_LENGTH_STATUS(3, m_NDELAY, m_dwNDELAYLength, m_dwNDELAYStatus)
	END_COLUMN_MAP()
};

class CMessageTableFindValueAccessor
{
public:
	TCHAR m_NTIME[27];
	TCHAR m_NIP[31];
	LONG m_NPORT;
	LONG m_NDELAY;
	// ISequentialStream* m_NPROCNAME;
	TCHAR m_NPROCNAME[8000];
	TCHAR m_NFINDNAME[8000];


	// ���� ������ ���� ������ �������  �� ���� �ش� 
	// �ʵ忡 ���� ���� ���� ��� �ֽ��ϴ�. �� ����
	// ����Ͽ� �����ͺ��̽�������ȯ�ϴ� NULL ����
	// �����ϰų� �����Ϸ����� ������ ��ȯ�� ��
	// ���� ������ ������ �� �ֽ��ϴ�. �̷��� �ʵ� ��뿡
	// ���� �ڼ��� ������ Visual C++ ������
	//  "������ ���� ������"���� "�ʵ� ���� ������ ���"�� �����Ͻʽÿ�.
	// ����: �����͸� ����/�����ϱ� ���� �̵� �ʵ带 �ʱ�ȭ�ؾ� �մϴ�.

	DBSTATUS m_dwNTIMEStatus;
	DBSTATUS m_dwNIPStatus;
	DBSTATUS m_dwNPORTStatus;
	DBSTATUS m_dwNDELAYStatus;
	DBSTATUS m_dwNPROCNAMEStatus;
	DBSTATUS m_dwNFINDNAMEStatus;

	// ���� ������ ���� ������ ������� �� ���� �ش� �ʵ忡 ����
	// ���� ���� ��� �ֽ��ϴ�.
	// ����: ���� ���� ���� ��� �����͸� ����/�����ϱ� ���� 
//       �̷��� 	 �ʵ带 �ʱ�ȭ�ؾ� �մϴ�.

	DBLENGTH m_dwNTIMELength;
	DBLENGTH m_dwNIPLength;
	DBLENGTH m_dwNPORTLength;
	DBLENGTH m_dwNDELAYLength;
	DBLENGTH m_dwNPROCNAMELength;
	DBLENGTH m_dwNFINDNAMELength;

	void GetRowsetProperties(CDBPropSet* pPropSet)
	{
		pPropSet->AddProperty(DBPROP_CANFETCHBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		pPropSet->AddProperty(DBPROP_CANSCROLLBACKWARDS, true, DBPROPOPTIONS_OPTIONAL);
		// pPropSet->AddProperty(DBPROP_ISequentialStream, true);
	}

	HRESULT OpenDataSource()
	{
		CDataSource _db;
		HRESULT hr;
//#error ���� ����: ���� ���ڿ��� ��ȣ�� ���ԵǾ� ���� �� �ֽ��ϴ�.
// �Ʒ� ���� ���ڿ��� �Ϲ� �ؽ�Ʈ ��ȣ ��/�Ǵ� 
// �ٸ� �߿��� ������ ���ԵǾ� ���� �� �ֽ��ϴ�.
// ���� ���� ������ �ִ��� ���� ���ڿ��� ������ �Ŀ� #error��(��) �����Ͻʽÿ�.
// �ٸ� �������� ��ȣ�� �����ϰų� �ٸ� ����� ������ ����Ͻʽÿ�.
		hr = _db.OpenFromInitializationString(L"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=DB_PhantomEye;Data Source=BP_MIKAARIEL-PC\\MIKAARIEL_DB;Use Procedure for Prepare=1;Auto Translate=True;Packet Size=4096;Workstation ID=BP_MIKAARIEL-PC;Use Encryption for Data=False;Tag with column collation when possible=False");
		if (FAILED(hr))
		{
#ifdef _DEBUG
			AtlTraceErrorRecords(hr);
#endif
			return hr;
		}
		return m_session.Open(_db);
	}

	void CloseDataSource()
	{
		m_session.Close();
	}

	operator const CSession&()
	{
		return m_session;
	}

	CSession m_session;

	DEFINE_COMMAND_EX(CMessageTableFindValueAccessor, L" \
	SELECT NIP, NPROCNAME, SUM(NDELAY) \
	FROM dbo.MessageTable \
	WHERE NPROCNAME = VALUES(?)\
	GROUP by NIP, NPROCNAME \
	ORDER by SUM(NDELAY) desc")

// �� ���̺�/��ɿ��� ISequentialStream �������̽��� ����
// �׼����� �� �ִ� ���� ��� �ֽ��ϴ�. �׷��� ��� �����ڰ�
// �� ����� �����ϴ� ���� �ƴϸ� �� ����� �����ϴ� �����ڵ�
// ���� �ϳ��� �� ���տ� �� �ϳ��� ISequentialStream�� �����ϵ��� ������ �޽��ϴ�.
// �� �������� ��Ʈ���� ����Ϸ��� �Ʒ��� ���� �ڵ带 ����ϰ�
// DBPROP_ISequentialStream �� ���� �Ӽ��� true�� �����Ͻʽÿ�.
// �׷��� Read() �޼��带 ����Ͽ� �����͸� �аų�
// Write() �޼��带 ����Ͽ� �����͸� �� �� �ֽ��ϴ�.
// �̷��� �Ϸ��� STGM_READ ��Ʈ�� �Ӽ��� STGM_WRITE �Ǵ� STGM_READWRITE��
// �����ؾ� �մϴ�.
// ISequentialStream ���ε��� ���� �ڼ��� ������ ������ �����Ͻʽÿ�.

// �Ϻ� �����ڿ� ���õ� ��� �������� �ذ��ϱ� ���� �Ʒ� �ڵ忡���� 
// �����ڰ� �����ϴ� �Ͱ� �ٸ� ������ ���� ���ε��� �� �ֽ��ϴ�.

BEGIN_PARAM_MAP(CMessageTableFindValueAccessor)
	SET_PARAM_TYPE(DBPARAMIO_INPUT)
	COLUMN_ENTRY_LENGTH_STATUS(1, m_NFINDNAME, m_dwNFINDNAMELength, m_dwNFINDNAMEStatus)
END_PARAM_MAP()

BEGIN_COLUMN_MAP(CMessageTableFindValueAccessor)
	COLUMN_ENTRY_LENGTH_STATUS(1, m_NIP, m_dwNIPLength, m_dwNIPStatus)
	COLUMN_ENTRY_LENGTH_STATUS(2, m_NPROCNAME, m_dwNPROCNAMELength, m_dwNPROCNAMEStatus)
	COLUMN_ENTRY_LENGTH_STATUS(3, m_NDELAY, m_dwNDELAYLength, m_dwNDELAYStatus)
END_COLUMN_MAP()


};
template <class T>
class CMessageTable : public CCommand<CAccessor<T> >
{
public:
	HRESULT OpenAll()
	{
		HRESULT hr;
		hr = OpenDataSource();
		if (FAILED(hr))
			return hr;
		__if_exists(GetRowsetProperties)
		{
			CDBPropSet propset(DBPROPSET_ROWSET);
			__if_exists(HasBookmark)
			{
				if( HasBookmark() )
					propset.AddProperty(DBPROP_IRowsetLocate, true);
			}
			GetRowsetProperties(&propset);
			return OpenRowset(&propset);
		}
		__if_not_exists(GetRowsetProperties)
		{
			__if_exists(HasBookmark)
			{
				if( HasBookmark() )
				{
					CDBPropSet propset(DBPROPSET_ROWSET);
					propset.AddProperty(DBPROP_IRowsetLocate, true);
					return OpenRowset(&propset);
				}
			}
		}
		return OpenRowset();
	}

	HRESULT OpenRowset(DBPROPSET *pPropSet = NULL)
	{
		HRESULT hr = Open(m_session, NULL, pPropSet);
#ifdef _DEBUG
		if(FAILED(hr))
			AtlTraceErrorRecords(hr);
#endif
		return hr;
	}

	void CloseAll()
	{
		Close();
		ReleaseCommand();
		CloseDataSource();
	}
};


