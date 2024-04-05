#include "wxoccpanel_styles.h"

const char * const STYLE_DEFAULT = "default";

wxOcctStylesContainer::wxOcctStylesContainer()
{
	wxOcctPanelStyle default_style(Quantity_NOC_GRAY70, Quantity_NOC_BLUE, Quantity_NOC_BLACK);
	m_styles.insert(std::pair<std::string, wxOcctPanelStyle>(STYLE_DEFAULT, default_style));
}

wxOcctPanelStyle wxOcctStylesContainer::GetStyle(const std::string &name) const
{
	auto it = m_styles.find(name);
	if (it != m_styles.end())
		return it->second;

	return m_styles.find(STYLE_DEFAULT)->second;
}

