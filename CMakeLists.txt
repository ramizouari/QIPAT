cmake_minimum_required(VERSION 3.16)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
include_directories(src)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        DataVisualization
        Test
        REQUIRED)

find_package(muparser REQUIRED)
find_package(Boost COMPONENTS unit_test_framework)


set(UTILITY_SOURCES
        src/utility.h src/utility.cpp)

set(CORE_SOURCES
        src/image/Image.h src/image/Image.cpp
        src/image/ImageReader.h src/image/ImageReader.cpp
        src/image/stats.h src/image/stats.cpp
        src/image/filter/Filter.cpp src/image/filter/Filter.h
        src/image/Padding.cpp src/image/Padding.h
        src/image/noise/ImpulsiveNoise.cpp src/image/noise/ImpulsiveNoise.h
        src/image/noise/Noise.cpp src/image/noise/Noise.h
        src/image/noise/GaussianNoise.cpp src/image/noise/GaussianNoise.h
        src/image/filter/MedianFilter.cpp src/image/filter/MedianFilter.h
        src/image/filter/ConvolutionalFilter.cpp src/image/filter/ConvolutionalFilter.h
        src/image/filter/MeanBlurFilter.cpp src/image/filter/MeanBlurFilter.h
        src/image/filter/edge/LaplacianFilter.cpp src/image/filter/edge/LaplacianFilter.h
        src/image/filter/IdentityFilter.cpp src/image/filter/IdentityFilter.h
        src/image/utils.h src/image/utils.cpp
        src/image/filter/edge/SobelFilter.cpp src/image/filter/edge/SobelFilter.h
        src/image/filter/gray/GrayFilter.cpp src/image/filter/gray/GrayFilter.h
        src/image/filter/gray/MaxChannelFilter.cpp src/image/filter/gray/MaxChannelFilter.h
        src/image/filter/gray/MeanChannelFilter.cpp src/image/filter/gray/MeanChannelFilter.h
        src/image/filter/edge/EdgeDetectionFilter.cpp src/image/filter/edge/EdgeDetectionFilter.h
        src/image/filter/differential/DifferentialFilter.cpp src/image/filter/differential/DifferentialFilter.h
        src/image/filter/differential/SobelOperator.cpp src/image/filter/differential/SobelOperator.h
        src/image/filter/gray/utils.cpp src/image/filter/gray/utils.h
        src/image/filter/differential/LaplacianOperator.cpp src/image/filter/differential/LaplacianOperator.h
        src/image/filter/gray/L1NormChannelFilter.cpp src/image/filter/gray/L1NormChannelFilter.h
        src/image/filter/gray/L2NormChannelFilter.cpp src/image/filter/gray/L2NormChannelFilter.h
        src/image/filter/differential/RobertsOperator.cpp src/image/filter/differential/RobertsOperator.h
        src/image/filter/edge/RobertsFilter.cpp src/image/filter/edge/RobertsFilter.h
        src/image/filter/global/IntensityFilter.cpp src/image/filter/global/IntensityFilter.h
        src/image/filter/global/HistogramEqualization.cpp src/image/filter/global/HistogramEqualization.h
        src/image/filter/global/GlobalFilter.cpp src/image/filter/global/GlobalFilter.h
        src/image/filter/global/IntensityMapper.cpp src/image/filter/global/IntensityMapper.h
        src/image/segmentation/OtsuSegmentation.cpp src/image/segmentation/OtsuSegmentation.h
        src/image/filter/spectral/SpectralFilter.cpp src/image/filter/spectral/SpectralFilter.h
        src/image/morphology/operators.cpp src/image/morphology/operators.h
        src/image/noise/SpeckleNoise.cpp src/image/noise/SpeckleNoise.h
        src/image/filter/GaussianBlurFilter.cpp src/image/filter/GaussianBlurFilter.h
        src/image/segmentation/ThresholdSegmentation.cpp src/image/segmentation/ThresholdSegmentation.h
        src/image/Operator.cpp src/image/Operator.h
        src/image/segmentation/Segmentation.cpp src/image/segmentation/Segmentation.h
        src/image/Mask.cpp src/image/Mask.h
        src/image/ImageWriter.h src/image/ImageWriter.cpp
        src/image/ImageFormat.h
        )
