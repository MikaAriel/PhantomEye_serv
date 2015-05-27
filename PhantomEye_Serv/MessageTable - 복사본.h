// MessageTable.h : CMessageTable의 선언입니다.

#pragma once

// 코드 생성 위치 2012년 12월 6일 목요일, 오전 3:49

class CMessageTableAccessor
{
public:
	TCHAR m_NTIME[27];
	TCHAR m_NIP[31];
	LONG m_NPORT;
	LONG m_NDELAY;
	// ISequentialStream* m_NPROCNAME;
	TCHAR m_NPROCNAME[8000];

	// 다음 마법사 생성 데이터 멤버에는  열 맵의 해당 
	// 필드에 대한 상태 값이 들어 있습니다. 이 값을
	// 사용하여 데이터베이스에서반환하는 NULL 값을
	// 보유하거나 컴파일러에서 오류를 반환할 때
	// 오류 정보를 보유할 수 있습니다. 이러한 필드 사용에
	// 대한 자세한 내용은 Visual C++ 설명서의
	//  "마법사 생성 접근자"에서 "필드 상태 데이터 멤버"를 참조하십시오.
	// 참고: 데이터를 설정/삽입하기 전에 이들 필드를 초기화해야 합니다.

	DBSTATUS m_dwNTIMEStatus;
	DBSTATUS m_dwNIPStatus;
	DBSTATUS m_dwNPORTStatus;
	DBSTATUS m_dwNDELAYStatus;
	DBSTATUS m_dwNPROCNAMEStatus;

	// 다음 마법사 생성 데이터 멤버에는 열 맵의 해당 필드에 대한
	// 길이 값이 들어 있습니다.
	// 참고: 가변 길이 열의 경우 데이터를 설정/삽입하기 전에 
//       이러한 	 필드를 초기화해야 합니다.

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
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
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

// 이 테이블/명령에는 ISequentialStream 인터페이스를 통해
// 액세스할 수 있는 열이 들어 있습니다. 그러나 모든 공급자가
// 이 기능을 지원하는 것은 아니며 이 기능을 지원하는 공급자도
// 보통 하나의 행 집합에 단 하나의 ISequentialStream만 지정하도록 제한을 받습니다.
// 이 접근자의 스트림을 사용하려면 아래의 예제 코드를 사용하고
// DBPROP_ISequentialStream 행 집합 속성을 true로 설정하십시오.
// 그러면 Read() 메서드를 사용하여 데이터를 읽거나
// Write() 메서드를 사용하여 데이터를 쓸 수 있습니다.
// 이렇게 하려면 STGM_READ 스트림 속성을 STGM_WRITE 또는 STGM_READWRITE로
// 변경해야 합니다.
// ISequentialStream 바인딩에 대한 자세한 내용은 설명서를 참조하십시오.

	// 일부 공급자와 관련된 몇몇 문제점을 해결하기 위해 아래 코드에서는 
	// 공급자가 보고하는 것과 다른 순서로 열을 바인딩할 수 있습니다.

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

	// 다음 마법사 생성 데이터 멤버에는  열 맵의 해당 
	// 필드에 대한 상태 값이 들어 있습니다. 이 값을
	// 사용하여 데이터베이스에서반환하는 NULL 값을
	// 보유하거나 컴파일러에서 오류를 반환할 때
	// 오류 정보를 보유할 수 있습니다. 이러한 필드 사용에
	// 대한 자세한 내용은 Visual C++ 설명서의
	//  "마법사 생성 접근자"에서 "필드 상태 데이터 멤버"를 참조하십시오.
	// 참고: 데이터를 설정/삽입하기 전에 이들 필드를 초기화해야 합니다.

	DBSTATUS m_dwNTIMEStatus;
	DBSTATUS m_dwNIPStatus;
	DBSTATUS m_dwNPORTStatus;
	DBSTATUS m_dwNDELAYStatus;
	DBSTATUS m_dwNPROCNAMEStatus;

	// 다음 마법사 생성 데이터 멤버에는 열 맵의 해당 필드에 대한
	// 길이 값이 들어 있습니다.
	// 참고: 가변 길이 열의 경우 데이터를 설정/삽입하기 전에 
//       이러한 	 필드를 초기화해야 합니다.

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
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
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

// 이 테이블/명령에는 ISequentialStream 인터페이스를 통해
// 액세스할 수 있는 열이 들어 있습니다. 그러나 모든 공급자가
// 이 기능을 지원하는 것은 아니며 이 기능을 지원하는 공급자도
// 보통 하나의 행 집합에 단 하나의 ISequentialStream만 지정하도록 제한을 받습니다.
// 이 접근자의 스트림을 사용하려면 아래의 예제 코드를 사용하고
// DBPROP_ISequentialStream 행 집합 속성을 true로 설정하십시오.
// 그러면 Read() 메서드를 사용하여 데이터를 읽거나
// Write() 메서드를 사용하여 데이터를 쓸 수 있습니다.
// 이렇게 하려면 STGM_READ 스트림 속성을 STGM_WRITE 또는 STGM_READWRITE로
// 변경해야 합니다.
// ISequentialStream 바인딩에 대한 자세한 내용은 설명서를 참조하십시오.

	// 일부 공급자와 관련된 몇몇 문제점을 해결하기 위해 아래 코드에서는 
	// 공급자가 보고하는 것과 다른 순서로 열을 바인딩할 수 있습니다.
	
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

