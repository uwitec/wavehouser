#include "StdAfx.h"
#include "CControl_check.h"
#include "CControl_material.h"
CControl_check::CControl_check(void)
{
}

CControl_check::~CControl_check(void)
{
}

void CControl_check::SetData( CDate_check *data )
{
	m_data = data;
}

bool CControl_check::Save()
{
	CControl_material tmp;
	if(!tmp.UpdataTotal(&m_data->m_material))
		return false;

	if(m_data->GetId().empty())
	{		
		m_data->CreateId();

		string sql = "insert into tab_check values('";
		sql += m_data->GetId();
		sql += "','";
		sql += m_data->m_userInfo.GetId();
		sql += "','";
		sql += m_data->m_material.GetId();
		sql += "','";
		sql += m_data->m_class.GetId();
		sql += "','";
		sql += CControl_bace::s_wareHouse.GetId();
		sql += "','";
		sql += m_data->m_checkModal == 1 ? "1":"0";
		sql += "','";
		char cTmp[20] = {0};
		itoa(m_data->m_num,cTmp,10);
		sql += cTmp;
		sql += "','";

		memset(cTmp,0,20);
		ltoa(m_data->m_total,cTmp,10);

		sql += cTmp;
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_tellPhone);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_detail);
		sql += "','";
		sql += CControl_bace::s_user.GetId();
		sql += "','";
		sql += m_dateChange.GetCurTimes();
		sql +="','0')";
		//return CADOOperate::ExecuteSQL(sql);
		return g_sqlite.DirectStatement(m_dateChange.Unicode2Utf8(sql));
	}
			
	return Updata();	
}

bool CControl_check::Delete()
{
	if(m_data->GetId().empty())
		return false;

	string sql = "update tab_check set del_flag='1' where id='";
	sql += m_data->GetId();
	sql += "';";
	//return CADOOperate::ExecuteSQL(sql);
	return g_sqlite.DirectStatement(m_dateChange.Unicode2Utf8(sql));
}

bool CControl_check::Updata()
{
	string sql = "update tab_check set u_id='";
	sql += m_data->m_userInfo.GetId();
	sql += "', m_id='";
	sql += m_data->m_material.GetId();
	sql += "', c_id='";
	sql += m_data->m_class.GetId();
	sql += "', w_id='";
	sql += CControl_bace::s_wareHouse.GetId();
	sql += "', num='";
	char cTmp[20] = {0};
	itoa(m_data->m_num,cTmp,10);
	sql += (string)cTmp;

	sql += "', total='";
	memset(cTmp,0,20);
	ltoa(m_data->m_total,cTmp,10);
	sql += (string)cTmp;

	sql += "', tellphone='";
	sql += m_dateChange.CStringtostring(m_data->m_tellPhone);
	sql += "',detail='";
	sql += m_dateChange.CStringtostring(m_data->m_detail);
	sql += "',create_time='";
	sql += m_dateChange.GetCurTimes();
	sql +="' where id='";
	sql += m_data->GetId();
	sql += "';";
	//return CADOOperate::ExecuteSQL(sql);
	return g_sqlite.DirectStatement(m_dateChange.Unicode2Utf8(sql));
}

bool CControl_check::Search()
{
	return false;
}

