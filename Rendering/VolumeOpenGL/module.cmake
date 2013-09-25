vtk_module(vtkRenderingVolumeOpenGL
  GROUPS
    Rendering
  IMPLEMENTS
    vtkRenderingVolume
  DEPENDS
    vtkRenderingOpenGL
  PRIVATE_DEPENDS
    vtksys
  TEST_DEPENDS
    vtkTestingCore
    vtkTestingRendering
    vtkRenderingFreeType
    vtkImagingSources
    vtkImagingGeneral
    vtkInteractionStyle
  )