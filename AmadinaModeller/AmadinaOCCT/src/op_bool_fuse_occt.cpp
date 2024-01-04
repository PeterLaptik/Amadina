#include "op_bool_fuse_occt.h"
#include <BRepBuilderAPI_Sewing.hxx>
#include <TopoDS_Shape.hxx>

void cad::modeller::occt::operations::OpBoolFuseOcct::Draw(AbstractCanvas &cnv)
{
	/*
	BRepBuilderAPI_Sewing sewing;
	std::vector<AbstractShape *> shapes = GetShapes();
	for (auto obj : shapes)
	{
		//sewing.Add(obj);
	}
	*/
}

bool cad::modeller::occt::operations::OpBoolFuseOcct::IsValid()
{
	return false; // !GetShapes().empty();
}

void cad::modeller::occt::operations::OpBoolFuseOcct::Purge(std::vector<AbstractShape *> &container)
{
	/*
	std::vector<AbstractShape*> shapes = GetShapes();
	for (auto obj : container)
	{
		// TODO CHECK
		shapes.erase(std::remove_if(shapes.begin(), shapes.end(), [&](auto e) {return e == obj; }), shapes.end());
	} 
	*/
}
