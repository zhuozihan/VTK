vtk_module(vtkFiltersGeometry
  GROUPS
    StandAlone
  DEPENDS
    vtkFiltersCore
  TEST_DEPENDS
    vtkIOXML
    vtkRenderingOpenGL
    vtkTestingRendering
    vtkInteractionStyle
  )