vector<CDate_check> CControl_check::SearchList_Check( CDate_search condition )
{
	vector<CDate_check> result;

	string sql = "SELECT ";
	sql += "  tch.id,tma.id,tcl.id,tus.id,tch.modal,tma.material_name,tma.material_modal,tcl.class_name,tus.user_name,tch.tellphone,tch.num,tch.total,tch.create_time,tch.detail ";
	sql += "FROM tab_check tch ";
	sql += "LEFT JOIN tab_class tcl ON tch.c_id=tcl.id ";//"and tcl.del_flag='0' ";
	sql += "LEFT JOIN tab_user tus ON tch.u_id = tus.id ";//"and tus.del_flag='0' ";
	sql += "LEFT JOIN tab_material tma ON tch.m_id=tma.id  ";//"and tma.del_flag='0' ";
	sql += " where ";
	if(!condition.m_name.IsEmpty()) //材料名
		sql = sql + " tma.material_name like '%"+ m_dateChange.CStringtostring(condition.m_name) + "%' and ";
	if(!condition.m_class.IsEmpty() && condition.m_class != _T("0")) //部门
		sql = sql + "tcl.id='" +m_dateChange.CStringtostring(condition.m_class) + "' and ";
	if(!condition.m_pName.IsEmpty() && condition.m_pName != _T("0")) //人员
		sql = sql + " tus.id='" +m_dateChange.CStringtostring(condition.m_pName) + "' and ";
	if(!condition.m_checkModal.IsEmpty() && condition.m_checkModal != _T("-1"))
		sql = sql + " tch.modal='" +m_dateChange.CStringtostring(condition.m_checkModal) + "' and ";
	if(!condition.m_tBegin.IsEmpty() && !condition.m_tEnd.IsEmpty())
	{
		if (condition.m_tBegin.IsEmpty() == condition.m_tEnd)
			sql = sql + "tch.create_time == '" + m_dateChange.CStringtostring(condition.m_tBegin) + "' and ";
		else
			sql = sql + "tch.create_time >= '" + m_dateChange.CStringtostring(condition.m_tBegin) + " 00:00:00' and tch.create_time <= '" + m_dateChange.CStringtostring(condition.m_tEnd) + " 23:59:59' and ";
	}
	if(!condition.GetKeyword().empty())
	{
		sql = sql + "(( tma.material_name like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "tma.material_modal like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "tma.material_manuf like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "tma.material_price like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "tma.material_unit like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "tma.detail like '%" + condition.GetKeyword() + "%'	) or ";

		sql = sql + "( tus.user_name like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "tus.user_tellphone like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "tus.user_email like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "tus.user_age like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "tus.detail like '%" + condition.GetKeyword() + "%'	) or ";

		sql = sql + "( tcl.class_name like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "tcl.p_name like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "tcl.c_name like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "tcl.tellphone like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "tcl.detail like '%" + condition.GetKeyword() + "%'	)) and ";

	}
	sql += " tch.del_flag='0' and tch.create_by ='";
	sql += CControl_bace::s_user.GetId();
	sql += "'";

	SQLiteStatement* stmt=g_sqlite.Statement(m_dateChange.Unicode2Utf8(sql));

	while(stmt->NextRow())
	{
		CDate_check tmp;
		tmp.SetId(stmt->ValueString (0));
		tmp.m_material.SetId( stmt->ValueString(1));
		tmp.m_class.SetId(    stmt->ValueString(2));
		tmp.m_userInfo.SetId( stmt->ValueString(3));
		tmp.m_checkModal       = atoi(m_dateChange.Utf82Unicode(stmt->ValueString (4)).c_str());
		tmp.m_material.m_name  = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (5)));
		tmp.m_material.m_modal = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (6)));
		tmp.m_class.m_name     = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (7)));
		tmp.m_userInfo.m_name  = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (8)));
		tmp.m_tellPhone        = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (9)));
		tmp.m_num              = atoi(m_dateChange.Utf82Unicode(stmt->ValueString (10)).c_str());
		tmp.m_total            = atol(m_dateChange.Utf82Unicode(stmt->ValueString (11)).c_str());
		tmp.m_time             = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (12)));
		tmp.m_detail           = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (13)));

		//tmp.SetDel(m_dateChange.Utf82Unicode(stmt->ValueString (9) == "0"));
		result.push_back(tmp);
	}
	return result;
}

int CControl_check::VerCheckMaterial( const string &id )
{
	int result = 0;
	CControl_material tmp;

	CDate_Material tmpM = tmp.Search_byId(id);
	if(!tmpM.GetId().empty() && !tmpM.m_total.IsEmpty())
	{
		result = atoi(m_dateChange.CStringtostring(tmpM.m_total).c_str()) > 0;		
	}
	return result;
}
