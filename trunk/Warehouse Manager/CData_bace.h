#pragma once
#include <string>

using namespace std;
class CData_bace
{
public:
	CData_bace(void);
	~CData_bace(void);

	bool CreateId();

	void SetId(const string &id);

	string GetId();
private:
	string m_id;
};
