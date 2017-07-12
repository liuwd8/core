﻿/*
 * (c) Copyright Ascensio System SIA 2010-2017
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at Lubanas st. 125a-25, Riga, Latvia,
 * EU, LV-1021.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */

#include "SXFORMULA_bu.h"

#include "SXFMLA_bu.h"
#include "PIVOTRULE.h"

#include "../Biff_records/SXFormula.h"
#include "../Biff_records/SxFmla.h"
#include "../Biff_records/SxName.h"
#include "../Biff_records/SXPair.h"

namespace XLS
{

SXFORMULA::SXFORMULA()
{
}

SXFORMULA::~SXFORMULA()
{
}

BaseObjectPtr SXFORMULA::clone()
{
	return BaseObjectPtr(new SXFORMULA(*this));
}


// SXFORMULA = SXFMLA PIVOTRULE SXFormula
const bool SXFORMULA::loadContent(BinProcessor& proc)
{
	global_info = proc.getGlobalWorkbookInfo();

	if(!proc.mandatory<SXFMLA>())
	{
		return false;
	}
	m_SXFMLA = elements_.back();
	elements_.pop_back();

	if(proc.mandatory<PIVOTRULE>())
	{
		m_PIVOTRULE = elements_.back();
		elements_.pop_back();
	}
	if(proc.mandatory<SXFormula>())
	{
		m_SXFormula = elements_.back();
		elements_.pop_back();
	}	return true;
}
int SXFORMULA::serialize(std::wostream & strm)
{
	SXFMLA* fmla = dynamic_cast<SXFMLA*>(m_SXFMLA.get());
	if (!fmla) return 0;

	SxFmla* sx_fmla	= dynamic_cast<SxFmla*>(fmla->m_SxFmla.get()); 

	CP_XML_WRITER(strm)
	{
		CP_XML_NODE(L"calculatedItem")
		{
			CP_XML_ATTR(L"formula", sx_fmla->fmla.getAssembledFormula());
			
			//for (size_t j = 0; j < global_info->arPivotSxNames.size(); j++)//???
			//{
			//	SxName *name = dynamic_cast<SxName*>(global_info->arPivotSxNames[j].m_SxName.get());
			//	CP_XML_NODE(L"pivotArea")
			//	{
			//	}
			//}
		}
	}
	return 0;
}
} // namespace XLS
