#ifndef WXOCCPANEL_STYLES_H
#define WXOCCPANEL_STYLES_H

#include<string>
#include<map>
#include <Standard_TypeDef.hxx>
#include <Quantity_NameOfColor.hxx>

///\brief
/// Represents colour scheme for a wxOccPanel
// TODO Add line width
class wxOcctPanelStyle final
{
	public:
		wxOcctPanelStyle(Quantity_NameOfColor shading, Quantity_NameOfColor line, Quantity_NameOfColor b_line)
			: m_shading_colour(shading), m_line_clolour(line), m_boundary_colour(b_line)
		{ }

		~wxOcctPanelStyle() = default;

		void SetLineWidth(Standard_Real value)
		{
			m_line_width = value;
		}

		void SetBoundaryWidth(Standard_Real value)
		{
			m_boundary_width = value;;
		}

		Quantity_NameOfColor GetShadingColour() const
		{
			return m_shading_colour;
		}

		Quantity_NameOfColor GetLineColour() const
		{
			return m_line_clolour;
		}

		Quantity_NameOfColor GetBoundaryColour() const
		{
			return m_boundary_colour;
		}

		Standard_Real GetLineWidth() const
		{
			return m_line_width;
		}

		Standard_Real GetBoundaryWidth() const
		{
			return m_boundary_width;
		}

	private:
		// Body
		Quantity_NameOfColor m_shading_colour;
		// Lines
		Quantity_NameOfColor m_line_clolour;
		Standard_Real m_line_width = 1.5;
		// Boundaries
		Quantity_NameOfColor m_boundary_colour;
		Standard_Real m_boundary_width = 1.0;
};


class wxOcctStylesContainer
{
	public:
		wxOcctStylesContainer();

		virtual ~wxOcctStylesContainer() = default;

		wxOcctPanelStyle GetStyle(const std::string &name) const;

	private:
		std::map<std::string, wxOcctPanelStyle> m_styles;
};

#endif // !WXOCCPANEL_STYLES_H