	// 다음 마법사 생성 데이터 멤버에는  열 맵의 해당 
	// 필드에 대한 상태 값이 들어 있습니다. 이 값을
	// 사용하여 데이터베이스에서반환하는 NULL 값을
	// 보유하거나 컴파일러에서 오류를 반환할 때
	// 오류 정보를 보유할 수 있습니다. 이러한 필드 사용에
	// 대한 자세한 내용은 Visual C++ 설명서의
	//  "마법사 생성 접근자"에서 "필드 상태 데이터 멤버"를 참조하십시오.
	// 참고: 데이터를 설정/삽입하기 전에 이들 필드를 초기화해야 합니다.

	DBSTATUS m_dwNTIMEStatus;
	DBSTATUS m_dwNIPStatus;
	DBSTATUS m_dwNPORTStatus;
	DBSTATUS m_dwNDELAYStatus;
	DBSTATUS m_dwNPROCNAMEStatus;

	// 다음 마법사 생성 데이터 멤버에는 열 맵의 해당 필드에 대한
	// 길이 값이 들어 있습니다.
	// 참고: 가변 길이 열의 경우 데이터를 설정/삽입하기 전에 
//       이러한 	 필드를 초기화해야 합니다.

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
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
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

// 이 테이블/명령에는 ISequentialStream 인터페이스를 통해
// 액세스할 수 있는 열이 들어 있습니다. 그러나 모든 공급자가
// 이 기능을 지원하는 것은 아니며 이 기능을 지원하는 공급자도
// 보통 하나의 행 집합에 단 하나의 ISequentialStream만 지정하도록 제한을 받습니다.
// 이 접근자의 스트림을 사용하려면 아래의 예제 코드를 사용하고
// DBPROP_ISequentialStream 행 집합 속성을 true로 설정하십시오.
// 그러면 Read() 메서드를 사용하여 데이터를 읽거나
// Write() 메서드를 사용하여 데이터를 쓸 수 있습니다.
// 이렇게 하려면 STGM_READ 스트림 속성을 STGM_WRITE 또는 STGM_READWRITE로
// 변경해야 합니다.
// ISequentialStream 바인딩에 대한 자세한 내용은 설명서를 참조하십시오.

	// 일부 공급자와 관련된 몇몇 문제점을 해결하기 위해 아래 코드에서는 
	// 공급자가 보고하는 것과 다른 순서로 열을 바인딩할 수 있습니다.

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


	// 다음 마법사 생성 데이터 멤버에는  열 맵의 해당 
	// 필드에 대한 상태 값이 들어 있습니다. 이 값을
	// 사용하여 데이터베이스에서반환하는 NULL 값을
	// 보유하거나 컴파일러에서 오류를 반환할 때
	// 오류 정보를 보유할 수 있습니다. 이러한 필드 사용에
	// 대한 자세한 내용은 Visual C++ 설명서의
	//  "마법사 생성 접근자"에서 "필드 상태 데이터 멤버"를 참조하십시오.
	// 참고: 데이터를 설정/삽입하기 전에 이들 필드를 초기화해야 합니다.

	DBSTATUS m_dwNTIMEStatus;
	DBSTATUS m_dwNIPStatus;
	DBSTATUS m_dwNPORTStatus;
	DBSTATUS m_dwNDELAYStatus;
	DBSTATUS m_dwNPROCNAMEStatus;
	DBSTATUS m_dwNFINDNAMEStatus;

	// 다음 마법사 생성 데이터 멤버에는 열 맵의 해당 필드에 대한
	// 길이 값이 들어 있습니다.
	// 참고: 가변 길이 열의 경우 데이터를 설정/삽입하기 전에 
//       이러한 	 필드를 초기화해야 합니다.

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
//#error 보안 문제: 연결 문자열에 암호가 포함되어 있을 수 있습니다.
// 아래 연결 문자열에 일반 텍스트 암호 및/또는 
// 다른 중요한 정보가 포함되어 있을 수 있습니다.
// 보안 관련 문제가 있는지 연결 문자열을 검토한 후에 #error을(를) 제거하십시오.
// 다른 형식으로 암호를 저장하거나 다른 사용자 인증을 사용하십시오.
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

// 이 테이블/명령에는 ISequentialStream 인터페이스를 통해
// 액세스할 수 있는 열이 들어 있습니다. 그러나 모든 공급자가
// 이 기능을 지원하는 것은 아니며 이 기능을 지원하는 공급자도
// 보통 하나의 행 집합에 단 하나의 ISequentialStream만 지정하도록 제한을 받습니다.
// 이 접근자의 스트림을 사용하려면 아래의 예제 코드를 사용하고
// DBPROP_ISequentialStream 행 집합 속성을 true로 설정하십시오.
// 그러면 Read() 메서드를 사용하여 데이터를 읽거나
// Write() 메서드를 사용하여 데이터를 쓸 수 있습니다.
// 이렇게 하려면 STGM_READ 스트림 속성을 STGM_WRITE 또는 STGM_READWRITE로
// 변경해야 합니다.
// ISequentialStream 바인딩에 대한 자세한 내용은 설명서를 참조하십시오.

// 일부 공급자와 관련된 몇몇 문제점을 해결하기 위해 아래 코드에서는 
// 공급자가 보고하는 것과 다른 순서로 열을 바인딩할 수 있습니다.

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


