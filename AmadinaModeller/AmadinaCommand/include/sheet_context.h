#ifndef AMADINA_SHEET_CONTEXT_H_INCLUDED
#define AMADINA_SHEET_CONTEXT_H_INCLUDED

#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

namespace cad::model
{
    class ModelTree;
    class AbstractCanvas;
}

namespace cad::model::flat
{
    class Sketch;
}

namespace cad::app
{
    class ApplicationContext;
}

namespace cad::app
{
    using cad::model::AbstractCanvas;
    using cad::model::ModelTree;
    using cad::model::flat::Sketch;

    class SheetContext
    {
        public:
            DLL_EXPORT SheetContext(ApplicationContext *app_ctx);
            DLL_EXPORT ~SheetContext() = default;

            DLL_EXPORT void SetModelTree(ModelTree *model_tree);

            DLL_EXPORT void SetActiveSketch(Sketch *sketch);
            DLL_EXPORT Sketch* GetActiveSketch();
            DLL_EXPORT void DeactivateSketch();

        private:
            ApplicationContext *m_app_context = nullptr;
            ModelTree *m_model_tree = nullptr;
            Sketch *m_active_sketch = nullptr;
            AbstractCanvas *m_canvas = nullptr;
    };
}

#endif // AMADINA_SHEET_CONTEXT_H_INCLUDED
