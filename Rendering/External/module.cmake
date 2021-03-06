vtk_module(vtkRenderingExternal
  TEST_DEPENDS
    vtkglew
    vtkTestingRendering
  EXCLUDE_FROM_ALL
  DEPENDS
    vtkCommonCore
    vtkRenderingOpenGL2
    vtkRenderingCore
  PRIVATE_DEPENDS
    vtkCommonMath
    vtkCommonTransforms
    vtkRenderingOpenGL2
  )