set(GUI_SOURCES
        src/gui/mainwindow.cpp src/gui/mainwindow.h src/gui/mainwindow.ui
        src/gui/histogram/Histogram.cpp src/gui/histogram/Histogram.h src/gui/histogram/histogram.ui
        src/gui/imageview.cpp src/gui/imageview.h src/gui/imageview.ui
        src/gui/histogram/HistogramCurveView.cpp src/gui/histogram/HistogramCurveView.h
        src/gui/statusbar/ImageInformationBar.cpp src/gui/statusbar/ImageInformationBar.h
        src/gui/options/PaddingInput.cpp src/gui/options/PaddingInput.h
        src/gui/options/GrayFilterInput.cpp src/gui/options/GrayFilterInput.h
        src/gui/options/FilterDialog.cpp src/gui/options/FilterDialog.h
        src/gui/histogram/HistogramCurve.cpp src/gui/histogram/HistogramCurve.h
        src/gui/options/ContrastDialog.cpp src/gui/options/ContrastDialog.h
        src/gui/options/ContrastTransformationView.cpp src/gui/options/ContrastTransformationView.h
        src/gui/options/ContrastForm.cpp src/gui/options/ContrastForm.h
        src/gui/options/SpectrumMaskDialog.cpp src/gui/options/SpectrumMaskDialog.h
        src/gui/spectrum/mask/RectangleMaskForm.cpp src/gui/spectrum/mask/RectangleMaskForm.h
        src/gui/spectrum/mask/MaskForm.cpp src/gui/spectrum/mask/MaskForm.h
        src/gui/spectrum/mask/CircleMaskForm.cpp src/gui/spectrum/mask/CircleMaskForm.h
        src/gui/spectrum/mask/RelationalEquationMaskForm.cpp src/gui/spectrum/mask/RelationalEquationMaskForm.h
        src/gui/spectrum/filter/FilterForm.cpp src/gui/spectrum/filter/FilterForm.h
        src/gui/options/SpectrumFilterDialog.cpp src/gui/options/SpectrumFilterDialog.h
        src/gui/spectrum/filter/GaussianBlurForm.cpp src/gui/spectrum/filter/GaussianBlurForm.h
        src/gui/spectrum/filter/MeanBlurForm.cpp src/gui/spectrum/filter/MeanBlurForm.h
        src/gui/spectrum/SpectrumFilterView.cpp src/gui/spectrum/SpectrumFilterView.h
        src/gui/spectrum/filter/MedianForm.cpp src/gui/spectrum/filter/MedianForm.h
        src/gui/spectrum/filter/FunctionFilterForm.cpp src/gui/spectrum/filter/FunctionFilterForm.h
        src/gui/options/MatrixExpression.cpp src/gui/options/MatrixExpression.h
        src/gui/options/MatrixInput.cpp src/gui/options/MatrixInput.h
        src/gui/options/MatrixSheet.cpp src/gui/options/MatrixSheet.h
        src/gui/spectrum/Spectrum3DView.cpp src/gui/spectrum/Spectrum3DView.h
        src/gui/spectrum/SpectrumView.cpp src/gui/spectrum/SpectrumView.h
        src/gui/spectrum/SpectrumMaskView.cpp src/gui/spectrum/SpectrumMaskView.h
        )

set(PARSER_SOURCES
        src/parser/PlanarParser.h
        src/parser/LineParser.h
        src/parser/ParametricParser.h
        src/parser/ImageFunctionParser.cpp src/parser/ImageFunctionParser.h
        )

set(PROJECT_SOURCES
        src/main.cpp
        ${CORE_SOURCES}
        ${GUI_SOURCES}
        ${PARSER_SOURCES}
        ${UTILITY_SOURCES}
        )

add_executable(ImageProcessing
        ${PROJECT_SOURCES}
        )

target_link_libraries(ImageProcessing
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Charts
        Qt::DataVisualization
        muparser
        )

add_executable(LinearAlgebraTest tests/linear_algebra/linear_algebra_approximate_test.cpp tests/linear_algebra/linear_algebra_exact_test.cpp tests/print.h)
add_executable(NumberTheoryTest tests/number_theory/modular_arithmetic_test.cpp tests/number_theory/number_theory_test.cpp tests/print.h)
add_executable(PolynomialTest tests/polynomial/polynomial_test.cpp tests/print.h tests/polynomial/polynomial_test.cpp tests/polynomial/fft_test.cpp)
add_executable(DataStructuresTest tests/data_structures/segment_tree_test.cpp tests/data_structures/fenwick_tree.cpp tests/print.h tests/data_structures/order_statistic_tree_test.cpp)

#add_executable(MachineLearningTest tests/ml/machine_learning_test.cpp tests/print.h)

add_executable(TopologyTest tests/topology/topology_test.cpp tests/print.h)
add_executable(AlgebraTest tests/algebra/abstract_algebra.cpp tests/print.h tests/algebra/binary_operation.cpp)
add_executable(ImageCoreTest tests/image/basic_image_test.cpp ${CORE_SOURCES} tests/image/image_filters_test.cpp tests/image/image_noise_test.cpp)
add_executable(ImageGUITest tests/gui/GUITest.cpp tests/gui/ImageViewTest.cpp tests/gui/ImageViewTest.h
        ${CORE_SOURCES} ${GUI_SOURCES}  ${PARSER_SOURCES} ${UTILITY_SOURCES}
        tests/gui/NoiseReductionScenario.cpp tests/gui/NoiseReductionScenario.h)
target_link_libraries (LinearAlgebraTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} )
target_link_libraries (NumberTheoryTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(PolynomialTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(DataStructuresTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
#target_link_libraries(MachineLearningTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(TopologyTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(AlgebraTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(ImageCoreTest ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(ImageGUITest PRIVATE Qt::Test Qt::Core Qt::Widgets Qt::Gui Qt::Charts Qt::DataVisualization muparser)


# Used for installing

#install(TARGETS  ImageProcessing RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
install(TARGETS ImageProcessing
        RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin
        LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Used for packaging

#include any runtime libraries that are needed by the project for the current plateform
#include(InstallRequiredSystemLibraries)

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
#set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
#set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-0.1-linux")
set(CPACK_GENERATOR TGZ)
set(CPACK_SOURCE_GENERATOR TGZ)
include(CPack)
