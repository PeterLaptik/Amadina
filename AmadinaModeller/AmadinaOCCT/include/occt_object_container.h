#ifndef SKETCH_OCCT_OBJECT_CONATINER_H
#define SKETCH_OCCT_OBJECT_CONATINER_H

#include <AIS_InteractiveObject.hxx>
#include <Geom_Curve.hxx>

#ifdef _WINDLL
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

namespace cad
{
	namespace modeller
	{
		namespace occt
		{
			namespace shapes2D
			{
				///\breaf The interface is corresponded for every visible object, operation, etc. 
				/// Each object corresponded to entity / entities drawn on a screen via OCCT-library appears a container for real OCCT-object.
				/// Creating, deleting and memory management for contained OCCT-objects should be implementet by the object itself.
				/// The object has to support the following interface.
				/// The interface is used by complex operations and composite objects.
				class DLL_EXPORT OcctObjectContainer
				{
					public:
						virtual ~OcctObjectContainer() = default;

						/// Returns list of OCCT AIS_InteractiveObject (objects with display and selection services)
						virtual void GetAisInteractiveObjects(std::vector<Handle(AIS_InteractiveObject)> &container) = 0;

						/// Returns geometric curves for operations (extrusion, etc).
						/// Implementation can be empty, if necessary
						virtual void ExtractGeomCurves(std::vector<Handle(Geom_Curve)> &container) = 0;
				};
			}
		}
	}
}

#endif // !SKETCH_OCCT_OBJECT_CONATINER_H

